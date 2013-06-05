/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.presenter.form;

import edu.stanford.isis.atb.domain.lexicon.Lexicon;
import edu.stanford.isis.atb.domain.lexicon.Term;
import edu.stanford.isis.atb.domain.template.TemplateContainer;
import edu.stanford.isis.atb.service.Command;
import edu.stanford.isis.atb.ui.presenter.form.AbstractFormPresenter.FormCloseListener;
import edu.stanford.isis.atb.ui.presenter.form.AbstractFormPresenter.FormSubmitListener;
import edu.stanford.isis.atb.ui.presenter.lexicon.form.LexiconFormPresenter;
import edu.stanford.isis.atb.ui.presenter.lexicon.form.TermFormPresenter;
import edu.stanford.isis.atb.ui.presenter.lexicon.search.CanAcceptSingleTerm;
import edu.stanford.isis.atb.ui.presenter.lexicon.search.LexiconSearch;
import edu.stanford.isis.atb.ui.presenter.lexicon.search.SearchPresenter.LexiconSearchMode;
import edu.stanford.isis.atb.ui.presenter.template.form.AlgorithmTypeFormPresenter;
import edu.stanford.isis.atb.ui.presenter.template.form.AnatomicEntityCharFormPresenter;
import edu.stanford.isis.atb.ui.presenter.template.form.AnatomicEntityFormPresenter;
import edu.stanford.isis.atb.ui.presenter.template.form.CharQuantificationFormPresenter;
import edu.stanford.isis.atb.ui.presenter.template.form.CodedTermFormPresenter;
import edu.stanford.isis.atb.ui.presenter.template.form.ComponentFormPresenter;
import edu.stanford.isis.atb.ui.presenter.template.form.EmptyFormPresenter;
import edu.stanford.isis.atb.ui.presenter.template.form.GeometricShapeFormPresenter;
import edu.stanford.isis.atb.ui.presenter.template.form.GroupFormPresenter;
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
import edu.stanford.isis.atb.ui.view.form.impl.EmptyFormViewImpl;
import edu.stanford.isis.atb.ui.view.lexicon.form.LexiconFormView;
import edu.stanford.isis.atb.ui.view.lexicon.form.TermFormView;
import edu.stanford.isis.atb.ui.view.lexicon.form.impl.LexiconFormViewImpl;
import edu.stanford.isis.atb.ui.view.lexicon.form.impl.TermFormViewImpl;
import edu.stanford.isis.atb.ui.view.template.form.AlgorithmTypeFormView;
import edu.stanford.isis.atb.ui.view.template.form.AnatomicEntityCharFormView;
import edu.stanford.isis.atb.ui.view.template.form.AnatomicEntityFormView;
import edu.stanford.isis.atb.ui.view.template.form.CharQuantificationFormView;
import edu.stanford.isis.atb.ui.view.template.form.CodedTermFormView;
import edu.stanford.isis.atb.ui.view.template.form.ComponentFormView;
import edu.stanford.isis.atb.ui.view.template.form.GeometricShapeFormView;
import edu.stanford.isis.atb.ui.view.template.form.GroupFormView;
import edu.stanford.isis.atb.ui.view.template.form.ImagingObservationCharFormView;
import edu.stanford.isis.atb.ui.view.template.form.ImagingObservationFormView;
import edu.stanford.isis.atb.ui.view.template.form.InferenceFormView;
import edu.stanford.isis.atb.ui.view.template.form.OrdinalLevelFormView;
import edu.stanford.isis.atb.ui.view.template.form.ScaleFormView;
import edu.stanford.isis.atb.ui.view.template.form.TagFormView;
import edu.stanford.isis.atb.ui.view.template.form.TemplateFormView;
import edu.stanford.isis.atb.ui.view.template.form.impl.AlgorithmTypeFormViewImpl;
import edu.stanford.isis.atb.ui.view.template.form.impl.AnatomicEntityCharFormViewImpl;
import edu.stanford.isis.atb.ui.view.template.form.impl.AnatomicEntityFormViewImpl;
import edu.stanford.isis.atb.ui.view.template.form.impl.CharQuantificationFormViewImpl;
import edu.stanford.isis.atb.ui.view.template.form.impl.CodedTermFormViewImpl;
import edu.stanford.isis.atb.ui.view.template.form.impl.ComponentFormViewImpl;
import edu.stanford.isis.atb.ui.view.template.form.impl.GeometricShapeFormViewImpl;
import edu.stanford.isis.atb.ui.view.template.form.impl.GroupFormViewImpl;
import edu.stanford.isis.atb.ui.view.template.form.impl.ImagingObservationCharFormViewImpl;
import edu.stanford.isis.atb.ui.view.template.form.impl.ImagingObservationFormViewImpl;
import edu.stanford.isis.atb.ui.view.template.form.impl.InferenceFormViewImpl;
import edu.stanford.isis.atb.ui.view.template.form.impl.IntervalFormViewImpl;
import edu.stanford.isis.atb.ui.view.template.form.impl.NumericalFormViewImpl;
import edu.stanford.isis.atb.ui.view.template.form.impl.OrdinalLevelFormViewImpl;
import edu.stanford.isis.atb.ui.view.template.form.impl.QuantileFormViewImpl;
import edu.stanford.isis.atb.ui.view.template.form.impl.ScaleFormViewImpl;
import edu.stanford.isis.atb.ui.view.template.form.impl.TagFormViewImpl;
import edu.stanford.isis.atb.ui.view.template.form.impl.TemplateFormViewImpl;

