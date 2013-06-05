/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


package edu.stanford.isis.ats;

import edu.stanford.isis.ats.utils.ATSLogger;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

/**
 *
 * @author alansnyder
 */
public class ConfigParser {

    private static ATSLogger log = ATSLogger.getLogger();

   public static Map<String, String> readConfigVars(String[] varNames) {
      String[] vars = new String[varNames.length];
      try {
         File configFile = new File("serverConfig.txt");
         BufferedReader reader = new BufferedReader(new FileReader(configFile));

         String line = reader.readLine();
         while (line != null) {
            int equalsInd = line.indexOf("=");
            if (equalsInd > -1) {
               String varName = line.substring(0, equalsInd).trim();
               for (int i = 0; i < varNames.length; i++) {
                  if (varName.equals(varNames[i])) {
                     vars[i] = line.substring(equalsInd + 1).trim();
                  }
               }
            }
            line = reader.readLine();
         }
         reader.close();
      } catch (FileNotFoundException e) {
         log.error("FileNotFound",e);
      } catch (IOException e) {
         log.error("IOException", e);
      }

      Map<String, String> varmap = new HashMap<String, String>();
      for (int i = 0; i < varNames.length; i++) {
         varmap.put(varNames[i], vars[i]);
      }
      return varmap;
   }

}
