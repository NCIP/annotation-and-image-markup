/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.domain.template;

import static edu.stanford.isis.atb.domain.template.DomainConst.DEFAULT_NAMESPACE;
import static edu.stanford.isis.atb.domain.template.DomainConst.XSI_NAMESPACE_LOCATION;
import static edu.stanford.isis.atb.domain.template.DomainConst.XSI_NAMESPACE_PREFIX;

import java.util.Collection;
import java.util.Collections;
import java.util.Set;

import javax.validation.Valid;

import org.simpleframework.xml.Attribute;
import org.simpleframework.xml.Element;
import org.simpleframework.xml.Namespace;

import edu.stanford.isis.atb.domain.template.RemovableElement.RemoveCommand;

/**
 * Template Container.
 * 
 * @author Vitaliy Semeshko
 */

@Namespace(reference=DEFAULT_NAMESPACE)
public abstract class AbstractTemplateContainer<T extends TemplateRef> extends AbstractPersistentContainer {
	
	@SuppressWarnings("unused")
	@Attribute
	@Namespace(reference=XSI_NAMESPACE_LOCATION, prefix=XSI_NAMESPACE_PREFIX)
	private String schemaLocation = DomainConst.SCHEMA_LOCATION;
	
	@Valid
	@Element(name="Tags", required=false)
	private Tags tags;
	
	public abstract Set<T> getTemplates();
	
	public abstract void addTemplate(T template);
	
	public void addTemplates(Iterable<T> templates) {
		for (T template : templates) {
			addTemplate(template);
		}
	}
	
	public void clearTemplates() {
		if (getTemplates() != null) {
			getTemplates().clear();
		}
	}
	
	public boolean containsTemplate(T template) {
		if (getTemplates() == null) {
			return false;
		}
		return getTemplates().contains(template);
	}
	
	public void removeTemplate(T template) {
		if (containsTemplate(template)) {
			getTemplates().remove(template);
		}
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
					AbstractTemplateContainer.this.tags = null;
				}
			});
		}
		tags.addTag(tag);
	}
	
}
