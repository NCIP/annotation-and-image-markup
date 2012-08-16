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
