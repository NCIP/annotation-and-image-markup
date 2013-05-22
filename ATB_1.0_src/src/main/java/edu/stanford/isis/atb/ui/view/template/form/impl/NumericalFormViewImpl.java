/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.template.form.impl;

import java.awt.Component;

import javax.swing.JComboBox;
import javax.swing.JFormattedTextField;
import javax.swing.text.JTextComponent;
import javax.swing.text.NumberFormatter;

import edu.stanford.isis.atb.domain.template.Operator;
import edu.stanford.isis.atb.ui.view.base.AbstractEditFormView;
import edu.stanford.isis.atb.ui.view.template.form.NumericalFormView;
import edu.stanford.isis.atb.ui.view.template.form.NumericalFormView.NumericalFormField;

/**
 * @author Vitaliy Semeshko
 */
public class NumericalFormViewImpl extends AbstractEditFormView<NumericalFormField> implements NumericalFormView {

	public NumericalFormViewImpl() {
		NumberFormatter numberformatter = new NumberFormatter();
		numberformatter.setValueClass(Double.class);
		JFormattedTextField value = new JFormattedTextField(numberformatter);
		addRow(NumericalFormField.VALUE, value, Mode.M_EN_EN);
		addRow(NumericalFormField.UCUM_STRING, textField(), Mode.M_EN_EN);
		addRow(NumericalFormField.OPERATOR, comboBox(Operator.values(), true), Mode.NM_EN_EN);
		buildForm();
	}
	
	@Override
	public void setFieldValue(NumericalFormField formField, Object value) {
		Component comp = getFieldComponent(formField);
		switch (formField) {
		case VALUE:
			((JFormattedTextField) comp).setValue(value);
			break;
		case UCUM_STRING:
			((JTextComponent) comp).setText(value.toString());
			break;
		case OPERATOR:
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
	public Object getFieldValue(NumericalFormField formField) {
		Component comp = getFieldComponent(formField);
		switch (formField) {
		case VALUE:
			return ((JFormattedTextField) comp).getValue();
		case UCUM_STRING:
			return ((JTextComponent) comp).getText();
		case OPERATOR:
			return ((JComboBox) comp).getSelectedItem();
		default:
			throw new IllegalArgumentException("Unknown field: " + formField.getLabel());
		}
	}

}
