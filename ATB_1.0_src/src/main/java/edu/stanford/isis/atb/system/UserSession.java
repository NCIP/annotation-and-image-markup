/*
 * Copyright Notice. Copyright 2011 Northwestern University and Stanford
 * University (“caBIG® Participant”). AIM Template Enterprise Service conforms
 * to caBIG® technical specifications and is part of the caBIG® initiative. The
 * software subject to this notice and license includes human readable source
 * code form, machine readable, binary, object code form and related
 * documentation (the “caBIG® Software”).
 *
 * This caBIG® Software License (the “License”) is between the National Cancer
 * Institute (NCI) and You. “You (or “Your”) shall mean a person or an entity,
 * and all other entities that control, are controlled by, or are under common
 * control with the entity. “Control” for purposes of this definition means (i)
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
 * Your redistributions of the source code for the caBIG® Software must retain
 * the above copyright notice, this list of conditions and the disclaimer and
 * limitation of liability of Article 6 below. Your redistributions in object
 * code form must reproduce the above copyright notice, this list of conditions
 * and the disclaimer of Article 6 in the documentation and/or other materials
 * provided with the distribution, if any.
 *
 * Your end-user documentation included with the redistribution, if any, must
 * include the following acknowledgment: “This product includes software
 * developed by Danny Korenblum, Alan Snyder, Vitaliy Semeshko, Vladimir Kleper
 * and Pattanasak Mongkolwat, Northwestern University and Stanford University.”
 * If You do not include such end-user documentation, You shall include this
 * acknowledgment in the caBIG® Software itself, wherever such third-party
 * acknowledgments normally appear.
 *
 * You may not use the names “Northwestern University”, “Stanford University”,
 * “The National Cancer Institute”, “NCI”, “Cancer Bioinformatics Grid” or
 * “caBIG®” to endorse or promote products derived from this caBIG® Software.
 * This License does not authorize You to use any trademarks, service marks,
 * trade names, logos or product names of either caBIG® Participant, NCI or
 * caBIG®, except as required to comply with the terms of this License.
 *
 * For sake of clarity, and not by way of limitation, You are not prohibited by
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
 * For sake of clarity, and not by way of limitation, You may add Your own
 * copyright statement to Your modifications and to the derivative works, and
 * You may provide additional or different license terms and conditions in
 * Your sublicenses of modifications of the caBIG® Software, or any derivative
 * works of the caBIG® Software as a whole, provided Your use, reproduction,
 * and distribution of the Work otherwise complies with the conditions stated
 * in this License.
 *
 * THIS caBIG® SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESSED OR IMPLIED
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

package edu.stanford.isis.atb.system;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.LinkedHashSet;
import java.util.List;
import java.util.Properties;
import java.util.Set;

import org.apache.commons.io.IOUtils;
import org.apache.commons.lang3.StringUtils;

import edu.stanford.isis.atb.system.config.PropertyManager;
import edu.stanford.isis.atb.system.exception.ATBException;
import edu.stanford.isis.atb.system.resources.ResourceManager;
import edu.stanford.isis.atb.ui.Const;

/**
 * @author Vitaliy Semeshko
 */
public class UserSession {

	public static final String SESSION_DIR = "etc/session";
	private static final String SESSION_FILE = "%s.session";
	
	private static final int LOCAL_LEXICON_SEARCH_HISTORY_MAX_SIZE = 15;
	
	private static final String ANONYMOUS = "anonymous";
	private static final String ATS_USER_NAME = "userName";
	private static final String ATS_SESSION_ID = "atsSessionId";
	private static final String LOCAL_LEXICON_SEARCH_HISTORY = "localLexiconSearchHistory";
	private static final String TEMPLATE_IMPORT_EXPORT_PATH = "templateImportExportPath";
	private static final String LEXICON_IMPORT_EXPORT_PATH = "lexiconImportExportPath";
	
	private static final String COLLECTION_ELEMENT_SEPARATOR = "<PRPRT_SPRTR>";
	
