/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.template.form.impl;

import java.awt.Component;

import javax.swing.JSpinner;
import javax.swing.SpinnerNumberModel;

import edu.stanford.isis.atb.ui.view.base.AbstractEditFormView;
import edu.stanford.isis.atb.ui.view.template.form.QuantileFormView;
import edu.stanford.isis.atb.ui.view.template.form.QuantileFormView.QuantileFormField;

/**
 * @author Vitaliy Semeshko
 */
public class QuantileFormViewImpl extends AbstractEditFormView<QuantileFormField> implements QuantileFormView {

	public QuantileFormViewImpl() {
		JSpinner spnBins = new JSpinner();
		spnBins.setModel(new SpinnerNumberModel(0, 0, Integer.MAX_VALUE, 1));
		addRow(QuantileFormField.BINS, spnBins, Mode.M_EN_EN);
		buildForm();
	}
	
	@Override
	public void setFieldValue(QuantileFormField formField, Object value) {
		Component comp = getFieldComponent(formField);
		switch (formField) {
		case BINS:
			((JSpinner) comp).setValue(value);
			break;
		default:
			throw new IllegalArgumentException("Unknown field: " + formField.getLabel());
		}
	}

	@Override
	public Object getFieldValue(QuantileFormField formField) {
		Component comp = getFieldComponent(formField);
		switch (formField) {
		case BINS:
			return ((JSpinner) comp).getValue();
		default:
			throw new IllegalArgumentException("Unknown field: " + formField.getLabel());
		}
	}

}
