/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.domain.template;

import org.simpleframework.xml.Attribute;

/**
 * @author Vitaliy Semeshko
 */
public class Quantile extends AbstractRemovableElement {

	@Attribute(required=false)
	private int bins;

	public int getBins() {
		return bins;
	}

	public void setBins(int bins) {
		this.bins = bins;
	}
	
	@Override
	public String toString() {
		return "Quantile: " + bins;
	}
	
}
