/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */

#include "dcmtk/dcmsr/dsrimpcc.h"


DSRImplantationPlanSRDocumentConstraintChecker::DSRImplantationPlanSRDocumentConstraintChecker()
  : DSRIODConstraintChecker()
{
}


DSRImplantationPlanSRDocumentConstraintChecker::~DSRImplantationPlanSRDocumentConstraintChecker()
{
}


OFBool DSRImplantationPlanSRDocumentConstraintChecker::isByReferenceAllowed() const
{
    return OFFalse;
}


OFBool DSRImplantationPlanSRDocumentConstraintChecker::isTemplateSupportRequired() const
{
    return OFTrue;
}


const char *DSRImplantationPlanSRDocumentConstraintChecker::getRootTemplateIdentifier() const
{
    return "7000";
}


DSRTypes::E_DocumentType DSRImplantationPlanSRDocumentConstraintChecker::getDocumentType() const
{
    return DT_ImplantationPlanSRDocument;
}


OFBool DSRImplantationPlanSRDocumentConstraintChecker::checkContentRelationship(const E_ValueType sourceValueType,
                                                                                const E_RelationshipType relationshipType,
                                                                                const E_ValueType targetValueType,
                                                                                const OFBool byReference) const
{
    /* the following code implements the constraints of table A.35.Y-2 in DICOM PS3.3 (Supplement 134) */
    OFBool result = OFFalse;
    /* by-reference relationships not allowed at all */
    if (!byReference)
    {
        /* row 1 of the table */
        if ((relationshipType == RT_contains) && (sourceValueType == VT_Container))
        {
            result = (targetValueType == VT_Text) || (targetValueType == VT_Code) || (targetValueType == VT_Num) ||
                     (targetValueType == VT_UIDRef) || (targetValueType == VT_Composite) || (targetValueType == VT_Image) ||
                     (targetValueType == VT_Container);
        }
        /* row 2 of the table */
        else if ((relationshipType == RT_hasObsContext) && (sourceValueType == VT_Container))
        {
            result = (targetValueType == VT_Text) || (targetValueType == VT_Code) || (targetValueType == VT_Num) ||
                     (targetValueType == VT_Date) || (targetValueType == VT_UIDRef) || (targetValueType == VT_PName) ||
                     (targetValueType == VT_Composite);
        }
        /* row 3 of the table */
        else if (relationshipType == RT_hasConceptMod)
        {
            result = (targetValueType == VT_Text) || (targetValueType == VT_Code);
        }
        /* row 4 of the table */
        else if ((relationshipType == RT_hasProperties) &&
            ((sourceValueType == VT_Text) || (sourceValueType == VT_Code) || (sourceValueType == VT_Num) ||
            (sourceValueType == VT_Image) || (sourceValueType == VT_UIDRef) || (sourceValueType == VT_Composite)))
        {
            result = (targetValueType == VT_Composite);
        }
    }
    return result;
}


/*
 *  CVS/RCS Log:
 *  $Log: dsrimpcc.cc,v $
 *  Revision 1.1  2010-11-05 11:06:57  joergr
 *  Added support for new Implantation Plan SR Document Storage SOP Class.
 *
 *
 *
 */
