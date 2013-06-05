/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.lexicon.impl;

import static edu.stanford.isis.atb.ui.Const.HNT_CREATE_LEXICON;
import static edu.stanford.isis.atb.ui.Const.HNT_DELETE_LEXICON;
import static edu.stanford.isis.atb.ui.Const.HNT_SEARCH_TERMINOLOGY;
import static edu.stanford.isis.atb.ui.view.lexicon.LexiconView.LexiconEditAction.CREATE;
import static edu.stanford.isis.atb.ui.view.lexicon.LexiconView.LexiconEditAction.DELETE;
import static edu.stanford.isis.atb.ui.view.lexicon.LexiconView.LexiconEditAction.EXPORT;
import static edu.stanford.isis.atb.ui.view.lexicon.LexiconView.LexiconEditAction.IMPORT;
import static edu.stanford.isis.atb.ui.view.lexicon.LexiconView.LexiconEditAction.IMPORT_EXPORT;
import static edu.stanford.isis.atb.ui.view.lexicon.LexiconView.LexiconEditAction.SEARCH;

import java.awt.Color;
import java.awt.Component;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

import edu.stanford.isis.atb.domain.lexicon.Lexicon;
import edu.stanford.isis.atb.service.Command;
import edu.stanford.isis.atb.ui.Const;
import edu.stanford.isis.atb.ui.action.ActionSet;
import edu.stanford.isis.atb.ui.action.CommandAction;
import edu.stanford.isis.atb.ui.view.base.ThreeCellSplitPaneView;
import edu.stanford.isis.atb.ui.view.lexicon.LexiconView;
import edu.stanford.isis.atb.ui.view.resources.ToolBarImageBundle;
import edu.stanford.isis.atb.ui.view.widget.ScrollableBlockWIthToolbar;
import edu.stanford.isis.atb.ui.view.widget.table.GenericTable;
import edu.stanford.isis.atb.ui.view.widget.table.column.TextColumn.TextColumnValue;

/**
 * Default lexicon view implementation.
 * 
 * @author Vitaliy Semeshko
 */
public class LexiconViewImpl extends ThreeCellSplitPaneView implements LexiconView {

	private static final int LEFT_PANE_WIDTH = 240;

	private ToolBarImageBundle imageBundle = ToolBarImageBundle.getInstance();

	private ActionSet actions = new ActionSet();

	private List<LexiconSelectionListener> lexiconSelectionListeners = new ArrayList<LexiconSelectionListener>();
	
	private GenericTable<Lexicon> lexiconsTable = new GenericTable<Lexicon>();

	public LexiconViewImpl(Component lexiconEditor) {
		setMainComponent(lexiconEditor);
		initializeLeftPane();
		hideRightComponent();
	}

	private void initializeLeftPane() {
		ScrollableBlockWIthToolbar left = new ScrollableBlockWIthToolbar();
		left.setScrollableAreaBackground(Color.white);
		left.setPreferredWidth(LEFT_PANE_WIDTH);
		left.setCaptionText(Const.LBL_LEXICONS);
		setLeftComponent(left);

		left.setMainComponent(lexiconsTable);

		lexiconsTable.addTextColumn(new TextColumnValue<Lexicon>() {
			@Override
			public String getValue(Lexicon source) {
				return source.getName();
			}
		}, Const.COLUMN_NAME, 150, true, false);
		
		lexiconsTable.addTextColumn(new TextColumnValue<Lexicon>() {
			@Override
			public String getValue(Lexicon source) {
				return String.valueOf(source.getTermCount());
			}
		}, Const.COLUMN_TERM_COUNT, 90, true, false);

		lexiconsTable.getSelectionModel().addListSelectionListener(new ListSelectionListener() {
			@Override
			public void valueChanged(ListSelectionEvent e) {
				if (!e.getValueIsAdjusting()) {
					Lexicon lexicon = lexiconsTable.getSelectedValue();
					// only if lexicon was selected
					// (this event also can be fired when we reload data into the table and selection is lost)
					if (lexicon != null) {
						for (LexiconSelectionListener listener : lexiconSelectionListeners) {
							listener.onLexiconSelected(lexicon);
						}
					}
				}
			}
		});
		
		// actions

		actions.add(CREATE, new CommandAction(HNT_CREATE_LEXICON, imageBundle.getCreateIcon()));
		actions.add(DELETE, new CommandAction(HNT_DELETE_LEXICON, imageBundle.getDeleteIcon()));
		actions.add(SEARCH, new CommandAction(HNT_SEARCH_TERMINOLOGY, imageBundle.getSearchLexiconsIcon()));

		CommandAction ie = new CommandAction(Const.HNT_IMPORT_EXPORT_LEXICON, imageBundle.getImportExportIcon());
		CommandAction i = new CommandAction(Const.HNT_IMPORT, imageBundle.getImportIcon());
		CommandAction e = new CommandAction(Const.HNT_EXPORT, imageBundle.getExportIcon());
		
		actions.add(IMPORT_EXPORT, ie);
		actions.add(IMPORT, i);
		actions.add(EXPORT, e);
		ie.addSubAction(i);
		ie.addSubAction(e);
		
		for (CommandAction action : actions.getAll()) {
			if (!action.isNested()) {
				left.addToolBarAction(action);
			}
		}
	}

	@Override
	public void setLexicons(Collection<Lexicon> lexicons) {
		int selectedRow = lexiconsTable.getSelectedRow();
		lexiconsTable.setValues(lexicons);
		lexiconsTable.selectRow(selectedRow);
	}
	
	@Override
	public Lexicon getActiveLexicon() {
		return lexiconsTable.getSelectedValue();
	}

	@Override
	public void setActiveLexicon(Lexicon lexicon) {
		// select row (if was not selected)
		//if (lexiconsTable.getSelectedRow() == -1) {
			int i = 0;
			for (Lexicon value : lexiconsTable.getValues()) {
				if (value.equals(lexicon)) {
					int rowToSelect = lexiconsTable.convertRowIndexToView(i);
					lexiconsTable.setRowSelectionInterval(rowToSelect, rowToSelect);
					break;
				}
				i++;
			}
		//}
	}
	
	// commands

	@Override
	public void setCommand(LexiconEditAction actionKey, Command command) {
		CommandAction action = actions.get(actionKey);
		if (action != null) {
			action.setCommand(command);
		}
	}

	// listeners
	
	@Override
	public void addLexiconSelectionListeners(LexiconSelectionListener... listeners) {
		for (LexiconSelectionListener listener : listeners) {
			lexiconSelectionListeners.add(listener);
		}
	}
	
	@Override
	public void clearSelection() {
		lexiconsTable.clearSelection();
	}

	@Override
	public void showEditForm(Component c, boolean forceShow) {
		showRightComponent(c);
	}

	@Override
	public void hideEditForm() {
		hideRightComponent();
	}

}
