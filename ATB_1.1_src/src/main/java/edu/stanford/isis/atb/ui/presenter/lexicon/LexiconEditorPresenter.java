/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.presenter.lexicon;

import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

import edu.stanford.isis.atb.domain.lexicon.Lexicon;
import edu.stanford.isis.atb.domain.lexicon.Term;
import edu.stanford.isis.atb.service.Command;
import edu.stanford.isis.atb.service.LexiconService;
import edu.stanford.isis.atb.ui.Const;
import edu.stanford.isis.atb.ui.model.tree.LexiconNodeType;
import edu.stanford.isis.atb.ui.presenter.AbstractPresenter;
import edu.stanford.isis.atb.ui.presenter.form.AbstractFormPresenter.FormSubmitListener;
import edu.stanford.isis.atb.ui.presenter.form.FormManager;
import edu.stanford.isis.atb.ui.presenter.lexicon.form.LexiconFormPresenter;
import edu.stanford.isis.atb.ui.presenter.lexicon.form.TermFormPresenter;
import edu.stanford.isis.atb.ui.view.lexicon.LazyTermNodeValueLoader;
import edu.stanford.isis.atb.ui.view.lexicon.LexiconEditorView;
import edu.stanford.isis.atb.ui.view.lexicon.LexiconEditorView.LexiconAction;
import edu.stanford.isis.atb.ui.view.lexicon.LexiconEditorView.TermAction;

/**
 * @author Vitaliy Semeshko
 */
public class LexiconEditorPresenter extends AbstractPresenter<LexiconEditorView> {

	private FormManager formManager = new FormManager();

	private LexiconService lexiconService;

	private List<LexiconChangeListener> lexiconChangeListeners = new ArrayList<LexiconChangeListener>();
	
	private List<LexiconContentChangeListener> lexiconContentChangeListeners = new ArrayList<LexiconContentChangeListener>();

	private Lexicon activeLexicon;

	public LexiconEditorPresenter(LexiconEditorView view) {
		super(view);
	}

	public void setLexiconService(LexiconService lexiconService) {
		this.lexiconService = lexiconService;
	}

	@Override
	public void bindView() {
		initLexiconActions();
		initTermActions();
		
		// set lazy node loader
		view.setLazyTermNodeValueLoader(new LazyTermNodeValueLoader() {
			@Override
			public Collection<Term> load(Term parent) {
				return lexiconService.getChildTerms(parent);
			}
		});
	}

	private void initLexiconActions() {
		view.setShowFormCommand(LexiconNodeType.LEXICON, new Command() {
			@Override
			public void execute() {
				if (activeLexicon != null) {
					showLexiconForm(activeLexicon, false);
				} else {
					view.showInformation(Const.MSG_NO_LEXICON_SELECTED);
				}
			}
		});

		view.setCommand(LexiconAction.ADD_TERM, new Command() {
			@Override
			public void execute() {
				Term newTerm = new Term();
				newTerm.setInitialized(false);
				// direct child of root (lexicon) node. It's level number is #2
				newTerm.setLevelNumber(2);
				Lexicon lexicon = view.getSelectedNodeValue();
				lexicon.addTerm(newTerm);
				lexiconService.saveOrUpdateTerm(newTerm);
				view.getTreeManager().addTerm(newTerm);
				notifyContentChanged(lexicon);
			}
		});
	}
	
	private void initTermActions() {
		view.setShowFormCommand(LexiconNodeType.TERM, new Command() {
			@Override
			public void execute() {
				Term term = view.getSelectedNodeValue();
				showTermForm(term, false);
			}
		});

		view.setCommand(TermAction.ADD_TERM, new Command() {
			@Override
			public void execute() {
				Term newTerm = new Term();
				newTerm.setInitialized(false);
				Term currentTerm = view.getSelectedNodeValue();
				newTerm.setLevelNumber(currentTerm.getLevelNumber() + 1);
				currentTerm.addTerm(newTerm);
				lexiconService.saveOrUpdateTerm(newTerm);
				view.getTreeManager().addTerm(newTerm);
				notifyContentChanged(currentTerm.getLexicon());
			}
		});
		
		view.setCommand(TermAction.DELETE, new Command() {
			@Override
			public void execute() {
				Term term = view.getSelectedNodeValue();
				lexiconService.deleteTerm(term);
				view.getTreeManager().removeLastSelectedNode();
				notifyContentChanged(term.getLexicon());
			}
		});
	}
	
	public void setActiveLexicon(Lexicon lexicon) {
		this.activeLexicon = lexicon;
		// load terms of the lexicon
		lexiconService.getTerms(lexicon);
		view.showLexicon(lexicon);
	}

	public void clear() {
		activeLexicon = null;
		view.clear();
	}

	public void editCurrentLexicon() {
		view.selectRootNode();
	}
	
	public void showLexiconForm(Lexicon value, boolean isCreation) {
		//TODO: optimize this (every call new listener is created)
		LexiconFormPresenter p = formManager.lexiconForm(new FormSubmitListener<Lexicon>() {
			@Override
			public void onFormSubmit(Lexicon value, boolean isCreation) {
				// save changes
				for (LexiconChangeListener listener : lexiconChangeListeners) {
					listener.onLexiconChanged(value);
				}
				value.setInitialized(true);
			}
		});
		p.setValue(value);
		view.showEditForm(p.prepareForm(isCreation));
	}
	
	public void showTermForm(Term value, boolean isCreation) {
		//TODO: optimize this (every call new listener is created)
		final TermFormPresenter p = formManager.termForm(null);
		p.setFormSubmitListener(new FormSubmitListener<Term>() {
			@Override
			public void onFormSubmit(Term value, boolean isCreation) {
				lexiconService.saveOrUpdateTerm(value);
				value.setInitialized(true);
				p.setValue(value);
				view.getTreeManager().refreshLastSelectedNode();
			}
		});
		p.setValue(value);
		view.showEditForm(p.prepareForm(isCreation));
	}

	private void notifyContentChanged(Lexicon lexicon) {
		for (LexiconContentChangeListener listener : lexiconContentChangeListeners) {
			listener.onLexiconContentChanged(lexicon);
		}
	}
	
	public void addLexiconChangeListener(LexiconChangeListener listener) {
		lexiconChangeListeners.add(listener);
	}
	
	public void addLexiconContentChangeListener(LexiconContentChangeListener listener) {
		lexiconContentChangeListeners.add(listener);
	}

	public void expandTermPath(Term termPath) {
		view.expandTermPath(termPath);
	}
	
	/**
	 * Implementors will be notified about changed lexicon.
	 * 
	 * @author Vitaliy Semeshko
	 */
	public interface LexiconChangeListener {

		/**
		 * Notify listeners that lexicon was changed.
		 * 
		 * @param lexicon lexicon that changed
		 */
		public void onLexiconChanged(Lexicon lexicon);

	}
	
	/**
	 * Implementors will be notified about changed lexicon's content.
	 * 
	 * @author Vitaliy Semeshko
	 */
	public interface LexiconContentChangeListener {
		
		/**
		 * Notify listeners that lexicon's content was changed.
		 * 
		 * @param lexicon lexicon that changed
		 */
		public void onLexiconContentChanged(Lexicon lexicon);
		
	}

}
