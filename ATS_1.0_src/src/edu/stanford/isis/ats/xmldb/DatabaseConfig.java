/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


package edu.stanford.isis.ats.xmldb;

import edu.stanford.isis.ats.ConfigParser;
import edu.stanford.isis.ats.utils.ATSLogger;
import java.util.Map;

/**
 *
 * @author alansnyder
 */
public class DatabaseConfig {

    protected Map<String, String> dbVars;

    private static final ATSLogger log = ATSLogger.getLogger();

    private DatabaseConfig() {

      dbVars = ConfigParser.readConfigVars(new String[] { "dbpath" });
      for (String key : dbVars.keySet()) {
         if (dbVars.get(key) == null) {
             log.error("Error: Could not read variable " + key + " in serverConfig.txt, shutting down.", null);
            System.exit(1);
         }
      }

    }

    public static DatabaseConfig getInstance() {
        return DatabaseConfigHolder.INSTANCE;
    }

    public Map<String, String> getDbVars(){
        return dbVars;
    }

    private static class DatabaseConfigHolder {
        private static final DatabaseConfig INSTANCE = new DatabaseConfig();
    }
 }
