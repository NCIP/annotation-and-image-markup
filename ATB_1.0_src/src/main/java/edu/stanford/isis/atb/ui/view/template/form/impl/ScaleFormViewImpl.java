/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.template.form.impl;

import static edu.stanford.isis.atb.ui.view.template.form.ScaleFormView.ScaleFormField.COMMENT;
import static edu.stanford.isis.atb.ui.view.template.form.ScaleFormView.ScaleFormField.DESCRIPTION;

import java.awt.Component;

import javax.swing.text.JTextComponent;

import edu.stanford.isis.atb.ui.view.base.AbstractEditFormView;
import edu.stanford.isis.atb.ui.view.template.form.ScaleFormView;
import edu.stanford.isis.atb.ui.view.template.form.ScaleFormView.ScaleFormField;

/**
 * @author Vitaliy Semeshko
 */
public class ScaleFormViewImpl extends AbstractEditFormView<ScaleFormField> implements ScaleFormView {

	public ScaleFormViewImpl() {
		addRow(DESCRIPTION, textArea(3), Mode.NM_EN_EN);
		addRow(COMMENT, textArea(3), Mode.NM_EN_EN);
		buildForm();
	}
	
	@Override
	public void setFieldValue(ScaleFormField formField, Object value) {
		Component comp = getFieldComponent(formField);
		switch (formField) {
		case DESCRIPTION:
		case COMMENT:
			((JTextComponent) comp).setText(value.toString());
			break;
		default:
			throw new IllegalArgumentException("Unknown field: " + formField.getLabel());
		}
	}

	@Override
	public Object getFieldValue(ScaleFormField formField) {
		Component comp = getFieldComponent(formField);
		switch (formField) {
		case DESCRIPTION:
		case COMMENT:
			return ((JTextComponent) comp).getText();
		default:
			throw new IllegalArgumentException("Unknown field: " + formField.getLabel());
		}
	}

}
