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
package edu.stanford.isis.ats.security.impl;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLEncoder;
import java.security.KeyManagementException;
import java.security.KeyStore;
import java.security.KeyStoreException;
import java.security.NoSuchAlgorithmException;
import java.security.cert.CertificateException;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

import javax.net.ssl.HttpsURLConnection;
import javax.net.ssl.SSLContext;
import javax.net.ssl.SSLSocketFactory;
import javax.net.ssl.TrustManagerFactory;

import org.restlet.engine.util.Base64;

import edu.stanford.isis.ats.ConfigParser;
import edu.stanford.isis.ats.security.SecurityManager;
import edu.stanford.isis.ats.security.SecurityStatus;
import edu.stanford.isis.ats.utils.ATSLogger;

/**
 * @author alansnyder
 * @author Vladimir Kleper
 */
public class SecurityManagerImpl implements SecurityManager {

	private Map<String, SessionStatus> sessions;
	private ATSLogger log;

	private static final String CA_GRID_SECURITY_URL = "CaGridSecurityUrl";
	private static Map<String, String> configValues;

	private final static String charsetUtf8 = "UTF-8";
	private final static String lineSeparator = System.getProperty("line.separator");

	private SecurityManagerImpl() {
		log = ATSLogger.getLogger();
		log.debug("SM-Impl");

		configValues = ConfigParser.readConfigVars(new String[] { CA_GRID_SECURITY_URL });

		sessions = new ConcurrentHashMap<String, SessionStatus>();
	}

	public static SecurityManagerImpl getInstance() {
		return SecurityManagerImpHolder.INSTANCE;
	}

	private static class SecurityManagerImpHolder {
		private static final SecurityManagerImpl INSTANCE = new SecurityManagerImpl();
	}

	/**
	 * Try to login. If it passes then return the value for the cookie. If it
	 * fails return null.
	 * 
	 * @param username - Username
	 * @param pwd - Password
	 * @return String value to use in the ATSSessionToken
	 */
	@Override
	public SecurityStatus doLogin(String username, String pwd) {

		// check guest account
		if (checkGuestAccount(username, pwd)) {
			SessionStatus ss = new SessionStatus(username, null);
			ss.setAsGuest();
			sessions.put(ss.getSessionToken(), ss);
			log.info("Using guest account.");
			return new SecurityStatus("login as guest", true, ss);

		}

		// temp testing item
//		if (checkTestAccount(username, pwd)) {
//			SessionStatus ss = new SessionStatus(username, null);
//			sessions.put(ss.getSessionToken(), ss);
//			log.info("Using test account. ****");
//			return new SecurityStatus("test account", true, ss);
//		}

		final String token = doCaGridLogin2(username, pwd);

		if (token != null) {
			SessionStatus ss = new SessionStatus(username, token);
			// TODO VK: Get group info from the token or an authorization service
//			ss.setGroups(token.getGroupMembership());
			sessions.put(ss.getSessionToken(), ss);
			return new SecurityStatus("good login", true, ss);
		}

		return null;
	}

	@Override
	public SecurityStatus checkLogin(String cookieValue) {
	    
		// log.debug("SMI.checkLogin");
		SessionStatus sessionStatus = cookieValue == null ? null : sessions.get(cookieValue);

		if (sessionStatus != null && sessionStatus.hasExpired()) {
			log.debug("SMI remove expired cookie");
			sessions.remove(cookieValue);
			return new SecurityStatus("session expired", false, null);
		}

		if (sessionStatus == null) {
			log.debug("SMI invalid cookie");
			return new SecurityStatus("invalid session cookie", false, null);
		}

		log.debug("SMI valid cookie");
		return new SecurityStatus("valid cookie", true, sessionStatus);
	}

    @Override
    public void doLogout(String cookieValue) {
        if (sessions.containsKey(cookieValue))
            sessions.remove(cookieValue);
    }

