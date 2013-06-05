/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
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
