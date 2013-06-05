/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.template.form.impl;

import static edu.stanford.isis.atb.ui.view.template.form.GeometricShapeFormView.GeometricShapeFormField.SHAPE_TYPE;

import java.awt.Component;

import javax.swing.JComboBox;

import edu.stanford.isis.atb.domain.template.GeometricShapeType;
import edu.stanford.isis.atb.ui.view.base.AbstractEditFormView;
import edu.stanford.isis.atb.ui.view.template.form.GeometricShapeFormView;
import edu.stanford.isis.atb.ui.view.template.form.GeometricShapeFormView.GeometricShapeFormField;

/**
 * @author Vitaliy Semeshko
 */
public class GeometricShapeFormViewImpl extends AbstractEditFormView<GeometricShapeFormField> 
		implements GeometricShapeFormView {

	public GeometricShapeFormViewImpl() {
		addRow(SHAPE_TYPE, comboBox(GeometricShapeType.values(), false), Mode.M_EN_EN);
		buildForm();
	}
	
	@Override
	public void setFieldValue(GeometricShapeFormField formField, Object value) {
		Component comp = getFieldComponent(formField);
		switch (formField) {
		case SHAPE_TYPE:
			JComboBox combo = (JComboBox) comp;
			if (value != null) {
				combo.setSelectedItem(value);
			} else {
				combo.setSelectedIndex(0);
			}
			break;
		default:
			throw new IllegalArgumentException("Unknown field: " + formField.getLabel());
		}
	}

	@Override
	public Object getFieldValue(GeometricShapeFormField formField) {
		Component comp = getFieldComponent(formField);
		switch (formField) {
		case SHAPE_TYPE:
			return ((JComboBox) comp).getSelectedItem();
		default:
			throw new IllegalArgumentException("Unknown field: " + formField.getLabel());
		}
	}

}
