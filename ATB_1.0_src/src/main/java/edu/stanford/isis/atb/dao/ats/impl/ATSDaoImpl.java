/*
 * Copyright Notice. Copyright 2011 Northwestern University and Stanford
 * University (“caBIG® Participant”). AIM Template Enterprise Service conforms
 * to caBIG® technical specifications and is part of the caBIG® initiative. The
 * software subject to this notice and license includes human readable source
 * code form, machine readable, binary, object code form and related
 * documentation (the “caBIG® Software”).
 *
 * This caBIG® Software License (the “License”) is between the National Cancer
 * Institute (NCI) and You. “You (or “Your”) shall mean a person or an entity,
 * and all other entities that control, are controlled by, or are under common
 * control with the entity. “Control” for purposes of this definition means (i)
 * the direct or indirect power to cause the direction or management of such
 * entity, whether by contract or otherwise, or (ii) ownership of fifty percent
 * (50%) or more of the outstanding shares, or (iii) beneficial ownership of
 * such entity.
 *
 * Provided that You agree to the conditions described below, NCI grants You a
 * non-exclusive, worldwide, perpetual, fully-paid-up, no-charge, irrevocable,
 * transferable and royalty-free right and license in its rights in the caBIG®
 * Software, including any copyright or patent rights therein, to (i) use,
 * install, disclose, access, operate, execute, reproduce, copy, modify,
 * translate, market, publicly display, publicly perform, and prepare
 * derivative works of the caBIG® Software in any manner and for any purpose,
 * and to have or permit others to do so; (ii) make, have made, use, practice,
 * sell, and offer for sale, import, and/or otherwise dispose of caBIG®
 * Software (or portions thereof); (iii) distribute and have distributed to and
 * by third parties the caBIG® Software and any modifications and derivative
 * works thereof; and (iv) sublicense the foregoing rights set out in (i), (ii)
 * and (iii) to third parties, including the right to license such rights to
 * further third parties. For sake of clarity, and not by way of limitation,
 * NCI shall have no right of accounting or right of payment from You or Your
 * sublicensees for the rights granted under this License. This License is
 * granted at no charge to You. Your downloading, copying, modifying,
 * displaying, distributing or use of caBIG® Software constitutes acceptance of
 * all of the terms and conditions of this Agreement. If you do not agree to
 * such terms and conditions, you have no right to download, copy, modify,
 * display, distribute or use the caBIG® Software.
 *
 * Your redistributions of the source code for the caBIG® Software must retain
 * the above copyright notice, this list of conditions and the disclaimer and
 * limitation of liability of Article 6 below. Your redistributions in object
 * code form must reproduce the above copyright notice, this list of conditions
 * and the disclaimer of Article 6 in the documentation and/or other materials
 * provided with the distribution, if any.
 *
 * Your end-user documentation included with the redistribution, if any, must
 * include the following acknowledgment: “This product includes software
 * developed by Danny Korenblum, Alan Snyder, Vitaliy Semeshko, Vladimir Kleper
 * and Pattanasak Mongkolwat, Northwestern University and Stanford University.”
 * If You do not include such end-user documentation, You shall include this
 * acknowledgment in the caBIG® Software itself, wherever such third-party
 * acknowledgments normally appear.
 *
 * You may not use the names “Northwestern University”, “Stanford University”,
 * “The National Cancer Institute”, “NCI”, “Cancer Bioinformatics Grid” or
 * “caBIG®” to endorse or promote products derived from this caBIG® Software.
 * This License does not authorize You to use any trademarks, service marks,
 * trade names, logos or product names of either caBIG® Participant, NCI or
 * caBIG®, except as required to comply with the terms of this License.
 *
 * For sake of clarity, and not by way of limitation, You are not prohibited by
 * this License from incorporating this caBIG® Software into Your proprietary
 * programs and into any third party proprietary programs. However, if You
 * incorporate the caBIG® Software into third party proprietary programs, You
 * agree that You are solely responsible for obtaining any permission from such
 * third parties required to incorporate the caBIG® Software into such third
 * party proprietary programs and for informing Your sublicensees, including
 * without limitation Your end-users, of their obligation to secure any
 * required permissions from such third parties before incorporating the caBIG®
 * Software into such third party proprietary software programs. In the event
 * that You fail to obtain such permissions, You agree to indemnify NCI for any
 * claims against NCI by such third parties, except to the extent prohibited by
 * law, resulting from Your failure to obtain such permissions.
 * For sake of clarity, and not by way of limitation, You may add Your own
 * copyright statement to Your modifications and to the derivative works, and
 * You may provide additional or different license terms and conditions in
 * Your sublicenses of modifications of the caBIG® Software, or any derivative
 * works of the caBIG® Software as a whole, provided Your use, reproduction,
 * and distribution of the Work otherwise complies with the conditions stated
 * in this License.
 *
 * THIS caBIG® SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES (INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE) ARE
 * DISCLAIMED. IN NO EVENT SHALL NCI OR THE NORTHWESTERN UNIVERSITY OR ITS
 * AFFILIATES BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS caBIG® SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
