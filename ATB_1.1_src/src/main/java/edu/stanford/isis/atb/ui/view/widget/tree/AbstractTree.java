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

package edu.stanford.isis.atb.ui.view.widget.tree;

import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.concurrent.TimeUnit;

import javax.swing.JPopupMenu;
import javax.swing.JTree;
import javax.swing.SwingUtilities;
import javax.swing.ToolTipManager;
import javax.swing.event.TreeSelectionEvent;
import javax.swing.event.TreeSelectionListener;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.TreeCellRenderer;
import javax.swing.tree.TreeModel;
import javax.swing.tree.TreePath;
import javax.swing.tree.TreeSelectionModel;

import edu.stanford.isis.atb.system.exception.ATBException;
import edu.stanford.isis.atb.ui.model.tree.NodeValue;

/**
 * Template tree widget.
 * 
 * @author Vitaliy Semeshko
 */
@SuppressWarnings("serial")
public abstract class AbstractTree<N extends NodeValue<?>> extends JTree {

	private JPopupMenu contextMenu;
	
	private List<NodeSelectionListener<N>> nodeSelectionListeners = new ArrayList<NodeSelectionListener<N>>();

	private boolean selectionListenersEnabled = true;
	
	public AbstractTree(TreeCellRenderer renderer) {
		// start with empty model
		super((TreeModel) null);

		// create a tree that allows one selection at a time.
		getSelectionModel().setSelectionMode(TreeSelectionModel.SINGLE_TREE_SELECTION);

		// set custom renderer
		setCellRenderer(renderer);

		// enable tool-tips
		ToolTipManager.sharedInstance().registerComponent(this);
		ToolTipManager.sharedInstance().setDismissDelay((int) TimeUnit.SECONDS.toMillis(10));
		ToolTipManager.sharedInstance().setInitialDelay(500);
		ToolTipManager.sharedInstance().setReshowDelay(500);
		
		addMouseListener(new MouseAdapter() {
			@Override
			public void mousePressed(MouseEvent e) {
				if (SwingUtilities.isRightMouseButton(e)) {
					int row = getRowForLocation(e.getX(), e.getY());

					if (isMultiSelectionEnabled() && e.isControlDown() ) {
						addSelection(new int[] {row});
					} else {
						setSelectionRow(row);
					}
				}
				if (getLastSelectedPathComponent() != null) {
					showPopup(e);
				}
			}

			@Override
			public void mouseReleased(MouseEvent e) {
				showPopup(e);
			}

			private void showPopup(MouseEvent e) {
				if (e.isPopupTrigger()) {
					if (contextMenu != null) {
						contextMenu.show(e.getComponent(), e.getX(), e.getY());
					}
				}
			}
		});
		
		addTreeSelectionListener(new TreeSelectionListener() {
			@Override
			public void valueChanged(TreeSelectionEvent e) {
				fireCurrentNodeSelected();
			}
		});
	}

	public void fireCurrentNodeSelected() {
		N nodeValue = getSelectedNodeValue();
		
		if (nodeValue == null) {
			// nothing selected	
			return;
		}
		
		if (selectionListenersEnabled) {
			for (NodeSelectionListener<N> listener : nodeSelectionListeners) {
				listener.onNodeSelected(nodeValue);
			}
		}		
	}

	@SuppressWarnings("unchecked")
	public N getSelectedNodeValue() {
		DefaultMutableTreeNode node = getLastSelectedNode();
		return node == null ? null : (N) node.getUserObject();
	}
	
	public void enableContextMenu() {
		 contextMenu = new JPopupMenu();
	}
	
	public JPopupMenu getContextMenu() {
		if (contextMenu == null) {
			throw new ATBException("Context menu was not enabled for the tree.");
		}
		return contextMenu;
	}
	
	public void addNodeSelectionListener(NodeSelectionListener<N> listener) {
		nodeSelectionListeners.add(listener);
	}
	
	/**
	 * Set selection path without firing event.
	 * 
	 * @param path the <code>TreePath</code> specifying the node to select
	 */
	public void setSelectionPathSilently(TreePath path) {
		boolean listenersEnabled = selectionListenersEnabled; 
		// disable
		selectionListenersEnabled = false;
		try {
			super.setSelectionPath(path);
		} finally {
			// restore
			selectionListenersEnabled = listenersEnabled;
		}
	}
	
	public DefaultMutableTreeNode getLastSelectedNode() {
		return (DefaultMutableTreeNode) getLastSelectedPathComponent();
	}
	
	public List<DefaultMutableTreeNode> getSelectedNodes() {
		TreePath[] paths = getSelectionPaths();
		if (paths != null && paths.length > 0) {
			List<DefaultMutableTreeNode> nodes = new ArrayList<DefaultMutableTreeNode>(); 
			for (TreePath path : paths) {
				nodes.add((DefaultMutableTreeNode) path.getLastPathComponent());
			}
			return nodes;
		}
		return Collections.emptyList();
	}
	
	public boolean areMultipleNodesSelected() {
		TreePath[] paths = getSelectionPaths();
		return paths != null && paths.length > 1;
	}
	
	public boolean isMultiSelectionEnabled() {
		return getSelectionModel().getSelectionMode() == TreeSelectionModel.CONTIGUOUS_TREE_SELECTION
				|| getSelectionModel().getSelectionMode() == TreeSelectionModel.DISCONTIGUOUS_TREE_SELECTION;
	}
	
	public void addSelection(int[] selection) {
		int[] currentSelection = getSelectionRows();
		if (currentSelection != null && currentSelection.length > 0) {
			int[] targetSelection = new int[(currentSelection != null ? currentSelection.length : 0) + selection.length];
			
			// merge previous selection with newly selected node
			System.arraycopy(currentSelection, 0, targetSelection, 0, currentSelection.length);
			System.arraycopy(selection, 0, targetSelection, currentSelection.length, selection.length);
			setSelectionRows(targetSelection);
		} else {
			setSelectionRows(selection);
		}
	}
	
	public void addSelection(TreePath[] selection) {
		TreePath[] currentSelection = getSelectionPaths();
		if (currentSelection != null && currentSelection.length > 0) {
			TreePath[] targetSelection = new TreePath[(currentSelection != null ? currentSelection.length : 0) + selection.length];
			
			// merge previous selection with newly selected node
			System.arraycopy(currentSelection, 0, targetSelection, 0, currentSelection.length);
			System.arraycopy(selection, 0, targetSelection, currentSelection.length, selection.length);
			setSelectionPaths(targetSelection);
		} else {
			setSelectionPaths(selection);
		}
	}
	
	/**
	 * Tree node selection listener.
	 * 
	 * @author Vitaliy Semeshko
	 */
	public interface NodeSelectionListener<N> {
		
		public void onNodeSelected(N nodeValue);
		
	}
	
}
