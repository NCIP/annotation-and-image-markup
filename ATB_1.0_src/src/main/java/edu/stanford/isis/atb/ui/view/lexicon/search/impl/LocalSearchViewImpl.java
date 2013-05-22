/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.lexicon.search.impl;

import static edu.stanford.isis.atb.ui.Const.EMPTY;
import static edu.stanford.isis.atb.ui.Const.HNT_SELECT_ALL_NESTED_TERMS;
import static edu.stanford.isis.atb.ui.Const.HNT_SELECT_DIRECT_CHILDREN;
import static edu.stanford.isis.atb.ui.model.tree.LexiconNodeType.TERM;

import java.awt.BorderLayout;
import java.awt.CardLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;

import javax.swing.BorderFactory;
import javax.swing.BoxLayout;
import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JSplitPane;
import javax.swing.SwingUtilities;
import javax.swing.border.EmptyBorder;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.TreeSelectionModel;

import edu.stanford.isis.atb.domain.lexicon.Lexicon;
import edu.stanford.isis.atb.domain.lexicon.Term;
import edu.stanford.isis.atb.service.Command;
import edu.stanford.isis.atb.ui.Const;
import edu.stanford.isis.atb.ui.action.ActionSet;
import edu.stanford.isis.atb.ui.action.CommandAction;
import edu.stanford.isis.atb.ui.model.tree.LexiconNodeType;
import edu.stanford.isis.atb.ui.model.tree.LexiconNodeValue;
import edu.stanford.isis.atb.ui.view.AbstractView;
import edu.stanford.isis.atb.ui.view.lexicon.LazyTermNodeValueLoader;
import edu.stanford.isis.atb.ui.view.lexicon.LexiconTreeManager;
import edu.stanford.isis.atb.ui.view.lexicon.impl.LexiconTreeManagerImpl;
import edu.stanford.isis.atb.ui.view.lexicon.rules.LocalSearchTreeRules;
import edu.stanford.isis.atb.ui.view.lexicon.search.LocalSearchView;
import edu.stanford.isis.atb.ui.view.resources.ToolBarImageBundle;
import edu.stanford.isis.atb.ui.view.widget.SuggestionBox;
import edu.stanford.isis.atb.ui.view.widget.lexicon.LexiconTermView;
import edu.stanford.isis.atb.ui.view.widget.table.GenericTable;
import edu.stanford.isis.atb.ui.view.widget.table.column.TextColumn.TextColumnValue;
import edu.stanford.isis.atb.ui.view.widget.tree.AbstractTree.NodeSelectionListener;
import edu.stanford.isis.atb.ui.view.widget.tree.LexiconTree;

/**
 * @author Vitaliy Semeshko
 */
public class LocalSearchViewImpl extends AbstractView implements LocalSearchView {

	private JPanel root = new JPanel(new BorderLayout());

	private JSplitPane splitPaneMain = new JSplitPane();

	private SuggestionBox searchBox = new SuggestionBox(false);
	
	private JCheckBox wholeWordCheckBox = new JCheckBox(Const.BTN_WHOLE_WORD);

	private ToolBarImageBundle tbImages = ToolBarImageBundle.getInstance();

	private Command searchCommand;
	
	private JButton selectButton = new JButton(tbImages.getUseAllowedTermIcon().loadIcon());

	private JList lexiconsList = new JList();

	private JPanel termDetailsPanel = new JPanel(new CardLayout());
	
	private JLabel multipleTemsLabel = new JLabel();
	
	private LexiconTermView termView = new LexiconTermView();

	private LexiconTree tree = new LexiconTree();
	
	private LexiconTreeManager treeManager;

	private GenericTable<Term> resultTable = new GenericTable<Term>();
	
	private List<TermSelectionListener> termSelectionListeners = new ArrayList<TermSelectionListener>();
	
	private List<ActionSet> actions = new ArrayList<ActionSet>();
	private ActionSet termActions = new ActionSet();
	
	private Map<LexiconNodeType, ActionSet> nodeActions = new HashMap<LexiconNodeType, ActionSet>();

