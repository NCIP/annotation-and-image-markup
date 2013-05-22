/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */

#include "dcmtk/dcmsr/dsrtypes.h"
#include "dcmtk/dcmsr/dsrwavtn.h"
#include "dcmtk/dcmsr/dsrxmld.h"


DSRWaveformTreeNode::DSRWaveformTreeNode(const E_RelationshipType relationshipType)
 : DSRDocumentTreeNode(relationshipType, VT_Waveform),
   DSRWaveformReferenceValue()
{
}


DSRWaveformTreeNode::~DSRWaveformTreeNode()
{
}


void DSRWaveformTreeNode::clear()
{
    DSRDocumentTreeNode::clear();
    DSRWaveformReferenceValue::clear();
}


OFBool DSRWaveformTreeNode::isValid() const
{
    return DSRDocumentTreeNode::isValid() && DSRWaveformReferenceValue::isValid();
}


OFBool DSRWaveformTreeNode::isShort(const size_t flags) const
{
    return DSRWaveformReferenceValue::isShort(flags);
}


OFCondition DSRWaveformTreeNode::print(STD_NAMESPACE ostream &stream,
                                       const size_t flags) const
{
    OFCondition result = DSRDocumentTreeNode::print(stream, flags);
    if (result.good())
    {
        DCMSR_PRINT_ANSI_ESCAPE_CODE(DCMSR_ANSI_ESCAPE_CODE_DELIMITER)
        stream << "=";
        DCMSR_PRINT_ANSI_ESCAPE_CODE(DCMSR_ANSI_ESCAPE_CODE_ITEM_VALUE)
        result = DSRWaveformReferenceValue::print(stream, flags);
    }
    return result;
}


OFCondition DSRWaveformTreeNode::writeXML(STD_NAMESPACE ostream &stream,
                                          const size_t flags) const
{
    OFCondition result = EC_Normal;
    writeXMLItemStart(stream, flags);
    result = DSRDocumentTreeNode::writeXML(stream, flags);
    stream << "<value>" << OFendl;
    DSRWaveformReferenceValue::writeXML(stream, flags);
    stream << "</value>" << OFendl;
    writeXMLItemEnd(stream, flags);
    return result;
}


OFCondition DSRWaveformTreeNode::readContentItem(DcmItem &dataset)
{
    /* read ReferencedSOPSequence */
    return DSRWaveformReferenceValue::readSequence(dataset, "1" /*type*/);
}


OFCondition DSRWaveformTreeNode::writeContentItem(DcmItem &dataset) const
{
    /* write ReferencedSOPSequence */
    return DSRWaveformReferenceValue::writeSequence(dataset);
}


OFCondition DSRWaveformTreeNode::readXMLContentItem(const DSRXMLDocument &doc,
                                                    DSRXMLCursor cursor)
{
    /* retrieve value from XML element "value" */
    return DSRWaveformReferenceValue::readXML(doc, doc.getNamedNode(cursor.gotoChild(), "value"));
}


OFCondition DSRWaveformTreeNode::renderHTMLContentItem(STD_NAMESPACE ostream &docStream,
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
        result = DSRWaveformReferenceValue::renderHTML(docStream, annexStream, annexNumber, flags);
        docStream << OFendl;
    }
    return result;
}
