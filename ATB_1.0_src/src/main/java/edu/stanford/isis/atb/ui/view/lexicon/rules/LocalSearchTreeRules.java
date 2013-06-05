/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.lexicon.rules;

import edu.stanford.isis.atb.domain.lexicon.Lexicon;
import edu.stanford.isis.atb.domain.lexicon.Term;
import edu.stanford.isis.atb.ui.action.ActionSet;
import edu.stanford.isis.atb.ui.action.CommandAction;
import edu.stanford.isis.atb.ui.model.tree.LexiconNodeValue;
import edu.stanford.isis.atb.ui.view.lexicon.search.LocalSearchView.TermSearchAction;

/**
 * Local search tree rules. 
 * 
 * @author Vitaliy Semeshko
 */
public class LocalSearchTreeRules {

	public void applyRulesForNode(LexiconNodeValue nodeValue, ActionSet actions) {
		
		// firstly enable all
		for (CommandAction action : actions.getAll()) {
			action.setEnabled(true);
		}
		
		// after apply rules to disable some actions
		switch (nodeValue.getNodeType()) {
		case LEXICON:
			applyLexiconRules((Lexicon) nodeValue.getValue(), actions);
			break;
		case TERM:
			applyTermRules((Term) nodeValue.getValue(), actions);
			break;
		default:
			throw new IllegalArgumentException("Unknown node type: " + nodeValue.getNodeType());
		}
	}
	
	private void applyLexiconRules(Lexicon lexicon, ActionSet actions) {
		// do nothing
	}
	
	private void applyTermRules(Term term, ActionSet actions) {
		if (term.isEmpty()) {
			disableAction(TermSearchAction.SELECT_DIRECT_CHILDREN, actions);
			disableAction(TermSearchAction.SELECT_ALL_NESTED_TERMS, actions);
		}
	}
	
	private void disableAction(Object actionKey, ActionSet actions) {
		CommandAction action = actions.get(actionKey);
		if (action != null) {
			action.setEnabled(false);
		}
	}
	
}
