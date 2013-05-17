/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.lexicon.form;

import edu.stanford.isis.atb.ui.Const;
import edu.stanford.isis.atb.ui.view.base.EditFormView;
import edu.stanford.isis.atb.ui.view.base.EditFormView.LabeledFormField;
import edu.stanford.isis.atb.ui.view.lexicon.form.TermFormView.TermFormField;

/**
 * @author Vitaliy Semeshko
 */
public interface TermFormView extends EditFormView<TermFormField> {

	public enum TermFormField implements LabeledFormField {
		CODE_MEANING(Const.FRM_LBL_CODE_MEANING),
		CODE_VALUE(Const.FRM_LBL_CODE_VALUE),
		DESCRIPTION(Const.FRM_LBL_DESCRIPTION),
		CREATION_DATE(Const.FRM_LBL_CREATION_DATE),
		MODIFICATION_DATE(Const.FRM_LBL_MODIFICATION_DATE);		
		
		private String label;
		
		private TermFormField(String label) {
			this.label = label;
		}
		
		@Override
		public String getLabel() {
			return label;
		}
		
	}
	
}
