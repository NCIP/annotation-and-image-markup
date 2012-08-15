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

package edu.stanford.isis.atb.ui.view.group.impl;

import static edu.stanford.isis.atb.ui.view.group.GroupView.GroupAction.COPY_GROUP;
import static edu.stanford.isis.atb.ui.view.group.GroupView.GroupAction.CREATE_GROUP;
import static edu.stanford.isis.atb.ui.view.group.GroupView.GroupAction.DELETE_GROUP;
import static edu.stanford.isis.atb.ui.view.group.GroupView.GroupAction.EDIT_GROUP;
import static edu.stanford.isis.atb.ui.view.group.GroupView.GroupAction.EXPORT;
import static edu.stanford.isis.atb.ui.view.group.GroupView.GroupAction.IMPORT;
import static edu.stanford.isis.atb.ui.view.group.GroupView.GroupAction.IMPORT_EXPORT;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.GridBagConstraints;
import java.awt.Insets;
import java.awt.Rectangle;
import java.awt.Dialog.ModalityType;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.io.File;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

import javax.swing.Icon;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.SwingUtilities;
import javax.swing.border.EmptyBorder;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

import org.apache.commons.io.FilenameUtils;
import org.apache.commons.lang3.StringUtils;

import edu.stanford.isis.atb.domain.template.TemplateContainer;
import edu.stanford.isis.atb.domain.template.TemplateRef;
import edu.stanford.isis.atb.service.Command;
import edu.stanford.isis.atb.ui.Application;
import edu.stanford.isis.atb.ui.Const;
import edu.stanford.isis.atb.ui.action.ActionSet;
import edu.stanford.isis.atb.ui.action.CommandAction;
import edu.stanford.isis.atb.ui.model.table.MarkedRef;
import edu.stanford.isis.atb.ui.util.UIUtil;
import edu.stanford.isis.atb.ui.view.base.ThreeCellSplitPaneView;
import edu.stanford.isis.atb.ui.view.group.GroupView;
import edu.stanford.isis.atb.ui.view.resources.MiscImageBundle;
import edu.stanford.isis.atb.ui.view.resources.ToolBarImageBundle;
import edu.stanford.isis.atb.ui.view.widget.BlockWIthToolbar;
import edu.stanford.isis.atb.ui.view.widget.EscapeDialog;
import edu.stanford.isis.atb.ui.view.widget.ScrollableBlockWIthToolbar;
import edu.stanford.isis.atb.ui.view.widget.group.GroupMembers;
import edu.stanford.isis.atb.ui.view.widget.table.GenericTable;
import edu.stanford.isis.atb.ui.view.widget.table.column.IconColumn;
import edu.stanford.isis.atb.ui.view.widget.table.column.BooleanColumn.BooleanColumnValue;
import edu.stanford.isis.atb.ui.view.widget.table.column.IconColumn.IconColumnValue;
import edu.stanford.isis.atb.ui.view.widget.table.column.TextColumn.TextColumnValue;

/**
 * Default group view implementation.
 * 
 * @author Vitaliy Semeshko
 */
@SuppressWarnings("serial")
public class GroupViewImpl extends ThreeCellSplitPaneView implements GroupView {

	private static final int LEFT_PANE_WIDTH = 240;
	private static final int RIGHT_PANE_WIDTH = 220;

	private ToolBarImageBundle imageBundle = ToolBarImageBundle.getInstance();
	
	private ActionSet actions = new ActionSet();
	
	private CommandAction linkTemplatesWithContainer;

	private GroupMembers groupMembers = new GroupMembers();
	
	private BlockWIthToolbar mainArea = new BlockWIthToolbar();
	
	private List<ContainerSelectionListener> containerSelectionListeners = new ArrayList<ContainerSelectionListener>();
	
	private GenericTable<TemplateContainer> containersTable = new GenericTable<TemplateContainer>();
	
	private GenericTable<MarkedRef<TemplateRef>> templatesTable = new GenericTable<MarkedRef<TemplateRef>>();

	public GroupViewImpl() {
		initializeLeftPane();
		initializeMainPane();
		initializeRightPane();
	}

