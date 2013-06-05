/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.presenter.template.form;

import static edu.stanford.isis.atb.ui.view.template.form.CharQuantificationFormView.CharQuantificationFormField.ANNOTATOR_CONFIDENCE;
import static edu.stanford.isis.atb.ui.view.template.form.CharQuantificationFormView.CharQuantificationFormField.NAME;

import org.apache.commons.lang3.StringUtils;

import edu.stanford.isis.atb.domain.template.CharacteristicQuantification;
import edu.stanford.isis.atb.ui.presenter.form.AbstractFormPresenter;
import edu.stanford.isis.atb.ui.view.template.form.CharQuantificationFormView;

/**
 * @author Vitaliy Semeshko
 */
public class CharQuantificationFormPresenter extends AbstractFormPresenter<CharacteristicQuantification, 
		CharQuantificationFormView> {

	public CharQuantificationFormPresenter(CharQuantificationFormView view) {
		super(view);
	}
	
	@Override
	public void setValue(CharacteristicQuantification value) {
		this.value = value;
		view.setFieldValue(NAME, StringUtils.trimToEmpty(value.getName()));
		view.setFieldValue(ANNOTATOR_CONFIDENCE, value.isAnnotatorConfidence());
	}

	@Override
	protected boolean validate() {
		String name = view.getFieldValue(NAME).toString();
		if (isEmptyString(name, NAME)) {
			return false;
		}
		
		Boolean confidence = (Boolean) view.getFieldValue(ANNOTATOR_CONFIDENCE);
		
		value.setName(name);
		value.setAnnotatorConfidence(confidence);
		
		return true;
	}
	
}
