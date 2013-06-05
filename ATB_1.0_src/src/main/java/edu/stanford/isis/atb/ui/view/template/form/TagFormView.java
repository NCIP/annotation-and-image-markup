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
import edu.stanford.isis.atb.ui.view.template.form.TagFormView.TagFormField;

/**
 * @author Vitaliy Semeshko
 */
public interface TagFormView extends EditFormView<TagFormField> {

	public void setSelectLexiconTagNameCommand(Command command);
	
	public void setSelectLexiconTagValueCommand(Command command);
	
	public enum TagFormField implements LabeledFormField {
		NAME_TERM_BLOCK(Const.EMPTY),
		VALUE_TERM_BLOCK(Const.EMPTY),
		VALUE_MODE_SWITCHER(Const.EMPTY),
		STRING_VALUE(Const.FRM_LBL_STRING_VALUE);
		
		private String label;
		
		private TagFormField(String label) {
			this.label = label;
		}
		
		@Override
		public String getLabel() {
			return label;
		}
		
	}
	
	public enum ValueMode {
		STRING,
		LEXICON_TERM;
	}
	
}
