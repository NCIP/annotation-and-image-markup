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
import javax.validation.constraints.NotNull;
import javax.validation.constraints.Size;

import org.apache.commons.lang3.StringUtils;
import org.simpleframework.xml.Attribute;
import org.simpleframework.xml.ElementList;
import org.simpleframework.xml.core.Commit;

/**
 * @author Vitaliy Semeshko
 */
public class Scale extends AbstractRemovableElement {

	@Attribute(required=false)
	private String description;
	
	@Attribute(required=false)
	private String comment;

	@Valid
	@NotNull(message = "{scale.ordinalLevels.min2}")
	@Size(min = 2, message = "{scale.ordinalLevels.min2}")
	@ElementList(name="OrdinalLevel", inline=true, required=false)
	private List<OrdinalLevel> ordinalLevels;
	
	@SuppressWarnings("unused")
	@Commit
	private void afterPropertiesSet() {
		if (ordinalLevels != null) {
			for (final OrdinalLevel ordinalLevel : ordinalLevels) {
				ordinalLevel.initRemoveCommand(ordinalLevels);
			}
		}
	}
	
	public String getDescription() {
		return description;
	}

	public void setDescription(String description) {
		this.description = description;
	}

	public String getComment() {
		return comment;
	}

	public void setComment(String comment) {
		this.comment = comment;
	}
	
	public Collection<OrdinalLevel> getOrdinalLevels() {
		if (ordinalLevels == null) {
			return Collections.emptyList();
		}
		return ordinalLevels;
	}

	public void addOrdinalLevel(OrdinalLevel ordinalLevel) {
		if (ordinalLevels == null) {
			ordinalLevels = new ArrayList<OrdinalLevel>();
		}
		ordinalLevels.add(ordinalLevel);
		ordinalLevel.initRemoveCommand(ordinalLevels);
	}
	
	@Override
	public String toString() {
		return "Scale: " + StringUtils.trimToEmpty(description);
	}
	
}
