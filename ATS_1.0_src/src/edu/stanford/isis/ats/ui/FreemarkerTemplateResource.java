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
