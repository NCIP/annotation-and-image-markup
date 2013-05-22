/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.widget.tree;

import edu.stanford.isis.atb.ui.model.tree.LexiconNodeValue;
import edu.stanford.isis.atb.ui.view.widget.tree.renderer.lexicon.LexiconTreeNodeRenderer;

/**
 * @author Vitaliy Semeshko
 */
public class LexiconTree extends AbstractTree<LexiconNodeValue> {

	public LexiconTree() {
		super(new LexiconTreeNodeRenderer());
	}
	
}
