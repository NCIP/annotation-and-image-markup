/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.system.exception;


/**
 * @author Vitaliy Semeshko
 */
public class ATSException extends ATBException {

	public ATSException(String message) {
		super(message);
	}

	public ATSException(Throwable cause) {
		super(cause);
	}
	
	public ATSException(String message, Throwable cause) {
		super(message, cause);
	}
	
	@Override
	public boolean isCritical() {
		return false;
	}
	
}
