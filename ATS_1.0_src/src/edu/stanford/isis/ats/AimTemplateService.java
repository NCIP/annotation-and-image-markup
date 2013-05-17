/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
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