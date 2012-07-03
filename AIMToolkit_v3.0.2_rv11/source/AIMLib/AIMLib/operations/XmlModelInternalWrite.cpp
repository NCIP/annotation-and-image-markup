/*
  Classname: XmlModelInternal

  © 2008-2010 Northwestern University

  Authors:
  Vladimir Kleper
  Northwestern University
  Feinberg School of Medicine
  Department of Radiology
  Imaging Informatics Section
  Chicago, IL

The Academic Free License v. 2.1

This Academic Free License (the "License") applies to any original work of
authorship (the "Original Work") whose owner (the "Licensor") has placed the
following notice immediately following the copyright notice for the Original
Work:

Licensed under the Academic Free License version 2.1

1) Grant of Copyright License. Licensor hereby grants You a world-wide, royalty-
free, non-exclusive, perpetual, sublicenseable license to do the following:

a) to reproduce the Original Work in copies;

b) to prepare derivative works ("Derivative Works") based upon the Original Work;

c) to distribute copies of the Original Work and Derivative Works to the public;

d) to perform the Original Work publicly; and

e) to display the Original Work publicly.

2) Grant of Patent License. Licensor hereby grants You a world-wide, royalty-
free, non-exclusive, perpetual, sublicenseable license, under patent claims
owned or controlled by the Licensor that are embodied in the Original Work as
furnished by the Licensor, to make, use, sell and offer for sale the Original
Work and Derivative Works.

3) Grant of Source Code License. The term "Source Code" means the preferred form
of the Original Work for making modifications to it and all available
documentation describing how to modify the Original Work. Licensor hereby agrees
to provide a machine-readable copy of the Source Code of the Original Work along
with each copy of the Original Work that Licensor distributes. Licensor reserves
the right to satisfy this obligation by placing a machine-readable copy of the
Source Code in an information repository reasonably calculated to permit
inexpensive and convenient access by You for as long as Licensor continues to
distribute the Original Work, and by publishing the address of that information
repository in a notice immediately following the copyright notice that applies
to the Original Work.

4) Exclusions From License Grant. Neither the names of Licensor, nor the names
of any contributors to the Original Work, nor any of their trademarks or service
marks, may be used to endorse or promote products derived from this Original
Work without express prior written permission of the Licensor. Nothing in this
License shall be deemed to grant any rights to trademarks, copyrights, patents,
trade secrets or any other intellectual property of Licensor except as expressly
stated herein. No patent license is granted to make, use, sell or offer to sell
embodiments of any patent claims other than the licensed claims defined in
Section 2. No right is granted to the trademarks of Licensor even if such marks
are included in the Original Work. Nothing in this License shall be interpreted
to prohibit Licensor from licensing under different terms from this License any
Original Work that Licensor otherwise would have a right to license.

5) This section intentionally omitted.

6) Attribution Rights. You must retain, in the Source Code of any Derivative
Works that You create, all copyright, patent or trademark notices from the
Source Code of the Original Work, as well as any notices of licensing and any
descriptive text identified therein as an "Attribution Notice." You must cause
the Source Code for any Derivative Works that You create to carry a prominent
Attribution Notice reasonably calculated to inform recipients that You have
modified the Original Work.

7) Warranty of Provenance and Disclaimer of Warranty. Licensor warrants that the
copyright in and to the Original Work and the patent rights granted herein by
Licensor are owned by the Licensor or are sublicensed to You under the terms of
this License with the permission of the contributor(s) of those copyrights and
patent rights. Except as expressly stated in the immediately proceeding
sentence, the Original Work is provided under this License on an "AS IS" BASIS
and WITHOUT WARRANTY, either express or implied, including, without limitation,
the warranties of NON-INFRINGEMENT, MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE. THE ENTIRE RISK AS TO THE QUALITY OF THE ORIGINAL WORK IS WITH YOU.
This DISCLAIMER OF WARRANTY constitutes an essential part of this License. No
license to Original Work is granted hereunder except under this disclaimer.

8) Limitation of Liability. Under no circumstances and under no legal theory,
whether in tort (including negligence), contract, or otherwise, shall the
Licensor be liable to any person for any direct, indirect, special, incidental,
or consequential damages of any character arising as a result of this License or
the use of the Original Work including, without limitation, damages for loss of
goodwill, work stoppage, computer failure or malfunction, or any and all other
commercial damages or losses. This limitation of liability shall not apply to
liability for death or personal injury resulting from Licensor's negligence to
the extent applicable law prohibits such limitation. Some jurisdictions do not
allow the exclusion or limitation of incidental or consequential damages, so
this exclusion and limitation may not apply to You.

9) Acceptance and Termination. If You distribute copies of the Original Work or
a Derivative Work, You must make a reasonable effort under the circumstances to
obtain the express assent of recipients to the terms of this License. Nothing
else but this License (or another written agreement between Licensor and You)
grants You permission to create Derivative Works based upon the Original Work or
to exercise any of the rights granted in Section 1 herein, and any attempt to do
so except under the terms of this License (or another written agreement between
Licensor and You) is expressly prohibited by U.S. copyright law, the equivalent
laws of other countries, and by international treaty. Therefore, by exercising
any of the rights granted to You in Section 1 herein, You indicate Your
acceptance of this License and all of its terms and conditions.

10) Termination for Patent Action. This License shall terminate automatically
and You may no longer exercise any of the rights granted to You by this License
as of the date You commence an action, including a cross-claim or counterclaim,
against Licensor or any licensee alleging that the Original Work infringes a
patent. This termination provision shall not apply for an action alleging patent
infringement by combinations of the Original Work with other software or 
hardware.

11) Jurisdiction, Venue and Governing Law. Any action or suit relating to this
License may be brought only in the courts of a jurisdiction wherein the Licensor
resides or in which Licensor conducts its primary business, and under the laws
of that jurisdiction excluding its conflict-of-law provisions. The application
of the United Nations Convention on Contracts for the International Sale of
Goods is expressly excluded. Any use of the Original Work outside the scope of
this License or after its termination shall be subject to the requirements and
penalties of the U.S. Copyright Act, 17 U.S.C. § 101 et seq., the equivalent
laws of other countries, and international treaty. This section shall survive
the termination of this License.

12) Attorneys Fees. In any action to enforce the terms of this License or
seeking damages relating thereto, the prevailing party shall be entitled to
recover its costs and expenses, including, without limitation, reasonable
attorneys' fees and costs incurred in connection with such action, including any
appeal of such action. This section shall survive the termination of this
License.

13) Miscellaneous. This License represents the complete agreement concerning the
subject matter hereof. If any provision of this License is held to be
unenforceable, such provision shall be reformed only to the extent necessary to
make it enforceable.

14) Definition of "You" in This License. "You" throughout this License, whether
in upper or lower case, means an individual or a legal entity exercising rights
under, and complying with all of the terms of, this License. For legal entities,
"You" includes any entity that controls, is controlled by, or is under common
control with you. For purposes of this definition, "control" means (i) the
power, direct or indirect, to cause the direction or management of such entity,
whether by contract or otherwise, or (ii) ownership of fifty percent (50%) or
more of the outstanding shares, or (iii) beneficial ownership of such entity.

15) Right to Use. You may use the Original Work in all ways not otherwise
restricted or conditioned by this License or by law, and Licensor promises not
to interfere with or be responsible for such uses by You.

This license is Copyright (C) 2003-2004 Lawrence E. Rosen. All rights reserved.
Permission is hereby granted to copy and distribute this license without
modification. This license may not be modified without the express written
permission of its copyright owner.

*/

