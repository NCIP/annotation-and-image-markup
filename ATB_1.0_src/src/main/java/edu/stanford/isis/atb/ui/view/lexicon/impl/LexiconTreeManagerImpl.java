/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.lexicon.impl;

import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeModel;
import javax.swing.tree.MutableTreeNode;
import javax.swing.tree.TreeNode;
import javax.swing.tree.TreePath;

import edu.stanford.isis.atb.domain.lexicon.Lexicon;
import edu.stanford.isis.atb.domain.lexicon.Term;
import edu.stanford.isis.atb.service.Command;
import edu.stanford.isis.atb.ui.model.tree.LexiconDomainConverter;
import edu.stanford.isis.atb.ui.model.tree.LexiconNodeValue;
import edu.stanford.isis.atb.ui.view.lexicon.LazyTermNodeValueLoader;
import edu.stanford.isis.atb.ui.view.lexicon.LexiconTreeManager;
import edu.stanford.isis.atb.ui.view.widget.tree.LazyTreeNode;
import edu.stanford.isis.atb.ui.view.widget.tree.LazyTreeNode.LazyNodeLoader;
import edu.stanford.isis.atb.ui.view.widget.tree.LexiconTree;

/**
 * @author Vitaliy Semeshko
 */
public class LexiconTreeManagerImpl implements LexiconTreeManager {

	private LexiconTree tree;

	private LazyTermNodeValueLoader loader;
	
	private LexiconDomainConverter converter = LexiconDomainConverter.getInstance();

	public LexiconTreeManagerImpl(LexiconTree tree, LazyTermNodeValueLoader loader) {
		this.tree = tree;
		this.loader = loader;
	}

	@Override
	public void clear() {
		tree.setModel(null);
	}

	@Override
	public void setLexicon(Lexicon lexicon, boolean selectRoot) {
		DefaultTreeModel model = converter.lexicon(lexicon);
		tree.setModel(model);
		
		// initialize first level lazy nodes
		Object root = model.getRoot();
		for (int i = 0; i < model.getChildCount(root); i++) {
			Object firstLevelNode = model.getChild(root, i);
			if (firstLevelNode instanceof LazyTreeNode) {
				initLazyTermNode((LazyTreeNode) firstLevelNode);
			}
		}
		
		// select root (template node)
		if (selectRoot) {
			selectRootNode();
		}
	}

	@Override
	public void addTerm(Term term) {
		LazyTreeNode newNode = converter.term(term);
		
		// initialize lazy node 
		initLazyTermNode(newNode);
		
		MutableTreeNode node = tree.getLastSelectedNode();
		insertNode(newNode, node, node.getChildCount());
		scrollToNodeAndSelect(new TreePath(newNode.getPath()));
	}

	@Override
	public void removeLastSelectedNode() {
		DefaultMutableTreeNode node = tree.getLastSelectedNode();
		DefaultMutableTreeNode parentNode = (DefaultMutableTreeNode) node.getParent(); 

		if (parentNode != null) {
			removeNode(node);

			// select parent node
			tree.setSelectionPath(new TreePath(parentNode.getPath()));
		}
	}

	@Override
	public void refreshLastSelectedNode() {
		((DefaultTreeModel) tree.getModel()).nodeChanged(tree.getLastSelectedNode());
	}

	@Override
	public void selectRootNode() {
		// select root (template node)
		tree.setSelectionRow(0);
		scrollToNodeAndSelect(tree.getSelectionPath());
	}

	@Override
	public void expandTermPath(Term termPath) {
		DefaultTreeModel model = (DefaultTreeModel) tree.getModel();
		expandTermPath(model.getRoot(), termPath);
	}

	//TODO: review this method
	@Override
	public void selectDirectChildrenOfLastSelectedNode() {
		TreeNode node = tree.getLastSelectedNode();
		
		if (node instanceof LazyTreeNode) {
			final LazyTreeNode lazyNode = (LazyTreeNode) node;
			// if node is not a leaf and can be expanded
			if (!lazyNode.isLeaf()) {
				final TreePath path = new TreePath(lazyNode.getPath());
				if (!tree.isExpanded(path)) {
					
					// set command in order to select children and deselect parent after expanded
					lazyNode.setAfterLoadedCommand(new Command() {
						@Override
						public void execute() {
							tree.removeSelectionPath(path);
							tree.addSelection(getChildPaths(lazyNode));
						}
					});
					
					tree.expandPath(path);
				} else {
					tree.removeSelectionPath(path);
					tree.addSelection(getChildPaths(lazyNode));
				}
			}
		}
	}
	
	@Override
	public void selectAllNestedNodesOfLastSelectedNode() {
		TreeNode node = tree.getLastSelectedNode();
		
		if (node instanceof LazyTreeNode) {
			List<TreePath> paths = expandLazyNodeAndCollectChildrenPaths(new ArrayList<TreePath>(), (LazyTreeNode) node);
			tree.removeSelectionPath(new TreePath(((DefaultMutableTreeNode) node).getPath()));
			
			TreePath[] p = new TreePath[paths.size()];
			for (int i = 0; i < paths.size(); i++) {
				TreePath path = paths.get(i);
				p[i] = path;
			}

			tree.addSelection(p);
		}
	}

