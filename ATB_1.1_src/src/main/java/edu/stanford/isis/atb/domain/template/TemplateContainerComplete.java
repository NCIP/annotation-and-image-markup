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

import org.hibernate.validator.constraints.NotEmpty;
import org.simpleframework.xml.ElementList;
import org.simpleframework.xml.Order;
import org.simpleframework.xml.Root;

/**
 * Template Container Complete.
 * Keeps full templates. Used for import/export.
 * 
 * @author Vitaliy Semeshko
 */

@Root(name="TemplateContainer", strict=false)
@Order(elements={"Template", "Tags"})
public class TemplateContainerComplete extends AbstractTemplateContainer<Template> {
	
	@NotEmpty(message = "{templateContainer.templates.notEmpty}")
	@ElementList(name="Template", inline=true, required=false)
	private Set<Template> templates;
	
	@Override
	public Set<Template> getTemplates() {
		if (templates == null) {
			return Collections.emptySet();
		}
		
		return templates;
	}

	@Override
	public void addTemplate(Template template) {
		if (templates == null) {
			templates = new HashSet<Template>();
		}
		
		templates.add(template);
	}
	
}