#include "../stdafx.h"
#include "../model/AimHeaders.h"

#include "../AIMUtil.h"

#include "XmlModelInternal.h"

using namespace aim_lib;
using namespace AIMXML;

static const std::string C_AIM_SCHEMA_LOCATION="AIM_v3_rv11_XML.xsd";

/*
 * This class uses AIM data model to populate AIM XML data model by traversing every class
 * in the AIM data model and generating corresponding AIM XML data model.
 *
 */

XmlModelInternal::XmlModelInternal(void)
{
}

XmlModelInternal::~XmlModelInternal(void)
{
}

/*
* 
*/
void XmlModelInternal::createXmlNode(CAIMXML& xmlDoc, Annotation* pAnnotation)
{
	const ImageAnnotation* pImgAnnotation = dynamic_cast<const ImageAnnotation*>(pAnnotation);
	const AnnotationOfAnnotation* pAnnAnnotation = dynamic_cast<const AnnotationOfAnnotation*>(pAnnotation);

	if (pImgAnnotation != NULL)
	{
		assert(pImgAnnotation->GetAnnotationKind() == Annotation::AK_ImageAnnotation);
		CImageAnnotation imgAnnotation = xmlDoc.ImageAnnotation.append();
		xmlDoc.SetSchemaLocation(C_AIM_SCHEMA_LOCATION);

		this->createXmlNodeImageAnnotation(imgAnnotation, *pImgAnnotation);
	}
	else if (pAnnAnnotation != NULL)
	{
		assert(pAnnAnnotation->GetAnnotationKind() == Annotation::AK_AnnotationOfAnnotation);
		CAnnotationOfAnnotation annAnnotation = xmlDoc.AnnotationOfAnnotation.append();
		xmlDoc.SetSchemaLocation(C_AIM_SCHEMA_LOCATION);

		this->createXmlNodeAnnotationOfAnnotation(annAnnotation, *pAnnAnnotation);
	}
	else
	{
		assert(false);
	}
}

// Create doc with multiple annotations
void XmlModelInternal::createXmlNodes(CAIMXML& xmlDoc, const AnnotationPtrVector& aAnnotations)
{
	for(AnnotationPtrVector::const_iterator iter = aAnnotations.begin(); iter < aAnnotations.end(); iter ++)
	{
		if (*iter != NULL)
			this->createXmlNode(xmlDoc, *iter);
	}
}

/*
* Create AnnotationOfAnnotation
*/
void XmlModelInternal::createXmlNodeAnnotationOfAnnotation(AIMXML::CAnnotationOfAnnotation xmlAnnotation, const AnnotationOfAnnotation& annAnnotation)
{
	xmlAnnotation.cagridId = 0;
	xmlAnnotation.aimVersion		= _T(annAnnotation.GetAimVersion());
	xmlAnnotation.dateTime			= AIMUtil::DateTimeToAltovaDateTime(annAnnotation.GetDateTime());
	xmlAnnotation.name				= _T(annAnnotation.GetName());
	xmlAnnotation.uniqueIdentifier	= _T(annAnnotation.GetUniqueIdentifier());
	if (!annAnnotation.GetComment().empty())
		xmlAnnotation.comment = _T(annAnnotation.GetComment());
	if (!annAnnotation.GetPrecedentReferencedAnnotationUID().empty())
		xmlAnnotation.precedentReferencedAnnotationUID = _T(annAnnotation.GetPrecedentReferencedAnnotationUID());

	// Annotation of Annotation Type
	xmlAnnotation.codeValue					= _T(annAnnotation.GetCodeValue());
	xmlAnnotation.codeMeaning				= _T(annAnnotation.GetCodeMeaning());
	xmlAnnotation.codingSchemeDesignator	= _T(annAnnotation.GetCodingSchemeDesignator());
	if (!annAnnotation.GetCodingSchemeVersion().empty())
		xmlAnnotation.codingSchemeVersion = _T(annAnnotation.GetCodingSchemeVersion());

	// Calculation
	const CalculationVector& calculations = annAnnotation.GetCalculationCollection();
	if (calculations.size() > 0)
	{
		CcalculationCollectionType xmlCalculations = xmlAnnotation.calculationCollection.append();
		for(CalculationVector::const_iterator iter = calculations.begin(); iter < calculations.end(); iter++)
			this->createXmlNode(xmlCalculations, *iter);
	}	
		
	// Inference
	const InferenceVector& inferences = annAnnotation.GetInferenceCollection();
	if (inferences.size() > 0)
	{
		CinferenceCollectionType xmlInferences = xmlAnnotation.inferenceCollection.append();
		for(InferenceVector::const_iterator iter = inferences.begin(); iter < inferences.end(); iter++)
			this->createXmlNode(xmlInferences, *iter);
	}

	// User
	if (annAnnotation.GetUser() != NULL)
	{
		CuserType xmlUserContainer = xmlAnnotation.user.append();
		this->createXmlNode(xmlUserContainer, annAnnotation.GetUser());
	}
	
	// Equipment
	if (annAnnotation.GetEquipment() != NULL)
	{
		CequipmentType xmlEquipmentContainer = xmlAnnotation.equipment.append();
		this->createXmlNode(xmlEquipmentContainer, annAnnotation.GetEquipment());
	}

	// Anatomic Entity
	const AnatomicEntityVector& anatomicEntities = annAnnotation.GetAnatomicEntityCollection();
	if (anatomicEntities.size() > 0)
	{
		CanatomicEntityCollectionType xmlAnatomicEntities = xmlAnnotation.anatomicEntityCollection.append();
		for(AnatomicEntityVector::const_iterator iter = anatomicEntities.begin(); iter < anatomicEntities.end(); iter++)
			this->createXmlNode(xmlAnatomicEntities, *iter);
	}	
	
	// Imaging Observation
	const ImagingObservationVector& imagingObservations = annAnnotation.GetImagingObservationCollection();
	if (imagingObservations.size() > 0)
	{
		CimagingObservationCollectionType xmlImagingObservations = xmlAnnotation.imagingObservationCollection.append();
		for(ImagingObservationVector::const_iterator iter = imagingObservations.begin(); iter < imagingObservations.end(); iter++)
			this->createXmlNode(xmlImagingObservations, *iter);
	}

	// AIM Status
	if (annAnnotation.GetAimStatus() != NULL)
	{
		CaimStatusType xmlAimStatusContainer = xmlAnnotation.aimStatus.append();
		this->createXmlNode(xmlAimStatusContainer, annAnnotation.GetAimStatus());
	}

	// Referenced Annotation Collection
	const aim_lib::ReferencedAnnotationVector referencedAnnotations = annAnnotation.GetReferencedAnnotationCollection();
//	if (referencedAnnotations.size() > 0)
	{
		AIMXML::CreferencedAnnotationCollectionType xmlReferencedAnnotations = xmlAnnotation.referencedAnnotationCollection.append();
		for(ReferencedAnnotationVector::const_iterator iter = referencedAnnotations.begin(); iter < referencedAnnotations.end(); iter++)
			this->createXmlNode(xmlReferencedAnnotations, *iter);
	}
}

