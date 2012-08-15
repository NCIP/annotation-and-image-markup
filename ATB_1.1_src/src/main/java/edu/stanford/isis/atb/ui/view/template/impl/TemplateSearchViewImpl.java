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

package edu.stanford.isis.atb.ui.view.template.impl;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.Dialog.ModalityType;
import java.awt.Dimension;
import java.awt.GridBagConstraints;
import java.awt.Insets;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Collection;

import javax.swing.Icon;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextField;
import javax.swing.border.EmptyBorder;

import edu.stanford.isis.atb.domain.ats.TemplateSearchRequest;
import edu.stanford.isis.atb.domain.ats.TemplateSingleResult;
import edu.stanford.isis.atb.service.Command;
import edu.stanford.isis.atb.ui.Application;
import edu.stanford.isis.atb.ui.Const;
import edu.stanford.isis.atb.ui.util.UIUtil;
import edu.stanford.isis.atb.ui.view.AbstractView;
import edu.stanford.isis.atb.ui.view.resources.MiscImageBundle;
import edu.stanford.isis.atb.ui.view.template.TemplateSearchView;
import edu.stanford.isis.atb.ui.view.widget.EscapeDialog;
import edu.stanford.isis.atb.ui.view.widget.table.GenericTable;
import edu.stanford.isis.atb.ui.view.widget.table.column.CommandColumn;
import edu.stanford.isis.atb.ui.view.widget.table.column.CommandColumn.CommandColumnValue;
import edu.stanford.isis.atb.ui.view.widget.table.column.TextColumn.TextColumnValue;

/**
 * @author Vitaliy Semeshko
 */
public class TemplateSearchViewImpl extends AbstractView implements TemplateSearchView {

	private JPanel root = new JPanel(new BorderLayout());
	
	private EscapeDialog dialog = new EscapeDialog();
	
	private GenericTable<TemplateSingleResult> resultTable = new GenericTable<TemplateSingleResult>();

	private MiscImageBundle miscImages = MiscImageBundle.getInstance(); 
	
	private JButton searchButton = new JButton(Const.BTN_SEARCH, miscImages.getButtonSubmitIcon().loadIcon());

	private Command selectCommand;
	
	private JTextField nameText = new JTextField();
	private JTextField codeDescText = new JTextField();
	private JTextField descriptionText = new JTextField();
	private JTextField authorText = new JTextField();
	private JTextField diseaseText = new JTextField();
	private JTextField bodyPartText = new JTextField();
	private JComboBox modalityComboBox;
	
	public TemplateSearchViewImpl() {
		dialog.add(root);
		dialog.setSize(1000, 600);
		dialog.setMinimumSize(new Dimension(800, 400));
		dialog.setModalityType(ModalityType.APPLICATION_MODAL);
		initForm();
		initResultTable();
	}

