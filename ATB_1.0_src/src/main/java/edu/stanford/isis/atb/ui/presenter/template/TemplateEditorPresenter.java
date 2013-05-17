/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.presenter.template;

import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import java.util.concurrent.Executor;

import javax.swing.tree.TreeModel;

import org.springframework.core.task.SimpleAsyncTaskExecutor;

import edu.stanford.isis.atb.domain.Initializable;
import edu.stanford.isis.atb.domain.LexiconTermAttributes;
import edu.stanford.isis.atb.domain.template.AbstractElement;
import edu.stanford.isis.atb.domain.template.AlgorithmType;
import edu.stanford.isis.atb.domain.template.AllowedTerm;
import edu.stanford.isis.atb.domain.template.AllowedTermWithQuantification;
import edu.stanford.isis.atb.domain.template.AnatomicEntity;
import edu.stanford.isis.atb.domain.template.AnatomicEntityCharacteristic;
import edu.stanford.isis.atb.domain.template.Calculation;
import edu.stanford.isis.atb.domain.template.CalculationType;
import edu.stanford.isis.atb.domain.template.CharacteristicQuantification;
import edu.stanford.isis.atb.domain.template.CodedTerm;
import edu.stanford.isis.atb.domain.template.GeometricShape;
import edu.stanford.isis.atb.domain.template.GeometricShapeType;
import edu.stanford.isis.atb.domain.template.ImagingObservation;
import edu.stanford.isis.atb.domain.template.ImagingObservationCharacteristic;
import edu.stanford.isis.atb.domain.template.Inference;
import edu.stanford.isis.atb.domain.template.Interval;
import edu.stanford.isis.atb.domain.template.NonQuantifiable;
import edu.stanford.isis.atb.domain.template.Numerical;
import edu.stanford.isis.atb.domain.template.Operator;
import edu.stanford.isis.atb.domain.template.OrdinalLevel;
import edu.stanford.isis.atb.domain.template.Quantile;
import edu.stanford.isis.atb.domain.template.QuestionType;
import edu.stanford.isis.atb.domain.template.RemovableElement;
import edu.stanford.isis.atb.domain.template.Scale;
import edu.stanford.isis.atb.domain.template.Tag;
import edu.stanford.isis.atb.domain.template.TagName;
import edu.stanford.isis.atb.domain.template.TagValue;
import edu.stanford.isis.atb.domain.template.Template;
import edu.stanford.isis.atb.domain.template.TemplateComponent;
import edu.stanford.isis.atb.domain.template.ValidTerm;
import edu.stanford.isis.atb.service.Command;
import edu.stanford.isis.atb.ui.Const;
import edu.stanford.isis.atb.ui.model.tree.TemplateNodeType;
import edu.stanford.isis.atb.ui.presenter.AbstractPresenter;
import edu.stanford.isis.atb.ui.presenter.form.AbstractFormPresenter.FormCloseListener;
import edu.stanford.isis.atb.ui.presenter.form.AbstractFormPresenter.FormSubmitListener;
import edu.stanford.isis.atb.ui.presenter.form.FormManager;
import edu.stanford.isis.atb.ui.presenter.lexicon.search.CanAcceptMultipleTerms;
import edu.stanford.isis.atb.ui.presenter.lexicon.search.SearchPresenter;
import edu.stanford.isis.atb.ui.presenter.lexicon.search.SearchPresenter.LexiconSearchMode;
import edu.stanford.isis.atb.ui.presenter.template.form.AlgorithmTypeFormPresenter;
import edu.stanford.isis.atb.ui.presenter.template.form.AnatomicEntityCharFormPresenter;
import edu.stanford.isis.atb.ui.presenter.template.form.AnatomicEntityFormPresenter;
import edu.stanford.isis.atb.ui.presenter.template.form.CharQuantificationFormPresenter;
import edu.stanford.isis.atb.ui.presenter.template.form.CodedTermFormPresenter;
import edu.stanford.isis.atb.ui.presenter.template.form.ComponentFormPresenter;
import edu.stanford.isis.atb.ui.presenter.template.form.EmptyFormPresenter;
import edu.stanford.isis.atb.ui.presenter.template.form.GeometricShapeFormPresenter;
import edu.stanford.isis.atb.ui.presenter.template.form.ImagingObservationCharFormPresenter;
import edu.stanford.isis.atb.ui.presenter.template.form.ImagingObservationFormPresenter;
import edu.stanford.isis.atb.ui.presenter.template.form.InferenceFormPresenter;
import edu.stanford.isis.atb.ui.presenter.template.form.IntervalFormPresenter;
import edu.stanford.isis.atb.ui.presenter.template.form.NumericalFormPresenter;
import edu.stanford.isis.atb.ui.presenter.template.form.OrdinalLevelFormPresenter;
import edu.stanford.isis.atb.ui.presenter.template.form.QuantileFormPresenter;
import edu.stanford.isis.atb.ui.presenter.template.form.ScaleFormPresenter;
import edu.stanford.isis.atb.ui.presenter.template.form.TagFormPresenter;
import edu.stanford.isis.atb.ui.presenter.template.form.TemplateFormPresenter;
import edu.stanford.isis.atb.ui.validation.TemplateTreeValidator;
import edu.stanford.isis.atb.ui.validation.TemplateValidationError;
import edu.stanford.isis.atb.ui.view.template.TemplateEditorView;
import edu.stanford.isis.atb.ui.view.template.TemplateEditorView.AlgorithmTypeAction;
import edu.stanford.isis.atb.ui.view.template.TemplateEditorView.AllowedTermAction;
import edu.stanford.isis.atb.ui.view.template.TemplateEditorView.AllowedTermWithQuantAction;
import edu.stanford.isis.atb.ui.view.template.TemplateEditorView.AnatomicEntityAction;
import edu.stanford.isis.atb.ui.view.template.TemplateEditorView.AnatomicEntityCharAction;
import edu.stanford.isis.atb.ui.view.template.TemplateEditorView.CalculationTypeAction;
import edu.stanford.isis.atb.ui.view.template.TemplateEditorView.CharQuantificationAction;
import edu.stanford.isis.atb.ui.view.template.TemplateEditorView.ComponentAction;
import edu.stanford.isis.atb.ui.view.template.TemplateEditorView.GeometricShapeAction;
import edu.stanford.isis.atb.ui.view.template.TemplateEditorView.ImagingObservationAction;
import edu.stanford.isis.atb.ui.view.template.TemplateEditorView.ImagingObservationCharAction;
import edu.stanford.isis.atb.ui.view.template.TemplateEditorView.InferenceAction;
import edu.stanford.isis.atb.ui.view.template.TemplateEditorView.IntervalAction;
import edu.stanford.isis.atb.ui.view.template.TemplateEditorView.MoveUpDownAction;
import edu.stanford.isis.atb.ui.view.template.TemplateEditorView.NonQuantifiableAction;
import edu.stanford.isis.atb.ui.view.template.TemplateEditorView.NumericalAction;
import edu.stanford.isis.atb.ui.view.template.TemplateEditorView.OrdinalLevelAction;
import edu.stanford.isis.atb.ui.view.template.TemplateEditorView.QuantileAction;
import edu.stanford.isis.atb.ui.view.template.TemplateEditorView.QuestionTypeAction;
import edu.stanford.isis.atb.ui.view.template.TemplateEditorView.ScaleAction;
import edu.stanford.isis.atb.ui.view.template.TemplateEditorView.TagAction;
import edu.stanford.isis.atb.ui.view.template.TemplateEditorView.TemplateAction;
import edu.stanford.isis.atb.ui.view.template.TemplateEditorView.TemplateWarningSelectionListener;
import edu.stanford.isis.atb.ui.view.template.TemplateEditorView.ValidTermAction;
import edu.stanford.isis.atb.ui.view.template.TemplateEditorView.СalculationAction;

