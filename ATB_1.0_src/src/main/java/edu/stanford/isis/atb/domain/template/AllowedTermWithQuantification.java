/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.domain.template;

import javax.validation.Valid;

import org.apache.commons.lang3.StringUtils;
import org.simpleframework.xml.Element;
import org.simpleframework.xml.Root;

import edu.stanford.isis.atb.domain.LexiconTermAttributes;

/**
 * @author Vitaliy Semeshko
 */

@Root(name="AllowedTerm", strict=false)
public class AllowedTermWithQuantification extends ValidTerm {

	@Valid
	@Element(name="CharacteristicQuantification", required=false)
	private CharacteristicQuantification characteristicQuantification;
	
	@Override
	protected void afterDescendantPropertiesSet() {
		if (characteristicQuantification != null) {
			characteristicQuantification.setRemoveCommand(new RemoveCommand() {
				@Override
				public void execute() {
					characteristicQuantification = null;
				}
			});
		}
	}
	
	public CharacteristicQuantification getCharacteristicQuantification() {
		return characteristicQuantification;
	}
	
	public void setCharacteristicQuantification(CharacteristicQuantification characteristicQuantification) {
		this.characteristicQuantification = characteristicQuantification;
		if (characteristicQuantification != null) {
			characteristicQuantification.setRemoveCommand(new RemoveCommand() {
				@Override
				public void execute() {
					AllowedTermWithQuantification.this.characteristicQuantification = null;
				}
			});
		}		
	}
	
	@Override
	public String toString() {
		return "Allowed Term: " + StringUtils.trimToEmpty(getCodeMeaning());
	}
	
	public static AllowedTermWithQuantification fromAttributes(LexiconTermAttributes attributes) {
		AllowedTermWithQuantification allowedTerm = new AllowedTermWithQuantification();
		allowedTerm.setCodeMeaning(attributes.getCodeMeaning());
		allowedTerm.setCodeValue(attributes.getCodeValue());
		allowedTerm.setSchemaDesignator(attributes.getSchemaDesignator());
		allowedTerm.setSchemaVersion(attributes.getSchemaVersion());
		return allowedTerm;
	}
	
}
