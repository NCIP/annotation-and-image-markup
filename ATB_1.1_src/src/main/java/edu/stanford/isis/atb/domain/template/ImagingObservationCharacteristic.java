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

@Root(name="ImagingObservationCharacteristic", strict=false)
public class ImagingObservationCharacteristic extends ComponentCharacteristic {

	@Attribute
	private boolean annotatorConfidence;
	
	public boolean isAnnotatorConfidence() {
		return annotatorConfidence;
	}

	public void setAnnotatorConfidence(boolean annotatorConfidence) {
		this.annotatorConfidence = annotatorConfidence;
	}

	@Override
	public String toString() {
		return "Imaging Observation Characteristic: " + getLabel();
	}
	
}
