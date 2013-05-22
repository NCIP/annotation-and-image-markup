/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.widget.group;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.text.SimpleDateFormat;

import javax.swing.BoxLayout;
import javax.swing.Icon;
import javax.swing.JFormattedTextField;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextField;
import javax.swing.border.EmptyBorder;

import edu.stanford.isis.atb.domain.template.TemplateContainer;
import edu.stanford.isis.atb.domain.template.TemplateRef;
import edu.stanford.isis.atb.ui.Const;
import edu.stanford.isis.atb.ui.view.resources.MiscImageBundle;
import edu.stanford.isis.atb.ui.view.widget.table.GenericTable;
import edu.stanford.isis.atb.ui.view.widget.table.column.IconColumn;
import edu.stanford.isis.atb.ui.view.widget.table.column.IconColumn.IconColumnValue;
import edu.stanford.isis.atb.ui.view.widget.table.column.TextColumn.TextColumnValue;

/**
 * @author Vitaliy Semeshko
 */
public class GroupMembers extends JPanel {

	private GenericTable<TemplateRef> templatesTable = new GenericTable<TemplateRef>();
	
	private JTextField groupText;
	private JTextField versionText;
	private JTextField authorText;
	private JFormattedTextField dateFormattedText;
	private JTextField uidText;
	private JTextField descriptionText;
	
	public GroupMembers() {
		setLayout(new BorderLayout());
		JPanel header = new JPanel();
		add(header, BorderLayout.NORTH);
		
		createGroupInfoHeader(header);
		
		JScrollPane scrollPane = new JScrollPane();
		scrollPane.setBorder(null);
		add(scrollPane, BorderLayout.CENTER);
		scrollPane.setViewportView(templatesTable);
		scrollPane.getViewport().setBackground(Color.white);
		
		IconColumn<TemplateRef> iconColumn = new IconColumn<TemplateRef>(new IconColumnValue<TemplateRef>() {
			private Icon warningIcon = MiscImageBundle.getInstance().getValidationWarningIcon().loadIcon();
			
			@Override
			public Icon getValue(TemplateRef source) {
				return source.isValid() ? null : warningIcon;
			}
		}, Const.EMPTY, 20);
		templatesTable.addGenericColumn(iconColumn, false);
		
		templatesTable.addTextColumn(new TextColumnValue<TemplateRef>() {
			@Override
			public String getValue(TemplateRef source) {
				return source.getName();
			}
		}, Const.COLUMN_NAME, 140, true, false);
		
		templatesTable.addTextColumn(new TextColumnValue<TemplateRef>() {
			@Override
			public String getValue(TemplateRef source) {
				return source.getCodeMeaning();
			}
		}, Const.COLUMN_CODE_MEANING, 180, false);
		
		templatesTable.addTextColumn(new TextColumnValue<TemplateRef>() {
			@Override
			public String getValue(TemplateRef source) {
				return source.getAuthors();
			}
		}, Const.COLUMN_AUTH, 80, false);
		
		templatesTable.addTextColumn(new TextColumnValue<TemplateRef>() {
			@Override
			public String getValue(TemplateRef source) {
				return source.getDescription();
			}
		}, Const.COLUMN_DESCRIPTION, 360, false);
		
	}
	
	public void setTemplateContainer(TemplateContainer container) {
		groupText.setText(container.getName());
		authorText.setText(container.getAuthors());
		dateFormattedText.setValue(container.getCreationDate());
		versionText.setText(container.getVersion());
		descriptionText.setText(container.getDescription());
		descriptionText.setCaretPosition(0);
		uidText.setText(container.getUid().getOriginal());
		uidText.setCaretPosition(0);
		
		templatesTable.setValues(container.getTemplates());
	}
	
	public void clearContainerDetails() {
		groupText.setText(Const.EMPTY);
		authorText.setText(Const.EMPTY);
		dateFormattedText.setValue(null);
		versionText.setText(Const.EMPTY);
		descriptionText.setText(Const.EMPTY);
		uidText.setText(Const.EMPTY);
		
		templatesTable.clear();
		templatesTable.refresh();
	}
	