/*
* Referenced Annotation
*/
void XmlModelInternal::createXmlNode(AIMXML::CreferencedAnnotationCollectionType& xmlParent, const ReferencedAnnotation& referencedAnnotation)
{
	AIMXML::CReferencedAnnotation xmlReferncedAnnotation = xmlParent.ReferencedAnnotation.append();
	xmlReferncedAnnotation.cagridId					= 0;
	xmlReferncedAnnotation.referencedAnnotationUID	= referencedAnnotation.GetReferencedAnnotationUID();
	AnnotationRole* pAnnotationRole = referencedAnnotation.GetAnnotationRole();
	if (pAnnotationRole != NULL)
	{
		AIMXML::CAnnotationRole xmlAnnotationRole = xmlReferncedAnnotation.annotationRole.append().AnnotationRole.append();
		xmlAnnotationRole.cagridId					= 0;
		xmlAnnotationRole.codeValue					= _T(pAnnotationRole->GetCodeValue());
		xmlAnnotationRole.codeMeaning				= _T(pAnnotationRole->GetCodeMeaning());
		xmlAnnotationRole.codingSchemeDesignator	= _T(pAnnotationRole->GetCodingSchemeDesignator());
		if (!pAnnotationRole->GetCodingSchemeVersion().empty())
			xmlAnnotationRole.codingSchemeVersion = _T(pAnnotationRole->GetCodingSchemeVersion());
		xmlAnnotationRole.roleSequenceNumber		= pAnnotationRole->GetRoleSequenceNumber();
	}
}

/*
* Create ImageAnnotation
*/
void XmlModelInternal::createXmlNodeImageAnnotation(AIMXML::CImageAnnotation& xmlAnnotation, const ImageAnnotation& annotation)
{
	xmlAnnotation.cagridId			= 0;
	xmlAnnotation.aimVersion		= _T(annotation.GetAimVersion());
	xmlAnnotation.dateTime			= AIMUtil::DateTimeToAltovaDateTime(annotation.GetDateTime());
	xmlAnnotation.name				= _T(annotation.GetName());
	xmlAnnotation.uniqueIdentifier	= _T(annotation.GetUniqueIdentifier());
	if (!annotation.GetComment().empty())
		xmlAnnotation.comment = _T(annotation.GetComment());
	if (!annotation.GetPrecedentReferencedAnnotationUID().empty())
		xmlAnnotation.precedentReferencedAnnotationUID = _T(annotation.GetPrecedentReferencedAnnotationUID());

	// Image Annotation type
	xmlAnnotation.codeValue					= _T(annotation.GetCodeValue());
	xmlAnnotation.codeMeaning				= _T(annotation.GetCodeMeaning());
	xmlAnnotation.codingSchemeDesignator	= _T(annotation.GetCodingSchemeDesignator());
	if (!annotation.GetCodingSchemeVersion().empty())
		xmlAnnotation.codingSchemeVersion = _T(annotation.GetCodingSchemeVersion());

	// Calculation
	const CalculationVector& calculations = annotation.GetCalculationCollection();
	if (calculations.size() > 0)
	{
		CcalculationCollectionType xmlCalculations = xmlAnnotation.calculationCollection.append();
		for(CalculationVector::const_iterator iter = calculations.begin(); iter < calculations.end(); iter++)
			this->createXmlNode(xmlCalculations, *iter);
	}

	// Inference
	const InferenceVector& inferences = annotation.GetInferenceCollection();
	if (inferences.size() > 0)
	{
		CinferenceCollectionType xmlInferences = xmlAnnotation.inferenceCollection.append();
		for(InferenceVector::const_iterator iter = inferences.begin(); iter < inferences.end(); iter++)
			this->createXmlNode(xmlInferences, *iter);
	}

	// User
	if (annotation.GetUser() != NULL)
	{
		CuserType xmlUserContainer = xmlAnnotation.user.append();
		this->createXmlNode(xmlUserContainer, annotation.GetUser());
	}
	
	// Equipment
	if (annotation.GetEquipment() != NULL)
	{
		CequipmentType xmlEquipmentContainer = xmlAnnotation.equipment.append();
		this->createXmlNode(xmlEquipmentContainer, annotation.GetEquipment());
	}
	
	// Anatomic Entity
	const AnatomicEntityVector& anatomicEntities = annotation.GetAnatomicEntityCollection();
	if (anatomicEntities.size() > 0)
	{
		CanatomicEntityCollectionType xmlAnatomicEntities = xmlAnnotation.anatomicEntityCollection.append();
		for(AnatomicEntityVector::const_iterator iter = anatomicEntities.begin(); iter < anatomicEntities.end(); iter++)
			this->createXmlNode(xmlAnatomicEntities, *iter);
	}	
	
	// Imaging Observation
	const ImagingObservationVector& imagingObservations = annotation.GetImagingObservationCollection();
	if (imagingObservations.size() > 0)
	{
		CimagingObservationCollectionType xmlImagingObservations = xmlAnnotation.imagingObservationCollection.append();
		for(ImagingObservationVector::const_iterator iter = imagingObservations.begin(); iter < imagingObservations.end(); iter++)
			this->createXmlNode(xmlImagingObservations, *iter);
	}

	// AIM Status
	if (annotation.GetAimStatus() != NULL)
	{
		CaimStatusType xmlAimStatusContainer = xmlAnnotation.aimStatus.append();
		this->createXmlNode(xmlAimStatusContainer, annotation.GetAimStatus());
	}

	// Segmentation
	const SegmentationVector& segmentations = annotation.GetSegmentationCollection();
	if (segmentations.size() > 0)
	{
		CsegmentationCollectionType xmlSegmentations = xmlAnnotation.segmentationCollection.append();
		for(SegmentationVector::const_iterator iter = segmentations.begin(); iter < segmentations.end(); iter++)
			this->createXmlNode(xmlSegmentations, *iter);
	}

	// Image Reference
	const aim_lib::ImageReferencePtrVector& imageReferences = annotation.GetImageReferenceCollection();
//	if (imageReferences.size() > 0)
	{
		CimageReferenceCollectionType xmlImageReferences = xmlAnnotation.imageReferenceCollection.append();
		for (ImageReferencePtrVector::const_iterator iter = imageReferences.begin(); iter < imageReferences.end(); iter++)
		{
			if (*iter != NULL)
				this->createXmlNode(xmlImageReferences, **iter);
		}
	}

	// Geometric Shape
	const GeoShapePtrVector& geoShapes = annotation.GetGeometricShapeCollection();
	if (geoShapes.size() > 0)
	{
		CgeometricShapeCollectionType xmlGeoShapes = xmlAnnotation.geometricShapeCollection.append();
		for(GeoShapePtrVector::const_iterator iter = geoShapes.begin(); iter < geoShapes.end(); iter++)
		{
			if (*iter != NULL)
				this->createXmlNode(xmlGeoShapes, **iter);
		}
	}

	// Patient
	//if (annotation.GetPatient() != NULL)
	{
		CpersonType xmlPersonContainer = xmlAnnotation.person.append();
		CPerson xmlPerson = xmlPersonContainer.Person.append();
		xmlPerson.cagridId		= 0;
		xmlPerson.name			= _T(annotation.GetPatient().GetName());
		xmlPerson.id			= annotation.GetPatient().GetId();
		if (annotation.GetPatient().GetBirthDate() != Date())
			xmlPerson.birthDate		= AIMUtil::DateToAltovaDateTime(annotation.GetPatient().GetBirthDate());
		if (!annotation.GetPatient().GetSex().empty())
			xmlPerson.sex			= _T(annotation.GetPatient().GetSex());
		if (!annotation.GetPatient().GetEthnicGroup().empty())
			xmlPerson.ethnicGroup	= _T(annotation.GetPatient().GetEthnicGroup());
	}

	// Text Annotation Collection
	const aim_lib::TextAnnotationVector& textAnnotations = annotation.GetTextAnnotationCollection();
	if (textAnnotations.size() > 0)
	{
		AIMXML::CtextAnnotationCollectionType xmlTextAnnotations = xmlAnnotation.textAnnotationCollection.append();
		for(TextAnnotationVector::const_iterator iter = textAnnotations.begin(); iter < textAnnotations.end(); iter++)
			this->createXmlNode(xmlTextAnnotations, *iter);
	}
}

