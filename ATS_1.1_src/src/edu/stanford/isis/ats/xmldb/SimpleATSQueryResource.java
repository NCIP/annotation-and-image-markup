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

package edu.stanford.isis.ats.xmldb;

import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.text.DateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

import org.restlet.Request;
import org.restlet.data.Form;
import org.restlet.data.MediaType;
import org.restlet.data.Status;
import org.restlet.representation.Representation;
import org.restlet.representation.StringRepresentation;
import org.restlet.resource.Post;

import com.sleepycat.db.DatabaseException;
import com.sleepycat.dbxml.XmlContainer;
import com.sleepycat.dbxml.XmlDocument;
import com.sleepycat.dbxml.XmlException;
import com.sleepycat.dbxml.XmlManager;
import com.sleepycat.dbxml.XmlManagerConfig;
import com.sleepycat.dbxml.XmlResults;

import edu.stanford.isis.ats.security.ATSLoginRequiredException;
import edu.stanford.isis.ats.ui.FreemarkerTemplateResource;
import edu.stanford.isis.ats.utils.FreemarkerUtil;


/**
 *
 * @author alansnyder
 * @author Vladimir Kleper
 */
public class SimpleATSQueryResource extends XMLDatabaseResource {


    @ATSQueryAPI(template="debug.ftl")
    public String debugAllContainers(Form queryForm, String template) 
            throws ATSLoginRequiredException, IOException
    {
        String collection = getCollection(queryForm);
        String namespace = getNamespace(queryForm);

        log.debug("debugXmlDbContents collection="+collection+" namespace="+namespace);

        String queryString = "for $x in collection(\""+collection+"\")/TemplateContainer \n"+
                             "return $x";

        List<String> results = processQuery(collection,namespace,queryString);

        Map<String,Object> dataModel = new HashMap<String,Object>();
        StringBuilder sb = new StringBuilder();
        boolean first = true;
        for(String curr : results){
            if( !first ){
                sb.append("\n<!-- new -->\n");
            }
            sb.append(curr);
            first=false;
        }
        dataModel.put("debugString", sb.toString());
        return FreemarkerUtil.getInstance().toHtmlString(template, dataModel);
    }


    /**
     * Generates only the table
     * @param queryForm
     * @param template
     * @param request
     * @return
     * @throws ATSLoginRequiredException
     */
    public String getAdminPermissionTable(Form queryForm, Request request)
        throws ATSLoginRequiredException
    {
        try {
            String collection = getCollection(queryForm);
            String namespace = getNamespace(queryForm);
            String owner = MetaDataUtil.getOwnerFromRequest(request);
            //log.debug("  owner="+owner);
            List<String> results = getMetaDataFromCollection(collection, owner, namespace);
            //log.debug("SQR getMetaDataFromCollection had: "+results.size()+" results");
            return generateAdminPermissionTable(results);
        } catch (Exception e) {
            log.error("Error while getting meta-data.", e);
            return "";
        }
    }


    /**
     * 
     * @param collection
     * @param owner
     * @return
     * @throws XmlException
     */
    private List<String> getMetaDataFromCollection(String collection, String owner, String namespace)
    {
        List<String> retVal = new ArrayList<String>();
        
        XmlManager manager = null;
        XmlContainer container = null;
        XmlResults xmlResults = null;
        try{
            
            manager = new XmlManager(env, XmlManagerConfig.DEFAULT);
            container = MetaDataUtil.getXmlContainerForCollection(collection, manager);

            xmlResults = MetaDataUtil.queryForAdmin(manager,collection,namespace);
            
            int debugIndex=1;
            while(xmlResults.hasNext()){
                //log.debug("document #: "+debugIndex);
                XmlDocument xmlDocument = xmlResults.next().asDocument();
                if(xmlDocument!=null){
                    //check if row is owner.

                    String row = createAdminTableRowForOwner(xmlDocument,owner);
                    if( !row.isEmpty() ){
                        retVal.add(row);
                    }
                    debugIndex++;
                }else{
                    log.debug("null xmlDocument");
                }
            }//while

            log.debug("getMetaDataFromCollection found: "+debugIndex+" docs.");

            return retVal;

        } catch(XmlException xe) {
            log.error("XmlException ", xe);
            return retVal;
        } finally {
            //close all the resources that open connections here.
            MetaDataUtil.deleteXmlResults(xmlResults);
            MetaDataUtil.closeXmlContainer(container);
            MetaDataUtil.closeXmlManager(manager);
        }
    }

 

