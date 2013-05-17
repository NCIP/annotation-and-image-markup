/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
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
import java.util.Enumeration;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

import javax.net.ssl.HttpsURLConnection;
import javax.net.ssl.SSLContext;
import javax.net.ssl.SSLSocketFactory;
import javax.net.ssl.TrustManagerFactory;

import org.picketlink.identity.federation.api.wstrust.WSTrustClient;
import org.picketlink.identity.federation.core.exceptions.ParsingException;
import org.picketlink.identity.federation.core.wstrust.SamlCredential;
import org.picketlink.identity.federation.core.wstrust.WSTrustException;
import org.picketlink.identity.federation.core.wstrust.plugins.saml.SAMLUtil;
import org.restlet.engine.util.Base64;
import org.w3c.dom.Element;

import edu.emory.cci.sts.client.CaGridSecurityTokenAttribute;
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

	private void loadResource(Class<?> clazz, String ... resourceNames) {
		if (clazz == null)
			return;
		for(String resourceName : resourceNames) {
			// Test #1
			InputStream in1 = clazz.getClassLoader().getResourceAsStream(resourceName);
			if (in1 != null)
				log.debug("ZZZ: ClassLoader[" + clazz.getName() + "] loaded resource: " + resourceName);
			// Test #2
			InputStream in2 = clazz.getResourceAsStream(resourceName);
			if (in2 != null)
				log.debug("ZZZ: Class[" + clazz.getName() + "] loaded resource: " + resourceName);
			// Test #3
			this.loadSystemResource(resourceName);
		}
	}

	private void loadSystemResource(String resourceName) {
		Enumeration<URL> res;
		try {
			res = ClassLoader.getSystemResources(resourceName);
			while(res.hasMoreElements())
				log.debug("ZZZ: System Resource: " + res.nextElement().getPath());
		} catch (IOException e) {
			log.error("ZZZ: loadSystemResource error: " + e.getMessage(), e);
		}
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
