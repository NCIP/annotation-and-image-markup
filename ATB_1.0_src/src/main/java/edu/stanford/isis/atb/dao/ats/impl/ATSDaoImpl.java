/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.dao.ats.impl;

import static edu.stanford.isis.atb.system.config.PropertyManager.ATS_EXPIRED_SESSION_MARKER;
import static edu.stanford.isis.atb.system.config.PropertyManager.ATS_PUBLISH_SUCCESS_MARKER;
import static edu.stanford.isis.atb.system.config.PropertyManager.ATS_SEARCH_SUCCESS_MARKER;
import static edu.stanford.isis.atb.system.config.PropertyManager.ATS_TEMPLATE_COLLECTION;

import java.io.InputStream;
import java.net.URL;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import org.apache.commons.lang3.StringUtils;
import org.simpleframework.xml.Serializer;
import org.simpleframework.xml.core.Persister;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.core.io.Resource;
import org.springframework.http.HttpEntity;
import org.springframework.http.HttpHeaders;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Repository;
import org.springframework.util.LinkedMultiValueMap;
import org.springframework.util.MultiValueMap;
import org.springframework.web.client.RestTemplate;

import edu.stanford.isis.atb.dao.ats.ATSDao;
import edu.stanford.isis.atb.domain.ats.ContainerResults;
import edu.stanford.isis.atb.domain.ats.ContainerSearchRequest;
import edu.stanford.isis.atb.domain.ats.TemplateResults;
import edu.stanford.isis.atb.domain.ats.TemplateSearchRequest;
import edu.stanford.isis.atb.system.UserSession;
import edu.stanford.isis.atb.system.config.PropertyManager;
import edu.stanford.isis.atb.system.exception.ATBException;
import edu.stanford.isis.atb.system.exception.ATSException;
import edu.stanford.isis.atb.system.exception.ATSLoginException;

/**
 * @author Vitaliy Semeshko
 */

@Repository
public class ATSDaoImpl implements ATSDao {
	
	private static final Logger logger = LoggerFactory.getLogger(ATSDaoImpl.class);
	
	private static final String ATB_USER_AGENT = "\"ATB\"";

	private static final String HEADER_USER_AGENT = "User-Agent";
	private static final String HEADER_COOKIE = "Cookie";
	private static final String HEADER_SET_COOKIE = "Set-Cookie";

	private static final String PARAM_USER = "user";
	private static final String PARAM_PASS = "pass";
	private static final String PARAM_XML_FILE = "xmlfile";
	private static final String PARAM_COLLECTION = "collection";
	
	private static final String ATS_BASE_URL = PropertyManager.getInstance().get(PropertyManager.ATS_BASE_URL);
	private static final String LOGIN_URL = ATS_BASE_URL + "/templates/login";
	private static final String SEARCH_URL = ATS_BASE_URL +  "/templates/search";
	private static final String DOWNLOAD_URL = ATS_BASE_URL + "/templates/download?uid=";
	private static final String PUBLISH_URL = ATS_BASE_URL + "/templates/upload";
	
	private static final String ATS_SESSION_COOKIES = "ATSSessionCookie";
	
	// session cookie pattern (Example: ATSSessionCookie=1315898886796A-2054455053)
	private static final Pattern SESSION_PATTERN = Pattern.compile("ATSSessionCookie=(.*)");
	
	@Autowired
	private RestTemplate rest;

	private PropertyManager properties = PropertyManager.getInstance();
	
	private Serializer serializer = new Persister();

	@Override
	public TemplateResults searchTemplates(TemplateSearchRequest request) {
		HttpEntity<?> entity = new HttpEntity<MultiValueMap<String, String>>(request.asParams(), getDefaultHeaders());
		
		logRequest(entity);
		
		ResponseEntity<String> response = rest.postForEntity(SEARCH_URL, entity, String.class);
		String responseText = response.getBody();
		
		logResponse(responseText);
		
		if (StringUtils.isEmpty(responseText) || !responseText.contains(properties.get(ATS_SEARCH_SUCCESS_MARKER))) {
			throw new ATSException("Search operation failed");
		}

		try {
			return serializer.read(TemplateResults.class, response.getBody());
		} catch (Exception e) {
			throw new ATSException("Can't parse ATS response", e);
		}
	}
	
