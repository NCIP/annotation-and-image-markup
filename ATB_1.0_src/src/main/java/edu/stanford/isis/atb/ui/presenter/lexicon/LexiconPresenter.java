/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
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