/**
 * @author Vitaliy Semeshko
 */
public class TemplateEditorPresenter extends AbstractPresenter<TemplateEditorView> {

	private FormManager formManager = new FormManager();

	private SearchPresenter lexiconSearchPresenter;
	
	private List<TemplateChangeListener> templateChangeListeners = new ArrayList<TemplateChangeListener>();

	private Template activeTemplate;

	private FormSubmitListener<Initializable> formSubmitListener = new FormSubmitListener<Initializable>() {
		@Override
		public void onFormSubmit(Initializable value, boolean isCreation) {
			// save changes
			notifyTemplateContentChanged();
			
			// mark value as initialized after saving
			value.setInitialized(true);
			
			// refresh selected node in the tree
			view.getTreeManager().refreshSelectedNode();
		}
	};

	private FormCloseListener formCloseListener = new FormCloseListener() {
		@Override
		public void onFormClose() {
			view.hideEditForm();
		}
	};

	private Command deleteTreeElement = new Command() {
		@Override
		public void execute() {
			RemovableElement element = view.getSelectedNodeValue();
			element.remove();
			view.getTreeManager().removeSelectedNode();
			notifyTemplateContentChanged();
		}
	};

	private Command addValidTermCommand = new Command() {
		@Override
		public void execute() {
			final ValidTerm validTerm = view.getSelectedNodeValue();
			
			lexiconSearchPresenter.setExistingTerms(validTerm.getValidTerms());
			
			lexiconSearchPresenter.setMultipleTermsAcceptor(new CanAcceptMultipleTerms() {
				@Override
				public void accept(Collection<LexiconTermAttributes> addedItems, List<CodedTerm> removedTerms) {
					for (CodedTerm term : removedTerms) {
						view.getTreeManager().removeChildNodeTermWithUserObject(term);
						term.remove();
					}
					
					for (LexiconTermAttributes termAttributes : addedItems) {
						ValidTerm  vt = ValidTerm.fromAttributes(termAttributes);
						validTerm.addValidTerm(vt);
						view.getTreeManager().addValidTerm(vt);
					}
					
					if (!addedItems.isEmpty() || !removedTerms.isEmpty()) {
						notifyTemplateContentChanged();
					}
				}
			});
			
			lexiconSearchPresenter.startSearch(LexiconSearchMode.BATCH);
		}
	};
	
