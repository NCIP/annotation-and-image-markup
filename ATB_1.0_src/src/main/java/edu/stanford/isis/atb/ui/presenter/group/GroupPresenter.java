/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
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
					view.showError(getErrorInformation(caught));
				}
			}
		});
	}
	
	private void showLoginDialog() {
		final String atsUsername = UserSession.getInstance().getATSUserName();
		final LoginDialog login = new LoginDialog();
		
		login.setLoginListener(new LoginListener() {
			@Override
			public void onLogin(String userName, String password) {
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
							login.showDialog(atsUsername);
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