// User
void XmlModelInternal::createXmlNode(CuserType& xmlParent, const User* pUser)
{
	if (pUser != NULL)
	{
		CUser xmlUser = xmlParent.User.append();
		xmlUser.cagridId						= 0;
		xmlUser.name							= _T(pUser->GetName());
		xmlUser.loginName						= _T(pUser->GetLoginName());
		if (!pUser->GetRoleInTrial().empty())
			xmlUser.roleInTrial = _T(pUser->GetRoleInTrial());
		if (pUser->GetNumberWithinRoleOfClinicalTrial() != -1)
			xmlUser.numberWithinRoleOfClinicalTrial	= pUser->GetNumberWithinRoleOfClinicalTrial();
	}
}

// Equipment
void XmlModelInternal::createXmlNode(CequipmentType& xmlParent, const Equipment* pEquipment)
{
	if (pEquipment != NULL)
	{
		CEquipment xmlEquipment = xmlParent.Equipment.append();
		xmlEquipment.cagridId				= 0;
		xmlEquipment.manufacturerName		= _T(pEquipment->GetManufacturerName());
		if (!pEquipment->GetManufacturerModelName().empty())
			xmlEquipment.manufacturerModelName = _T(pEquipment->GetManufacturerModelName());
		if (!pEquipment->GetSoftwareVersion().empty())
			xmlEquipment.softwareVersion = _T(pEquipment->GetSoftwareVersion());
	}
}

// AimStatus
void XmlModelInternal::createXmlNode(AIMXML::CaimStatusType& xmlParent, const AimStatus* pAimStatus)
{
	if (pAimStatus != NULL)
	{
		CAimStatus xmlAimStatus = xmlParent.AimStatus.append();
		xmlAimStatus.cagridId				= 0;
		xmlAimStatus.annotationVersion		= pAimStatus->GetAnnotationVersion();
		xmlAimStatus.codeValue				= _T(pAimStatus->GetCodeValue());
		xmlAimStatus.codeMeaning			= _T(pAimStatus->GetCodeMeaning());
		xmlAimStatus.codingSchemeDesignator	= _T(pAimStatus->GetCodingSchemeDesignator());
		if (!pAimStatus->GetCodingSchemeVersion().empty())
			xmlAimStatus.codingSchemeVersion = _T(pAimStatus->GetCodingSchemeVersion());

		if (!pAimStatus->GetAuthorizedBy().empty())
			xmlAimStatus.authorizedBy = _T(pAimStatus->GetAuthorizedBy());
	}
}

/*
* Text Annotation Collection
*/
void XmlModelInternal::createXmlNode(CtextAnnotationCollectionType& xmlParent, const TextAnnotation &textAnnotation)
{
	AIMXML::CTextAnnotation xmlTextAnnotation = xmlParent.TextAnnotation.append();
	xmlTextAnnotation.cagridId		= 0;
	xmlTextAnnotation.text			= _T(textAnnotation.GetText());
	if (!textAnnotation.GetFont().empty())
		xmlTextAnnotation.font = _T(textAnnotation.GetFont());
	if (!textAnnotation.GetFontColor().empty())
		xmlTextAnnotation.fontColor = _T(textAnnotation.GetFontColor());
	if (!textAnnotation.GetFontEffect().empty())
		xmlTextAnnotation.fontEffect = _T(textAnnotation.GetFontEffect());
	if (!textAnnotation.GetFontSize().empty())
		xmlTextAnnotation.fontSize = _T(textAnnotation.GetFontSize());
	if (!textAnnotation.GetFontStyle().empty())
		xmlTextAnnotation.fontStyle = _T(textAnnotation.GetFontStyle());
	if (!textAnnotation.GetTextJustify().empty())
		xmlTextAnnotation.textJustify = _T(textAnnotation.GetTextJustify());
	if (!textAnnotation.GetFontOpacity().empty())
		xmlTextAnnotation.fontOpacity = _T(textAnnotation.GetFontOpacity());

	const MultiPoint* pMultiPoint = textAnnotation.GetConnectorPoints();

	if (pMultiPoint != NULL && pMultiPoint->GetSpatialCoordinateCollection().size() > 0)
	{
		CMultiPoint xmlMultiPoint = xmlTextAnnotation.multiPoint.append().MultiPoint.append();
		xmlMultiPoint.cagridId			= 0;
		xmlMultiPoint.includeFlag		= pMultiPoint->GetIncludeFlag();
		xmlMultiPoint.shapeIdentifier	= pMultiPoint->GetShapeIdentifier();
		if (!pMultiPoint->GetLineColor().empty())
			xmlMultiPoint.lineColor = _T(pMultiPoint->GetLineColor());
		if (!pMultiPoint->GetLineOpacity().empty())
			xmlMultiPoint.lineOpacity = _T(pMultiPoint->GetLineOpacity());
		if (!pMultiPoint->GetLineStyle().empty())
			xmlMultiPoint.lineStyle = _T(pMultiPoint->GetLineStyle());
		if (!pMultiPoint->GetLineThickness().empty())
			xmlMultiPoint.lineThickness = _T(pMultiPoint->GetLineThickness());

		const SpatialCoordPtrVector& spatialCoordinates = pMultiPoint->GetSpatialCoordinateCollection();
//		if (spatialCoordinates.size() > 0)
		{
			assert(spatialCoordinates.size() <= 2); // up two points are allowed here
			CspatialCoordinateCollectionType xmlSpatialCoordinates = xmlMultiPoint.spatialCoordinateCollection.append();
			for(SpatialCoordPtrVector::const_iterator iter = spatialCoordinates.begin(); iter < spatialCoordinates.end(); iter++)
			{
				if (*iter != NULL)
					this->createXmlNode(xmlSpatialCoordinates, **iter);
			}
		}
	}
}

