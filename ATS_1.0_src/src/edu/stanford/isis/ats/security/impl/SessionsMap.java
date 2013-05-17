/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


package edu.stanford.isis.ats.security.impl;

import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

/**
 * Keeps track of all the active sessions.
 * @author alansnyder
 */
public class SessionsMap {

    private Map<String,SessionStatus> sessions = new ConcurrentHashMap<String,SessionStatus>();

    private SessionsMap() {
    }

    public static SessionsMap getInstance() {
        return ActiveSessionsHolder.INSTANCE;
    }

    private static class ActiveSessionsHolder {
        private static final SessionsMap INSTANCE = new SessionsMap();
    }
 }
