package edu.stanford.isis.ats.xmldb;

import com.sleepycat.dbxml.XmlException;
import com.sleepycat.dbxml.XmlResults;
import com.sleepycat.dbxml.XmlValue;

import edu.stanford.isis.ats.utils.ATSLogger;

/**
 * 
 * @author Vladimir Kleper
 *
 */
public class DbUtils {
    public static String getAttributeValue(XmlValue node, String attributeLocalName) throws XmlException {
        if (node == null || attributeLocalName == null)
            return null;
        
        try {
            if (!node.isNode() || node.getNodeType() != XmlValue.ELEMENT_NODE)
                return null;
            
            XmlResults attribs = node.getAttributes();
            while(attribs.hasNext()) {
                XmlValue attrib = attribs.next();
                if (attrib.getNodeType() == XmlValue.ATTRIBUTE_NODE) {
                    if (attrib.getLocalName().equals(attributeLocalName))
                        return attrib.getNodeValue();
                }
            }
            
        } catch (Exception e) {
            ATSLogger.getLogger().error("(DU-30): Failed to get attribute[" + attributeLocalName + "]", e);
        }
        return null;
    }
}
