/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.ats.utils;

/**
 * @author Vladimir Kleper
 */
public class ATSException extends Exception {
    private static final long serialVersionUID = 77377201238837505L;

    public ATSException() {
        super();
    }

    public ATSException(String message) {
        super(message);
    }

    public ATSException(String message, Throwable cause) {
        super(message, cause);
    }

    public ATSException(Throwable cause) {
        super(cause);
    }
}