/**
 * Creates edit forms. 
 * 
 * @author Vitaliy Semeshko
 */
public class FormManager {

	// component form
	private GroupFormPresenter groupForm;
	
	// template forms
	private TemplateFormPresenter templateForm;
	private ComponentFormPresenter componentForm;
	private AnatomicEntityFormPresenter anatomicEntityForm;
	private AnatomicEntityCharFormPresenter anatomicEntityCharForm;
	private ImagingObservationFormPresenter imagingObservationForm;
	private ImagingObservationCharFormPresenter imagingObservationCharForm;
	private InferenceFormPresenter inferenceEntityForm;
	private GeometricShapeFormPresenter geometricShapeForm;
	private CharQuantificationFormPresenter charQuantificationForm;
	private CodedTermFormPresenter codedTermForm;
	private AlgorithmTypeFormPresenter algorithmTypeForm;
	private TagFormPresenter tagForm;
	private ScaleFormPresenter scaleForm;
	private OrdinalLevelFormPresenter ordinalLevelForm;
	private NumericalFormPresenter numericalForm;
	private IntervalFormPresenter intervalForm;
	private QuantileFormPresenter quantileForm;
	private EmptyFormPresenter emptyForm;
	
	// lexicon forms
	private LexiconFormPresenter lexiconForm;
	private TermFormPresenter termForm;
	
	public GroupFormPresenter groupForm(FormCloseListener close, FormSubmitListener<TemplateContainer> submit) {
		if (groupForm == null) {
			GroupFormView view = new GroupFormViewImpl();
			groupForm = new GroupFormPresenter(view);
			groupForm.setFormCloseListener(close);
			groupForm.setFormSubmitListener(submit);
		}
		return groupForm;
	}
	
	@SuppressWarnings({ "rawtypes", "unchecked" })
	public TemplateFormPresenter templateForm(FormCloseListener close, FormSubmitListener submit,
			final LexiconSearch lexiconSearch) {
		if (templateForm == null) {
			TemplateFormView view = new TemplateFormViewImpl();
			templateForm = new TemplateFormPresenter(view);
			templateForm.setFormCloseListener(close);
			templateForm.setFormSubmitListener(submit);
			templateForm.setSelectLexiconCommand(getStartSingleLexiconSearchCommand(lexiconSearch, templateForm));
		}
		return templateForm;
	}
	
	@SuppressWarnings({ "unchecked", "rawtypes" })
	public ComponentFormPresenter componentForm(FormCloseListener close, FormSubmitListener submit) {
		if (componentForm == null) {
			ComponentFormView view = new ComponentFormViewImpl();
			componentForm = new ComponentFormPresenter(view);
			componentForm.setFormCloseListener(close);
			componentForm.setFormSubmitListener(submit);
		}
		return componentForm;
	}
	
	@SuppressWarnings({ "unchecked", "rawtypes" })
	public AnatomicEntityCharFormPresenter anatomicEntityCharForm(FormCloseListener close, FormSubmitListener submit) {
		if (anatomicEntityCharForm == null) {
			AnatomicEntityCharFormView view = new AnatomicEntityCharFormViewImpl();
			anatomicEntityCharForm = new AnatomicEntityCharFormPresenter(view);
			anatomicEntityCharForm.setFormCloseListener(close);
			anatomicEntityCharForm.setFormSubmitListener(submit);
		}
		return anatomicEntityCharForm;
	}
	
