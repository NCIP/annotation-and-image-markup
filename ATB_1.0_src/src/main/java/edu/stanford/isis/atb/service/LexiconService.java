/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.service;

import java.io.File;
import java.util.Collection;

import edu.stanford.isis.atb.domain.lexicon.Lexicon;
import edu.stanford.isis.atb.domain.lexicon.Term;

/**
 * Lexicon service provides operations on lexicons.
 * 
 * @author Vitaliy Semeshko
 */
public interface LexiconService {

	public Collection<Lexicon> getLexicons();
	
	public void saveOrUpdateLexicon(Lexicon lexicon);
	
	public void deleteLexicon(Lexicon lexicon);
	
	public void getTerms(Lexicon lexicon);
	
	public Collection<Term> findTerms(String searchText, Lexicon lexicon, boolean exactMatch);
	
	public Collection<Term> getChildTerms(Term parent);
	
	public void saveOrUpdateTerm(Term term);
	
	public void deleteTerm(Term term);

	public Term getPathToTheRoot(Term term);
	
	public void importFromCsv(File path, WatchingCallback<Lexicon> callback);
	
	public void exportToCsv(Lexicon lexicon, File path, WatchingCallback<Void> callback);
	
}