// Image Reference
void XmlModelInternal::createXmlNode(AIMXML::CimageReferenceCollectionType& xmlParent, const aim_lib::ImageReference& imageReference)
{
	switch (imageReference.GetImageReferenceType())
	{
		case ImageReference::T_DICOM_IMAGE_REF:   
		{
			AIMXML::CDICOMImageReference xmlDICOMImageReference = xmlParent.ImageReference.appendSpecial(AIMXML::_altova_ti_altova_CDICOMImageReference);
			const DICOMImageReference& dicomImageReference = (const DICOMImageReference&)imageReference; 

			xmlDICOMImageReference.cagridId = 0;
			
			// ImageStudy
			const ImageStudy& study = dicomImageReference.GetStudy();
			AIMXML::CImageStudy xmlImageStudy = xmlDICOMImageReference.imageStudy.append().ImageStudy.append();
			xmlImageStudy.cagridId		= 0;
			xmlImageStudy.instanceUID	= _T(study.GetInstanceUID());
			xmlImageStudy.startDate		= AIMUtil::DateToAltovaDateTime(study.GetStartDate());
			xmlImageStudy.startTime		= _T(study.GetStartTime().GetDicomFormatedTime());
			
			const ImageSeries& series = study.GetSeries();
			CImageSeries xmlImageSeries = xmlImageStudy.imageSeries.append().ImageSeries.append();

			xmlImageSeries.cagridId		= 0;
			xmlImageSeries.instanceUID	= _T(series.GetInstanceUID());

			const ImageVector& images = series.GetImageCollection();
			CimageCollectionType xmlImages = xmlImageSeries.imageCollection.append();
			for(ImageVector::const_iterator iter = images.begin(); iter < images.end(); iter++)
				this->createXmlNode(xmlImages, *iter);

			// Presentation State
			const PresentationStateVector& presentationStates = dicomImageReference.GetPresentationStateCollection();
			if (!presentationStates.empty())
			{
				CpresentationStateCollectionType xmlPresentationStates = xmlDICOMImageReference.presentationStateCollection.append();
				for(PresentationStateVector::const_iterator iter = presentationStates.begin(); iter < presentationStates.end(); iter++)
					this->createXmlNode(xmlPresentationStates, *iter);
			}

			break;
		}
		case ImageReference::T_WEB_IMAGE_REF:
		{
			AIMXML::CWebImageReference xmlWebImageReference = xmlParent.ImageReference.appendSpecial(AIMXML::_altova_ti_altova_CWebImageReference);
			const WebImageReference& webImageReference = (const WebImageReference&) imageReference;

			xmlWebImageReference.cagridId	= 0;
			xmlWebImageReference.uri		= _T(webImageReference.GetURI());
			break;
		}
		default:
			assert(false); // Unknown shape type was given
	}
}

// Image
void XmlModelInternal::createXmlNode(AIMXML::CimageCollectionType &xmlParent, const aim_lib::Image& image)
{
	AIMXML::CImage xmlImage = xmlParent.Image.append();

	xmlImage.cagridId					= 0;
	xmlImage.sopClassUID				= _T(image.GetSopClassUID());
	xmlImage.sopInstanceUID				= _T(image.GetSopInstanceUID());
}

// Presentation State
void XmlModelInternal::createXmlNode(AIMXML::CpresentationStateCollectionType& xmlParent, const aim_lib::PresentationState& presentationState)
{
	CPresentationState xmlPresentationState = xmlParent.PresentationState.append();

	xmlPresentationState.cagridId		= 0;
	xmlPresentationState.sopInstanceUID	= _T(presentationState.GetSopInstanceUID());
}

// Geometric Shape
void XmlModelInternal::createXmlNode(AIMXML::CgeometricShapeCollectionType& xmlParent, const aim_lib::GeometricShape& geometricShape)
{
    CGeometricShape* pXmlGeometricShape = NULL;
	
	switch (geometricShape.GetShapeType())
	{
		case GeometricShape::SHT_Circle:
		{
			AIMXML::CCircle xmlCircle = xmlParent.GeometricShape.appendSpecial(AIMXML::_altova_ti_altova_CCircle);
			pXmlGeometricShape = &xmlCircle;
			break;
		}
		case GeometricShape::SHT_Point:
		{
			AIMXML::CPoint xmlPoint = xmlParent.GeometricShape.appendSpecial(AIMXML::_altova_ti_altova_CPoint);
			pXmlGeometricShape = &xmlPoint;
			break;
		}	
		case GeometricShape::SHT_Ellipse:
		{
			AIMXML::CEllipse xmlEllipse = xmlParent.GeometricShape.appendSpecial(AIMXML::_altova_ti_altova_CEllipse);
			pXmlGeometricShape = &xmlEllipse;
			break;
		}	
		case GeometricShape::SHT_Polyline:
		{
			AIMXML::CPolyline xmlPolyline = xmlParent.GeometricShape.appendSpecial(AIMXML::_altova_ti_altova_CPolyline);
			pXmlGeometricShape = &xmlPolyline;
			break;
		}	
		case GeometricShape::SHT_Multipoint:
		{
			AIMXML::CMultiPoint xmlMultiPoint = xmlParent.GeometricShape.appendSpecial(AIMXML::_altova_ti_altova_CMultiPoint);
			pXmlGeometricShape = &xmlMultiPoint;
			break;
		}	
	}

	if (pXmlGeometricShape == NULL)
	{
		assert(false); // Unknown shape type was given
		return;
	}

	pXmlGeometricShape->cagridId		= 0;
	pXmlGeometricShape->includeFlag		= geometricShape.GetIncludeFlag();
	pXmlGeometricShape->shapeIdentifier	= geometricShape.GetShapeIdentifier();
	if (!geometricShape.GetLineColor().empty())
		pXmlGeometricShape->lineColor = _T(geometricShape.GetLineColor());
	if (!geometricShape.GetLineOpacity().empty())
		pXmlGeometricShape->lineOpacity = _T(geometricShape.GetLineOpacity());
	if (!geometricShape.GetLineStyle().empty())
		pXmlGeometricShape->lineStyle = _T(geometricShape.GetLineStyle());
	if (!geometricShape.GetLineThickness().empty())
		pXmlGeometricShape->lineThickness = _T(geometricShape.GetLineThickness());

	const aim_lib::SpatialCoordPtrVector& spatialCoordinates = geometricShape.GetSpatialCoordinateCollection();
//	if (spatialCoordinates.size() > 0)
	{
		CspatialCoordinateCollectionType xmlSpatialCoordinates = pXmlGeometricShape->spatialCoordinateCollection.append();
		for(SpatialCoordPtrVector::const_iterator iter = spatialCoordinates.begin(); iter < spatialCoordinates.end(); iter++)
		{
			if (*iter != NULL)
				this->createXmlNode(xmlSpatialCoordinates, **iter);
		}
	}
}

// Spatial Coordinate
void XmlModelInternal::createXmlNode(CspatialCoordinateCollectionType& xmlParent, const SpatialCoordinate& spatialCoordinate)
{
	switch(spatialCoordinate.GetCoordinateType())
	{
	case SpatialCoordinate::T_2D_SPCOORD:
		{
			const TwoDimensionSpatialCoordinate& spatialCoord2D = (TwoDimensionSpatialCoordinate&)spatialCoordinate;
			CTwoDimensionSpatialCoordinate xmlSpatialCoord2D = xmlParent.SpatialCoordinate.appendSpecial(AIMXML::_altova_ti_altova_CTwoDimensionSpatialCoordinate);
			xmlSpatialCoord2D.cagridId				= 0;
			xmlSpatialCoord2D.coordinateIndex		= spatialCoord2D.GetCoordinateIndex();
			xmlSpatialCoord2D.x						= spatialCoord2D.GetX();
			xmlSpatialCoord2D.y						= spatialCoord2D.GetY();
			xmlSpatialCoord2D.imageReferenceUID		= _T(spatialCoord2D.GetImageReferenceUID());
			xmlSpatialCoord2D.referencedFrameNumber	= spatialCoord2D.GetReferencedFrameNumber();
		}
		break;
	case SpatialCoordinate::T_3D_SPCOORD:
		{
			const ThreeDimensionSpatialCoordinate& spatialCoord3D = (ThreeDimensionSpatialCoordinate&)spatialCoordinate;
			CThreeDimensionSpatialCoordinate xmlSpatialCoord3D = xmlParent.SpatialCoordinate.appendSpecial(AIMXML::_altova_ti_altova_CThreeDimensionSpatialCoordinate);
			xmlSpatialCoord3D.cagridId				= 0;
			xmlSpatialCoord3D.coordinateIndex		= spatialCoord3D.GetCoordinateIndex();
			xmlSpatialCoord3D.x						= spatialCoord3D.GetX();
			xmlSpatialCoord3D.y						= spatialCoord3D.GetY();
			xmlSpatialCoord3D.z						= spatialCoord3D.GetZ();
			xmlSpatialCoord3D.frameOfReferenceUID	= _T(spatialCoord3D.GetFrameOfReferenceUID());
		}
		break;
	default:
		assert(false); // Unknown spatial coordinate
	}
}