	public TemplateEditorPresenter(TemplateEditorView view) {
		super(view);
	}

	@Override
	public void bindView() {
		initMoveUpDownActions();
		initTemplateActions();
		initComponentActions();
		initTagActions();
		initQuestionTypeActions();
		initAnatomicEntityActions();
		initAnatomicEntityCharActions();
		initGeometricShapeActions();
		initInferenceActions();
		initAllowedTermActions();
		initValidTermActions();
		initCalculationActions();
		initNonQuantifiableActions();
		initImgObsActions();
		initImgObsCharActions();
		initCharQuantificationActions();
		initScaleActions();
		
		view.addWarningSelectionListeners(new TemplateWarningSelectionListener() {
			@Override
			public void onWarningSelected(TemplateValidationError warning) {
				view.getTreeManager().scrollToNodeAndSelect(warning.getNode());
			}
		});
	}

	public void setLexiconSearchPresenter(SearchPresenter lexiconSearchPresenter) {
		this.lexiconSearchPresenter = lexiconSearchPresenter;
	}

	private void initMoveUpDownActions() {
		view.setCommand(MoveUpDownAction.UP, new Command() {
			@Override
			public void execute() {
				AbstractElement el = view.getSelectedNodeValue();
				if (el.getContext().canMoveUp()) {
					el.getContext().moveUp();
					view.getTreeManager().moveSelectedNodeUp();
					notifyTemplateContentChanged();
				}
			}
		});
		
		view.setCommand(MoveUpDownAction.DOWN, new Command() {
			@Override
			public void execute() {
				AbstractElement el = view.getSelectedNodeValue();
				if (el.getContext().canMoveDown()) {
					el.getContext().moveDown();
					view.getTreeManager().moveSelectedNodeDown();
					notifyTemplateContentChanged();
				}
			}
		});
	}
	
	private void initTemplateActions() {
		view.setShowFormCommand(TemplateNodeType.TEMPLATE, new Command() {
			@Override
			public void execute() {
				if (activeTemplate != null) {
					showTemplateForm(activeTemplate, false);
				} else {
					view.showInformation(Const.MSG_NO_TEMPLATE_SELECTED);
				}
			}
		});

		view.setCommand(TemplateAction.CREATE_COMPONENT, new Command() {
			@Override
			public void execute() {
				TemplateComponent component = new TemplateComponent();
				component.setInitialized(false);
				activeTemplate.addComponent(component);
				view.getTreeManager().addComponent(component);
				notifyTemplateContentChanged();
			}
		});

		view.setCommand(TemplateAction.CREATE_TAG, new Command() {
			@Override
			public void execute() {
				// create tag with empty name and value
				Tag tag = new Tag();
				tag.setTagName(new TagName());
				TagValue value = new TagValue();
				tag.setTagValue(value);
				value.setCodedValue(new CodedTerm());

				activeTemplate.addTag(tag);
				view.getTreeManager().addTag(tag);
				notifyTemplateContentChanged();
			}
		});
	}

	private void initComponentActions() {
		view.setShowFormCommand(TemplateNodeType.COMPONENT, new Command() {
			@Override
			public void execute() {
				TemplateComponent component = view.getSelectedNodeValue();
				showComponentForm(component);
			}
		});

		view.setCommand(ComponentAction.DELETE, deleteTreeElement);

		view.setCommand(ComponentAction.CREATE_QST_TYPE, new Command() {
			@Override
			public void execute() {
				QuestionType questionType = new QuestionType();
				TemplateComponent component = view.getSelectedNodeValue();
				component.setQuestionType(questionType);
				view.getTreeManager().addQuestionType(questionType);
				notifyTemplateContentChanged();
			}
		});

		view.setCommand(ComponentAction.CREATE_AN_ENTITY, new Command() {
			@Override
			public void execute() {
				AnatomicEntity anatomicEntity = new AnatomicEntity();
				TemplateComponent component = view.getSelectedNodeValue();
				component.setContent(anatomicEntity);
				view.getTreeManager().addAnatomicEntity(anatomicEntity);
				notifyTemplateContentChanged();
			}
		});

		view.setCommand(ComponentAction.CREATE_IMG_OBS, new Command() {
			@Override
			public void execute() {
				ImagingObservation imagingObservation = new ImagingObservation();
				TemplateComponent component = view.getSelectedNodeValue();
				component.setContent(imagingObservation);
				view.getTreeManager().addImagingObservation(imagingObservation);
				notifyTemplateContentChanged();
			}
		});

		view.setCommand(ComponentAction.CREATE_INFERENCE, new Command() {
			@Override
			public void execute() {
				Inference inference = new Inference();
				TemplateComponent component = view.getSelectedNodeValue();
				component.setContent(inference);
				view.getTreeManager().addInference(inference);
				notifyTemplateContentChanged();
			}
		});

		view.setCommand(ComponentAction.CREATE_GEOM_SHAPE, new Command() {
			@Override
			public void execute() {
				GeometricShape geometricShape = new GeometricShape();
				// set any value to be default
				geometricShape.setValue(GeometricShapeType.Point);
				TemplateComponent component = view.getSelectedNodeValue();
				component.setContent(geometricShape);
				view.getTreeManager().addGeometricShape(geometricShape);
				notifyTemplateContentChanged();
			}
		});

		view.setCommand(ComponentAction.CREATE_CALCULATION, new Command() {
			@Override
			public void execute() {
				Calculation calculation = new Calculation();
				TemplateComponent component = view.getSelectedNodeValue();
				component.setContent(calculation);
				view.getTreeManager().addCalculation(calculation);
				notifyTemplateContentChanged();
			}
		});
		
		view.setCommand(ComponentAction.ADD_ALLOWED_TERMS, new Command() {
			@Override
			public void execute() {
				final TemplateComponent component = view.getSelectedNodeValue();
				
				lexiconSearchPresenter.setExistingTerms(component.getAllowedTerms());
				
				lexiconSearchPresenter.setMultipleTermsAcceptor(new CanAcceptMultipleTerms() {
					@Override
					public void accept(Collection<LexiconTermAttributes> addedItems, List<CodedTerm> removedTerms) {
						for (CodedTerm term : removedTerms) {
							view.getTreeManager().removeChildNodeTermWithUserObject(term);
							term.remove();
						}
						
						for (LexiconTermAttributes termAttributes : addedItems) {
							AllowedTerm at = AllowedTerm.fromAttributes(termAttributes);
							component.addAllowedTerm(at);
							view.getTreeManager().addAllowedTerm(at);
						}
						
						if (!addedItems.isEmpty() || !removedTerms.isEmpty()) {
							notifyTemplateContentChanged();
						}
					}
				});
				
				lexiconSearchPresenter.startSearch(LexiconSearchMode.BATCH);
			}
		});
	}
	
