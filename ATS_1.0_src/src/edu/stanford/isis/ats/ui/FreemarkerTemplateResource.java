/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


package edu.stanford.isis.ats.ui;

import edu.stanford.isis.ats.security.ATSLoginRequiredException;
import edu.stanford.isis.ats.utils.ATSLogger;
import edu.stanford.isis.ats.utils.ATSLoginUtil;
import edu.stanford.isis.ats.utils.FreemarkerUtil;
import edu.stanford.isis.ats.xmldb.SimpleATSQueryResource;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;
import org.restlet.Request;
import org.restlet.data.Form;
import org.restlet.data.MediaType;
import org.restlet.representation.Representation;
import org.restlet.resource.Get;
import org.restlet.resource.ServerResource;

/**
 *
 * @author alansnyder
 * @author Vladimir Kleper
 */
public class FreemarkerTemplateResource extends ServerResource {

    static ATSLogger log = ATSLogger.getLogger();

    public FreemarkerTemplateResource(){}

    @Get
    public Representation displayPage() throws ATSLoginRequiredException
    {

        //create data
        Map<String,Object> pageData = new HashMap<String, Object>();

        //we don't have a Results table here!
        pageData.put("resultsTableHtml", "");

        //
        String loginHtml = ATSLoginUtil.getInstance().checkForLoginCookie(this.getRequest());
        if(loginHtml==null){
            return displayLoginPage();
        }

        pageData.put("loginHtml", loginHtml);

        String pageParam = getParam("page");
        if("upload".equalsIgnoreCase(pageParam)){
            //ToDo: add check for UserName. Cannot be guest.
            return displayUploadPage(pageData, this.getRequest());
        }else if("login".equalsIgnoreCase(pageParam)){
            return displayLoginPage();
        }else if("search".equalsIgnoreCase(pageParam)){
            String typeParam = getParam("type");
            pageData.put("resultsTableHtml", "");
            if("adv-template".equalsIgnoreCase(typeParam)){
                return createHtmlTemplate("adv-template-search.ftl",pageData);
            }else if("adv-container".equalsIgnoreCase(typeParam)){
                return createHtmlTemplate("adv-container-search.ftl",pageData);
            }else if("adv-component".equalsIgnoreCase(typeParam)){
                return createHtmlTemplate("component-search.ftl",pageData);
            }else{
                throw new IllegalArgumentException("Unrecongnized type parameter. type="+typeParam);
            }

        }else if("admin".equalsIgnoreCase(pageParam)){
            return displayAdminPage(pageData, this.getQuery(), this.getRequest());
        }
//        }else if("admin-change".equalsIgnoreCase(pageParam)){
//            log.debug("create admin-change page");
//            String uid = getParam("uid");
//            AdminResource adminResource = new AdminResource();
//            adminResource.setAdminChangeParamsForUid(uid,pageData);
//            pageData.put("uid", uid);
//            return createHtmlTemplate("admin-change.ftl",pageData);
//        }

        return createHtmlTemplate("adv-template-search.ftl",pageData);
    }

    public static Representation displayAdminChangePage(Map<String,Object> pageData, Form form, Request request)
        throws ATSLoginRequiredException
    {
            log.debug("create admin-change page");
            return createHtmlTemplate("admin-change.ftl",pageData);
    }

    public static Representation displayAdminPage(Map<String,Object> pageData, Form form, Request request)
        throws ATSLoginRequiredException
    {
        String permData = generateAdminPermissionTable(form,request);
        pageData.put("permissionTableResult", permData);
        return createHtmlTemplate("admin.ftl",pageData);
    }

    private static Representation createHtmlTemplate(String templateName, Map<String,Object> pageData){
        return FreemarkerUtil.getInstance().
                toRepresentation(templateName,
                    pageData,MediaType.TEXT_HTML);
    }

    /**
     * Display the login page.
     * @return Representation
     */
    public static Representation displayLoginPage(){
        //just need empty data here.
        Map<String,Object> pageData = new HashMap<String, Object>();

        return FreemarkerUtil.getInstance().
            toRepresentation("login.ftl",
                pageData, MediaType.TEXT_HTML);
    }

