/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
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