	private void initQuestionTypeActions() {
		view.setShowFormCommand(TemplateNodeType.QUESTION_TYPE, new Command() {
			@Override
			public void execute() {
				CodedTerm term = view.getSelectedNodeValue();
				showCodedTermForm(term);
			}
		});

		view.setCommand(QuestionTypeAction.DELETE, deleteTreeElement);
		
		view.setCommand(QuestionTypeAction.ADD_VALID_TERMS, addValidTermCommand);
	}

	private void initAnatomicEntityActions() {
		view.setCommand(AnatomicEntityAction.CREATE_AN_ENTITY_CHAR, new Command() {
			@Override
			public void execute() {
				AnatomicEntityCharacteristic characteristic = new AnatomicEntityCharacteristic();
				characteristic.setInitialized(false);
				AnatomicEntity anatomicEntity = view.getSelectedNodeValue();
				anatomicEntity.addCharacteristic(characteristic);
				view.getTreeManager().addAnatomicEntityChar(characteristic);
				notifyTemplateContentChanged();
			}
		});

		view.setShowFormCommand(TemplateNodeType.ANATOMIC_ENTITY, new Command() {
			@Override
			public void execute() {
				AnatomicEntity anatomicEntity = view.getSelectedNodeValue();
				showAnatomicEntityForm(anatomicEntity);
			}
		});

		view.setCommand(AnatomicEntityAction.DELETE, deleteTreeElement);
	}

	private void initAnatomicEntityCharActions() {
		view.setShowFormCommand(TemplateNodeType.ANATOMIC_ENTITY_CHARACTERISTIC, new Command() {
			@Override
			public void execute() {
				AnatomicEntityCharacteristic characteristic = view.getSelectedNodeValue();
				showAnatomicEntityCharForm(characteristic);
			}
		});

		view.setCommand(AnatomicEntityCharAction.DELETE, deleteTreeElement);

		view.setCommand(AnatomicEntityCharAction.ADD_ALLOWED_TERMS, new Command() {
			@Override
			public void execute() {
				final AnatomicEntityCharacteristic characteristic = view.getSelectedNodeValue();
				
				lexiconSearchPresenter.setExistingTerms(characteristic.getAllowedTerms());
				
				lexiconSearchPresenter.setMultipleTermsAcceptor(new CanAcceptMultipleTerms() {
					@Override
					public void accept(Collection<LexiconTermAttributes> addedItems, List<CodedTerm> removedTerms) {
						for (CodedTerm term : removedTerms) {
							view.getTreeManager().removeChildNodeTermWithUserObject(term);
							term.remove();
						}
						
						for (LexiconTermAttributes termAttributes : addedItems) {
							AllowedTermWithQuantification  at = AllowedTermWithQuantification.
									fromAttributes(termAttributes);
							characteristic.addAllowedTerm(at);
							view.getTreeManager().addAllowedTermWithQuantification(at);
						}
						
						if (!addedItems.isEmpty() || !removedTerms.isEmpty()) {
							notifyTemplateContentChanged();
						}
					}
				});
				
				lexiconSearchPresenter.startSearch(LexiconSearchMode.BATCH);
			}
		});

		view.setCommand(AnatomicEntityCharAction.CREATE_QST_TYPE, new Command() {
			@Override
			public void execute() {
				QuestionType questionType = new QuestionType();
				AnatomicEntityCharacteristic characteristic = view.getSelectedNodeValue();
				characteristic.setQuestionType(questionType);
				view.getTreeManager().addQuestionType(questionType);
				notifyTemplateContentChanged();
			}
		});
	}

