/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.template.form;

import edu.stanford.isis.atb.service.Command;
import edu.stanford.isis.atb.ui.Const;
import edu.stanford.isis.atb.ui.view.base.EditFormView;
import edu.stanford.isis.atb.ui.view.base.EditFormView.LabeledFormField;
import edu.stanford.isis.atb.ui.view.template.form.AlgorithmTypeFormView.AlgorithmTypeFormField;

/**
 * @author Vitaliy Semeshko
 */
public interface AlgorithmTypeFormView extends EditFormView<AlgorithmTypeFormField> {

	public void setSelectLexiconCommand(Command command);
	
	public enum AlgorithmTypeFormField implements LabeledFormField {
		TERM_BLOCK(Const.EMPTY),
		DESCRIPTION(Const.FRM_LBL_DESCRIPTION),
		UNIQUE_IDENTIFIER(Const.FRM_LBL_UNIQUE_IDENTIFIER),
		ALGORITHM_NAME(Const.FRM_LBL_ALGORITHM_NAME),
		ALGORITHM_VERSION(Const.FRM_LBL_ALGORITHM_VERSION),
		MATH_ML(Const.FRM_LBL_MATH_ML);
		
		private String label;
		
		private AlgorithmTypeFormField(String label) {
			this.label = label;
		}
		
		@Override
		public String getLabel() {
			return label;
		}
		
	}
	
}
