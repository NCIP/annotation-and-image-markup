/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.template.form.impl;

import static edu.stanford.isis.atb.ui.view.template.form.AlgorithmTypeFormView.AlgorithmTypeFormField.ALGORITHM_NAME;
import static edu.stanford.isis.atb.ui.view.template.form.AlgorithmTypeFormView.AlgorithmTypeFormField.ALGORITHM_VERSION;
import static edu.stanford.isis.atb.ui.view.template.form.AlgorithmTypeFormView.AlgorithmTypeFormField.DESCRIPTION;
import static edu.stanford.isis.atb.ui.view.template.form.AlgorithmTypeFormView.AlgorithmTypeFormField.MATH_ML;
import static edu.stanford.isis.atb.ui.view.template.form.AlgorithmTypeFormView.AlgorithmTypeFormField.TERM_BLOCK;
import static edu.stanford.isis.atb.ui.view.template.form.AlgorithmTypeFormView.AlgorithmTypeFormField.UNIQUE_IDENTIFIER;

import java.awt.Component;

import javax.swing.text.JTextComponent;

import edu.stanford.isis.atb.domain.template.CodedTerm;
import edu.stanford.isis.atb.service.Command;
import edu.stanford.isis.atb.ui.view.base.AbstractEditFormView;
import edu.stanford.isis.atb.ui.view.template.form.AlgorithmTypeFormView;
import edu.stanford.isis.atb.ui.view.template.form.AlgorithmTypeFormView.AlgorithmTypeFormField;
import edu.stanford.isis.atb.ui.view.widget.lexicon.LexiconTermEdit;

/**
 * @author Vitaliy Semeshko
 */
public class AlgorithmTypeFormViewImpl extends AbstractEditFormView<AlgorithmTypeFormField> 
		implements AlgorithmTypeFormView {

	private LexiconTermEdit lexiconTermEdit = new LexiconTermEdit();
	
	public AlgorithmTypeFormViewImpl() {
		addBlock(TERM_BLOCK, lexiconTermEdit);
		addRow(DESCRIPTION, textArea(3), Mode.M_EN_EN);
		addRow(UNIQUE_IDENTIFIER, textField(), Mode.NM_EN_EN);
		addRow(ALGORITHM_NAME, textField(), Mode.NM_EN_EN);
		addRow(ALGORITHM_VERSION, textField(), Mode.NM_EN_EN);
		addRow(MATH_ML, textField(), Mode.NM_EN_EN);
		
		buildForm();
	}
	
	@Override
	public void setFieldValue(AlgorithmTypeFormField formField, Object value) {
		Component comp = getFieldComponent(formField);
		switch (formField) {
		case TERM_BLOCK:
			((LexiconTermEdit) comp).setValue((CodedTerm) value);
			break;
		case DESCRIPTION:
		case UNIQUE_IDENTIFIER:
		case ALGORITHM_NAME:
		case ALGORITHM_VERSION:
		case MATH_ML:
			((JTextComponent) comp).setText(value.toString());
			break;
		default:
			throw new IllegalArgumentException("Unknown field: " + formField.getLabel());
		}
	}

	@Override
	public Object getFieldValue(AlgorithmTypeFormField formField) {
		Component comp = getFieldComponent(formField);
		switch (formField) {
		case TERM_BLOCK:
			return ((LexiconTermEdit) comp).getValue();
		case DESCRIPTION:
		case UNIQUE_IDENTIFIER:
		case ALGORITHM_NAME:
		case ALGORITHM_VERSION:
		case MATH_ML:
			return ((JTextComponent) comp).getText();
		default:
			throw new IllegalArgumentException("Unknown field: " + formField.getLabel());
		}
	}

	@Override
	public void setSelectLexiconCommand(Command command) {
		lexiconTermEdit.setSelectLexiconCommand(command);
	}

}
