/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.presenter.template.form;

import static edu.stanford.isis.atb.ui.view.template.form.TagFormView.TagFormField.NAME_TERM_BLOCK;
import static edu.stanford.isis.atb.ui.view.template.form.TagFormView.TagFormField.STRING_VALUE;
import static edu.stanford.isis.atb.ui.view.template.form.TagFormView.TagFormField.VALUE_MODE_SWITCHER;
import static edu.stanford.isis.atb.ui.view.template.form.TagFormView.TagFormField.VALUE_TERM_BLOCK;

import org.apache.commons.lang3.StringUtils;

import edu.stanford.isis.atb.domain.template.CodedTerm;
import edu.stanford.isis.atb.domain.template.Tag;
import edu.stanford.isis.atb.service.Command;
import edu.stanford.isis.atb.system.exception.ATBException;
import edu.stanford.isis.atb.ui.model.TermSearchItem;
import edu.stanford.isis.atb.ui.presenter.form.AbstractFormPresenter;
import edu.stanford.isis.atb.ui.presenter.lexicon.search.CanAcceptSingleTerm;
import edu.stanford.isis.atb.ui.view.template.form.TagFormView;
import edu.stanford.isis.atb.ui.view.template.form.TagFormView.TagFormField;
import edu.stanford.isis.atb.ui.view.template.form.TagFormView.ValueMode;

/**
 * @author Vitaliy Semeshko
 */
public class TagFormPresenter extends AbstractFormPresenter<Tag, TagFormView> implements CanAcceptSingleTerm {

	private TagFormField lexiconSearchInitiator;
	
	public TagFormPresenter(TagFormView view) {
		super(view);
	}
	
	@Override
	public void setValue(Tag value) {
		this.value = value;
		
		view.setFieldValue(NAME_TERM_BLOCK, value.getTagName());
		
		if (value.getTagValue() == null) {
			throw new ATBException("Tag should have value.");
		}
		
		CodedTerm codedValue = value.getTagValue().getCodedValue();
		
		if (codedValue != null) {
			view.setFieldValue(VALUE_MODE_SWITCHER, ValueMode.LEXICON_TERM);
			view.setFieldValue(VALUE_TERM_BLOCK, codedValue);
		} else {
			view.setFieldValue(VALUE_MODE_SWITCHER, ValueMode.STRING);
			view.setFieldValue(STRING_VALUE, StringUtils.trimToEmpty(value.getTagValue().getStringValue()));
		}
	}

	@Override
	protected boolean validate() {
		CodedTerm nameCodedTerm = (CodedTerm) view.getFieldValue(NAME_TERM_BLOCK); 
		CodedTerm valueCodedTerm = (CodedTerm) view.getFieldValue(VALUE_TERM_BLOCK); 
		
		String stringValue = (String) view.getFieldValue(STRING_VALUE);
		
		ValueMode valueMode = (ValueMode) view.getFieldValue(VALUE_MODE_SWITCHER);
		
		switch (valueMode) {
		case STRING:
			value.getTagValue().setCodedValue(null);
			value.getTagValue().setStringValue(stringValue);
			break;
		case LEXICON_TERM:
			value.getTagValue().setStringValue(null);
			
			CodedTerm codedValue = new CodedTerm(); 
			value.getTagValue().setCodedValue(codedValue);
			
			codedValue.setCodeMeaning(valueCodedTerm.getCodeMeaning());
			codedValue.setCodeValue(valueCodedTerm.getCodeValue());
			codedValue.setSchemaDesignator(valueCodedTerm.getSchemaDesignator());
			codedValue.setSchemaVersion(valueCodedTerm.getSchemaVersion());
			break;
		}
		
		value.getTagName().setCodeMeaning(nameCodedTerm.getCodeMeaning());
		value.getTagName().setCodeValue(nameCodedTerm.getCodeValue());
		value.getTagName().setSchemaDesignator(nameCodedTerm.getSchemaDesignator());
		value.getTagName().setSchemaVersion(nameCodedTerm.getSchemaVersion());
		
		return true;
	}
	
	public void setSelectLexiconCommand(final Command command) {
		view.setSelectLexiconTagNameCommand(new Command() {
			@Override
			public void execute() {
				lexiconSearchInitiator = NAME_TERM_BLOCK;
				command.execute();
			}
		});
		
		view.setSelectLexiconTagValueCommand(new Command() {
			@Override
			public void execute() {
				lexiconSearchInitiator = VALUE_TERM_BLOCK;
				command.execute();
			}
		});
	}

	@Override
	public void accept(TermSearchItem searchItem) {
		if (lexiconSearchInitiator == NAME_TERM_BLOCK || lexiconSearchInitiator == VALUE_TERM_BLOCK) {
			view.setFieldValue(lexiconSearchInitiator, searchItem.getCodedTerm());
		} else {
			throw new ATBException("Unknown lexicon search initiator.");
		}
	}
	
}
