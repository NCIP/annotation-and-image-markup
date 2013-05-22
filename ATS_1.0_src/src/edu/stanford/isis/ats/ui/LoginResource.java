/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
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