	private void initImgObsActions() {
		view.setCommand(ImagingObservationAction.CREATE_IMG_OBS_CHAR, new Command() {
			@Override
			public void execute() {
				ImagingObservationCharacteristic characteristic = new ImagingObservationCharacteristic();
				characteristic.setInitialized(false);
				ImagingObservation imagingObservation = view.getSelectedNodeValue();
				imagingObservation.addCharacteristic(characteristic);
				view.getTreeManager().addImagingObservationChar(characteristic);
				notifyTemplateContentChanged();
			}
		});

		view.setShowFormCommand(TemplateNodeType.IMAGING_OBSERVATION, new Command() {
			@Override
			public void execute() {
				ImagingObservation imagingObservation = view.getSelectedNodeValue();
				showImagingObservationForm(imagingObservation);
			}
		});

		view.setCommand(ImagingObservationAction.DELETE, deleteTreeElement);
	}

	private void initImgObsCharActions() {
		view.setShowFormCommand(TemplateNodeType.IMAGING_OBSERVATION_CHARACTERISTIC, new Command() {
			@Override
			public void execute() {
				ImagingObservationCharacteristic characteristic = view.getSelectedNodeValue();
				showImagingObservationCharForm(characteristic);
			}
		});

		view.setCommand(ImagingObservationCharAction.DELETE, deleteTreeElement);

		view.setCommand(ImagingObservationCharAction.ADD_ALLOWED_TERMS, new Command() {
			@Override
			public void execute() {
				final ImagingObservationCharacteristic characteristic = view.getSelectedNodeValue();
				
				lexiconSearchPresenter.setExistingTerms(characteristic.getAllowedTerms());
				
				lexiconSearchPresenter.setMultipleTermsAcceptor(new CanAcceptMultipleTerms() {
					@Override
					public void accept(Collection<LexiconTermAttributes> addedItems, List<CodedTerm> removedTerms) {
						for (CodedTerm term : removedTerms) {
							view.getTreeManager().removeChildNodeTermWithUserObject(term);
							term.remove();
						}
						
						for (LexiconTermAttributes termAttributes : addedItems) {
							AllowedTermWithQuantification  at = AllowedTermWithQuantification.
									fromAttributes(termAttributes);
							characteristic.addAllowedTerm(at);
							view.getTreeManager().addAllowedTermWithQuantification(at);
						}
						
						if (!addedItems.isEmpty() || !removedTerms.isEmpty()) {
							notifyTemplateContentChanged();
						}
					}
				});
				
				lexiconSearchPresenter.startSearch(LexiconSearchMode.BATCH);
			}
		});

		view.setCommand(ImagingObservationCharAction.CREATE_QST_TYPE, new Command() {
			@Override
			public void execute() {
				QuestionType questionType = new QuestionType();
				ImagingObservationCharacteristic characteristic = view.getSelectedNodeValue();
				characteristic.setQuestionType(questionType);
				view.getTreeManager().addQuestionType(questionType);
				notifyTemplateContentChanged();
			}
		});
	}

	private void initGeometricShapeActions() {
		view.setShowFormCommand(TemplateNodeType.GEOMETRIC_SHAPE, new Command() {
			@Override
			public void execute() {
				GeometricShape geometricShape = view.getSelectedNodeValue();
				showGeometricShapeForm(geometricShape);
			}
		});

		view.setCommand(GeometricShapeAction.DELETE, deleteTreeElement);
	}

	private void initInferenceActions() {
		view.setShowFormCommand(TemplateNodeType.INFERENCE, new Command() {
			@Override
			public void execute() {
				Inference inference = view.getSelectedNodeValue();
				showInferenceForm(inference);
			}
		});

		view.setCommand(InferenceAction.DELETE, deleteTreeElement);

		view.setCommand(InferenceAction.CREATE_QST_TYPE, new Command() {
			@Override
			public void execute() {
				QuestionType questionType = new QuestionType();
				Inference inference = view.getSelectedNodeValue();
				inference.setQuestionType(questionType);
				view.getTreeManager().addQuestionType(questionType);
				notifyTemplateContentChanged();
			}
		});
	}

	private void initAllowedTermActions() {
		view.setShowFormCommand(TemplateNodeType.ALLOWED_TERM, new Command() {
			@Override
			public void execute() {
				AllowedTerm term = view.getSelectedNodeValue();
				showCodedTermForm(term);
			}
		});

		view.setShowFormCommand(TemplateNodeType.ALLOWED_TERM_WITH_QUANTIFICATION, new Command() {
			@Override
			public void execute() {
				AllowedTermWithQuantification term = view.getSelectedNodeValue();
				showCodedTermForm(term);
			}
		}); 

		view.setCommand(AllowedTermAction.DELETE, deleteTreeElement);
		view.setCommand(AllowedTermWithQuantAction.DELETE, deleteTreeElement);

		view.setCommand(AllowedTermAction.ADD_VALID_TERMS, addValidTermCommand);
		view.setCommand(AllowedTermWithQuantAction.ADD_VALID_TERMS, addValidTermCommand);
		
		view.setCommand(AllowedTermAction.CREATE_NON_QUANT, new Command() {
			@Override
			public void execute() {
				NonQuantifiable nonQuantifiable = new NonQuantifiable();
				AllowedTerm allowedTerm = view.getSelectedNodeValue();
				allowedTerm.addNonQuantifiable(nonQuantifiable);
				view.getTreeManager().addNonQuantifiable(nonQuantifiable);
				notifyTemplateContentChanged();
			}
		});

		view.setCommand(AllowedTermWithQuantAction.CREATE_CHAR_QUANT, new Command() {
			@Override
			public void execute() {
				CharacteristicQuantification cq = new CharacteristicQuantification();
				AllowedTermWithQuantification allowedTerm = view.getSelectedNodeValue();
				allowedTerm.setCharacteristicQuantification(cq);
				view.getTreeManager().addCharacteristicQuantification(cq);
				notifyTemplateContentChanged();
			}
		});
	}
	
