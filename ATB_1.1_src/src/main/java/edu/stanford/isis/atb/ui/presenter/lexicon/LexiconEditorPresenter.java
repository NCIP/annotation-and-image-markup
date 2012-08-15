/*
 * Copyright Notice. Copyright 2011 Northwestern University and Stanford
 * University (“caBIG® Participant”). AIM Template Enterprise Service conforms
 * to caBIG® technical specifications and is part of the caBIG® initiative. The
 * software subject to this notice and license includes human readable source
 * code form, machine readable, binary, object code form and related
 * documentation (the “caBIG® Software”).
 *
 * This caBIG® Software License (the “License”) is between the National Cancer
 * Institute (NCI) and You. “You (or “Your”) shall mean a person or an entity,
 * and all other entities that control, are controlled by, or are under common
 * control with the entity. “Control” for purposes of this definition means (i)
 * the direct or indirect power to cause the direction or management of such
 * entity, whether by contract or otherwise, or (ii) ownership of fifty percent
 * (50%) or more of the outstanding shares, or (iii) beneficial ownership of
 * such entity.
 *
 * Provided that You agree to the conditions described below, NCI grants You a
 * non-exclusive, worldwide, perpetual, fully-paid-up, no-charge, irrevocable,
 * transferable and royalty-free right and license in its rights in the caBIG®
 * Software, including any copyright or patent rights therein, to (i) use,
 * install, disclose, access, operate, execute, reproduce, copy, modify,
 * translate, market, publicly display, publicly perform, and prepare
 * derivative works of the caBIG® Software in any manner and for any purpose,
 * and to have or permit others to do so; (ii) make, have made, use, practice,
 * sell, and offer for sale, import, and/or otherwise dispose of caBIG®
 * Software (or portions thereof); (iii) distribute and have distributed to and
 * by third parties the caBIG® Software and any modifications and derivative
 * works thereof; and (iv) sublicense the foregoing rights set out in (i), (ii)
 * and (iii) to third parties, including the right to license such rights to
 * further third parties. For sake of clarity, and not by way of limitation,
 * NCI shall have no right of accounting or right of payment from You or Your
 * sublicensees for the rights granted under this License. This License is
 * granted at no charge to You. Your downloading, copying, modifying,
 * displaying, distributing or use of caBIG® Software constitutes acceptance of
 * all of the terms and conditions of this Agreement. If you do not agree to
 * such terms and conditions, you have no right to download, copy, modify,
 * display, distribute or use the caBIG® Software.
 *
 * Your redistributions of the source code for the caBIG® Software must retain
 * the above copyright notice, this list of conditions and the disclaimer and
 * limitation of liability of Article 6 below. Your redistributions in object
 * code form must reproduce the above copyright notice, this list of conditions
 * and the disclaimer of Article 6 in the documentation and/or other materials
 * provided with the distribution, if any.
 *
 * Your end-user documentation included with the redistribution, if any, must
 * include the following acknowledgment: “This product includes software
 * developed by Danny Korenblum, Alan Snyder, Vitaliy Semeshko, Vladimir Kleper
 * and Pattanasak Mongkolwat, Northwestern University and Stanford University.”
 * If You do not include such end-user documentation, You shall include this
 * acknowledgment in the caBIG® Software itself, wherever such third-party
 * acknowledgments normally appear.
 *
 * You may not use the names “Northwestern University”, “Stanford University”,
 * “The National Cancer Institute”, “NCI”, “Cancer Bioinformatics Grid” or
 * “caBIG®” to endorse or promote products derived from this caBIG® Software.
 * This License does not authorize You to use any trademarks, service marks,
 * trade names, logos or product names of either caBIG® Participant, NCI or
 * caBIG®, except as required to comply with the terms of this License.
 *
 * For sake of clarity, and not by way of limitation, You are not prohibited by
 * this License from incorporating this caBIG® Software into Your proprietary
 * programs and into any third party proprietary programs. However, if You
 * incorporate the caBIG® Software into third party proprietary programs, You
 * agree that You are solely responsible for obtaining any permission from such
 * third parties required to incorporate the caBIG® Software into such third
 * party proprietary programs and for informing Your sublicensees, including
 * without limitation Your end-users, of their obligation to secure any
 * required permissions from such third parties before incorporating the caBIG®
 * Software into such third party proprietary software programs. In the event
 * that You fail to obtain such permissions, You agree to indemnify NCI for any
 * claims against NCI by such third parties, except to the extent prohibited by
 * law, resulting from Your failure to obtain such permissions.
 * For sake of clarity, and not by way of limitation, You may add Your own
 * copyright statement to Your modifications and to the derivative works, and
 * You may provide additional or different license terms and conditions in
 * Your sublicenses of modifications of the caBIG® Software, or any derivative
 * works of the caBIG® Software as a whole, provided Your use, reproduction,
 * and distribution of the Work otherwise complies with the conditions stated
 * in this License.
 *
 * THIS caBIG® SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES (INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE) ARE
 * DISCLAIMED. IN NO EVENT SHALL NCI OR THE NORTHWESTERN UNIVERSITY OR ITS
 * AFFILIATES BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS caBIG® SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
