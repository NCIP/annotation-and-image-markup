/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.widget.lexicon;

import static edu.stanford.isis.atb.ui.Const.FRM_LBL_CODE_MEANING;
import static edu.stanford.isis.atb.ui.Const.TPL_FORM_LABEL;

import java.awt.GridBagConstraints;
import java.awt.Insets;

import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.border.TitledBorder;

import edu.stanford.isis.atb.ui.Const;
import edu.stanford.isis.atb.ui.util.UIUtil;

/**
 * @author Vitaliy Semeshko
 */
public class LexiconTermView extends JPanel {

	private JTextField txtCodeMeaning = new JTextField();
	private JTextField txtCodeValue = new JTextField();
	private JTextField txtSchemaDesignator = new JTextField();
	private JTextField txtSchemaVersion = new JTextField();
	private JTextArea taDescription = new JTextArea();
	
	public LexiconTermView() {
		setBorder(new TitledBorder(Const.LBL_LEXICON_TERM));
	
		txtCodeMeaning.setEditable(false);
		txtCodeValue.setEditable(false);
		txtSchemaDesignator.setEditable(false);
		txtSchemaVersion.setEditable(false);
		taDescription.setEditable(false);
		taDescription.setLineWrap(true);
		
		setLayout(UIUtil.createFormLayout(5));
		
		GridBagConstraints gbcLabelCodeMeaning = new GridBagConstraints();
		gbcLabelCodeMeaning.insets = new Insets(10, 10, 5, 8);
		gbcLabelCodeMeaning.anchor = GridBagConstraints.EAST;
		gbcLabelCodeMeaning.gridx = 0;
		gbcLabelCodeMeaning.gridy = 0;
		add(label(String.format(TPL_FORM_LABEL, FRM_LBL_CODE_MEANING)), gbcLabelCodeMeaning);
		
		GridBagConstraints gbcTextCodeMeaning = new GridBagConstraints();
		gbcTextCodeMeaning.insets = new Insets(10, 0, 5, 10);
		gbcTextCodeMeaning.fill = GridBagConstraints.HORIZONTAL;
		gbcTextCodeMeaning.gridx = 1;
		gbcTextCodeMeaning.gridy = 0;
		add(txtCodeMeaning, gbcTextCodeMeaning);
		txtCodeMeaning.setColumns(10);
		
		GridBagConstraints gbcLabelCodeValue = new GridBagConstraints();
		gbcLabelCodeValue.anchor = GridBagConstraints.EAST;
		gbcLabelCodeValue.insets = new Insets(0, 10, 5, 8);
		gbcLabelCodeValue.gridx = 0;
		gbcLabelCodeValue.gridy = 1;
		add(label(Const.FRM_LBL_CODE_VALUE), gbcLabelCodeValue);
		
		GridBagConstraints gbcTextCodeValue = new GridBagConstraints();
		gbcTextCodeValue.insets = new Insets(0, 0, 5, 10);
		gbcTextCodeValue.fill = GridBagConstraints.HORIZONTAL;
		gbcTextCodeValue.gridx = 1;
		gbcTextCodeValue.gridy = 1;
		add(txtCodeValue, gbcTextCodeValue);
		txtCodeValue.setColumns(10);
		
		GridBagConstraints gbcLabelSchemaDesignator = new GridBagConstraints();
		gbcLabelSchemaDesignator.insets = new Insets(0, 10, 5, 8);
		gbcLabelSchemaDesignator.anchor = GridBagConstraints.EAST;
		gbcLabelSchemaDesignator.gridx = 0;
		gbcLabelSchemaDesignator.gridy = 2;
		add(label(Const.FRM_LBL_SCHEMA_DESIGNATOR), gbcLabelSchemaDesignator);
		
		GridBagConstraints gbcTextSchemaDesignator = new GridBagConstraints();
		gbcTextSchemaDesignator.insets = new Insets(0, 0, 5, 10);
		gbcTextSchemaDesignator.fill = GridBagConstraints.HORIZONTAL;
		gbcTextSchemaDesignator.gridx = 1;
		gbcTextSchemaDesignator.gridy = 2;
		add(txtSchemaDesignator, gbcTextSchemaDesignator);
		txtSchemaDesignator.setColumns(10);
		
		GridBagConstraints gbcLabelSchemaVersion = new GridBagConstraints();
		gbcLabelSchemaVersion.anchor = GridBagConstraints.EAST;
		gbcLabelSchemaVersion.insets = new Insets(0, 10, 0, 8);
		gbcLabelSchemaVersion.gridx = 0;
		gbcLabelSchemaVersion.gridy = 3;
		add(label(Const.FRM_LBL_SCHEMA_VERSION), gbcLabelSchemaVersion);
		
		GridBagConstraints gbcTextSchemaVersion = new GridBagConstraints();
		gbcTextSchemaVersion.insets = new Insets(0, 0, 5, 10);
		gbcTextSchemaVersion.fill = GridBagConstraints.HORIZONTAL;
		gbcTextSchemaVersion.gridx = 1;
		gbcTextSchemaVersion.gridy = 3;
		add(txtSchemaVersion, gbcTextSchemaVersion);
		txtSchemaVersion.setColumns(10);
		
		GridBagConstraints gbcLabelDescription = new GridBagConstraints();
		gbcLabelDescription.anchor = GridBagConstraints.NORTHEAST;
		gbcLabelDescription.insets = new Insets(0, 10, 0, 8);
		gbcLabelDescription.gridx = 0;
		gbcLabelDescription.gridy = 4;
		add(label(Const.FRM_LBL_DESCRIPTION), gbcLabelDescription);
		
		GridBagConstraints gbcTextDescription = new GridBagConstraints();
		gbcTextDescription.insets = new Insets(0, 0, 5, 10);
		gbcTextDescription.fill = GridBagConstraints.HORIZONTAL;
		gbcTextDescription.gridx = 1;
		gbcTextDescription.gridy = 4;
		add(new JScrollPane(taDescription), gbcTextDescription);
		taDescription.setColumns(10);
		taDescription.setRows(5);
	}
	
	private JLabel label(String text) {
		return new JLabel(String.format(Const.TPL_FORM_LABEL, text));
	}
	
	public void setCodeMeaning(String codeMeaning) {
		txtCodeMeaning.setText(codeMeaning);
		txtCodeMeaning.setCaretPosition(0);
	}
	
	public void setCodeValue(String codeValue) {
		txtCodeValue.setText(codeValue);
		txtCodeValue.setCaretPosition(0);
	}
	
	public void setSchemaDesignator(String schemaDesignator) {
		txtSchemaDesignator.setText(schemaDesignator);
		txtSchemaDesignator.setCaretPosition(0);
	}
	
	public void setSchemaVersion(String schemaVersion) {
		txtSchemaVersion.setText(schemaVersion);
		txtSchemaVersion.setCaretPosition(0);
	}
	
	public void setDescription(String description) {
		taDescription.setText(description);
		taDescription.setCaretPosition(0);
	}
	
	public void clear() {
		txtCodeMeaning.setText(Const.EMPTY);
		txtCodeValue.setText(Const.EMPTY);
		txtSchemaDesignator.setText(Const.EMPTY);
		txtSchemaVersion.setText(Const.EMPTY);
		taDescription.setText(Const.EMPTY);
	}
	
}