// Segmentation
void XmlModelInternal::createXmlNode(CsegmentationCollectionType& xmlParent, const Segmentation& segmentation)
{
	CSegmentation xmlSegmentation = xmlParent.Segmentation.append();

	xmlSegmentation.cagridId					= 0;
	xmlSegmentation.sopInstanceUID				= _T(segmentation.GetSopInstanceUID());
	xmlSegmentation.sopClassUID					= _T(segmentation.GetSopClassUID());
	xmlSegmentation.referencedSopInstanceUID	= _T(segmentation.GetReferencedSopInstanceUID());
	xmlSegmentation.segmentNumber				= segmentation.GetSegmentNumber();

	const ImagingObservation* pImagingObservation = segmentation.GetImagingObservation();
	if (pImagingObservation != NULL)
	{
		CImagingObservation xmlImagingObservation = xmlSegmentation.imagingObservation.append().ImagingObservation.append();
		xmlImagingObservation.cagridId					= 0;
		xmlImagingObservation.codeValue					= _T(pImagingObservation->GetCodeValue());
		xmlImagingObservation.codeMeaning				= _T(pImagingObservation->GetCodeMeaning());
		xmlImagingObservation.codingSchemeDesignator	= _T(pImagingObservation->GetCodingSchemeDesignator());
		xmlImagingObservation.label						= _T(pImagingObservation->GetLabel());
		xmlImagingObservation.isPresent					= _T(pImagingObservation->GetIsPresent());
		if (!pImagingObservation->GetCodingSchemeVersion().empty())
			xmlImagingObservation.codingSchemeVersion = _T(pImagingObservation->GetCodingSchemeVersion());
		if (!pImagingObservation->GetComment().empty())
			xmlImagingObservation.comment = _T(pImagingObservation->GetComment());

		ImagingObservationCharacteristicVector imagingObsCharacteristics = pImagingObservation->GetImagingObservationCharacteristicCollection();
//		if (imagingObsCharacteristics.size() > 0)
		{
			CimagingObservationCharacteristicCollectionType xmlImagingObsCharacteristics = xmlImagingObservation.imagingObservationCharacteristicCollection.append();
			for(ImagingObservationCharacteristicVector::const_iterator iter = imagingObsCharacteristics.begin(); iter < imagingObsCharacteristics.end(); iter++)
				this->createXmlNode(xmlImagingObsCharacteristics, *iter);
		}
	}
}

// Inference
void XmlModelInternal::createXmlNode(CinferenceCollectionType& xmlParent, const Inference& inference)
{
	CInference xmlInference = xmlParent.Inference.append();

	xmlInference.cagridId				= 0;
	xmlInference.codeValue				= _T(inference.GetCodeValue());
	xmlInference.codeMeaning			= _T(inference.GetCodeMeaning());
	xmlInference.codingSchemeDesignator	= _T(inference.GetCodingSchemeDesignator());
	xmlInference.codingSchemeVersion	= _T(inference.GetCodingSchemeVersion());
	if (inference.GetAnnotatorConfidence() != NULL)
		xmlInference.annotatorConfidence = *inference.GetAnnotatorConfidence();
	xmlInference.imageEvidence			= inference.GetImageEvidence();
}


/*
* Anatomic Entity
*/
void XmlModelInternal::createXmlNode(CanatomicEntityCollectionType& xmlParent, const AnatomicEntity& anatomicEntity)
{
	CAnatomicEntity xmlAnatomicEntity  = xmlParent.AnatomicEntity.append();
	xmlAnatomicEntity.cagridId					= 0;
	xmlAnatomicEntity.label						= _T(anatomicEntity.GetLabel());
	xmlAnatomicEntity.isPresent					= _T(anatomicEntity.GetIsPresent());
	xmlAnatomicEntity.codeValue					= _T(anatomicEntity.GetCodeValue());
	xmlAnatomicEntity.codeMeaning				= _T(anatomicEntity.GetCodeMeaning());
	xmlAnatomicEntity.codingSchemeDesignator	= _T(anatomicEntity.GetCodingSchemeDesignator());
	if (!anatomicEntity.GetCodingSchemeVersion().empty())
		xmlAnatomicEntity.codingSchemeVersion		= _T(anatomicEntity.GetCodingSchemeVersion());
	if (anatomicEntity.GetAnnotatorConfidence() != NULL)
		xmlAnatomicEntity.annotatorConfidence = *anatomicEntity.GetAnnotatorConfidence();

	AnatomicEntityCharacteristicVector anatomicEntityCharachteristics = anatomicEntity.GetAnatomicEntityCharacteristicCollection();
	if (anatomicEntityCharachteristics.size() > 0)
	{
		CanatomicEntityCharacteristicCollectionType xmlAnatomicEntityCharacteristics = xmlAnatomicEntity.anatomicEntityCharacteristicCollection.append();
		for(AnatomicEntityCharacteristicVector::const_iterator iter = anatomicEntityCharachteristics.begin(); iter < anatomicEntityCharachteristics.end(); ++iter)
			this->createXmlNode(xmlAnatomicEntityCharacteristics, *iter);
	}
}


void XmlModelInternal::createXmlNode(CanatomicEntityCharacteristicCollectionType& xmlParent, const AnatomicEntityCharacteristic& anatomicEntityCharacteristic)
{
	CAnatomicEntityCharacteristic xmlAnatomicEntityCharateristic = xmlParent.AnatomicEntityCharacteristic.append();
	xmlAnatomicEntityCharateristic.cagridId					= 0;
	xmlAnatomicEntityCharateristic.label					= _T(anatomicEntityCharacteristic.GetLabel());
	xmlAnatomicEntityCharateristic.codeValue				= _T(anatomicEntityCharacteristic.GetCodeValue());
	xmlAnatomicEntityCharateristic.codeMeaning				= _T(anatomicEntityCharacteristic.GetCodeMeaning());
	xmlAnatomicEntityCharateristic.codingSchemeDesignator	= _T(anatomicEntityCharacteristic.GetCodingSchemeDesignator());
	if (!anatomicEntityCharacteristic.GetCodingSchemeDesignator().empty())
		xmlAnatomicEntityCharateristic.codingSchemeVersion = _T(anatomicEntityCharacteristic.GetCodingSchemeVersion());
	if (anatomicEntityCharacteristic.GetAnnotatorConfidence() != NULL)
		xmlAnatomicEntityCharateristic.annotatorConfidence = *anatomicEntityCharacteristic.GetAnnotatorConfidence();

	// Characteristic Quantification
	const CharacteristicQuantificationPtrVector& charQuantifications = anatomicEntityCharacteristic.GetCharacteristicQuantificationCollection();
	if (!charQuantifications.empty())
	{
		CcharacteristicQuantificationCollectionType xmlCharQuantifications = xmlAnatomicEntityCharateristic.characteristicQuantificationCollection.append();
		for(CharacteristicQuantificationPtrVector::const_iterator iter = charQuantifications.begin(); iter < charQuantifications.end(); iter++)
		{
			if (*iter != NULL)
			{
				CharacteristicQuantificationWrapper charQuantificationWrapper(&xmlCharQuantifications);
				this->createXmlNode(charQuantificationWrapper, **iter);
			}
		}
	}
}

