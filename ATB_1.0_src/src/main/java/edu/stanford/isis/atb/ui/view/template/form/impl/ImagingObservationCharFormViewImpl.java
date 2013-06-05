/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.template.form.impl;

import static edu.stanford.isis.atb.ui.view.template.form.ImagingObservationCharFormView.ImagingObservationCharFormField.ANNOTATOR_CONFIDENCE;
import static edu.stanford.isis.atb.ui.view.template.form.ImagingObservationCharFormView.ImagingObservationCharFormField.AUTHORS;
import static edu.stanford.isis.atb.ui.view.template.form.ImagingObservationCharFormView.ImagingObservationCharFormField.CARDINALITY;
import static edu.stanford.isis.atb.ui.view.template.form.ImagingObservationCharFormView.ImagingObservationCharFormField.EXPL_TEXT;
import static edu.stanford.isis.atb.ui.view.template.form.ImagingObservationCharFormView.ImagingObservationCharFormField.GROUP_LABEL;
import static edu.stanford.isis.atb.ui.view.template.form.ImagingObservationCharFormView.ImagingObservationCharFormField.LABEL;
import static edu.stanford.isis.atb.ui.view.template.form.ImagingObservationCharFormView.ImagingObservationCharFormField.SHOULD_DISPLAY;

import java.awt.Component;

import javax.swing.JCheckBox;
import javax.swing.text.JTextComponent;

import edu.stanford.isis.atb.ui.model.Cardinality;
import edu.stanford.isis.atb.ui.view.base.AbstractEditFormView;
import edu.stanford.isis.atb.ui.view.template.form.ImagingObservationCharFormView;
import edu.stanford.isis.atb.ui.view.template.form.ImagingObservationCharFormView.ImagingObservationCharFormField;
import edu.stanford.isis.atb.ui.view.widget.CardinalityWidget;

/**
 * @author Vitaliy Semeshko
 */
public class ImagingObservationCharFormViewImpl extends AbstractEditFormView<ImagingObservationCharFormField> 
		implements ImagingObservationCharFormView {

	public ImagingObservationCharFormViewImpl() {
		addRow(LABEL, textField(), Mode.M_EN_EN);
		addRow(EXPL_TEXT, textArea(3), Mode.NM_EN_EN);
		addRow(CARDINALITY, cardinality(), Mode.M_EN_EN);
		addRow(SHOULD_DISPLAY, new JCheckBox(), Mode.M_EN_EN);
		addRow(ANNOTATOR_CONFIDENCE, new JCheckBox(), Mode.M_EN_EN);
		addRow(AUTHORS, textField(), Mode.NM_EN_EN);
		addRow(GROUP_LABEL, textField(), Mode.NM_EN_EN);
		
		buildForm();
	}
	
	@Override
	public void setFieldValue(ImagingObservationCharFormField formField, Object value) {
		Component comp = getFieldComponent(formField);
		switch (formField) {
		case LABEL:
			((JTextComponent) comp).setText(value.toString());
			break;
		case EXPL_TEXT:
			((JTextComponent) comp).setText(value.toString());
			break;
		case CARDINALITY:
			((CardinalityWidget) comp).setCardinality((Cardinality) value);
			break;
		case SHOULD_DISPLAY:
			((JCheckBox) comp).setSelected((Boolean) value);
			break;
		case ANNOTATOR_CONFIDENCE:
			((JCheckBox) comp).setSelected((Boolean) value);
			break;
		case AUTHORS:
			((JTextComponent) comp).setText(value.toString());
			break;
		case GROUP_LABEL:
			((JTextComponent) comp).setText(value.toString());
			break;
		default:
			throw new IllegalArgumentException("Unknown field: " + formField.getLabel());
		}
	}

	@Override
	public Object getFieldValue(ImagingObservationCharFormField formField) {
		Component comp = getFieldComponent(formField);
		switch (formField) {
		case LABEL:
			return ((JTextComponent) comp).getText();
		case EXPL_TEXT:
			return ((JTextComponent) comp).getText();
		case CARDINALITY:
			return ((CardinalityWidget) comp).getCardinality();
		case SHOULD_DISPLAY:
			return ((JCheckBox) comp).isSelected();
		case ANNOTATOR_CONFIDENCE:
			return ((JCheckBox) comp).isSelected();
		case AUTHORS:
			return ((JTextComponent) comp).getText();
		case GROUP_LABEL:
			return ((JTextComponent) comp).getText();
		default:
			throw new IllegalArgumentException("Unknown field: " + formField.getLabel());
		}
	}

}
