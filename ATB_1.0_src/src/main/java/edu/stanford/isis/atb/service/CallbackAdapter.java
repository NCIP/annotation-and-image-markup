/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.service;

import org.apache.commons.lang3.StringUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import edu.stanford.isis.atb.system.exception.ATBException;
import edu.stanford.isis.atb.ui.Const;

/**
 * @author Vitaliy Semeshko
 */
public abstract class CallbackAdapter<T> implements Callback<T> {

	private static final Logger logger = LoggerFactory.getLogger(CallbackAdapter.class);
	
	@Override
	public final void onFailure(Throwable caught) {
		// wrap into ATBException 
		ATBException ex = null;
		if (caught instanceof ATBException) {
			ex = (ATBException) caught;
		} else {
			ex = new ATBException(caught);
		}
		
		// handle exception here
		if (ex.isCritical()) {
			logger.error("Critical operation failed...", caught);
		} else {
			logger.warn("Non-critical operation failed...", caught);
		}
		
		onFailure(ex);
	}
	
	protected abstract void onFailure(ATBException caught);
	
	protected String getErrorInformation(ATBException caught) {
		return getErrorInformation(Const.EMPTY, caught);
	}
	
	protected String getErrorInformation(String msg, ATBException caught) {
		String errorText = caught.getMessage();
		Throwable cause = caught.getCause();  
		
		if (cause != null) {
			if (StringUtils.isNotEmpty(errorText)) {
				errorText = errorText + "\n" + cause.getMessage();
			} else {
				errorText = cause.getMessage();
			}
		}
		
		if (StringUtils.isNotEmpty(msg)) {
			if (StringUtils.isNotEmpty(errorText)) {
				return msg + "\n\n" + errorText;
			} else {
				return msg;
			}
		
		}
		return errorText;
	}
	
}
