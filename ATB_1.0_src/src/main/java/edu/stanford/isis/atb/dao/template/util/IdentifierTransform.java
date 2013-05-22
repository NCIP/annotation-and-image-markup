/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.dao.template.util;

import org.simpleframework.xml.transform.Transform;

import edu.stanford.isis.atb.domain.template.Identifier;

/**
 * Transform for {@link Identifier} during regular read/write.
 * 
 * @author Vitaliy Semeshko
 */
public class IdentifierTransform implements Transform<Identifier> {

	public synchronized Identifier read(String text) throws Exception {      
		return new Identifier(text);
	}

	public synchronized String write(Identifier identifier) throws Exception {
		return identifier.getComposite();
	}

}
