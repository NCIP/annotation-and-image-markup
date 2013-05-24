/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.domain.template;

import org.hibernate.validator.constraints.NotEmpty;
import org.simpleframework.xml.Attribute;
import org.simpleframework.xml.Root;

/**
 * @author Vitaliy Semeshko
 */

@Root(name="Numerical", strict=false)
public class Numerical extends AbstractRemovableElement {

	@Attribute(required=false)
	private double value;
	
	@NotEmpty(message = "{numerical.ucumString.notEmpty}")
	@Attribute(required=false)
	private String ucumString;
	
	@Attribute(required=false)
	private Operator operator;

	public double getValue() {
		return value;
	}

	public void setValue(double value) {
		this.value = value;
	}

	public String getUcumString() {
		return ucumString;
	}

	public void setUcumString(String ucumString) {
		this.ucumString = ucumString;
	}

	public Operator getOperator() {
		return operator;
	}

	public void setOperator(Operator operator) {
		this.operator = operator;
	}
	
	@Override
	public String toString() {
		return "Numerical: " + value;
	}
	
}
