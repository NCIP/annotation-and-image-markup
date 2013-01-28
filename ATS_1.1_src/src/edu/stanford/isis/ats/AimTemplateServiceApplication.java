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