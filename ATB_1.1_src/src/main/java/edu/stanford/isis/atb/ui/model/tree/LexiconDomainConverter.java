/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.model.tree;

import static edu.stanford.isis.atb.ui.model.tree.LexiconNodeType.LEXICON;
import static edu.stanford.isis.atb.ui.model.tree.LexiconNodeType.TERM;

import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeModel;
import javax.swing.tree.TreeModel;

import edu.stanford.isis.atb.domain.lexicon.Lexicon;
import edu.stanford.isis.atb.domain.lexicon.Term;
import edu.stanford.isis.atb.ui.view.widget.tree.LazyTreeNode;

/**
 * Provides methods to convert domain object that can be presented as tree nodes.
 * 
 * @author Vitaliy Semeshko
 */
public class LexiconDomainConverter {

	private static final LexiconDomainConverter instance = new LexiconDomainConverter();
	
	private LexiconDomainConverter() {}
	
	public static LexiconDomainConverter getInstance() {
		return instance;
	}
	
	/**
	 * Convert domain model to {@link TreeModel}.
	 * 
	 * @param t domain model to be converted.
	 * @return implementation of {@link TreeModel}
	 */
	public DefaultTreeModel lexicon(Lexicon value) {
		DefaultMutableTreeNode root = createNode(LEXICON, value);
		
		for (Term t : value.getTerms()) {
			root.add(term(t));
		}
		
		return new DefaultTreeModel(root);
	}
	
	public LazyTreeNode term(Term value) {
		LazyTreeNode node = new LazyTreeNode(new LexiconNodeValue(TERM, value), value.isEmpty()); 
				
		for (Term t : value.getTerms()) {
			node.add(term(t));
		}
		
		return node;
	}
	
	private DefaultMutableTreeNode createNode(LexiconNodeType type, Object userObject) {
		return new DefaultMutableTreeNode(new LexiconNodeValue(type, userObject));
	}
	
}
