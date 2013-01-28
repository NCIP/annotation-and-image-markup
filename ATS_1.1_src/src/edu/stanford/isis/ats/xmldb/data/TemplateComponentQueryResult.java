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

package edu.stanford.isis.ats.xmldb.data;

import java.util.Arrays;
import java.util.Date;
import java.util.List;

import com.sleepycat.dbxml.XmlDocument;
import com.sleepycat.dbxml.XmlException;
import com.sleepycat.dbxml.XmlValue;

import edu.stanford.isis.ats.utils.ATSLogger;
import edu.stanford.isis.ats.utils.ATSStringUtils;
import edu.stanford.isis.ats.xmldb.MetaDataUtil;

/**
 * @author Vladimir Kleper
 */
public class TemplateComponentQueryResult {

    private String fileName;
    private String templateOwner;
    private List<String> allowedUsers;
    private TemplatePermissionType permissionType;
    private Date publishDate;
    private String templateComponent; // String representation of a template document
    
    public String getFileName() {
        return fileName;
    }
    
    public void setFileName(String fileName) {
        this.fileName = fileName;
    }
    
    public String getTemplateOwner() {
        return templateOwner;
    }
    
    public void setTemplateOwner(String templateOwner) {
        this.templateOwner = templateOwner;
    }

    public List<String> getAllowedUsers() {
        return allowedUsers;
    }

    public void setAllowedUsers(List<String> allowedUsers) {
        this.allowedUsers = allowedUsers;
    }

    public TemplatePermissionType getPermissionType() {
        return permissionType;
    }

    public void setPermissionType(TemplatePermissionType permissionType) {
        this.permissionType = permissionType;
    }

    public Date getPublishDate() {
        return publishDate;
    }

    public void setPublishDate(Date publishDate) {
        this.publishDate = publishDate;
    }

    public String getTemplateComponent() {
        return templateComponent;
    }

    public void setTemplateComponent(String templateComponent) {
        this.templateComponent = templateComponent;
    }
    
    /**
     * Parses result of a query into the data object
     */
    public static QueryResultAdapter<TemplateComponentQueryResult> templateComponentQueryResultAdapter = new QueryResultAdapter<TemplateComponentQueryResult>() {
        protected final ATSLogger log = ATSLogger.getLogger();
        
        @Override
        public TemplateComponentQueryResult adaptResult(XmlValue value) {
            try {
                final TemplateComponentQueryResult queryResult = new TemplateComponentQueryResult();
                final XmlDocument xmlDocument = value.asDocument();
                // 1. Get available metadata
                //queryResult.setFileName(MetaDataUtil.getDocName(xmlDocument));
                queryResult.setFileName(MetaDataUtil.getMetaData(MetaDataUtil.DOC_FILE_NAME, xmlDocument));
                queryResult.setTemplateOwner(MetaDataUtil.getMetaData(MetaDataUtil.OWNER, xmlDocument));
                try {
                    final String permission = MetaDataUtil.getMetaData(MetaDataUtil.PERMISSION, xmlDocument);
                    TemplatePermissionType permissionType = TemplatePermissionType.valueOf(ATSStringUtils.toTitleCase(permission.toLowerCase()));
                    queryResult.setPermissionType(permissionType);
                } catch (IllegalArgumentException  ex) {
                    log.error("(TQQR-92): Failed to recognize stored template permission. Will use default value.", ex);
                    queryResult.setPermissionType(TemplatePermissionType.Public);
                }
                try {
                    long millis = Long.parseLong(MetaDataUtil.getMetaData(MetaDataUtil.DATE_PUBLISHED, xmlDocument));
                    //final Date publishDate = DateFormat.getDateInstance().parse(MetaDataUtil.getMetaData(MetaDataUtil.DATE_PUBLISHED, xmlDocument));
                    final Date publishDate = new Date(millis);
                    queryResult.setPublishDate(publishDate);
                } catch (NumberFormatException e) {
                    log.error("(TQQR-100): Failed to parse document date", e);
                }
                final List<String> allowedUsers = Arrays.asList(MetaDataUtil.getMetaData(MetaDataUtil.ALLOWED_USER, xmlDocument).split(","));
                queryResult.setAllowedUsers(allowedUsers);
                // 2. Get the document
                queryResult.setTemplateComponent(xmlDocument.getContentAsString());
                
                return queryResult;
            } catch(XmlException ex) {
                log.error("(TQQR-120: Failed to parse query result into a Template Container", ex);
            }
            return null;
        }
    };
}
