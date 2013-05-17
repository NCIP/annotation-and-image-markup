/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.system.validation;

import java.util.Set;

import org.apache.commons.collections.CollectionUtils;

import edu.stanford.isis.atb.domain.template.Template;

/**
 * @author Vitaliy Semeshko
 */
public class TemplateValidator extends AbstractValidator {

	private static final TemplateValidator instance = new TemplateValidator();
	
	public static TemplateValidator getInstance() {
		return instance;
	}

	public void validateTemplate(Template template) {
		Set<ValidationError> templateErrors = validateGraph(template);
		template.setValid(CollectionUtils.isEmpty(templateErrors));
	}
	
}
