/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.domain.template;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.List;

import javax.validation.Valid;

import org.simpleframework.xml.Attribute;
import org.simpleframework.xml.ElementList;
import org.simpleframework.xml.Root;
import org.simpleframework.xml.core.Commit;

/**
 * @author Vitaliy Semeshko
 */

@Root(name="ImagingObservation", strict=false)
public class ImagingObservation extends AbstractRemovableElement {

	@Attribute
	private boolean annotatorConfidence;

	@Valid
	@ElementList(name="ImagingObservationCharacteristic", inline=true, required=false)
	private List<ImagingObservationCharacteristic> characteristics;
	
	@SuppressWarnings("unused")
	@Commit
	private void afterPropertiesSet() {
		if (characteristics != null) {
			for (ImagingObservationCharacteristic characteristic : characteristics) {
				characteristic.initRemoveCommand(characteristics);
				characteristic.initContext(characteristics);
			}
		}
	}
	
	public boolean isAnnotatorConfidence() {
		return annotatorConfidence;
	}

	public void setAnnotatorConfidence(boolean annotatorConfidence) {
		this.annotatorConfidence = annotatorConfidence;
	}

	public Collection<ImagingObservationCharacteristic> getCharacteristics() {
		if (characteristics == null) {
			return Collections.emptyList();
		}
		return characteristics;
	}

	public void addCharacteristic(ImagingObservationCharacteristic characteristic) {
		if (characteristics == null) {
			characteristics = new ArrayList<ImagingObservationCharacteristic>();
		}
		characteristics.add(characteristic);
		characteristic.initRemoveCommand(characteristics);
		characteristic.initContext(characteristics);
	}

	@Override
	public String toString() {
		return "Imaging Observation";
	}
	
}
