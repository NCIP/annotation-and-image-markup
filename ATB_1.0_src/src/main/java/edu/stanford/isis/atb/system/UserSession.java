/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.system;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.LinkedHashSet;
import java.util.List;
import java.util.Properties;
import java.util.Set;

import org.apache.commons.io.IOUtils;
import org.apache.commons.lang3.StringUtils;

import edu.stanford.isis.atb.system.config.PropertyManager;
import edu.stanford.isis.atb.system.exception.ATBException;
import edu.stanford.isis.atb.system.resources.ResourceManager;
import edu.stanford.isis.atb.ui.Const;

/**
 * @author Vitaliy Semeshko
 */
public class UserSession {

	public static final String SESSION_DIR = "etc/session";
	private static final String SESSION_FILE = "%s.session";
	
	private static final int LOCAL_LEXICON_SEARCH_HISTORY_MAX_SIZE = 15;
	
	private static final String ANONYMOUS = "anonymous";
	private static final String ATS_USER_NAME = "userName";
	private static final String ATS_SESSION_ID = "atsSessionId";
	private static final String LOCAL_LEXICON_SEARCH_HISTORY = "localLexiconSearchHistory";
	private static final String TEMPLATE_IMPORT_EXPORT_PATH = "templateImportExportPath";
	private static final String LEXICON_IMPORT_EXPORT_PATH = "lexiconImportExportPath";
	
	private static final String COLLECTION_ELEMENT_SEPARATOR = "<PRPRT_SPRTR>";
	
	private static final UserSession instance = new UserSession();
	
	private ResourceManager resourceManager = ResourceManager.getInstance();
	
	private Properties properties = new Properties();
	
	private UserSession() {
		String userName = getUserName();
		
		String sessionResourceFile = String.format(SESSION_FILE, userName);
		String sessionResourceName = SESSION_DIR + Const.R_SEP + sessionResourceFile;
		
		if (resourceManager.isExists(sessionResourceName)) {
			try {
				InputStream inputStrem = resourceManager.getResourceAsStream(sessionResourceName); 
				try {
					properties.load(inputStrem);
				} finally {
					IOUtils.closeQuietly(inputStrem);
				}
			} catch (IOException e) {
				throw new ATBException("Could not load session information: " + sessionResourceFile, e);
			}
		} else {
			properties.setProperty(ATS_USER_NAME, userName);
			save();
		}
	}
	
	public static UserSession getInstance() {
		return instance;
	}
	
	public String getATSUserName() {
		return properties.getProperty(ATS_USER_NAME);
	}
	
	public String getATSSessionId() {
		return properties.getProperty(ATS_SESSION_ID);
	}
	
	public void setATSSessionId(String sessionId) {
		properties.setProperty(ATS_SESSION_ID, sessionId);
		save();
	}
	
	public String getTemplateImportExportPath() {
		return properties.getProperty(TEMPLATE_IMPORT_EXPORT_PATH);
	}
	
	public void setTemplateImportExportPath(String path) {
		properties.setProperty(TEMPLATE_IMPORT_EXPORT_PATH, path);
		save();
	}
	
	public String getLexiconImportExportPath() {
		return properties.getProperty(LEXICON_IMPORT_EXPORT_PATH);
	}
	
	public void setLexiconImportExportPath(String path) {
		properties.setProperty(LEXICON_IMPORT_EXPORT_PATH, path);
		save();
	}
	
	public void addLocalSearchHistoryText(String text) {
		List<String> currentHistory = new ArrayList<String>(getList(LOCAL_LEXICON_SEARCH_HISTORY));
		
		// add to the start
		currentHistory.add(0, text);

		// need to store only unique values in the same order
		Set<String> historyUnique = new LinkedHashSet<String>(currentHistory);
		
		List<String> history = new ArrayList<String>();
		for (String s : historyUnique) {
			if (history.size() < LOCAL_LEXICON_SEARCH_HISTORY_MAX_SIZE) {
				history.add(s);
			} else {
				break;
			}
		}
		
		setList(LOCAL_LEXICON_SEARCH_HISTORY, history);
	}
	
	public List<String> getLocalSearchHistory() {
		return getList(LOCAL_LEXICON_SEARCH_HISTORY);
	}
	
	private String getUserName() {
		String userName = PropertyManager.getInstance().get(PropertyManager.CA_GRID_USER_NAME);
		
		if (StringUtils.isEmpty(userName)) {
			userName = ANONYMOUS;
		}
		
		return userName;
	}
	
	private void save() {
		String sessionResourceFile = String.format(SESSION_FILE, getUserName());
		String path = resourceManager.getAbsoluteResourcePath(SESSION_DIR) + File.separator + sessionResourceFile;
		try {
			properties.store(new FileOutputStream(path), Const.EMPTY);
		} catch (Exception e) {
			throw new ATBException("Could not create session information file: " + sessionResourceFile, e);
		}
	}
	
	private List<String> getList(String key) {
		String value = properties.getProperty(key);
		if (value == null) {
			return Collections.emptyList();
		}
		String[] result = value.split(COLLECTION_ELEMENT_SEPARATOR);
		return Arrays.asList(result);
	}
	
	private void setList(String key, List<String> values) {
		StringBuffer value = new StringBuffer();
		
		for (String s : values) {
			value.append(s).append(COLLECTION_ELEMENT_SEPARATOR);
		}
		
		properties.setProperty(key, value.toString());
		save();
	}

}