    /**
     * Display the upload page.
     * @param pageData
     * @return Representation
     */
    public static Representation displayUploadPage(Map<String,Object> pageData, Request req){
        // Only logged in non-guest users can upload
        boolean isProperLogin = ATSLoginUtil.getInstance().isNonGuestLogin(req);
        pageData.put("isProperlyLogedIn", isProperLogin);

        if (!pageData.containsKey("isProperLogin"))
            pageData.put("isProperLogin", false);
        
        return FreemarkerUtil.getInstance().
            toRepresentation("upload.ftl",
                pageData, MediaType.TEXT_HTML);
    }

    public static String generateAdminResultsPage(List<String> tableRows, String templateName, Request req)
        throws ATSLoginRequiredException
    {
        try{
            Map<String,Object> pageData = new HashMap<String, Object>();
            //Is session still valid?
            String loginHtml = ATSLoginUtil.getInstance().checkForLoginCookie(req);
            if(loginHtml==null){
                throw new ATSLoginRequiredException();
            }
            pageData.put("loginHtml", loginHtml);
            pageData.put("permissionTableResult", generateTable(tableRows));
            pageData.put("message", "");

            return FreemarkerUtil.getInstance().toHtmlString(templateName, pageData);
        }catch(Exception e){
            log.error("Failed to generate template for: "+templateName, e);
            return generateErrorPageAsHtml("Failed to generate template for: "+templateName);
        }
    }

    /**
     *
     * @param tableRows
     * @param templateName
     * @return
     */
    public static String generateTemplateSearchResultsPage(List<String> tableRows, String templateName, Request req)
        throws ATSLoginRequiredException
    {
        try{
            Map<String,Object> pageData = new HashMap<String, Object>();
            //Is session still valid?
            String loginHtml = ATSLoginUtil.getInstance().checkForLoginCookie(req);
            if(loginHtml==null){
                throw new ATSLoginRequiredException();
            }
            pageData.put("loginHtml", loginHtml);
            pageData.put("resultsTableHtml", generateTable(tableRows));

            return FreemarkerUtil.getInstance().toHtmlString(templateName, pageData);
        } catch(ATSLoginRequiredException ex) {
        	throw ex;
        }catch(Exception e){
            log.error("Failed to generate template for: "+templateName, e);
            return generateErrorPageAsHtml("Failed to generate template for: "+templateName);
        }
    }


    public static String generateAdminPermissionTable(Form form, Request request)
            throws ATSLoginRequiredException
    {
        try{
            //log.debug("ftr.generateAdminPermissionTable");
            String username = ATSLoginUtil.getInstance().
                    getUsernameFromLoginCookie(request);
            if(username!=null){
                log.debug("username="+username);
                SimpleATSQueryResource r = new SimpleATSQueryResource();
                String table = r.getAdminPermissionTable(form,request);
                //log.debug("----\n"+table+"----\n");
                return table;
            }else{
                return "no username.";
            }
        }catch(Exception e){
            log.error("Failed to generate permission table.", e);
            return "Error";
        }catch(Error temp){
            log.error("Caught error: ", temp);
            return "Error::";
        }

    }


    /**
     * Creates the result table.
     * @param tableRows
     * @return
     */
    public static String generateTable(List<String> tableRows){
        StringBuilder sb = new StringBuilder();
        sb.append("<table id='resultTable'>");
        for(String curr: tableRows){
            sb.append(curr);
        }
        sb.append("</table>");

        return sb.toString();
    }


    /**
     * Generates an error message to the 'error-page.ftl' template.
     * @param errorMessage
     * @return String HTML of error page.
     */
    public static String generateErrorPageAsHtml(String errorMessage)
    {
        try{
            Representation rep = FreemarkerUtil.getInstance()
                .toRepresentation("error-page.ftl", errorMessage, MediaType.TEXT_HTML);

            return rep.getText();
        }catch(Exception e){
            log.error("Failed to generate error page", e);
            return "<html><body>"+errorMessage+"</body><html>";
        }
    }


    /**
     * Look for /web?...=...
     * @return String value of 'page' parameter.
     */
    private String getParam(String paramName){
        Form queryForm = this.getReference().getQueryAsForm();
        return getParam(paramName,queryForm);
    }

    private static String getParam(String paramName, Form queryForm){
        Set<String> names = queryForm.getNames();
        if(names.contains(paramName)){
            return queryForm.getFirstValue(paramName);
        }
        return null;
    }
}
