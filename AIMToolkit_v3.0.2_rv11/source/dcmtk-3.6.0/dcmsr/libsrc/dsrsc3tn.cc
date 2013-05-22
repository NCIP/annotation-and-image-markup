/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */

#include "dcmtk/dcmsr/dsrtypes.h"
#include "dcmtk/dcmsr/dsrsc3tn.h"
#include "dcmtk/dcmsr/dsrxmld.h"


DSRSCoord3DTreeNode::DSRSCoord3DTreeNode(const E_RelationshipType relationshipType)
 : DSRDocumentTreeNode(relationshipType, VT_SCoord3D),
   DSRSpatialCoordinates3DValue()
{
}


DSRSCoord3DTreeNode::~DSRSCoord3DTreeNode()
{
}


void DSRSCoord3DTreeNode::clear()
{
    DSRDocumentTreeNode::clear();
    DSRSpatialCoordinates3DValue::clear();
}


OFBool DSRSCoord3DTreeNode::isValid() const
{
    return DSRDocumentTreeNode::isValid() && DSRSpatialCoordinates3DValue::isValid();
}


OFBool DSRSCoord3DTreeNode::isShort(const size_t flags) const
{
    return DSRSpatialCoordinates3DValue::isShort(flags);
}


OFCondition DSRSCoord3DTreeNode::print(STD_NAMESPACE ostream &stream,
                                       const size_t flags) const
{
    OFCondition result = DSRDocumentTreeNode::print(stream, flags);
    if (result.good())
    {
        stream << "=";
        result = DSRSpatialCoordinates3DValue::print(stream, flags);
    }
    return result;
}


OFCondition DSRSCoord3DTreeNode::writeXML(STD_NAMESPACE ostream &stream,
                                          const size_t flags) const
{
    OFCondition result = EC_Normal;
    writeXMLItemStart(stream, flags, OFFalse /*closingBracket*/);
    stream << " type=\"" << graphicType3DToEnumeratedValue(getGraphicType()) << "\"";
    stream << ">" << OFendl;
    result = DSRDocumentTreeNode::writeXML(stream, flags);
    DSRSpatialCoordinates3DValue::writeXML(stream, flags);
    writeXMLItemEnd(stream, flags);
    return result;
}


OFCondition DSRSCoord3DTreeNode::readContentItem(DcmItem &dataset)
{
    /* read SpatialCoordinates */
    return DSRSpatialCoordinates3DValue::read(dataset);
}


OFCondition DSRSCoord3DTreeNode::writeContentItem(DcmItem &dataset) const
{
    /* write SpatialCoordinates */
    return DSRSpatialCoordinates3DValue::write(dataset);
}


OFCondition DSRSCoord3DTreeNode::readXMLContentItem(const DSRXMLDocument &doc,
                                                    DSRXMLCursor cursor)
{
    OFCondition result = SR_EC_CorruptedXMLStructure;
    if (cursor.valid())
    {
        OFString tmpString;
        /* read 'type' and check validity */
        result = setGraphicType(enumeratedValueToGraphicType3D(doc.getStringFromAttribute(cursor, tmpString, "type")));
        if (result.good())
        {
            /* proceed reading the spatial coordinates */
            result = DSRSpatialCoordinates3DValue::readXML(doc, cursor);
        } else
            printUnknownValueWarningMessage("SCOORD3D type", tmpString.c_str());
    }
    return result;
}


OFCondition DSRSCoord3DTreeNode::renderHTMLContentItem(STD_NAMESPACE ostream &docStream,
                                                       STD_NAMESPACE ostream &annexStream,
                                                       const size_t /*nestingLevel*/,
                                                       size_t &annexNumber,
                                                       const size_t flags) const
{
    /* render ConceptName */
    OFCondition result = renderHTMLConceptName(docStream, flags);
    /* render SpatialCoordinates */
    if (result.good())
    {
        result = DSRSpatialCoordinates3DValue::renderHTML(docStream, annexStream, annexNumber, flags);
        docStream << OFendl;
    }
    return result;
}


/*
 *  CVS/RCS Log:
 *  $Log: dsrsc3tn.cc,v $
 *  Revision 1.2  2010-10-14 13:14:41  joergr
 *  Updated copyright header. Added reference to COPYRIGHT file.
 *
 *  Revision 1.1  2010-09-28 14:07:29  joergr
 *  Added support for Colon CAD SR which requires a new value type (SCOORD3D).
 *
 *
 */
