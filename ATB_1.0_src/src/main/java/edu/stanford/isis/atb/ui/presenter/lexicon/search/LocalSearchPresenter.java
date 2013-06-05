/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.presenter.lexicon.search;

import java.util.ArrayList;
import java.util.Collection;
import java.util.LinkedHashSet;
import java.util.List;

import javax.swing.tree.DefaultMutableTreeNode;

import org.apache.commons.lang3.StringUtils;

import edu.stanford.isis.atb.domain.lexicon.Lexicon;
import edu.stanford.isis.atb.domain.lexicon.Term;
import edu.stanford.isis.atb.service.Command;
import edu.stanford.isis.atb.service.LexiconService;
import edu.stanford.isis.atb.system.UserSession;
import edu.stanford.isis.atb.ui.Const;
import edu.stanford.isis.atb.ui.model.tree.LexiconNodeValue;
import edu.stanford.isis.atb.ui.presenter.AbstractPresenter;
import edu.stanford.isis.atb.ui.view.lexicon.LazyTermNodeValueLoader;
import edu.stanford.isis.atb.ui.view.lexicon.search.LocalSearchView;
import edu.stanford.isis.atb.ui.view.lexicon.search.LocalSearchView.TermSearchAction;
import edu.stanford.isis.atb.ui.view.lexicon.search.LocalSearchView.TermSelectionListener;

/**
 * Local Lexicon Search Presenter.
 * 
 * @author Vitaliy Semeshko
 */
public class LocalSearchPresenter extends AbstractPresenter<LocalSearchView> {

	private static final int MIN_SEARCH_TEXT_LENGTH = 3;
	
	private LexiconService lexiconService;
	
	private UserSession session = UserSession.getInstance();
	
	public LocalSearchPresenter(LocalSearchView view) {
		super(view);
	}

	public void setLexiconService(LexiconService lexiconService) {
		this.lexiconService = lexiconService;
	}

	public void beforeShowingDialog(boolean isBatch) {
		// initialize before showing
		view.setLexicons(lexiconService.getLexicons());
		view.setBatchMode(isBatch);
		setSearchHistory();
		view.clear(true);
	}
	
	public void onShowingDialog() {
		view.setInitialFocus();
	}
	
	public List<Term> getSelectedTerms() {
		List<Term> terms = new ArrayList<Term>();
		Collection<DefaultMutableTreeNode> nodes = view.getSelectedTreeNodes();

		for (DefaultMutableTreeNode node : nodes) {
			LexiconNodeValue nodeValue = ((LexiconNodeValue) node.getUserObject());
			Object value = nodeValue.getValue();
			// skip non-Term nodes 
			if (value instanceof Term) {
				terms.add((Term) value);
			}
		}
		
		return terms;
	}

	@Override
	public void bindView() {
		view.setSearchCommand(new Command() {
			@Override
			public void execute() {
				String searchText = view.getSearchText();
				if (StringUtils.isEmpty(searchText)) {
					view.showInformation(Const.MSG_EMPTY_SEARCH_TEXT);
					return;
				} else if (searchText.length() < MIN_SEARCH_TEXT_LENGTH) {
					view.showInformation(Const.MSG_SHORT_SEARCH_TEXT);
					return;
				}
				
				Collection<Lexicon> lexicons = view.getSelectedLexicons();
				if (lexicons.isEmpty()) {
					view.showInformation(Const.MSG_NO_LEXICON_SELECTED_FOR_SEARCH);
					return;
				}
				
				view.clear(false);
				
				List<Term> searchResult = new ArrayList<Term>();
				
				for (Lexicon lexicon : lexicons) {
					Collection<Term> terms = lexiconService.findTerms(searchText, lexicon, view.isExactMatch());
					for (Term term : terms) {
						term.setLexicon(lexicon);
						searchResult.add(term);
					}
				}
				
				view.setSearchResult(searchResult);
				
				// save search in session
				session.addLocalSearchHistoryText(searchText);
				// update search history
				setSearchHistory();
			}
		});
		
		view.addTermSelectionListener(new TermSelectionListener() {
			@Override
			public void onTermSelected(Term term) {
				// load terms of the lexicon
				Lexicon lexicon = term.getLexicon();
				lexiconService.getTerms(lexicon);
				view.showLexiconTree(lexicon);
					
				// load term path (from the root to currently selected)
				Term termPath = lexiconService.getPathToTheRoot(term);
				view.expandTermPath(termPath);
			}
		});
		
		// set lazy node loader
		view.setLazyTermNodeValueLoader(new LazyTermNodeValueLoader() {
			@Override
			public Collection<Term> load(Term parent) {
				return lexiconService.getChildTerms(parent);
			}
		});
		
		bindTermActions();
	}
	
	private void bindTermActions() {
		view.setCommand(TermSearchAction.SELECT_DIRECT_CHILDREN, new Command() {
			@Override
			public void execute() {
				view.selectDirectChildrenOfLastSelectedNode();
			}
		});
		
		view.setCommand(TermSearchAction.SELECT_ALL_NESTED_TERMS, new Command() {
			@Override
			public void execute() {
				view.selectAllNestedNodesOfLastSelectedNode();
			}
		});
	}
	
	public void setSelectCommand(Command command) {
		view.setSelectCommand(command);
	}
	
	private void setSearchHistory() {
		view.setSearchHistory(new LinkedHashSet<String>(session.getLocalSearchHistory()));
	}
	
}