	//TODO: improve functionality of this method
	private List<TreePath> expandLazyNodeAndCollectChildrenPaths(final List<TreePath> paths, final LazyTreeNode lazyNode) {
		final DefaultTreeModel model = (DefaultTreeModel) tree.getModel();
		
		// if node is not a leaf and can be expanded
		if (!lazyNode.isLeaf()) {
			final TreePath path = new TreePath(lazyNode.getPath());
			if (!tree.isExpanded(path)) {
				// set command in order to select children and deselect parent after expanded
				lazyNode.setAfterLoadedCommand(new Command() {
					@Override
					public void execute() {
						int childCount = model.getChildCount(lazyNode);
						
						for (int i = 0; i < childCount; i++) {
							Object o = model.getChild(lazyNode, i);
							if (o instanceof LazyTreeNode) {
								DefaultMutableTreeNode childNode = (DefaultMutableTreeNode) o;
								
								//paths.add(new TreePath(childNode.getPath()));
								tree.addSelection(new TreePath[] {new TreePath(childNode.getPath())});
								
								expandLazyNodeAndCollectChildrenPaths(paths, (LazyTreeNode) o);
							}
						}
					}
				});
				tree.expandPath(path);
			} else {
				int childCount = model.getChildCount(lazyNode);
				
				for (int i = 0; i < childCount; i++) {
					Object o = model.getChild(lazyNode, i);
					if (o instanceof LazyTreeNode) {
						DefaultMutableTreeNode childNode = (DefaultMutableTreeNode) o;
						
						//paths.add(new TreePath(childNode.getPath()));
						tree.addSelection(new TreePath[] {new TreePath(childNode.getPath())});
						
						expandLazyNodeAndCollectChildrenPaths(paths, (LazyTreeNode) o);
					}
				}
			}
		}
		return paths;
	}
	
	/**
	 * Get paths of child nodes by parent node.
	 * 
	 * @param parent parent node
	 * @return array of TreePath pointing to child nodes
	 */
	private TreePath[] getChildPaths(TreeNode parent) {
		final DefaultTreeModel model = (DefaultTreeModel) tree.getModel();
		int childCount = model.getChildCount(parent);
		TreePath[] children = new TreePath[childCount];
		
		for (int i = 0; i < childCount; i++) {
			Object o = model.getChild(parent, i);
			if (o instanceof DefaultMutableTreeNode) {
				DefaultMutableTreeNode childNode = (DefaultMutableTreeNode) o;
				children[i] = new TreePath(childNode.getPath());
			}
		}
		return children;
	}
	
	//TODO: review this method
	private void expandTermPath(Object parentNode, final Term term) {
		DefaultTreeModel model = (DefaultTreeModel) tree.getModel();
		
		for (int i = 0; i < model.getChildCount(parentNode); i++) {
			Object node = model.getChild(parentNode, i);
			if (node instanceof LazyTreeNode) {
				final LazyTreeNode lazyNode = (LazyTreeNode) node;
				LexiconNodeValue nodeValue = (LexiconNodeValue) lazyNode.getUserObject();
				
				// node on current level was found
				if (nodeValue.getValue().equals(term)) {
					// select if this node is last in the path
					if (term.getTerms().isEmpty()) {
						scrollToNodeAndSelect(new TreePath(lazyNode.getPath()));
					} else {
						lazyNode.setAfterLoadedCommand(new Command() {
							@Override
							public void execute() {
								// recursively call for nested lazy nodes (until reach the last one)
								for (Term childTerm : term.getTerms()) {
									expandTermPath(lazyNode, childTerm);
									break;
								}
							}
						});
						tree.expandPath(new TreePath(lazyNode.getPath()));
					}
				}
			}
		}
	}
	
	private void initLazyTermNode(LazyTreeNode lazyNode) {
		LexiconNodeValue userObject = (LexiconNodeValue) lazyNode.getUserObject();
		final Term term = userObject.getValue();
		
		// lazy nodes listen for the tree events
		tree.addTreeWillExpandListener(lazyNode);
		
		// lazy nodes manipulate the model
		lazyNode.setModel((DefaultTreeModel) tree.getModel());
		
		// create loader
		lazyNode.setNodeLoader(new LazyNodeLoader() {
			@Override
			public Collection<MutableTreeNode> load() {
				// load child terms
				Collection<Term> childTerms = loader.load(term);
				
				// prepare list for nodes
				List<MutableTreeNode> childNodes = new ArrayList<MutableTreeNode>(childTerms.size());
				
				for (Term childTerm : childTerms) {
					term.addTerm(childTerm);
					
					LazyTreeNode childNode = converter.term(childTerm);
					
					// initialize lazy loading on child objects
					initLazyTermNode(childNode);
					
					childNodes.add(childNode);
				}
				
				return childNodes;
			}
		});
	}
	
	private void scrollToNodeAndSelect(TreePath path) {
		tree.scrollPathToVisible(path);
		tree.setSelectionPath(path);		
	}
	
	//TODO: this is not used any more
//	private void scrollToNodeAndSelectSilently(TreePath path) {
//		tree.scrollPathToVisible(path);
//		tree.setSelectionPathSilently(path);
//	}

	private void insertNode(MutableTreeNode newNode, MutableTreeNode node, int index) {
		((DefaultTreeModel) tree.getModel()).insertNodeInto(newNode, node, index);
	}

	private void removeNode(MutableTreeNode node) {
		((DefaultTreeModel) tree.getModel()).removeNodeFromParent(node);
	}
	
}
