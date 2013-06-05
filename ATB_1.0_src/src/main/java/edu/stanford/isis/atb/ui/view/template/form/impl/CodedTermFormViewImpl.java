/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.template.form.impl;

import static edu.stanford.isis.atb.ui.view.template.form.CodedTermFormView.CodedTermFormField.TERM_BLOCK;

import java.awt.Component;

import edu.stanford.isis.atb.domain.template.CodedTerm;
import edu.stanford.isis.atb.service.Command;
import edu.stanford.isis.atb.ui.view.base.AbstractEditFormView;
import edu.stanford.isis.atb.ui.view.template.form.CodedTermFormView;
import edu.stanford.isis.atb.ui.view.template.form.CodedTermFormView.CodedTermFormField;
import edu.stanford.isis.atb.ui.view.widget.lexicon.LexiconTermEdit;

/**
 * @author Vitaliy Semeshko
 */
public class CodedTermFormViewImpl extends AbstractEditFormView<CodedTermFormField> implements CodedTermFormView {

	private LexiconTermEdit lexiconTermEdit = new LexiconTermEdit();
	
	public CodedTermFormViewImpl() {
		addBlock(TERM_BLOCK, lexiconTermEdit);
		
		buildForm();
	}
	
	@Override
	public void setFieldValue(CodedTermFormField formField, Object value) {
		Component comp = getFieldComponent(formField);
		switch (formField) {
		case TERM_BLOCK:
			((LexiconTermEdit) comp).setValue((CodedTerm) value);
			break;
		default:
			throw new IllegalArgumentException("Unknown field: " + formField.getLabel());
		}
	}

	@Override
	public Object getFieldValue(CodedTermFormField formField) {
		Component comp = getFieldComponent(formField);
		switch (formField) {
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
