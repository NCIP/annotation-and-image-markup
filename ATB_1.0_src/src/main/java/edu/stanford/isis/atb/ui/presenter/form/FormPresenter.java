/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.presenter.form;

import java.awt.Component;

import edu.stanford.isis.atb.ui.presenter.Presenter;
import edu.stanford.isis.atb.ui.view.View;

/**
 * @author Vitaliy Semeshko
 */
public interface FormPresenter<V extends View> extends Presenter<V> {

	/**
	 * Prepare form for displaying.
	 * 
	 * @param isCreation indicates that form is shown in order to create new element
	 * @return {@link Component}
	 */
	public Component prepareForm(boolean isCreation);
	
}
