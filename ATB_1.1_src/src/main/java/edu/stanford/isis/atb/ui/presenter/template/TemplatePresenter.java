/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.presenter.template;

import static edu.stanford.isis.atb.ui.Const.MSG_NO_TEMPLATE_SELECTED;
import static edu.stanford.isis.atb.ui.Const.MSG_TEMPLATE_COPIED;
import static edu.stanford.isis.atb.ui.Const.QST_DELETE_TEMPLATE;

import java.util.ArrayList;
import java.util.Collection;
import java.util.concurrent.Executor;

import org.springframework.core.task.SimpleAsyncTaskExecutor;

import edu.stanford.isis.atb.domain.template.Identifier;
import edu.stanford.isis.atb.domain.template.Template;
import edu.stanford.isis.atb.domain.template.TemplateRef;
import edu.stanford.isis.atb.service.Command;
import edu.stanford.isis.atb.service.TemplateService;
import edu.stanford.isis.atb.system.validation.TemplateValidator;
import edu.stanford.isis.atb.ui.action.EventBus;
import edu.stanford.isis.atb.ui.presenter.AbstractEventBusAwarePresenter;
import edu.stanford.isis.atb.ui.presenter.template.TemplateEditorPresenter.TemplateChangeListener;
import edu.stanford.isis.atb.ui.view.template.TemplateView;
import edu.stanford.isis.atb.ui.view.template.TemplateView.TemplateEditAction;
import edu.stanford.isis.atb.ui.view.template.TemplateView.TemplateSelectionListener;

/**
 * Template Presenter.
 * 
 * @author Vitaliy Semeshko
 */
public class TemplatePresenter extends AbstractEventBusAwarePresenter<TemplateView, EventBus> {

	private TemplateRef activeTemplateRef;
	
	private TemplateService templateService;

	private TemplateEditorPresenter editorPresenter;
	
	private TemplateSearchPresenter searchPresenter;

	public TemplatePresenter(TemplateView view, EventBus eventBus) {
		super(view, eventBus);
	}

	public void setTemplateService(TemplateService templateService) {
		this.templateService = templateService;		
	}

	public void setSearchPresenter(TemplateSearchPresenter searchPresenter) {
		this.searchPresenter = searchPresenter;
	}

	public void setEditorPresenter(TemplateEditorPresenter editorPresenter) {
		this.editorPresenter = editorPresenter;
		
		editorPresenter.addTemplateChangeListener(new TemplateChangeListener() {
			@Override
			public void onTemplateChanged(final Template template, boolean isAttributeOnlyChanged) {
				templateService.saveTemplate(template);
				
				// refresh view if attributes changed
				if (isAttributeOnlyChanged) {
					refreshView(template);
					eventBus.onTemplateChanged(template);
				}
				
				final TemplateRef ref = templateService.getTemplateRef(template.getUid());
				validateTemplates(new ArrayList<TemplateRef>() {{add(ref);}});
			}
		});
	}
	
	@Override
	public void bindView() {
		loadData();

		// bind commands
		view.setCommand(TemplateEditAction.CREATE_TEMPLATE, new Command() {
			@Override 
			public void execute() {
				editorPresenter.clear();
				view.clearSelection();
				Template newTemplate = new Template();
				newTemplate.setUid(Identifier.generate());
				newTemplate.setInitialized(false);
				editorPresenter.showTemplateForm(newTemplate, true);
			}
		});

		view.setCommand(TemplateEditAction.DELETE_TEMPLATE, new Command() {
			@Override 
			public void execute() {
				if (activeTemplateRef != null) {
					if (view.confirm(QST_DELETE_TEMPLATE)) {
						templateService.deleteTemplate(activeTemplateRef);
						activeTemplateRef = null;
						refreshView(null);
						eventBus.onTemplateDeleted(activeTemplateRef);
					}
				} else {
					view.showInformation(MSG_NO_TEMPLATE_SELECTED);
				}
			}
		});

		view.setCommand(TemplateEditAction.COPY_TEMPLATE, new Command() {
			@Override 
			public void execute() {
				if (activeTemplateRef != null) {
					TemplateRef copy = templateService.copyTemplate(activeTemplateRef);
					eventBus.onTemplateImported(copy);
					view.showInformation(String.format(MSG_TEMPLATE_COPIED, copy.getName()));
				} else {
					view.showInformation(MSG_NO_TEMPLATE_SELECTED);
				}
			}
		});

		view.setCommand(TemplateEditAction.SEARCH_TEMPLATE, new Command() {
			@Override 
			public void execute() {
				searchPresenter.startSearch();
			}
		});

		view.addTemplateSelectionListeners(new TemplateSelectionListener() {
			@Override
			public void onTemplateSelected(TemplateRef template) {
				activeTemplateRef = template;		
				editorPresenter.setActiveTemplate(templateService.getTemplate(template));
			}
		});
	}

	private void loadData() {
		final Collection<TemplateRef> refs = templateService.getTemplates(); 
		view.setTemplates(refs);
		validateTemplates(refs);
	}

	/**
	 * Refresh view and after select provided element.
	 * 
	 * @param template template to be selected after refresh. If <code>null</code> then currently selected element
	 * will be re-selected. If no currently selected element, nothing will be selected.
	 */
	public void refreshView(TemplateRef template) {
		TemplateRef target = template != null ? template : activeTemplateRef;
		
		// load reference from storage
		if (target != null) {
			target = templateService.getTemplateRef(target.getUid());
		}

		// reload data
		loadData();

		if (target != null) {
			view.setActiveTemplate(target);
			editorPresenter.setActiveTemplate(templateService.getTemplate(target));
		} else {
			// clear all selections and showing data
			view.hideEditForm();
			view.clearSelection();
			editorPresenter.clear();
		}
	}
	
	private void validateTemplates(final Collection<TemplateRef> refs) {
		// start validation in separate thread
		Executor executor = new SimpleAsyncTaskExecutor();
		executor.execute(new Runnable() {
			@Override
			public void run() {
				for (TemplateRef ref : refs) {
					Template template = templateService.getTemplate(ref);
					TemplateValidator.getInstance().validateTemplate(template);
					ref.setValid(template.isValid());
				}
				view.refreshTable();
				eventBus.onTemplateValidationFinished();
			}
		});
	}
	
}
