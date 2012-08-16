package edu.stanford.isis.ats.xmldb.data;

import com.sleepycat.dbxml.XmlValue;

/**
 * @author Vladimir Kleper
 * @param <T>
 */
public interface QueryResultAdapter<T> {

    public T adaptResult(XmlValue value);
}
