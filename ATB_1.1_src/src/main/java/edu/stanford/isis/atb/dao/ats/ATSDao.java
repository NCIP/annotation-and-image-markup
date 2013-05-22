/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.dao.ats;

import java.io.InputStream;

import org.springframework.core.io.Resource;

import edu.stanford.isis.atb.domain.ats.ContainerResults;
import edu.stanford.isis.atb.domain.ats.ContainerSearchRequest;
import edu.stanford.isis.atb.domain.ats.TemplateResults;
import edu.stanford.isis.atb.domain.ats.TemplateSearchRequest;

/**
 * @author Vitaliy Semeshko
 */
public interface ATSDao {

	public TemplateResults searchTemplates(TemplateSearchRequest request);
	
	public ContainerResults searchContainers(ContainerSearchRequest request);
	
	public InputStream download(String uid);
	
	public String loginAndReturnSessionId(String userName, String password);
	
	public void uploadContainer(Resource container);
	
}
