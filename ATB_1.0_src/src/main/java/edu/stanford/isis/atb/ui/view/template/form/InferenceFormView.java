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
import edu.stanford.isis.atb.ui.view.template.form.InferenceFormView.InferenceFormField;

/**
 * @author Vitaliy Semeshko
 */
public interface InferenceFormView extends EditFormView<InferenceFormField> {

	public enum InferenceFormField implements LabeledFormField {
		ANNOTATOR_CONFIDENCE(Const.FRM_LBL_ANNOTATOR_CONFIDENCE);
		
		private String label;
		
		private InferenceFormField(String label) {
			this.label = label;
		}
		
		@Override
		public String getLabel() {
			return label;
		}
		
	}
	
}
