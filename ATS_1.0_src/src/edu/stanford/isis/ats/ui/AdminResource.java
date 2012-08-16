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
