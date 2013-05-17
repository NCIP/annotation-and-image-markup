/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.presenter.lexicon.search;

import edu.stanford.isis.atb.ui.model.TermSearchItem;

/**
 * Implementors can accept single lexicon term selected in search dialog.
 * 
 * @author Vitaliy Semeshko
 */
public interface CanAcceptSingleTerm {

	public void accept(TermSearchItem searchItem);
	
}