	@Override
	public ContainerResults searchContainers(ContainerSearchRequest request) {
		HttpEntity<?> entity = new HttpEntity<MultiValueMap<String, String>>(request.asParams(), getDefaultHeaders());
		
		logRequest(entity);
		
		ResponseEntity<String> response = rest.postForEntity(SEARCH_URL, entity, String.class);
		String responseText = response.getBody();
		
		logResponse(responseText);
		
		if (StringUtils.isEmpty(responseText) || !responseText.contains(properties.get(ATS_SEARCH_SUCCESS_MARKER))) {
			throw new ATSException("Search operation failed");
		}

		try {
			return serializer.read(ContainerResults.class, response.getBody());
		} catch (Exception e) {
			throw new ATSException("Can't parse ATS response", e);
		}
	}

	@Override
	public InputStream download(String uid) {
		String url = DOWNLOAD_URL + uid;
		try {
			return new URL(url).openStream();
		} catch (Exception e) {
			throw new ATBException("Can't download template from: " + url, e);
		}
	}
	
	@Override
	public String loginAndReturnSessionId(String userName, String password) {
		MultiValueMap<String, String> params = new LinkedMultiValueMap<String, String>();
		params.add(PARAM_USER, userName);
		params.add(PARAM_PASS, password);

		HttpEntity<?> entity = new HttpEntity<MultiValueMap<String, String>>(params, getDefaultHeaders());

		logRequest(entity);
		
		ResponseEntity<String> response = rest.postForEntity(LOGIN_URL, entity, String.class);
		
		logResponse(response.getBody());
		
		List<String> cookies = response.getHeaders().get(HEADER_SET_COOKIE);
		if (cookies != null) {
			for (String cookie : cookies) {
				Matcher m = SESSION_PATTERN.matcher(cookie);
				if (m.find() && m.groupCount() == 1) {
					return m.group(1);
				}
			}
		}

		return null;
	}
	
	@Override
	public void uploadContainer(Resource container) {
		String sessionCookie = ATS_SESSION_COOKIES + "=" + UserSession.getInstance().getATSSessionId();
		HttpHeaders headers = getDefaultHeaders();
		headers.add(HEADER_COOKIE, sessionCookie);

		MultiValueMap<String, Object> params = new LinkedMultiValueMap<String, Object>();
		params.add(PARAM_COLLECTION, properties.get(ATS_TEMPLATE_COLLECTION));
		params.add(PARAM_XML_FILE, container);
		
		HttpEntity<?> entity = new HttpEntity<MultiValueMap<String, Object>>(params, headers);
		
		logRequest(entity);
		
		ResponseEntity<String> response = rest.postForEntity(PUBLISH_URL, entity, String.class);
		String responseText = response.getBody(); 
		
		logResponse(responseText);
		
		if (StringUtils.isEmpty(responseText)) {
			throw new ATSException("Publish operation failed with no details.");
		}
		
		if (responseText.contains(properties.get(ATS_EXPIRED_SESSION_MARKER))) {
			throw new ATSLoginException("Session expired.");
		}
		
		if (!responseText.contains(properties.get(ATS_PUBLISH_SUCCESS_MARKER))) {
			throw new ATSException("Publish operation failed:\n" + responseText);
		}
	}

	private HttpHeaders getDefaultHeaders() {
		HttpHeaders headers = new HttpHeaders();
		headers.add(HEADER_USER_AGENT, ATB_USER_AGENT);
		return headers;
	}

	private void logRequest(HttpEntity<?> entity) {
		if (logger.isDebugEnabled()) {
			// log headers
			HttpHeaders headers = entity.getHeaders();
			if (headers != null) {
				logger.debug("Headers: " + headers.toSingleValueMap());
			}
			
			// log parameters
			Object params = entity.getBody();
			if (params instanceof MultiValueMap<?,?>) {
				if (params != null) {
					logger.debug("Parameters: " + ((MultiValueMap<?,?>) params).toString());
				}
			}
		}
	}
	
	private void logResponse(String responseText) {
		if (logger.isDebugEnabled()) {
			logger.debug(responseText);
		}
	}
	
}
