/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.domain.ats;

/**
 * @author Vitaliy Semeshko
 */
public class ContainerSingleResult extends AbstractSingleResult {

	@Override
	public String toString() {
		return "ContainerSingleResult [uid=" + uid + ", name=" + name
				+ ", author=" + author + ", desc=" + desc + ", disease="
				+ disease + ", bodyPart=" + bodyPart + ", modality=" + modality
				+ "]";
	}

}