/*
* Imaging Observation Collection
*/
void XmlModelInternal::createXmlNode(CimagingObservationCollectionType& xmlParent, const ImagingObservation &imagingObservation)
{
	CImagingObservation xmlImagingObservation = xmlParent.ImagingObservation.append();
	xmlImagingObservation.cagridId					= 0;
	xmlImagingObservation.label						= _T(imagingObservation.GetLabel());
	xmlImagingObservation.isPresent					= _T(imagingObservation.GetIsPresent());
	xmlImagingObservation.codeValue					= _T(imagingObservation.GetCodeValue());
	xmlImagingObservation.codeMeaning				= _T(imagingObservation.GetCodeMeaning());
	xmlImagingObservation.codingSchemeDesignator	= _T(imagingObservation.GetCodingSchemeDesignator());
	if (!imagingObservation.GetCodingSchemeVersion().empty())
		xmlImagingObservation.codingSchemeVersion = _T(imagingObservation.GetCodingSchemeVersion());
	if (!imagingObservation.GetComment().empty())
		xmlImagingObservation.comment = _T(imagingObservation.GetComment());
	if (imagingObservation.GetAnnotatorConfidence() != NULL)
		xmlImagingObservation.annotatorConfidence = *imagingObservation.GetAnnotatorConfidence();

	ImagingObservationCharacteristicVector imagingObsCharacteristics = imagingObservation.GetImagingObservationCharacteristicCollection();
	if (imagingObsCharacteristics.size() > 0)
	{
		CimagingObservationCharacteristicCollectionType xmlImagingObsCharacteristics = xmlImagingObservation.imagingObservationCharacteristicCollection.append();
		for(ImagingObservationCharacteristicVector::const_iterator iter = imagingObsCharacteristics.begin(); iter < imagingObsCharacteristics.end(); iter++)
			this->createXmlNode(xmlImagingObsCharacteristics, *iter);
	}

	if (imagingObservation.GetReferencedGeometricShape() != NULL)
	{
		CreferencedGeometricShapeType xmlRefGeoShapeContainer = xmlImagingObservation.referencedGeometricShape.append();
		CReferencedGeometricShape xmlRefGeoShape = xmlRefGeoShapeContainer.ReferencedGeometricShape.append();

		xmlRefGeoShape.cagridId						= 0;
		xmlRefGeoShape.referencedShapeIdentifier	= imagingObservation.GetReferencedGeometricShape()->GetReferencedShapeIdentifier();
	}
}

/*
* Imaging Observation Characteristic Collection
*/
void XmlModelInternal::createXmlNode(CimagingObservationCharacteristicCollectionType& xmlParent, const ImagingObservationCharacteristic &imagingObsCharacteristic)
{
	CImagingObservationCharacteristic xmlImagingObsCharateristic = xmlParent.ImagingObservationCharacteristic.append();
	xmlImagingObsCharateristic.cagridId					= 0;
	xmlImagingObsCharateristic.label					= _T(imagingObsCharacteristic.GetLabel());
	xmlImagingObsCharateristic.codeValue				= _T(imagingObsCharacteristic.GetCodeValue());
	xmlImagingObsCharateristic.codeMeaning				= _T(imagingObsCharacteristic.GetCodeMeaning());
	xmlImagingObsCharateristic.codingSchemeDesignator	= _T(imagingObsCharacteristic.GetCodingSchemeDesignator());
	if (!imagingObsCharacteristic.GetCodingSchemeVersion().empty())
		xmlImagingObsCharateristic.codingSchemeVersion = _T(imagingObsCharacteristic.GetCodingSchemeVersion());
	if (!imagingObsCharacteristic.GetComment().empty())
		xmlImagingObsCharateristic.comment = _T(imagingObsCharacteristic.GetComment());
	if (imagingObsCharacteristic.GetAnnotatorConfidence() != NULL)
		xmlImagingObsCharateristic.annotatorConfidence = *imagingObsCharacteristic.GetAnnotatorConfidence();

	// Characteristic Quantification
	const CharacteristicQuantificationPtrVector& charQuantifications = imagingObsCharacteristic.GetCharacteristicQuantificationCollection();
	if (!charQuantifications.empty())
	{
		CcharacteristicQuantificationCollectionType2 xmlCharQuantifications = xmlImagingObsCharateristic.characteristicQuantificationCollection.append();
		for(CharacteristicQuantificationPtrVector::const_iterator iter = charQuantifications.begin(); iter < charQuantifications.end(); iter++)
		{
			if (*iter != NULL)
			{
				CharacteristicQuantificationWrapper charQuantificationWrapper(&xmlCharQuantifications);
				this->createXmlNode(charQuantificationWrapper, **iter);
			}
		}
	}
}

void XmlModelInternal::createXmlNode(CharacteristicQuantificationWrapper& parentObj, const CharacteristicQuantification& charQuantification)
{
	switch(charQuantification.GetQuantificationType())
	{
	case CharacteristicQuantification::QT_Numerical:
		{
			const Numerical& numerical = (Numerical&)charQuantification;
			CNumerical xmlNumerical = parentObj.appendSpecial(AIMXML::_altova_ti_altova_CNumerical).GetNode();
			xmlNumerical.numericalValue = numerical.GetValue();
			xmlNumerical.ucumString = _T(numerical.GetUcumString());
			if (numerical.GetOperator() != InvalidComparisonOperatorType)
				xmlNumerical.numericalOperator = _T(AimEnum::ComparisonOperatorTypeToString(numerical.GetOperator()));
		}
		break;
	case CharacteristicQuantification::QT_Quantile:
		{
			const Quantile& quantile = (Quantile&)charQuantification;
			CQuantile xmlQuantile = parentObj.appendSpecial(AIMXML::_altova_ti_altova_CQuantile).GetNode();
			xmlQuantile.bin = quantile.GetBin();
		}
		break;
	case CharacteristicQuantification::QT_Non_Quantifiable:
		{
			const NonQuantifiable& nonQuantifiable = (NonQuantifiable&)charQuantification;
			CNonQuantifiable xmlNonQuantifiable = parentObj.appendSpecial(AIMXML::_altova_ti_altova_CNonQuantifiable).GetNode();
			xmlNonQuantifiable.codeValue				= _T(nonQuantifiable.GetCodeValue());
			xmlNonQuantifiable.codeMeaning				= _T(nonQuantifiable.GetCodeMeaning());
			xmlNonQuantifiable.codingSchemeDesignator	= _T(nonQuantifiable.GetCodingSchemeDesignator());
			if (!nonQuantifiable.GetCodingSchemeVersion().empty())
				xmlNonQuantifiable.codingSchemeVersion = _T(nonQuantifiable.GetCodingSchemeVersion());
		}
		break;
	case CharacteristicQuantification::QT_Scale:
		{
			const Scale& scale = (Scale&)charQuantification;
			CScale xmlScale = parentObj.appendSpecial(AIMXML::_altova_ti_altova_CScale).GetNode();
			xmlScale.scaleValue = _T(scale.GetValue());
			if (!scale.GetComment().empty())
				xmlScale.comment = _T(scale.GetComment());
			if (!scale.GetDescription().empty())
				xmlScale.description = _T(scale.GetDescription());
		}
		break;
	case CharacteristicQuantification::QT_Interval:
		{
			const Interval& interval = (Interval&)charQuantification;
			CInterval xmlInterval = parentObj.appendSpecial(AIMXML::_altova_ti_altova_CInterval).GetNode();
			xmlInterval.minValue	= interval.GetMinValue();
			xmlInterval.maxValue	= interval.GetMaxValue();
			xmlInterval.minOperator	= _T(AimEnum::ComparisonOperatorTypeToString(interval.GetMinOperator()));
			xmlInterval.maxOperator	= _T(AimEnum::ComparisonOperatorTypeToString(interval.GetMaxOperator()));
			xmlInterval.ucumString	= _T(interval.GetUcumString());
		}
		break;
	default:
		assert(false); // Unknown Quantification Characteristic
		return;
	}

	// Common attributes
	CCharacteristicQuantification xmlCharQuantification = parentObj.last();
	xmlCharQuantification.cagridId	= 0;
	xmlCharQuantification.name		= _T(charQuantification.GetName());
	if (charQuantification.GetAnnotatorConfidence() != NULL)
		xmlCharQuantification.annotatorConfidence = *charQuantification.GetAnnotatorConfidence();
}

