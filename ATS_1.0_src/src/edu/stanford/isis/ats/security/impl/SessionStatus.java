/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
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
