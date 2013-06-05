/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.template;

import java.util.Collection;

import edu.stanford.isis.atb.domain.ats.TemplateSearchRequest;
import edu.stanford.isis.atb.domain.ats.TemplateSingleResult;
import edu.stanford.isis.atb.service.Command;
import edu.stanford.isis.atb.ui.view.View;

/**
 * @author Vitaliy Semeshko
 */
public interface TemplateSearchView extends View {

	public void setTemplates(Collection<TemplateSingleResult> templates);
	
	public TemplateSingleResult getSelectedTemplate();
	
	public TemplateSearchRequest getTemplateSearchRequest();
	
	public void clear();
	
	public void setSearchCommand(Command command);
	
	public void setSelectCommand(Command command);
	
	public void showAsDialog();
	
}
