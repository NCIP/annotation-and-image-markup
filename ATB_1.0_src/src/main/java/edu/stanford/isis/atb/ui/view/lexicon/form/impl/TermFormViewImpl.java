/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.lexicon.form.impl;

import static edu.stanford.isis.atb.ui.Const.FMT_TIME_DATE_DISPLAY;
import static edu.stanford.isis.atb.ui.view.lexicon.form.TermFormView.TermFormField.DESCRIPTION;
import static edu.stanford.isis.atb.ui.view.lexicon.form.TermFormView.TermFormField.CODE_MEANING;
import static edu.stanford.isis.atb.ui.view.lexicon.form.TermFormView.TermFormField.CODE_VALUE;

import java.awt.Component;
import java.text.SimpleDateFormat;

import javax.swing.JFormattedTextField;
import javax.swing.text.JTextComponent;

import edu.stanford.isis.atb.ui.view.base.AbstractEditFormView;
import edu.stanford.isis.atb.ui.view.lexicon.form.TermFormView;
import edu.stanford.isis.atb.ui.view.lexicon.form.TermFormView.TermFormField;

/**
 * @author Vitaliy Semeshko
 */
public class TermFormViewImpl extends AbstractEditFormView<TermFormField> implements TermFormView {

	public TermFormViewImpl() {
		addRow(CODE_MEANING, textField(), Mode.M_EN_EN);
		addRow(DESCRIPTION, textArea(6), Mode.NM_EN_EN);
		addRow(CODE_VALUE, textField(), Mode.M_EN_EN);

		JFormattedTextField creationDate = new JFormattedTextField(new SimpleDateFormat(FMT_TIME_DATE_DISPLAY));
		addRow(TermFormField.CREATION_DATE, creationDate, Mode.NM_DIS_DIS);
		
		JFormattedTextField modificationDate = new JFormattedTextField(new SimpleDateFormat(FMT_TIME_DATE_DISPLAY));
		addRow(TermFormField.MODIFICATION_DATE, modificationDate, Mode.NM_DIS_DIS);
		
		buildForm();
	}
	
	@Override
	public void setFieldValue(TermFormField formField, Object value) {
		Component comp = getFieldComponent(formField);
		switch (formField) {
		case CODE_MEANING:
		case CODE_VALUE:	
		case DESCRIPTION:
			((JTextComponent) comp).setText(value.toString());
			break;
		case CREATION_DATE:
		case MODIFICATION_DATE:
			((JFormattedTextField) comp).setValue(value);
			break;
		default:
			throw new IllegalArgumentException("Unknown field: " + formField.getLabel());
		}
	}

	@Override
	public Object getFieldValue(TermFormField formField) {
		Component comp = getFieldComponent(formField);
		switch (formField) {
		case CODE_MEANING:
		case CODE_VALUE:
		case DESCRIPTION:
			return ((JTextComponent) comp).getText();
		case CREATION_DATE:
		case MODIFICATION_DATE:
			return ((JFormattedTextField) comp).getValue();
		default:
			throw new IllegalArgumentException("Unknown field: " + formField.getLabel());
		}
	}

}
