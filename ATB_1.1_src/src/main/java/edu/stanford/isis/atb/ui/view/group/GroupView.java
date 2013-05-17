/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.group;

import java.awt.Component;
import java.util.Collection;

import edu.stanford.isis.atb.domain.template.TemplateContainer;
import edu.stanford.isis.atb.domain.template.TemplateRef;
import edu.stanford.isis.atb.service.Command;
import edu.stanford.isis.atb.ui.view.View;

/**
 * @author Vitaliy Semeshko
 */
public interface GroupView extends View {

	// data
	
	public void setContainers(Collection<TemplateContainer> containers);
	
	public void setTemplates(Collection<TemplateRef> templates);
	
	public void setActiveContainer(TemplateContainer container, boolean updateMemberships);
	
	public Iterable<TemplateRef> getMarkedTemplatesForLinking();
	
	// commands
	
	public void setLinkTemplatesWithContainerCommand(Command command);
	
	public void setCommand(GroupAction actionKey, Command command);
	
	// listeners
	
	public void addContainerSelectionListener(ContainerSelectionListener listener);
	
	// view
	
	public void hideEditForm();
	
	public void showEditForm(Component c);
	
	public void clearContainerDetails(boolean unmarkMemberships);
	
	public boolean showTemplateNamePrompt(TemplateContainer container);
	
	/**
	 * Refresh view and after select provided element.
	 * 
	 * @param container container to select after refresh. If <code>null</code> then
	 */
	//public void refresh(TemplateContainer container);
	
	/**
	 * Listeners of container selections should implement this interface.
	 * 
	 * @author Vitaliy Semeshko
	 */
	public interface ContainerSelectionListener {
		
		public void onContainerSelected(TemplateContainer container);
		
	}
	
	public enum GroupAction {
		CREATE_GROUP,
		EDIT_GROUP,
		DELETE_GROUP,
		COPY_GROUP,
		IMPORT_EXPORT,
		IMPORT,
		EXPORT,
		SEARCH_PUBLISH,
		SEARCH,
		PUBLISH;
	}
	
}
