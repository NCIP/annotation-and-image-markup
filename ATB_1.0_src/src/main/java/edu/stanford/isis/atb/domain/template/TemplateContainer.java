/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.domain.template;

import java.util.Collections;
import java.util.HashSet;
import java.util.Set;

import org.apache.commons.collections.CollectionUtils;
import org.hibernate.validator.constraints.NotEmpty;
import org.simpleframework.xml.ElementList;
import org.simpleframework.xml.Root;

/**
 * Template Container.
 * 
 * @author Vitaliy Semeshko
 */

@Root(name="TemplateContainer", strict=false)
public class TemplateContainer extends AbstractTemplateContainer<TemplateRef> {
	
	@NotEmpty(message = "{templateContainer.templates.notEmpty}")
	@ElementList(name="Template", inline=true, required=false)
	private Set<TemplateRef> templates;
	
	@Override
	public Set<TemplateRef> getTemplates() {
		if (templates == null) {
			return Collections.emptySet();
		}
		
		return templates;
	}

	@Override
	public void addTemplate(TemplateRef template) {
		if (templates == null) {
			templates = new HashSet<TemplateRef>();
		}
		
		templates.add(template);
	}
	
	public boolean isValid() {
		boolean isValid = CollectionUtils.isNotEmpty(templates);
		if (isValid) {
			for (TemplateRef template : templates) {
				if (!template.isValid()) {
					isValid = false;
					break;
				}
			}
		}
		return isValid;
	}
	
}
