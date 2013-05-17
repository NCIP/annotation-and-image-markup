/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.presenter.template.form;

import static edu.stanford.isis.atb.ui.view.template.form.IntervalFormView.IntervalFormField.MAX_OPERATOR;
import static edu.stanford.isis.atb.ui.view.template.form.IntervalFormView.IntervalFormField.MAX_VALUE;
import static edu.stanford.isis.atb.ui.view.template.form.IntervalFormView.IntervalFormField.MIN_OPERATOR;
import static edu.stanford.isis.atb.ui.view.template.form.IntervalFormView.IntervalFormField.MIN_VALUE;
import static edu.stanford.isis.atb.ui.view.template.form.IntervalFormView.IntervalFormField.UCUM_STRING;

import org.apache.commons.lang3.StringUtils;

import edu.stanford.isis.atb.domain.template.Interval;
import edu.stanford.isis.atb.domain.template.Operator;
import edu.stanford.isis.atb.ui.presenter.form.AbstractFormPresenter;
import edu.stanford.isis.atb.ui.view.template.form.IntervalFormView;

/**
 * @author Vitaliy Semeshko
 */
public class IntervalFormPresenter extends AbstractFormPresenter<Interval, IntervalFormView> {

	public IntervalFormPresenter(IntervalFormView view) {
		super(view);
	}
	
	@Override
	public void setValue(Interval value) {
		this.value = value;
		view.setFieldValue(MIN_VALUE, value.getMinValue());
		view.setFieldValue(MAX_VALUE, value.getMaxValue());
		view.setFieldValue(MIN_OPERATOR, value.getMinOperator());
		view.setFieldValue(MAX_OPERATOR, value.getMaxOperator());
		view.setFieldValue(UCUM_STRING, StringUtils.trimToEmpty(value.getUcumString()));
	}

	@Override
	protected boolean validate() {
		Double minVal = (Double) view.getFieldValue(MIN_VALUE);
		if (isEmpty(minVal, MIN_VALUE)) return false;
		
		Double maxVal = (Double) view.getFieldValue(MAX_VALUE);
		if (isEmpty(maxVal, MAX_VALUE)) return false;
		
		String ucumString = view.getFieldValue(UCUM_STRING).toString();
		if (isEmptyString(ucumString, UCUM_STRING)) return false;
		
		Object minOperator = view.getFieldValue(MIN_OPERATOR);
		if (minOperator != null && minOperator instanceof Operator) {
			value.setMinOperator((Operator) minOperator);
		} else {
			notifyWrongFieldValue(MIN_OPERATOR);
		}
		
		Object maxOperator = view.getFieldValue(MAX_OPERATOR);
		if (maxOperator != null && maxOperator instanceof Operator) {
			value.setMaxOperator((Operator) maxOperator);
		} else {
			notifyWrongFieldValue(MAX_OPERATOR);
		}
		
		value.setMinValue(minVal);
		value.setMaxValue(maxVal);
		value.setUcumString(ucumString);
		
		return true;
	}
	
}
