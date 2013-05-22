/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.widget.tree.renderer.lexicon;

import java.awt.Component;
import java.util.HashMap;
import java.util.Map;

import javax.swing.JTree;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeCellRenderer;

import edu.stanford.isis.atb.ui.model.tree.LexiconNodeType;
import edu.stanford.isis.atb.ui.model.tree.LexiconNodeValue;
import edu.stanford.isis.atb.ui.view.widget.tree.renderer.ElementRenderer;
import edu.stanford.isis.atb.ui.view.widget.tree.renderer.RenderInfo;

/**
 * Custom tree node renderer.
 * 
 * @author Vitaliy Semeshko
 */
public class LexiconTreeNodeRenderer extends DefaultTreeCellRenderer {

	@SuppressWarnings("rawtypes")
	private Map<LexiconNodeType, ElementRenderer> renderers = new HashMap<LexiconNodeType, ElementRenderer>();
	
	public LexiconTreeNodeRenderer() {
		renderers.put(LexiconNodeType.LEXICON, new LexiconRenderer());
		renderers.put(LexiconNodeType.TERM, new TermRenderer());
	}
	
	public Component getTreeCellRendererComponent(JTree tree, Object value, boolean sel, boolean expanded,
			boolean leaf, int row, boolean hasFocus) {
		// basic operations
		super.getTreeCellRendererComponent(tree, value, sel, expanded, leaf, row, hasFocus);
		
		// render node according to the type
		renderNode(((DefaultMutableTreeNode) value).getUserObject());

		return this;
	}

	@SuppressWarnings({ "rawtypes", "unchecked" })
	private void renderNode(Object value) {
		if (value instanceof LexiconNodeValue) {
			LexiconNodeValue nodeValue = ((LexiconNodeValue) value);
			
			ElementRenderer renderer = renderers.get(nodeValue.getNodeType());
			
			if (renderer == null) {
				throw new RuntimeException("No renderer found for node type: " + nodeValue.getNodeType());
			}
			
			RenderInfo info = renderer.collectRenderInfo(nodeValue.getValue());
			
			setText(info.getText());
			setToolTipText(info.getToolTipText());
			setIcon(info.getIcon());
		}
	}

}
