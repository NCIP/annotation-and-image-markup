/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.template;

import java.util.Collection;

import edu.stanford.isis.atb.domain.template.TemplateRef;
import edu.stanford.isis.atb.service.Command;
import edu.stanford.isis.atb.ui.view.CanShowEditForm;
import edu.stanford.isis.atb.ui.view.View;

/**
 * @author Vitaliy Semeshko
 */
public interface TemplateView extends View, CanShowEditForm {

	public void setTemplates(Collection<TemplateRef> templates);
	
	public void setActiveTemplate(TemplateRef template);
	
	public void clearSelection();
	
	public void refreshTable();
	
	// commands
	
	public void setCommand(TemplateEditAction actionKey, Command command);
	
	// set listeners
	
	public void addTemplateSelectionListeners(TemplateSelectionListener ... listeners);
	
	/**
	 * Listeners of templates selections should implement this interface.
	 * 
	 * @author Vitaliy Semeshko
	 */
	public interface TemplateSelectionListener {
		
		public void onTemplateSelected(TemplateRef template);
		
	}
	
	public enum TemplateEditAction {
		CREATE_TEMPLATE,
		DELETE_TEMPLATE,
		COPY_TEMPLATE,
		EDIT_TEMPLATE,
		REMOTE_TEMPLATE_SEARCH,
		SEARCH_TEMPLATE;
	}
	
}
