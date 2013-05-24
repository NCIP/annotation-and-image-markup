/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
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

import org.apache.commons.lang3.StringUtils;
import org.simpleframework.xml.ElementList;
import org.simpleframework.xml.Root;

import edu.stanford.isis.atb.domain.LexiconTermAttributes;

/**
 * @author Vitaliy Semeshko
 */

@Root(name="AllowedTerm", strict=false)
public class AllowedTerm extends ValidTerm {

	@Valid
	@ElementList(name="NonQuantifiable", inline=true, required=false)
	private List<NonQuantifiable> nonQuantifiables;
	
	@Override
	protected void afterDescendantPropertiesSet() {
		if (nonQuantifiables != null) {
			for (final NonQuantifiable nonQuantifiable : nonQuantifiables) {
				nonQuantifiable.initRemoveCommand(nonQuantifiables);
			}
		}
	}
	
	public Collection<NonQuantifiable> getNonQuantifiables() {
		if (nonQuantifiables == null) {
			return Collections.emptyList();
		}
		
		return nonQuantifiables;
	}
	
	public void addNonQuantifiable(NonQuantifiable nonQuantifiable) {
		if (nonQuantifiables == null) {
			nonQuantifiables = new ArrayList<NonQuantifiable>();
		}
		
		nonQuantifiables.add(nonQuantifiable);
		nonQuantifiable.initRemoveCommand(nonQuantifiables);
	}
	
	@Override
	public String toString() {
		return "Allowed Term: " + StringUtils.trimToEmpty(getCodeMeaning());
	}
	
	public static AllowedTerm fromAttributes(LexiconTermAttributes attributes) {
		AllowedTerm allowedTerm = new AllowedTerm();
		allowedTerm.setCodeMeaning(attributes.getCodeMeaning());
		allowedTerm.setCodeValue(attributes.getCodeValue());
		allowedTerm.setSchemaDesignator(attributes.getSchemaDesignator());
		allowedTerm.setSchemaVersion(attributes.getSchemaVersion());
		return allowedTerm;
	}
	
}
