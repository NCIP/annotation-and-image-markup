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

package edu.stanford.isis.ats.utils;

/**
 *
 * @author alansnyder
 * @author Vladimir Kleper
 */
public class ATSLogger {
    
    // VK: Add log levels to shut this thing up
    public enum LogLevel {
        INFO,
        ERROR,
        DEBUG
    }
    
    private static LogLevel logLevel = LogLevel.INFO;

    static {
        // LogLevel initialization 
        // EX: -Dats.logLevel=ERROR
        final String logLevel = System.getProperty("ats.logLevel");
        if (logLevel != null) {
            try {
                ATSLogger.logLevel = LogLevel.valueOf(logLevel.trim().toUpperCase());
            } catch (IllegalArgumentException ex) {
            }
        }
    }
    
    private ATSLogger() {
    }

    public static ATSLogger getLogger() {
        return ATSLoggerHolder.INSTANCE;
    }

    private static class ATSLoggerHolder {
        private static final ATSLogger INSTANCE = new ATSLogger();
    }

    public void debug(String message){
        if (logLevel == LogLevel.DEBUG)
            System.out.println("Debug: "+message);
    }

    public void info(String message){
        if (logLevel == LogLevel.INFO || logLevel == LogLevel.DEBUG)
            System.out.println("Info: "+message);
    }

    public void error(String message, Throwable t){
        StringBuilder sb = new StringBuilder(message);
        if(t!=null){
            sb.append(", msg=").append(t.getMessage());
        }
        System.err.println("Error: "+sb.toString());

        if(t!=null){
            StackTraceElement[] st =  t.getStackTrace();
            for(StackTraceElement curr: st){
                System.err.println("    "+curr.toString());
            }
        }
    }
 }
