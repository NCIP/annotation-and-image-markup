/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.widget.tree;

import java.util.Collection;

import javax.swing.SwingWorker;
import javax.swing.event.TreeExpansionEvent;
import javax.swing.event.TreeWillExpandListener;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeModel;
import javax.swing.tree.ExpandVetoException;
import javax.swing.tree.MutableTreeNode;

import edu.stanford.isis.atb.service.Command;
import edu.stanford.isis.atb.system.exception.ATBException;

/**
 * @author Vitaliy Semeshko
 */
public class LazyTreeNode extends DefaultMutableTreeNode implements TreeWillExpandListener {

	private DefaultTreeModel model;
	
	private LazyNodeLoader nodeLoader;

	private Command afterLoadedCommand;
	
	private boolean empty;
	
	public LazyTreeNode(Object userObject, boolean isEmpty) {
		super(userObject);
		this.empty = isEmpty;
	}

	public void setModel(DefaultTreeModel model) {
		this.model = model;
	}
	
	public void setNodeLoader(LazyNodeLoader nodeLoader) {
		this.nodeLoader = nodeLoader;
	}
	
	public void setAfterLoadedCommand(Command afterLoadedCommand) {
		this.afterLoadedCommand = afterLoadedCommand;
	}

	/**
	 * Retrieve nodes on expand
	 */
	public void treeWillExpand(TreeExpansionEvent event) throws ExpandVetoException {
		if (this.equals(event.getPath().getLastPathComponent())) {
			if (getChildCount() > 0) {
				return;
			}
			SwingWorker<Collection<MutableTreeNode>, ?> worker = createSwingWorker();
			worker.execute();
		}
	}

	/**
	 * Define children nodes
	 * 
	 * @param nodes new nodes
	 */
	protected void setChildren(Collection<MutableTreeNode> nodes) {
		int i = 0;
		for (MutableTreeNode node : nodes) {
			model.insertNodeInto(node, this, i);
			i++;
		}
		
		// call command after all nodes were inserted
		if (afterLoadedCommand != null) {
			afterLoadedCommand.execute();
		}
	}
	
	/**
	 * Create worker that will load the nodes.
	 *  
	 * @return the newly created SwingWorker
	 */
	protected SwingWorker<Collection<MutableTreeNode>, ?> createSwingWorker() {

		SwingWorker<Collection<MutableTreeNode>, ?> worker = new SwingWorker<Collection<MutableTreeNode>, Object>() {
			@Override
			protected void done() {
				try {
					if (!isCancelled()) {
						Collection<MutableTreeNode> nodes = get();
						setAllowsChildren(!nodes.isEmpty());
						setChildren(nodes);
					}
				} catch (Exception e) {
					throw new ATBException(e);
				}
			}

			@Override
			protected Collection<MutableTreeNode> doInBackground() throws Exception {
				return nodeLoader.load();
			}

		};
		return worker;
	}
	
	public boolean isLeaf() {
		return !(!empty || getChildCount() > 0);
	}
	
	@Override
	public void treeWillCollapse(TreeExpansionEvent event) throws ExpandVetoException {}

	/**
	 * Used for loading child nodes of the {@link LazyTreeNode}.
	 * 
	 * @author Vitaliy Semeshko
	 */
	public interface LazyNodeLoader {
		
		public Collection<MutableTreeNode> load();
		
	}
	
}
