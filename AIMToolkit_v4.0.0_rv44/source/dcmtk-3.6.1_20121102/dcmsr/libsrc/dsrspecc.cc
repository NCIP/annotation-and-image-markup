/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */

#include "dcmtk/dcmsr/dsrspecc.h"


DSRSpectaclePrescriptionReportConstraintChecker::DSRSpectaclePrescriptionReportConstraintChecker()
  : DSRIODConstraintChecker()
{
}


DSRSpectaclePrescriptionReportConstraintChecker::~DSRSpectaclePrescriptionReportConstraintChecker()
{
}


OFBool DSRSpectaclePrescriptionReportConstraintChecker::isByReferenceAllowed() const
{
    return OFFalse;
}


OFBool DSRSpectaclePrescriptionReportConstraintChecker::isTemplateSupportRequired() const
{
    return OFTrue;
}


const char *DSRSpectaclePrescriptionReportConstraintChecker::getRootTemplateIdentifier() const
{
    return "2020";
}


DSRTypes::E_DocumentType DSRSpectaclePrescriptionReportConstraintChecker::getDocumentType() const
{
    return DT_SpectaclePrescriptionReport;
}


OFBool DSRSpectaclePrescriptionReportConstraintChecker::checkContentRelationship(const E_ValueType sourceValueType,
                                                                                 const E_RelationshipType relationshipType,
                                                                                 const E_ValueType targetValueType,
                                                                                 const OFBool byReference) const
{
    /* the following code implements the constraints of table A.35.9-2 in DICOM PS3.3 */
    OFBool result = OFFalse;
    /* by-reference relationships not allowed at all */
    if (!byReference)
    {
        /* row 1 of the table */
        if ((relationshipType == RT_contains) && (sourceValueType == VT_Container))
        {
            result = (targetValueType == VT_Container) || (targetValueType == VT_Code) ||
                     (targetValueType == VT_Num) || (targetValueType == VT_Text);
        }
    }
    return result;
}
