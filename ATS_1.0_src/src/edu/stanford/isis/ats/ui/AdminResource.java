/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


package edu.stanford.isis.ats.ui;

import java.util.HashMap;
import java.util.LinkedHashSet;
import java.util.Map;
import java.util.StringTokenizer;

import org.restlet.data.Form;
import org.restlet.data.MediaType;
import org.restlet.data.Parameter;
import org.restlet.data.Status;
import org.restlet.representation.Representation;
import org.restlet.representation.StringRepresentation;
import org.restlet.resource.Get;
import org.restlet.resource.Post;

import com.sleepycat.dbxml.XmlContainer;
import com.sleepycat.dbxml.XmlDocument;
import com.sleepycat.dbxml.XmlException;
import com.sleepycat.dbxml.XmlManager;
import com.sleepycat.dbxml.XmlManagerConfig;
import com.sleepycat.dbxml.XmlResults;

import edu.stanford.isis.ats.security.ATSLoginRequiredException;
import edu.stanford.isis.ats.utils.ATSLoginUtil;
import edu.stanford.isis.ats.utils.ATSStringUtils;
import edu.stanford.isis.ats.xmldb.MetaDataUtil;
import edu.stanford.isis.ats.xmldb.XMLDatabaseResource;

/**
 * @author alansnyder
 * @author Vladimir Kleper
 */
public class AdminResource extends XMLDatabaseResource {

    @Get
    public Representation createAdminChange(Representation entity) {
        String uid = "n/a";
        String containerName = "";

        XmlManager manager = null;
        XmlContainer container = null;
        try {
            // check for login.
            String loginHtml = ATSLoginUtil.getInstance().checkForLoginCookie(this.getRequest());
            if (loginHtml == null) {
                return FreemarkerTemplateResource.displayLoginPage();
            }

            Map<String, Object> pageData = new HashMap<String, Object>();
            pageData.put("loginHtml", loginHtml);
            pageData.put("containerName", containerName);

            Form queryForm = this.getReference().getQueryAsForm();

            final Parameter paramUid = queryForm.getFirst("uid", true);
            if (paramUid == null) {
                // Display admin page if no UID is provided
                final String message = "Select a template to start editing its permissions";
                pageData.put("message", message);
                return FreemarkerTemplateResource.displayAdminPage(pageData, queryForm, this.getRequest());
            }

            uid = paramUid.getValue();
            pageData.put("uid", uid);
            log.debug("createAdminChange uid=" + uid);

            // putContainerName(queryForm,pageData); //${containerName} in admin-change.ftl page.

            String collection = getCollection(queryForm);
            manager = new XmlManager(env, XmlManagerConfig.DEFAULT);
            container = MetaDataUtil.getXmlContainerForCollection(collection, manager);

            setAdminChangeParamsForUid(uid, pageData, manager, queryForm);
            return FreemarkerTemplateResource.displayAdminChangePage(pageData, queryForm, this.getRequest());

        } catch (ATSLoginRequiredException ex) {
            return FreemarkerTemplateResource.displayLoginPage();
        } catch (Exception e) {
            String err = "Error changing uid=" + uid;
            log.error(err, e);
            setStatus(Status.SERVER_ERROR_INTERNAL, err);
            return new StringRepresentation(genErrorXML(err), MediaType.TEXT_XML);
        } finally {
            MetaDataUtil.closeXmlContainer(container);
            MetaDataUtil.closeXmlManager(manager);
        }
    }

    @Post
    public Representation receiveRepresentation(Representation entity) {
        String uid = "n/a";

        XmlManager manager = null;
        XmlContainer container = null;
        try {
            // check for login.
            String loginHtml = ATSLoginUtil.getInstance().checkForLoginCookie(this.getRequest());
            if (loginHtml == null) {
                return FreemarkerTemplateResource.displayLoginPage();
            }

            Map<String, Object> pageData = new HashMap<String, Object>();
            pageData.put("loginHtml", loginHtml);

            Form queryForm = new Form(entity);
            String function = queryForm.getFirstValue("function", true);
            // log.debug("function=_"+function+"_");

            final String btnCancel = queryForm.getFirstValue("btnCancel");

            uid = queryForm.getFirstValue("uid", true);

            String collection = getCollection(queryForm);
            manager = new XmlManager(env, XmlManagerConfig.DEFAULT);
            container = MetaDataUtil.getXmlContainerForCollection(collection, manager);

            String message = null;
            if (btnCancel != null) {
                ; // NO-OP
            } else if ("change".equalsIgnoreCase(function)) {
                log.debug("change");
                message = processChange(uid, queryForm, container, manager);
            } else if ("delete".equalsIgnoreCase(function)) {
                log.debug("delete");
                message = processDelete(uid, queryForm, container, manager);
            } else {
                log.debug("AdminResource doesn't recognize function=" + function);
            }

            pageData.put("message", message);
            return FreemarkerTemplateResource.displayAdminPage(pageData, queryForm, this.getRequest());
        } catch (ATSLoginRequiredException ex) {
            return FreemarkerTemplateResource.displayLoginPage();
        } catch (Exception e) {
            String err = "Error changing uid=" + uid;
            log.error(err, e);
            setStatus(Status.SERVER_ERROR_INTERNAL, err);
            return new StringRepresentation(genErrorXML(err), MediaType.TEXT_XML);
        } finally {
            // close all the potential resources used here.
            MetaDataUtil.closeXmlContainer(container);
            MetaDataUtil.closeXmlManager(manager);
        }
    }

