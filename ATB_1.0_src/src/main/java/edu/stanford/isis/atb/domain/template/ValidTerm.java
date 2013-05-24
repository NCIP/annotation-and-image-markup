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
import org.simpleframework.xml.core.Commit;

import edu.stanford.isis.atb.domain.LexiconTermAttributes;

/**
 * @author Vitaliy Semeshko
 */

@Root(name="ValidTerm", strict=false)
public class ValidTerm extends CodedTerm {

	@Valid
	@ElementList(name="ValidTerm", inline=true, required=false)
	private List<ValidTerm> validTerms;
	
	@SuppressWarnings("unused")
	@Commit
	private void afterPropertiesSet() {
		if (validTerms != null) {
			for (ValidTerm validTerm : validTerms) {
				validTerm.initRemoveCommand(validTerms);
				validTerm.initContext(validTerms);
			}
		}
		afterDescendantPropertiesSet();
	}
	
	protected void afterDescendantPropertiesSet() {}
	
	public Collection<ValidTerm> getValidTerms() {
		if (validTerms == null) {
			return Collections.emptyList();
		}
		
		return validTerms;
	}

	public void addValidTerm(ValidTerm validTerm) {
		if (validTerms == null) {
			validTerms = new ArrayList<ValidTerm>();
		}
		
		validTerms.add(validTerm);
		validTerm.initRemoveCommand(validTerms);
		validTerm.initContext(validTerms);
	}
	
	@Override
	public String toString() {
		return "Valid Term: " + StringUtils.trimToEmpty(getCodeMeaning());
	}
	
	public static ValidTerm fromAttributes(LexiconTermAttributes attributes) {
		ValidTerm validTerm = new ValidTerm();
		validTerm.setCodeMeaning(attributes.getCodeMeaning());
		validTerm.setCodeValue(attributes.getCodeValue());
		validTerm.setSchemaDesignator(attributes.getSchemaDesignator());
		validTerm.setSchemaVersion(attributes.getSchemaVersion());
		return validTerm;
	}
	
}
