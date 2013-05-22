/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */

#include "dcmtk/dcmsr/dsrbascc.h"


DSRBasicTextSRConstraintChecker::DSRBasicTextSRConstraintChecker()
  : DSRIODConstraintChecker()
{
}


DSRBasicTextSRConstraintChecker::~DSRBasicTextSRConstraintChecker()
{
}


OFBool DSRBasicTextSRConstraintChecker::isByReferenceAllowed() const
{
    return OFFalse;
}


OFBool DSRBasicTextSRConstraintChecker::isTemplateSupportRequired() const
{
    return OFFalse;
}


const char *DSRBasicTextSRConstraintChecker::getRootTemplateIdentifier() const
{
    return NULL;
}


DSRTypes::E_DocumentType DSRBasicTextSRConstraintChecker::getDocumentType() const
{
    return DT_BasicTextSR;
}


OFBool DSRBasicTextSRConstraintChecker::checkContentRelationship(const E_ValueType sourceValueType,
                                                                 const E_RelationshipType relationshipType,
                                                                 const E_ValueType targetValueType,
                                                                 const OFBool byReference) const
{
    /* the following code implements the constraints of table A.35.1-2 in DICOM PS3.3 */
    OFBool result = OFFalse;
    /* by-reference relationships not allowed at all */
    if (!byReference)
    {
        /* row 1 of the table */
        if ((relationshipType == RT_contains) && (sourceValueType == VT_Container))
        {
            result = (targetValueType == VT_Text)     || (targetValueType == VT_Code)      || (targetValueType == VT_DateTime) ||
                     (targetValueType == VT_Date)     || (targetValueType == VT_Time)      || (targetValueType == VT_UIDRef)   ||
                     (targetValueType == VT_PName)    || (targetValueType == VT_Composite) || (targetValueType == VT_Image)    ||
                     (targetValueType == VT_Waveform) || (targetValueType == VT_Container);
        }
        /* row 2 of the table */
        else if ((relationshipType == RT_hasObsContext) && (sourceValueType == VT_Container))
        {
            result = (targetValueType == VT_Text)  || (targetValueType == VT_Code) || (targetValueType == VT_DateTime) ||
                     (targetValueType == VT_Date)  || (targetValueType == VT_Time) || (targetValueType == VT_UIDRef)   ||
                     (targetValueType == VT_PName) || (targetValueType == VT_Composite);
        }
        /* row 3 of the table */
        else if ((relationshipType == RT_hasAcqContext) && ((sourceValueType == VT_Container) ||
            (sourceValueType == VT_Image) || (sourceValueType == VT_Waveform) || (sourceValueType == VT_Composite)))
        {
            result = (targetValueType == VT_Text) || (targetValueType == VT_Code) || (targetValueType == VT_DateTime) ||
                     (targetValueType == VT_Date) || (targetValueType == VT_Time) || (targetValueType == VT_UIDRef)   ||
                     (targetValueType == VT_PName);
        }
        /* row 4 of the table */
        else if (relationshipType == RT_hasConceptMod)
        {
            result = (targetValueType == VT_Text) || (targetValueType == VT_Code);
        }
        /* row 5 and 6 of the table */
        else if (((relationshipType == RT_hasProperties) || (relationshipType == RT_inferredFrom)) &&
            (sourceValueType == VT_Text))
        {
            result = (targetValueType == VT_Text)  || (targetValueType == VT_Code)      || (targetValueType == VT_DateTime) ||
                     (targetValueType == VT_Date)  || (targetValueType == VT_Time)      || (targetValueType == VT_UIDRef)   ||
                     (targetValueType == VT_PName) || (targetValueType == VT_Composite) || (targetValueType == VT_Image)    ||
                     (targetValueType == VT_Waveform);
        }
    }
    return result;
}


/*
 *  CVS/RCS Log:
 *  $Log: dsrbascc.cc,v $
 *  Revision 1.4  2010-10-14 13:14:40  joergr
 *  Updated copyright header. Added reference to COPYRIGHT file.
 *
 *  Revision 1.3  2005-12-08 15:47:37  meichel
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