	@SuppressWarnings({ "unchecked", "rawtypes" })
	public GeometricShapeFormPresenter geometricShapeForm(FormCloseListener close, FormSubmitListener submit) {
		if (geometricShapeForm == null) {
			GeometricShapeFormView view = new GeometricShapeFormViewImpl();
			geometricShapeForm = new GeometricShapeFormPresenter(view);
			geometricShapeForm.setFormCloseListener(close);
			geometricShapeForm.setFormSubmitListener(submit);
		}
		return geometricShapeForm;
	}
	
	@SuppressWarnings({ "unchecked", "rawtypes" })
	public CharQuantificationFormPresenter charQuantificationForm(FormCloseListener close, FormSubmitListener submit) {
		if (charQuantificationForm == null) {
			CharQuantificationFormView view = new CharQuantificationFormViewImpl();
			charQuantificationForm = new CharQuantificationFormPresenter(view);
			charQuantificationForm.setFormCloseListener(close);
			charQuantificationForm.setFormSubmitListener(submit);
		}
		return charQuantificationForm;
	}
	
	@SuppressWarnings({ "unchecked", "rawtypes" })
	public AnatomicEntityFormPresenter anatomicEntityForm(FormCloseListener close, FormSubmitListener submit) {
		if (anatomicEntityForm == null) {
			AnatomicEntityFormView view = new AnatomicEntityFormViewImpl();
			anatomicEntityForm = new AnatomicEntityFormPresenter(view);
			anatomicEntityForm.setFormCloseListener(close);
			anatomicEntityForm.setFormSubmitListener(submit);
		}
		return anatomicEntityForm;
	}
	
	@SuppressWarnings({ "unchecked", "rawtypes" })
	public InferenceFormPresenter inferenceForm(FormCloseListener close, FormSubmitListener submit) {
		if (inferenceEntityForm == null) {
			InferenceFormView view = new InferenceFormViewImpl();
			inferenceEntityForm = new InferenceFormPresenter(view);
			inferenceEntityForm.setFormCloseListener(close);
			inferenceEntityForm.setFormSubmitListener(submit);
		}
		return inferenceEntityForm;
	}
	
	@SuppressWarnings({ "unchecked", "rawtypes" })
	public ImagingObservationFormPresenter imagingObservationForm(FormCloseListener close, FormSubmitListener submit) {
		if (imagingObservationForm == null) {
			ImagingObservationFormView view = new ImagingObservationFormViewImpl();
			imagingObservationForm = new ImagingObservationFormPresenter(view);
			imagingObservationForm.setFormCloseListener(close);
			imagingObservationForm.setFormSubmitListener(submit);
		}
		return imagingObservationForm;
	}
	
	@SuppressWarnings({ "unchecked", "rawtypes" })
	public ImagingObservationCharFormPresenter imagingObservationCharForm(FormCloseListener close, 
			FormSubmitListener submit) {
		if (imagingObservationCharForm == null) {
			ImagingObservationCharFormView view = new ImagingObservationCharFormViewImpl();
			imagingObservationCharForm = new ImagingObservationCharFormPresenter(view);
			imagingObservationCharForm.setFormCloseListener(close);
			imagingObservationCharForm.setFormSubmitListener(submit);
		}
		return imagingObservationCharForm;
	}
	
	@SuppressWarnings({ "unchecked", "rawtypes" })
	public ScaleFormPresenter scaleForm(FormCloseListener close, FormSubmitListener submit) {
		if (scaleForm == null) {
			ScaleFormView view = new ScaleFormViewImpl();
			scaleForm = new ScaleFormPresenter(view);
			scaleForm.setFormCloseListener(close);
			scaleForm.setFormSubmitListener(submit);
		}
		return scaleForm;
	}
	
	@SuppressWarnings({ "unchecked", "rawtypes" })
	public OrdinalLevelFormPresenter ordinalLevelForm(FormCloseListener close, FormSubmitListener submit) {
		if (ordinalLevelForm == null) {
			OrdinalLevelFormView view = new OrdinalLevelFormViewImpl();
			ordinalLevelForm = new OrdinalLevelFormPresenter(view);
			ordinalLevelForm.setFormCloseListener(close);
			ordinalLevelForm.setFormSubmitListener(submit);
		}
		return ordinalLevelForm;
	}
	
