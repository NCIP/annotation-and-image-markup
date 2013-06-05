/*
*  2010 – 2012 Copyright Northwestern University and Stanford University 
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.domain.ats;

/**
 * @author Vitaliy Semeshko
 */
public class TemplateSingleResult extends AbstractSingleResult {

	@Override
	public String toString() {
		return "TemplateSingleResult [uid=" + uid + ", name=" + name
				+ ", author=" + author + ", desc=" + desc + ", disease="
				+ disease + ", bodyPart=" + bodyPart + ", modality=" + modality
				+ "]";
	}

}
