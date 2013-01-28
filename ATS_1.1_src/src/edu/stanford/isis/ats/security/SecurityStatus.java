/*
 * Copyright (c) 2008-2013, Northwestern University
 * All rights reserved.
 *  
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *  
 *   Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 *  
 *   Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *  
 *   Neither the name of the Northwestern University nor the names of its contributors
 *   may be used to endorse or promote products derived from this software
 *   without specific prior written permission.
 *  
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
