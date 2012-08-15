/*
 * Copyright Notice. Copyright 2011 Northwestern University and Stanford
 * University (“caBIG® Participant”). AIM Template Enterprise Service conforms
 * to caBIG® technical specifications and is part of the caBIG® initiative. The
 * software subject to this notice and license includes human readable source
 * code form, machine readable, binary, object code form and related
 * documentation (the “caBIG® Software”).
 *
 * This caBIG® Software License (the “License”) is between the National Cancer
 * Institute (NCI) and You. “You (or “Your”) shall mean a person or an entity,
 * and all other entities that control, are controlled by, or are under common
 * control with the entity. “Control” for purposes of this definition means (i)
 * the direct or indirect power to cause the direction or management of such
 * entity, whether by contract or otherwise, or (ii) ownership of fifty percent
 * (50%) or more of the outstanding shares, or (iii) beneficial ownership of
 * such entity.
 *
 * Provided that You agree to the conditions described below, NCI grants You a
 * non-exclusive, worldwide, perpetual, fully-paid-up, no-charge, irrevocable,
 * transferable and royalty-free right and license in its rights in the caBIG®
 * Software, including any copyright or patent rights therein, to (i) use,
 * install, disclose, access, operate, execute, reproduce, copy, modify,
 * translate, market, publicly display, publicly perform, and prepare
 * derivative works of the caBIG® Software in any manner and for any purpose,
 * and to have or permit others to do so; (ii) make, have made, use, practice,
 * sell, and offer for sale, import, and/or otherwise dispose of caBIG®
 * Software (or portions thereof); (iii) distribute and have distributed to and
 * by third parties the caBIG® Software and any modifications and derivative
 * works thereof; and (iv) sublicense the foregoing rights set out in (i), (ii)
 * and (iii) to third parties, including the right to license such rights to
 * further third parties. For sake of clarity, and not by way of limitation,
 * NCI shall have no right of accounting or right of payment from You or Your
 * sublicensees for the rights granted under this License. This License is
 * granted at no charge to You. Your downloading, copying, modifying,
 * displaying, distributing or use of caBIG® Software constitutes acceptance of
 * all of the terms and conditions of this Agreement. If you do not agree to
 * such terms and conditions, you have no right to download, copy, modify,
 * display, distribute or use the caBIG® Software.
 *
 * Your redistributions of the source code for the caBIG® Software must retain
 * the above copyright notice, this list of conditions and the disclaimer and
 * limitation of liability of Article 6 below. Your redistributions in object
 * code form must reproduce the above copyright notice, this list of conditions
 * and the disclaimer of Article 6 in the documentation and/or other materials
 * provided with the distribution, if any.
 *
 * Your end-user documentation included with the redistribution, if any, must
 * include the following acknowledgment: “This product includes software
 * developed by Danny Korenblum, Alan Snyder, Vitaliy Semeshko, Vladimir Kleper
 * and Pattanasak Mongkolwat, Northwestern University and Stanford University.”
 * If You do not include such end-user documentation, You shall include this
 * acknowledgment in the caBIG® Software itself, wherever such third-party
 * acknowledgments normally appear.
 *
 * You may not use the names “Northwestern University”, “Stanford University”,
 * “The National Cancer Institute”, “NCI”, “Cancer Bioinformatics Grid” or
 * “caBIG®” to endorse or promote products derived from this caBIG® Software.
 * This License does not authorize You to use any trademarks, service marks,
 * trade names, logos or product names of either caBIG® Participant, NCI or
 * caBIG®, except as required to comply with the terms of this License.
 *
 * For sake of clarity, and not by way of limitation, You are not prohibited by
 * this License from incorporating this caBIG® Software into Your proprietary
 * programs and into any third party proprietary programs. However, if You
 * incorporate the caBIG® Software into third party proprietary programs, You
 * agree that You are solely responsible for obtaining any permission from such
 * third parties required to incorporate the caBIG® Software into such third
 * party proprietary programs and for informing Your sublicensees, including
 * without limitation Your end-users, of their obligation to secure any
 * required permissions from such third parties before incorporating the caBIG®
 * Software into such third party proprietary software programs. In the event
 * that You fail to obtain such permissions, You agree to indemnify NCI for any
 * claims against NCI by such third parties, except to the extent prohibited by
 * law, resulting from Your failure to obtain such permissions.
 * For sake of clarity, and not by way of limitation, You may add Your own
 * copyright statement to Your modifications and to the derivative works, and
 * You may provide additional or different license terms and conditions in
 * Your sublicenses of modifications of the caBIG® Software, or any derivative
 * works of the caBIG® Software as a whole, provided Your use, reproduction,
 * and distribution of the Work otherwise complies with the conditions stated
 * in this License.
 *
 * THIS caBIG® SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES (INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE) ARE
 * DISCLAIMED. IN NO EVENT SHALL NCI OR THE NORTHWESTERN UNIVERSITY OR ITS
 * AFFILIATES BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS caBIG® SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
