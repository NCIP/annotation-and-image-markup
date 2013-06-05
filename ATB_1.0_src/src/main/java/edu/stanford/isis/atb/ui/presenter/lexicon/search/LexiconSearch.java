/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.presenter.lexicon.search;

import edu.stanford.isis.atb.ui.presenter.lexicon.search.SearchPresenter.LexiconSearchMode;

/**
 * @author Vitaliy Semeshko
 */
public interface LexiconSearch {

	public void startSearch(LexiconSearchMode mode);
	
	public void setSingleTermAcceptor(CanAcceptSingleTerm singleTermAcceptor);
	
	public void setMultipleTermsAcceptor(CanAcceptMultipleTerms multipleTermsAcceptor);
	
}
