/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.presenter.lexicon.form;

import static edu.stanford.isis.atb.ui.view.lexicon.form.TermFormView.TermFormField.CODE_MEANING;
import static edu.stanford.isis.atb.ui.view.lexicon.form.TermFormView.TermFormField.CODE_VALUE;
import static edu.stanford.isis.atb.ui.view.lexicon.form.TermFormView.TermFormField.CREATION_DATE;
import static edu.stanford.isis.atb.ui.view.lexicon.form.TermFormView.TermFormField.DESCRIPTION;
import static edu.stanford.isis.atb.ui.view.lexicon.form.TermFormView.TermFormField.MODIFICATION_DATE;

import org.apache.commons.lang3.StringUtils;

import edu.stanford.isis.atb.domain.lexicon.Term;
import edu.stanford.isis.atb.ui.presenter.form.AbstractFormPresenter;
import edu.stanford.isis.atb.ui.view.lexicon.form.TermFormView;

/**
 * @author Vitaliy Semeshko
 */
public class TermFormPresenter extends AbstractFormPresenter<Term, TermFormView> {

	public TermFormPresenter(TermFormView view) {
		super(view);
	}
	
	@Override
	public void setValue(Term value) {
		this.value = value;
		
		// initialize form fields
		view.setFieldValue(CODE_MEANING, StringUtils.trimToEmpty(value.getCodeMeaning()));
		view.setFieldValue(CODE_VALUE, StringUtils.trimToEmpty(value.getCodeValue()));
		view.setFieldValue(DESCRIPTION, StringUtils.trimToEmpty(value.getDescription()));
		view.setFieldValue(CREATION_DATE, value.getCreationDate());
		view.setFieldValue(MODIFICATION_DATE, value.getModificationDate());

		view.setReadOnly(value.getLexicon().isReadOnly());
	}

	@Override
	protected boolean validate() {
		String codeMeaning = view.getFieldValue(CODE_MEANING).toString();
		if (isEmptyString(codeMeaning, CODE_MEANING)) {
			return false;
		}
		
		String codeValue = view.getFieldValue(CODE_VALUE).toString();
		if (isEmptyString(codeValue, CODE_VALUE)) {
			return false;
		}
		
		String description = view.getFieldValue(DESCRIPTION).toString();

		value.setCodeMeaning(codeMeaning);
		value.setCodeValue(codeValue);
		value.setDescription(description);
		
		return true;
	}
	
}
