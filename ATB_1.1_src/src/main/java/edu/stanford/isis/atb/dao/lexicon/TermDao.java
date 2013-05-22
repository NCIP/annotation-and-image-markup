/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.dao.lexicon;

import java.util.Collection;

import edu.stanford.isis.atb.domain.lexicon.Term;

/**
 * @author Vitaliy Semeshko
 */
public interface TermDao {

	public Collection<Term> getAllTop(String termTable);
	
	public Collection<Term> getForExport(String termTable, int limitFrom, int limitSize);
	
	public int getTermCount(String termTable);
	
	public Collection<Term> find(String searchText, String termTable);
	
	public Collection<Term> getChildren(Term parent);
	
	public void insert(Term term);
	
	public void update(Term term);
	
	public void delete(Term term);
	
	public void dropTermTable(String termTable);
	
	public Term getParent(Term term);
	
}
