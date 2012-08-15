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

import static edu.stanford.isis.atb.ui.Const.MSG_LEXICON_EXPORT_FAILED;
import static edu.stanford.isis.atb.ui.Const.MSG_LEXICON_IS_EMPTY;
import static edu.stanford.isis.atb.ui.Const.MSG_LEXICON_IS_NOT_ALLOWED_FOR_EXPORT;
import static edu.stanford.isis.atb.ui.Const.MSG_LEXICON_IS_READONLY;
import static edu.stanford.isis.atb.ui.Const.MSG_NO_LEXICON_SELECTED;
import static edu.stanford.isis.atb.ui.view.lexicon.LexiconView.LexiconEditAction.CREATE;
import static edu.stanford.isis.atb.ui.view.lexicon.LexiconView.LexiconEditAction.DELETE;
import static edu.stanford.isis.atb.ui.view.lexicon.LexiconView.LexiconEditAction.EXPORT;
import static edu.stanford.isis.atb.ui.view.lexicon.LexiconView.LexiconEditAction.IMPORT;
import static edu.stanford.isis.atb.ui.view.lexicon.LexiconView.LexiconEditAction.SEARCH;

import java.io.File;
import java.util.HashSet;
import java.util.Set;

import edu.stanford.isis.atb.domain.lexicon.Lexicon;
import edu.stanford.isis.atb.domain.lexicon.Term;
import edu.stanford.isis.atb.service.Command;
import edu.stanford.isis.atb.service.LexiconService;
import edu.stanford.isis.atb.service.WatchingCallbackAdapter;
import edu.stanford.isis.atb.system.UserSession;
import edu.stanford.isis.atb.system.exception.ATBException;
import edu.stanford.isis.atb.ui.Const;
import edu.stanford.isis.atb.ui.action.EventBus;
import edu.stanford.isis.atb.ui.model.TermSearchItem;
import edu.stanford.isis.atb.ui.presenter.AbstractEventBusAwarePresenter;
import edu.stanford.isis.atb.ui.presenter.lexicon.LexiconEditorPresenter.LexiconChangeListener;
import edu.stanford.isis.atb.ui.presenter.lexicon.LexiconEditorPresenter.LexiconContentChangeListener;
import edu.stanford.isis.atb.ui.presenter.lexicon.search.CanAcceptSingleTerm;
import edu.stanford.isis.atb.ui.presenter.lexicon.search.SearchPresenter;
import edu.stanford.isis.atb.ui.presenter.lexicon.search.SearchPresenter.LexiconSearchMode;
import edu.stanford.isis.atb.ui.view.lexicon.LexiconView;
import edu.stanford.isis.atb.ui.view.lexicon.LexiconView.LexiconSelectionListener;
import edu.stanford.isis.atb.ui.view.widget.ImportExportDialog;
import edu.stanford.isis.atb.ui.view.widget.ImportExportDialog.ImportExportListener;
import edu.stanford.isis.atb.ui.view.widget.ImportExportDialog.Mode;

/**
 * Template Presenter.
 * 
 * @author Vitaliy Semeshko
 */
public class LexiconPresenter extends AbstractEventBusAwarePresenter<LexiconView, EventBus> {

	private Lexicon activeLexicon;

	private LexiconService lexiconService;

	private LexiconEditorPresenter editorPresenter;

	private SearchPresenter lexiconSearchPresenter;
	
	private UserSession session = UserSession.getInstance();
	
	private Set<String> prohibitedExport = new HashSet<String>() {{add("Radlex");}};
	
	private ImportExportDialog importExportDialog; 
	
	public LexiconPresenter(LexiconView view, EventBus eventBus) {
		super(view, eventBus);
	}

	public void setLexiconService(LexiconService lexiconService) {
		this.lexiconService = lexiconService;
	}

	public void setLexiconSearchPresenter(SearchPresenter lexiconSearchPresenter) {
		this.lexiconSearchPresenter = lexiconSearchPresenter;
	}
	
	public void setEditorPresenter(LexiconEditorPresenter editorPresenter) {
		this.editorPresenter = editorPresenter;

		editorPresenter.addLexiconChangeListener(new LexiconChangeListener() {
			@Override
			public void onLexiconChanged(Lexicon lexicon) {
				lexiconService.saveOrUpdateLexicon(lexicon);
				refreshView(lexicon);
			}
		});
		
		editorPresenter.addLexiconContentChangeListener(new LexiconContentChangeListener() {
			@Override
			public void onLexiconContentChanged(Lexicon lexicon) {
				loadData();
				activeLexicon = view.getActiveLexicon();
			}
		});
	}

