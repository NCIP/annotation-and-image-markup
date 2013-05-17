/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.presenter.lexicon.search;

import java.util.Collection;
import java.util.List;

import edu.stanford.isis.atb.domain.LexiconTermAttributes;
import edu.stanford.isis.atb.domain.template.CodedTerm;

/**
 * Implementors can accept multiple lexicon terms selected in search dialog.
 * 
 * @author Vitaliy Semeshko
 */
public interface CanAcceptMultipleTerms {

	public void accept(Collection<LexiconTermAttributes> addedItems, List<CodedTerm> removedTerms);
	
}
