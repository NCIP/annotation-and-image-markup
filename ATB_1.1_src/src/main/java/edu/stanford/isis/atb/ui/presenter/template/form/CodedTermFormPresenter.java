/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.presenter.template.form;

import static edu.stanford.isis.atb.ui.view.template.form.CodedTermFormView.CodedTermFormField.TERM_BLOCK;
import edu.stanford.isis.atb.domain.template.CodedTerm;
import edu.stanford.isis.atb.service.Command;
import edu.stanford.isis.atb.ui.model.TermSearchItem;
import edu.stanford.isis.atb.ui.presenter.form.AbstractFormPresenter;
import edu.stanford.isis.atb.ui.presenter.lexicon.search.CanAcceptSingleTerm;
import edu.stanford.isis.atb.ui.view.template.form.CodedTermFormView;

/**
 * @author Vitaliy Semeshko
 */
public class CodedTermFormPresenter extends AbstractFormPresenter<CodedTerm, CodedTermFormView> 
		implements CanAcceptSingleTerm {

	public CodedTermFormPresenter(CodedTermFormView view) {
		super(view);
	}
	
	@Override
	public void setValue(CodedTerm value) {
		this.value = value;
		
		view.setFieldValue(TERM_BLOCK, value);
	}

	@Override
	protected boolean validate() {
		CodedTerm codedTerm = (CodedTerm) view.getFieldValue(TERM_BLOCK); 
			
		value.setCodeMeaning(codedTerm.getCodeMeaning());
		value.setCodeValue(codedTerm.getCodeValue());
		value.setSchemaDesignator(codedTerm.getSchemaDesignator());
		value.setSchemaVersion(codedTerm.getSchemaVersion());
		
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