	private void initializeLeftPane() {
		ScrollableBlockWIthToolbar left = new ScrollableBlockWIthToolbar();
		left.setScrollableAreaBackground(Color.white);
		left.setPreferredWidth(LEFT_PANE_WIDTH);
		left.setCaptionText(Const.LBL_GROUPS);
		setLeftComponent(left);

		left.setMainComponent(containersTable);
		
		IconColumn<TemplateContainer> iconColumn = new IconColumn<TemplateContainer>(new IconColumnValue<TemplateContainer>() {
			private Icon warningIcon = MiscImageBundle.getInstance().getValidationWarningIcon().loadIcon();
			
			@Override
			public Icon getValue(TemplateContainer source) {
				return source.isValid() ? null : warningIcon;
			}
		}, Const.EMPTY, 20);
		containersTable.addGenericColumn(iconColumn, false);
		
		containersTable.addTextColumn(new TextColumnValue<TemplateContainer>() {
			@Override
			public String getValue(TemplateContainer source) {
				return source.getName();
			}
		}, Const.COLUMN_NAME, 140, true, false);
		
		containersTable.addTextColumn(new TextColumnValue<TemplateContainer>() {
			@Override
			public String getValue(TemplateContainer source) {
				DateFormat df = new SimpleDateFormat(Const.FMT_DATE_DISPLAY);
				return df.format(source.getCreationDate());
			}
		}, Const.COLUMN_DATE, 80, false);
		
		containersTable.addTextColumn(new TextColumnValue<TemplateContainer>() {
			@Override
			public String getValue(TemplateContainer source) {
				return source.getVersion();
			}
		}, Const.COLUMN_VERSION, 70, false);
		
		containersTable.getSelectionModel().addListSelectionListener(new ListSelectionListener() {
			@Override
			public void valueChanged(ListSelectionEvent e) {
				if (!e.getValueIsAdjusting()) {
					TemplateContainer container = containersTable.getSelectedValue();
					// only if container was selected
					// (this event also can be fired when we reload data into the table and selection is lost)
					if (container != null) {
						for (ContainerSelectionListener listener : containerSelectionListeners) {
							listener.onContainerSelected(container);
						}
					}
				}
			}
		});
		
		// actions
		
		actions.add(CREATE_GROUP, new CommandAction(Const.HNT_CREATE_GROUP, imageBundle.getCreateIcon()));
		actions.add(EDIT_GROUP, new CommandAction(Const.HNT_EDIT_GROUP, imageBundle.getEditIcon()));
		actions.add(DELETE_GROUP, new CommandAction(Const.HNT_DELETE_GROUP, imageBundle.getDeleteIcon()));
		actions.add(COPY_GROUP, new CommandAction(Const.HNT_COPY_GROUP, imageBundle.getCopyGroupIcon()));
		
		CommandAction ie = new CommandAction(Const.HNT_IMPORT_EXPORT_GROUP, imageBundle.getImportExportIcon());
		CommandAction i = new CommandAction(Const.HNT_IMPORT, imageBundle.getImportIcon());
		CommandAction e = new CommandAction(Const.HNT_EXPORT, imageBundle.getExportIcon());
		
		actions.add(IMPORT_EXPORT, ie);
		actions.add(IMPORT, i);
		actions.add(EXPORT, e);
		ie.addSubAction(i);
		ie.addSubAction(e);
		
		// VK: Disabled ATB integration for v1.0
		CommandAction ps = new CommandAction(Const.HNT_SEARCH_PUBLISH_GROUP, imageBundle.getRemoteServiceIcon());
		CommandAction s = new CommandAction(Const.HNT_SEARCH_GROUPS, imageBundle.getSearchGroupsIcon());
		CommandAction p = new CommandAction(Const.HNT_PUBLISH_GROUP, imageBundle.getPublishIcon());
		
		actions.add(GroupAction.SEARCH_PUBLISH, ps);
		actions.add(GroupAction.SEARCH, s);
		actions.add(GroupAction.PUBLISH, p);
		ps.addSubAction(s);
		ps.addSubAction(p);
	
		for (CommandAction action : actions.getAll()) {
			if (!action.isNested()) {
				left.addToolBarAction(action);
			}
		}
	}

