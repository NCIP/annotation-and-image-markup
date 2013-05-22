/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.template.form.impl;

import static edu.stanford.isis.atb.ui.view.template.form.IntervalFormView.IntervalFormField.MAX_OPERATOR;
import static edu.stanford.isis.atb.ui.view.template.form.IntervalFormView.IntervalFormField.MAX_VALUE;
import static edu.stanford.isis.atb.ui.view.template.form.IntervalFormView.IntervalFormField.MIN_OPERATOR;
import static edu.stanford.isis.atb.ui.view.template.form.IntervalFormView.IntervalFormField.MIN_VALUE;
import static edu.stanford.isis.atb.ui.view.template.form.IntervalFormView.IntervalFormField.UCUM_STRING;

import java.awt.Component;

import javax.swing.JComboBox;
import javax.swing.JFormattedTextField;
import javax.swing.text.JTextComponent;
import javax.swing.text.NumberFormatter;

import edu.stanford.isis.atb.domain.template.Operator;
import edu.stanford.isis.atb.ui.view.base.AbstractEditFormView;
import edu.stanford.isis.atb.ui.view.template.form.IntervalFormView;
import edu.stanford.isis.atb.ui.view.template.form.IntervalFormView.IntervalFormField;

/**
 * @author Vitaliy Semeshko
 */
public class IntervalFormViewImpl extends AbstractEditFormView<IntervalFormField> implements IntervalFormView {

	public IntervalFormViewImpl() {
		NumberFormatter numberformatter = new NumberFormatter();
		numberformatter.setValueClass(Double.class);
		JFormattedTextField minValue = new JFormattedTextField(numberformatter);
		JFormattedTextField maxValue = new JFormattedTextField(numberformatter);
		addRow(MIN_VALUE, minValue, Mode.M_EN_EN);
		addRow(MAX_VALUE, maxValue, Mode.M_EN_EN);
		addRow(MIN_OPERATOR, comboBox(Operator.values(), false), Mode.M_EN_EN);
		addRow(MAX_OPERATOR, comboBox(Operator.values(), false), Mode.M_EN_EN);
		addRow(UCUM_STRING, textField(), Mode.M_EN_EN);
		buildForm();
	}
	
	@Override
	public void setFieldValue(IntervalFormField formField, Object value) {
		Component comp = getFieldComponent(formField);
		switch (formField) {
		case MIN_VALUE:
		case MAX_VALUE:
			((JFormattedTextField) comp).setValue(value);
			break;
		case MIN_OPERATOR:
		case MAX_OPERATOR:
			JComboBox combo = (JComboBox) comp;
			if (value != null) {
				combo.setSelectedItem(value);
			} else {
				combo.setSelectedIndex(0);
			}
			break;
		case UCUM_STRING:
			((JTextComponent) comp).setText(value.toString());
			break;
		default:
			throw new IllegalArgumentException("Unknown field: " + formField.getLabel());
		}
	}

	@Override
	public Object getFieldValue(IntervalFormField formField) {
		Component comp = getFieldComponent(formField);
		switch (formField) {
		case MIN_VALUE:
		case MAX_VALUE:
			return ((JFormattedTextField) comp).getValue();
		case MIN_OPERATOR:
		case MAX_OPERATOR:
			return ((JComboBox) comp).getSelectedItem();
		case UCUM_STRING:
			return ((JTextComponent) comp).getText();
		default:
			throw new IllegalArgumentException("Unknown field: " + formField.getLabel());
		}
	}

}
