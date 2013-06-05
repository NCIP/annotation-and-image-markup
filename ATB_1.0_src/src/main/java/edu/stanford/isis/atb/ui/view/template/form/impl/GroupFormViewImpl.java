/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.template.form.impl;

import static edu.stanford.isis.atb.ui.view.template.form.GroupFormView.GroupFormField.AUTHORS;
import static edu.stanford.isis.atb.ui.view.template.form.GroupFormView.GroupFormField.CREATION_DATE;
import static edu.stanford.isis.atb.ui.view.template.form.GroupFormView.GroupFormField.DESCRIPTION;
import static edu.stanford.isis.atb.ui.view.template.form.GroupFormView.GroupFormField.NAME;
import static edu.stanford.isis.atb.ui.view.template.form.GroupFormView.GroupFormField.UID;
import static edu.stanford.isis.atb.ui.view.template.form.GroupFormView.GroupFormField.VERSION;

import java.awt.Component;
import java.text.SimpleDateFormat;

import javax.swing.JFormattedTextField;
import javax.swing.text.JTextComponent;

import edu.stanford.isis.atb.ui.Const;
import edu.stanford.isis.atb.ui.view.base.AbstractEditFormView;
import edu.stanford.isis.atb.ui.view.template.form.GroupFormView;
import edu.stanford.isis.atb.ui.view.template.form.GroupFormView.GroupFormField;

/**
 * @author Vitaliy Semeshko
 */
public class GroupFormViewImpl extends AbstractEditFormView<GroupFormField> implements GroupFormView {

	public GroupFormViewImpl() {
		addRow(NAME, textField(), Mode.M_EN_EN);
		addRow(VERSION, textField(), Mode.M_EN_EN);
		addRow(DESCRIPTION, textArea(3), Mode.M_EN_EN);
		addRow(AUTHORS, textField(), Mode.NM_EN_EN);
		addRow(UID, textField(), Mode.M_DIS_DIS);
		
		JFormattedTextField creationDate = new JFormattedTextField(new SimpleDateFormat(Const.FMT_DATE_DISPLAY));
		addRow(CREATION_DATE, creationDate, Mode.NM_DIS_DIS);
		
		buildForm();
	}
	
	@Override
	public void setFieldValue(GroupFormField formField, Object value) {
		Component comp = getFieldComponent(formField);
		switch (formField) {
		case UID:
		case NAME:
		case VERSION:
		case DESCRIPTION:
		case AUTHORS:
			((JTextComponent) comp).setText(value.toString());
			break;
		case CREATION_DATE:
			((JFormattedTextField) comp).setValue(value);
			break;
		default:
			throw new IllegalArgumentException("Unknown field: " + formField.getLabel());
		}
	}

	@Override
	public Object getFieldValue(GroupFormField formField) {
		Component comp = getFieldComponent(formField);
		switch (formField) {
		case UID:
		case NAME:
		case VERSION:
		case DESCRIPTION:
		case AUTHORS:
			return ((JTextComponent) comp).getText();
		case CREATION_DATE:
			return ((JFormattedTextField) comp).getValue();
		default:
			throw new IllegalArgumentException("Unknown field: " + formField.getLabel());
		}
	}

}
