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
public class TemplateSearchRequest extends AbstractSearchRequestParams {

	private static final String PARAM_TEMPLATE_FUNCTION = "function";
	private static final String PARAM_TEMPLATE_FUNCTION_NAME = "getAdvancedTemplate";
	private static final String PARAM_TEMPLATE_NAME = "tn";
	private static final String PARAM_TEMPLATE_CODE_DESC = "tcd";
	private static final String PARAM_TEMPLATE_DESCRIPTION = "td";
	private static final String PARAM_TEMPLATE_AUTHOR = "ta";
	private static final String PARAM_DISEASE = "d";
	private static final String PARAM_BODY_PART = "bp";
	private static final String PARAM_MODALITY = "m";
	
	private String codeDesc;

	public String getCodeDesc() {
		return codeDesc;
	}

	public void setCodeDesc(String codeDesc) {
		this.codeDesc = codeDesc;
	}
	
	public MultiValueMap<String, String> asParams() {
		MultiValueMap<String, String> params = new LinkedMultiValueMap<String, String>();
		params.add(PARAM_TEMPLATE_FUNCTION, PARAM_TEMPLATE_FUNCTION_NAME);
		
		if (StringUtils.isNotBlank(name)) {
			params.add(PARAM_TEMPLATE_NAME, name);
		}
		
		if (StringUtils.isNotBlank(codeDesc)) {
			params.add(PARAM_TEMPLATE_CODE_DESC, codeDesc);
		}
		
		if (StringUtils.isNotBlank(description)) {
			params.add(PARAM_TEMPLATE_DESCRIPTION, description);
		}
		
		if (StringUtils.isNotBlank(author)) {
			params.add(PARAM_TEMPLATE_AUTHOR, author);
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
