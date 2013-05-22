/*L
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
import edu.stanford.isis.atb.ui.view.template.form.ComponentFormView.ComponentFormField;

/**
 * @author Vitaliy Semeshko
 */
public interface ComponentFormView extends EditFormView<ComponentFormField> {

	public enum ComponentFormField implements LabeledFormField {
		LABEL(Const.FRM_LBL_LABEL),
		EXPL_TEXT(Const.FRM_LBL_EXPLANATORY_TEXT),
		CARDINALITY(Const.FRM_LBL_CARDINALITY),
		AUTHORS(Const.FRM_LBL_AUTHORS),
		SHOULD_DISPLAY(Const.FRM_LBL_SHOULD_DISPLAY),
		GROUP_LABEL(Const.FRM_LBL_GROUP_LABEL);
		
		private String label;
		
		private ComponentFormField(String label) {
			this.label = label;
		}
		
		@Override
		public String getLabel() {
			return label;
		}
		
	}
	
}
