/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */

#include "dcmtk/dcmsr/dsrkeycc.h"


DSRKeyObjectSelectionDocumentConstraintChecker::DSRKeyObjectSelectionDocumentConstraintChecker()
  : DSRIODConstraintChecker()
{
}


DSRKeyObjectSelectionDocumentConstraintChecker::~DSRKeyObjectSelectionDocumentConstraintChecker()
{
}


OFBool DSRKeyObjectSelectionDocumentConstraintChecker::isByReferenceAllowed() const
{
    return OFFalse;
}


OFBool DSRKeyObjectSelectionDocumentConstraintChecker::isTemplateSupportRequired() const
{
    return OFTrue;
}


const char *DSRKeyObjectSelectionDocumentConstraintChecker::getRootTemplateIdentifier() const
{
    return "2010";
}


DSRTypes::E_DocumentType DSRKeyObjectSelectionDocumentConstraintChecker::getDocumentType() const
{
    return DT_KeyObjectSelectionDocument;
}


OFBool DSRKeyObjectSelectionDocumentConstraintChecker::checkContentRelationship(const E_ValueType sourceValueType,
                                                                                const E_RelationshipType relationshipType,
                                                                                const E_ValueType targetValueType,
                                                                                const OFBool byReference) const
{
    /* the following code implements the constraints of table A.35.4-2 in DICOM PS3.3 */
    OFBool result = OFFalse;
    /* by-reference relationships not allowed at all */
    if (!byReference)
    {
        /* row 1 of the table */
        if ((relationshipType == RT_contains) && (sourceValueType == VT_Container))
        {
            result = (targetValueType == VT_Text) || (targetValueType == VT_Image) ||
                     (targetValueType == VT_Waveform) || (targetValueType == VT_Composite);
        }
        /* row 2 of the table */
        else if ((relationshipType == RT_hasObsContext) && (sourceValueType == VT_Container))
        {
            result = (targetValueType == VT_Text) || (targetValueType == VT_Code) ||
                     (targetValueType == VT_UIDRef) || (targetValueType == VT_PName);
        }
        /* row 3 of the table */
        else if ((relationshipType == RT_hasConceptMod) && (sourceValueType == VT_Container))
        {
            result = (targetValueType == VT_Code);
        }
    }
    return result;
}


/*
 *  CVS/RCS Log:
 *  $Log: dsrkeycc.cc,v $
 *  Revision 1.5  2010-10-14 13:14:41  joergr
 *  Updated copyright header. Added reference to COPYRIGHT file.
 *
 *  Revision 1.4  2010-09-30 08:57:45  joergr
 *  Renamed class and enumeration related to the Key Object Selection Document.
 *
 *  Revision 1.3  2005-12-08 15:47:57  meichel
 *  Changed include path schema for all DCMTK header files
 *
 *  Revision 1.2  2003/10/09 13:00:41  joergr
 *  Added check for root template identifier when reading an SR document.
 *
 *  Revision 1.1  2003/09/15 14:16:50  joergr
 *  Introduced new class to facilitate checking of SR IOD relationship content
 *  constraints. Replaced old implementation distributed over numerous classes.
 *
 */
