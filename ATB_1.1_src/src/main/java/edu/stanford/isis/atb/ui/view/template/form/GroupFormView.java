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
import edu.stanford.isis.atb.ui.view.template.form.GroupFormView.GroupFormField;

/**
 * @author Vitaliy Semeshko
 */
public interface GroupFormView extends EditFormView<GroupFormField> {

	public enum GroupFormField implements LabeledFormField {
		UID(Const.FRM_LBL_UID),
		NAME(Const.FRM_LBL_NAME),
		VERSION(Const.FRM_LBL_VERSION),
		DESCRIPTION(Const.FRM_LBL_DESCRIPTION),
		AUTHORS(Const.FRM_LBL_AUTHORS),
		CREATION_DATE(Const.FRM_LBL_DATE);
		
		private String label;
		
		private GroupFormField(String label) {
			this.label = label;
		}
		
		@Override
		public String getLabel() {
			return label;
		}
		
	}
	
}
