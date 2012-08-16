/*
 * Copyright Notice. Copyright 2011 - 2012 Northwestern University and Stanford
 * University ("caBIG® Participant"). AIM Template Enterprise Service conforms
 * to caBIG® technical specifications and is part of the caBIG® initiative. The
 * software subject to this notice and license includes human readable source
 * code form, machine readable, binary, object code form and related
 * documentation (the "caBIG® Software").
 *
 * This caBIG® Software License (the "License") is between the National Cancer
 * Institute (NCI) and You. "You (or "Your") shall mean a person or an entity,
 * and all other entities that control, are controlled by, or are under common
 * control with the entity. "Control" for purposes of this definition means (i)
 * the direct or indirect power to cause the direction or management of such
 * entity, whether by contract or otherwise, or (ii) ownership of fifty percent
 * (50%) or more of the outstanding shares, or (iii) beneficial ownership of
 * such entity.
 *
 * Provided that You agree to the conditions described below, NCI grants You a
 * non-exclusive, worldwide, perpetual, fully-paid-up, no-charge, irrevocable,
 * transferable and royalty-free right and license in its rights in the caBIG®
 * Software, including any copyright or patent rights therein, to (i) use,
 * install, disclose, access, operate, execute, reproduce, copy, modify,
 * translate, market, publicly display, publicly perform, and prepare
 * derivative works of the caBIG® Software in any manner and for any purpose,
 * and to have or permit others to do so; (ii) make, have made, use, practice,
 * sell, and offer for sale, import, and/or otherwise dispose of caBIG®
 * Software (or portions thereof); (iii) distribute and have distributed to and
 * by third parties the caBIG® Software and any modifications and derivative
 * works thereof; and (iv) sublicense the foregoing rights set out in (i), (ii)
 * and (iii) to third parties, including the right to license such rights to
 * further third parties. For sake of clarity, and not by way of limitation,
 * NCI shall have no right of accounting or right of payment from You or Your
 * sublicensees for the rights granted under this License. This License is
 * granted at no charge to You. Your downloading, copying, modifying,
 * displaying, distributing or use of caBIG® Software constitutes acceptance of
 * all of the terms and conditions of this Agreement. If you do not agree to
 * such terms and conditions, you have no right to download, copy, modify,
 * display, distribute or use the caBIG® Software.
 *
 * 1. Your redistributions of the source code for the caBIG® Software must retain
 * the above copyright notice, this list of conditions and the disclaimer and
 * limitation of liability of Article 6 below. Your redistributions in object
 * code form must reproduce the above copyright notice, this list of conditions
 * and the disclaimer of Article 6 in the documentation and/or other materials
 * provided with the distribution, if any.
 *
 * 2. Your end-user documentation included with the redistribution, if any, must
 * include the following acknowledgment: "This product includes software
 * developed by Alan Snyder, Vitaliy Semeshko, Vladimir Kleper
 * and Pattanasak Mongkolwat, Northwestern University and Stanford University."
 * If You do not include such end-user documentation, You shall include this
 * acknowledgment in the caBIG® Software itself, wherever such third-party
 * acknowledgments normally appear.
 *
 * 3. You may not use the names "Northwestern University", "Stanford University",
 * "The National Cancer Institute", "NCI", "Cancer Bioinformatics Grid" or
 * "caBIG®" to endorse or promote products derived from this caBIG® Software.
 * This License does not authorize You to use any trademarks, service marks,
 * trade names, logos or product names of either caBIG® Participant, NCI or
 * caBIG®, except as required to comply with the terms of this License.
 *
 * 4. For sake of clarity, and not by way of limitation, You are not prohibited by
 * this License from incorporating this caBIG® Software into Your proprietary
 * programs and into any third party proprietary programs. However, if You
 * incorporate the caBIG® Software into third party proprietary programs, You
 * agree that You are solely responsible for obtaining any permission from such
 * third parties required to incorporate the caBIG® Software into such third
 * party proprietary programs and for informing Your sublicensees, including
 * without limitation Your end-users, of their obligation to secure any
 * required permissions from such third parties before incorporating the caBIG®
 * Software into such third party proprietary software programs. In the event
 * that You fail to obtain such permissions, You agree to indemnify NCI for any
 * claims against NCI by such third parties, except to the extent prohibited by
 * law, resulting from Your failure to obtain such permissions.
 * 
 * 5. For sake of clarity, and not by way of limitation, You may add Your own
 * copyright statement to Your modifications and to the derivative works, and
 * You may provide additional or different license terms and conditions in
 * Your sublicenses of modifications of the caBIG® Software, or any derivative
 * works of the caBIG® Software as a whole, provided Your use, reproduction,
 * and distribution of the Work otherwise complies with the conditions stated
 * in this License.
 *
 * 6. THIS caBIG® SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES (INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE) ARE
 * DISCLAIMED. IN NO EVENT SHALL NCI OR THE NORTHWESTERN UNIVERSITY OR ITS
 * AFFILIATES BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS caBIG® SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
package edu.stanford.isis.ats.ui;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.HashMap;
import java.util.List;
import java.util.Locale;
import java.util.Map;

import org.restlet.data.Disposition;
import org.restlet.data.Form;
import org.restlet.data.MediaType;
import org.restlet.representation.Representation;
import org.restlet.representation.StringRepresentation;
import org.restlet.resource.Get;

import com.sleepycat.dbxml.XmlException;
import com.sleepycat.dbxml.XmlValue;

import edu.stanford.isis.ats.resources.Constants;
import edu.stanford.isis.ats.resources.Uid;
import edu.stanford.isis.ats.utils.FreemarkerUtil;
import edu.stanford.isis.ats.xmldb.DbUtils;
import edu.stanford.isis.ats.xmldb.XMLDatabaseResource;
import edu.stanford.isis.ats.xmldb.data.QueryResultAdapter;
import edu.stanford.isis.ats.xmldb.data.TemplateComponentQueryResult;

/**
 * The resource to download search results as XML.
 * @author alansnyder
 * @author Vladimir Kleper
 */
