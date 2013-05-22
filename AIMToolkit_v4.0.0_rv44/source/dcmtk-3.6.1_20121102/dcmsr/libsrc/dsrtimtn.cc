/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */

#include "dcmtk/dcmsr/dsrtypes.h"
#include "dcmtk/dcmsr/dsrtimtn.h"
#include "dcmtk/dcmsr/dsrxmld.h"


DSRTimeTreeNode::DSRTimeTreeNode(const E_RelationshipType relationshipType)
  : DSRDocumentTreeNode(relationshipType, VT_Time),
    DSRStringValue()
{
}


DSRTimeTreeNode::DSRTimeTreeNode(const E_RelationshipType relationshipType,
                                 const OFString &timeValue,
                                 const OFBool check)
  : DSRDocumentTreeNode(relationshipType, VT_Time),
    DSRStringValue(timeValue, check)
{
}


DSRTimeTreeNode::~DSRTimeTreeNode()
{
}


void DSRTimeTreeNode::clear()
{
    DSRDocumentTreeNode::clear();
    DSRStringValue::clear();
}


OFBool DSRTimeTreeNode::isValid() const
{
    /* ConceptNameCodeSequence required */
    return DSRDocumentTreeNode::isValid() && getConceptName().isValid() && checkCurrentValue().good();
}


OFCondition DSRTimeTreeNode::print(STD_NAMESPACE ostream &stream,
                                   const size_t flags) const
{
    OFCondition result = DSRDocumentTreeNode::print(stream, flags);
    if (result.good())
    {
        DCMSR_PRINT_ANSI_ESCAPE_CODE(DCMSR_ANSI_ESCAPE_CODE_DELIMITER)
        stream << "=";
        DCMSR_PRINT_ANSI_ESCAPE_CODE(DCMSR_ANSI_ESCAPE_CODE_ITEM_VALUE)
        DSRStringValue::print(stream);
    }
    return result;
}


OFCondition DSRTimeTreeNode::writeXML(STD_NAMESPACE ostream &stream,
                                      const size_t flags) const
{
    OFString tmpString;
    OFCondition result = EC_Normal;
    writeXMLItemStart(stream, flags);
    result = DSRDocumentTreeNode::writeXML(stream, flags);
    /* output time in ISO 8601 format */
    DcmTime::getISOFormattedTimeFromString(getValue(), tmpString);
    writeStringValueToXML(stream, tmpString, "value", (flags & XF_writeEmptyTags) > 0);
    writeXMLItemEnd(stream, flags);
    return result;
}


OFCondition DSRTimeTreeNode::readContentItem(DcmItem &dataset)
{
    /* read Time */
    return DSRStringValue::read(dataset, DCM_Time);
}


OFCondition DSRTimeTreeNode::writeContentItem(DcmItem &dataset) const
{
    /* write Time */
    return DSRStringValue::write(dataset, DCM_Time);
}


OFCondition DSRTimeTreeNode::readXMLContentItem(const DSRXMLDocument &doc,
                                                DSRXMLCursor cursor)
{
    OFString tmpString;
    /* retrieve value from XML element "value" */
    OFCondition result = setValue(getValueFromXMLNodeContent(doc, doc.getNamedNode(cursor.gotoChild(), "value"), tmpString));
    if (result == EC_IllegalParameter)
        result = SR_EC_InvalidValue;
    return result;
}


OFString &DSRTimeTreeNode::getValueFromXMLNodeContent(const DSRXMLDocument &doc,
                                                      DSRXMLCursor cursor,
                                                      OFString &timeValue,
                                                      const OFBool clearString)
{
    if (clearString)
        timeValue.clear();
    /* check whether node is valid */
    if (cursor.valid())
    {
        OFString tmpString;
        /* retrieve value from XML element */
        if (!doc.getStringFromNodeContent(cursor, tmpString).empty())
        {
            OFTime tmpTime;
            /* convert ISO to DICOM format */
            if (tmpTime.setISOFormattedTime(tmpString))
                DcmTime::getDicomTimeFromOFTime(tmpTime, timeValue);
        }
    }
    return timeValue;
}


OFCondition DSRTimeTreeNode::renderHTMLContentItem(STD_NAMESPACE ostream &docStream,
                                                   STD_NAMESPACE ostream & /*annexStream*/,
                                                   const size_t /*nestingLevel*/,
                                                   size_t & /*annexNumber*/,
                                                   const size_t flags) const
{
    /* render ConceptName */
    OFCondition result = renderHTMLConceptName(docStream, flags);
    /* render Time */
    if (result.good())
    {
        OFString htmlString;
        if (!(flags & DSRTypes::HF_renderItemsSeparately))
        {
            if (flags & DSRTypes::HF_XHTML11Compatibility)
                docStream << "<span class=\"time\">";
            else if (flags & DSRTypes::HF_HTML32Compatibility)
                docStream << "<u>";
            else /* HTML 4.01 */
                docStream << "<span class=\"under\">";
        }
        docStream << dicomToReadableTime(getValue(), htmlString);
        if (!(flags & DSRTypes::HF_renderItemsSeparately))
        {
            if (flags & DSRTypes::HF_HTML32Compatibility)
                docStream << "</u>";
            else
                docStream << "</span>";
        }
        docStream << OFendl;
    }
    return result;
}


OFCondition DSRTimeTreeNode::checkValue(const OFString &timeValue) const
{
    /* first, make sure that the mandatory value is non-empty */
    OFCondition result = DSRStringValue::checkValue(timeValue);
    /* then, check whether the passed value is valid */
    if (result.good())
        result = DcmTime::checkStringValue(timeValue, "1");
    return result;
}
