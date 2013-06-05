/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.presenter.template.form;

import static edu.stanford.isis.atb.ui.view.template.form.OrdinalLevelFormView.OrdinalLevelFormField.DESCRIPTION;
import static edu.stanford.isis.atb.ui.view.template.form.OrdinalLevelFormView.OrdinalLevelFormField.VALUE;

import org.apache.commons.lang3.StringUtils;

import edu.stanford.isis.atb.domain.template.OrdinalLevel;
import edu.stanford.isis.atb.ui.presenter.form.AbstractFormPresenter;
import edu.stanford.isis.atb.ui.view.template.form.OrdinalLevelFormView;

/**
 * @author Vitaliy Semeshko
 */
public class OrdinalLevelFormPresenter extends AbstractFormPresenter<OrdinalLevel, OrdinalLevelFormView> {

	public OrdinalLevelFormPresenter(OrdinalLevelFormView view) {
		super(view);
	}
	
	@Override
	public void setValue(OrdinalLevel value) {
		this.value = value;
		view.setFieldValue(VALUE, value.getIntegerValue());
		view.setFieldValue(DESCRIPTION, StringUtils.trimToEmpty(value.getDescription()));
	}

	@Override
	protected boolean validate() {
		Integer intValue = (Integer) view.getFieldValue(VALUE);
		if (isEmpty(intValue, VALUE)) return false;
		
		String description = view.getFieldValue(DESCRIPTION).toString();
		
		value.setDescription(description);
		value.setIntegerValue(intValue);
		
		return true;
	}
	
}
