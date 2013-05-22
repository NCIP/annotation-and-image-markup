/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.domain.template;

import org.apache.commons.lang3.StringUtils;
import org.hibernate.validator.constraints.NotEmpty;
import org.simpleframework.xml.Attribute;
import org.simpleframework.xml.Root;

/**
 * @author Vitaliy Semeshko
 */

@Root(name="AlgorithmType", strict=false)
public class AlgorithmType extends CodedTerm {

	@NotEmpty(message = "{algorithmType.description.notEmpty}")
	@Attribute(required=false)
	private String description;
	
	@Attribute(required=false)
	private String uniqueIdentifier;
	
	@Attribute(required=false)
	private String algorithmName;
	
	@Attribute(required=false)
	private String algorithmVersion;
	
	@Attribute(required=false)
	private String mathML;

	public String getDescription() {
		return description;
	}

	public void setDescription(String description) {
		this.description = description;
	}

	public String getUniqueIdentifier() {
		return uniqueIdentifier;
	}

	public void setUniqueIdentifier(String uniqueIdentifier) {
		this.uniqueIdentifier = uniqueIdentifier;
	}

	public String getAlgorithmName() {
		return algorithmName;
	}

	public void setAlgorithmName(String algorithmName) {
		this.algorithmName = algorithmName;
	}

	public String getAlgorithmVersion() {
		return algorithmVersion;
	}

	public void setAlgorithmVersion(String algorithmVersion) {
		this.algorithmVersion = algorithmVersion;
	}

	public String getMathML() {
		return mathML;
	}

	public void setMathML(String mathML) {
		this.mathML = mathML;
	}

	@Override
	public String toString() {
		return "Algorithm Type: " + StringUtils.trimToEmpty(algorithmName);
	}
	
}
