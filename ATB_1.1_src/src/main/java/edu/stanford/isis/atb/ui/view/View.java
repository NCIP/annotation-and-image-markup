/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view;

import java.awt.Component;

/**
 * Basic View.
 * 
 * @author Vitaliy Semeshko
 */
public interface View {

	public Component asComponent();
	
	public void showInformation(String text);
	
	public void showError(String text);
	
	public void showValidationError(String text);
	
	public boolean confirm(String text);
	
}