public class DownloadResource extends XMLDatabaseResource {

    private static final String PARAM_NAME_UID = "uid"; // template UID
    private static final String PARAM_NAME_MODE = "mode"; // download mode: View, Save As, etc.
    
    private static final String MODE_SAVE_AS = "save"; // will trigger attachment Save As dialog in a browser
    private static final String MODE_VIEW = "view"; // in-line viewing mode (default)

    private static final String TEMPLATE_XQUERY = "for $x in collection(\"%s\")/TemplateContainer/Template[@uid=\"%s\"] \n return $x";
    private static final String GROUP_XQUERY = "for $x in collection(\"%s\")/TemplateContainer[@uid=\"%s\"] \n return $x";

    private static final HashMap<String, String> templateContainerProtos;
    static {
        templateContainerProtos = new HashMap<String, String>();
        templateContainerProtos.put(Constants.TEMPLATE_SCHEMA_NAME_V1RV23, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<TemplateContainer creationDate=\"%s\" authors=\"ATS 1.0\" name=\"ATS Template\" version=\"1\" uid=\"%s\" description=\"Template container generated by ATS 1.0\" xsi:schemaLocation=\"gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIMTemplate AIMTemplate_v1rv23.xsd\" xmlns=\"gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIMTemplate\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">\n%s\n</TemplateContainer>");
    }
    
    private String downloadFileName = null;
    private String templateSchemaName = null;
    
    @Get
    public Representation downloadXmlResult(Representation entity) {

        Form queryForm = new Form(entity);

        final String uid = getParamValue(PARAM_NAME_UID, null);

        log.info("downloading item with UID=" + uid);

        this.downloadFileName = uid == null ? "template" : "template_" + uid + ".xml";
        String result = findResultForUid(uid, queryForm);

        if (result != null && result.length() > 0) {
            boolean isSaveAsMode = getParamValue(PARAM_NAME_MODE, MODE_VIEW).equalsIgnoreCase(MODE_SAVE_AS);
            
            // Generate container for single template for browser download
            if (isSaveAsMode && (!result.startsWith("<?xml version") && !result.startsWith("<TemplateContainer"))) {
                result = this.generateTemplateContainer(result);
            }
            final StringRepresentation download = new StringRepresentation(result);
            download.setMediaType(MediaType.TEXT_XML);
            if (isSaveAsMode) {
                final Disposition disposition = new Disposition(Disposition.TYPE_ATTACHMENT);
                disposition.setFilename(this.downloadFileName == null ? "template.xml" : this.downloadFileName);
                download.setDisposition(disposition);
            }
            return download;
        } else {
            // give an error message that UID=... was not found.
            Map<String, Object> pageData = new HashMap<String, Object>();
            String errorMessage = "Could not find result for UID=" + uid;
            pageData.put("errorMessage", errorMessage);
            return FreemarkerUtil.getInstance().toRepresentation("error-page.ftl", pageData, MediaType.TEXT_HTML);
        }
    }

    /**
     * Get submitted parameter value
     * 
     * @param paramName - name of the parameter
     * @param defaultValue - the value to return if the given parameter is not found
     * @return String  - query string value of the given parameter (case-insensitive) or defaultValue
     */
    private String getParamValue(String paramName, String defaultValue){
        final Form queryForm = this.getReference().getQueryAsForm();
        return queryForm.getFirstValue(paramName, true, defaultValue);
    }

    /**
     * Find the Result for the UID and return as XML, or null if not found.
     * @param uid
     * @return String result as XML String or null if not found.
     */
    private String findResultForUid(String uid,Form queryForm){

        if(uid==null){
            return null;
        }

        try{
            String collection = getCollection(queryForm);
            String namespace = getNamespace(queryForm);

            log.debug("debugXQuery collection="+collection+" namespace="+namespace);
            
            // List<String> results = getResults(TEMPLATE_XQUERY,uid,collection,namespace);
            final String templateQuery = String.format(TEMPLATE_XQUERY, collection, uid);
            List<String> results = processQuery(collection, namespace, templateQuery, new QueryResultAdapter<String>() {
                @Override
                public String adaptResult(XmlValue value) {
                    if (value == null)
                        return null;
                    
                    try {
                        // Figure out template schema version
                        final String schemaLocation = DbUtils.getAttributeValue(value.getParentNode(), "schemaLocation");
                        if (schemaLocation != null) {
                            if (schemaLocation.endsWith(Constants.TEMPLATE_SCHEMA_NAME_V1RV23))
                                templateSchemaName = Constants.TEMPLATE_SCHEMA_NAME_V1RV23;
                        }
                        log.debug("Identified schema name is " + templateSchemaName);
                    
                        return value.asString();
                    } catch (XmlException ex) {
                        log.error("(DR-250): Failed to convert query result to string. The value will be ignored.", ex);
                    }
                    return null;
                }
            });
            
            if(results.isEmpty()){
                log.debug("Checking Template Groups for uid: "+uid);
//                results = getResults(GROUP_XQUERY,uid,collection,namespace);
                // VK: find out template file name
                final String templateComponentQuery = String.format(GROUP_XQUERY, collection, uid);
                List<TemplateComponentQueryResult> queryResults = processQuery(collection, namespace, templateComponentQuery, TemplateComponentQueryResult.templateComponentQueryResultAdapter);
                if (!queryResults.isEmpty()) {
                    if (queryResults.get(0).getFileName() != null)
                        this.downloadFileName = queryResults.get(0).getFileName();
                    for(TemplateComponentQueryResult queryResult : queryResults)
                        results.add(queryResult.getTemplateComponent());
                }
               
                
                log.info("Group found: "+results.size()+" results for uid="+uid);
            }

            return toXmlTemplateDownload(results);
//        }catch(UnsupportedEncodingException uee){
//            log.error("DR-88, Encoding failure. ", uee);
//        }
        } catch (Exception ex) {
            log.error("DR-288, Error:", ex);
        }
        return null;
    }

    private String generateTemplateContainer(String innerTemplate) {
        final String currentTemplateSchemaName = templateContainerProtos.containsKey(this.templateSchemaName) ? this.templateSchemaName : Constants.TEMPLATE_SCHEMA_NAME_V1RV23;
        final String containerProto = templateContainerProtos.get(currentTemplateSchemaName);
        final DateFormat df = new SimpleDateFormat("yyyy-MM-dd", Locale.US);
        final String uid = Uid.generate();
        
        return String.format(containerProto, df.format(new Date()), uid, innerTemplate);
    }
}
