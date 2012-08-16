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
package edu.stanford.isis.ats.xmldb;

import java.io.File;
import java.io.FileOutputStream;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.apache.commons.fileupload.FileItem;
import org.apache.commons.fileupload.FileUploadException;
import org.apache.commons.fileupload.disk.DiskFileItemFactory;
import org.restlet.data.Disposition;
import org.restlet.data.MediaType;
import org.restlet.data.Method;
import org.restlet.data.Parameter;
import org.restlet.engine.http.header.DispositionReader;
import org.restlet.engine.http.header.HeaderConstants;
import org.restlet.ext.fileupload.RestletFileUpload;
import org.restlet.representation.Representation;
import org.restlet.representation.StringRepresentation;
import org.restlet.resource.Get;
import org.restlet.resource.Post;
import org.restlet.util.Series;

import com.sleepycat.db.DatabaseException;
import com.sleepycat.dbxml.XmlContainer;
import com.sleepycat.dbxml.XmlDocument;
import com.sleepycat.dbxml.XmlDocumentConfig;
import com.sleepycat.dbxml.XmlException;
import com.sleepycat.dbxml.XmlInputStream;
import com.sleepycat.dbxml.XmlManager;
import com.sleepycat.dbxml.XmlManagerConfig;
import com.sleepycat.dbxml.XmlValue;

import edu.stanford.isis.ats.data.validation.AimTemplateValidator;
import edu.stanford.isis.ats.data.validation.TemplateValidationException;
import edu.stanford.isis.ats.ui.FreemarkerTemplateResource;
import edu.stanford.isis.ats.utils.ATSLoginUtil;

/**
 *
 * @author alansnyder
 * @author Vladimir Kleper
 * @see edu.cornell.cs.aimannotations.server.xmldbresource
 */
public class UploadResource extends XMLDatabaseResource {

    private static final class UidFilePair {
        private String uid;
        private File file;

        public UidFilePair(String uid, File file) {
            this.uid = uid;
            this.file = file;
        }

        public String getUid() {
            return uid;
        }

        public File getFile() {
            return file;
        }
   }
    
    /**
     * Processes POST requests of file upload.
     * 
     * @param entity
     * @return
     */
    @Post
    public Representation receiveRepresentation(Representation entity) {
        if (entity != null) {
            // VK: check credentials before uploading
            if (!ATSLoginUtil.getInstance().isLoginValid(this.getRequest()))
                return FreemarkerTemplateResource.displayLoginPage();
            
            if (entity.getMediaType().equals(MediaType.MULTIPART_FORM_DATA, true))
                return receiveMultipartFormData();
            else if (entity.getMediaType().equals(MediaType.APPLICATION_XML, true))
                return receiveXmlFile(entity);
        }
        return this.createRepresentation("Error: Form type must be multipart/form-data or file", null);
    }

    @Get
    public Representation receiveRepresentatinGet(Representation entity) {
        return this.createRepresentation(null, null);
    }
    
    // FIXME: vk: - see if this is never called
    private Representation receiveXmlFile(Representation entity) {
        Representation returnRep;
        File storeDir = new File(dbVars.get("dbpath"));
        try {
            @SuppressWarnings("unchecked")
            Series<Parameter> params = (Series<Parameter>) this.getRequest().getAttributes().get(HeaderConstants.ATTRIBUTE_HEADERS); // "org.restlet.http.headers"
            String header = params.getFirstValue(HeaderConstants.HEADER_CONTENT_DISPOSITION);
            if (header == null)
                throw new Exception("No Content-Disposition found in header.");
            Disposition disp = new DispositionReader(header).readValue();
            String containerName = disp.getParameters().getFirstValue("collection");

            File tempFile = new File(storeDir, disp.getFilename());

            log.debug("Uploading temp file.: " + tempFile.getAbsolutePath());

            FileOutputStream fos = new FileOutputStream(tempFile);
            entity.write(fos);
            fos.close();
            List<File> uploaded = new ArrayList<File>();
            uploaded.add(tempFile);
            returnRep = addFiles(uploaded, containerName);
        } catch (Exception e) {
            returnRep = this.createRepresentation("File upload failed: " + e.getMessage(), null);
        }

        return returnRep;
    }

