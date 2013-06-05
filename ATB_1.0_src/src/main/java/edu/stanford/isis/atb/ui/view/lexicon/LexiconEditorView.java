/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.lexicon;

import java.awt.Component;

import edu.stanford.isis.atb.domain.lexicon.Lexicon;
import edu.stanford.isis.atb.domain.lexicon.Term;
import edu.stanford.isis.atb.service.Command;
import edu.stanford.isis.atb.ui.model.tree.LexiconNodeType;
import edu.stanford.isis.atb.ui.view.View;

/**
 * @author Vitaliy Semeshko
 */
public interface LexiconEditorView extends View {

	// data
	
	public void showLexicon(Lexicon lexicon);
	
	public <T> T getSelectedNodeValue();
	
	public void setLazyTermNodeValueLoader(LazyTermNodeValueLoader loader);
	
	// commands
	
	public void setCommand(Object actionKey, Command command);
	
	public void setShowFormCommand(LexiconNodeType nodeType, Command command);
	
	// view
	
	public void hideEditForm();
	
	public void showEditForm(Component c);
	
	public void clear();

	public void selectRootNode();
	
	public void expandTermPath(Term termPath);
	
	public LexiconTreeManager getTreeManager();
	
	public enum LexiconAction {
		ADD_TERM;
	}
	
	public enum TermAction {
		DELETE,
		ADD_TERM;
	}

}
