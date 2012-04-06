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

import static edu.stanford.isis.atb.ui.view.template.TemplateView.TemplateEditAction.COPY_TEMPLATE;
import static edu.stanford.isis.atb.ui.view.template.TemplateView.TemplateEditAction.CREATE_TEMPLATE;
import static edu.stanford.isis.atb.ui.view.template.TemplateView.TemplateEditAction.DELETE_TEMPLATE;
import static edu.stanford.isis.atb.ui.view.template.TemplateView.TemplateEditAction.REMOTE_TEMPLATE_SEARCH;
import static edu.stanford.isis.atb.ui.view.template.TemplateView.TemplateEditAction.SEARCH_TEMPLATE;

import java.awt.Color;
import java.awt.Component;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

import javax.swing.Icon;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

import edu.stanford.isis.atb.domain.template.TemplateRef;
import edu.stanford.isis.atb.service.Command;
import edu.stanford.isis.atb.ui.Const;
import edu.stanford.isis.atb.ui.action.ActionSet;
import edu.stanford.isis.atb.ui.action.CommandAction;
import edu.stanford.isis.atb.ui.view.base.ThreeCellSplitPaneView;
import edu.stanford.isis.atb.ui.view.resources.MiscImageBundle;
import edu.stanford.isis.atb.ui.view.resources.ToolBarImageBundle;
import edu.stanford.isis.atb.ui.view.template.TemplateView;
import edu.stanford.isis.atb.ui.view.widget.ScrollableBlockWIthToolbar;
import edu.stanford.isis.atb.ui.view.widget.table.GenericTable;
import edu.stanford.isis.atb.ui.view.widget.table.column.IconColumn;
import edu.stanford.isis.atb.ui.view.widget.table.column.IconColumn.IconColumnValue;
import edu.stanford.isis.atb.ui.view.widget.table.column.TextColumn.TextColumnValue;

/**
 * Default template view implementation.
 * 
 * @author Vitaliy Semeshko
 */
public class TemplateViewImpl extends ThreeCellSplitPaneView implements TemplateView {

	private static final int LEFT_PANE_WIDTH = 240;

	private ToolBarImageBundle imageBundle = ToolBarImageBundle.getInstance();
	
	private MiscImageBundle miscImageBundle = MiscImageBundle.getInstance();

	private ActionSet actions = new ActionSet();

	private List<TemplateSelectionListener> templateSelectionListeners = new ArrayList<TemplateSelectionListener>();

	private GenericTable<TemplateRef> templatesTable = new GenericTable<TemplateRef>();

	public TemplateViewImpl(Component templateEditor) {
		setMainComponent(templateEditor);
		initializeLeftPane();
		hideRightComponent();
	}

	private void initializeLeftPane() {
		ScrollableBlockWIthToolbar left = new ScrollableBlockWIthToolbar();
		left.setScrollableAreaBackground(Color.white);
		left.setPreferredWidth(LEFT_PANE_WIDTH);
		left.setCaptionText(Const.LBL_TEMPLATES);
		setLeftComponent(left);

		left.setMainComponent(templatesTable);
		
		IconColumn<TemplateRef> iconColumn = new IconColumn<TemplateRef>(new IconColumnValue<TemplateRef>() {
			private Icon warningIcon = miscImageBundle.getValidationWarningIcon().loadIcon();
			
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
				DateFormat df = new SimpleDateFormat(Const.FMT_DATE_DISPLAY);
				return df.format(source.getCreationDate());
			}
		}, Const.COLUMN_DATE, 80, false);

		templatesTable.addTextColumn(new TextColumnValue<TemplateRef>() {
			@Override
			public String getValue(TemplateRef source) {
				return source.getVersion();
			}
		}, Const.COLUMN_VERSION, 70, false);

		templatesTable.getSelectionModel().addListSelectionListener(new ListSelectionListener() {
			@Override
			public void valueChanged(ListSelectionEvent e) {
				if (!e.getValueIsAdjusting()) {
					TemplateRef template = templatesTable.getSelectedValue();
					// only if template was selected
					// (this event also can be fired when we reload data into the table and selection is lost)
					if (template != null) {
						for (TemplateSelectionListener listener : templateSelectionListeners) {
							listener.onTemplateSelected(template);
						}
					}
				}
			}
		});

		// actions

		actions.add(CREATE_TEMPLATE, new CommandAction(Const.HNT_CREATE_TEMPLATE, imageBundle.getCreateIcon()));
		actions.add(DELETE_TEMPLATE, new CommandAction(Const.HNT_DELETE_TEMPLATE, imageBundle.getDeleteIcon()));
		actions.add(COPY_TEMPLATE, new CommandAction(Const.HNT_COPY_TEMPLATE, imageBundle.getCopyTemplateIcon()));
		
		// VK: Disabled ATS integration for v1.0
//		CommandAction searchGroup = new CommandAction(Const.HNT_SEARCH_TEMPLATES, imageBundle.getRemoteServiceIcon());
//		CommandAction search = new CommandAction(Const.HNT_SEARCH_TEMPLATES, imageBundle.getSearchTemplateIcon());
//		
//		actions.add(REMOTE_TEMPLATE_SEARCH, searchGroup);
//		actions.add(SEARCH_TEMPLATE, search);
//		searchGroup.addSubAction(search);

		for (CommandAction action : actions.getAll()) {
			if (!action.isNested()) {
				left.addToolBarAction(action);
			}
		}
	}

	@Override
	public void setTemplates(Collection<TemplateRef> templates) {
		templatesTable.setValues(templates);
	}
	
	@Override
	public void setActiveTemplate(TemplateRef template) {
		// select row (if was not selected)
		if (templatesTable.getSelectedRow() == -1) {
			int i = 0;
			for (TemplateRef value : templatesTable.getValues()) {
				if (value.equals(template)) {
					int rowToSelect = templatesTable.convertRowIndexToView(i);
					templatesTable.selectRow(rowToSelect);
					break;
				}
				i++;
			}
		}
	}
	
	@Override
	public void clearSelection() {
		templatesTable.clearSelection();
	}
	
	@Override
	public void refreshTable() {
		templatesTable.refresh();		
	}
	
	// set commands

	@Override
	public void setCommand(TemplateEditAction actionKey, Command command) {
		CommandAction action = actions.get(actionKey);
		if (action != null) {
			action.setCommand(command);
		}
	}

	// set listeners

	@Override
	public void addTemplateSelectionListeners(TemplateSelectionListener... listeners) {
		for (TemplateSelectionListener listener : listeners) {
			templateSelectionListeners.add(listener);
		}
	}

	@Override
	public void showEditForm(Component c, boolean forceShow) {
		showRightComponent(c, forceShow);
	}

	@Override
	public void hideEditForm() {
		hideRightComponent();
	}
	
}