    private Representation receiveMultipartFormData() {
        final File storeDir = new File(dbVars.get("dbpath"), "temp");
        List<FileItem> files = null;
        boolean bOk = true;
        if (!storeDir.exists()) {
            try {
                storeDir.mkdir();
            } catch (SecurityException ex) {
                log.error("(UR-225) Cannot create temp upload folder", ex);
                bOk = false;
            }
        }
        
        if (bOk) {
            DiskFileItemFactory itemFactory = new DiskFileItemFactory();
            itemFactory.setSizeThreshold(1024000);
            RestletFileUpload fileUpload = new RestletFileUpload(itemFactory);
            try {
                files = fileUpload.parseRequest(getRequest());
                log.debug("Multipart- found: " + files.size() + " files to upload.");
            } catch (FileUploadException e) {
                log.error("UR-81", e);
            }
        }

        String containerName = null;
        final List<File> uploaded = new ArrayList<File>();
        if (files != null) {
            for (FileItem fi : files) {
                // Check to see if the FileItem is in fact the form field
                // containing the container we should use
                if (fi.isFormField() && fi.getFieldName().equals("collection")) {
                    containerName = fi.getString();
                } else if (fi.getName() != null && fi.getName().length() > 0) {

                    String onlyFileName = getFileNameAtEndOfPath(fi);
                    File file = new File(storeDir, onlyFileName);

                    boolean failed = false;
                    try {
                        fi.write(file);
                    } catch (Exception e) {
                        log.error("UR-97", e);
                        failed = true;
                    }
                    if (!failed)
                        uploaded.add(file);
                    log.debug("Mulitpart uploaded: " + file.getAbsolutePath());
                }
            }
        }

        return addFiles(uploaded, containerName);
    }

    private Representation addFiles(List<File> uploaded, String containerName) {
        XmlManager manager = null;
        XmlContainer container = null;
        log.debug("Uploading: " + uploaded.size() + " files to " + containerName);
        String returnString = null;
        String error = null;

        // FIXME: The document is being read three times: twice during validation and once during load. Do I want to load it into memory if it is too big?

        // Validation
        final List<UidFilePair> uidFilePairs = new ArrayList<UploadResource.UidFilePair>();
        for (File file : uploaded) {
            try {
                final String uid = AimTemplateValidator.validateTemplateAndGetUid(file);
                if (returnString == null && uid != null)
                    uidFilePairs.add(new UidFilePair(uid, file));
            } catch (TemplateValidationException e) {
                uidFilePairs.clear(); // make it all or nothing uploading
                if (returnString == null)
                    returnString = "Validation Error(s): \n";
                returnString += e.getMessage();
                if (e.getReason() != null)
                    returnString += " Reason: " + e.getReason();
                returnString += "\n";
            }
        }
        
        if (uidFilePairs.size() > 0) {
            log.debug("Validated file count is " + uidFilePairs.size());
            returnString = "Files added:\n";
            try {
                manager = new XmlManager(env, XmlManagerConfig.DEFAULT);
                if (manager.existsContainer(containerName) == 0) {
                    returnString = "Collection created.\n" + returnString;
                    container = manager.createContainer(containerName);
                } else {
                    container = manager.openContainer(containerName);
                    returnString = "Added to collection " + containerName + ".\n" + returnString;
                }

                XmlDocumentConfig docConfig = XmlDocumentConfig.DEFAULT;
                docConfig.setGenerateName(false);
                for (UidFilePair ufp : uidFilePairs) {
                    final File f = ufp.getFile();
                    XmlInputStream xis = manager.createLocalFileInputStream(f.getPath());
                    XmlDocument doc = manager.createDocument();
                    doc.setName(ufp.getUid());
                    doc.setContentAsXmlInputStream(xis);
                    addMetaData(doc, f.getName());
                    container.putDocument(doc, docConfig);
                    returnString += f.getName() + "\n";

                    log.debug("Added file " + f.getName() + " with uid=" + ufp.getUid());
                }
            } catch (DatabaseException e) {
                log.error("(UR-152) Failed to upload file.", e);
                returnString = "Error - internal database (UR-167): " + e.getMessage();

                // Get a specific error for the web
                if (e instanceof XmlException) {
                    final XmlException ex = (XmlException) e;
                    switch (ex.getErrorCode()) {
                    case XmlException.NO_MEMORY_ERROR:
                        error = "Out of memory. Notify system adminstrator.\n";
                        break;
                    case XmlException.INTERNAL_ERROR:
                        error = "Internal error. Notify system adminstrator.\n";
                        break;
                    case XmlException.INDEXER_PARSER_ERROR:
                        error = "Cannot parse the given template. Is the template a valid XML file?";
                        break;
                    case XmlException.UNIQUE_ERROR:
                        error = "Given template document(s) already exist";
                        break;
                    default:
                        error = "Error adding template file(s) [" + ex.getErrorCode() + "]";
                    }
                }
            } catch (Exception e) {
                log.error("(UR-155) Error while uploading file.", e);
                returnString = "Error (UR-170): " + e.getMessage();
            } finally {
                try {
                    MetaDataUtil.closeXmlContainer(container);
                    MetaDataUtil.closeXmlManager(manager);
                    cleanup();
                    log.debug("Upload complete.");
                } catch (DatabaseException e) {
                    log.error("(UR-168) Cleanup failed.", e);
                }
            }
        }
        
        // Delete local copies of files
        for (File f : uploaded) {
            try {
                f.delete();
            } catch (Exception e) {
                log.error("Failed to delete uploaded file.", e);
            }
        }
       
        return this.createRepresentation(returnString, error);
    }
    
