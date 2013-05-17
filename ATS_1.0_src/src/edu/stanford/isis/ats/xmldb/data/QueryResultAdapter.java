/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

package edu.stanford.isis.ats.xmldb.data;

import com.sleepycat.dbxml.XmlValue;

/**
 * @author Vladimir Kleper
 * @param <T>
 */
public interface QueryResultAdapter<T> {

    public T adaptResult(XmlValue value);
}
