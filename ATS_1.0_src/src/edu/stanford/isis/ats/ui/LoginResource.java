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

import edu.stanford.isis.ats.security.SecurityManager;
import edu.stanford.isis.ats.security.SecurityStatus;
import edu.stanford.isis.ats.security.impl.SecurityManagerImpl;
import edu.stanford.isis.ats.utils.ATSLogger;
import edu.stanford.isis.ats.utils.ATSLoginUtil;
import edu.stanford.isis.ats.utils.FreemarkerUtil;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;
import org.restlet.data.CookieSetting;
import org.restlet.data.Form;
import org.restlet.data.MediaType;
import org.restlet.representation.Representation;
import org.restlet.resource.Get;
import org.restlet.resource.Post;
import org.restlet.resource.ServerResource;
import org.restlet.util.Series;

/**
 *
 * @author alansnyder
 * @author Vladimir Kleper
 */
public class LoginResource extends ServerResource {

    ATSLogger log;
    SecurityManager securityManager;

    public LoginResource(){
        log = ATSLogger.getLogger();
        log.debug("LoginResource");
        securityManager = SecurityManagerImpl.getInstance();
    }

    /**
     * Show the login page, or deal with a session logout.
     * @param entity
     * @return
     */
    @Get
    public Representation handleGet(Representation entity){

        //check for logout.
        checkForLogout();

        //display the login page.
        Map<String,Object> pageData = new HashMap<String, Object>();

        return FreemarkerUtil.getInstance().
                toRepresentation("login.ftl",
                pageData, MediaType.TEXT_HTML);
    }

    /**
     * If the parameter is '/login?page=logout
     * @return true if it tried to clear cookies, otherwise false.
     */
    private boolean checkForLogout(){

        String page = getPageParam();
        if("logout".equalsIgnoreCase(page)){
            securityManager.doLogout(ATSLoginUtil.getInstance().getLoginCookieValue(this.getRequest()));
            Series<CookieSetting> cookies = this.getResponse().getCookieSettings();
            cookies.clear();
            this.getResponse().setCookieSettings(cookies);
            return true;
        }
        return false;
    }

    /**
     * Look for /web?page=...
     * @return String value of 'page' parameter.
     */
    private String getPageParam(){
        Form queryForm = this.getReference().getQueryAsForm();
        Set<String> names = queryForm.getNames();
        if(names.contains("page")){
            return queryForm.getFirstValue("page");
        }
        return null;
    }

    /**
     * Try to validate a login and forward a GET to /web
     * @param entity
     * @return
     */
    @Post
    public Representation receiveRepresentation(Representation entity){
        
        Form queryForm = new Form(entity);
        String user = queryForm.getFirstValue("user");
        String pass = queryForm.getFirstValue("pass");
        String asGuest = queryForm.getFirstValue("guest");
        if(asGuest!=null){
            log.debug("As guest checked.");
            user="guest";
            pass="guest";
        }

        String loginName = null;
        Set<String> loginGroups = null;
        log.debug("User name: "+user+" has entered a password.");

        SecurityStatus securityStatus = securityManager.doLogin(user, pass);
        if(securityStatus!=null){
            loginName=user;
            loginGroups = securityStatus.getGroups();
            log.debug("Login success!! sessionCookieValue="+securityStatus.getToken());
        } else {
            //return to error page.
            Map<String,Object> pageData = new HashMap<String, Object>();
            pageData.put("errorMessage", "Login failed");
            return FreemarkerUtil.getInstance()
                    .toRepresentation("error-page.ftl", pageData, MediaType.TEXT_HTML);
        }

        Map<String,Object> pageData = createPageData(loginName, loginGroups);
        Representation returnRep = FreemarkerUtil.getInstance()
                .toRepresentation("adv-template-search.ftl", pageData, MediaType.TEXT_HTML);

        //set cookie.
        CookieSetting cs = ATSLoginUtil.createATSSessionCookie(securityStatus.getToken());
        Series<CookieSetting> series = this.getResponse().getCookieSettings();
        series.add(cs);
        this.getResponse().setCookieSettings(series);

        return returnRep;
    }

    private Map<String,Object> createPageData(String loginName, Set<String> loginGroups){
        Map<String,Object> retVal = new HashMap<String,Object>();
        retVal.put("loginHtml", ATSLoginUtil.showLoginName(loginName, loginGroups));
        retVal.put("resultsTableHtml", "");
        return retVal;
    }

}
