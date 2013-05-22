/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.domain.template;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.List;

import javax.validation.Valid;

import org.hibernate.validator.constraints.NotEmpty;
import org.simpleframework.xml.Attribute;
import org.simpleframework.xml.Element;
import org.simpleframework.xml.ElementList;
import org.simpleframework.xml.Root;
import org.simpleframework.xml.core.Commit;

import edu.stanford.isis.atb.domain.template.NumberedElement.NumberingCommand;
import edu.stanford.isis.atb.domain.template.RemovableElement.RemoveCommand;

/**
 * @author Vitaliy Semeshko
 */
@Root(name="Template", strict=false)
public class Template extends TemplateRef {

	@Attribute(required=false)
	private ModalityType modality;
	
	@Attribute(required=false)
	private PrecedingAnnotationRequest precedingAnnotation;
	
	@Valid
	@NotEmpty(message = "{template.components.notEmpty}")
	@ElementList(name="Component", inline=true, required=false)
	private List<TemplateComponent> components;
	
	@Valid
	@Element(name="Tags", required=false)
	private Tags tags;
	
	@SuppressWarnings("unused")
	@Commit
	private void afterPropertiesSet() {
		if (components != null) {
			for (TemplateComponent component : components) {
				component.initRemoveCommand(components);
				component.initContext(components);
				component.setNumberingCommand(new NumberingCommand() {
					@Override
					public void execute() {
						reNumberComponents();
					}
				});
			}
		}

		if (tags != null) {
			tags.setRemoveCommand(new RemoveCommand() {
				@Override
				public void execute() {
					Template.this.tags = null;
				}
			});
		}
	}
	
	public ModalityType getModality() {
		return modality;
	}

	public void setModality(ModalityType modality) {
		this.modality = modality;
	}

	public PrecedingAnnotationRequest getPrecedingAnnotation() {
		return precedingAnnotation;
	}

	public void setPrecedingAnnotation(PrecedingAnnotationRequest precedingAnnotation) {
		this.precedingAnnotation = precedingAnnotation;
	}

	public Collection<TemplateComponent> getComponents() {
		if (components == null) {
			return Collections.emptyList();
		}
		return components;
	}

	public void addComponent(TemplateComponent component) {
		if (components == null) {
			components = new ArrayList<TemplateComponent>();
		}
		components.add(component);
		component.setItemNumber(components.size());
		component.initRemoveCommand(components);
		component.initContext(components);
		component.setNumberingCommand(new NumberingCommand() {
			@Override
			public void execute() {
				reNumberComponents();
			}
		});
	}
	
	public Collection<Tag> getTags() {
		if (tags == null) {
			return Collections.emptyList();
		}
		return tags.getTags();
	}
	
	public void addTag(Tag tag) {
		if (tags == null) {
			tags = new Tags();
			tags.setRemoveCommand(new RemoveCommand() {
				@Override
				public void execute() {
					Template.this.tags = null;
				}
			});
		}
		tags.addTag(tag);
	}

	private void reNumberComponents() {
		// update item numbers
		for (int i = 0; i < components.size(); i++) {
			TemplateComponent c = components.get(i);
			c.setItemNumber(i+1);
		}
	}
	
}