	private void createGroupInfoHeader(JPanel header) {
		header.setBorder(new EmptyBorder(new Insets(4, 4, 4, 4)));
		header.setLayout(new BoxLayout(header, BoxLayout.Y_AXIS));
		
		JPanel groupInfoTop = new JPanel();
		groupInfoTop.setBorder(new EmptyBorder(new Insets(0, 0, 4, 0)));
		header.add(groupInfoTop);
		GridBagLayout gbl_groupInfoTop = new GridBagLayout();
		gbl_groupInfoTop.columnWidths = new int[]{0, 0, 0};
		gbl_groupInfoTop.rowHeights = new int[]{0, 0};
		gbl_groupInfoTop.columnWeights = new double[]{0.0, 1.0, Double.MIN_VALUE};
		gbl_groupInfoTop.rowWeights = new double[]{0.0, Double.MIN_VALUE};
		groupInfoTop.setLayout(gbl_groupInfoTop);
		
		JLabel lblGroup = new JLabel(Const.FRM_LBL_GROUP);
		GridBagConstraints gbc_lblGroup = new GridBagConstraints();
		gbc_lblGroup.insets = new Insets(0, 0, 0, 5);
		gbc_lblGroup.anchor = GridBagConstraints.EAST;
		gbc_lblGroup.gridx = 0;
		gbc_lblGroup.gridy = 0;
		groupInfoTop.add(lblGroup, gbc_lblGroup);
		
		groupText = new JTextField();
		groupText.setEditable(false);
		GridBagConstraints gbc_txtGroup = new GridBagConstraints();
		gbc_txtGroup.fill = GridBagConstraints.HORIZONTAL;
		gbc_txtGroup.gridx = 1;
		gbc_txtGroup.gridy = 0;
		groupInfoTop.add(groupText, gbc_txtGroup);
		groupText.setColumns(10);
		
		JPanel groupInfoMiddle = new JPanel();
		groupInfoMiddle.setBorder(new EmptyBorder(new Insets(0, 0, 4, 0)));
		header.add(groupInfoMiddle);
		GridBagLayout gbl_groupInfoMiddle = new GridBagLayout();
		gbl_groupInfoMiddle.columnWidths = new int[]{0, 0, 0, 0, 0, 0, 0};
		gbl_groupInfoMiddle.rowHeights = new int[]{0, 0};
		gbl_groupInfoMiddle.columnWeights = new double[]{0.0, 0.5, 0.0, 0.0, 0.0, 0.0, Double.MIN_VALUE};
		gbl_groupInfoMiddle.rowWeights = new double[]{0.0, Double.MIN_VALUE};
		groupInfoMiddle.setLayout(gbl_groupInfoMiddle);
		
		JLabel lblAuthor = new JLabel(Const.FRM_LBL_AUTHORS);
		GridBagConstraints gbc_lblAuthor = new GridBagConstraints();
		gbc_lblAuthor.anchor = GridBagConstraints.EAST;
		gbc_lblAuthor.insets = new Insets(0, 0, 0, 5);
		gbc_lblAuthor.gridx = 0;
		gbc_lblAuthor.gridy = 0;
		groupInfoMiddle.add(lblAuthor, gbc_lblAuthor);
		
		authorText = new JTextField();
		authorText.setColumns(1);
		authorText.setEditable(false);
		GridBagConstraints gbc_txtAuthor = new GridBagConstraints();
		gbc_txtAuthor.insets = new Insets(0, 0, 0, 5);
		gbc_txtAuthor.fill = GridBagConstraints.HORIZONTAL;
		gbc_txtAuthor.gridx = 1;
		gbc_txtAuthor.gridy = 0;
		groupInfoMiddle.add(authorText, gbc_txtAuthor);
		
		JLabel lblDate = new JLabel(Const.FRM_LBL_DATE);
		GridBagConstraints gbc_lblDate = new GridBagConstraints();
		gbc_lblDate.anchor = GridBagConstraints.EAST;
		gbc_lblDate.insets = new Insets(0, 0, 0, 5);
		gbc_lblDate.gridx = 2;
		gbc_lblDate.gridy = 0;
		groupInfoMiddle.add(lblDate, gbc_lblDate);
		
		dateFormattedText = new JFormattedTextField(new SimpleDateFormat(Const.FMT_DATE_DISPLAY));
		dateFormattedText.setEditable(false);
		GridBagConstraints gbc_txtDate = new GridBagConstraints();
		gbc_txtDate.anchor = GridBagConstraints.WEST;
		gbc_txtDate.insets = new Insets(0, 0, 0, 5);
		gbc_txtDate.gridx = 3;
		gbc_txtDate.gridy = 0;
		groupInfoMiddle.add(dateFormattedText, gbc_txtDate);
		dateFormattedText.setColumns(7);
		
		JLabel lblVersion = new JLabel(Const.FRM_LBL_VERSION);
		GridBagConstraints gbc_lblVersion = new GridBagConstraints();
		gbc_lblVersion.fill = GridBagConstraints.HORIZONTAL;
		gbc_lblVersion.insets = new Insets(0, 0, 0, 5);
		gbc_lblVersion.anchor = GridBagConstraints.WEST;
		gbc_lblVersion.gridx = 4;
		gbc_lblVersion.gridy = 0;
		groupInfoMiddle.add(lblVersion, gbc_lblVersion);
		
		versionText = new JTextField();
		versionText.setEditable(false);
		GridBagConstraints gbc_txtVersion = new GridBagConstraints();
		gbc_txtVersion.anchor = GridBagConstraints.WEST;
		gbc_txtVersion.gridx = 5;
		gbc_txtVersion.gridy = 0;
		groupInfoMiddle.add(versionText, gbc_txtVersion);
		versionText.setColumns(4);
		
		JPanel uidInfo = new JPanel();
		uidInfo.setBorder(new EmptyBorder(new Insets(0, 0, 4, 0)));
		header.add(uidInfo);
		GridBagLayout gblUidInfoTop = new GridBagLayout();
		gblUidInfoTop.columnWidths = new int[]{0, 0, 0};
		gblUidInfoTop.rowHeights = new int[]{0, 0};
		gblUidInfoTop.columnWeights = new double[]{0.0, 1.0, Double.MIN_VALUE};
		gblUidInfoTop.rowWeights = new double[]{0.0, Double.MIN_VALUE};
		uidInfo.setLayout(gblUidInfoTop);
		
		JLabel uidLabel = new JLabel(Const.FRM_LBL_UID);
		GridBagConstraints gbcUidLabel = new GridBagConstraints();
		gbcUidLabel.anchor = GridBagConstraints.WEST;
		gbcUidLabel.insets = new Insets(0, 0, 0, 5);
		gbcUidLabel.gridx = 0;
		gbcUidLabel.gridy = 0;
		uidInfo.add(uidLabel, gbcUidLabel);
		
		uidText = new JTextField();
		uidText.setEditable(false);
		GridBagConstraints gbcUidText = new GridBagConstraints();
		gbcUidText.fill = GridBagConstraints.HORIZONTAL;
		gbcUidText.gridx = 1;
		gbcUidText.gridy = 0;
		uidInfo.add(uidText, gbcUidText);
		uidText.setColumns(10);
		
		JPanel groupInfoBottom = new JPanel();
		header.add(groupInfoBottom);
		GridBagLayout gbl_groupInfoBottom = new GridBagLayout();
		gbl_groupInfoBottom.columnWidths = new int[]{0, 0, 0};
		gbl_groupInfoBottom.rowHeights = new int[]{0, 0};
		gbl_groupInfoBottom.columnWeights = new double[]{0.0, 1.0, Double.MIN_VALUE};
		gbl_groupInfoBottom.rowWeights = new double[]{1.0, Double.MIN_VALUE};
		groupInfoBottom.setLayout(gbl_groupInfoBottom);
		
		JLabel lblDescription = new JLabel(Const.FRM_LBL_DESCRIPTION);
		GridBagConstraints gbc_lblDescription = new GridBagConstraints();
		gbc_lblDescription.anchor = GridBagConstraints.WEST;
		gbc_lblDescription.insets = new Insets(0, 0, 0, 5);
		gbc_lblDescription.gridx = 0;
		gbc_lblDescription.gridy = 0;
		groupInfoBottom.add(lblDescription, gbc_lblDescription);
		
		descriptionText = new JTextField();
		descriptionText.setEditable(false);
		GridBagConstraints gbc_txtDescription = new GridBagConstraints();
		gbc_txtDescription.fill = GridBagConstraints.HORIZONTAL;
		gbc_txtDescription.gridx = 1;
		gbc_txtDescription.gridy = 0;
		groupInfoBottom.add(descriptionText, gbc_txtDescription);
		descriptionText.setColumns(10);
	}
	
}
