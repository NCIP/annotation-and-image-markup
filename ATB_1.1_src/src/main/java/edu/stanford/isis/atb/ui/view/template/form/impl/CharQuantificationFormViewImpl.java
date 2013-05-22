/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.template.form.impl;

import static edu.stanford.isis.atb.ui.view.template.form.CharQuantificationFormView.CharQuantificationFormField.ANNOTATOR_CONFIDENCE;
import static edu.stanford.isis.atb.ui.view.template.form.CharQuantificationFormView.CharQuantificationFormField.NAME;

import java.awt.Component;

import javax.swing.JCheckBox;
import javax.swing.text.JTextComponent;

import edu.stanford.isis.atb.ui.view.base.AbstractEditFormView;
import edu.stanford.isis.atb.ui.view.template.form.CharQuantificationFormView;
import edu.stanford.isis.atb.ui.view.template.form.CharQuantificationFormView.CharQuantificationFormField;

/**
 * @author Vitaliy Semeshko
 */
public class CharQuantificationFormViewImpl extends AbstractEditFormView<CharQuantificationFormField> 
		implements CharQuantificationFormView {

	public CharQuantificationFormViewImpl() {
		addRow(NAME, textField(), Mode.M_EN_EN);
		addRow(ANNOTATOR_CONFIDENCE, new JCheckBox(), Mode.M_EN_EN);
		buildForm();
	}
	
	@Override
	public void setFieldValue(CharQuantificationFormField formField, Object value) {
		Component comp = getFieldComponent(formField);
		switch (formField) {
		case NAME:
			((JTextComponent) comp).setText(value.toString());
			break;
		case ANNOTATOR_CONFIDENCE:
			((JCheckBox) comp).setSelected((Boolean) value);
			break;
		default:
			throw new IllegalArgumentException("Unknown field: " + formField.getLabel());
		}
	}

	@Override
	public Object getFieldValue(CharQuantificationFormField formField) {
		Component comp = getFieldComponent(formField);
		switch (formField) {
		case NAME:
			return ((JTextComponent) comp).getText();
		case ANNOTATOR_CONFIDENCE:
			return ((JCheckBox) comp).isSelected();
		default:
			throw new IllegalArgumentException("Unknown field: " + formField.getLabel());
		}
	}

}
