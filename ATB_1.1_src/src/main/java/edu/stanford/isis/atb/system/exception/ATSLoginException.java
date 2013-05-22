/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.system.exception;


/**
 * @author Vitaliy Semeshko
 */
public class ATSLoginException extends ATSException {

	public ATSLoginException(String message) {
		super(message);
	}

	public ATSLoginException(Throwable cause) {
		super(cause);
	}
	
}
