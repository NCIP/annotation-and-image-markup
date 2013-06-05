/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.presenter.template.form;

import static edu.stanford.isis.atb.ui.view.template.form.AnatomicEntityFormView.AnatomicEntityFormField.ANNOTATOR_CONFIDENCE;
import edu.stanford.isis.atb.domain.template.AnatomicEntity;
import edu.stanford.isis.atb.ui.presenter.form.AbstractFormPresenter;
import edu.stanford.isis.atb.ui.view.template.form.AnatomicEntityFormView;

/**
 * @author Vitaliy Semeshko
 */
public class AnatomicEntityFormPresenter extends AbstractFormPresenter<AnatomicEntity, AnatomicEntityFormView> {

	public AnatomicEntityFormPresenter(AnatomicEntityFormView view) {
		super(view);
	}
	
	@Override
	public void setValue(AnatomicEntity value) {
		this.value = value;
		view.setFieldValue(ANNOTATOR_CONFIDENCE, value.isAnnotatorConfidence());
	}

	@Override
	protected boolean validate() {
		Boolean confidence = (Boolean) view.getFieldValue(ANNOTATOR_CONFIDENCE);
		value.setAnnotatorConfidence(confidence);
		return true;
	}
	
}