	private void initValidTermActions() {
		view.setShowFormCommand(TemplateNodeType.VALID_TERM, new Command() {
			@Override
			public void execute() {
				ValidTerm term = view.getSelectedNodeValue();
				showCodedTermForm(term);
			}
		});
		
		view.setCommand(ValidTermAction.ADD_VALID_TERMS, addValidTermCommand);
		
		view.setCommand(ValidTermAction.DELETE, deleteTreeElement);
	}

	private void initCharQuantificationActions() {
		view.setShowFormCommand(TemplateNodeType.CHARACTERISTIC_QUANTIFICATION, new Command() {
			@Override
			public void execute() {
				CharacteristicQuantification charQuant = view.getSelectedNodeValue();
				showCharQuantificationForm(charQuant);
			}
		});
		
		view.setCommand(CharQuantificationAction.DELETE, deleteTreeElement);

		view.setCommand(CharQuantificationAction.CREATE_NON_QUANT, new Command() {
			@Override
			public void execute() {
				NonQuantifiable nonQuantifiable = new NonQuantifiable();
				CharacteristicQuantification charQuant = view.getSelectedNodeValue();
				charQuant.addNonQuantifiable(nonQuantifiable);
				view.getTreeManager().addNonQuantifiable(nonQuantifiable);
				notifyTemplateContentChanged();
			}
		});

		view.setCommand(CharQuantificationAction.CREATE_SCALE, new Command() {
			@Override
			public void execute() {
				Scale scale = new Scale();
//				scale.addOrdinalLevel(new OrdinalLevel());
//				scale.addOrdinalLevel(new OrdinalLevel());
				CharacteristicQuantification charQuant = view.getSelectedNodeValue();
				charQuant.setScale(scale);
				view.getTreeManager().addScale(scale);
				notifyTemplateContentChanged();
			}
		});
		
		view.setCommand(CharQuantificationAction.CREATE_NUMERICAL, new Command() {
			@Override
			public void execute() {
				Numerical numerical = new Numerical();
				CharacteristicQuantification charQuant = view.getSelectedNodeValue();
				charQuant.addNumerical(numerical);
				view.getTreeManager().addNumerical(numerical);
				notifyTemplateContentChanged();
			}
		});
		
		view.setCommand(CharQuantificationAction.CREATE_INTERVAL, new Command() {
			@Override
			public void execute() {
				Interval interval = new Interval();
				interval.setMinOperator(Operator.Equal);
				interval.setMaxOperator(Operator.Equal);
				CharacteristicQuantification charQuant = view.getSelectedNodeValue();
				charQuant.addInterval(interval);
				view.getTreeManager().addInterval(interval);
				notifyTemplateContentChanged();
			}
		});
		
		view.setCommand(CharQuantificationAction.CREATE_QUANTILE, new Command() {
			@Override
			public void execute() {
				Quantile quantile = new Quantile();
				CharacteristicQuantification charQuant = view.getSelectedNodeValue();
				charQuant.setQuantile(quantile);
				view.getTreeManager().addQuantile(quantile);
				notifyTemplateContentChanged();
			}
		});

		// numerical
		
		view.setShowFormCommand(TemplateNodeType.NUMERICAL, new Command() {
			@Override
			public void execute() {
				Numerical numerical = view.getSelectedNodeValue();
				showNumericalForm(numerical);
			}
		});

		view.setCommand(NumericalAction.DELETE, deleteTreeElement);
		
		// interval
		
		view.setShowFormCommand(TemplateNodeType.INTERVAL, new Command() {
			@Override
			public void execute() {
				Interval interval = view.getSelectedNodeValue();
				showIntervalForm(interval);
			}
		});

		view.setCommand(IntervalAction.DELETE, deleteTreeElement);
		
		// quantile

		view.setShowFormCommand(TemplateNodeType.QUANTILE, new Command() {
			@Override
			public void execute() {
				Quantile quantile = view.getSelectedNodeValue();
				showQuantileForm(quantile);
			}
		});
		
		view.setCommand(QuantileAction.DELETE, deleteTreeElement);
	}	
	