	private static final UserSession instance = new UserSession();
	
	private ResourceManager resourceManager = ResourceManager.getInstance();
	
	private Properties properties = new Properties();
	
	private UserSession() {
		String userName = getUserName();
		
		String sessionResourceFile = String.format(SESSION_FILE, userName);
		String sessionResourceName = SESSION_DIR + Const.R_SEP + sessionResourceFile;
		
		if (resourceManager.isExists(sessionResourceName)) {
			try {
				InputStream inputStrem = resourceManager.getResourceAsStream(sessionResourceName); 
				try {
					properties.load(inputStrem);
				} finally {
					IOUtils.closeQuietly(inputStrem);
				}
			} catch (IOException e) {
				throw new ATBException("Could not load session information: " + sessionResourceFile, e);
			}
		} else {
			properties.setProperty(ATS_USER_NAME, userName);
			save();
		}
	}
	
	public static UserSession getInstance() {
		return instance;
	}
	
	public String getATSUserName() {
		return properties.getProperty(ATS_USER_NAME);
	}
	
	public String getATSSessionId() {
		return properties.getProperty(ATS_SESSION_ID);
	}
	
	public void setATSSessionId(String sessionId) {
		properties.setProperty(ATS_SESSION_ID, sessionId);
		save();
	}
	
	public String getTemplateImportExportPath() {
		return properties.getProperty(TEMPLATE_IMPORT_EXPORT_PATH);
	}
	
	public void setTemplateImportExportPath(String path) {
		properties.setProperty(TEMPLATE_IMPORT_EXPORT_PATH, path);
		save();
	}
	
	public String getLexiconImportExportPath() {
		return properties.getProperty(LEXICON_IMPORT_EXPORT_PATH);
	}
	
	public void setLexiconImportExportPath(String path) {
		properties.setProperty(LEXICON_IMPORT_EXPORT_PATH, path);
		save();
	}
	
	public void addLocalSearchHistoryText(String text) {
		List<String> currentHistory = new ArrayList<String>(getList(LOCAL_LEXICON_SEARCH_HISTORY));
		
		// add to the start
		currentHistory.add(0, text);

		// need to store only unique values in the same order
		Set<String> historyUnique = new LinkedHashSet<String>(currentHistory);
		
		List<String> history = new ArrayList<String>();
		for (String s : historyUnique) {
			if (history.size() < LOCAL_LEXICON_SEARCH_HISTORY_MAX_SIZE) {
				history.add(s);
			} else {
				break;
			}
		}
		
		setList(LOCAL_LEXICON_SEARCH_HISTORY, history);
	}
	
	public List<String> getLocalSearchHistory() {
		return getList(LOCAL_LEXICON_SEARCH_HISTORY);
	}
	
	private String getUserName() {
		String userName = PropertyManager.getInstance().get(PropertyManager.CA_GRID_USER_NAME);
		
		if (StringUtils.isEmpty(userName)) {
			userName = ANONYMOUS;
		}
		
		return userName;
	}
	
	private void save() {
		String sessionResourceFile = String.format(SESSION_FILE, getUserName());
		String path = resourceManager.getAbsoluteResourcePath(SESSION_DIR) + File.separator + sessionResourceFile;
		try {
			properties.store(new FileOutputStream(path), Const.EMPTY);
		} catch (Exception e) {
			throw new ATBException("Could not create session information file: " + sessionResourceFile, e);
		}
	}
	
	private List<String> getList(String key) {
		String value = properties.getProperty(key);
		if (value == null) {
			return Collections.emptyList();
		}
		String[] result = value.split(COLLECTION_ELEMENT_SEPARATOR);
		return Arrays.asList(result);
	}
	
	private void setList(String key, List<String> values) {
		StringBuffer value = new StringBuffer();
		
		for (String s : values) {
			value.append(s).append(COLLECTION_ELEMENT_SEPARATOR);
		}
		
		properties.setProperty(key, value.toString());
		save();
	}

}
