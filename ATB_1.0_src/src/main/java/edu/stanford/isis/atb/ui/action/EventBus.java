/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.action;

import edu.stanford.isis.atb.domain.template.TemplateContainer;
import edu.stanford.isis.atb.domain.template.TemplateRef;

/**
 * Application event bus.
 * 
 * @author Vitaliy Semeshko
 */
public interface EventBus {

	public void onTemplateChanged(TemplateRef template);
	
	public void onTemplateDeleted(TemplateRef template);
	
	public void onContainerImported(TemplateContainer container);
	
	public void onTemplateImported(TemplateRef template);
	
	public void onTemplateValidationFinished();
	
}