    private String createAdminTableRowForOwner(XmlDocument xmlDocument, String owner){
        String docOwner = MetaDataUtil.getMetaData(MetaDataUtil.OWNER,xmlDocument);
        if(docOwner!=null && docOwner.equalsIgnoreCase(owner)){
            return createAdminTableRow(xmlDocument);
        }
        //an empty String to indicate this isn't owned.
        return "";
    }

    /**
     *
     * @param xmlDocument
     * @return a valid row or empty string.
     * @throws XmlException
     */
    private String createAdminTableRow(XmlDocument xmlDocument){
        StringBuilder sb = new StringBuilder();
        sb.append("<tr>");
        //sb.append("<td>").append(MetaDataUtil.getDocName(xmlDocument)).append("</td>");
        sb.append("<td>").append(MetaDataUtil.getMetaData(MetaDataUtil.DOC_FILE_NAME,xmlDocument)).append("</td>");
        sb.append("<td>").append(MetaDataUtil.getMetaData(MetaDataUtil.OWNER,xmlDocument)).append("</td>");
        //sb.append("<td>").append(MetaDataUtil.getMetaData(MetaDataUtil.DATE_PUBLISHED,xmlDocument)).append("</td>");
        String dateStr = "-";
        try {
            long millis = Long.parseLong(MetaDataUtil.getMetaData(MetaDataUtil.DATE_PUBLISHED,xmlDocument));
            dateStr = DateFormat.getInstance().format(new Date(millis));
        } catch (NumberFormatException e) {
        }
        sb.append("<td>").append(dateStr).append("</td>");
        sb.append("<td>").append(MetaDataUtil.getMetaData(MetaDataUtil.PERMISSION,xmlDocument)).append("</td>");
        sb.append("<td>").append(MetaDataUtil.getMetaData(MetaDataUtil.ALLOWED_USER,xmlDocument)).append("</td>");
        String uid = MetaDataUtil.getUidAttribFromDoc(xmlDocument);
        sb.append("<td><a href='/templates/admin?uid=").append(uid).append("' >Change</a>").append("</td>");
        sb.append("<td><a href='/templates/download?uid=").append(uid).append("' target='_blank' >").append("View").append("</a></td>");
        sb.append("</tr>");
        return sb.toString();
    }


    @ATSQueryAPI(template="adv-template-search.ftl")
    public String getAdvancedTemplate(Form queryForm, String template, String userName)
        throws ATSLoginRequiredException
    {
        String collection = getCollection(queryForm);
        String namespace = getNamespace(queryForm);

        String queryString = generateAdvTemplateXQuery(queryForm, userName);

        List<String> results = processQuery(collection,namespace,queryString);

        boolean useXml = isRequestByAtb();
        if(!useXml){
            return generateHtmlResult(results,template,true);
        }else{
            return generateXmlResult(results);
        }
    }

    private String generateAdvTemplateXQuery(Form queryForm, String userName){
        logValues(queryForm);

        boolean xmlResponse = isRequestByAtb();

        ATSQueryBuilder xQuery = new ATSQueryBuilder.Builder(false).formData(queryForm).userName(userName).setXmlReturnType(xmlResponse).build();
        String queryString = xQuery.getXQuery();
        log.info(queryString);

        return queryString;
    }


    @ATSQueryAPI(template="adv-container-search.ftl")
    public String getAdvancedContainer(Form queryForm, String template, String userName)
        throws ATSLoginRequiredException
    {
        String collection = getCollection(queryForm);
        String namespace = getNamespace(queryForm);

        String queryString = generateAdvContainerXQuery(queryForm, userName);

        List<String> results = processQuery(collection,namespace,queryString);

        try{
            if (results != null)
                results = modifyPrivateContainers(results,queryForm,collection);
        }catch(Exception e){
            log.error("Modify Private Containers had: ", e);
        }

       boolean useXml = isRequestByAtb();
        if(!useXml){
            return generateHtmlResult(results,template,false);
        }else{
            return generateXmlResult(results);
        }
    }


    private String generateAdvContainerXQuery(Form queryForm, String userName){
        logValues(queryForm);

        boolean xmlResponse = isRequestByAtb();

        ATSQueryBuilder xQuery = new ATSQueryBuilder.Builder(true).formData(queryForm).userName(userName).setXmlReturnType(xmlResponse).build();
        String queryString = xQuery.getXQuery();
        log.debug(queryString);

        return queryString;
    }


    private Set<String> getUsedSearchParameters(Form queryForm){
        Set<String> retVal = new HashSet<String>();
        Set<String> names = queryForm.getNames();
        for(String curr : names){
            if("function".equalsIgnoreCase(curr)){
                continue;
            }
            String val = queryForm.getFirstValue(curr);
            if(val!=null){
                retVal.add(curr);
            }
        }
        return retVal;
    }