	private LocalSearchTreeRules localSearchTreeRules = new LocalSearchTreeRules();
	
	private enum TermDetailCard {
		INFO,
		LABEL;
	}
	
	public LocalSearchViewImpl() {
		root.add(splitPaneMain, BorderLayout.CENTER);
		splitPaneMain.setResizeWeight(0.5);

		JSplitPane nestedSplitPane = new JSplitPane(JSplitPane.VERTICAL_SPLIT);
		nestedSplitPane.setResizeWeight(0.5);
		splitPaneMain.setRightComponent(nestedSplitPane);
		
		multipleTemsLabel.setBorder(BorderFactory.createEmptyBorder(14, 14, 14, 14));
		multipleTemsLabel.setVerticalAlignment(JLabel.TOP);

		termDetailsPanel.add(new JScrollPane(termView), TermDetailCard.INFO.toString());
		termDetailsPanel.add(multipleTemsLabel, TermDetailCard.LABEL.toString());
		
		nestedSplitPane.setTopComponent(termDetailsPanel);
		nestedSplitPane.setBottomComponent(new JScrollPane(tree));

		nodeActions.put(TERM, termActions);
		actions.add(termActions);
		
		initSearch();
		initSearchResult();
		initTermActions();
		initTree();
	}

	private void initSearch() {
		JPanel top = new JPanel(new BorderLayout());
		JPanel searchControls = new JPanel();
		top.add(searchControls, BorderLayout.WEST);
		root.add(top, BorderLayout.NORTH);

		JPanel searchOptions = new JPanel();
		searchOptions.setLayout(new BoxLayout(searchOptions, BoxLayout.Y_AXIS));
		searchControls.add(searchOptions);
		
		// search options
		searchBox.setPreferredSize(new Dimension(220, (int) searchBox.getPreferredSize().getHeight()));
		searchBox.setAlignmentX(Component.LEFT_ALIGNMENT);
		searchOptions.add(searchBox);
		wholeWordCheckBox.setAlignmentX(Component.LEFT_ALIGNMENT);
		searchOptions.add(wholeWordCheckBox);
		wholeWordCheckBox.setFocusable(false);
		
		searchBox.addKeyListener(new KeyAdapter() {
			@Override
			public void keyPressed(KeyEvent e) {
				if (e.getKeyCode() == KeyEvent.VK_ENTER) {
					if (searchCommand != null) {
						searchCommand.execute();
					}
				}
			}
		});
		
		// lexicons
		lexiconsList.setVisibleRowCount(3);
		lexiconsList.setFixedCellWidth(200);
		final JScrollPane listScroller = new JScrollPane(lexiconsList);
		searchControls.add(listScroller);
		lexiconsList.addKeyListener(new KeyAdapter() {
			@Override
			public void keyPressed(KeyEvent e) {
				if (e.getKeyCode() == KeyEvent.VK_ENTER) {
					if (searchCommand != null) {
						searchCommand.execute();
					}
				}
			}
		});

		// search button
		JButton searchButton = new JButton(tbImages.getSearchLexiconsIcon().loadIcon());
		searchControls.add(searchButton);
		searchButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				if (searchCommand != null) {
					searchCommand.execute();
				}
			}
		});

		// add select lexicon term button (wrap to avoid filling all east area)
		JPanel searchButtonHolder = new JPanel(new GridBagLayout());
		searchButtonHolder.setBorder(new EmptyBorder(new Insets(0, 0, 0, 10)));
		searchButtonHolder.add(selectButton);
		top.add(searchButtonHolder, BorderLayout.EAST);
	}

	private void initSearchResult() {
		JScrollPane tableScroller = new JScrollPane(resultTable);
		tableScroller.getViewport().setBackground(Color.white);
		splitPaneMain.setLeftComponent(tableScroller);

		resultTable.addTextColumn(new TextColumnValue<Term>() {
			@Override
			public String getValue(Term source) {
				return source.getLexicon() == null ? "" : source.getLexicon().getName();
			}
		}, Const.COLUMN_LEXICON, 60, false, false);

		resultTable.addTextColumn(new TextColumnValue<Term>() {
			@Override
			public String getValue(Term source) {
				return source.getCodeValue();
			}
		}, Const.COLUMN_VALUE, 70, false, false);

		resultTable.addTextColumn(new TextColumnValue<Term>() {
			@Override
			public String getValue(Term source) {
				return source.getCodeMeaning();
			}
		}, Const.COLUMN_MEANING, 100, false, false);

		resultTable.addTextColumn(new TextColumnValue<Term>() {
			@Override
			public String getValue(Term source) {
				return source.getDescription();
			}
		}, Const.COLUMN_DESCRIPTION, 240, false, false);
		
		resultTable.getSelectionModel().addListSelectionListener(new ListSelectionListener() {
			@Override
			public void valueChanged(ListSelectionEvent e) {
				if (!e.getValueIsAdjusting()) {
					Term term = resultTable.getSelectedValue();
					// only if term was selected
					// (this event also can be fired when we reload data into the table and selection is lost)
					if (term != null) {
						for (TermSelectionListener listener : termSelectionListeners) {
							listener.onTermSelected(term);
						}
					}
				}
			}
		});
	}

	private void initTree() {
		tree.enableContextMenu();
		
		tree.addNodeSelectionListener(new NodeSelectionListener<LexiconNodeValue>() {
			@Override
			public void onNodeSelected(LexiconNodeValue nodeValue) {
				// if term node selected (ignoring root lexicon node)
				if (nodeValue.getValue() instanceof Term) {
					Term term = (Term) nodeValue.getValue();
					showTermDetails(term);
					selectTermInResultTable(term);
				} else {
					clearTermDetails();
				}
				
				ActionSet actions = nodeActions.get(nodeValue.getNodeType());
				tree.getContextMenu().removeAll();
				
				if (actions != null) {
					// apply rules according to the node state
					localSearchTreeRules.applyRulesForNode(nodeValue, actions);
					
					// add actions to the context menu 
					for (CommandAction action : actions.getAll()) {
						tree.getContextMenu().add(action);
					}
				}
				//TODO: if no menu items, don't show menu at all (because now only shadow is visible)
			}
		});
	}
	
	private void selectTermInResultTable(Term term) {
		// if currently selected row is the same what should be selected
		Term currentSelection = resultTable.getSelectedValue();
		if (term.equals(currentSelection)) {
			return;
		}
		
		//TODO: implement logic: when user selects tree node, try to find row in the table
//		int i = 0;
//		for (Term current : resultTable.getValues()) {
//			if (term.equals(current)) {
//				int rowToSelect = resultTable.convertRowIndexToView(i);
//				resultTable.selectRow(rowToSelect);
//				//resultTable.setRowSelectionInterval(rowToSelect, rowToSelect);
//				return;
//			}
//			i++;
//		}
		
		resultTable.clearSelection();
	}
	
	private void initTermActions() {
		CommandAction selectDirectChildren = new CommandAction(HNT_SELECT_DIRECT_CHILDREN, null);
		termActions.add(TermSearchAction.SELECT_DIRECT_CHILDREN, selectDirectChildren);
		
		CommandAction selectAllNestedTerms = new CommandAction(HNT_SELECT_ALL_NESTED_TERMS, null);
		termActions.add(TermSearchAction.SELECT_ALL_NESTED_TERMS, selectAllNestedTerms);
	}
	
	@Override
	public void setSearchHistory(Set<String> history) {
		searchBox.setOptions(history);
	}

	@Override
	public void setLexicons(Collection<Lexicon> lexicons) {
		DefaultListModel model = new DefaultListModel();
		for (Lexicon lexicon : lexicons) {
			model.addElement(lexicon);
		}
		lexiconsList.setModel(model);
	}
	
	@Override
	public void setLazyTermNodeValueLoader(LazyTermNodeValueLoader loader) {
		treeManager = new LexiconTreeManagerImpl(tree, loader);
	}

	@Override
	public void showLexiconTree(Lexicon lexicon) {
		treeManager.setLexicon(lexicon, false);
	}

	@Override
	public void expandTermPath(Term termPath) {
		treeManager.expandTermPath(termPath);
	}

	@Override
	public void selectDirectChildrenOfLastSelectedNode() {
		treeManager.selectDirectChildrenOfLastSelectedNode();
	}

	@Override
	public void selectAllNestedNodesOfLastSelectedNode() {
		treeManager.selectAllNestedNodesOfLastSelectedNode();
	}

	@Override
	public String getSearchText() {
		return searchBox.getText();
	}

	@Override
	public boolean isExactMatch() {
		return wholeWordCheckBox.isSelected();
	}

	@Override
	public Collection<DefaultMutableTreeNode> getSelectedTreeNodes() {
		return tree.getSelectedNodes();
	}

	@Override
	public void setSearchResult(Collection<Term> terms) {
		resultTable.setValues(terms);
	}

	@Override
	public Collection<Lexicon> getSelectedLexicons() {
		if (lexiconsList.isSelectionEmpty()) {
			return Collections.emptyList();
		} else {
			List<Lexicon> selectedLexicons = new ArrayList<Lexicon>();
			for (Object o : lexiconsList.getSelectedValues()) {
				selectedLexicons.add((Lexicon) o);
			}
			return selectedLexicons;
		}
	}

	@Override
	public void setSearchCommand(final Command command) {
		searchCommand = command;
	}
	
	@Override
	public void setSelectCommand(final Command command) {
		selectButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				command.execute();
			}
		});
	}

	@Override
	public void addTermSelectionListener(TermSelectionListener listener) {
		termSelectionListeners.add(listener);
	}

	@Override
	public void clear(boolean clearSearchText) {
		resultTable.clear();
		treeManager.clear();
		clearTermDetails();
		if (clearSearchText) {
			searchBox.clear();
		}
	}

	@Override
	public void setInitialFocus() {
		SwingUtilities.invokeLater(new Runnable() {
			@Override
			public void run() {
				searchBox.requestFocusInWindow();
			}
		});
	}

	@Override
	public void setBatchMode(boolean isBatch) {
		selectButton.setVisible(isBatch);
		tree.getSelectionModel().setSelectionMode(isBatch ? TreeSelectionModel.DISCONTIGUOUS_TREE_SELECTION 
				: TreeSelectionModel.SINGLE_TREE_SELECTION);
	}

	@Override
	public void setCommand(Object actionKey, Command command) {
		for (ActionSet actionSet : actions) {
			CommandAction action = actionSet.get(actionKey);
			if (action != null) {
				action.setCommand(command);
				break;
			}
		}
	}

	@Override
	public Component asComponent() {
		return root;
	}

	private void showTermDetails(Term term) {
		if (tree.areMultipleNodesSelected()) {
			multipleTemsLabel.setText(String.format(Const.LBL_SELECTED_TERMS, tree.getSelectionPaths().length));
			switchCards(TermDetailCard.LABEL);
		} else {
			switchCards(TermDetailCard.INFO);
			termView.setCodeMeaning(term.getCodeMeaning());
			termView.setCodeValue(term.getCodeValue());
			termView.setSchemaDesignator(term.getLexicon().getSchemaDesignator());
			termView.setSchemaVersion(term.getLexicon().getSchemaVersion());
			termView.setDescription(term.getDescription());		
		}
	}
	
	private void clearTermDetails() {
		switchCards(TermDetailCard.INFO);
		termView.setCodeMeaning(EMPTY);
		termView.setCodeValue(EMPTY);
		termView.setSchemaDesignator(EMPTY);
		termView.setSchemaVersion(EMPTY);
		termView.setDescription(EMPTY);		
	}
	
	private void switchCards(TermDetailCard card) {
		CardLayout cards = (CardLayout) termDetailsPanel.getLayout();
		cards.show(termDetailsPanel, card.toString());
	}
	
}
