/*L
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

import org.hibernate.validator.constraints.NotEmpty;
import org.simpleframework.xml.ElementList;
import org.simpleframework.xml.core.Commit;

/**
 * @author Vitaliy Semeshko
 */
public class Calculation extends AbstractRemovableElement {

	@Valid
	@NotEmpty(message = "{calculation.calculationTypes.notEmpty}")
	@ElementList(name="CalculationType", inline=true, required=false)
	private List<CalculationType> calculationTypes;
	
	@SuppressWarnings("unused")
	@Commit
	private void afterPropertiesSet() {
		if (calculationTypes != null) {
			for (CalculationType calculationType : calculationTypes) {
				calculationType.initRemoveCommand(calculationTypes);
			}
		}
	}
	
	public Collection<CalculationType> getCalculationType() {
		if (calculationTypes == null) {
			return Collections.emptyList();
		}
		return calculationTypes;
	}

	public void addCalculationType(CalculationType calculationType) {
		if (calculationTypes == null) {
			calculationTypes = new ArrayList<CalculationType>();
		}
		calculationTypes.add(calculationType);
		calculationType.initRemoveCommand(calculationTypes);
	}

	@Override
	public String toString() {
		return "Calculation";
	}
	
}
