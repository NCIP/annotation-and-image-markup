/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


package edu.stanford.isis.ats.utils;

import freemarker.template.Configuration;
import java.io.IOException;
import java.util.HashMap;
import org.restlet.Context;
import org.restlet.data.MediaType;

import org.restlet.ext.freemarker.ContextTemplateLoader;
import org.restlet.ext.freemarker.TemplateRepresentation;
import org.restlet.representation.Representation;

/**
 *
 * @author alansnyder
 */
public class FreemarkerUtil {

    private Configuration configuration;
    private boolean isInit;
    private ATSLogger log;

    private FreemarkerUtil() {
        isInit=false;
    }

    public static FreemarkerUtil getInstance() {
        return FreemarkerUtilHolder.INSTANCE;
    }

    private static class FreemarkerUtilHolder {
        private static final FreemarkerUtil INSTANCE = new FreemarkerUtil();
    }

    public void initConfiguration(Context context){
        log = ATSLogger.getLogger();
        // initialize the Freemarker's configuration
        configuration = new Configuration();
        configuration.setTemplateLoader(new ContextTemplateLoader(context,
                "clap://thread/edu/stanford/isis/ats/ui/templates"));

        isInit=true;
    }

    public Representation toRepresentation(String templateName, Object dataModel, MediaType mediaType){
        if(!isInit){
            throw new IllegalStateException("FreemarkerUtil was not initialized!! Need to call FreemarkerUtil.getInstance.initConfiruration during start-up of Application.");
        }

        log.debug("Showing template="+templateName);

        if(dataModel==null){
            //Create an empty model.
            dataModel = new HashMap<String, Object>();
            log.debug("No data for template.");
        }

        return new TemplateRepresentation(templateName, configuration, dataModel, mediaType);
    }

    /**
     * Get the string format for this template.
     * @param templateName
     * @param dataModel
     * @return
     * @throws IOException
     */
    public String toHtmlString(String templateName, Object dataModel)
        throws IOException
    {
        Representation rep = toRepresentation(templateName,dataModel, MediaType.TEXT_HTML);
        return rep.getText();
    }

 }
