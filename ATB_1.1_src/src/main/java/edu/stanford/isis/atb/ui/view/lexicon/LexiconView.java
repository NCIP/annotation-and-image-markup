/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.lexicon;

import java.util.Collection;

import edu.stanford.isis.atb.domain.lexicon.Lexicon;
import edu.stanford.isis.atb.service.Command;
import edu.stanford.isis.atb.ui.view.CanShowEditForm;
import edu.stanford.isis.atb.ui.view.View;

/**
 * @author Vitaliy Semeshko
 */
public interface LexiconView extends View, CanShowEditForm {

	public void setLexicons(Collection<Lexicon> lexicons);
	
	public Lexicon getActiveLexicon();
	
	public void setActiveLexicon(Lexicon lexicon);
	
	public void clearSelection();
	
	// commands
	
	public void setCommand(LexiconEditAction actionKey, Command command);
	
	// set listeners
	
	public void addLexiconSelectionListeners(LexiconSelectionListener ... listeners);
	
	/**
	 * Listeners of lexicon selections should implement this interface.
	 * 
	 * @author Vitaliy Semeshko
	 */
	public interface LexiconSelectionListener {
		
		public void onLexiconSelected(Lexicon lexicon);
		
	}
	
	public enum LexiconEditAction {
		CREATE,
		EDIT,
		DELETE,
		SEARCH,
		IMPORT_EXPORT,
		IMPORT,
		EXPORT;
	}
	
}
