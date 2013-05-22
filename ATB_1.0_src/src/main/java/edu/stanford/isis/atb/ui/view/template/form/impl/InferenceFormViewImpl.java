/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.template.form.impl;

import static edu.stanford.isis.atb.ui.view.template.form.InferenceFormView.InferenceFormField.ANNOTATOR_CONFIDENCE;

import java.awt.Component;

import javax.swing.JCheckBox;

import edu.stanford.isis.atb.ui.view.base.AbstractEditFormView;
import edu.stanford.isis.atb.ui.view.template.form.InferenceFormView;
import edu.stanford.isis.atb.ui.view.template.form.InferenceFormView.InferenceFormField;

/**
 * @author Vitaliy Semeshko
 */
public class InferenceFormViewImpl extends AbstractEditFormView<InferenceFormField> implements InferenceFormView {

	public InferenceFormViewImpl() {
		addRow(ANNOTATOR_CONFIDENCE, new JCheckBox(), Mode.M_EN_EN);
		buildForm();
	}
	
	@Override
	public void setFieldValue(InferenceFormField formField, Object value) {
		Component comp = getFieldComponent(formField);
		switch (formField) {
		case ANNOTATOR_CONFIDENCE:
			((JCheckBox) comp).setSelected((Boolean) value);
			break;
		default:
			throw new IllegalArgumentException("Unknown field: " + formField.getLabel());
		}
	}

	@Override
	public Object getFieldValue(InferenceFormField formField) {
		Component comp = getFieldComponent(formField);
		switch (formField) {
		case ANNOTATOR_CONFIDENCE:
			return ((JCheckBox) comp).isSelected();
		default:
			throw new IllegalArgumentException("Unknown field: " + formField.getLabel());
		}
	}

}
