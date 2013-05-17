/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.group.impl;

import static edu.stanford.isis.atb.ui.view.group.GroupView.GroupAction.COPY_GROUP;
import static edu.stanford.isis.atb.ui.view.group.GroupView.GroupAction.CREATE_GROUP;
import static edu.stanford.isis.atb.ui.view.group.GroupView.GroupAction.DELETE_GROUP;
import static edu.stanford.isis.atb.ui.view.group.GroupView.GroupAction.EDIT_GROUP;
import static edu.stanford.isis.atb.ui.view.group.GroupView.GroupAction.EXPORT;
import static edu.stanford.isis.atb.ui.view.group.GroupView.GroupAction.IMPORT;
import static edu.stanford.isis.atb.ui.view.group.GroupView.GroupAction.IMPORT_EXPORT;

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

import edu.stanford.isis.atb.domain.template.TemplateContainer;
import edu.stanford.isis.atb.domain.template.TemplateRef;
import edu.stanford.isis.atb.service.Command;
import edu.stanford.isis.atb.ui.Const;
import edu.stanford.isis.atb.ui.action.ActionSet;
import edu.stanford.isis.atb.ui.action.CommandAction;
import edu.stanford.isis.atb.ui.model.table.MarkedRef;
import edu.stanford.isis.atb.ui.view.base.ThreeCellSplitPaneView;
import edu.stanford.isis.atb.ui.view.group.GroupView;
import edu.stanford.isis.atb.ui.view.resources.MiscImageBundle;
import edu.stanford.isis.atb.ui.view.resources.ToolBarImageBundle;
import edu.stanford.isis.atb.ui.view.widget.BlockWIthToolbar;
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
//		CommandAction ps = new CommandAction(Const.HNT_SEARCH_PUBLISH_GROUP, imageBundle.getRemoteServiceIcon());
//		CommandAction s = new CommandAction(Const.HNT_SEARCH_GROUPS, imageBundle.getSearchGroupsIcon());
//		CommandAction p = new CommandAction(Const.HNT_PUBLISH_GROUP, imageBundle.getPublishIcon());
//		
//		actions.add(GroupAction.SEARCH_PUBLISH, ps);
//		actions.add(GroupAction.SEARCH, s);
//		actions.add(GroupAction.PUBLISH, p);
//		ps.addSubAction(s);
//		ps.addSubAction(p);
		
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
	
}
