/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.system.exception;

import edu.stanford.isis.atb.ui.Const;

/**
 * General exception.
 * 
 * @author Vitaliy Semeshko
 */
public class ATBException extends RuntimeException {

	public ATBException(String message) {
		super(message);
	}

	public ATBException(String message, Throwable cause) {
		super(message, cause);
	}

	public ATBException(Throwable cause) {
		super(Const.EMPTY, cause);
	}

	public boolean isCritical() {
		return true;
	}
	
}
