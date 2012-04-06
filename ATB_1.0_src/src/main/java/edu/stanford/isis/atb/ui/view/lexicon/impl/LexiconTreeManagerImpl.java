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
