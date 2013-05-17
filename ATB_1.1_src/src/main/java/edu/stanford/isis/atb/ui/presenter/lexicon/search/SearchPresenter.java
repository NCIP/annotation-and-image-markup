/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.presenter.lexicon.search;

import static edu.stanford.isis.atb.ui.Const.MSG_TERM_ALREADY_SELECTED;

import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

import javax.swing.JLabel;

import org.apache.commons.collections.CollectionUtils;

import edu.stanford.isis.atb.domain.LexiconTermAttributes;
import edu.stanford.isis.atb.domain.lexicon.Term;
import edu.stanford.isis.atb.domain.template.CodedTerm;
import edu.stanford.isis.atb.service.Command;
import edu.stanford.isis.atb.system.exception.ATBException;
import edu.stanford.isis.atb.ui.model.TermSearchItem;
import edu.stanford.isis.atb.ui.presenter.AbstractPresenter;
import edu.stanford.isis.atb.ui.view.lexicon.search.SearchView;

/**
 * Lexicon Search Presenter.
 * 
 * @author Vitaliy Semeshko
 */
public class SearchPresenter extends AbstractPresenter<SearchView> implements LexiconSearch {

	private LocalSearchPresenter localSearchPresenter;
	
	private CanAcceptSingleTerm singleTermAcceptor;
	
	private CanAcceptMultipleTerms multipleTermsAcceptor;
	
	private LexiconSearchMode searchMode;
	
	private List<CodedTerm> existingTerms;
	
	public static enum LexiconSearchMode {
		SINGLE,
		SINGLE_LOCAL_ONLY,
		BATCH;
	}
	
	public SearchPresenter(SearchView view) {
		super(view);
	}
	
	public void setLocalSearchPresenter(LocalSearchPresenter localSearchPresenter) {
		this.localSearchPresenter = localSearchPresenter;
	}

	public void setExistingTerms(Collection<? extends CodedTerm> terms) {
		existingTerms = new ArrayList<CodedTerm>(terms);
		view.setAllowedTerms(new ArrayList<LexiconTermAttributes>(terms));
	}
	
	@Override
	public void setSingleTermAcceptor(CanAcceptSingleTerm singleTermAcceptor) {
		this.singleTermAcceptor = singleTermAcceptor;
	}

	@Override
	public void setMultipleTermsAcceptor(CanAcceptMultipleTerms multipleTermsAcceptor) {
		this.multipleTermsAcceptor = multipleTermsAcceptor;
	}

	@Override
	public void startSearch(LexiconSearchMode searchMode) {
		this.searchMode = searchMode; 
		
		// initialize before showing
		localSearchPresenter.beforeShowingDialog(searchMode == LexiconSearchMode.BATCH);
		
		view.showAsDialog(searchMode == LexiconSearchMode.BATCH, new Command() {
			@Override
			public void execute() {
				localSearchPresenter.onShowingDialog();				
			}
		});
	}
	
	@Override
	public void bindView() {
		view.setLocalSearchTab(localSearchPresenter.getView().asComponent());
		view.setRemoteSearchTab(new JLabel("TODO"));
		
		// bind commands
		view.setSubmitCommand(new Command() {
			@Override
			public void execute() {
				switch (searchMode) {
				case SINGLE:
				case SINGLE_LOCAL_ONLY:
					returnSingleTerm();
					break;
				case BATCH:
					returnMultipleTerms();
					break;
				}
			}
		});
		
		localSearchPresenter.setSelectCommand(new Command() {
			@Override
			public void execute() {
				List<? extends LexiconTermAttributes> newTerms = localSearchPresenter.getSelectedTerms();
				for (LexiconTermAttributes newTerm : newTerms) {
					if (newTerms != null) {
						// only add if there is no such term
						for (LexiconTermAttributes term : view.getAllowedTerms()) {
							if (newTerm.getCodeValue().equals(term.getCodeValue()) &&
									newTerm.getCodeMeaning().equals(term.getCodeMeaning()) &&
									newTerm.getSchemaDesignator().equals(term.getSchemaDesignator()) &&
									newTerm.getSchemaVersion().equals(term.getSchemaVersion())) {
								// notify with message
								view.showInformation(String.format(MSG_TERM_ALREADY_SELECTED, term.getCodeMeaning()));
								return;
							}
						}
						view.addAllowedTerm(newTerm);
					}
				}
			}
		});
	}
	
	private void returnSingleTerm() {
		if (singleTermAcceptor == null) {
			throw new ATBException("No single term acceptor defined");
		}
		
		List<Term> terms = localSearchPresenter.getSelectedTerms();
		
		if (CollectionUtils.isNotEmpty(terms)) {
			singleTermAcceptor.accept(new TermSearchItem(terms.get(0)));
		}
	}
	
	private void returnMultipleTerms() {
		if (multipleTermsAcceptor == null) {
			throw new ATBException("No multiple terms acceptor defined");
		}
		
		// find added terms
		List<LexiconTermAttributes> addedTerms = new ArrayList<LexiconTermAttributes>();
		for (LexiconTermAttributes term : view.getAllowedTerms()) {
			boolean found = false;
			for (CodedTerm existingTerm : existingTerms) {
				if (existingTerm.equals(term)) {
					found = true;
					break;
				}
			}
			// if not found in list of existing terms (initial) then was added
			if (!found) {
				addedTerms.add(term);
			}
		}
		
		// find removed terms
		List<CodedTerm> removedTerms = new ArrayList<CodedTerm>();
		for (CodedTerm existingTerm : existingTerms) {
			boolean found = false;
			for (LexiconTermAttributes term : view.getAllowedTerms()) {
				if (existingTerm.equals(term)) {
					found = true;
					break;
				}
			}
			// if not found in list of added terms then was deleted
			if (!found) {
				removedTerms.add(existingTerm);
			}
		}

		multipleTermsAcceptor.accept(addedTerms, removedTerms);		
	}
	
}
