/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.service.impl;

import java.io.File;
import java.io.InputStream;

import org.apache.commons.io.IOUtils;
import org.apache.commons.io.output.ByteArrayOutputStream;
import org.apache.commons.lang3.StringUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import edu.stanford.isis.atb.dao.ats.ATSDao;
import edu.stanford.isis.atb.dao.template.impl.TemplateDaoImpl;
import edu.stanford.isis.atb.domain.ats.ContainerResults;
import edu.stanford.isis.atb.domain.ats.ContainerSearchRequest;
import edu.stanford.isis.atb.domain.ats.TemplateResults;
import edu.stanford.isis.atb.domain.ats.TemplateSearchRequest;
import edu.stanford.isis.atb.domain.template.TemplateContainer;
import edu.stanford.isis.atb.domain.template.TemplateRef;
import edu.stanford.isis.atb.service.Callback;
import edu.stanford.isis.atb.service.Command;
import edu.stanford.isis.atb.service.TemplateSearchService;
import edu.stanford.isis.atb.system.UserSession;
import edu.stanford.isis.atb.system.exception.ATBException;
import edu.stanford.isis.atb.system.exception.ATSException;
import edu.stanford.isis.atb.system.exception.ATSLoginException;
import edu.stanford.isis.atb.system.resources.FileBackedByteArrayResource;

/**
 * @author Vitaliy Semeshko
 */

@Service
public class TemplateSearchServiceImpl extends AbstractService implements TemplateSearchService {

	@Autowired
	private ATSDao atsDao;
	
	@Autowired
	private TemplateDaoImpl templateDao;
	
	@Override
	public void searchTemplates(final TemplateSearchRequest request, final Callback<TemplateResults> callback) {
		executeAsynchronously(new Command() {
			@Override
			public void execute() {
				try {
					TemplateResults result = atsDao.searchTemplates(request);
					callback.onSuccess(result);
				} catch (ATBException e) {
					callback.onFailure(e);					
				} catch (Exception e) {
					callback.onFailure(new ATSException(e));					
				}
			}
		});
	}
	
	@Override
	public void importTemplate(final String uid, final Callback<TemplateRef> callback) {
		executeAsynchronously(new Command() {
			@Override
			public void execute() {
				try {
					InputStream input = atsDao.download(uid);
					try {
						TemplateRef result = templateDao.importTemplate(input);
						callback.onSuccess(result);
					} finally {
						IOUtils.closeQuietly(input);
					}
				} catch (ATBException e) {
					callback.onFailure(e);
				}				
			}
		});
	}

	@Override
	public void searchContainers(final ContainerSearchRequest request, final Callback<ContainerResults> callback) {
		executeAsynchronously(new Command() {
			@Override
			public void execute() {
				try {
					ContainerResults result = atsDao.searchContainers(request);
					callback.onSuccess(result);
				} catch (ATBException e) {
					callback.onFailure(e);
				} catch (Exception e) {
					//callback.onFailure(new ATSException(e));
					callback.onFailure(new ATSException("Search Terms Not Found!"));
				}
			}
		});
	}

	@Override
	public void importContainer(final String uid, final Callback<TemplateContainer> callback) {
		executeAsynchronously(new Command() {
			@Override
			public void execute() {
				try {
					InputStream input = atsDao.download(uid);
					try {
						TemplateContainer result = templateDao.importContainer(input);
						callback.onSuccess(result);
					} finally {
						IOUtils.closeQuietly(input);
					}
				} catch (ATBException e) {
					callback.onFailure(e);
				}				
			}
		});
	}

	@Override
	public void login(final String userName, final String password, final Callback<Void> callback) {
		executeAsynchronously(new Command() {
			@Override
			public void execute() {
				String sessionId = null;
				try {
					sessionId = atsDao.loginAndReturnSessionId(userName, password);
				} catch (Exception e) {
					callback.onFailure(new ATBException(e));
					return;
				}

				// if no session ID then login was not successful
				if (StringUtils.isEmpty(sessionId)) {
					callback.onFailure(new ATSLoginException("Couldn't start session for user: " + userName));
					return;
				}
				
				// store session ID for future requests
				UserSession.getInstance().setATSSessionId(sessionId);
				
				callback.onSuccess(null);
			}
		});
	}

	@Override
	public void publishContainer(final TemplateContainer container, final Callback<Void> callback) {
		executeAsynchronously(new Command() {
			@Override
			public void execute() {
				try {
					// export container to byte array
					ByteArrayOutputStream outBytes = new ByteArrayOutputStream();
					templateDao.validateAndExportContainer(container, outBytes);
					
					// use named byte array resource for uploading
					//File file = new File(container.getFileName());
					File file = new File(container.getPublishedFileName());
					FileBackedByteArrayResource resource = new FileBackedByteArrayResource(outBytes.toByteArray(), file); 
					atsDao.uploadContainer(resource);
					callback.onSuccess(null);
				} catch (ATSException e) {
					// VK: added this catch to prevent double-wrapped exceptions
					callback.onFailure(e);
					return;
				} catch (Exception e) {
					callback.onFailure(new ATBException(e));
					return;
				}
			}
		});
	}
	
}
