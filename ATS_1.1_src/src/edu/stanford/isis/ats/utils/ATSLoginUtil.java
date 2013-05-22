/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.ats.utils;

import java.util.Set;

import org.restlet.Request;
import org.restlet.data.Cookie;
import org.restlet.data.CookieSetting;
import org.restlet.util.Series;

import edu.stanford.isis.ats.security.SecurityManager;
import edu.stanford.isis.ats.security.SecurityStatus;
import edu.stanford.isis.ats.security.impl.SecurityManagerImpl;
import edu.stanford.isis.ats.security.impl.SessionStatus;

/**
 *
 * @author alansnyder
 * @author Vladimir Kleper
 */
public class ATSLoginUtil {

    public static final String ATS_SESSION_COOKIE = "ATSSessionCookie";
    private static final ATSLogger log = ATSLogger.getLogger();

    private SecurityManager securityManager;

    private ATSLoginUtil() {
        securityManager = SecurityManagerImpl.getInstance(); 
    }

    public static ATSLoginUtil getInstance() {
        return ATSLoginUtilHolder.INSTANCE;
    }

    private static class ATSLoginUtilHolder {
        private static final ATSLoginUtil INSTANCE = new ATSLoginUtil();
    }
    
    public String getUsernameFromLoginCookie(Request req){
        final SecurityStatus ss = getSecurityStatusFromLoginCookie(req);
        return ss == null ? null : ss.getUsername();
    }

    private SecurityStatus getSecurityStatusFromCookieSeries(Series<Cookie> cookies, Request req)
    {
        final String cookieValue = this.getLoginCookieValue(cookies, req);
        final SecurityStatus ss = securityManager.checkLogin(cookieValue);
        if (ss != null && ss.hasValidSession()) {
            log.debug("Validated cookieValue=" + cookieValue + " for userName=" + ss.getUsername());
            return ss;
        } else {
            log.debug("cookieValue=" + cookieValue + " was invalid. Removing it.");
            cookies.removeAll(ATSLoginUtil.ATS_SESSION_COOKIE);
            if (req != null) {
                req.setCookies(cookies);
            }
            return null;
        }
    }

    private SecurityStatus getSecurityStatusFromLoginCookie(Request req){
        Series<Cookie> cookies = req.getCookies();
        return getSecurityStatusFromCookieSeries(cookies,req);
    }

    /**
     * Check that this request has a valid ATS session cookie.
     * @return String. If a valid login then return the name. Otherwise null.
     */
    public String checkForLoginCookie(Request req){
        final SecurityStatus ss = getSecurityStatusFromLoginCookie(req);
        return ss == null ? null : ATSLoginUtil.showLoginName(ss.getUsername(),ss.getGroups());
    }

    /**
     * Checks whether the given request has a valid login cookie or not
     * @return true is cookie is present and valid; false - otherwise
     */
    public boolean isLoginValid(Request req) {
        return getSecurityStatusFromLoginCookie(req) != null;
    }
    
    /**
     * Checks whether the currently logged in user is logged in and does NOT belong to the guest group.
     * @param req - web request
     * @return returns true if the user is logged in under non-guest account; false - if not logged in or is a guest
     */
    public boolean isNonGuestLogin(Request req) {
        final SecurityStatus ss = getSecurityStatusFromLoginCookie(req);
        return ss == null ? false : !ss.isGuest();
    }
    
    public String getLoginCookieValue(Request req) {
        return req == null ? null : getLoginCookieValue(req.getCookies(), req);
    }

    private String getLoginCookieValue(Series<Cookie> cookies, Request req) {
        if (cookies != null) {
            log.debug("Found " + cookies.size() + " cookies.");
            for (Cookie cookie : cookies) {
                final String cookieName = cookie.getName();
                final String cookieValue = cookie.getValue();
                // log.debug("Cookie: "+cookieName+" , "+cookieValue);
                if (ATSLoginUtil.ATS_SESSION_COOKIE.equalsIgnoreCase(cookieName)) {
                    return cookieValue;
                }
            }
        }
        log.debug("No valid cookie found.");
        return null;
    }

    /**
     *
     * @return
     */
//    public static String showLoginHtml(){
//        StringBuilder sb = new StringBuilder();
//        sb.append("<div id='loginSection'>");
//        sb.append("<form class='loginForm' action='/templates/login' method='post'>");
//        sb.append("<table id='login'>");
//        sb.append("<tr>");
//        sb.append("  <td> login: <input type='text' name='user' size='15'></td>");
//        sb.append("  <td> password: <input type='password' name='pass' size='10'></td>");
//        sb.append("  <td> <input type='submit' value='Login'></td>");
//        sb.append("</tr>");
//        sb.append("</table>");
//        sb.append("");
//        sb.append("</form>");
//        sb.append("</div>");
//        sb.append("<br />");
//
//        return sb.toString();
//    }

    public static String showLoginName(SessionStatus sessionStatus){
        return showLoginName(sessionStatus.getUsername(), sessionStatus.getGroups());
    }

    /**
     * Create HTML <div/> with logged-in user's name and groups
     * @param user - user name to display
     * @param groups - list of user groups to display. Can be null.
     * @return - returns HTML fragment that contains user's name and groups
     */
    public static String showLoginName(String user, Set<String> groups) {
        final StringBuilder sb = new StringBuilder();
        sb.append("<div id='loginSection' class='loginStatus'>login name: ");
        sb.append(user);
        sb.append("&nbsp;|&nbsp;");
        if (groups != null) {
            boolean first = true;
            for (String currGroup : groups) {
                if (currGroup == null)
                    continue;
                if (first) {
                    sb.append("group: ");
                    first = false;
                } else {
                    sb.append(", ");
                }
                sb.append(currGroup);
            }
            if (!first)
                sb.append("&nbsp;|&nbsp;");
        }
        sb.append("<a href='/templates/login?page=logout'>Sign out</a></div>");

        return sb.toString();
    }

    /**
     * 
     * @param value
     * @return
     */
    public static CookieSetting createATSSessionCookie(String value){
        CookieSetting cs = new CookieSetting();
        cs.setName(ATS_SESSION_COOKIE);
        cs.setValue(value);

        return cs;
    }
}
