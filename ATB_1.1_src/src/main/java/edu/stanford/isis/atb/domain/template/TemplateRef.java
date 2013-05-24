/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.domain.template;

import javax.validation.Valid;
import javax.validation.constraints.NotNull;

import org.simpleframework.xml.Attribute;
import org.simpleframework.xml.Root;

import edu.stanford.isis.atb.system.validation.ForceGraphValidation;

/**
 * Template reference. 
 * Encapsulates all template attributes without nested elements. 
 * 
 * @author Vitaliy Semeshko
 */

@Root(name="Template", strict=false)
public class TemplateRef extends AbstractPersistentContainer {

	@Valid
	@ForceGraphValidation
	@NotNull
	private CodedTerm codedTerm = new CodedTerm();
	
	private boolean valid = true;
	
	@Attribute(required=false)
	public String getCodeValue() {
		return codedTerm.getCodeValue();
	}

	@Attribute(required=false)
	public void setCodeValue(String codeValue) {
		codedTerm.setCodeValue(codeValue);
	}

	@Attribute(required=false)
	public String getCodeMeaning() {
		return codedTerm.getCodeMeaning();
	}

	@Attribute(required=false)
	public void setCodeMeaning(String codeMeaning) {
		codedTerm.setCodeMeaning(codeMeaning);
	}

	@Attribute(required=false)
	public String getCodingSchemeDesignator() {
		return codedTerm.getSchemaDesignator();
	}

	@Attribute(required=false)
	public void setCodingSchemeDesignator(String codingSchemeDesignator) {
		codedTerm.setSchemaDesignator(codingSchemeDesignator);
	}
	
	@Attribute(required=false)
	public String getCodingSchemeVersion() {
		return codedTerm.getSchemaVersion();
	}

	@Attribute(required=false)
	public void setCodingSchemeVersion(String codingSchemeVersion) {
		codedTerm.setSchemaVersion(codingSchemeVersion);
	}

	public boolean isValid() {
		return valid;
	}

	public void setValid(boolean valid) {
		this.valid = valid;
	}
	
}
