/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.widget.lexicon;

import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.border.TitledBorder;

import org.apache.commons.lang3.StringUtils;

import edu.stanford.isis.atb.domain.template.CodedTerm;
import edu.stanford.isis.atb.service.Command;
import edu.stanford.isis.atb.system.exception.ATBException;
import edu.stanford.isis.atb.ui.Const;

/**
 * @author Vitaliy Semeshko
 */
public class LexiconTermEdit extends JPanel {

	private JTextField txtCodeMeaning = new JTextField();
	private JTextField txtCodeValue = new JTextField();
	private JTextField txtSchemaDesignator = new JTextField();
	private JTextField txtSchemaVersion = new JTextField();
	private JButton btnFindTerm = new JButton(Const.BTN_SELECT_TERM);
	
	private Command selectTermCommand;
	
	public LexiconTermEdit() {
		this(null);
	}
	
	public LexiconTermEdit(String name) {
		String title = Const.LBL_LEXICON_TERM + (StringUtils.isEmpty(name) ? "" : " (" + name + ")" );
		setBorder(new TitledBorder(title));
	
		txtCodeMeaning.setEditable(false);
		txtCodeValue.setEditable(false);
		txtSchemaDesignator.setEditable(false);
		txtSchemaVersion.setEditable(false);
		
		GridBagLayout gblRoot = new GridBagLayout();
		gblRoot.columnWidths = new int[] {0, 0, 0};
		gblRoot.rowHeights = new int[] {0, 0, 0, 0, 0};
		gblRoot.columnWeights = new double[] {0.0, 1.0, Double.MIN_VALUE};
		gblRoot.rowWeights = new double[] {0.0, 0.0, 0.0, 0.0, Double.MIN_VALUE};
		setLayout(gblRoot);
		
		GridBagConstraints gbcLabelCodeMeaning = new GridBagConstraints();
		gbcLabelCodeMeaning.insets = new Insets(10, 10, 5, 8);
		gbcLabelCodeMeaning.anchor = GridBagConstraints.EAST;
		gbcLabelCodeMeaning.gridx = 0;
		gbcLabelCodeMeaning.gridy = 0;
		add(mandatoryLabel(Const.FRM_LBL_CODE_MEANING), gbcLabelCodeMeaning);
		
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
		add(mandatoryLabel(Const.FRM_LBL_CODE_VALUE), gbcLabelCodeValue);
		
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
		add(mandatoryLabel(Const.FRM_LBL_SCHEMA_DESIGNATOR), gbcLabelSchemaDesignator);
		
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
		
		GridBagConstraints gbcButtonFindTerm = new GridBagConstraints();
		gbcButtonFindTerm.insets = new Insets(0, 0, 5, 10);
		gbcButtonFindTerm.anchor = GridBagConstraints.EAST;
		gbcButtonFindTerm.gridx = 1;
		gbcButtonFindTerm.gridy = 4;
		add(btnFindTerm, gbcButtonFindTerm);
		
		btnFindTerm.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				if (selectTermCommand != null) {
					selectTermCommand.execute();
				}
			}
		});
	}
	
	private JLabel label(String text) {
		return new JLabel(String.format(Const.TPL_FORM_LABEL, text));
	}
	
	private JLabel mandatoryLabel(String text) {
		return new JLabel(String.format(Const.TPL_FORM_LABEL_MANDATORY, text));
	}
	
	public void setValue(CodedTerm value) {
		if (value == null) {
			throw new ATBException("Empty coded term.");
		}
		
		txtCodeMeaning.setText(value.getCodeMeaning());
		txtCodeMeaning.setCaretPosition(0);
		txtCodeValue.setText(value.getCodeValue());
		txtCodeValue.setCaretPosition(0);
		txtSchemaDesignator.setText(value.getSchemaDesignator());
		txtSchemaDesignator.setCaretPosition(0);
		txtSchemaVersion.setText(value.getSchemaVersion());
		txtSchemaVersion.setCaretPosition(0);
	}
	
	public CodedTerm getValue() {
		CodedTerm value = new CodedTerm();
		value.setCodeMeaning(txtCodeMeaning.getText());
		value.setCodeValue(txtCodeValue.getText());
		value.setSchemaDesignator(txtSchemaDesignator.getText());
		value.setSchemaVersion(txtSchemaVersion.getText());
		return value;
	}
	
	public void clearValue() {
		txtCodeMeaning.setText(Const.EMPTY);
		txtCodeValue.setText(Const.EMPTY);
		txtSchemaDesignator.setText(Const.EMPTY);
		txtSchemaVersion.setText(Const.EMPTY);
	}
	
	public void setSelectLexiconCommand(Command command) {
		selectTermCommand = command;
	}
	
	@Override
	public void setEnabled(boolean enabled) {
		btnFindTerm.setEnabled(enabled);
	}
	
}
