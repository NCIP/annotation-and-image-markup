/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.system.config;

import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;

import org.apache.commons.io.IOUtils;

import edu.stanford.isis.atb.system.exception.ATBException;
import edu.stanford.isis.atb.system.resources.ResourceManager;

/**
 * Property manager.
 * 
 * @author Alexander Semeshko
 */
public class PropertyManager {
	
	private static final String ATB_PROPERTIES = "conf/atb.properties";
	
	// available properties
	public static final String CA_GRID_USER_NAME = "caGridUsername";
	public static final String HELP_URL = "helpPageBaseUrl";
	public static final String VERSION = "version";
	
	public static final String ATS_BASE_URL = "atsBaseUrl";
	public static final String ATS_TEMPLATE_COLLECTION = "atsTemplateCollection";
	public static final String ATS_SEARCH_SUCCESS_MARKER = "atsSearchSuccessMarker";
	public static final String ATS_PUBLISH_SUCCESS_MARKER = "atsPublishSuccessMarker";
	public static final String ATS_EXPIRED_SESSION_MARKER = "atsExpiredSessionMarker";

	private static PropertyManager instance = new PropertyManager();
	
	private Properties properties = new Properties();
	
	private PropertyManager() {
		try {
			InputStream inputStrem = ResourceManager.getInstance().getResourceAsStream(ATB_PROPERTIES); 
			try {
				properties.load(inputStrem);
			} finally {
				IOUtils.closeQuietly(inputStrem);
			}
		} catch (IOException e) {
			throw new ATBException("Could not load atb.properties file", e);
		}
	}
	
	public static PropertyManager getInstance() {
		return instance;
	}
	
	public String get(String key) {
		String value = properties.getProperty(key);
		if (value == null) {
			throw new ATBException("Property: " + key + " not found");
		}
		return value;
	}
	
}