    /**
     * Creates representation with upload results
     * @param uploadResults - info about uploaded files, errors, etc. that will be sent to all clients
     * @param webError - web client-specific error. Can be null.
     * @return representation of the upload results
     */
    private Representation createRepresentation(String uploadResults, String webError) {

        if (this.isRequestByAtb()) {
            // ATB is expecting a string here
            return new StringRepresentation(uploadResults);
        } else {
            final Map<String, Object> pageData = new HashMap<String, Object>();

            final String loginHtml = ATSLoginUtil.getInstance().checkForLoginCookie(this.getRequest());
            // This could happen if we come to the upload page through a bookmark.
            if (loginHtml == null) {
                if (this.getRequest().getMethod() == Method.POST) // POST should check for login before upload
                    log.error("UR-285", new Throwable("Abnormal State: no login information is present after upload"));
                return FreemarkerTemplateResource.displayLoginPage();
            }
            pageData.put("loginHtml", loginHtml == null ? "" : loginHtml);

            // Show detailed error on the web
            pageData.put("outputMessage", webError == null ? (uploadResults == null ? "" : uploadResults) : webError);

            return FreemarkerTemplateResource.displayUploadPage(pageData, this.getRequest());
        }
    }

    private void addMetaData(XmlDocument doc, String fileName) {
        try {
            // add owner to file.
            doc.setMetaData(MetaDataUtil.METADATA_URI, MetaDataUtil.OWNER, new XmlValue(MetaDataUtil.getOwnerFromRequest(this.getRequest())));
            doc.setMetaData(MetaDataUtil.METADATA_URI, MetaDataUtil.DATE_PUBLISHED, new XmlValue("" + System.currentTimeMillis()));
            doc.setMetaData(MetaDataUtil.METADATA_URI, MetaDataUtil.PERMISSION, new XmlValue(MetaDataUtil.PERM_PUBLIC));
            doc.setMetaData(MetaDataUtil.METADATA_URI, MetaDataUtil.DOC_FILE_NAME, new XmlValue(fileName));

            log.debug("Added meta-data: owner=" + MetaDataUtil.getOwnerFromRequest(this.getRequest()));
        } catch (Exception e) {
            log.error("Failed to add meta-data", e);
        }
    }

    /**
     * Pull out just the file-name from the path.
     * 
     * @param fi
     * @return String just file-name.
     */
    private String getFileNameAtEndOfPath(FileItem fi) {

        String name = fi.getName();
        log.debug("FileItem name: " + name);

        String retVal = name;

        int lastSlash = name.lastIndexOf("\\");
        if (lastSlash > 0) {
            retVal = name.substring(lastSlash);
            log.debug("getFileNameAtEndOfPath=" + retVal);
        }

        return retVal;
    }
}