	// Authenticates against current STS and returns received SAML assertion
	private String doCaGridLogin2(String username, String password) {
    	try {
    		
    		final String authUtl = String.format("%s/issueToken?targetService=%s", 
    				configValues.get(CA_GRID_SECURITY_URL), 
    				URLEncoder.encode("http://services.testcorp.org/provider1", charsetUtf8));
			final URL loginUrl = new URL(authUtl);
			final HttpURLConnection conn = (HttpURLConnection)loginUrl.openConnection();

			// Add self-signed certs to the SSL context
			try {
				if (conn instanceof HttpsURLConnection) {
					final SSLContext sslContext = SSLContext.getInstance("TLS");
					final TrustManagerFactory tmf = TrustManagerFactory.getInstance(TrustManagerFactory.getDefaultAlgorithm());
					final KeyStore ks = KeyStore.getInstance("JKS");
					
					// NOTE: This requires JKS file to be present in the right location; therefore, the file may not be found in the debugger.
					final InputStream inputJks = this.getClass().getClassLoader().getResourceAsStream("certificate/stsClient.jks");
					ks.load(inputJks, "yearkiwi".toCharArray());
					tmf.init(ks);
					sslContext.init(null, tmf.getTrustManagers(), null);

					final SSLSocketFactory sf = sslContext.getSocketFactory();
					((HttpsURLConnection) conn).setSSLSocketFactory(sf);
				}
			} catch (IOException ex) {
				log.error("Login2: Failed to load keystore", ex);
			}  catch (NoSuchAlgorithmException ex) {
				log.error("Login2: Failed to load keystore", ex);
			} catch (KeyStoreException ex) {
				log.error("Login2: Failed to load keystore", ex);
			} catch (CertificateException ex) {
				log.error("Login2: Failed to load keystore", ex);
			} catch (KeyManagementException ex) {
				log.error("Login2: Failed to load keystore", ex);
			}
			
			conn.setRequestMethod("GET");
			conn.setRequestProperty("Accept-Charset", charsetUtf8);
			
			// Encode user name and password pair with a base64 implementation.
			final String userPass = username + ":" + password;
			final String encoded = Base64.encode(userPass.toCharArray(), charsetUtf8, false);
			// Basic access authentication header to connection request.
			conn.setRequestProperty("Authorization", "Basic " + encoded);
			
			conn.setUseCaches(false);
			conn.setRequestProperty("User-Agent",
					String.format("ATS/1.0 (%s; %s; %s)",
							URLEncoder.encode(System.getProperty("os.name"), charsetUtf8),
							URLEncoder.encode(System.getProperty("os.version"), charsetUtf8), 
							URLEncoder.encode(System.getProperty("os.arch"), charsetUtf8)));
			
			conn.connect();
			int responseCode = conn.getResponseCode();
			log.debug("Login2: Response returned by the server = " + responseCode);
			
			if (responseCode == 401) {
				log.info("Authorization failed for [" + username + "] (WWW-Authenticate=" + conn.getHeaderField("WWW-Authenticate") + ") [response = " + responseCode + "].");
				return null;
			}

			// Read response
			final String contentType = conn.getHeaderField("Content-Type");
			String charset = null;
			for (String param : contentType.replace(" ", "").split(";")) {
			    if (param.startsWith("charset=")) {
			        charset = param.split("=", 2)[1];
			        break;
			    }
			}
			// Assume UTF-8 for xml if no charset was provided
			if (charset == null && contentType != null && contentType.contains("text/xml"))
				charset = charsetUtf8;
			
			final StringBuffer sb = new StringBuffer();
			if (charset != null) {
			    BufferedReader reader = null;
			    try {
					reader = new BufferedReader(new InputStreamReader(conn.getInputStream(), charset));
					for (String line; (line = reader.readLine()) != null;) {
						sb.append(line).append(lineSeparator);
					}
			    } finally {
					if (reader != null)
						try {
							reader.close();
						} catch (IOException logOrIgnore) {}
			    }
			} else {
			    log.debug("Login2: Failed to understand response. " + contentType);
			}
			
			log.debug("Login2 Token: \n" + sb.toString());
			if (sb.length() > 0)
				return sb.toString();
			
		} catch (MalformedURLException ex) {
			log.error("Login2: Failed to instantiate login URL (" + configValues.get(CA_GRID_SECURITY_URL) + ")", ex);
			return null;
		} catch (IOException ex) {
			log.error("Login2: Failed to connect to login server", ex);
		} catch (Exception ex) {
			log.error("Login2: Failed to connect to login server and retrieve security token", ex);
		} 
    	
    	return null;
    }
	
	/**
	 * User this account when the caGrid isn't available.
	 * 
	 * @param user
	 * @param password
	 * @return boolean
	 */
	private boolean checkTestAccount(String user, String password) {
		return ("guest2".equals(user) && "guest2".equals(password));
	}

	/**
	 * Determine if this is a guest account.
	 * 
	 * @param user
	 * @param password
	 * @return true if this is a guest account.
	 */
	private boolean checkGuestAccount(String user, String password) {
		return ("guest".equalsIgnoreCase(user) && "guest"
				.equalsIgnoreCase(password));
	}

}
