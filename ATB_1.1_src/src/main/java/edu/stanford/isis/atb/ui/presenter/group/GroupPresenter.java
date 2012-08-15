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

package edu.stanford.isis.atb.ui.presenter.group;

import static edu.stanford.isis.atb.ui.Const.MSG_CONTAINER_COPIED;
import static edu.stanford.isis.atb.ui.Const.MSG_CONTAINER_EXPORTED;
import static edu.stanford.isis.atb.ui.Const.MSG_CONTAINER_EXPORT_FAILED;
import static edu.stanford.isis.atb.ui.Const.MSG_CONTAINER_IMPORTED;
import static edu.stanford.isis.atb.ui.Const.MSG_CONTAINER_IS_EMPTY;
import static edu.stanford.isis.atb.ui.Const.MSG_CONTAINER_IS_INCORRECT;
import static edu.stanford.isis.atb.ui.Const.MSG_NO_CONTAINER_SELECTED;
import static edu.stanford.isis.atb.ui.view.group.GroupView.GroupAction.COPY_GROUP;
import static edu.stanford.isis.atb.ui.view.group.GroupView.GroupAction.CREATE_GROUP;
import static edu.stanford.isis.atb.ui.view.group.GroupView.GroupAction.DELETE_GROUP;
import static edu.stanford.isis.atb.ui.view.group.GroupView.GroupAction.EDIT_GROUP;
import static edu.stanford.isis.atb.ui.view.group.GroupView.GroupAction.EXPORT;
import static edu.stanford.isis.atb.ui.view.group.GroupView.GroupAction.IMPORT;
import static edu.stanford.isis.atb.ui.view.group.GroupView.GroupAction.PUBLISH;
import static edu.stanford.isis.atb.ui.view.group.GroupView.GroupAction.SEARCH;

import java.io.File;

import javax.swing.JFileChooser;
import javax.swing.filechooser.FileNameExtensionFilter;

import org.apache.commons.collections.CollectionUtils;
import org.apache.commons.lang3.StringUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import edu.stanford.isis.atb.domain.template.Identifier;
import edu.stanford.isis.atb.domain.template.TemplateContainer;
import edu.stanford.isis.atb.domain.template.TemplateRef;
import edu.stanford.isis.atb.service.CallbackAdapter;
import edu.stanford.isis.atb.service.Command;
import edu.stanford.isis.atb.service.TemplateSearchService;
import edu.stanford.isis.atb.service.TemplateService;
import edu.stanford.isis.atb.system.UserSession;
import edu.stanford.isis.atb.system.exception.ATBException;
import edu.stanford.isis.atb.system.exception.ATSLoginException;
import edu.stanford.isis.atb.ui.Const;
import edu.stanford.isis.atb.ui.action.EventBus;
import edu.stanford.isis.atb.ui.presenter.AbstractEventBusAwarePresenter;
import edu.stanford.isis.atb.ui.presenter.form.AbstractFormPresenter.FormCloseListener;
import edu.stanford.isis.atb.ui.presenter.form.AbstractFormPresenter.FormSubmitListener;
import edu.stanford.isis.atb.ui.presenter.form.FormManager;
import edu.stanford.isis.atb.ui.presenter.template.form.GroupFormPresenter;
import edu.stanford.isis.atb.ui.view.group.GroupView;
import edu.stanford.isis.atb.ui.view.group.GroupView.ContainerSelectionListener;
import edu.stanford.isis.atb.ui.view.widget.LoginDialog;
import edu.stanford.isis.atb.ui.view.widget.LoginDialog.LoginListener;

/**
 * Group Presenter.
 * 
 * @author Vitaliy Semeshko
 */