	@Override
	public void bindView() {
		loadData();

		// bind commands
		view.setCommand(CREATE, new Command() {
			@Override 
			public void execute() {
				editorPresenter.clear();
				view.clearSelection();
				Lexicon newLexicon = new Lexicon();
				newLexicon.setInitialized(false);
				editorPresenter.showLexiconForm(newLexicon, true);
			}
		});

		view.setCommand(DELETE, new Command() {
			@Override 
			public void execute() {
				if (activeLexicon != null) {
					if (!activeLexicon.isReadOnly()) {
						if (view.confirm(Const.QST_DELETE_LEXICON)) {
							lexiconService.deleteLexicon(activeLexicon);
							activeLexicon = null;
							refreshView(null);
						}
					} else {
						view.showInformation(MSG_LEXICON_IS_READONLY);
					}
				} else {
					view.showInformation(MSG_NO_LEXICON_SELECTED);
				}
			}
		});

		view.setCommand(SEARCH, new Command() {
			@Override 
			public void execute() {
				// define acceptor
				lexiconSearchPresenter.setSingleTermAcceptor(new CanAcceptSingleTerm() {
					@Override
					public void accept(TermSearchItem searchItem) {
						view.clearSelection();
						
						// load terms of the lexicon
						Lexicon lexicon = searchItem.getTerm().getLexicon();
						lexiconService.getTerms(lexicon);
						view.setActiveLexicon(lexicon);
						
						// load term path (from the root to currently selected)
						Term termPath = lexiconService.getPathToTheRoot(searchItem.getTerm());
						editorPresenter.expandTermPath(termPath);
					}
				});
				// show
				lexiconSearchPresenter.startSearch(LexiconSearchMode.SINGLE);
			}
		});

		view.setCommand(EXPORT, new Command() {
			@Override
			public void execute() {
				if (!validateCurrentLexicon()) {
					return;
				}
				
				final ImportExportDialog dialog = getImportExportDialog();
				dialog.setCurrentDirectory(session.getLexiconImportExportPath());
				
				final WatchingCallbackAdapter<Void> callback = new WatchingCallbackAdapter<Void>() {

					@Override
					public void notifyStatus(String status) {
						dialog.notifyStatus(status);
					}
					
					@Override
					public void notifyCancelled() {
						dialog.notifyCancelled();
					}

					@Override
					public void onSuccess(Void result) {
						dialog.notifySuccess();
					}

					@Override
					protected void onFailure(ATBException caught) {
						dialog.notifyFail();
						String msg = String.format(MSG_LEXICON_EXPORT_FAILED, activeLexicon.getName());
						view.showError(getErrorInformation(msg, caught));						
					}
				};

				dialog.setListener(new ImportExportListener() {
					
					@Override
					public void onStart(final String filePath) {
						callback.setCancelled(false);
						File file = new File(filePath);
						File folder = file.getParentFile();
						
						if (folder == null || !folder.exists()) {
							dialog.notifyFail();
							view.showInformation(String.format(Const.MSG_INCORRECT_FILE_LOCATION, filePath));
							return;
						}
						session.setLexiconImportExportPath(folder.getAbsolutePath());
						lexiconService.exportToCsv(activeLexicon, file, callback);
					}
					
					@Override
					public void onCancel() {
						callback.setCancelled(true);
					}
				});
				
				dialog.showAsDialog(Mode.EXPORT);
			}
		});
		
		view.setCommand(IMPORT, new Command() {
			@Override
			public void execute() {
				final ImportExportDialog dialog = getImportExportDialog();
				dialog.setCurrentDirectory(session.getLexiconImportExportPath());
				
				final WatchingCallbackAdapter<Lexicon> callback = new WatchingCallbackAdapter<Lexicon>() {

					@Override
					public void notifyStatus(String status) {
						dialog.notifyStatus(status);
					}
					
					@Override
					public void notifyCancelled() {
						dialog.notifyCancelled();
					}

					@Override
					public void onSuccess(Lexicon result) {
						dialog.notifySuccess();
						refreshView(result);
					}

					@Override
					protected void onFailure(ATBException caught) {
						dialog.notifyFail();
						view.showError(getErrorInformation(Const.MSG_LEXICON_IMPORT_FAILED, caught));						
					}
				};
				
				dialog.setListener(new ImportExportListener() {
					
					@Override
					public void onStart(final String filePath) {
						callback.setCancelled(false);
						File file = new File(filePath);
						
						if (!file.exists()) {
							dialog.notifyFail();
							view.showInformation(String.format(Const.MSG_INCORRECT_FILE_LOCATION, filePath));
							return;
						}
						session.setLexiconImportExportPath(file.getParent());
						lexiconService.importFromCsv(file, callback);
					}
					
					@Override
					public void onCancel() {
						callback.setCancelled(true);
					}
				});
				
				dialog.showAsDialog(Mode.IMPORT);
			}
		});
		
		view.addLexiconSelectionListeners(new LexiconSelectionListener() {
			@Override
			public void onLexiconSelected(Lexicon lexicon) {
				activeLexicon = lexicon;
				editorPresenter.setActiveLexicon(lexicon);
			}
		});
	}

	private ImportExportDialog getImportExportDialog() {
		if (importExportDialog == null) {
			importExportDialog = new ImportExportDialog();
			importExportDialog.setDefaultExtension(Const.EXT_CSV);
			importExportDialog.setDefaultExtensionText(Const.EXT_CSV_TEXT);
		}
		return importExportDialog;
	}
	
	private void loadData() {
		view.setLexicons(lexiconService.getLexicons());
	}

	/**
	 * Refresh view and after select provided element.
	 * 
	 * @param lexicon lexicon to be selected after refresh. If <code>null</code> then currently selected element
	 * will be re-selected. If no currently selected element, nothing will be selected.
	 */
	public void refreshView(Lexicon lexicon) {
		Lexicon target = lexicon != null ? lexicon : activeLexicon;

		view.setLexicons(lexiconService.getLexicons());

		if (target != null) {
			view.setActiveLexicon(lexicon);
			editorPresenter.setActiveLexicon(lexicon);
		} else {
			// clear all selections and showing data
			view.hideEditForm();
			view.clearSelection();
			editorPresenter.clear();
		}
	}

	private boolean validateCurrentLexicon() {
		if (activeLexicon == null) {
			view.showInformation(MSG_NO_LEXICON_SELECTED);
			return false;
		}
		
		// don't export empty lexicon
		if (activeLexicon.getTermCount() == 0) {
			view.showInformation(MSG_LEXICON_IS_EMPTY);
			return false;
		}
		
		// check prohibited export
		if (prohibitedExport.contains(activeLexicon.getName())) {
			view.showInformation(MSG_LEXICON_IS_NOT_ALLOWED_FOR_EXPORT);
			return false;
		}
		
		// other validation
				
		return true;
	}
	
}
