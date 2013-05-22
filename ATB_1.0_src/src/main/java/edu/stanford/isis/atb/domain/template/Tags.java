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
import org.simpleframework.xml.ElementList;
import org.simpleframework.xml.Root;
import org.simpleframework.xml.core.Commit;

/**
 * @author Vitaliy Semeshko
 */

@Root(name="Tags", strict=false)
public class Tags extends AbstractRemovableElement {

	@Valid
	@NotEmpty(message = "{tags.tags.notEmpty}")
	@ElementList(name="Tag", inline=true, required=false)
	private List<Tag> tags;

	@SuppressWarnings("unused")
	@Commit
	private void afterPropertiesSet() {
		if (tags != null) {
			for (Tag tag : tags) {
				initTagsRemoveCommand(tag);
			}
		}
	}
	
	protected void afterDescendantPropertiesSet() {}
	
	public Collection<Tag> getTags() {
		if (tags == null) {
			return Collections.emptyList();
		}
		
		return tags;
	}

	public void addTag(Tag tag) {
		if (tags == null) {
			tags = new ArrayList<Tag>();
		}
		
		tags.add(tag);
		initTagsRemoveCommand(tag);
	}
	
	private void initTagsRemoveCommand(final Tag tag) {
		tag.setRemoveCommand(new RemoveCommand() {
			@Override
			public void execute() {
				tags.remove(tag);
				// if no tags left remove wrapper itself
				if (tags.isEmpty()) {
					Tags.this.remove();
				}
			}
		});
	}
	
}
