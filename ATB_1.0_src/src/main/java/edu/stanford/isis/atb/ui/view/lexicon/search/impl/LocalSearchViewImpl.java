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
