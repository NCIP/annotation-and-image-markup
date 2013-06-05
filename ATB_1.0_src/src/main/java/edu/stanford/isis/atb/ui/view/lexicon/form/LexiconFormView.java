/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.lexicon.form;

import edu.stanford.isis.atb.ui.Const;
import edu.stanford.isis.atb.ui.view.base.EditFormView;
import edu.stanford.isis.atb.ui.view.base.EditFormView.LabeledFormField;
import edu.stanford.isis.atb.ui.view.lexicon.form.LexiconFormView.LexiconFormField;

/**
 * @author Vitaliy Semeshko
 */
public interface LexiconFormView extends EditFormView<LexiconFormField> {

	public enum LexiconFormField implements LabeledFormField {
		NAME(Const.FRM_LBL_NAME),
		SCHEMA_DESIGNATOR(Const.FRM_LBL_SCHEMA_DESIGNATOR),
		SCHEMA_VERSION(Const.FRM_LBL_SCHEMA_VERSION),
		DESCRIPTION(Const.FRM_LBL_DESCRIPTION),
		AUTHORS(Const.FRM_LBL_AUTHORS),
		READ_ONLY(Const.FRM_LBL_IS_READ_ONLY),
		CREATION_DATE(Const.FRM_LBL_CREATION_DATE),
		MODIFICATION_DATE(Const.FRM_LBL_MODIFICATION_DATE);
		
		private String label;
		
		private LexiconFormField(String label) {
			this.label = label;
		}
		
		@Override
		public String getLabel() {
			return label;
		}
		
	}
	
}
