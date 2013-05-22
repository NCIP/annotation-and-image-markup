/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.domain.template;

import javax.validation.constraints.NotNull;

import org.simpleframework.xml.Root;
import org.simpleframework.xml.Text;

/**
 * @author Vitaliy Semeshko
 */

@Root(name="GeometricShape", strict=false)
public class GeometricShape extends AbstractRemovableElement {

	@NotNull(message = "{geometricShape.value.notNull}")
	@Text(required=false)
	private GeometricShapeType value;

	public GeometricShapeType getValue() {
		return value;
	}

	public void setValue(GeometricShapeType value) {
		this.value = value;
	}

	@Override
	public String toString() {
		return "Geometric Shape: " + (value == null ? "" : value.toString());
	}
	
}