	private void initForm() {
		JPanel search = new JPanel(new BorderLayout());
		JPanel form = new JPanel();
		JPanel buttons = new JPanel();
		
		form.add(initLeftForm(), BorderLayout.WEST);
		form.add(initRightForm(), BorderLayout.EAST);
		
		search.add(form, BorderLayout.CENTER);
		search.add(buttons, BorderLayout.SOUTH);
		
		JButton resetButton = new JButton(Const.BTN_RESET, miscImages.getButtonResetIcon().loadIcon());
		
		resetButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				clear();
			}
		});
		
		JButton cancelButton = new JButton(Const.BTN_CANCEL, miscImages.getButtonCancelIcon().loadIcon());
		
		cancelButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				dialog.setVisible(false);
			}
		});
		
		buttons.add(searchButton);
		buttons.add(resetButton);
		buttons.add(cancelButton);
		
		root.add(search, BorderLayout.NORTH);
	}
	
	private JPanel initLeftForm() {
		JPanel form = new JPanel(UIUtil.createFormLayout(4));
		
		GridBagConstraints gbcLabelTemplateName = new GridBagConstraints();
		gbcLabelTemplateName.insets = new Insets(10, 10, 5, 8);
		gbcLabelTemplateName.anchor = GridBagConstraints.EAST;
		gbcLabelTemplateName.gridx = 0;
		gbcLabelTemplateName.gridy = 0;
		form.add(label(Const.FRM_LBL_TEMPLATE_NAME), gbcLabelTemplateName);
		
		GridBagConstraints gbcTextTemplateName = new GridBagConstraints();
		gbcTextTemplateName.insets = new Insets(10, 0, 5, 10);
		gbcTextTemplateName.fill = GridBagConstraints.HORIZONTAL;
		gbcTextTemplateName.gridx = 1;
		gbcTextTemplateName.gridy = 0;
		form.add(nameText, gbcTextTemplateName);
		nameText.setColumns(20);
		
		GridBagConstraints gbcLabelCodeDesc = new GridBagConstraints();
		gbcLabelCodeDesc.anchor = GridBagConstraints.EAST;
		gbcLabelCodeDesc.insets = new Insets(0, 10, 5, 8);
		gbcLabelCodeDesc.gridx = 0;
		gbcLabelCodeDesc.gridy = 1;
		form.add(label(Const.FRM_LBL_TEMPLATE_CODE_DESC), gbcLabelCodeDesc);
		
		GridBagConstraints gbcTextCodeDesc = new GridBagConstraints();
		gbcTextCodeDesc.insets = new Insets(0, 0, 5, 10);
		gbcTextCodeDesc.fill = GridBagConstraints.HORIZONTAL;
		gbcTextCodeDesc.gridx = 1;
		gbcTextCodeDesc.gridy = 1;
		form.add(codeDescText, gbcTextCodeDesc);
		codeDescText.setColumns(20);
		
		GridBagConstraints gbcLabelDescription = new GridBagConstraints();
		gbcLabelDescription.insets = new Insets(0, 10, 5, 8);
		gbcLabelDescription.anchor = GridBagConstraints.EAST;
		gbcLabelDescription.gridx = 0;
		gbcLabelDescription.gridy = 2;
		form.add(label(Const.FRM_LBL_TEMPLATE_DESCRIPTION), gbcLabelDescription);
		
		GridBagConstraints gbcTextDescription = new GridBagConstraints();
		gbcTextDescription.insets = new Insets(0, 0, 5, 10);
		gbcTextDescription.fill = GridBagConstraints.HORIZONTAL;
		gbcTextDescription.gridx = 1;
		gbcTextDescription.gridy = 2;
		form.add(descriptionText, gbcTextDescription);
		descriptionText.setColumns(20);
		
		GridBagConstraints gbcLabelAuthor = new GridBagConstraints();
		gbcLabelAuthor.anchor = GridBagConstraints.EAST;
		gbcLabelAuthor.insets = new Insets(0, 10, 0, 8);
		gbcLabelAuthor.gridx = 0;
		gbcLabelAuthor.gridy = 3;
		form.add(label(Const.FRM_LBL_TEMPLATE_AUTHOR), gbcLabelAuthor);
		
		GridBagConstraints gbcTextAuthor = new GridBagConstraints();
		gbcTextAuthor.insets = new Insets(0, 0, 5, 10);
		gbcTextAuthor.fill = GridBagConstraints.HORIZONTAL;
		gbcTextAuthor.gridx = 1;
		gbcTextAuthor.gridy = 3;
		form.add(authorText, gbcTextAuthor);
		authorText.setColumns(20);
		
		form.setBorder(new EmptyBorder(new Insets(0, 0, 0, 10)));
		return form;
	}
	
	private JPanel initRightForm() {
		JPanel form = new JPanel(UIUtil.createFormLayout(4));
		
		GridBagConstraints gbcLabelDisease = new GridBagConstraints();
		gbcLabelDisease.insets = new Insets(10, 10, 5, 8);
		gbcLabelDisease.anchor = GridBagConstraints.EAST;
		gbcLabelDisease.gridx = 0;
		gbcLabelDisease.gridy = 0;
		form.add(label(Const.FRM_LBL_DISEASE), gbcLabelDisease);
		
		GridBagConstraints gbcTextDisease = new GridBagConstraints();
		gbcTextDisease.insets = new Insets(10, 0, 5, 10);
		gbcTextDisease.fill = GridBagConstraints.HORIZONTAL;
		gbcTextDisease.gridx = 1;
		gbcTextDisease.gridy = 0;
		form.add(diseaseText, gbcTextDisease);
		diseaseText.setColumns(20);
		
		GridBagConstraints gbcLabelBodyPart = new GridBagConstraints();
		gbcLabelBodyPart.anchor = GridBagConstraints.EAST;
		gbcLabelBodyPart.insets = new Insets(0, 10, 5, 8);
		gbcLabelBodyPart.gridx = 0;
		gbcLabelBodyPart.gridy = 1;
		form.add(label(Const.FRM_LBL_BODY_PART), gbcLabelBodyPart);
		
		GridBagConstraints gbcTextBodyPart = new GridBagConstraints();
		gbcTextBodyPart.insets = new Insets(0, 0, 5, 10);
		gbcTextBodyPart.fill = GridBagConstraints.HORIZONTAL;
		gbcTextBodyPart.gridx = 1;
		gbcTextBodyPart.gridy = 1;
		form.add(bodyPartText, gbcTextBodyPart);
		bodyPartText.setColumns(20);
		
		GridBagConstraints gbcLabelModality = new GridBagConstraints();
		gbcLabelModality.insets = new Insets(0, 10, 5, 8);
		gbcLabelModality.anchor = GridBagConstraints.EAST;
		gbcLabelModality.gridx = 0;
		gbcLabelModality.gridy = 2;
		form.add(label(Const.FRM_LBL_MODALITY), gbcLabelModality);
		
		GridBagConstraints gbcTextModality = new GridBagConstraints();
		gbcTextModality.insets = new Insets(0, 0, 5, 10);
		gbcTextModality.fill = GridBagConstraints.HORIZONTAL;
		gbcTextModality.gridx = 1;
		gbcTextModality.gridy = 2;
		form.add(modalityComboBox = new JComboBox(getModalities()), gbcTextModality);
		//modalityText.setColumns(20);
		
		GridBagConstraints gbcPlaceholder = new GridBagConstraints();
		gbcPlaceholder.insets = new Insets(0, 10, 5, 8);
		gbcPlaceholder.anchor = GridBagConstraints.EAST;
		gbcPlaceholder.gridx = 0;
		gbcPlaceholder.gridy = 3;
		form.add(new JPanel(), gbcPlaceholder);
		
		form.setBorder(new EmptyBorder(new Insets(0, 10, 0, 0)));
		return form;
	}
	
	private Object[] getModalities() {
		Object[] values = edu.stanford.isis.atb.domain.template.ModalityType.values();
		Object[] valuesWithEmptyOption = new Object[values.length + 1];
		valuesWithEmptyOption[0] = Const.EMPTY;
		for (int i = 1; i < valuesWithEmptyOption.length; i++) {
			valuesWithEmptyOption[i] = values[i-1];
		}
		return valuesWithEmptyOption;
	}
	
	private JLabel label(String text) {
		return new JLabel(String.format(Const.TPL_FORM_LABEL, text));
	}
	
	private void initResultTable() {
		JScrollPane scrollPane = new JScrollPane();
		scrollPane.setBorder(null);
		root.add(scrollPane, BorderLayout.CENTER);
		scrollPane.setViewportView(resultTable);
		scrollPane.getViewport().setBackground(Color.white);
		
		CommandColumn<TemplateSingleResult> dc = 
				new CommandColumn<TemplateSingleResult>(new CommandColumnValue<TemplateSingleResult>() {
			@Override
			public String getValue(TemplateSingleResult source) {
				return source.getName();
			}

			@Override
			public Command getCommand() {
				return selectCommand;
			}

			@Override
			public Icon getIcon() {
				return miscImages.getDownloadIcon().loadIcon();
			}
			
		}, Const.COLUMN_NAME, 120);
		
		resultTable.addGenericColumn(dc, true);
		
		resultTable.addTextColumn(new TextColumnValue<TemplateSingleResult>() {
			@Override
			public String getValue(TemplateSingleResult source) {
				return source.getAuthor();
			}
		}, Const.COLUMN_AUTHORS, 100, false);
		
		resultTable.addTextColumn(new TextColumnValue<TemplateSingleResult>() {
			@Override
			public String getValue(TemplateSingleResult source) {
				return source.getDesc();
			}
		}, Const.COLUMN_DESCRIPTION, 200, false);
		
		resultTable.addTextColumn(new TextColumnValue<TemplateSingleResult>() {
			@Override
			public String getValue(TemplateSingleResult source) {
				return source.getDisease();
			}
		}, Const.COLUMN_DISEASE, 180, false);
		
		resultTable.addTextColumn(new TextColumnValue<TemplateSingleResult>() {
			@Override
			public String getValue(TemplateSingleResult source) {
				return source.getBodyPart();
			}
		}, Const.COLUMN_BODY_PART, 80, false);
		
		resultTable.addTextColumn(new TextColumnValue<TemplateSingleResult>() {
			@Override
			public String getValue(TemplateSingleResult source) {
				return source.getModality();
			}
		}, Const.COLUMN_MODALITY, 60, false);
		
		resultTable.addTextColumn(new TextColumnValue<TemplateSingleResult>() {
			@Override
			public String getValue(TemplateSingleResult source) {
				return source.getUid();
			}
		}, Const.COLUMN_UID, 120, false);
	}

	@Override
	public void setTemplates(Collection<TemplateSingleResult> templates) {
		resultTable.setValues(templates);
	}

	@Override
	public TemplateSingleResult getSelectedTemplate() {
		return resultTable.getSelectedValue();
	}

	@Override
	public TemplateSearchRequest getTemplateSearchRequest() {
		TemplateSearchRequest request = new TemplateSearchRequest();
		request.setAuthor(authorText.getText());
		request.setBodyPart(bodyPartText.getText());
		request.setCodeDesc(codeDescText.getText());
		request.setDescription(descriptionText.getText());
		request.setDisease(diseaseText.getText());
		
		Object modality = modalityComboBox.getSelectedItem();
		if (modality != null && modality instanceof edu.stanford.isis.atb.domain.template.ModalityType) {
			request.setModality(((edu.stanford.isis.atb.domain.template.ModalityType) modality).toString());
		}
		
		if (modality != null) {
			
		}
		request.setName(nameText.getText());
		return request;
	}

	@Override
	public void clear() {
		resultTable.clear();
		nameText.setText(Const.EMPTY);
		codeDescText.setText(Const.EMPTY);
		descriptionText.setText(Const.EMPTY);
		authorText.setText(Const.EMPTY);
		diseaseText.setText(Const.EMPTY);
		bodyPartText.setText(Const.EMPTY);
		modalityComboBox.setSelectedIndex(0);
	}

	@Override
	public void setSearchCommand(final Command command) {
		searchButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				command.execute();
			}
		});
	}

	@Override
	public void setSelectCommand(Command command) {
		selectCommand = command;
	}

	@Override
	public void showAsDialog() {
		Rectangle outerBounds = Application.accessApplication().asComponent().getBounds();
		int x = outerBounds.x + (outerBounds.width - dialog.getSize().width) / 2;
		int y = outerBounds.y + (outerBounds.height - dialog.getSize().height) / 2;
		dialog.setLocation(x, y);
		dialog.setVisible(true);
	}

	@Override
	public Component asComponent() {
		return root;
	}
	
}
