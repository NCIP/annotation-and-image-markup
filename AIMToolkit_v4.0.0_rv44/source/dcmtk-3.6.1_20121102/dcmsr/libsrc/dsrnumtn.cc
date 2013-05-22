/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */

#include "dcmtk/dcmsr/dsrtypes.h"
#include "dcmtk/dcmsr/dsrnumtn.h"
#include "dcmtk/dcmsr/dsrxmld.h"


DSRNumTreeNode::DSRNumTreeNode(const E_RelationshipType relationshipType)
 : DSRDocumentTreeNode(relationshipType, VT_Num),
   DSRNumericMeasurementValue()
{
}


DSRNumTreeNode::~DSRNumTreeNode()
{
}


void DSRNumTreeNode::clear()
{
    DSRDocumentTreeNode::clear();
    DSRNumericMeasurementValue::clear();
}


OFBool DSRNumTreeNode::isValid() const
{
    /* ConceptNameCodeSequence required */
    return DSRDocumentTreeNode::isValid() && DSRNumericMeasurementValue::isValid() && getConceptName().isValid();
}


OFCondition DSRNumTreeNode::print(STD_NAMESPACE ostream &stream,
                                  const size_t flags) const
{
    OFCondition result = DSRDocumentTreeNode::print(stream, flags);
    if (result.good())
    {
        DCMSR_PRINT_ANSI_ESCAPE_CODE(DCMSR_ANSI_ESCAPE_CODE_DELIMITER)
        stream << "=";
        DCMSR_PRINT_ANSI_ESCAPE_CODE(DCMSR_ANSI_ESCAPE_CODE_ITEM_VALUE)
        result = DSRNumericMeasurementValue::print(stream, flags);
    }
    return result;
}


OFCondition DSRNumTreeNode::writeXML(STD_NAMESPACE ostream &stream,
                                     const size_t flags) const
{
    OFCondition result = EC_Normal;
    writeXMLItemStart(stream, flags);
    result = DSRDocumentTreeNode::writeXML(stream, flags);
    DSRNumericMeasurementValue::writeXML(stream, flags);
    writeXMLItemEnd(stream, flags);
    return result;
}


OFCondition DSRNumTreeNode::readContentItem(DcmItem &dataset)
{
    return DSRNumericMeasurementValue::readSequence(dataset);
}


OFCondition DSRNumTreeNode::writeContentItem(DcmItem &dataset) const
{
    return DSRNumericMeasurementValue::writeSequence(dataset);
}


OFCondition DSRNumTreeNode::readXMLContentItem(const DSRXMLDocument &doc,
                                               DSRXMLCursor cursor)
{
    return DSRNumericMeasurementValue::readXML(doc, cursor);
}


OFCondition DSRNumTreeNode::renderHTMLContentItem(STD_NAMESPACE ostream &docStream,
                                                  STD_NAMESPACE ostream &annexStream,
                                                  const size_t /*nestingLevel*/,
                                                  size_t &annexNumber,
                                                  const size_t flags) const
{
    /* render ConceptName */
    OFCondition result = renderHTMLConceptName(docStream, flags);
    /* render Num */
    if (result.good())
    {
        result = DSRNumericMeasurementValue::renderHTML(docStream, annexStream, annexNumber, flags);
        docStream << OFendl;
    }
    return result;
}
