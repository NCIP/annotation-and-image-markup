/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.ui.view.group;

import java.util.Collection;

import edu.stanford.isis.atb.domain.ats.ContainerSearchRequest;
import edu.stanford.isis.atb.domain.ats.ContainerSingleResult;
import edu.stanford.isis.atb.service.Command;
import edu.stanford.isis.atb.ui.view.View;

/**
 * @author Vitaliy Semeshko
 */
public interface GroupSearchView extends View {

	public void setContainers(Collection<ContainerSingleResult> containers);
	
	public ContainerSingleResult getSelectedContainer();
	
	public ContainerSearchRequest getContainerSearchRequest();
	
	public void clear();
	
	public void setSearchCommand(Command command);
	
	public void setSelectCommand(Command command);
	
	public void showAsDialog();
	
}
