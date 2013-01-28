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
