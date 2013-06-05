/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.action;

import org.springframework.stereotype.Component;

import edu.stanford.isis.atb.domain.template.TemplateContainer;
import edu.stanford.isis.atb.domain.template.TemplateRef;
import edu.stanford.isis.atb.system.exception.ATBException;
import edu.stanford.isis.atb.ui.presenter.group.GroupPresenter;
import edu.stanford.isis.atb.ui.presenter.template.TemplatePresenter;

/**
 * @author Vitaliy Semeshko
 */

//TODO: this implementation is very simple and is actually Mediator.
// make smarter, decoupled from real presenters

@Component
public class EventBusImpl implements EventBus {

	private GroupPresenter groupPresenter;
	
	private TemplatePresenter templatePresenter;
	
	public void registerGroupPresenter(GroupPresenter groupPresenter) {
		this.groupPresenter = groupPresenter;
	}
	
	public void registerTemplatePresenter(TemplatePresenter templatePresenter) {
		this.templatePresenter = templatePresenter;
	}

	@Override
	public void onTemplateChanged(TemplateRef template) {
		beforeHandleAction();
		groupPresenter.refreshView(null);
	}
	
	@Override
	public void onTemplateDeleted(TemplateRef template) {
		beforeHandleAction();
		groupPresenter.refreshView(null);
	}

	@Override
	public void onContainerImported(TemplateContainer container) {
		beforeHandleAction();
		groupPresenter.refreshView(container);
		templatePresenter.refreshView(null);
	}

	@Override
	public void onTemplateImported(TemplateRef template) {
		beforeHandleAction();
		templatePresenter.refreshView(template);
		groupPresenter.refreshView(null);
	}

	@Override
	public void onTemplateValidationFinished() {
		beforeHandleAction();
		groupPresenter.refreshView(null);
	}

	/**
	 * Ensure completeness.
	 */
	private void beforeHandleAction() {
		if (groupPresenter == null || templatePresenter == null) {
			throw new ATBException("Event bus not is not completely initialized.");
		}
	}
	
}
