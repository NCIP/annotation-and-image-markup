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
