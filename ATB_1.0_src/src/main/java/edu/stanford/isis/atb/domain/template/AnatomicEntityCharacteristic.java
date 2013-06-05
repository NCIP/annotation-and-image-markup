/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
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

@Root(name="AnatomicEntityCharacteristic", strict=false)
public class AnatomicEntityCharacteristic extends ComponentCharacteristic {

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
		return "Anatomic Entity Characteristic: " + getLabel();
	}
	
}
