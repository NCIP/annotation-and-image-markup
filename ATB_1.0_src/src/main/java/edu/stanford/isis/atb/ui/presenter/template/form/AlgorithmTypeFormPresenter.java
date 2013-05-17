/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.presenter.template.form;

import static edu.stanford.isis.atb.ui.view.template.form.AlgorithmTypeFormView.AlgorithmTypeFormField.ALGORITHM_NAME;
import static edu.stanford.isis.atb.ui.view.template.form.AlgorithmTypeFormView.AlgorithmTypeFormField.ALGORITHM_VERSION;
import static edu.stanford.isis.atb.ui.view.template.form.AlgorithmTypeFormView.AlgorithmTypeFormField.DESCRIPTION;
import static edu.stanford.isis.atb.ui.view.template.form.AlgorithmTypeFormView.AlgorithmTypeFormField.MATH_ML;
import static edu.stanford.isis.atb.ui.view.template.form.AlgorithmTypeFormView.AlgorithmTypeFormField.TERM_BLOCK;
import static edu.stanford.isis.atb.ui.view.template.form.AlgorithmTypeFormView.AlgorithmTypeFormField.UNIQUE_IDENTIFIER;

import org.apache.commons.lang3.StringUtils;

import edu.stanford.isis.atb.domain.template.AlgorithmType;
import edu.stanford.isis.atb.domain.template.CodedTerm;
import edu.stanford.isis.atb.service.Command;
import edu.stanford.isis.atb.ui.model.TermSearchItem;
import edu.stanford.isis.atb.ui.presenter.form.AbstractFormPresenter;
import edu.stanford.isis.atb.ui.presenter.lexicon.search.CanAcceptSingleTerm;
import edu.stanford.isis.atb.ui.view.template.form.AlgorithmTypeFormView;
import edu.stanford.isis.atb.ui.view.template.form.AlgorithmTypeFormView.AlgorithmTypeFormField;

/**
 * @author Vitaliy Semeshko
 */
public class AlgorithmTypeFormPresenter extends AbstractFormPresenter<AlgorithmType, AlgorithmTypeFormView> 
		implements CanAcceptSingleTerm {

	public AlgorithmTypeFormPresenter(AlgorithmTypeFormView view) {
		super(view);
	}
	
	@Override
	public void setValue(AlgorithmType value) {
		this.value = value;
		
		view.setFieldValue(AlgorithmTypeFormField.TERM_BLOCK, value);
		view.setFieldValue(DESCRIPTION, StringUtils.trimToEmpty(value.getDescription()));
		view.setFieldValue(UNIQUE_IDENTIFIER, StringUtils.trimToEmpty(value.getUniqueIdentifier()));
		view.setFieldValue(ALGORITHM_NAME, StringUtils.trimToEmpty(value.getAlgorithmName()));
		view.setFieldValue(ALGORITHM_VERSION, StringUtils.trimToEmpty(value.getAlgorithmVersion()));
		view.setFieldValue(MATH_ML, StringUtils.trimToEmpty(value.getMathML()));
	}

	@Override
	protected boolean validate() {
		CodedTerm codedTerm = (CodedTerm) view.getFieldValue(TERM_BLOCK); 
			
		String description = view.getFieldValue(DESCRIPTION).toString();
		if (isEmptyString(description, AlgorithmTypeFormField.DESCRIPTION)) {
			return false;
		}
		
		String uniqueIdentifier = view.getFieldValue(UNIQUE_IDENTIFIER).toString();
		String algorithmName = view.getFieldValue(ALGORITHM_NAME).toString();
		String algorithmVersion = view.getFieldValue(ALGORITHM_VERSION).toString();
		String mathML = view.getFieldValue(MATH_ML).toString();
		
		value.setCodeMeaning(codedTerm.getCodeMeaning());
		value.setCodeValue(codedTerm.getCodeValue());
		value.setSchemaDesignator(codedTerm.getSchemaDesignator());
		value.setSchemaVersion(codedTerm.getSchemaVersion());
		
		value.setDescription(description);
		value.setUniqueIdentifier(uniqueIdentifier);
		value.setAlgorithmName(algorithmName);
		value.setAlgorithmVersion(algorithmVersion);
		value.setMathML(mathML);
		
		return true;
	}
	
	public void setSelectLexiconCommand(Command command) {
		view.setSelectLexiconCommand(command);
	}

	@Override
	public void accept(TermSearchItem searchItem) {
		view.setFieldValue(AlgorithmTypeFormField.TERM_BLOCK, searchItem.getCodedTerm());
	}
	
}
