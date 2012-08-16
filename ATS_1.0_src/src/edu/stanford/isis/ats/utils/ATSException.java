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
