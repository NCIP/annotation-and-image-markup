/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


package edu.stanford.isis.ats;

import edu.stanford.isis.ats.ui.DownloadResource;
import edu.stanford.isis.ats.ui.FreemarkerTemplateResource;
import edu.stanford.isis.ats.ui.LoginResource;
import edu.stanford.isis.ats.utils.ATSLogger;
import edu.stanford.isis.ats.utils.FreemarkerUtil;
import edu.stanford.isis.ats.ui.AdminResource;
import edu.stanford.isis.ats.xmldb.SimpleATSQueryResource;
import edu.stanford.isis.ats.xmldb.UploadResource;
import java.io.File;

import org.restlet.Application;
import org.restlet.Restlet;
import org.restlet.resource.Directory;
import org.restlet.routing.Redirector;
import org.restlet.routing.Router;

public class AimTemplateServiceApplication extends Application {

    public AimTemplateServiceApplication(){
        ATSLogger.getLogger().info("Version: Sept. 30, 2011 - 10:00");
    }

    @Override
    public synchronized Restlet createInboundRoot() {
        //initialize Freemarket templates
        FreemarkerUtil.getInstance().initConfiguration(getContext());

        Router router = new Router(getContext());
        router.attach("/upload", UploadResource.class);
        router.attach("/search", SimpleATSQueryResource.class);
        router.attach("/web", FreemarkerTemplateResource.class);
        router.attach("/login", LoginResource.class);
        router.attach("/download", DownloadResource.class);
        router.attach("/admin", AdminResource.class);

        Directory directory = createStaticFilesDirectory();
        router.attach("/static", directory);
        
        router.attachDefault(new Redirector(getContext(), "/web", Redirector.MODE_CLIENT_PERMANENT));

        return router;
    }

    private Directory createStaticFilesDirectory(){
        String curDir = System.getProperty("user.dir");

        File fl = new File(curDir,"static");
        String rootUri = fl.toURI().toString();
        //String rootUri = "file://"+curDir+"/static/";

        ATSLogger.getLogger().info("Static file rootURI="+rootUri);

        Directory directory = new Directory(getContext(),rootUri);
        directory.setListingAllowed(true);

        return directory;
    }
    
}