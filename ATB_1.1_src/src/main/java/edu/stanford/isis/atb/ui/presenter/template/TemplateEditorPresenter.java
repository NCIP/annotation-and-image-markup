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
import edu.stanford.isis.atb.domain.template.AbstractNumberedElement;
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
			if (element instanceof AbstractNumberedElement)
				((AbstractNumberedElement)element).number();
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
					if (el instanceof AbstractNumberedElement)
						((AbstractNumberedElement)el).number();
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
					if (el instanceof AbstractNumberedElement)
						((AbstractNumberedElement)el).number();
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
