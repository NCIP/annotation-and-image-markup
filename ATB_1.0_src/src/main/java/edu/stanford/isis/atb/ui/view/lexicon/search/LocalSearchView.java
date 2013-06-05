/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.lexicon.search;

import java.util.Collection;
import java.util.Set;

import javax.swing.tree.DefaultMutableTreeNode;

import edu.stanford.isis.atb.domain.lexicon.Lexicon;
import edu.stanford.isis.atb.domain.lexicon.Term;
import edu.stanford.isis.atb.service.Command;
import edu.stanford.isis.atb.ui.view.View;
import edu.stanford.isis.atb.ui.view.lexicon.LazyTermNodeValueLoader;

/**
 * @author Vitaliy Semeshko
 */
public interface LocalSearchView extends View {

	public void setSearchHistory(Set<String> history);
	
	public void setLexicons(Collection<Lexicon> lexicons);
	
	public void setLazyTermNodeValueLoader(LazyTermNodeValueLoader loader);
	
	public void showLexiconTree(Lexicon lexicon);
	
	public void expandTermPath(Term termPath);
	
	public void selectDirectChildrenOfLastSelectedNode();
	
	public void selectAllNestedNodesOfLastSelectedNode();
	
	public Collection<Lexicon> getSelectedLexicons();
	
	public String getSearchText();
	
	public void setSearchResult(Collection<Term> terms);
	
	public void setSearchCommand(Command command);
	
	public void setSelectCommand(Command command);

	public boolean isExactMatch();
	
	public Collection<DefaultMutableTreeNode> getSelectedTreeNodes();
	
	// listeners
	
	public void addTermSelectionListener(TermSelectionListener listener);
	
	// view
	
	public void clear(boolean clearSearchText);
	
	public void setInitialFocus();
	
	public void setBatchMode(boolean isBatch);
	
	// commands
	
	public void setCommand(Object actionKey, Command command);
	
	/**
	 * Listeners of term selections should implement this interface.
	 * 
	 * @author Vitaliy Semeshko
	 */
	public interface TermSelectionListener {
		
		public void onTermSelected(Term term);
		
	}
	
	public enum TermSearchAction {
		SELECT_DIRECT_CHILDREN,
		SELECT_ALL_NESTED_TERMS;
	}
	
}
