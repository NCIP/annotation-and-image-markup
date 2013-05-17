/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.lexicon.impl;

import static edu.stanford.isis.atb.ui.Const.HNT_ADD_TERM;
import static edu.stanford.isis.atb.ui.Const.HNT_DELETE_TERM;
import static edu.stanford.isis.atb.ui.model.tree.LexiconNodeType.LEXICON;
import static edu.stanford.isis.atb.ui.model.tree.LexiconNodeType.TERM;

import java.awt.Component;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import javax.swing.JPopupMenu;
import javax.swing.tree.DefaultMutableTreeNode;

import edu.stanford.isis.atb.domain.lexicon.Lexicon;
import edu.stanford.isis.atb.domain.lexicon.Term;
import edu.stanford.isis.atb.service.Command;
import edu.stanford.isis.atb.ui.Const;
import edu.stanford.isis.atb.ui.action.ActionSet;
import edu.stanford.isis.atb.ui.action.CommandAction;
import edu.stanford.isis.atb.ui.model.tree.LexiconNodeType;
import edu.stanford.isis.atb.ui.model.tree.LexiconNodeValue;
import edu.stanford.isis.atb.ui.view.AbstractView;
import edu.stanford.isis.atb.ui.view.CanShowEditForm;
import edu.stanford.isis.atb.ui.view.lexicon.LazyTermNodeValueLoader;
import edu.stanford.isis.atb.ui.view.lexicon.LexiconEditorView;
import edu.stanford.isis.atb.ui.view.lexicon.LexiconTreeManager;
import edu.stanford.isis.atb.ui.view.lexicon.rules.LexiconModificationRules;
import edu.stanford.isis.atb.ui.view.resources.ToolBarImageBundle;
import edu.stanford.isis.atb.ui.view.widget.ScrollableBlockWIthToolbar;
import edu.stanford.isis.atb.ui.view.widget.tree.AbstractTree.NodeSelectionListener;
import edu.stanford.isis.atb.ui.view.widget.tree.LexiconTree;

/**
 * @author Vitaliy Semeshko
 */
public class LexiconEditorViewImpl extends AbstractView implements LexiconEditorView {

	private CanShowEditForm editFormManager;
	
	private ScrollableBlockWIthToolbar root = new ScrollableBlockWIthToolbar();

	private LexiconTree tree = new LexiconTree();
	
	private LexiconTreeManager treeManager;

	private JPopupMenu contextMenu = new JPopupMenu();
	
	private ToolBarImageBundle images = ToolBarImageBundle.getInstance();

	private LexiconModificationRules modificationRules = new LexiconModificationRules();
	
	private Map<LexiconNodeType, Command> formShowCommands = new HashMap<LexiconNodeType, Command>();
	
	private List<ActionSet> actions = new ArrayList<ActionSet>();
	private ActionSet lexiconActions = new ActionSet();
	private ActionSet termActions = new ActionSet();
	
	private Map<LexiconNodeType, ActionSet> nodeActions = new HashMap<LexiconNodeType, ActionSet>();
	
	public LexiconEditorViewImpl() {
		root.setCaptionText(Const.LBL_LEXICON_TERMS);
		root.setMainComponent(tree);

		initTree();
		
		initNodeActions();
		
		actions.add(lexiconActions);
		actions.add(termActions);
		
		initLexiconActions();
		initTermActions();
	}

	public void setEditFormManager(CanShowEditForm editFormManager) {
		this.editFormManager = editFormManager;
	}
	
	private void initTree() {
		tree.enableContextMenu();
		
		tree.addNodeSelectionListener(new NodeSelectionListener<LexiconNodeValue>() {
			@Override
			public void onNodeSelected(LexiconNodeValue nodeValue) {
				ActionSet actions = nodeActions.get(nodeValue.getNodeType());
				
				// show/hide form
				Command showFormCommand = formShowCommands.get(nodeValue.getNodeType());
				if (showFormCommand != null) {
					showFormCommand.execute();
				} else {
					// hide edit form if no form to show
					hideEditForm();
				}
				
				tree.getContextMenu().removeAll();
				root.clearToolBar();
				
				if (actions != null) {
					// apply rules according to the node state
					modificationRules.applyRulesForNode(nodeValue, actions);
					
					// add actions to the toolbar and context menu 
					for (CommandAction action : actions.getAll()) {
						root.addToolBarAction(action);
						tree.getContextMenu().add(action);
					}
				}
			}
		});
		
	}
	
	private void initNodeActions() {
		nodeActions.put(LEXICON, lexiconActions);
		nodeActions.put(TERM, termActions);
	}
	
	private void initLexiconActions() {
		CommandAction addTerm = new CommandAction(HNT_ADD_TERM, images.getCreateAllowedTermIcon());
		lexiconActions.add(LexiconAction.ADD_TERM, addTerm);
	}
	
	private void initTermActions() {
		CommandAction addTerm = new CommandAction(HNT_ADD_TERM, images.getCreateAllowedTermIcon());
		termActions.add(TermAction.ADD_TERM, addTerm);
		
		CommandAction delete = new CommandAction(HNT_DELETE_TERM, images.getDeleteIcon());
		termActions.addSeparator();
		termActions.add(TermAction.DELETE, delete);
	}
	
	@Override
	public Component asComponent() {
		return root;
	}

	@SuppressWarnings("unchecked")
	@Override
	public <T> T getSelectedNodeValue() {
		DefaultMutableTreeNode node = tree.getLastSelectedNode();
		LexiconNodeValue nodeValue = ((LexiconNodeValue) node.getUserObject());
		return (T) nodeValue.getValue();
	}
	
	@Override
	public void setLazyTermNodeValueLoader(LazyTermNodeValueLoader loader) {
		treeManager = new LexiconTreeManagerImpl(tree, loader);
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
	public void setShowFormCommand(LexiconNodeType nodeType, Command command) {
		formShowCommands.put(nodeType, command);
	}
	
	// view

	@Override
	public void hideEditForm() {
		editFormManager.hideEditForm();
	}

	@Override
	public void showEditForm(Component c) {
		editFormManager.showEditForm(c, false);
	}

	@Override
	public void showLexicon(Lexicon lexicon) {
		treeManager.setLexicon(lexicon, true);
	}
	
	@Override
	public void clear() {
		treeManager.clear();
		root.clearToolBar();
		contextMenu.removeAll();		
	}

	@Override
	public void selectRootNode() {
		treeManager.selectRootNode();
	}

	@Override
	public LexiconTreeManager getTreeManager() {
		return treeManager;
	}

	@Override
	public void expandTermPath(Term termPath) {
		treeManager.expandTermPath(termPath);
	}
	
}
