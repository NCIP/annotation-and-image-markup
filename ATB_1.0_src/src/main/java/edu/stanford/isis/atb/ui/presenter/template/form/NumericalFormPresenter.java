/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.presenter.template.form;

import static edu.stanford.isis.atb.ui.view.template.form.NumericalFormView.NumericalFormField.OPERATOR;
import static edu.stanford.isis.atb.ui.view.template.form.NumericalFormView.NumericalFormField.UCUM_STRING;
import static edu.stanford.isis.atb.ui.view.template.form.NumericalFormView.NumericalFormField.VALUE;

import org.apache.commons.lang3.StringUtils;

import edu.stanford.isis.atb.domain.template.Numerical;
import edu.stanford.isis.atb.domain.template.Operator;
import edu.stanford.isis.atb.ui.presenter.form.AbstractFormPresenter;
import edu.stanford.isis.atb.ui.view.template.form.NumericalFormView;

/**
 * @author Vitaliy Semeshko
 */
public class NumericalFormPresenter extends AbstractFormPresenter<Numerical, NumericalFormView> {

	public NumericalFormPresenter(NumericalFormView view) {
		super(view);
	}
	
	@Override
	public void setValue(Numerical value) {
		this.value = value;
		view.setFieldValue(VALUE, value.getValue());
		view.setFieldValue(UCUM_STRING, StringUtils.trimToEmpty(value.getUcumString()));
		view.setFieldValue(OPERATOR, value.getOperator());
	}

	@Override
	protected boolean validate() {
		Double val = (Double) view.getFieldValue(VALUE);
		if (isEmpty(val, VALUE)) return false;
		
		String ucumString = view.getFieldValue(UCUM_STRING).toString();
		if (isEmptyString(ucumString, UCUM_STRING)) return false;
		
		Object operator = view.getFieldValue(OPERATOR);
		if (operator != null && operator instanceof Operator) {
			value.setOperator((Operator) operator);
		} else {
			value.setOperator(null);
		}
		
		value.setValue(val);
		value.setUcumString(ucumString);
		
		return true;
	}
	
}
