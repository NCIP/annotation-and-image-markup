/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.template.form.impl;

import static edu.stanford.isis.atb.ui.view.template.form.TemplateFormView.TemplateFormField.AUTHORS;
import static edu.stanford.isis.atb.ui.view.template.form.TemplateFormView.TemplateFormField.CREATION_DATE;
import static edu.stanford.isis.atb.ui.view.template.form.TemplateFormView.TemplateFormField.DESCRIPTION;
import static edu.stanford.isis.atb.ui.view.template.form.TemplateFormView.TemplateFormField.MODALITY;
import static edu.stanford.isis.atb.ui.view.template.form.TemplateFormView.TemplateFormField.NAME;
import static edu.stanford.isis.atb.ui.view.template.form.TemplateFormView.TemplateFormField.PRECEDING_ANNOTATION;
import static edu.stanford.isis.atb.ui.view.template.form.TemplateFormView.TemplateFormField.TERM_BLOCK;
import static edu.stanford.isis.atb.ui.view.template.form.TemplateFormView.TemplateFormField.UID;
import static edu.stanford.isis.atb.ui.view.template.form.TemplateFormView.TemplateFormField.VERSION;

import java.awt.Component;
import java.text.SimpleDateFormat;

import javax.swing.JComboBox;
import javax.swing.JFormattedTextField;
import javax.swing.text.JTextComponent;

import edu.stanford.isis.atb.domain.template.CodedTerm;
import edu.stanford.isis.atb.domain.template.ModalityType;
import edu.stanford.isis.atb.domain.template.PrecedingAnnotationRequest;
import edu.stanford.isis.atb.service.Command;
import edu.stanford.isis.atb.ui.Const;
import edu.stanford.isis.atb.ui.view.base.AbstractEditFormView;
import edu.stanford.isis.atb.ui.view.template.form.TemplateFormView;
import edu.stanford.isis.atb.ui.view.template.form.TemplateFormView.TemplateFormField;
import edu.stanford.isis.atb.ui.view.widget.lexicon.LexiconTermEdit;

/**
 * @author Vitaliy Semeshko
 */
public class TemplateFormViewImpl extends AbstractEditFormView<TemplateFormField> implements TemplateFormView {

	private LexiconTermEdit lexiconTermEdit = new LexiconTermEdit();
	
	public TemplateFormViewImpl() {
		addRow(NAME, textField(), Mode.M_EN_EN);
		addRow(DESCRIPTION, textArea(3), Mode.M_EN_EN);
		addRow(AUTHORS, textField(), Mode.NM_EN_EN);
		addRow(MODALITY, comboBox(ModalityType.values(), true), Mode.NM_EN_EN);
		addRow(PRECEDING_ANNOTATION, comboBox(PrecedingAnnotationRequest.values(), true), Mode.NM_EN_EN);
		addRow(UID, textField(), Mode.M_DIS_DIS);
		
		JFormattedTextField creationDate = new JFormattedTextField(new SimpleDateFormat(Const.FMT_DATE_DISPLAY));
		addRow(CREATION_DATE, creationDate, Mode.NM_DIS_DIS);
		
		addRow(VERSION, textField(), Mode.M_EN_EN);
		
		addBlock(TERM_BLOCK, lexiconTermEdit);
		
		buildForm();
	}
	
	@Override
	public void setFieldValue(TemplateFormField formField, Object value) {
		Component comp = getFieldComponent(formField);
		switch (formField) {
		case NAME:
			((JTextComponent) comp).setText(value.toString());
			break;
		case DESCRIPTION:
			((JTextComponent) comp).setText(value.toString());
			break;
		case AUTHORS:
			((JTextComponent) comp).setText(value.toString());
			break;
		case MODALITY:
			JComboBox modalityComboBox = (JComboBox) comp;
			if (value != null) {
				modalityComboBox.setSelectedItem(value);
			} else {
				modalityComboBox.setSelectedIndex(0);
			}
			break;
		case PRECEDING_ANNOTATION:
			JComboBox precedingAnnotationComboBox = (JComboBox) comp;
			if (value != null) {
				precedingAnnotationComboBox.setSelectedItem(value);
			} else {
				precedingAnnotationComboBox.setSelectedIndex(0);
			}
			break;
		case UID:
			((JTextComponent) comp).setText(value.toString());
			break;
		case CREATION_DATE:
			((JFormattedTextField) comp).setValue(value);
			break;
		case VERSION:
			((JTextComponent) comp).setText(value.toString());
			break;
		case TERM_BLOCK:
			((LexiconTermEdit) comp).setValue((CodedTerm) value);
			break;
		default:
			throw new IllegalArgumentException("Unknown field: " + formField.getLabel());
		}
	}

	@Override
	public Object getFieldValue(TemplateFormField formField) {
		Component comp = getFieldComponent(formField);
		switch (formField) {
		case NAME:
			return ((JTextComponent) comp).getText();
		case DESCRIPTION:
			return ((JTextComponent) comp).getText();
		case AUTHORS:
			return ((JTextComponent) comp).getText();
		case MODALITY:
			return ((JComboBox) comp).getSelectedItem();
		case PRECEDING_ANNOTATION:
			return ((JComboBox) comp).getSelectedItem();
		case UID:
			return ((JTextComponent) comp).getText();
		case CREATION_DATE:
			return ((JFormattedTextField) comp).getValue();
		case VERSION:
			return ((JTextComponent) comp).getText();
		case TERM_BLOCK:
			return ((LexiconTermEdit) comp).getValue();
		default:
			throw new IllegalArgumentException("Unknown field: " + formField.getLabel());
		}
	}

	@Override
	public void setSelectLexiconCommand(Command command) {
		lexiconTermEdit.setSelectLexiconCommand(command);
	}
	
}
