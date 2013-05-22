/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.domain.template;

import static org.apache.commons.lang3.StringUtils.isNotEmpty;

import javax.validation.Valid;
import javax.validation.constraints.AssertTrue;

import org.simpleframework.xml.Element;
import org.simpleframework.xml.Root;

import edu.stanford.isis.atb.system.validation.ForceGraphValidation;

/**
 * @author Vitaliy Semeshko
 */

@Root(name="TagValue", strict=false)
public class TagValue extends AbstractRemovableElement {

	@Valid
	@ForceGraphValidation
	@Element(name="CodedValue", required=false)
	private CodedTerm codedValue;
	
	@Element(name="StringValue", required=false)
	private String stringValue;

	@AssertTrue(message = "{tagValue.isValid}")
	public boolean isValid() {
		return codedValue != null || isNotEmpty(stringValue);
	}
	
	public CodedTerm getCodedValue() {
		return codedValue;
	}

	public void setCodedValue(CodedTerm codedValue) {
		this.codedValue = codedValue;
	}

	public String getStringValue() {
		return stringValue;
	}

	public void setStringValue(String stringValue) {
		this.stringValue = stringValue;
	}

	@Override
	public String toString() {
		return "TagValue";
	}
	
}
