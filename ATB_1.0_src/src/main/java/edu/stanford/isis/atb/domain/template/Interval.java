/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.domain.template;

import javax.validation.constraints.NotNull;

import org.hibernate.validator.constraints.NotEmpty;
import org.simpleframework.xml.Attribute;
import org.simpleframework.xml.Root;

/**
 * @author Vitaliy Semeshko
 */

@Root(name="Interval", strict=false)
public class Interval extends AbstractRemovableElement {

	@Attribute(required=false)
	private double minValue;
	
	@Attribute(required=false)
	private double maxValue;
	
	@NotNull(message = "{interval.minOperator.notNull}")
	@Attribute(required=false)
	private Operator minOperator;
	
	@NotNull(message = "{interval.maxOperator.notNull}")
	@Attribute(required=false)
	private Operator maxOperator;
	
	@NotEmpty(message = "{interval.ucumString.notEmpty}")
	@Attribute(required=false)
	private String ucumString;

	public double getMinValue() {
		return minValue;
	}

	public void setMinValue(double minValue) {
		this.minValue = minValue;
	}

	public double getMaxValue() {
		return maxValue;
	}

	public void setMaxValue(double maxValue) {
		this.maxValue = maxValue;
	}

	public Operator getMinOperator() {
		return minOperator;
	}

	public void setMinOperator(Operator minOperator) {
		this.minOperator = minOperator;
	}

	public Operator getMaxOperator() {
		return maxOperator;
	}

	public void setMaxOperator(Operator maxOperator) {
		this.maxOperator = maxOperator;
	}

	public String getUcumString() {
		return ucumString;
	}

	public void setUcumString(String ucumString) {
		this.ucumString = ucumString;
	}
	
	@Override
	public String toString() {
		return "Interval: min: " + minValue + " max: " + maxValue;
	}
	
}
