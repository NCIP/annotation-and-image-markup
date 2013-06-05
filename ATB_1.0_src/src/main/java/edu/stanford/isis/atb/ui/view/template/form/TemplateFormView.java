/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.template.form;

import edu.stanford.isis.atb.service.Command;
import edu.stanford.isis.atb.ui.Const;
import edu.stanford.isis.atb.ui.view.base.EditFormView;
import edu.stanford.isis.atb.ui.view.base.EditFormView.LabeledFormField;
import edu.stanford.isis.atb.ui.view.template.form.TemplateFormView.TemplateFormField;

/**
 * @author Vitaliy Semeshko
 */
public interface TemplateFormView extends EditFormView<TemplateFormField> {

	public void setSelectLexiconCommand(Command command);
	
	public enum TemplateFormField implements LabeledFormField {
		UID(Const.FRM_LBL_UID),
		NAME(Const.FRM_LBL_NAME),
		VERSION(Const.FRM_LBL_VERSION),
		DESCRIPTION(Const.FRM_LBL_DESCRIPTION),
		AUTHORS(Const.FRM_LBL_AUTHORS),
		CREATION_DATE(Const.FRM_LBL_DATE),
		BODY_PART(Const.FRM_LBL_BODY_PART),
		DISEASE(Const.FRM_LBL_DISEASE),
		MODALITY(Const.FRM_LBL_MODALITY),
		PRECEDING_ANNOTATION(Const.FRM_LBL_PRECEDING_ANNOTATION),
		TERM_BLOCK(Const.EMPTY);
		
		private String label;
		
		private TemplateFormField(String label) {
			this.label = label;
		}
		
		@Override
		public String getLabel() {
			return label;
		}
		
	}
	
}
