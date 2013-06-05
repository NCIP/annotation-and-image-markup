/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.lexicon.search.impl;

import static edu.stanford.isis.atb.ui.Const.HNT_REMOVE_TERM;

import java.awt.Color;
import java.awt.Component;
import java.awt.Dialog.ModalityType;
import java.awt.FlowLayout;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Collection;

import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JTabbedPane;

import edu.stanford.isis.atb.domain.LexiconTermAttributes;
import edu.stanford.isis.atb.service.Command;
import edu.stanford.isis.atb.ui.Application;
import edu.stanford.isis.atb.ui.Const;
import edu.stanford.isis.atb.ui.action.CommandAction;
import edu.stanford.isis.atb.ui.view.base.TwoCellSplitPaneView;
import edu.stanford.isis.atb.ui.view.lexicon.search.SearchView;
import edu.stanford.isis.atb.ui.view.resources.MiscImageBundle;
import edu.stanford.isis.atb.ui.view.resources.ToolBarImageBundle;
import edu.stanford.isis.atb.ui.view.widget.EscapeDialog;
import edu.stanford.isis.atb.ui.view.widget.ScrollableBlockWIthToolbar;
import edu.stanford.isis.atb.ui.view.widget.table.GenericTable;
import edu.stanford.isis.atb.ui.view.widget.table.column.TextColumn.TextColumnValue;

/**
 * Default lexicon search view.
 * 
 * @author Vitaliy Semeshko
 */
public class SearchViewImpl extends TwoCellSplitPaneView implements SearchView {

	private static final int BATCH_MODE_WIDTH_EXTENSION = 280;
	
	private EscapeDialog dialog = new EscapeDialog();

	private JTabbedPane tabbedPane;
	
	private Command submitCommand;

	private ScrollableBlockWIthToolbar allowedTermsPane = new ScrollableBlockWIthToolbar();

	private GenericTable<LexiconTermAttributes> allowedTermsTable = new GenericTable<LexiconTermAttributes>();
	
	private CommandAction removeAllowedTermAction;
	
	private MiscImageBundle miscImages = MiscImageBundle.getInstance();

	private ToolBarImageBundle tbImages = ToolBarImageBundle.getInstance();
	
	public SearchViewImpl() {
		splitPaneMain.setResizeWeight(1);
		dialog.setTitle(Const.TTL_LEXICON_SEARCH);
		dialog.setModalityType(ModalityType.APPLICATION_MODAL);
		dialog.add(asComponent());
		dialog.setSize(860, 640);
		
		initTabs();
		initBottomPane();
		initRightPane();
	}
	
	public void initTabs() {
		tabbedPane = new JTabbedPane(JTabbedPane.TOP);
		tabbedPane.setFocusable(false);
		setLeftComponent(tabbedPane);
	}

	@Override
	public void setLocalSearchTab(Component tab) {
		tabbedPane.addTab(Const.TAB_LOCAL_LEXICON_SEARCH, tab);
	}

	@Override
	public void setRemoteSearchTab(Component tab) {
		tabbedPane.addTab(Const.TAB_BIOPORTAL_LEXICON_SEARCH, tab);
		tabbedPane.setEnabledAt(1, false);
	}

	private void initBottomPane() {
		JPanel bottom = new JPanel(new FlowLayout());

		JButton btnSubmit = new JButton(Const.BTN_OK, miscImages.getButtonSubmitIcon().loadIcon());
		JButton btnCancel = new JButton(Const.BTN_CANCEL, miscImages.getButtonCancelIcon().loadIcon());

		bottom.add(btnSubmit);
		bottom.add(btnCancel);
		
		setBottomComponent(bottom);
		
		btnSubmit.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				submitCommand.execute();
				dialog.setVisible(false);
			}
		});

		btnCancel.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				dialog.setVisible(false);
			}
		});
	}

	private void initRightPane() {
		allowedTermsPane.setScrollableAreaBackground(Color.white);
		allowedTermsPane.setCaptionText(Const.LBL_ALLOWED_TERMS);
		allowedTermsPane.setPreferredWidth(BATCH_MODE_WIDTH_EXTENSION);
		hideRightComponent();
		
		allowedTermsPane.setMainComponent(allowedTermsTable);
		
		allowedTermsTable.addTextColumn(new TextColumnValue<LexiconTermAttributes>() {
			@Override
			public String getValue(LexiconTermAttributes source) {
				return source.getCodeValue();
			}
		}, Const.COLUMN_VALUE, 90, true, false);
		
		allowedTermsTable.addTextColumn(new TextColumnValue<LexiconTermAttributes>() {
			@Override
			public String getValue(LexiconTermAttributes source) {
				return source.getCodeMeaning();
			}
		}, Const.COLUMN_MEANING, 180, true, false);
		
		// add actions
		removeAllowedTermAction = new CommandAction(HNT_REMOVE_TERM, tbImages.getDeleteIcon());
		allowedTermsPane.addToolBarAction(removeAllowedTermAction);
		removeAllowedTermAction.setCommand(new Command() {
			@Override
			public void execute() {
				allowedTermsTable.removeSelectedValue();
			}
		});
	}
	
	@Override
	public void setSubmitCommand(Command command) {
		submitCommand = command;
	}

	@Override
	public void setAllowedTerms(Collection<LexiconTermAttributes> terms) {
		allowedTermsTable.setValues(terms);
	}

	@Override
	public void addAllowedTerm(LexiconTermAttributes term) {
		allowedTermsTable.addValue(term);
	}

	@Override
	public Collection<LexiconTermAttributes> getAllowedTerms() {
		return allowedTermsTable.getValues();
	}

	@Override
	public void showAsDialog(boolean showRightPane, Command afterShowing) {
		if (showRightPane) {
			if (!isShowingRightComponent()) {
				dialog.setSize(dialog.getWidth() + BATCH_MODE_WIDTH_EXTENSION, dialog.getHeight());
			}
			showRightComponent(allowedTermsPane);
		} else {
			if (isShowingRightComponent()) {
				dialog.setSize(dialog.getWidth() - BATCH_MODE_WIDTH_EXTENSION, dialog.getHeight());
			}
			hideRightComponent();
		}

		Rectangle outerBounds = Application.accessApplication().asComponent().getBounds();
		int x = outerBounds.x + (outerBounds.width - dialog.getSize().width) / 2;
		int y = outerBounds.y + (outerBounds.height - dialog.getSize().height) / 2;
		dialog.setLocation(x, y);

		if (afterShowing != null) {
			afterShowing.execute();
		}
		
		dialog.setVisible(true);
	}

}
