/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.presenter.group;

import edu.stanford.isis.atb.domain.ats.ContainerResults;
import edu.stanford.isis.atb.domain.ats.ContainerSearchRequest;
import edu.stanford.isis.atb.domain.ats.ContainerSingleResult;
import edu.stanford.isis.atb.domain.template.TemplateContainer;
import edu.stanford.isis.atb.service.CallbackAdapter;
import edu.stanford.isis.atb.service.Command;
import edu.stanford.isis.atb.service.TemplateSearchService;
import edu.stanford.isis.atb.system.exception.ATBException;
import edu.stanford.isis.atb.ui.Const;
import edu.stanford.isis.atb.ui.action.EventBus;
import edu.stanford.isis.atb.ui.presenter.AbstractEventBusAwarePresenter;
import edu.stanford.isis.atb.ui.view.group.GroupSearchView;

/**
 * Group Search Presenter (ATS).
 * 
 * @author Vitaliy Semeshko
 */
public class GroupSearchPresenter extends AbstractEventBusAwarePresenter<GroupSearchView, EventBus> {

	private TemplateSearchService searchService;

	public GroupSearchPresenter(GroupSearchView view, EventBus eventBus) {
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
				ContainerSearchRequest req = view.getContainerSearchRequest();
				searchService.searchContainers(req, new CallbackAdapter<ContainerResults>() {
					@Override
					public void onSuccess(ContainerResults result) {
						view.setContainers(result.getContainers());
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
				ContainerSingleResult selection = view.getSelectedContainer();
				if (selection != null) {
					searchService.importContainer(selection.getUid(), new CallbackAdapter<TemplateContainer>() {
						@Override
						public void onSuccess(TemplateContainer result) {
							// refresh list, but don't navigate the container
							eventBus.onContainerImported(null/*result*/);
							view.showInformation(String.format(Const.MSG_CONTAINER_IMPORTED, result.getName()));
						}
						
						@Override
						public void onFailure(ATBException caught) {
							view.showError(getErrorInformation(caught));
						}
					});
				} else {
					view.showInformation(Const.MSG_NO_CONTAINER_SELECTED);
				}
			}
		});
	}
	
	public void startSearch() {
		view.clear();
		view.showAsDialog();
	}
	
}
