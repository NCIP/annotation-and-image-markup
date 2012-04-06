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
