/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.template.form;

import edu.stanford.isis.atb.ui.Const;
import edu.stanford.isis.atb.ui.view.base.EditFormView;
import edu.stanford.isis.atb.ui.view.base.EditFormView.LabeledFormField;
import edu.stanford.isis.atb.ui.view.template.form.IntervalFormView.IntervalFormField;

/**
 * @author Vitaliy Semeshko
 */
public interface IntervalFormView extends EditFormView<IntervalFormField> {

	public enum IntervalFormField implements LabeledFormField {
		MIN_VALUE(Const.FRM_LBL_MIN_VALUE),
		MAX_VALUE(Const.FRM_LBL_MAX_VALUE),
		MIN_OPERATOR(Const.FRM_LBL_MIN_OPERATOR),
		MAX_OPERATOR(Const.FRM_LBL_MAX_OPERATOR),
		UCUM_STRING(Const.FRM_LBL_UCUM_STRING);
		
		private String label;
		
		private IntervalFormField(String label) {
			this.label = label;
		}
		
		@Override
		public String getLabel() {
			return label;
		}
		
	}
	
}
