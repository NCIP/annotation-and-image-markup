/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.lexicon.search;

import java.awt.Component;
import java.util.Collection;

import edu.stanford.isis.atb.domain.LexiconTermAttributes;
import edu.stanford.isis.atb.service.Command;
import edu.stanford.isis.atb.ui.view.View;

/**
 * @author Vitaliy Semeshko
 */
public interface SearchView extends View {

	public void setLocalSearchTab(Component tab);
	
	public void setRemoteSearchTab(Component tab);
	
	public void showAsDialog(boolean showRightPane, Command afterShowing);
	
	public void setAllowedTerms(Collection<LexiconTermAttributes> terms);
	
	public void addAllowedTerm(LexiconTermAttributes term);
	
	public Collection<LexiconTermAttributes> getAllowedTerms();
	
	// commands
	
	public void setSubmitCommand(Command command);
	
}
