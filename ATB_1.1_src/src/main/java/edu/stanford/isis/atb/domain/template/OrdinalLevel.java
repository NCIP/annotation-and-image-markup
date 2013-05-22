/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.domain.template;

import org.simpleframework.xml.Attribute;
import org.simpleframework.xml.Root;

/**
 * @author Vitaliy Semeshko
 */

@Root(name="OrdinalLevel", strict=false)
public class OrdinalLevel extends AbstractRemovableElement {

	@Attribute
	private int integerValue;
	
	@Attribute(required=false)
	private String description;

	public int getIntegerValue() {
		return integerValue;
	}

	public void setIntegerValue(int integerValue) {
		this.integerValue = integerValue;
	}

	public String getDescription() {
		return description;
	}

	public void setDescription(String description) {
		this.description = description;
	}
	
	@Override
	public String toString() {
		return "Ordinal Level: " + integerValue;
	}
	
}
