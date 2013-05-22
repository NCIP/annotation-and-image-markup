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
import edu.stanford.isis.atb.ui.view.template.form.AnatomicEntityCharFormView.AnatomicEntityCharFormField;

/**
 * @author Vitaliy Semeshko
 */
public interface AnatomicEntityCharFormView extends EditFormView<AnatomicEntityCharFormField> {

	public enum AnatomicEntityCharFormField implements LabeledFormField {
		LABEL(Const.FRM_LBL_LABEL),
		EXPL_TEXT(Const.FRM_LBL_EXPLANATORY_TEXT),
		CARDINALITY(Const.FRM_LBL_CARDINALITY),
		ITEM_NUMBER(Const.FRM_LBL_ITEM_NUMBER),
		AUTHORS(Const.FRM_LBL_AUTHORS),
		SHOULD_DISPLAY(Const.FRM_LBL_SHOULD_DISPLAY),
		ANNOTATOR_CONFIDENCE(Const.FRM_LBL_ANNOTATOR_CONFIDENCE),
		GROUP_LABEL(Const.FRM_LBL_GROUP_LABEL);
		
		private String label;
		
		private AnatomicEntityCharFormField(String label) {
			this.label = label;
		}
		
		@Override
		public String getLabel() {
			return label;
		}
		
	}
	
}
