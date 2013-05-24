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

import edu.stanford.isis.atb.domain.LexiconTermAttributes;

/**
 * @author Vitaliy Semeshko
 */

@Root(strict=false)
public class CodedTerm extends AbstractRemovableElement implements LexiconTermAttributes {

	@NotEmpty(message = "{codedTerm.codeValue.notEmpty}")
	@Attribute(required=false)
	private String codeValue;
	
	@NotEmpty(message = "{codedTerm.codeMeaning.notEmpty}")
	@Attribute(required=false)
	private String codeMeaning;
	
	@NotEmpty(message = "{codedTerm.schemaDesignator.notEmpty}")
	@Attribute(name="codingSchemeDesignator", required=false)
	private String schemaDesignator;
	
	@Attribute(name="codingSchemeVersion", required=false)
	private String schemaVersion;
	
	@Override
	public String getCodeValue() {
		return codeValue;
	}

	public void setCodeValue(String codeValue) {
		this.codeValue = codeValue;
	}

	@Override
	public String getCodeMeaning() {
		return codeMeaning;
	}

	public void setCodeMeaning(String codeMeaning) {
		this.codeMeaning = codeMeaning;
	}

	@Override
	public String getSchemaDesignator() {
		return schemaDesignator;
	}

	public void setSchemaDesignator(String schemaDesignator) {
		this.schemaDesignator = schemaDesignator;
	}

	@Override
	public String getSchemaVersion() {
		return schemaVersion;
	}

	public void setSchemaVersion(String schemaVersion) {
		this.schemaVersion = schemaVersion;
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result
				+ ((codeMeaning == null) ? 0 : codeMeaning.hashCode());
		result = prime * result
				+ ((codeValue == null) ? 0 : codeValue.hashCode());
		result = prime
				* result
				+ ((schemaDesignator == null) ? 0 : schemaDesignator.hashCode());
		result = prime * result
				+ ((schemaVersion == null) ? 0 : schemaVersion.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (!(obj instanceof LexiconTermAttributes))
			return false;
		LexiconTermAttributes other = (LexiconTermAttributes) obj;
		if (codeMeaning == null) {
			if (other.getCodeMeaning() != null)
				return false;
		} else if (!codeMeaning.equals(other.getCodeMeaning()))
			return false;
		if (codeValue == null) {
			if (other.getCodeValue() != null)
				return false;
		} else if (!codeValue.equals(other.getCodeValue()))
			return false;
		if (schemaDesignator == null) {
			if (other.getSchemaDesignator() != null)
				return false;
		} else if (!schemaDesignator.equals(other.getSchemaDesignator()))
			return false;
		if (schemaVersion == null) {
			if (other.getSchemaVersion() != null)
				return false;
		} else if (!schemaVersion.equals(other.getSchemaVersion()))
			return false;
		return true;
	}

	@Override
	public String toString() {
		return "Coded Term: " + codeMeaning;
	}
	
}
