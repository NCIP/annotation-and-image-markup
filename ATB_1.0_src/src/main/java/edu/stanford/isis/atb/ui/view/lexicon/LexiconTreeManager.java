/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.lexicon;

import edu.stanford.isis.atb.domain.lexicon.Lexicon;
import edu.stanford.isis.atb.domain.lexicon.Term;

/**
 * @author Vitaliy Semeshko
 */
public interface LexiconTreeManager {
	
	public void setLexicon(Lexicon lexicon, boolean selectRoot);
	
	public void addTerm(Term term);
	
	public void clear();
	
	public void removeLastSelectedNode();
	
	public void refreshLastSelectedNode();
	
	public void selectRootNode();
	
	public void expandTermPath(Term termPath);
	
	public void selectDirectChildrenOfLastSelectedNode();
	
	public void selectAllNestedNodesOfLastSelectedNode();
	
}