/*
* Calculation Collection
*/
void XmlModelInternal::createXmlNode(CcalculationCollectionType& xmlParent, const Calculation &calculation)
{
	CCalculation xmlCalc = xmlParent.Calculation.append();
	xmlCalc.cagridId				= 0;
	xmlCalc.uid						= _T(calculation.GetUID());
	xmlCalc.description				= _T(calculation.GetDescription());
	xmlCalc.codeValue				= _T(calculation.GetCodeValue());
	xmlCalc.codeMeaning				= _T(calculation.GetCodeMeaning());
	xmlCalc.codingSchemeDesignator	= _T(calculation.GetCodingSchemeDesignator());
	if (!calculation.GetCodingSchemeVersion().empty())
		xmlCalc.codingSchemeVersion = _T(calculation.GetCodingSchemeVersion());
	if (!calculation.GetMathML().empty())
		xmlCalc.mathML = _T(calculation.GetMathML());
	if (!calculation.GetAlgorithmName().empty())
		xmlCalc.algorithmName = _T(calculation.GetAlgorithmName());
	if (!calculation.GetAlgorithmVersion().empty())
		xmlCalc.algorithmVersion = _T(calculation.GetAlgorithmVersion());

	const ReferencedCalcVector& refCalcs = calculation.GetReferencedCalculationCollection();
//	if (refCalcs.size() > 0)
	{
		CreferencedCalculationCollectionType xmlRefCalcs = xmlCalc.referencedCalculationCollection.append();
		for(ReferencedCalcVector::const_iterator iter = refCalcs.begin(); iter < refCalcs.end(); iter++)
			this->createXmlNode(xmlRefCalcs, *iter);
	}

	const CalcResultVector& calcResults = calculation.GetCalculationResultCollection();
//	if (calcResults.size() > 0)
	{
		CcalculationResultCollectionType xmlCalcResults = xmlCalc.calculationResultCollection.append();
		for(CalcResultVector::const_iterator iter = calcResults.begin(); iter < calcResults.end(); iter++)
			this->createXmlNode(xmlCalcResults, *iter);
	}

	const ReferencedGeometricShapeVector& refGeoShapes = calculation.GetReferencedGeometricShapeCollection();
	CreferencedGeometricShapeCollectionType xmlRefGeoShapes = xmlCalc.referencedGeometricShapeCollection.append();
	for(ReferencedGeometricShapeVector::const_iterator iter = refGeoShapes.begin(); iter < refGeoShapes.end(); iter++)
		this->createXmlNode(xmlRefGeoShapes, *iter);
}

/*
* Referenced Calculation Collection
*/
void XmlModelInternal::createXmlNode(CreferencedCalculationCollectionType& xmlParent, const ReferencedCalculation& refCalculation)
{
	CReferencedCalculation xmlRefCalc = xmlParent.ReferencedCalculation.append();

	xmlRefCalc.cagridId			= 0;
	xmlRefCalc.uniqueIdentifier	= _T(refCalculation.GetUniqueIdentifier());
}

/*
* Referenced Geometric Shape Collection
*/
void XmlModelInternal::createXmlNode(CreferencedGeometricShapeCollectionType& xmlParent, const ReferencedGeometricShape& refGeoShape)
{
	CReferencedGeometricShape xmlRefGeoShape = xmlParent.ReferencedGeometricShape.append();

	xmlRefGeoShape.cagridId						= 0;
	xmlRefGeoShape.referencedShapeIdentifier	= refGeoShape.GetReferencedShapeIdentifier();
}

/*
* Calculation Result
*/
void XmlModelInternal::createXmlNode(CcalculationResultCollectionType& xmlParent, const CalculationResult& calcResult)
{
	CCalculationResult xmlCalcResult = xmlParent.CalculationResult.append();
	xmlCalcResult.cagridId				= 0;
	xmlCalcResult.type					= _T(CalculationResult::CalculationResultTypeToString(calcResult.GetType()));
	xmlCalcResult.numberOfDimensions	= calcResult.GetNumberOfDimensions();
	xmlCalcResult.unitOfMeasure			= _T(calcResult.GetUnitOfMeasure());

	const CalculationDataVector& datum = calcResult.GetCalculationDataCollection();
//	if (datum.size() > 0)
	{
		CcalculationDataCollectionType xmlCalculationDatum = xmlCalcResult.calculationDataCollection.append();
		for(CalculationDataVector::const_iterator iter = datum.begin(); iter < datum.end(); iter++)
			this->createXmlNode(xmlCalculationDatum, *iter);
	}

	const DimensionVector& dimensions = calcResult.GetDimensionCollection();
//	if (dimensions.size() > 0)
	{
		CdimensionCollectionType xmlDimensions = xmlCalcResult.dimensionCollection.append();
		for(DimensionVector::const_iterator iter = dimensions.begin(); iter < dimensions.end(); iter++)
			this->createXmlNode(xmlDimensions, *iter);
	}
}

/*
* Dimension Collection
*/
void XmlModelInternal::createXmlNode(CdimensionCollectionType& xmlParent, const Dimension& dimension)
{
	CDimension xmlDimension = xmlParent.Dimension.append();

	xmlDimension.cagridId	= 0;
	xmlDimension.index		= dimension.GetIndex();
	xmlDimension.size		= dimension.GetSize();
	xmlDimension.label		= _T(dimension.GetLabel());
}

/*
* Data Collection
*/
void XmlModelInternal::createXmlNode(CcalculationDataCollectionType& xmlParent, const CalculationData& data)
{
	CCalculationData xmlCalculationData = xmlParent.CalculationData.append();

	xmlCalculationData.cagridId		= 0;
	xmlCalculationData.dataValue	= data.GetValue();
	
	const CoordinateVector& coordinates = data.GetCoordinateCollection();
//	if (coordinates.size() > 0)
	{
		CcoordinateCollectionType xmlCoordinates = xmlCalculationData.coordinateCollection.append();
		for(CoordinateVector::const_iterator iter = coordinates.begin(); iter < coordinates.end(); iter++)
			this->createXmlNode(xmlCoordinates, *iter);
	}
}

void XmlModelInternal::createXmlNode(CcoordinateCollectionType &xmlParent, const Coordinate& coordinate)
{
	CCoordinate xmlCoordinate = xmlParent.Coordinate.append();

	xmlCoordinate.cagridId			= 0;
	xmlCoordinate.dimensionIndex	= coordinate.GetDimensionIndex();
	xmlCoordinate.position			= coordinate.GetPosition();
}