public class GroupPresenter extends AbstractEventBusAwarePresenter<GroupView, EventBus> 
implements ContainerSelectionListener {

	private static final Logger logger = LoggerFactory.getLogger(GroupPresenter.class);
	
	private TemplateService templateService;

	private TemplateSearchService searchService;
	
	private TemplateContainer activeContainer;
	
	private GroupSearchPresenter searchPresenter;
	
	private FormManager formManager = new FormManager();
	
	private UserSession session = UserSession.getInstance();
	
	private FormCloseListener formCloseListener = new FormCloseListener() {
		@Override
		public void onFormClose() {
			view.hideEditForm();
		}
	};
	
	private FormSubmitListener<TemplateContainer> formSubmitListener = new FormSubmitListener<TemplateContainer>() {
		@Override
		public void onFormSubmit(TemplateContainer value, boolean isCreation) {
			templateService.saveContainer(value);
			value.setInitialized(true);
			view.hideEditForm();
			refreshView(value);
		}
	};
	
	public GroupPresenter(GroupView view, EventBus eventBus, TemplateService templateService) {
		super(view, eventBus);
		this.templateService = templateService;
	}

	public void setSearchService(TemplateSearchService searchService) {
		this.searchService = searchService;
	}
	
	public void setSearchPresenter(GroupSearchPresenter searchPresenter) {
		this.searchPresenter = searchPresenter;
	}

	@Override
	public void bindView() {
		initializeData();

		// bind commands
		view.setLinkTemplatesWithContainerCommand(new Command() {
			@Override 
			public void execute() {
				if (activeContainer == null) {
					view.showInformation(Const.MSG_NO_CONTAINER_SELECTED);
					return;
				}

				// clear templates
				activeContainer.clearTemplates();

				// add new
				for (TemplateRef template : view.getMarkedTemplatesForLinking()) {
					activeContainer.addTemplate(template);
				}

				// save
				templateService.saveContainer(activeContainer);

				// refresh view
				refreshView(null);
			}
		});

		view.setCommand(CREATE_GROUP, new Command() {
			@Override 
			public void execute() {
				// clear container details and unmark memberships
				view.clearContainerDetails(true);
				
				TemplateContainer newContainer = new TemplateContainer();
				newContainer.setUid(Identifier.generate());
				newContainer.setInitialized(false);
				
				// show form
				showGroupForm(newContainer, true);
			}
		});

		view.setCommand(EDIT_GROUP, new Command() {
			@Override 
			public void execute() {
				if (activeContainer != null) {
					showGroupForm(activeContainer, false);
				} else {
					view.showInformation(Const.MSG_NO_CONTAINER_SELECTED);
				}
			}
		});

		view.setCommand(DELETE_GROUP, new Command() {
			@Override 
			public void execute() {
				view.hideEditForm();
				if (activeContainer != null) {
					if (view.confirm(Const.QST_DELETE_GROUP)) {
						templateService.deleteContainer(activeContainer);
						activeContainer = null;
						refreshView(null);
					}
				} else {
					view.showInformation(Const.MSG_NO_CONTAINER_SELECTED);
				}
			}
		});

		view.setCommand(COPY_GROUP, new Command() {
			@Override 
			public void execute() {
				view.hideEditForm();
				if (activeContainer != null) {
					TemplateContainer copy = templateService.copyContainer(activeContainer);
					eventBus.onContainerImported(copy);
					view.showInformation(String.format(MSG_CONTAINER_COPIED, copy.getName()));
				} else {
					view.showInformation(Const.MSG_NO_CONTAINER_SELECTED);
				}
			}
		});
		
		view.setCommand(IMPORT, new Command() {
			@Override
			public void execute() {
				JFileChooser c = createFileChoser();
				int rVal = c.showOpenDialog(view.asComponent());
				if (rVal == JFileChooser.APPROVE_OPTION) {
					templateService.importContainer(c.getSelectedFile(), new CallbackAdapter<TemplateContainer>() {
						@Override 
						public void onSuccess(TemplateContainer result) {
							eventBus.onContainerImported(result);
							view.showInformation(String.format(MSG_CONTAINER_IMPORTED, result.getName()));
						}
						@Override
						public void onFailure(ATBException caught) {
							view.showError(getErrorInformation(Const.MSG_INVALID_TEMPLATE, caught));
						}
					});
					// save import path
					session.setTemplateImportExportPath(c.getSelectedFile().getParent());
				}
			}
		});

		view.setCommand(EXPORT, new Command() {
			@Override
			public void execute() {
				if (activeContainer != null) {
					
					if (!validateCurrentContainer()) {
						return;
					}
					
					final JFileChooser c = createFileChoser();
					int rVal = c.showSaveDialog(view.asComponent());
					if (rVal == JFileChooser.APPROVE_OPTION) {
						if (!c.getSelectedFile().getPath().toLowerCase().endsWith("." + Const.EXT_XML)) {
						    c.setSelectedFile(new File(c.getSelectedFile().getPath() + "." + Const.EXT_XML));
						}
						templateService.exportContainer(activeContainer, c.getSelectedFile(), new CallbackAdapter<Void>() {
							@Override
							public void onSuccess(Void result) {
								view.showInformation(String.format(MSG_CONTAINER_EXPORTED, activeContainer.getName()));
							}
							@Override
							public void onFailure(ATBException caught) {
								String msg = String.format(MSG_CONTAINER_EXPORT_FAILED, activeContainer.getName());
								view.showError(getErrorInformation(msg, caught));
							}
						});
						// save export path
						session.setTemplateImportExportPath(c.getSelectedFile().getParent());
					}
				} else {
					view.showInformation(MSG_NO_CONTAINER_SELECTED);
				}
			}
		});

		view.setCommand(SEARCH, new Command() {
			@Override
			public void execute() {
				searchPresenter.startSearch();
			}
		});

		view.setCommand(PUBLISH, new Command() {
			@Override
			public void execute() {
				if (activeContainer != null) {
					
					if (!validateCurrentContainer()) {
						return;
					}
					
					if (StringUtils.isEmpty(UserSession.getInstance().getATSSessionId())) {
						showLoginDialog();
					} else {
						publish();
					}
				} else {
					view.showInformation(MSG_NO_CONTAINER_SELECTED);
				}
			}
		});

		view.addContainerSelectionListener(this);
	}

	private JFileChooser createFileChoser() {
		JFileChooser c = new JFileChooser();
		c.setFileFilter(new FileNameExtensionFilter(Const.EXT_XML_TEXT, Const.EXT_XML));
		c.setAcceptAllFileFilterUsed(false);
		
		String path = session.getTemplateImportExportPath();
		if (StringUtils.isNotEmpty(path)) {
			File dir = new File(path);
			if (dir.isDirectory()) {
				c.setCurrentDirectory(dir);
			}
		}
		return c;
	}
	
	private boolean validateCurrentContainer() {
		// don't export empty container
		if (CollectionUtils.isEmpty(activeContainer.getTemplates())) {
			view.showInformation(MSG_CONTAINER_IS_EMPTY);
			return false;
		}
		
		// don't export incorrect container
		if (!activeContainer.isValid()) {
			view.showInformation(MSG_CONTAINER_IS_INCORRECT);
			return false;
		}
		
		return true;
	}
	
	private void publish() {
		if (activeContainer == null) {
			view.showInformation(MSG_NO_CONTAINER_SELECTED);
			return;
		}
		
		if (!view.showTemplateNamePrompt(activeContainer))
			return;
		
		searchService.publishContainer(activeContainer, new CallbackAdapter<Void>() {
			@Override
			public void onSuccess(Void result) {
				view.showInformation(String.format(Const.MSG_CONTAINER_PUBLISHED, activeContainer.getName()));
			}

			@Override
			protected void onFailure(ATBException caught) {
				if (caught instanceof ATSLoginException) {
					showLoginDialog();
				} else {
					// VK: write actual error to the log. Show only the error for duplicate templates.
					logger.error("Template Publishing Error", caught);
					final String ERROR_MARKER_DUPS = "Error - internal database (UR-167): Error: Document exists: ";
					final String ERROR_MARKER_DUPS_START = "Error - internal database (UR-167): Error: ";
					int i = caught.getMessage().indexOf(ERROR_MARKER_DUPS, 0);
					if (i >= 0)
						view.showError(caught.getMessage().substring(i + ERROR_MARKER_DUPS_START.length()));
					else
						view.showError("Failed to publish your template. See log for details.");
//					view.showError(getErrorInformation(caught));
				}
			}
		});
	}
	
	private void showLoginDialog() {
		final String atsUsername = UserSession.getInstance().getATSUserName();
		final LoginDialog login = new LoginDialog();
		
		login.setLoginListener(new LoginListener() {
			@Override
			public void onLogin(final String userName, String password) {
				searchService.login(userName, password, new CallbackAdapter<Void>() {
					@Override
					public void onSuccess(Void result) {
						login.hideDialog();
						publish();
					}

					@Override
					protected void onFailure(ATBException caught) {
						if (caught instanceof ATSLoginException) {
							login.authenticationFailed();
							login.showDialog(userName);
						} else {
							view.showError(getErrorInformation(caught));
						}
					}
				});
			}
		});
		
		login.showDialog(atsUsername);
	}
	
	private void showGroupForm(TemplateContainer container, boolean isCreation) {
		GroupFormPresenter p = formManager.groupForm(formCloseListener, formSubmitListener);
		p.setValue(container);
		view.showEditForm(p.prepareForm(isCreation));
	}

	private void initializeData() {
		view.setContainers(templateService.getContainers());
		view.setTemplates(templateService.getTemplates());
	}

	@Override
	public void onContainerSelected(TemplateContainer container) {
		activeContainer = container;
		view.setActiveContainer(container, true);
		view.hideEditForm();
	}

	/**
	 * Refresh view and after select provided element.
	 * 
	 * @param container container to be selected after refresh. If <code>null</code> then currently selected element
	 * will be re-selected. If no currently selected element, nothing will be selected.
	 */
	public void refreshView(TemplateContainer container) {
		TemplateContainer target = container != null ? container : activeContainer;

		view.setContainers(templateService.getContainers());
		view.setTemplates(templateService.getTemplates());

		if (target != null) {
			view.setActiveContainer(target, true);
		} else {
			// clear containers details without unmarking memberships (data has been already replaced)
			view.clearContainerDetails(false);
		}
	}
}
