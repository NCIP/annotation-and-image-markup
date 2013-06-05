/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.lexicon;

import java.util.Collection;

import edu.stanford.isis.atb.domain.lexicon.Term;

/**
 * Used for loading {@link Term}s.
 * 
 * @author Vitaliy Semeshko
 */
public interface LazyTermNodeValueLoader {
	
	/**
	 * Load terms by parent.
	 * 
	 * @param parent id of the term which is parent for being loaded
	 * @return <code>Collection</code> of {@link Term}s
	 */
	public Collection<Term> load(Term parent);
	
}
