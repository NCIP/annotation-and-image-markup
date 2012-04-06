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

package edu.stanford.isis.atb.ui.presenter.template.form;

import static edu.stanford.isis.atb.ui.Const.EMPTY;
import static edu.stanford.isis.atb.ui.view.template.form.TemplateFormView.TemplateFormField.AUTHORS;
import static edu.stanford.isis.atb.ui.view.template.form.TemplateFormView.TemplateFormField.CREATION_DATE;
import static edu.stanford.isis.atb.ui.view.template.form.TemplateFormView.TemplateFormField.DESCRIPTION;
import static edu.stanford.isis.atb.ui.view.template.form.TemplateFormView.TemplateFormField.MODALITY;
import static edu.stanford.isis.atb.ui.view.template.form.TemplateFormView.TemplateFormField.NAME;
import static edu.stanford.isis.atb.ui.view.template.form.TemplateFormView.TemplateFormField.PRECEDING_ANNOTATION;
import static edu.stanford.isis.atb.ui.view.template.form.TemplateFormView.TemplateFormField.TERM_BLOCK;
import static edu.stanford.isis.atb.ui.view.template.form.TemplateFormView.TemplateFormField.UID;
import static edu.stanford.isis.atb.ui.view.template.form.TemplateFormView.TemplateFormField.VERSION;

import java.util.Date;

import org.apache.commons.lang3.StringUtils;

import edu.stanford.isis.atb.domain.template.CodedTerm;
import edu.stanford.isis.atb.domain.template.Identifier;
import edu.stanford.isis.atb.domain.template.ModalityType;
import edu.stanford.isis.atb.domain.template.PrecedingAnnotationRequest;
import edu.stanford.isis.atb.domain.template.Template;
import edu.stanford.isis.atb.service.Command;
import edu.stanford.isis.atb.system.config.PropertyManager;
import edu.stanford.isis.atb.ui.Const;
import edu.stanford.isis.atb.ui.model.TermSearchItem;
import edu.stanford.isis.atb.ui.presenter.form.AbstractFormPresenter;
import edu.stanford.isis.atb.ui.presenter.lexicon.search.CanAcceptSingleTerm;
import edu.stanford.isis.atb.ui.view.template.form.TemplateFormView;

/**
 * @author Vitaliy Semeshko
 */
public class TemplateFormPresenter extends AbstractFormPresenter<Template, TemplateFormView> 
		implements CanAcceptSingleTerm {

	public TemplateFormPresenter(TemplateFormView view) {
		super(view);
	}
	
	@Override
	public void setValue(Template value) {
		this.value = value;
		
		// initialize form fields
		view.setFieldValue(NAME, StringUtils.trimToEmpty(value.getName()));
		view.setFieldValue(DESCRIPTION, StringUtils.trimToEmpty(value.getDescription()));
		
		String authors = StringUtils.trimToEmpty(value.getAuthors());
		if (StringUtils.isNotEmpty(authors)) {
			view.setFieldValue(AUTHORS, authors);
		} else if (!value.isInitialized()) {
			view.setFieldValue(AUTHORS, PropertyManager.getInstance().get(PropertyManager.CA_GRID_USER_NAME));
		} else {
			view.setFieldValue(AUTHORS, Const.EMPTY);
		}
		
		view.setFieldValue(MODALITY, value.getModality());
		view.setFieldValue(PRECEDING_ANNOTATION, value.getPrecedingAnnotation());
		
		Identifier uid = value.getUid();
		String uidStr;
		if (uid != null) {
			uidStr = StringUtils.trimToEmpty(uid.getOriginal());
		} else {
			uidStr = EMPTY;
		}
		
		view.setFieldValue(UID, uidStr);
		view.setFieldValue(CREATION_DATE, value.getCreationDate());
		view.setFieldValue(VERSION, StringUtils.trimToEmpty(value.getVersion()));
		
		CodedTerm term = new CodedTerm();
		term.setCodeValue(value.getCodeValue());
		term.setCodeMeaning(value.getCodeMeaning());
		term.setSchemaDesignator(value.getCodingSchemeDesignator());
		term.setSchemaVersion(value.getCodingSchemeVersion());
		view.setFieldValue(TERM_BLOCK, term);
	}

	@Override
	protected boolean validate() {
		String name = view.getFieldValue(NAME).toString();
		if (isEmptyString(name, NAME)) {
			return false;
		}

		String description = view.getFieldValue(DESCRIPTION).toString();
		if (isEmptyString(description, DESCRIPTION)) {
			return false;
		}
		
		String authors = view.getFieldValue(AUTHORS).toString();
//		if (isEmptyString(authors, AUTHORS)) {
//			return false;
//		}

		String uid = view.getFieldValue(UID).toString();
		if (isEmptyString(uid, UID)) {
			return false;
		}
		
		Date date = (Date) view.getFieldValue(CREATION_DATE);
		if (date == null) {
			notifyWrongFieldValue(CREATION_DATE);
			return false;
		}
		
		String version = view.getFieldValue(VERSION).toString();
		if (isEmptyString(version, VERSION)) {
			return false;
		}
		
		CodedTerm term = (CodedTerm) view.getFieldValue(TERM_BLOCK);
		
		if (creation) {
			value.setCreationDate(date);
		}
			
		value.setName(name);
		value.setDescription(description);
		value.setAuthors(authors);
			
		Object modality = view.getFieldValue(MODALITY);
		if (modality != null && modality instanceof ModalityType) {
			value.setModality((ModalityType) modality);
		} else {
			value.setModality(null);
		}
		
		Object precedingAnnotation = view.getFieldValue(PRECEDING_ANNOTATION);
		if (precedingAnnotation != null && precedingAnnotation instanceof PrecedingAnnotationRequest) {
			value.setPrecedingAnnotation((PrecedingAnnotationRequest) precedingAnnotation);
		} else {
			value.setPrecedingAnnotation(null);
		}
		
		value.setVersion(version);
		value.setCodeMeaning(term.getCodeMeaning());
		value.setCodeValue(term.getCodeValue());
		value.setCodingSchemeDesignator(term.getSchemaDesignator());
		value.setCodingSchemeVersion(term.getSchemaVersion());
		
		return true;
	}

	public void setSelectLexiconCommand(Command command) {
		view.setSelectLexiconCommand(command);
	}

	@Override
	public void accept(TermSearchItem searchItem) {
		view.setFieldValue(TERM_BLOCK, searchItem.getCodedTerm());
	}
	
}
