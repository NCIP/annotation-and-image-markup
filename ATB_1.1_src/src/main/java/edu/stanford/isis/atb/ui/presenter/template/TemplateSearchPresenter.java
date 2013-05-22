/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.presenter.template;

import edu.stanford.isis.atb.domain.ats.TemplateResults;
import edu.stanford.isis.atb.domain.ats.TemplateSearchRequest;
import edu.stanford.isis.atb.domain.ats.TemplateSingleResult;
import edu.stanford.isis.atb.domain.template.TemplateRef;
import edu.stanford.isis.atb.service.CallbackAdapter;
import edu.stanford.isis.atb.service.Command;
import edu.stanford.isis.atb.service.TemplateSearchService;
import edu.stanford.isis.atb.system.exception.ATBException;
import edu.stanford.isis.atb.ui.Const;
import edu.stanford.isis.atb.ui.action.EventBus;
import edu.stanford.isis.atb.ui.presenter.AbstractEventBusAwarePresenter;
import edu.stanford.isis.atb.ui.view.template.TemplateSearchView;

/**
 * Template Search Presenter (ATS).
 * 
 * @author Vitaliy Semeshko
 */
public class TemplateSearchPresenter extends AbstractEventBusAwarePresenter<TemplateSearchView, EventBus> {

	private TemplateSearchService searchService;

	public TemplateSearchPresenter(TemplateSearchView view, EventBus eventBus) {
		super(view, eventBus);
	}

	public void setSearchService(TemplateSearchService searchService) {
		this.searchService = searchService;
	}

	@Override
	public void bindView() {
		// bind commands
		view.setSearchCommand(new Command() {
			@Override
			public void execute() {
				TemplateSearchRequest req = view.getTemplateSearchRequest();
				searchService.searchTemplates(req, new CallbackAdapter<TemplateResults>() {
					@Override
					public void onSuccess(TemplateResults result) {
						view.setTemplates(result.getTemplates());
					}

					@Override
					protected void onFailure(ATBException caught) {
						view.showError(getErrorInformation(caught));
					}
				});
			}
		});
		
		view.setSelectCommand(new Command() {
			@Override
			public void execute() {
				TemplateSingleResult selection = view.getSelectedTemplate();
				if (selection != null) {
					searchService.importTemplate(selection.getUid(), new CallbackAdapter<TemplateRef>() {
						@Override
						public void onSuccess(TemplateRef result) {
							// refresh list, but don't navigate the template
							eventBus.onTemplateImported(null/*result*/);
							view.showInformation(String.format(Const.MSG_TEMPLATE_IMPORTED, result.getName()));
						}
						
						@Override
						public void onFailure(ATBException caught) {
							view.showError(getErrorInformation(caught));
						}
					});
				} else {
					view.showInformation(Const.MSG_NO_TEMPLATE_SELECTED);
				}
			}
		});
	}
	
	public void startSearch() {
		view.clear();
		view.showAsDialog();
	}
	
}
