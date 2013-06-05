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
import edu.stanford.isis.atb.ui.view.template.form.GeometricShapeFormView.GeometricShapeFormField;

/**
 * @author Vitaliy Semeshko
 */
public interface GeometricShapeFormView extends EditFormView<GeometricShapeFormField> {

	public enum GeometricShapeFormField implements LabeledFormField {
		SHAPE_TYPE(Const.FRM_LBL_SHAPE_TYPE);
		
		private String label;
		
		private GeometricShapeFormField(String label) {
			this.label = label;
		}
		
		@Override
		public String getLabel() {
			return label;
		}
		
	}
	
}
