/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.lexicon.form.impl;

import static edu.stanford.isis.atb.ui.Const.FMT_TIME_DATE_DISPLAY;
import static edu.stanford.isis.atb.ui.view.lexicon.form.LexiconFormView.LexiconFormField.AUTHORS;
import static edu.stanford.isis.atb.ui.view.lexicon.form.LexiconFormView.LexiconFormField.CREATION_DATE;
import static edu.stanford.isis.atb.ui.view.lexicon.form.LexiconFormView.LexiconFormField.DESCRIPTION;
import static edu.stanford.isis.atb.ui.view.lexicon.form.LexiconFormView.LexiconFormField.MODIFICATION_DATE;
import static edu.stanford.isis.atb.ui.view.lexicon.form.LexiconFormView.LexiconFormField.NAME;
import static edu.stanford.isis.atb.ui.view.lexicon.form.LexiconFormView.LexiconFormField.READ_ONLY;
import static edu.stanford.isis.atb.ui.view.lexicon.form.LexiconFormView.LexiconFormField.SCHEMA_DESIGNATOR;
import static edu.stanford.isis.atb.ui.view.lexicon.form.LexiconFormView.LexiconFormField.SCHEMA_VERSION;

import java.awt.Component;
import java.text.SimpleDateFormat;

import javax.swing.JCheckBox;
import javax.swing.JFormattedTextField;
import javax.swing.text.JTextComponent;

import edu.stanford.isis.atb.ui.view.base.AbstractEditFormView;
import edu.stanford.isis.atb.ui.view.lexicon.form.LexiconFormView;
import edu.stanford.isis.atb.ui.view.lexicon.form.LexiconFormView.LexiconFormField;

/**
 * @author Vitaliy Semeshko
 */
public class LexiconFormViewImpl extends AbstractEditFormView<LexiconFormField> implements LexiconFormView {

	public LexiconFormViewImpl() {
		addRow(NAME, textField(), Mode.M_EN_EN);
		addRow(SCHEMA_DESIGNATOR, textField(), Mode.M_EN_EN);
		addRow(SCHEMA_VERSION, textField(), Mode.NM_EN_EN);
		addRow(DESCRIPTION, textArea(6), Mode.NM_EN_EN);
		addRow(AUTHORS, textField(), Mode.NM_EN_EN);
		addRow(READ_ONLY, new JCheckBox(), Mode.NM_DIS_DIS);

		JFormattedTextField creationDate = new JFormattedTextField(new SimpleDateFormat(FMT_TIME_DATE_DISPLAY));
		addRow(CREATION_DATE, creationDate, Mode.NM_DIS_DIS);
		
		JFormattedTextField modificationDate = new JFormattedTextField(new SimpleDateFormat(FMT_TIME_DATE_DISPLAY));
		addRow(MODIFICATION_DATE, modificationDate, Mode.NM_DIS_DIS);
		
		buildForm();
	}
	
	@Override
	public void setFieldValue(LexiconFormField formField, Object value) {
		Component comp = getFieldComponent(formField);
		switch (formField) {
		case NAME:
		case SCHEMA_DESIGNATOR:
		case SCHEMA_VERSION:
		case DESCRIPTION:
		case AUTHORS:
			((JTextComponent) comp).setText(value.toString());
			break;
		case READ_ONLY:
			((JCheckBox) comp).setSelected((Boolean) value);
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
	public Object getFieldValue(LexiconFormField formField) {
		Component comp = getFieldComponent(formField);
		switch (formField) {
		case NAME:
		case SCHEMA_DESIGNATOR:
		case SCHEMA_VERSION:
		case DESCRIPTION:
		case AUTHORS:
			return ((JTextComponent) comp).getText();
		case READ_ONLY:
			return ((JCheckBox) comp).isSelected();
		case CREATION_DATE:
		case MODIFICATION_DATE:
			return ((JFormattedTextField) comp).getValue();
		default:
			throw new IllegalArgumentException("Unknown field: " + formField.getLabel());
		}
	}

}
