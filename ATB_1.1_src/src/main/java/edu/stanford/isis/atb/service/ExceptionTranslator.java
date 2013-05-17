/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.service;

import java.util.HashMap;
import java.util.Map;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.jdbc.CannotGetJdbcConnectionException;

import edu.stanford.isis.atb.Main;
import edu.stanford.isis.atb.ui.Const;

/**
 * @author Vitaliy Semeshko
 */
public class ExceptionTranslator {

	private static final Map<Class<?>, Throwable> rules = new HashMap<Class<?>, Throwable>();
	
	private static final ExceptionTranslator instance = new ExceptionTranslator(); 
	
	private final Logger logger = LoggerFactory.getLogger(Main.class);
	
	private ExceptionTranslator() {
		rules.put(CannotGetJdbcConnectionException.class, new RuntimeException(Const.MSG_CANT_CONNECT_TO_DB));
	}
	
	public static ExceptionTranslator getInstance() {
		return instance;
	}
	
	public Throwable translate(Throwable originalException) {
		Throwable ex = rules.get(originalException.getClass());
		
		if (logger.isInfoEnabled()) {
			if (ex == null) {
				logger.info("No translation for exception " + originalException);
			} else {
				logger.info("Exception " + originalException + " translated to " + ex);
			}
		}
		
		return ex == null ? originalException : ex;
	}
	
}