	private void initScaleActions() {
		view.setShowFormCommand(TemplateNodeType.SCALE, new Command() {
			@Override
			public void execute() {
				Scale scale = view.getSelectedNodeValue();
				showScaleForm(scale);
			}
		});
		
		view.setCommand(ScaleAction.DELETE, deleteTreeElement);

		view.setCommand(ScaleAction.CREATE_ORD_LEVEL, new Command() {
			@Override
			public void execute() {
				OrdinalLevel ordinalLevel = new OrdinalLevel();
				Scale scale = view.getSelectedNodeValue();
				scale.addOrdinalLevel(ordinalLevel);
				view.getTreeManager().addOrdinalLevel(ordinalLevel);
				notifyTemplateContentChanged();
			}
		});
		
		// ordinal level
		
		view.setShowFormCommand(TemplateNodeType.ORDINAL_LEVEL, new Command() {
			@Override
			public void execute() {
				OrdinalLevel ordinalLevel = view.getSelectedNodeValue();
				showOrdinalLevelForm(ordinalLevel);
			}
		});
		
		view.setCommand(OrdinalLevelAction.DELETE, deleteTreeElement);
	}
	
	private void initCalculationActions() {
		view.setShowFormCommand(TemplateNodeType.CALCULATION, new Command() {
			@Override
			public void execute() {
				showEmptyForm();
			}
		});
		
		view.setCommand(СalculationAction.DELETE, deleteTreeElement);

		view.setCommand(СalculationAction.CREATE_CALC_TYPE, new Command() {
			@Override
			public void execute() {
				CalculationType calculationType = new CalculationType();
				Calculation calculation = view.getSelectedNodeValue();
				calculation.addCalculationType(calculationType);
				view.getTreeManager().addCalculationType(calculationType);
				notifyTemplateContentChanged();
			}
		});

		view.setShowFormCommand(TemplateNodeType.CALCULATION_TYPE, new Command() {
			@Override
			public void execute() {
				CalculationType calculationType = view.getSelectedNodeValue();
				showCodedTermForm(calculationType);
			}
		});

		view.setCommand(CalculationTypeAction.DELETE, deleteTreeElement);

		view.setCommand(CalculationTypeAction.ADD_VALID_TERMS, addValidTermCommand);
		
		view.setCommand(CalculationTypeAction.CREATE_ALGORITHM_TYPE, new Command() {
			@Override
			public void execute() {
				AlgorithmType algorithmType = new AlgorithmType();
				CalculationType calculationType = view.getSelectedNodeValue();
				calculationType.addAlgorithmType(algorithmType);
				view.getTreeManager().addAlgorithmType(algorithmType);
				notifyTemplateContentChanged();
			}
		});

		view.setShowFormCommand(TemplateNodeType.ALGORITHM_TYPE, new Command() {
			@Override
			public void execute() {
				AlgorithmType algorithmType = view.getSelectedNodeValue();
				showAlgorithmTypeForm(algorithmType);
			}
		});

		view.setCommand(AlgorithmTypeAction.DELETE, deleteTreeElement);
	}

	private void initNonQuantifiableActions() {
		view.setCommand(NonQuantifiableAction.DELETE, deleteTreeElement);

		view.setShowFormCommand(TemplateNodeType.NON_QUANTIFIABLE, new Command() {
			@Override
			public void execute() {
				NonQuantifiable nonQuantifiable = view.getSelectedNodeValue(); 
				showCodedTermForm(nonQuantifiable);
			}
		});
	}

	private void initTagActions() {
		view.setCommand(TagAction.DELETE, deleteTreeElement);

		view.setShowFormCommand(TemplateNodeType.TAG, new Command() {
			@Override
			public void execute() {
				showTagForm((Tag) view.getSelectedNodeValue());
			}
		});
	}
	
	public Template getActiveTemplate() {
		return activeTemplate;
	}

	public void setActiveTemplate(Template template) {
		activeTemplate = template;
		view.setActiveTemplate(template);
		
		// show empty warnings table
		view.clearWarnings();
		view.showWarnings();
		
		runTemplateTreeValidation();
	}
	
	/**
	 * Validate active template (separate thread)
	 */
	private void runTemplateTreeValidation() {
		Executor executor = new SimpleAsyncTaskExecutor();
		executor.execute(new Runnable() {
			@Override
			public void run() {
				TreeModel model = view.getTreeManager().getTreeModel();
				view.setWarnings(TemplateTreeValidator.getInstance().validateTemplateTree(model));
			}
		});
	}
	
	public void clear() {
		activeTemplate = null;
		view.clear();
		view.hideWarnings();
	}

	private void notifyTemplateContentChanged() {
		// notify template change listeners
		for (TemplateChangeListener listener : templateChangeListeners) {
			listener.onTemplateChanged(activeTemplate, false);
			runTemplateTreeValidation();
		}
	}

	public void editCurrentTemplate() {
		view.selectRootNode();
	}
	
	public void showTemplateForm(Template value, boolean isCreation) {
		//TODO: optimize this (every call new listener is created)
		TemplateFormPresenter p = formManager.templateForm(formCloseListener, new FormSubmitListener<Template>() {
			@Override
			public void onFormSubmit(Template value, boolean isCreation) {
				// save changes
				for (TemplateChangeListener listener : templateChangeListeners) {
					listener.onTemplateChanged(value, true);
				}
				
				// mark template as initialized after saving
				value.setInitialized(true);
			}
		}, lexiconSearchPresenter);
		p.setValue(value);
		view.showEditForm(p.prepareForm(isCreation), isCreation);
	}