    /**
     * Write all the values in the form to a logger.
     * @param queryForm
     */
    private void logValues(Form queryForm){
        Set<String> names = getUsedSearchParameters(queryForm);
        for(String curr : names){
            String val = queryForm.getFirstValue(curr);
            log.debug(curr+"="+val);
        }
    }

    private String generateAdminPermissionTable(List<String> results) throws ATSLoginRequiredException {
        if (results == null) {
            return genErrorXML(getStatus().getDescription());
        } else {
            log.debug("sqr.generateAdminPermissionTable - list #result=" + results.size());
            StringBuilder sb = new StringBuilder();
            sb.append("<tr>");
            sb.append("<th>Name</th>");
            sb.append("<th>Owner</th>");
            sb.append("<th>Publish Date</th>");
            sb.append("<th>Permissions</th>");
            sb.append("<th>Allowed Users</th>");
            sb.append("<th>Change</th>");
            sb.append("<th>View</th>");
            sb.append("</tr>");
            results.add(0, sb.toString());

            return FreemarkerTemplateResource.generateTable(results);
        }
    }

    /**
     * Generates an XML result.
     * 
     * ToDo: move to XMLDatabaseResource
     * @param results
     * @return
     */
    private String generateHtmlResult(List<String> results, String templateName, boolean includeModality) throws ATSLoginRequiredException
    {
        if(results == null){
            return genErrorXML(getStatus().getDescription());
        }else{
            StringBuilder sb = new StringBuilder();
            sb.append("<tr>");
            sb.append("<th>Template Name</th>");
            sb.append("<th>Authors</th>");
            sb.append("<th>Template Description</th>");
            sb.append("<th>Disease</th>");
            sb.append("<th>Body Part</th>");
            if(includeModality){
                sb.append("<th>Modality</th>");
            }
            sb.append("<th>Download Template</th>");
            sb.append("</tr>");
            results.add(0,sb.toString());

            return FreemarkerTemplateResource.generateTemplateSearchResultsPage(results, templateName, this.getRequest());
        }
    }

    /**
     * 
     * @param result
     * @return
     */
    private String generateXmlResult(List<String> result){
        StringBuilder sb = new StringBuilder();
        sb.append("<?xml version='1.0' encoding='UTF-8' ?>");
        sb.append("<results>");
        for(String curr : result){
            sb.append(curr);
        }
        sb.append("</results>");

        return sb.toString();
    }

   /**
    * Processes POST requests for annotations based on a predefined set of
    * functions.
    * @param entity
    * @return
    */
   @Post
   public Representation receiveRepresentation(Representation entity) {
      MediaType returnType = MediaType.TEXT_HTML;

      Form queryForm = new Form(entity);
      String function = queryForm.getFirstValue("function");
      log.debug("function=_"+function+"_");

      if(function == null) {
         String err = "No function requested.";
         setStatus(Status.CLIENT_ERROR_BAD_REQUEST, err);
         return new StringRepresentation(genErrorXML(err), returnType);
      }
      else {
         Method m = getATSQueryAPIMethod(function);
         String templateName = getTemplateNameFromAnnotation(m);

         if(m != null) {
            try {
               final String userName = MetaDataUtil.getOwnerFromRequest(this.getRequest());
               String result = (String)m.invoke(this, queryForm, templateName, userName);
               return new StringRepresentation(result, returnType);

            } catch (Exception e) { 
                //IDE doesn't realize invoke throws this exception.
                if(e instanceof ATSLoginRequiredException || ( e instanceof InvocationTargetException && e.getCause() instanceof ATSLoginRequiredException)){
                    return FreemarkerTemplateResource.displayLoginPage();
                }

               log.error("SAQR-382 receiveRepresentation. function="+function+" had: ", e);
               String err = "SAQR-382 - Error invoking function: " + e.getMessage();
               setStatus(Status.SERVER_ERROR_INTERNAL, err);
               returnType = MediaType.TEXT_XML;
               return new StringRepresentation(genErrorXML(err), returnType);
            }
         }
         else {
            String err = "Unknown function requested.";
            setStatus(Status.CLIENT_ERROR_BAD_REQUEST, err);
            return new StringRepresentation(genErrorXML(err), returnType);
         }
      }
   }

   /**
    * Find and return the Method of this instance that matches the AIM
    * query API function
    * @param function
    * @return Matching AIM query API function, or null if it does not exist
    */
   private Method getATSQueryAPIMethod(String function) {
      Method[] classMethods = this.getClass().getDeclaredMethods();
      for(Method m : classMethods) {
         if(m.getName().equals(function) && m.isAnnotationPresent(ATSQueryAPI.class))
            return m;
      }
      throw new IllegalArgumentException("No ATSQuery annotation found for function=_"+function+"_");
   }

