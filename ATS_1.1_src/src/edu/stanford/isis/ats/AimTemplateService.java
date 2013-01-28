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
import org.restlet.Component;
import org.restlet.Server;
import org.restlet.data.Parameter;
import org.restlet.data.Protocol;
import org.restlet.routing.Redirector;
import org.restlet.util.Series;

import java.util.Map;

/**
 * The AimTemplateServer class implements an XML database server for aim templates.
 * @author amsnyder
 * @author Vladimir Kleper
 */
public class AimTemplateService {

   /**
    * This is the entry point of the server application.
    * @param args
    */
   public static void main(String[] args) {
      ATSLogger log = ATSLogger.getLogger();

      Map<String, String> serverVars = ConfigParser.readConfigVars(new String[] { "port", "keystorepath", "keystorename" });

      //Default port number
      int portNum = 8080;
      if(serverVars.get("port") != null)
         portNum = Integer.parseInt(serverVars.get("port"));
      
      try {
         Component component = new Component();
         if (serverVars.get("keystorepath") != null && serverVars.get("keystorename") != null) {
            log.info("Keystore detected, using SSL");
            // Set up SSL
            Server xqueryServer = component.getServers().add(Protocol.HTTPS, portNum);
            Series<Parameter> serverParams = xqueryServer.getContext().getParameters();
            serverParams.add("keystorePath", serverVars.get("keystorepath") + "/" + serverVars.get("keystorename"));
            serverParams.add("keystorePassword", "annotations");
            serverParams.add("keystoreType", "JKS");
         } else {
            log.info("No keystore detected, using unencrypted connection");
            component.getServers().add(Protocol.HTTP, portNum);
         }

         //server files from a static directory.
         component.getClients().add(Protocol.FILE);
         component.getServers().add(Protocol.CLAP);
         component.getClients().add(Protocol.CLAP);

         component.getDefaultHost().attach("/templates", new AimTemplateServiceApplication());
         component.getDefaultHost().attachDefault(new Redirector(component.getContext(), "/templates/web", Redirector.MODE_CLIENT_TEMPORARY));
         component.start();
      } catch (Exception e) {
         log.error(e.getMessage(),e);
      }
   }

}