	private void initializeRightPane() {
		ScrollableBlockWIthToolbar right = new ScrollableBlockWIthToolbar();
		right.setScrollableAreaBackground(Color.white);
		right.setPreferredWidth(RIGHT_PANE_WIDTH);
		right.setCaptionText(Const.LBL_GROUP_MEMBERSHIPS);
		setRightComponent(right);
		
		right.setMainComponent(templatesTable);
		
		templatesTable.addBooleanColumn(new BooleanColumnValue<MarkedRef<TemplateRef>>() {
			@Override
			public Boolean getValue(MarkedRef<TemplateRef> source) {
				return source.isMarked();
			}
			@Override
			public void setValue(MarkedRef<TemplateRef> source, Object value) {
				source.setMarked((Boolean) value);
			}
			
		}, Const.EMPTY, 30, true);
		
		templatesTable.addTextColumn(new TextColumnValue<MarkedRef<TemplateRef>>() {
			@Override
			public String getValue(MarkedRef<TemplateRef> source) {
				return source.getValue().getName();
			}
		}, Const.COLUMN_NAME, 140, true, false);
		
		templatesTable.addTextColumn(new TextColumnValue<MarkedRef<TemplateRef>>() {
			@Override
			public String getValue(MarkedRef<TemplateRef> source) {
				DateFormat df = new SimpleDateFormat(Const.FMT_DATE_DISPLAY);
				return df.format(source.getValue().getCreationDate());
			}
		}, Const.COLUMN_DATE, 80, false);
		
		templatesTable.addTextColumn(new TextColumnValue<MarkedRef<TemplateRef>>() {
			@Override
			public String getValue(MarkedRef<TemplateRef> source) {
				return source.getValue().getVersion();
			}
		}, Const.COLUMN_VERSION, 70, false);
		
		// add actions
		linkTemplatesWithContainer = new CommandAction(Const.HNT_INCLUDE_TEMPLATES, imageBundle.getLinkTemplatesIcon());
		right.addToolBarAction(linkTemplatesWithContainer);
	}

	private void initializeMainPane() {
		mainArea.setCaptionText(Const.LBL_GROUP_MEMBERS);
		setMainComponent(mainArea);

		mainArea.setMainComponent(groupMembers);
	}

	@Override
	public void setContainers(Collection<TemplateContainer> containers) {
		containersTable.setValues(containers);
	}

	@Override
	public void setTemplates(Collection<TemplateRef> templates) {
		List<MarkedRef<TemplateRef>> markedRefs = new ArrayList<MarkedRef<TemplateRef>>();
		for (TemplateRef template : templates) {
			markedRefs.add(new MarkedRef<TemplateRef>(template, false));
		}
		templatesTable.setValues(markedRefs);
	}
	
	@Override
	public void setActiveContainer(TemplateContainer container, boolean updateMemberships) {
		// update main area (labels, central table)
		groupMembers.setTemplateContainer(container);
		
		// update marked members
		if (updateMemberships) {
			for (MarkedRef<TemplateRef> ref : templatesTable.getValues()) {
				ref.setMarked(container.containsTemplate(ref.getValue()));
			}
			templatesTable.refresh();
		}
		
		// select row (if was not selected)
		if (containersTable.getSelectedRow() == -1) {
			int i = 0;
			for (TemplateContainer value : containersTable.getValues()) {
				if (value.equals(container)) {
					int rowToSelect = containersTable.convertRowIndexToView(i);
					containersTable.setRowSelectionInterval(rowToSelect, rowToSelect);
					break;
				}
				i++;
			}
		}
	}
	
	@Override
	public Iterable<TemplateRef> getMarkedTemplatesForLinking() {
		List<TemplateRef> markedTemplates = new ArrayList<TemplateRef>();
		for (MarkedRef<TemplateRef> template : templatesTable.getValues()) {
			if (template.isMarked()) {
				markedTemplates.add(template.getValue());
			}
		}
		return markedTemplates;
	}
	
	// set commands
	
	@Override
	public void setLinkTemplatesWithContainerCommand(Command command) {
		linkTemplatesWithContainer.setCommand(command);
	}
	
	@Override
	public void setCommand(GroupAction actionKey, Command command) {
		CommandAction action = actions.get(actionKey);
		if (action != null) {
			action.setCommand(command);
		}
	}
	
	// set listeners
	
	@Override
	public void addContainerSelectionListener(ContainerSelectionListener listener) {
		containerSelectionListeners.add(listener);
	}

	// view
	
	@Override
	public void hideEditForm() {
		mainArea.hideBottomSplitArea();
	}

	@Override
	public void showEditForm(Component c) {
		mainArea.showBottomSplitArea(c);
	}

	@Override
	public void clearContainerDetails(boolean unmarkMemberships) {
		groupMembers.clearContainerDetails();
		containersTable.clearSelection();
		
		if (unmarkMemberships) {
			for (MarkedRef<TemplateRef> template : templatesTable.getValues()) {
				template.setMarked(false);
			}
			
			templatesTable.refresh();
		}
	}

