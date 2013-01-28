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

package edu.stanford.isis.ats.security.impl;

import java.util.HashSet;
import java.util.List;
import java.util.Random;
import java.util.Set;

/**
 *
 * @author alansnyder
 * @author Vladimir Kleper
 */
public class SessionStatus {

    public static String GUEST = "guest";

    private String loginName;
    private long sessionEndTime;
    private String sessionToken;
    private String samlToken; // SAML token that is returned by STS or GRID

    private Set<String> groups;

    public SessionStatus(String userName, String samlToken){
        loginName = userName;
        this.samlToken = samlToken;
        sessionEndTime = System.currentTimeMillis()+(24*60*60*1000); // TODO VK: get expiration time from SAML token
        Random rand = new Random(sessionEndTime);

        sessionToken = ""+sessionEndTime+"A"+rand.nextInt();

        groups = new HashSet<String>();
    }

    /**
     * Get the value in the cookie.
     * @return
     */
    public String getSessionToken(){
        return sessionToken;
    }

    public String getUsername(){
        return loginName;
    }
    
    public String getSamlToken() {
    	return samlToken;
    }

    public boolean hasExpired(){
        long currTime = System.currentTimeMillis();

        return (currTime>sessionEndTime);
    }

    /**
     * Set the groups associated with this account.
     * @param groups
     */
    public void setGroups(List<String> groups){
        this.groups = new HashSet<String>(groups);
        if(isGuest()){
            setAsGuest();
        }
    }

    /**
     * 
     * @return
     */
    public Set<String> getGroups(){
        return groups;
    }

    /**
     * Set the status to guest, which cannot below to any groups.
     * @return
     */
    public void setAsGuest(){
        groups.clear();
        groups.add(GUEST);
    }

    /**
     * Set to true if a guest.
     * @return boolean true if a guest.
     */
    public boolean isGuest(){
        return (groups.contains(GUEST));
    }

}
