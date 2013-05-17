/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.template.form.impl;

import static edu.stanford.isis.atb.ui.view.template.form.TagFormView.TagFormField.NAME_TERM_BLOCK;
import static edu.stanford.isis.atb.ui.view.template.form.TagFormView.TagFormField.STRING_VALUE;
import static edu.stanford.isis.atb.ui.view.template.form.TagFormView.TagFormField.VALUE_MODE_SWITCHER;
import static edu.stanford.isis.atb.ui.view.template.form.TagFormView.TagFormField.VALUE_TERM_BLOCK;

import java.awt.Component;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;

import javax.swing.BoxLayout;
import javax.swing.ButtonGroup;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.JTextField;
import javax.swing.text.JTextComponent;

import edu.stanford.isis.atb.domain.template.CodedTerm;
import edu.stanford.isis.atb.service.Command;
import edu.stanford.isis.atb.ui.Const;
import edu.stanford.isis.atb.ui.view.base.AbstractEditFormView;
import edu.stanford.isis.atb.ui.view.template.form.TagFormView;
import edu.stanford.isis.atb.ui.view.template.form.TagFormView.TagFormField;
import edu.stanford.isis.atb.ui.view.widget.lexicon.LexiconTermEdit;

/**
 * @author Vitaliy Semeshko
 */
public class TagFormViewImpl extends AbstractEditFormView<TagFormField> implements TagFormView {

	private LexiconTermEdit lxTagName = new LexiconTermEdit(Const.FRM_LBL_TAG_NAME);
	private LexiconTermEdit lxTagValue = new LexiconTermEdit(Const.FRM_LBL_TAG_VALUE);
	private ValueModeSwitcher valueModeSwitcher = new ValueModeSwitcher();
	private JTextField txtTagValue = textField();
	
	public TagFormViewImpl() {
		addBlock(NAME_TERM_BLOCK, lxTagName);
		addRow(VALUE_MODE_SWITCHER, valueModeSwitcher, Mode.NM_EN_EN);
		addRow(STRING_VALUE, txtTagValue, Mode.NM_EN_EN);
		addBlock(VALUE_TERM_BLOCK, lxTagValue);
		
		valueModeSwitcher.setStringValueSelectionListener(new ItemListener() {
			@Override
			public void itemStateChanged(ItemEvent e) {
				if (e.getStateChange() == ItemEvent.SELECTED) {
					txtTagValue.setEnabled(true);
					lxTagValue.setEnabled(false);
					lxTagValue.clearValue();
				}
			}
		});
		
		valueModeSwitcher.setLexiconTermValueSelectionListener(new ItemListener() {
			@Override
			public void itemStateChanged(ItemEvent e) {
				if (e.getStateChange() == ItemEvent.SELECTED) {
					txtTagValue.setEnabled(false);
					lxTagValue.setEnabled(true);
					txtTagValue.setText(Const.EMPTY);
				}
			}
		});
		
		buildForm();
	}
	
	@Override
	public void setFieldValue(TagFormField formField, Object value) {
		Component comp = getFieldComponent(formField);
		switch (formField) {
		case NAME_TERM_BLOCK:
		case VALUE_TERM_BLOCK:
			((LexiconTermEdit) comp).setValue((CodedTerm) value);
			break;
		case VALUE_MODE_SWITCHER:
			((ValueModeSwitcher) comp).setValueMode((ValueMode) value);
			break;
		case STRING_VALUE:
			((JTextComponent) comp).setText(value.toString());
			break;
		default:
			throw new IllegalArgumentException("Unknown field: " + formField.getLabel());
		}
	}

	@Override
	public Object getFieldValue(TagFormField formField) {
		Component comp = getFieldComponent(formField);
		switch (formField) {
		case NAME_TERM_BLOCK:
		case VALUE_TERM_BLOCK:
			return ((LexiconTermEdit) comp).getValue();
		case VALUE_MODE_SWITCHER:
			return ((ValueModeSwitcher) comp).getValueMode();
		case STRING_VALUE:
			return ((JTextComponent) comp).getText();
		default:
			throw new IllegalArgumentException("Unknown field: " + formField.getLabel());
		}
	}

	@Override
	public void setSelectLexiconTagNameCommand(Command command) {
		lxTagName.setSelectLexiconCommand(command);
	}
	
	@Override
	public void setSelectLexiconTagValueCommand(Command command) {
		lxTagValue.setSelectLexiconCommand(command);
	}

	private class ValueModeSwitcher extends JPanel {
		
		private JRadioButton rbStringValue = new JRadioButton(Const.FRM_LBL_USE_STRING_VALUE);
		private JRadioButton rbLexiconTermValue = new JRadioButton(Const.FRM_LBL_USE_LEXICON_TERM);
		
		public ValueModeSwitcher() {
			setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
			
			ButtonGroup group = new ButtonGroup();
		    group.add(rbStringValue);
		    group.add(rbLexiconTermValue);
		    
		    add(rbStringValue);
		    add(rbLexiconTermValue);
		}
		
		public void setValueMode(ValueMode mode) {
			rbStringValue.setSelected(mode == ValueMode.STRING);
			rbLexiconTermValue.setSelected(mode == ValueMode.LEXICON_TERM);
		}
		
		public ValueMode getValueMode() {
			return rbStringValue.isSelected() ? ValueMode.STRING : ValueMode.LEXICON_TERM;
		}
		
		public void setStringValueSelectionListener(final ItemListener listener) {
			rbStringValue.addItemListener(listener);
		}
		
		public void setLexiconTermValueSelectionListener(final ItemListener listener) {
			rbLexiconTermValue.addItemListener(listener);
		}
		
	}
	
}