	public void showComponentForm(TemplateComponent value) {
		ComponentFormPresenter p = formManager.componentForm(formCloseListener, formSubmitListener);
		p.setValue(value);
		view.showEditForm(p.prepareForm(false));
	}

	public void showAnatomicEntityForm(AnatomicEntity value) {
		AnatomicEntityFormPresenter p = formManager.anatomicEntityForm(formCloseListener, formSubmitListener);
		p.setValue(value);
		view.showEditForm(p.prepareForm(false));
	}

	public void showAnatomicEntityCharForm(AnatomicEntityCharacteristic value) {
		AnatomicEntityCharFormPresenter p = formManager.anatomicEntityCharForm(formCloseListener, formSubmitListener);
		p.setValue(value);
		view.showEditForm(p.prepareForm(false));
	}

	public void showImagingObservationForm(ImagingObservation value) {
		ImagingObservationFormPresenter p = formManager.imagingObservationForm(formCloseListener, formSubmitListener);
		p.setValue(value);
		view.showEditForm(p.prepareForm(false));
	}

	public void showImagingObservationCharForm(ImagingObservationCharacteristic value) {
		ImagingObservationCharFormPresenter p = formManager.imagingObservationCharForm(formCloseListener, formSubmitListener);
		p.setValue(value);
		view.showEditForm(p.prepareForm(false));
	}

	public void showInferenceForm(Inference value) {
		InferenceFormPresenter p = formManager.inferenceForm(formCloseListener, formSubmitListener);
		p.setValue(value);
		view.showEditForm(p.prepareForm(false));
	}

	public void showGeometricShapeForm(GeometricShape value) {
		GeometricShapeFormPresenter p = formManager.geometricShapeForm(formCloseListener, formSubmitListener);
		p.setValue(value);
		view.showEditForm(p.prepareForm(false));
	}

	public void showCharQuantificationForm(CharacteristicQuantification value) {
		CharQuantificationFormPresenter p = formManager.charQuantificationForm(formCloseListener, formSubmitListener);
		p.setValue(value);
		view.showEditForm(p.prepareForm(false));
	}
	
	public void showScaleForm(Scale value) {
		ScaleFormPresenter p = formManager.scaleForm(formCloseListener, formSubmitListener);
		p.setValue(value);
		view.showEditForm(p.prepareForm(false));
	}
	
	public void showOrdinalLevelForm(OrdinalLevel value) {
		OrdinalLevelFormPresenter p = formManager.ordinalLevelForm(formCloseListener, formSubmitListener);
		p.setValue(value);
		view.showEditForm(p.prepareForm(false));
	}
	
	public void showNumericalForm(Numerical value) {
		NumericalFormPresenter p = formManager.numericalForm(formCloseListener, formSubmitListener);
		p.setValue(value);
		view.showEditForm(p.prepareForm(false));
	}
	
	public void showIntervalForm(Interval value) {
		IntervalFormPresenter p = formManager.intervalForm(formCloseListener, formSubmitListener);
		p.setValue(value);
		view.showEditForm(p.prepareForm(false));
	}

	public void showQuantileForm(Quantile value) {
		QuantileFormPresenter p = formManager.quantileForm(formCloseListener, formSubmitListener);
		p.setValue(value);
		view.showEditForm(p.prepareForm(false));
	}
	
	private void showCodedTermForm(CodedTerm value) {
		CodedTermFormPresenter p = formManager.codedTermForm(formCloseListener, formSubmitListener, lexiconSearchPresenter);
		p.setValue(value);
		view.showEditForm(p.prepareForm(false));
	}

	private void showAlgorithmTypeForm(AlgorithmType value) {
		AlgorithmTypeFormPresenter p = formManager.algorithmTypeForm(formCloseListener, formSubmitListener, 
				lexiconSearchPresenter);
		p.setValue(value);
		view.showEditForm(p.prepareForm(false));
	}

	private void showTagForm(Tag value) {
		TagFormPresenter p = formManager.tagForm(formCloseListener, formSubmitListener, lexiconSearchPresenter);
		p.setValue(value);
		view.showEditForm(p.prepareForm(false));
	}

	private void showEmptyForm() {
		EmptyFormPresenter p = formManager.emptyForm();
		view.showEditForm(p.prepareForm(false));
	}
	
	public void addTemplateChangeListener(TemplateChangeListener listener) {
		templateChangeListeners.add(listener);
	}

	/**
	 * Implementors will be notified about changed template.
	 * 
	 * @author Vitaliy Semeshko
	 */
	public interface TemplateChangeListener {

		/**
		 * Notify listeners that template was changed.
		 * 
		 * @param template template that changed
		 * @param isAttributeOnlyChanged states that only attributes of template changed, not it's content
		 */
		public void onTemplateChanged(Template template, boolean isAttributeOnlyChanged);
		
	}

}
