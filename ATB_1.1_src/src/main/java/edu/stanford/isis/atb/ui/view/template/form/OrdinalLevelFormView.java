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
import edu.stanford.isis.atb.ui.view.template.form.OrdinalLevelFormView.OrdinalLevelFormField;

/**
 * @author Vitaliy Semeshko
 */
public interface OrdinalLevelFormView extends EditFormView<OrdinalLevelFormField> {

	public enum OrdinalLevelFormField implements LabeledFormField {
		VALUE(Const.FRM_LBL_VALUE),
		DESCRIPTION(Const.FRM_LBL_DESCRIPTION);
		
		private String label;
		
		private OrdinalLevelFormField(String label) {
			this.label = label;
		}
		
		@Override
		public String getLabel() {
			return label;
		}
		
	}
	
}
