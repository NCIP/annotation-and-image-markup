/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.domain.ats;

import org.apache.commons.lang3.StringUtils;
import org.springframework.util.LinkedMultiValueMap;
import org.springframework.util.MultiValueMap;

/**
 * @author Vitaliy Semeshko
 */
public class ContainerSearchRequest extends AbstractSearchRequestParams {

	private static final String PARAM_CONTAINER_FUNCTION = "function";
	private static final String PARAM_CONTAINER_FUNCTION_NAME = "getAdvancedContainer";
	private static final String PARAM_CONTAINER_NAME = "cn";
	private static final String PARAM_CONTAINER_DESCRIPTION = "cd";
	private static final String PARAM_CONTAINER_AUTHOR = "ca";
	private static final String PARAM_DISEASE = "d";
	private static final String PARAM_BODY_PART = "bp";
	private static final String PARAM_MODALITY = "m";
	
	public MultiValueMap<String, String> asParams() {
		MultiValueMap<String, String> params = new LinkedMultiValueMap<String, String>();
		params.add(PARAM_CONTAINER_FUNCTION, PARAM_CONTAINER_FUNCTION_NAME);
		
		if (StringUtils.isNotBlank(name)) {
			params.add(PARAM_CONTAINER_NAME, name);
		}
		
		if (StringUtils.isNotBlank(description)) {
			params.add(PARAM_CONTAINER_DESCRIPTION, description);
		}
		
		if (StringUtils.isNotBlank(author)) {
			params.add(PARAM_CONTAINER_AUTHOR, author);
		}
		
		if (StringUtils.isNotBlank(disease)) {
			params.add(PARAM_DISEASE, disease);
		}
		
		if (StringUtils.isNotBlank(bodyPart)) {
			params.add(PARAM_BODY_PART, bodyPart);
		}
		
		if (StringUtils.isNotBlank(modality)) {
			params.add(PARAM_MODALITY, modality);
		}
		
		return params;
	}
	
}
