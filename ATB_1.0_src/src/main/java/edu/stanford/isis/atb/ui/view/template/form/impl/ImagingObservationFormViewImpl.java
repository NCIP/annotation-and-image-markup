/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.template.form.impl;

import static edu.stanford.isis.atb.ui.view.template.form.ImagingObservationFormView.ImagingObservationFormField.ANNOTATOR_CONFIDENCE;

import java.awt.Component;

import javax.swing.JCheckBox;

import edu.stanford.isis.atb.ui.view.base.AbstractEditFormView;
import edu.stanford.isis.atb.ui.view.template.form.ImagingObservationFormView;
import edu.stanford.isis.atb.ui.view.template.form.ImagingObservationFormView.ImagingObservationFormField;

/**
 * @author Vitaliy Semeshko
 */
public class ImagingObservationFormViewImpl extends AbstractEditFormView<ImagingObservationFormField> 
		implements ImagingObservationFormView {

	public ImagingObservationFormViewImpl() {
		addRow(ANNOTATOR_CONFIDENCE, new JCheckBox(), Mode.M_EN_EN);
		buildForm();
	}
	
	@Override
	public void setFieldValue(ImagingObservationFormField formField, Object value) {
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
	public Object getFieldValue(ImagingObservationFormField formField) {
		Component comp = getFieldComponent(formField);
		switch (formField) {
		case ANNOTATOR_CONFIDENCE:
			return ((JCheckBox) comp).isSelected();
		default:
			throw new IllegalArgumentException("Unknown field: " + formField.getLabel());
		}
	}

}
