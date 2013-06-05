/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.domain.template;

import javax.validation.Valid;

import org.simpleframework.xml.Element;
import org.simpleframework.xml.Root;

import edu.stanford.isis.atb.system.validation.ForceGraphValidation;

/**
 * @author Vitaliy Semeshko
 */

@Root(name="Tag", strict=false)
public class Tag extends AbstractRemovableElement {

	@Valid
	@ForceGraphValidation
	@Element(name="TagName", required=false)
	private TagName tagName;
	
	@Valid
	@ForceGraphValidation
	@Element(name="TagValue", required=false)
	private TagValue tagValue;

	public TagName getTagName() {
		return tagName;
	}

	public void setTagName(TagName tagName) {
		this.tagName = tagName;
	}

	public TagValue getTagValue() {
		return tagValue;
	}

	public void setTagValue(TagValue tagValue) {
		this.tagValue = tagValue;
	}

	@Override
	public String toString() {
		return "Tag";
	}
	
}
