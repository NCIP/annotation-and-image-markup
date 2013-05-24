/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.model;

import edu.stanford.isis.atb.domain.LexiconTermAttributes;
import edu.stanford.isis.atb.domain.lexicon.Term;
import edu.stanford.isis.atb.domain.template.CodedTerm;

/**
 * @author Vitaliy Semeshko
 */
public class TermSearchItem {

	private Term term;
	
	private LexiconTermAttributes codedTerm;
	
	public TermSearchItem(Term term) {
		this.term = term;
		CodedTerm codedTerm = new CodedTerm();
		codedTerm.setCodeMeaning(term.getCodeMeaning());
		codedTerm.setCodeValue(term.getCodeValue());
		codedTerm.setSchemaDesignator(term.getLexicon().getSchemaDesignator());
		codedTerm.setSchemaVersion(term.getLexicon().getSchemaVersion());
		this.codedTerm = codedTerm;
	}
	
	public TermSearchItem(LexiconTermAttributes codedTerm) {
		this.codedTerm = codedTerm;
	}

	public Term getTerm() {
		return term;
	}

	public LexiconTermAttributes getCodedTerm() {
		return codedTerm;
	}
	
}