   /**
    * Find the template associated with this annotation.
    * @param method
    * @return String
    */
   private String getTemplateNameFromAnnotation(Method method){

       ATSQueryAPI api = method.getAnnotation(ATSQueryAPI.class);
       return api.template();  
   }

    /**
     * Modify the Containers that are private, so they cannot be downloaded.
     * @param results
     */
    private List<String> modifyPrivateContainers(List<String> results,Form queryForm, String collection){
        try {

            initXmlDbEnvironment();

            List<String> retVal = new ArrayList<String>();
            //Go through all the documents, to create the set of private UIDs.
            Set<String> privateUIDs = createSetOfPrivateUids(queryForm,collection);
            log.debug(" collection: "+collection+" has "+privateUIDs.size()+" private template groups");
            //check each result.
            for (String currTableRow : results) {
                String currUid = parseUidFromTableRow(currTableRow);
                log.debug("currUid="+currUid);
                if (privateUIDs.contains(currUid)) {
                    currTableRow = modifyTableRow(currTableRow);
                }
                retVal.add(currTableRow);
            }
            return retVal;
        } catch (XmlException ex) {
            log.error("Failed to modify Containers with setting PRIVATE", ex);
            return results;
        } catch (DatabaseException dbe) {
            log.error("Failed to modify Containers with setting PRIVATE", dbe);
            return results;
        } finally {
            try {
                cleanup();
            } catch (DatabaseException ex) {
                log.error("modifyPrivateContainers failed to cleanup.", ex);
            }
        }

    }

    private Set<String> createSetOfPrivateUids(Form queryForm,String collection) throws XmlException, DatabaseException{

        Set<String> retVal = new HashSet<String>();
        XmlResults xmlResults = null;
        XmlContainer container = null;
        XmlManager manager = null;
        try{
            //Get list of all documents.
            manager = new XmlManager(env, XmlManagerConfig.DEFAULT);
            container = manager.openContainer(collection);
            xmlResults = getResultSetForCollecton(queryForm,manager);
    
            //go through that list.
            while(xmlResults.hasNext()){
                XmlDocument xmlDocument = xmlResults.next().asDocument();
                if(xmlDocument!=null){
                    //read meta-data to mark some private.
                    String permission = MetaDataUtil.getMetaData(MetaDataUtil.PERMISSION, xmlDocument);
                    
                    if(permission.equalsIgnoreCase(MetaDataUtil.PERM_PRIVATE)){
                        retVal.add(MetaDataUtil.getUidAttribFromDoc(xmlDocument));
                    }
                }
            }
        }finally{
            MetaDataUtil.deleteXmlResults(xmlResults);
            MetaDataUtil.closeXmlContainer(container);
            MetaDataUtil.closeXmlManager(manager);
        }
        return retVal;
    }

    private static String parseUidFromTableRow(String currTableRow){
        int start = currTableRow.indexOf("download?uid=");

        int qm = currTableRow.indexOf("=",start);
        String part = currTableRow.substring(qm+1).replace("\"", " ");
        part = part.replace("'", " ").trim();
        int end = part.indexOf(" ");
        
        String retVal;
        if(end<0){
            retVal = part;
        }else{
            retVal = part.substring(0, end);
        }

        //log.debug(" parsed uid: _"+retVal+"_");

        return retVal;
    }



    /* <td><a href='/templates/download?uid={string($uid)}'>download</a></td></tr> */


    /**
     * Turn this ...
     * <td><a href='/templates/download?uid={string($uid)}'>download</a></td></tr>
     *
     * into ...
     * <td><div uid=>Private</div></td></tr>
     *
     * @param currTableRow
     * @return
     */
    private static String modifyTableRow(String currTableRow){

        currTableRow = currTableRow.replaceFirst("<td><a href='/templates/download?", "<td><div ");
        currTableRow = currTableRow.replaceFirst("<td><a href=\"/templates/download?", "<td><div ");
        currTableRow = currTableRow.replaceFirst(">download</a>", ">PRIVATE</div>");

        log.debug("Modified table: "+currTableRow);

        return currTableRow;
    }


    private static XmlResults getResultSetForCollecton(Form queryForm,XmlManager manager)
            throws XmlException
    {
        String collection = getCollection(queryForm);
        String namespace = getNamespace(queryForm);

        return MetaDataUtil.queryForAdmin(manager,collection,namespace);
    }

}
