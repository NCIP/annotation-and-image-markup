/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.template.form;

import edu.stanford.isis.atb.ui.Const;
import edu.stanford.isis.atb.ui.view.base.EditFormView;
import edu.stanford.isis.atb.ui.view.base.EditFormView.LabeledFormField;
import edu.stanford.isis.atb.ui.view.template.form.NumericalFormView.NumericalFormField;

/**
 * @author Vitaliy Semeshko
 */
public interface NumericalFormView extends EditFormView<NumericalFormField> {

	public enum NumericalFormField implements LabeledFormField {
		VALUE(Const.FRM_LBL_VALUE),
		UCUM_STRING(Const.FRM_LBL_UCUM_STRING),
		OPERATOR(Const.FRM_LBL_OPERATOR);
		
		private String label;
		
		private NumericalFormField(String label) {
			this.label = label;
		}
		
		@Override
		public String getLabel() {
			return label;
		}
		
	}
	
}
