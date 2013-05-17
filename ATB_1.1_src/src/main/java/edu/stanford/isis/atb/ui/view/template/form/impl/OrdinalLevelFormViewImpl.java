/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.template.form.impl;

import static edu.stanford.isis.atb.ui.view.template.form.OrdinalLevelFormView.OrdinalLevelFormField.DESCRIPTION;
import static edu.stanford.isis.atb.ui.view.template.form.OrdinalLevelFormView.OrdinalLevelFormField.VALUE;

import java.awt.Component;

import javax.swing.JSpinner;
import javax.swing.SpinnerNumberModel;
import javax.swing.text.JTextComponent;

import edu.stanford.isis.atb.ui.view.base.AbstractEditFormView;
import edu.stanford.isis.atb.ui.view.template.form.OrdinalLevelFormView;
import edu.stanford.isis.atb.ui.view.template.form.OrdinalLevelFormView.OrdinalLevelFormField;

/**
 * @author Vitaliy Semeshko
 */
public class OrdinalLevelFormViewImpl extends AbstractEditFormView<OrdinalLevelFormField> 
	implements OrdinalLevelFormView {

	public OrdinalLevelFormViewImpl() {
		JSpinner spnValue = new JSpinner();
		spnValue.setModel(new SpinnerNumberModel(0, 0, Integer.MAX_VALUE, 1));
		addRow(VALUE, spnValue, Mode.M_EN_EN);
		addRow(DESCRIPTION, textArea(3), Mode.NM_EN_EN);
		buildForm();
	}
	
	@Override
	public void setFieldValue(OrdinalLevelFormField formField, Object value) {
		Component comp = getFieldComponent(formField);
		switch (formField) {
		case VALUE:
			((JSpinner) comp).setValue(value);
			break;
		case DESCRIPTION:
			((JTextComponent) comp).setText(value.toString());
			break;
		default:
			throw new IllegalArgumentException("Unknown field: " + formField.getLabel());
		}
	}

	@Override
	public Object getFieldValue(OrdinalLevelFormField formField) {
		Component comp = getFieldComponent(formField);
		switch (formField) {
		case VALUE:
			return ((JSpinner) comp).getValue();
		case DESCRIPTION:
			return ((JTextComponent) comp).getText();
		default:
			throw new IllegalArgumentException("Unknown field: " + formField.getLabel());
		}
	}

}
