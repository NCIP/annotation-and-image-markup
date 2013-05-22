/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
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
		CommandAction searchGroup = new CommandAction(Const.HNT_SEARCH_TEMPLATES, imageBundle.getRemoteServiceIcon());
		CommandAction search = new CommandAction(Const.HNT_SEARCH_TEMPLATES, imageBundle.getSearchTemplateIcon());
		
		actions.add(REMOTE_TEMPLATE_SEARCH, searchGroup);
		actions.add(SEARCH_TEMPLATE, search);
		searchGroup.addSubAction(search);

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