	@SuppressWarnings({ "unchecked", "rawtypes" })
	public NumericalFormPresenter numericalForm(FormCloseListener close, FormSubmitListener submit) {
		if (numericalForm == null) {
			numericalForm = new NumericalFormPresenter(new NumericalFormViewImpl());
			numericalForm.setFormCloseListener(close);
			numericalForm.setFormSubmitListener(submit);
		}
		return numericalForm;
	}
	
	@SuppressWarnings({ "unchecked", "rawtypes" })
	public IntervalFormPresenter intervalForm(FormCloseListener close, FormSubmitListener submit) {
		if (intervalForm == null) {
			intervalForm = new IntervalFormPresenter(new IntervalFormViewImpl());
			intervalForm.setFormCloseListener(close);
			intervalForm.setFormSubmitListener(submit);
		}
		return intervalForm;
	}
	
	@SuppressWarnings({ "unchecked", "rawtypes" })
	public QuantileFormPresenter quantileForm(FormCloseListener close, FormSubmitListener submit) {
		if (quantileForm == null) {
			quantileForm = new QuantileFormPresenter(new QuantileFormViewImpl());
			quantileForm.setFormCloseListener(close);
			quantileForm.setFormSubmitListener(submit);
		}
		return quantileForm;
	}
	
	@SuppressWarnings({ "unchecked", "rawtypes" })
	public TagFormPresenter tagForm(FormCloseListener close, FormSubmitListener submit, 
			final LexiconSearch lexiconSearch) {
		if (tagForm == null) {
			TagFormView view = new TagFormViewImpl();
			tagForm = new TagFormPresenter(view);
			tagForm.setFormCloseListener(close);
			tagForm.setFormSubmitListener(submit);
			tagForm.setSelectLexiconCommand(getStartSingleLexiconSearchCommand(lexiconSearch, tagForm));
		}
		return tagForm;
	}
	
	@SuppressWarnings({ "unchecked", "rawtypes" })
	public CodedTermFormPresenter codedTermForm(FormCloseListener close, FormSubmitListener submit, 
			final LexiconSearch lexiconSearch) {
		if (codedTermForm == null) {
			CodedTermFormView view = new CodedTermFormViewImpl();
			codedTermForm = new CodedTermFormPresenter(view);
			codedTermForm.setFormCloseListener(close);
			codedTermForm.setFormSubmitListener(submit);
			codedTermForm.setSelectLexiconCommand(getStartSingleLexiconSearchCommand(lexiconSearch, codedTermForm));
		}
		return codedTermForm;
	}
	
	@SuppressWarnings({ "unchecked", "rawtypes" })
	public AlgorithmTypeFormPresenter algorithmTypeForm(FormCloseListener close, FormSubmitListener submit, 
			final LexiconSearch lexiconSearch) {
		if (algorithmTypeForm == null) {
			AlgorithmTypeFormView view = new AlgorithmTypeFormViewImpl();
			algorithmTypeForm = new AlgorithmTypeFormPresenter(view);
			algorithmTypeForm.setFormCloseListener(close);
			algorithmTypeForm.setFormSubmitListener(submit);
			algorithmTypeForm.setSelectLexiconCommand(getStartSingleLexiconSearchCommand(lexiconSearch, algorithmTypeForm));
		}
		return algorithmTypeForm;
	}
	
	public EmptyFormPresenter emptyForm() {
		if (emptyForm == null) {
			emptyForm = new EmptyFormPresenter(new EmptyFormViewImpl());
		}
		return emptyForm;
	}
	
	public LexiconFormPresenter lexiconForm(FormSubmitListener<Lexicon> submit) {
		if (lexiconForm == null) {
			LexiconFormView view = new LexiconFormViewImpl();
			lexiconForm = new LexiconFormPresenter(view);
			lexiconForm.setFormSubmitListener(submit);
		}
		return lexiconForm;
	}
	
	public TermFormPresenter termForm(FormSubmitListener<Term> submit) {
		if (termForm == null) {
			TermFormView view = new TermFormViewImpl();
			termForm = new TermFormPresenter(view);
			termForm.setFormSubmitListener(submit);
		}
		return termForm;
	}
	
	private Command getStartSingleLexiconSearchCommand(final LexiconSearch lexiconSearch, 
			final CanAcceptSingleTerm acceptor) {
		return new Command() {
			@Override
			public void execute() {
				// define acceptor
				lexiconSearch.setSingleTermAcceptor(acceptor);
				// show
				lexiconSearch.startSearch(LexiconSearchMode.SINGLE);
			}
		};
	}
	
}
