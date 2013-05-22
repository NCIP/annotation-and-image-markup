/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */

#include "dcmtk/dcmsr/dsrtypes.h"
#include "dcmtk/dcmsr/dsrimgtn.h"
#include "dcmtk/dcmsr/dsrxmld.h"


DSRImageTreeNode::DSRImageTreeNode(const E_RelationshipType relationshipType)
  : DSRDocumentTreeNode(relationshipType, VT_Image),
    DSRImageReferenceValue()
{
}


DSRImageTreeNode::~DSRImageTreeNode()
{
}


void DSRImageTreeNode::clear()
{
    DSRDocumentTreeNode::clear();
    DSRImageReferenceValue::clear();
}


OFBool DSRImageTreeNode::isValid() const
{
    return DSRDocumentTreeNode::isValid() && DSRImageReferenceValue::isValid();
}


OFBool DSRImageTreeNode::isShort(const size_t flags) const
{
    return DSRImageReferenceValue::isShort(flags);
}


OFCondition DSRImageTreeNode::print(STD_NAMESPACE ostream &stream,
                                    const size_t flags) const
{
    OFCondition result = DSRDocumentTreeNode::print(stream, flags);
    if (result.good())
    {
        DCMSR_PRINT_ANSI_ESCAPE_CODE(DCMSR_ANSI_ESCAPE_CODE_DELIMITER)
        stream << "=";
        DCMSR_PRINT_ANSI_ESCAPE_CODE(DCMSR_ANSI_ESCAPE_CODE_ITEM_VALUE)
        result = DSRImageReferenceValue::print(stream, flags);
    }
    return result;
}


OFCondition DSRImageTreeNode::writeXML(STD_NAMESPACE ostream &stream,
                                       const size_t flags) const
{
    OFCondition result = EC_Normal;
    writeXMLItemStart(stream, flags);
    result = DSRDocumentTreeNode::writeXML(stream, flags);
    stream << "<value>" << OFendl;
    DSRImageReferenceValue::writeXML(stream, flags);
    stream << "</value>" << OFendl;
    writeXMLItemEnd(stream, flags);
    return result;
}


OFCondition DSRImageTreeNode::readContentItem(DcmItem &dataset)
{
    /* read ReferencedSOPSequence */
    return DSRImageReferenceValue::readSequence(dataset, "1" /*type*/);
}


OFCondition DSRImageTreeNode::writeContentItem(DcmItem &dataset) const
{
    /* write ReferencedSOPSequence */
    return DSRImageReferenceValue::writeSequence(dataset);
}


OFCondition DSRImageTreeNode::readXMLContentItem(const DSRXMLDocument &doc,
                                                 DSRXMLCursor cursor)
{
    /* retrieve value from XML element "value" */
    return DSRImageReferenceValue::readXML(doc, doc.getNamedNode(cursor.gotoChild(), "value"));
}


OFCondition DSRImageTreeNode::renderHTMLContentItem(STD_NAMESPACE ostream &docStream,
                                                    STD_NAMESPACE ostream &annexStream,
                                                    const size_t /*nestingLevel*/,
                                                    size_t &annexNumber,
                                                    const size_t flags) const
{
    /* render ConceptName */
    OFCondition result = renderHTMLConceptName(docStream, flags);
    /* render Reference */
    if (result.good())
    {
        result = DSRImageReferenceValue::renderHTML(docStream, annexStream, annexNumber, flags);
        docStream << OFendl;
    }
    return result;
}
