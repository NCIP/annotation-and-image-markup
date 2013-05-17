/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.ats.security;

import edu.stanford.isis.ats.security.impl.SessionStatus;
import java.util.HashSet;
import java.util.Set;

/**
 * Message class to
 * @author alansnyder
 */
public class SecurityStatus {

    private boolean isValidSession;

    //private String sessionUserName;
    SessionStatus sessionStatus;

    private String message;

    public SecurityStatus(String message, boolean session, SessionStatus sessionStatus){
        isValidSession = session;
        this.message = message;
        //sessionUserName = user;
        this.sessionStatus = sessionStatus;
    }

    /**
     * Is this a valid session?
     * @return boolean
     */
    public boolean hasValidSession(){
        return isValidSession;
    }
    
    /**
     * 
     * @return String
     */
    public String getMessage(){
        return message;
    }

    /**
     *
     * @return String
     */
    public String getUsername(){
        if(sessionStatus!=null){
            return sessionStatus.getUsername();
        }
        return null;
    }

    
    public Set<String> getGroups(){
        if(sessionStatus!=null){
            return sessionStatus.getGroups();
        }
        return new HashSet<String>();
    }

    public String getToken(){
        if(sessionStatus!=null){
            return sessionStatus.getSessionToken();
        }
        return "n/a";
    }
    
    public boolean isGuest() {
        return sessionStatus == null ? false : sessionStatus.isGuest();
    }
    
    public Set<String> getUserGroups() {
        return sessionStatus == null ? null : sessionStatus.getGroups();
    }
}
