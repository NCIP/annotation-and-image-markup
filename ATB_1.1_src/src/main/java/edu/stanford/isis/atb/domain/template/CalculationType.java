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

/**
 * @author Vitaliy Semeshko
 */

@Root(name="CalculationType", strict=false)
public class CalculationType extends ValidTerm {

	@Valid
	@ElementList(name="AlgorithmType", inline=true, required=false)
	private List<AlgorithmType> algorithmTypes;
	
	@Override
	protected void afterDescendantPropertiesSet() {
		if (algorithmTypes != null) {
			for (AlgorithmType algorithmType : algorithmTypes) {
				algorithmType.initRemoveCommand(algorithmTypes);
			}
		}
	}
	
	public Collection<AlgorithmType> getAlgorithmTypes() {
		if (algorithmTypes == null) {
			return Collections.emptyList();
		}
		return algorithmTypes;
	}

	public void addAlgorithmType(AlgorithmType algorithmType) {
		if (algorithmTypes == null) {
			algorithmTypes = new ArrayList<AlgorithmType>();
		}
		algorithmTypes.add(algorithmType);
		algorithmType.initRemoveCommand(algorithmTypes);
	}

	@Override
	public String toString() {
		return "CalculationType: " + StringUtils.trimToEmpty(getCodeMeaning());
	}
	
}
