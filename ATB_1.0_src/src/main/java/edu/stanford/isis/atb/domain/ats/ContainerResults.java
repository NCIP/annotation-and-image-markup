/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.domain.ats;

import java.util.List;

import org.simpleframework.xml.ElementList;
import org.simpleframework.xml.Root;

/**
 * @author Vitaliy Semeshko
 */

@Root(name="results", strict=false)
public class ContainerResults {

	@ElementList(name="result", inline=true, required=false)
	private List<ContainerSingleResult> containers;

	public List<ContainerSingleResult> getContainers() {
		return containers;
	}
	
}
