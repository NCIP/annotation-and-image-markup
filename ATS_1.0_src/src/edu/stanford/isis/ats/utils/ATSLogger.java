/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
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
