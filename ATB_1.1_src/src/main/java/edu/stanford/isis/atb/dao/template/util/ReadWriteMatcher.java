/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.dao.template.util;

import java.util.Date;

import org.simpleframework.xml.transform.Matcher;
import org.simpleframework.xml.transform.Transform;

import edu.stanford.isis.atb.domain.template.Identifier;

/**
 * Matcher is used during regular read/write.
 * 
 * @author Vitaliy Semeshko
 */
public class ReadWriteMatcher implements Matcher {

	@SuppressWarnings("rawtypes")
	@Override
    public Transform match(Class type) throws Exception {
        if (type == null) {
            return null;
        } else if (type == Date.class) {
            return new ShortFormatDateTransform();
        } else if (type == Identifier.class) {
        	return new IdentifierTransform();
        }
        return null;
    }

}
