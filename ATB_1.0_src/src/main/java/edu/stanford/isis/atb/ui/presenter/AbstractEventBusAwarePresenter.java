/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.presenter;

import edu.stanford.isis.atb.ui.action.EventBus;
import edu.stanford.isis.atb.ui.view.View;

/**
 * Abstract Presenter that is aware of Event Bus.
 * @param <V> View
 * @param <E> Event Bus
 * 
 * @author Vitaliy Semeshko
 */
public abstract class AbstractEventBusAwarePresenter<V extends View, E extends EventBus> extends AbstractPresenter<V> {

	protected E eventBus;
	
	public AbstractEventBusAwarePresenter(V view, E eventBus) {
		super(view);
		this.eventBus = eventBus;
	}
	
}
