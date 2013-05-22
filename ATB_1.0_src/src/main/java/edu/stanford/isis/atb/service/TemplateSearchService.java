/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.service;

import edu.stanford.isis.atb.domain.ats.ContainerResults;
import edu.stanford.isis.atb.domain.ats.ContainerSearchRequest;
import edu.stanford.isis.atb.domain.ats.TemplateResults;
import edu.stanford.isis.atb.domain.ats.TemplateSearchRequest;
import edu.stanford.isis.atb.domain.template.TemplateContainer;
import edu.stanford.isis.atb.domain.template.TemplateRef;

/**
 * @author Vitaliy Semeshko
 */
public interface TemplateSearchService {

	public void searchTemplates(TemplateSearchRequest request, Callback<TemplateResults> callback);
	
	public void importTemplate(String uid, Callback<TemplateRef> callback);
	
	public void searchContainers(ContainerSearchRequest request, Callback<ContainerResults> callback);
	
	public void importContainer(String uid, Callback<TemplateContainer> callback);
	
	public void login(String userName, String password, Callback<Void> callback);
	
	public void publishContainer(TemplateContainer container, Callback<Void> callback);
	
}
