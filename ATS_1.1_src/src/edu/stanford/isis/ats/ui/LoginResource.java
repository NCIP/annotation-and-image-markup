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