    private static XmlResults getResultSetForCollecton(Form queryForm, XmlManager manager) throws XmlException {
        String collection = getCollection(queryForm);
        String namespace = getNamespace(queryForm);

        return MetaDataUtil.queryForAdmin(manager, collection, namespace);
    }

    private void setAdminChangeParamsForUid(String uid, Map<String, Object> pageParam, XmlManager manager, Form queryForm) {
        XmlResults xmlResults = null;
        try {
            xmlResults = getResultSetForCollecton(queryForm, manager);
            XmlDocument doc = MetaDataUtil.getXmlDocumentForUid(uid, xmlResults);

            pageParam.put("owner", MetaDataUtil.getMetaData(MetaDataUtil.OWNER, doc));
            pageParam.put("permission", MetaDataUtil.getMetaData(MetaDataUtil.PERMISSION, doc));
            pageParam.put("allowedUsers", MetaDataUtil.getMetaData(MetaDataUtil.ALLOWED_USER, doc));
            pageParam.put("published-date", MetaDataUtil.getMetaData(MetaDataUtil.DATE_PUBLISHED, doc));
            pageParam.put("templateDocName", MetaDataUtil.getMetaData(MetaDataUtil.DOC_FILE_NAME, doc));

        } catch (XmlException ex) {
            log.error("setAdminChangeParam... had: ", ex);
        } finally {
            MetaDataUtil.deleteXmlResults(xmlResults);
        }
    }

    private String processChange(String uid, Form queryForm, XmlContainer container, XmlManager manager) {
        XmlResults xmlResults = null;
        try {
            StringBuilder message = new StringBuilder();
            String result = null;

            xmlResults = getResultSetForCollecton(queryForm, manager);
            XmlDocument doc = MetaDataUtil.getXmlDocumentForUid(uid, xmlResults);

            // 1. Validate and save Permission
            final String permission = getFormParameterValue(MetaDataUtil.PERMISSION, queryForm, true);
            if (permission != null) {
                if (permission.equals(MetaDataUtil.PERM_PUBLIC) || permission.equals(MetaDataUtil.PERM_PRIVATE) || permission.equals(MetaDataUtil.PERM_GROUP))
                    queryForm.set(MetaDataUtil.PERMISSION, permission);
                else
                    queryForm.set(MetaDataUtil.PERMISSION, null);
            }
            result = MetaDataUtil.changeMetaDataIfFound(doc, MetaDataUtil.PERMISSION, queryForm);
            if (result != null) {
                message.append(result).append("\n");
            }
            
            // 2. Make sure that Allowed Users is a comma-separated list of unique valid user names
            // TODO - refactor validation
            final String allowedUsers = getFormParameterValue(MetaDataUtil.ALLOWED_USER, queryForm, false);
            if (allowedUsers != null) {
                final StringTokenizer strTok = new StringTokenizer(allowedUsers, ",");
                final LinkedHashSet<String> users = new LinkedHashSet<String>();
                while(strTok.hasMoreTokens()) {
                    final String userName = strTok.nextToken().trim();
                    // allow for non-empty alphanumeric user names with "_-~" chars
                    if (userName.length() < 1 || !userName.matches("^[a-zA-Z0-9-~_]+$"))
                        continue;
                    users.add(userName);
                }
                queryForm.set(MetaDataUtil.ALLOWED_USER, users.isEmpty() ? null : ATSStringUtils.join(users, ","));
            }
            result = MetaDataUtil.changeMetaDataIfFound(doc, MetaDataUtil.ALLOWED_USER, queryForm);
            container.updateDocument(doc);
            log.debug("Updated meta-data for doc uid=" + uid + " message=" + message.toString());
            return message.toString();
        } catch (XmlException ex) {
            log.error("Failed to update document uid=" + uid, ex);
            return ex.getMessage();
        } finally {
            MetaDataUtil.deleteXmlResults(xmlResults);
        }
    }

    private String processDelete(String uid, Form queryForm, XmlContainer container, XmlManager manager) {
        XmlResults xmlResults = null;
        try {
            xmlResults = getResultSetForCollecton(queryForm, manager);
            XmlDocument doc = MetaDataUtil.getXmlDocumentForUid(uid, xmlResults);

            container.deleteDocument(doc);
            return "Deleted document uid=" + uid;
        } catch (XmlException ex) {
            log.error("Failed to delete document uid=" + uid, ex);
            return "Failed to delete document uid=" + uid;
        } finally {
            MetaDataUtil.deleteXmlResults(xmlResults);
        }
    }
    
    private static String getFormParameterValue(String paramName, Form queryForm, boolean lowerCase) {
        final Parameter param = queryForm.getFirst(paramName, true);
        return param == null ? null : (lowerCase ? param.getValue().toLowerCase() : param.getValue());
    }
}
