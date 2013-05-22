/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.domain.template;


/**
 * Used by elements that can be removed from parent.
 * 
 * @author Vitaliy Semeshko
 */
public interface RemovableElement {

	public void setRemoveCommand(RemoveCommand command);
	
	public void remove();
	
	public interface RemoveCommand {
		
		public void execute();
		
	}
	
}