	private static interface Cancelable {
		boolean getOk();
		void setOk(boolean cancel);
	}
		
	@Override
	public boolean showTemplateNamePrompt(final TemplateContainer container) {
		final Cancelable cancelStatus = new Cancelable() {
			private boolean isOk = false;
			
			@Override
			public void setOk(boolean cancel) {
				this.isOk = cancel;
			}
			
			@Override
			public boolean getOk() {
				return this.isOk;
			}
		};
		
		final EscapeDialog dialog = new EscapeDialog();
		dialog.setResizable(false);
		dialog.setSize(420, 150);
		dialog.setModalityType(ModalityType.APPLICATION_MODAL);
		dialog.setTitle(Const.DLG_TITLE_PUBLISHED_TEMPLATE_FILE_NAME);

		JPanel panel = new JPanel(new BorderLayout());
		dialog.getContentPane().add(panel, BorderLayout.CENTER);

		panel.setLayout(UIUtil.createFormLayout(3));
		panel.setBorder(new EmptyBorder(new Insets(10, 5, 10, 5)));

		// fields

		GridBagConstraints gbcLabelTemplateFileName = new GridBagConstraints();
		gbcLabelTemplateFileName.insets = new Insets(10, 10, 10, 8);
		gbcLabelTemplateFileName.anchor = GridBagConstraints.EAST;
		gbcLabelTemplateFileName.gridx = 0;
		gbcLabelTemplateFileName.gridy = 0;
		panel.add(new JLabel(String.format(Const.TPL_FORM_LABEL_MANDATORY, Const.LBL_TEMPLATE_FILE_NAME)), gbcLabelTemplateFileName);

		final JTextField templateFileNameText = new JTextField();
		
		File templateFile = new File(container.getFileName());
		final String templateFileNameWithoutExt = FilenameUtils.removeExtension(StringUtils.isEmpty(container.getPublishedFileName()) ? templateFile.getName() : container.getPublishedFileName());
		templateFileNameText.setText(templateFileNameWithoutExt);
		
		GridBagConstraints gbcTextTemplateFileName = new GridBagConstraints();
		gbcTextTemplateFileName.insets = new Insets(10, 0, 10, 10);
		gbcTextTemplateFileName.fill = GridBagConstraints.HORIZONTAL;
		gbcTextTemplateFileName.gridx = 1;
		gbcTextTemplateFileName.gridy = 0;
		panel.add(templateFileNameText, gbcTextTemplateFileName);
		templateFileNameText.setColumns(10);

		// buttons

		JPanel bottom = new JPanel(new BorderLayout());
		dialog.getContentPane().add(bottom, BorderLayout.SOUTH);

		JPanel buttons = new JPanel();
		buttons.setBorder(new EmptyBorder(new Insets(0, 0, 10, 10)));
		bottom.add(buttons, BorderLayout.EAST);

		final JButton publish = new JButton(Const.BTN_PUBLISH);
		final JButton cancel = new JButton(Const.BTN_CANCEL);
		buttons.add(publish);
		buttons.add(cancel);
		dialog.getRootPane().setDefaultButton(publish);

		// actions
		
		publish.addActionListener(new ActionListener() {
			final static String extXml = ".xml";
			@Override
			public void actionPerformed(ActionEvent e) {
				String publishedFileName = templateFileNameText.getText().trim();
				container.setPublishedFileName(StringUtils.endsWithIgnoreCase(publishedFileName, extXml) ? publishedFileName : publishedFileName + extXml);
				cancelStatus.setOk(true);
				dialog.setVisible(false);
			}
		});
		
		cancel.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				dialog.setVisible(false);
			}
		});

		publish.setEnabled(templateFileNameText.getText().trim().length() > 0);
		templateFileNameText.addKeyListener(new KeyAdapter() {
			@Override
			public void keyTyped(KeyEvent e) {
				publish.setEnabled(templateFileNameText.getText().trim().length() > 0);
			}
		});

		SwingUtilities.invokeLater(new Runnable() {  
			@Override
			public void run() {
				templateFileNameText.requestFocusInWindow();
			}
		});
		
		Rectangle outerBounds = Application.accessApplication().asComponent().getBounds();
		int x = outerBounds.x + (outerBounds.width - dialog.getSize().width) / 2;
		int y = outerBounds.y + (outerBounds.height - dialog.getSize().height) / 2;
		dialog.setLocation(x, y);
		dialog.setVisible(true);

		return cancelStatus.getOk();
	}	
}
