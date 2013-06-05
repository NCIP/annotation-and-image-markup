/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
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
