/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.base;

import java.awt.event.ActionListener;

import edu.stanford.isis.atb.ui.view.View;

/**
 * @author Vitaliy Semeshko
 */
public interface EditFormView<E extends Enum<?>> extends View {

	public void setFormSubmitActionListener(ActionListener l);
	
	public void setFormCloseActionListener(ActionListener l);
	
	public void setFieldValue(E field, Object value); 
	
	public void setReadOnly(boolean readOnly); 
	
	public Object getFieldValue(E field);
	
	public void initFieldsState(boolean isCreation);
	
	public void notifyValidationError(LabeledFormField formField, String msg);
	
	public interface LabeledFormField {
		
		public String getLabel();
		
	}
	
}
