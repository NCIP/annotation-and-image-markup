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

#include "../../AltovaXML/XercesString.h"

#include <algorithm>
#include <limits.h>

#include "../memdebug.h"

using namespace aim_lib;
using namespace AIMXML;

static const std::string _emptyStr = std::string("");

ImageAnnotation* XmlModelInternal::readXmlNodeImageAnnotation(CImageAnnotation& xmlImgAnnotation)
{
	ImageAnnotation* pImgAnnotation = new ImageAnnotation();

	try
	{
		// AIM Version
		pImgAnnotation->SetAimVersion(xmlImgAnnotation.aimVersion.exists() ? xmlImgAnnotation.aimVersion : _emptyStr);
		// UID
		pImgAnnotation->SetUniqueidentifier(xmlImgAnnotation.uniqueIdentifier.exists() ? xmlImgAnnotation.uniqueIdentifier : _emptyStr);
		// Name
		pImgAnnotation->SetName(xmlImgAnnotation.name.exists() ? xmlImgAnnotation.name : _emptyStr);
		// Date Time
		pImgAnnotation->SetDateTime(xmlImgAnnotation.dateTime.exists() ? AIMUtil::DateTimeConvert(xmlImgAnnotation.dateTime) : 0);
		// Comment
		pImgAnnotation->SetComment(xmlImgAnnotation.comment.exists() ? xmlImgAnnotation.comment : _emptyStr);
		// Code Value
		pImgAnnotation->SetCodeValue(xmlImgAnnotation.codeValue.exists() ? xmlImgAnnotation.codeValue : _emptyStr);
		// Code Meaning
		pImgAnnotation->SetCodeMeaning(xmlImgAnnotation.codeMeaning.exists() ? xmlImgAnnotation.codeMeaning : _emptyStr);
		// Coding Scheme Designator
		pImgAnnotation->SetCodingSchemeDesignator(xmlImgAnnotation.codingSchemeDesignator.exists() ? xmlImgAnnotation.codingSchemeDesignator : _emptyStr);
		// Coding Scheme Version
		pImgAnnotation->SetCodingSchemeVersion(xmlImgAnnotation.codingSchemeVersion.exists() ? xmlImgAnnotation.codingSchemeVersion : _emptyStr);
		// Precedent Referenced Annotation UID
		pImgAnnotation->SetPrecedentReferencedAnnotationUID(xmlImgAnnotation.precedentReferencedAnnotationUID.exists() ? xmlImgAnnotation.precedentReferencedAnnotationUID : _emptyStr);

		
		// PORTABILITY NOTE: Linux wants to have const references when passing arguments, but we don't get that from Altova code.
		// Also, Linux cannot pass temp variables as const references to methods
		// That's why we need to have two intermediate variables for each set method


		// User Info
		if (xmlImgAnnotation.user.exists() && xmlImgAnnotation.user.first().User.exists())
		{
			CUser xmlUser = xmlImgAnnotation.user.first().User.first();
			User user = this->readXmlNode(xmlUser);
			pImgAnnotation->SetUser(&user);
		}

		// Equipment
		if (xmlImgAnnotation.equipment.exists() && xmlImgAnnotation.equipment.first().Equipment.exists())
		{
			CEquipment xmlEquipment = xmlImgAnnotation.equipment.first().Equipment.first();
			Equipment equipment = this->readXmlNode(xmlEquipment);
			pImgAnnotation->SetEquipment(&equipment);
		}

		// Anatomic Entities
		if (xmlImgAnnotation.anatomicEntityCollection.exists())
		{
			CanatomicEntityCollectionType xmlAnatomicEntityCollection = xmlImgAnnotation.anatomicEntityCollection.first();
			AnatomicEntityVector anatomicEnities = this->readXmlNode(xmlAnatomicEntityCollection);
			pImgAnnotation->SetAnatomicEntityCollection(anatomicEnities);
		}

		// Patient
		if (xmlImgAnnotation.person.exists() && xmlImgAnnotation.person.first().Person.exists())
		{
			CPerson xmlPatient = xmlImgAnnotation.person.first().Person.first();
			Person patient;
			patient.SetName(xmlPatient.name.exists() ? xmlPatient.name : _emptyStr);
			patient.SetId(xmlPatient.id.exists() ? xmlPatient.id : _emptyStr);
			patient.SetBirthDate(xmlPatient.birthDate.exists() ? AIMUtil::DateConvert(xmlPatient.birthDate) : Date());
			patient.SetSex(xmlPatient.sex.exists() ? xmlPatient.sex : _emptyStr);
			patient.SetEthnicGroup(xmlPatient.ethnicGroup.exists() ? xmlPatient.ethnicGroup : _emptyStr);

			pImgAnnotation->SetPatient(patient);
		}

		// Imaging Observations
		if (xmlImgAnnotation.imagingObservationCollection.exists())
		{
			CimagingObservationCollectionType xmlImagingObservationCollection = xmlImgAnnotation.imagingObservationCollection.first();
			ImagingObservationVector imagingObservations = this->readXmlNode(xmlImagingObservationCollection);
			pImgAnnotation->SetImagingObservationCollection(imagingObservations);
		}

		// Segmentations
		if (xmlImgAnnotation.segmentationCollection.exists())
		{
			CsegmentationCollectionType xmlSegmentations = xmlImgAnnotation.segmentationCollection.first();
			SegmentationVector segmentations = this->readXmlNode(xmlSegmentations);
			pImgAnnotation->SetSegmentationCollection(segmentations);
		}

		// Calculations
		if (xmlImgAnnotation.calculationCollection.exists())
		{
			CcalculationCollectionType xmlCalculations = xmlImgAnnotation.calculationCollection.first();
			CalculationVector calculations = this->readXmlNode(xmlCalculations);
			pImgAnnotation->SetCalculationCollection(calculations);
		}

		// Image References
		if (xmlImgAnnotation.imageReferenceCollection.exists())
		{
			CimageReferenceCollectionType xmlImageReferences = xmlImgAnnotation.imageReferenceCollection.first();
			ImageReferencePtrVector imageReferences = this->readXmlNode(xmlImageReferences);
			pImgAnnotation->SetImageReferenceCollection(imageReferences);
			while(imageReferences.size() > 0)
			{
				delete imageReferences[imageReferences.size() - 1];
				imageReferences.pop_back();
			}
		}

		// Inferences
		if (xmlImgAnnotation.inferenceCollection.exists())
		{
			CinferenceCollectionType xmlInferences = xmlImgAnnotation.inferenceCollection.first();
			InferenceVector inferences = this->readXmlNode(xmlInferences);
			pImgAnnotation->SetInferenceCollection(inferences);
		}

		// Text Annotations
		if (xmlImgAnnotation.textAnnotationCollection.exists())
		{
			CtextAnnotationCollectionType xmlTextAnnotations = xmlImgAnnotation.textAnnotationCollection.first();
			TextAnnotationVector textAnnotations = this->readXmlNode(xmlTextAnnotations);
			pImgAnnotation->SetTextAnnotationCollection(textAnnotations);
		}

		// Geometric Shapes
		if (xmlImgAnnotation.geometricShapeCollection.exists())
		{
			CgeometricShapeCollectionType xmlGeoShapes = xmlImgAnnotation.geometricShapeCollection.first();
			GeoShapePtrVector geoShapes = this->readXmlNode(xmlGeoShapes);
			pImgAnnotation->SetGeometricShapeCollection(geoShapes);
			while(geoShapes.size() > 0)
			{
				delete geoShapes[geoShapes.size() - 1];
				geoShapes.pop_back();
			}
		}

		// AIM Status
		if (xmlImgAnnotation.aimStatus.exists() && xmlImgAnnotation.aimStatus.first().AimStatus.exists())
		{
			CAimStatus xmlAimStatus = xmlImgAnnotation.aimStatus.first().AimStatus.first();
			AimStatus aimStatus = this->readXmlNode(xmlAimStatus);
			pImgAnnotation->SetAimStatus(&aimStatus);
		}
	}
	catch (std::exception ex)
	{
		delete pImgAnnotation;
		return NULL;
	}

	return pImgAnnotation;
}


AnnotationOfAnnotation* XmlModelInternal::readXmlNodeAnnotationOfAnnotation(CAnnotationOfAnnotation& xmlAnnOfAnnotation)
{
	AnnotationOfAnnotation* pAnnAnnotation = new AnnotationOfAnnotation();

	try
	{
		// AIM Version
		pAnnAnnotation->SetAimVersion(xmlAnnOfAnnotation.aimVersion.exists() ? xmlAnnOfAnnotation.aimVersion : _emptyStr);
		// UID
		pAnnAnnotation->SetUniqueidentifier(xmlAnnOfAnnotation.uniqueIdentifier.exists() ? xmlAnnOfAnnotation.uniqueIdentifier : _emptyStr);
		// Name
		pAnnAnnotation->SetName(xmlAnnOfAnnotation.name.exists() ? xmlAnnOfAnnotation.name : _emptyStr);
		// Date Time
		pAnnAnnotation->SetDateTime(xmlAnnOfAnnotation.dateTime.exists() ? AIMUtil::DateTimeConvert(xmlAnnOfAnnotation.dateTime) : 0);
		// Comment
		pAnnAnnotation->SetComment(xmlAnnOfAnnotation.comment.exists() ? xmlAnnOfAnnotation.comment : _emptyStr);
		// Code Value
		pAnnAnnotation->SetCodeValue(xmlAnnOfAnnotation.codeValue.exists() ? xmlAnnOfAnnotation.codeValue : _emptyStr);
		// Code Meaning
		pAnnAnnotation->SetCodeMeaning(xmlAnnOfAnnotation.codeMeaning.exists() ? xmlAnnOfAnnotation.codeMeaning : _emptyStr);
		// Coding Scheme Designator
		pAnnAnnotation->SetCodingSchemeDesignator(xmlAnnOfAnnotation.codingSchemeDesignator.exists() ? xmlAnnOfAnnotation.codingSchemeDesignator : _emptyStr);
		// Coding Scheme Version
		pAnnAnnotation->SetCodingSchemeVersion(xmlAnnOfAnnotation.codingSchemeVersion.exists() ? xmlAnnOfAnnotation.codingSchemeVersion : _emptyStr);
		// Precedent Referenced Annotation UID
		pAnnAnnotation->SetPrecedentReferencedAnnotationUID(xmlAnnOfAnnotation.precedentReferencedAnnotationUID.exists() ? xmlAnnOfAnnotation.precedentReferencedAnnotationUID : _emptyStr);

		// User Info
		if (xmlAnnOfAnnotation.user.exists() && xmlAnnOfAnnotation.user.first().User.exists())
		{
			CUser xmlUser = xmlAnnOfAnnotation.user.first().User.first();
			User user = this->readXmlNode(xmlUser);
			pAnnAnnotation->SetUser(&user);
		}

		// Equipment
		if (xmlAnnOfAnnotation.equipment.exists() && xmlAnnOfAnnotation.equipment.first().Equipment.exists())
		{
			CEquipment xmlEquipment = xmlAnnOfAnnotation.equipment.first().Equipment.first();
			Equipment equipment = this->readXmlNode(xmlEquipment);
			pAnnAnnotation->SetEquipment(&equipment);
		}

		// Anatomic Entities
		if (xmlAnnOfAnnotation.anatomicEntityCollection.exists())
		{
			CanatomicEntityCollectionType xmlAnatomicEntities = xmlAnnOfAnnotation.anatomicEntityCollection.first();
			AnatomicEntityVector anatomicEnities = this->readXmlNode(xmlAnatomicEntities);
			pAnnAnnotation->SetAnatomicEntityCollection(anatomicEnities);
		}

		// Imaging Observations
		if (xmlAnnOfAnnotation.imagingObservationCollection.exists())
		{
			CimagingObservationCollectionType xmlImagingObservations = xmlAnnOfAnnotation.imagingObservationCollection.first();
			ImagingObservationVector imagingObservations = this->readXmlNode(xmlImagingObservations);
			pAnnAnnotation->SetImagingObservationCollection(imagingObservations);
		}

		// Calculations
		if (xmlAnnOfAnnotation.calculationCollection.exists())
		{
			CcalculationCollectionType xmlCalculations = xmlAnnOfAnnotation.calculationCollection.first();
			CalculationVector calculations = this->readXmlNode(xmlCalculations);
			pAnnAnnotation->SetCalculationCollection(calculations);
		}

		// Referenced Annotation
		if (xmlAnnOfAnnotation.referencedAnnotationCollection.exists())
		{
			CreferencedAnnotationCollectionType xmlReferencedAnnotations = xmlAnnOfAnnotation.referencedAnnotationCollection.first();
			ReferencedAnnotationVector referencedAnnotations = this->readXmlNode(xmlReferencedAnnotations);
			pAnnAnnotation->SetReferencedAnnotationCollection(referencedAnnotations);
		}

		// AIM Status
		if (xmlAnnOfAnnotation.aimStatus.exists() && xmlAnnOfAnnotation.aimStatus.first().AimStatus.exists())
		{
			CAimStatus xmlAimStatus = xmlAnnOfAnnotation.aimStatus.first().AimStatus.first();
			AimStatus aimStatus = this->readXmlNode(xmlAimStatus);
			pAnnAnnotation->SetAimStatus(&aimStatus);
		}
	}
	catch (std::exception ex)
	{
		delete pAnnAnnotation;
		return NULL;
	}

	return pAnnAnnotation;
}

// User 
const User XmlModelInternal::readXmlNode(CUser& xmlUser)
{
	User user;
	user.SetName(xmlUser.name.exists() ? xmlUser.name : _emptyStr);
	user.SetLoginName(xmlUser.loginName.exists() ? xmlUser.loginName : _emptyStr);
	user.SetRoleInTrial(xmlUser.roleInTrial.exists() ? xmlUser.roleInTrial : _emptyStr);
	user.SetNumberWithinRoleOfClinicalTrial(xmlUser.numberWithinRoleOfClinicalTrial.exists() ? (int)xmlUser.numberWithinRoleOfClinicalTrial : 0);
	return user;
}

// Equipment
const Equipment XmlModelInternal::readXmlNode(CEquipment& xmlEquipment)
{
	Equipment equipment;

	equipment.SetManufacturerName(xmlEquipment.manufacturerName.exists() ? xmlEquipment.manufacturerName : _emptyStr);
	equipment.SetManufacturerModelName(xmlEquipment.manufacturerModelName.exists() ? xmlEquipment.manufacturerModelName : _emptyStr);
	equipment.SetSoftwareVersion(xmlEquipment.softwareVersion.exists() ? xmlEquipment.softwareVersion : _emptyStr);

	return equipment;
}

// AIM Status
const AimStatus XmlModelInternal::readXmlNode(AIMXML::CAimStatus& xmlAimStatus)
{
	AimStatus aimStatus;
	aimStatus.SetAnnotationVersion(xmlAimStatus.annotationVersion.exists() ? xmlAimStatus.annotationVersion : 0.0);
	aimStatus.SetCodeMeaning(xmlAimStatus.codeMeaning.exists() ? xmlAimStatus.codeMeaning : _emptyStr);
	aimStatus.SetCodeValue(xmlAimStatus.codeValue.exists() ? xmlAimStatus.codeValue : _emptyStr);
	aimStatus.SetCodingSchemeDesignator(xmlAimStatus.codingSchemeDesignator.exists() ? xmlAimStatus.codingSchemeDesignator : _emptyStr);
	aimStatus.SetCodingSchemeVersion(xmlAimStatus.codingSchemeVersion.exists() ? xmlAimStatus.codingSchemeVersion : _emptyStr);
	aimStatus.SetAuthorizedBy(xmlAimStatus.authorizedBy.exists() ? xmlAimStatus.authorizedBy : _emptyStr);

	return aimStatus;
}

// Image Reference Collection
const ImageReferencePtrVector XmlModelInternal::readXmlNode(CimageReferenceCollectionType& xmlImageReferences)
{
	ImageReferencePtrVector imageReferences;
	if (xmlImageReferences.ImageReference.exists())
	{
		for(AIMXML::Iterator<CImageReference> iter = xmlImageReferences.ImageReference.all(); iter; ++iter)
		{
			std::string typeName = this->GetSubClassType(iter->GetNode());
			if ("DICOMImageReference" == typeName)
			{
				CDICOMImageReference xmlDicomImageRef(iter->GetNode());

				DICOMImageReference dicomImageRef;
				if (xmlDicomImageRef.imageStudy.exists() && xmlDicomImageRef.imageStudy.first().ImageStudy.exists())
				{
					CImageStudy xmlImageStudy = xmlDicomImageRef.imageStudy.first().ImageStudy.first();
					ImageStudy imageStudy;
					imageStudy.SetInstanceUID(xmlImageStudy.instanceUID.exists() ? xmlImageStudy.instanceUID : _emptyStr);
					imageStudy.SetStartDate(xmlImageStudy.startDate.exists() ? AIMUtil::DateConvert(xmlImageStudy.startDate) : Date());
					imageStudy.SetStartTime(xmlImageStudy.startTime.exists() ? AIMUtil::TimeConvert(AIMUtil::TimeConvert(xmlImageStudy.startTime)) : Time());
					if (xmlImageStudy.imageSeries.exists() && xmlImageStudy.imageSeries.first().ImageSeries.exists())
					{
						CImageSeries xmlImageSeries = xmlImageStudy.imageSeries.first().ImageSeries.first();
						ImageSeries imageSeries;
						imageSeries.SetInstanceUID(xmlImageSeries.instanceUID.exists() ? xmlImageSeries.instanceUID : _emptyStr);

						if (xmlImageSeries.imageCollection.exists())
						{
							CimageCollectionType xmlImages = xmlImageSeries.imageCollection.first();
							ImageVector images = readXmlNode(xmlImages);
							imageSeries.SetImageCollection(images);
						}

						imageStudy.SetSeries(imageSeries);
					}

					dicomImageRef.SetStudy(imageStudy);
				}
				else
				{
					assert(false); // DICOMImageReference is missing study information
				}

				// Presentation State
				if (xmlDicomImageRef.presentationStateCollection.exists())
				{
					CpresentationStateCollectionType xmlPresentationStates = xmlDicomImageRef.presentationStateCollection.first();
					PresentationStateVector presentationStates = this->readXmlNode(xmlPresentationStates);
					dicomImageRef.SetPresentationStateCollection(presentationStates);
				}

				imageReferences.push_back(dicomImageRef.Clone());
			}
			else if ("WebImageReference" == typeName)
			{
				CWebImageReference xmlWebImageRef(iter->GetNode());

				WebImageReference webImageRef;
				webImageRef.SetURI(xmlWebImageRef.uri.exists() ? xmlWebImageRef.uri : _emptyStr);

				imageReferences.push_back(webImageRef.Clone());
			}
			else
				assert(false); // unknown image reference type
		}
	}
	return imageReferences;
}

// Image
const ImageVector XmlModelInternal::readXmlNode(CimageCollectionType &xmlImages)
{
	ImageVector images;

	if (xmlImages.Image.exists())
	{
		for(AIMXML::Iterator<CImage> iter = xmlImages.Image.all(); iter; ++iter)
		{
			Image image;
			image.SetSopClassUID(iter->sopClassUID.exists() ? iter->sopClassUID : _emptyStr);
			image.SetSopInstanceUID(iter->sopInstanceUID.exists() ? iter->sopInstanceUID : _emptyStr);

			images.push_back(image);
		}
	}

	return images;
}

const PresentationStateVector XmlModelInternal::readXmlNode(CpresentationStateCollectionType& xmlPresentationStates)
{
	PresentationStateVector presentationStates;
	if (xmlPresentationStates.PresentationState.exists())
	{
		for (AIMXML::Iterator<CPresentationState> iter = xmlPresentationStates.PresentationState.all(); iter; ++iter)
		{
			PresentationState presentationState;
			presentationState.SetSopInstanceUID(iter->sopInstanceUID.exists() ? iter->sopInstanceUID : _emptyStr);

			presentationStates.push_back(presentationState);
		}
	}

	return presentationStates;
}


// Anatomic Entity
const AnatomicEntityVector XmlModelInternal::readXmlNode(CanatomicEntityCollectionType& xmlAnatomicEntities)
{
	AnatomicEntityVector anatomicEntities;
	if (xmlAnatomicEntities.AnatomicEntity.exists())
	{
		for (AIMXML::Iterator<CAnatomicEntity> iter = xmlAnatomicEntities.AnatomicEntity.all(); iter; ++iter)
		{
			AnatomicEntity anatomicEntity;
			anatomicEntity.SetCodeMeaning(iter->codeMeaning.exists() ? iter->codeMeaning : _emptyStr);
			anatomicEntity.SetCodeValue(iter->codeValue.exists() ? iter->codeValue : _emptyStr);
			anatomicEntity.SetCodingSchemeDesignator(iter->codingSchemeDesignator.exists() ? iter->codingSchemeDesignator : _emptyStr);
			anatomicEntity.SetCodingSchemeVersion(iter->codingSchemeVersion.exists() ? iter->codingSchemeVersion : _emptyStr);
			anatomicEntity.SetIsPresent(iter->isPresent.exists() ? iter->isPresent : true);
			anatomicEntity.SetLabel(iter->label.exists() ? iter->label : _emptyStr);
			if (iter->annotatorConfidence.exists())
			{
				double val = iter->annotatorConfidence;
				anatomicEntity.SetAnnotatorConfidence(&val);
			}

			if (iter->anatomicEntityCharacteristicCollection.exists())
			{
				CanatomicEntityCharacteristicCollectionType xmlAnatomicEntityChars = iter->anatomicEntityCharacteristicCollection.first();
				AnatomicEntityCharacteristicVector anatomicEntityChars = readXmlNode(xmlAnatomicEntityChars);
				anatomicEntity.SetAnatomicEntityCharacteristicCollection(anatomicEntityChars);
			}

			anatomicEntities.push_back(anatomicEntity);
		}
	}
	return anatomicEntities;
}

// Anatomic Entity Characteristic
const AnatomicEntityCharacteristicVector XmlModelInternal::readXmlNode(AIMXML::CanatomicEntityCharacteristicCollectionType& xmlAnatomicEntityCharacteristics)
{
	AnatomicEntityCharacteristicVector anatomicEntityCharacteristics;

	if (xmlAnatomicEntityCharacteristics.AnatomicEntityCharacteristic.exists())
	{
		for (AIMXML::Iterator<CAnatomicEntityCharacteristic> iter = xmlAnatomicEntityCharacteristics.AnatomicEntityCharacteristic.all(); iter; ++iter)
		{
			AnatomicEntityCharacteristic anatomicEntityCharacteristic;
			anatomicEntityCharacteristic.SetCodeMeaning(iter->codeMeaning.exists() ? iter->codeMeaning : _emptyStr);
			anatomicEntityCharacteristic.SetCodeValue(iter->codeValue.exists() ? iter->codeValue : _emptyStr);
			anatomicEntityCharacteristic.SetCodingSchemeDesignator(iter->codingSchemeDesignator.exists() ? iter->codingSchemeDesignator : _emptyStr);
			anatomicEntityCharacteristic.SetCodingSchemeVersion(iter->codingSchemeVersion.exists() ? iter->codingSchemeVersion : _emptyStr);
			anatomicEntityCharacteristic.SetLabel(iter->label.exists() ? iter->label : _emptyStr);
			if (iter->annotatorConfidence.exists())
			{
				//double val = AIMUtil::StringToDouble(iter->confidence);
				double val = iter->annotatorConfidence;
				anatomicEntityCharacteristic.SetAnnotatorConfidence(&val);
			}

			// Characteristic Quantifications
			if (iter->characteristicQuantificationCollection.exists())
			{
				CcharacteristicQuantificationCollectionType xmlCharacteristicQuantifications = iter->characteristicQuantificationCollection.first();
				CharacteristicQuantificationWrapper charQuantificationWrapper(&xmlCharacteristicQuantifications);
				CharacteristicQuantificationPtrVector charQuantifications = this->readXmlNode(charQuantificationWrapper);
				anatomicEntityCharacteristic.SetCharacteristicQuantificationCollection(charQuantifications);
				while(charQuantifications.size() > 0)
				{
					delete charQuantifications[charQuantifications.size() - 1];
					charQuantifications.pop_back();
				}
			}

			anatomicEntityCharacteristics.push_back(anatomicEntityCharacteristic);
		}
	}
	return anatomicEntityCharacteristics;
}

// Imaging Observation
const ImagingObservationVector XmlModelInternal::readXmlNode(CimagingObservationCollectionType& xmlImagingObservations)
{
	ImagingObservationVector imagingObservations;

	if (xmlImagingObservations.ImagingObservation.exists())
	{
		for (AIMXML::Iterator<CImagingObservation> iter = xmlImagingObservations.ImagingObservation.all(); iter; ++iter)
		{
			ImagingObservation imagingObservation;
			imagingObservation.SetCodeMeaning(iter->codeMeaning.exists() ? iter->codeMeaning : _emptyStr);
			imagingObservation.SetCodeValue(iter->codeValue.exists() ? iter->codeValue : _emptyStr);
			imagingObservation.SetCodingSchemeDesignator(iter->codingSchemeDesignator.exists() ? iter->codingSchemeDesignator : _emptyStr);
			imagingObservation.SetCodingSchemeVersion(iter->codingSchemeVersion.exists() ? iter->codingSchemeVersion : _emptyStr);
			imagingObservation.SetComment(iter->comment.exists() ? iter->comment : _emptyStr);
			imagingObservation.SetIsPresent(iter->isPresent.exists() ? iter->isPresent : true);
			imagingObservation.SetLabel(iter->label.exists() ? iter->label : _emptyStr);
			if (iter->annotatorConfidence.exists())
			{
				double val = iter->annotatorConfidence;
				imagingObservation.SetAnnotatorConfidence(&val);
			}

			if (iter->referencedGeometricShape.exists() && iter->referencedGeometricShape.first().ReferencedGeometricShape.exists())
			{
				CReferencedGeometricShape xmlReferencedShape = iter->referencedGeometricShape.first().ReferencedGeometricShape.first();
				ReferencedGeometricShape referencedShape;
				referencedShape.SetReferencedShapeIdentifier(xmlReferencedShape.referencedShapeIdentifier.exists() ? xmlReferencedShape.referencedShapeIdentifier : INT_MIN);
				imagingObservation.SetReferencedGeometricShape(&referencedShape);
			}

			if (iter->imagingObservationCharacteristicCollection.exists())
			{
				CimagingObservationCharacteristicCollectionType xmlImagingObservationChars = iter->imagingObservationCharacteristicCollection.first();
				ImagingObservationCharacteristicVector imagingObservationChars = this->readXmlNode(xmlImagingObservationChars);
				imagingObservation.SetImagingObservationCharacteristicCollection(imagingObservationChars);
			}

			imagingObservations.push_back(imagingObservation);
		}
	}
	return imagingObservations;
}

// Imaging Observation Characteristic
const ImagingObservationCharacteristicVector XmlModelInternal::readXmlNode(CimagingObservationCharacteristicCollectionType& xmlImagingObsCharacteristics)
{
	ImagingObservationCharacteristicVector imagingObsCharacteristics;

	if (xmlImagingObsCharacteristics.ImagingObservationCharacteristic.exists())
	{
		for (AIMXML::Iterator<CImagingObservationCharacteristic> iter = xmlImagingObsCharacteristics.ImagingObservationCharacteristic.all(); iter; ++iter)
		{
			ImagingObservationCharacteristic imagingObservationCharacteristic;
			imagingObservationCharacteristic.SetCodeMeaning(iter->codeMeaning.exists() ? iter->codeMeaning : _emptyStr);
			imagingObservationCharacteristic.SetCodeValue(iter->codeValue.exists() ? iter->codeValue : _emptyStr);
			imagingObservationCharacteristic.SetCodingSchemeDesignator(iter->codingSchemeDesignator.exists() ? iter->codingSchemeDesignator : _emptyStr);
			imagingObservationCharacteristic.SetCodingSchemeVersion(iter->codingSchemeVersion.exists() ? iter->codingSchemeVersion : _emptyStr);
			imagingObservationCharacteristic.SetComment(iter->comment.exists() ? iter->comment : _emptyStr);
			imagingObservationCharacteristic.SetLabel(iter->label.exists() ? iter->label : _emptyStr);
			if (iter->annotatorConfidence.exists())
			{
				double val = iter->annotatorConfidence;
				imagingObservationCharacteristic.SetAnnotatorConfidence(&val);
			}

			// Characteristic Quantifications
			if (iter->characteristicQuantificationCollection.exists())
			{
				CcharacteristicQuantificationCollectionType2 xmlCharacteristicQuantifications = iter->characteristicQuantificationCollection.first();
				CharacteristicQuantificationWrapper charQuantificationWrapper(&xmlCharacteristicQuantifications);
				CharacteristicQuantificationPtrVector charQuantifications = this->readXmlNode(charQuantificationWrapper);
				imagingObservationCharacteristic.SetCharacteristicQuantificationCollection(charQuantifications);
				while(charQuantifications.size() > 0)
				{
					delete charQuantifications[charQuantifications.size() - 1];
					charQuantifications.pop_back();
				}
			}

			imagingObsCharacteristics.push_back(imagingObservationCharacteristic);
		}
	}
	return imagingObsCharacteristics;
}

const CharacteristicQuantificationPtrVector XmlModelInternal::readXmlNode(CharacteristicQuantificationWrapper& parentObj)
{
	CharacteristicQuantificationPtrVector characteristicQuantifications;

	if (parentObj.exists())
	{
		for (AIMXML::Iterator<CCharacteristicQuantification> iter = parentObj.all(); iter; ++iter)
		{
			CharacteristicQuantification* pCharacteristicQuantification = NULL;
			std::string quantificationType = this->GetSubClassType(iter->GetNode());
			if(C_QUANTIFICATION_NUMERICAL_NAME == quantificationType)
			{
				CNumerical xmlNumerical = iter->GetNode();
				pCharacteristicQuantification = this->readXmlNode(xmlNumerical).Clone();
			}
			else if (C_QUANTIFICATION_QUANTILE_NAME == quantificationType)
			{
				CQuantile xmlQuantile = iter->GetNode();
				pCharacteristicQuantification = this->readXmlNode(xmlQuantile).Clone();
			}
			else if (C_QUANTIFICATION_NON_QUANTIFIABLE_NAME == quantificationType)
			{
				CNonQuantifiable xmlNonQuantifiable = iter->GetNode();
				pCharacteristicQuantification = this->readXmlNode(xmlNonQuantifiable).Clone();
			}
			else if (C_QUANTIFICATION_SCALE_NAME == quantificationType)
			{
				CScale xmlScale = iter->GetNode();
				pCharacteristicQuantification = this->readXmlNode(xmlScale).Clone();
			}
			else if (C_QUANTIFICATION_INTERVAL_NAME == quantificationType)
			{
				CInterval xmlInterval = iter->GetNode();
				pCharacteristicQuantification = this->readXmlNode(xmlInterval).Clone();
			}
			else
				assert(false);

			if (pCharacteristicQuantification != NULL)
				characteristicQuantifications.push_back(pCharacteristicQuantification);
		}
	}

	return characteristicQuantifications;
}

const Numerical XmlModelInternal::readXmlNode(AIMXML::CNumerical& xmlNumerical) const
{
	Numerical numerical;

	// Set common Characteristic Quantifications
	this->readXmlNode(numerical, xmlNumerical);

	if (xmlNumerical.numericalValue.exists())
		numerical.SetValue(xmlNumerical.numericalValue);
	numerical.SetUcumString(xmlNumerical.ucumString.exists() ? xmlNumerical.ucumString : _emptyStr);
	if (xmlNumerical.numericalOperator.exists())
		numerical.SetOperator(AimEnum::StringToComparisonOperatorType(xmlNumerical.numericalOperator));

	return numerical;
}

const Quantile XmlModelInternal::readXmlNode(AIMXML::CQuantile& xmlQuantile) const
{
	Quantile quantile;

	// Set common Characteristic Quantifications
	this->readXmlNode(quantile, xmlQuantile);

	quantile.SetBin(xmlQuantile.bin.exists() ? xmlQuantile.bin : INT_MIN);

	return quantile;
}

const NonQuantifiable XmlModelInternal::readXmlNode(AIMXML::CNonQuantifiable& xmlNonQuantifiable) const
{
	NonQuantifiable nonQuantifiable;

	// Set common Characteristic Quantifications
	this->readXmlNode(nonQuantifiable, xmlNonQuantifiable);

	nonQuantifiable.SetCodeValue(xmlNonQuantifiable.codeValue.exists() ? xmlNonQuantifiable.codeValue : _emptyStr);
	nonQuantifiable.SetCodeMeaning(xmlNonQuantifiable.codeMeaning.exists() ? xmlNonQuantifiable.codeMeaning : _emptyStr);
	nonQuantifiable.SetCodingSchemeDesignator(xmlNonQuantifiable.codingSchemeDesignator.exists() ? xmlNonQuantifiable.codingSchemeDesignator : _emptyStr);
	nonQuantifiable.SetCodingSchemeVersion(xmlNonQuantifiable.codingSchemeVersion.exists() ? xmlNonQuantifiable.codingSchemeVersion : _emptyStr);

	return nonQuantifiable;
}

const Scale XmlModelInternal::readXmlNode(AIMXML::CScale& xmlScale) const
{
	Scale scale;

	// Set common Characteristic Quantifications
	this->readXmlNode(scale, xmlScale);

	scale.SetValue(xmlScale.scaleValue.exists() ? xmlScale.scaleValue : _emptyStr);
	scale.SetComment(xmlScale.comment.exists() ? xmlScale.comment : _emptyStr);
	scale.SetDescription(xmlScale.description.exists() ?  xmlScale.description : _emptyStr);

	return scale;
}

const Interval XmlModelInternal::readXmlNode(AIMXML::CInterval& xmlInterval) const
{
	Interval interval;

	// Set common Characteristic Quantifications
	this->readXmlNode(interval, xmlInterval);

	interval.SetMinValue(xmlInterval.minValue.exists() ? xmlInterval.minValue : 0.0);
	interval.SetMaxValue(xmlInterval.maxValue.exists() ? xmlInterval.maxValue : 0.0);
	interval.SetMinOperator(xmlInterval.minOperator.exists() ? AimEnum::StringToComparisonOperatorType(xmlInterval.minOperator) : InvalidComparisonOperatorType);
	interval.SetMaxOperator(xmlInterval.maxOperator.exists() ? AimEnum::StringToComparisonOperatorType(xmlInterval.maxOperator) : InvalidComparisonOperatorType);
	interval.SetUcumString(xmlInterval.ucumString.exists() ? xmlInterval.ucumString : _emptyStr);

	return interval;
}

// Set common fields for all Characteristic Quantifications
void XmlModelInternal::readXmlNode(CharacteristicQuantification& charQuantification, AIMXML::CCharacteristicQuantification& xmlCharQuantification) const
{
	charQuantification.SetName(xmlCharQuantification.name.exists() ? xmlCharQuantification.name : _emptyStr);
	if (xmlCharQuantification.annotatorConfidence.exists())
	{
		double confidence = xmlCharQuantification.annotatorConfidence;
		charQuantification.SetAnnotatorConfidence(&confidence);
	}
}

const CalculationVector XmlModelInternal::readXmlNode(AIMXML::CcalculationCollectionType& xmlCalculations)
{
	CalculationVector calculations;

	if (xmlCalculations.Calculation.exists())
	{
		for (AIMXML::Iterator<CCalculation> iter = xmlCalculations.Calculation.all(); iter; ++iter)
		{
			Calculation calculation;
			calculation.SetUID(iter->uid.exists() ? iter->uid : _emptyStr);
			calculation.SetDescription(iter->description.exists() ? iter->description : _emptyStr);
			calculation.SetMathML(iter->mathML.exists() ? iter->mathML : _emptyStr);
			calculation.SetCodeValue(iter->codeValue.exists() ? iter->codeValue : _emptyStr);
			calculation.SetCodeMeaning(iter->codeMeaning.exists() ? iter->codeMeaning : _emptyStr);
			calculation.SetCodingSchemeDesignator(iter->codingSchemeDesignator.exists() ? iter->codingSchemeDesignator : _emptyStr);
			calculation.SetCodingSchemeVersion(iter->codingSchemeVersion.exists() ? iter->codingSchemeVersion : _emptyStr);
			calculation.SetAlgorithmName(iter->algorithmName.exists() ? iter->algorithmName : _emptyStr);
			calculation.SetAlgorithmVersion(iter->algorithmVersion.exists() ? iter->algorithmVersion: _emptyStr);

			if (iter->calculationResultCollection.exists())
			{
				CcalculationResultCollectionType xmlCalculationResults = iter->calculationResultCollection.first();
				CalcResultVector calcResults = this->readXmlNode(xmlCalculationResults);
				calculation.SetCalculationResultCollection(calcResults);
			}

			if (iter->referencedCalculationCollection.exists())
			{
				CreferencedCalculationCollectionType xmlReferencedCalculations = iter->referencedCalculationCollection.first();
				ReferencedCalcVector referencedCals = this->readXmlNode(xmlReferencedCalculations);
				calculation.SetReferencedCalculationCollection(referencedCals);
			}

			if (iter->referencedGeometricShapeCollection.exists())
			{
				CreferencedGeometricShapeCollectionType xmlReferencedGeoShapes = iter->referencedGeometricShapeCollection.first();
				ReferencedGeometricShapeVector referencedGeoShapes = this->readXmlNode(xmlReferencedGeoShapes);
				calculation.SetReferencedGeometricShapeCollection(referencedGeoShapes);
			}

			calculations.push_back(calculation);
		}
	}
	return calculations;
}

const CalcResultVector XmlModelInternal::readXmlNode(AIMXML::CcalculationResultCollectionType& xmlCalculationResults)
{
	CalcResultVector calculationResults;

	if (xmlCalculationResults.CalculationResult.exists())
	{
		for (AIMXML::Iterator<CCalculationResult> iter = xmlCalculationResults.CalculationResult.all(); iter; ++iter)
		{
			CalculationResult calculationResult;
			if (iter->type.exists())
				calculationResult.SetType(CalculationResult::StringToCalculationResultType(iter->type));
			calculationResult.SetNumberOfDimensions(iter->numberOfDimensions.exists() ? (int)iter->numberOfDimensions : 0);
			calculationResult.SetUnitOfMeasure(iter->unitOfMeasure.exists() ? iter->unitOfMeasure : _emptyStr);
			
			if (iter->calculationDataCollection.exists())
			{
				CcalculationDataCollectionType xmlCalculationDatum = iter->calculationDataCollection.first();
				CalculationDataVector calculationDatum = this->readXmlNode(xmlCalculationDatum);
				calculationResult.SetCalculationDataCollection(calculationDatum);
			}

			if (iter->dimensionCollection.exists())
			{
				CdimensionCollectionType xmlDimensions = iter->dimensionCollection.first();
				DimensionVector dimensions = this->readXmlNode(xmlDimensions);
				calculationResult.SetDimensionCollection(dimensions);
			}

			calculationResults.push_back(calculationResult);
		}
	}
	return calculationResults;
}

const ReferencedCalcVector XmlModelInternal::readXmlNode(AIMXML::CreferencedCalculationCollectionType& xmlReferencedCalculations)
{
	ReferencedCalcVector referencedCalculations;

	if (xmlReferencedCalculations.ReferencedCalculation.exists())
	{
		for (AIMXML::Iterator<CReferencedCalculation> iter = xmlReferencedCalculations.ReferencedCalculation.all(); iter; ++iter)
		{
			ReferencedCalculation referencedCalculation;
			referencedCalculation.SetUniqueIdentifier(iter->uniqueIdentifier.exists() ? iter->uniqueIdentifier : _emptyStr);
			
			referencedCalculations.push_back(referencedCalculation);
		}
	}
	return referencedCalculations;
}

const ReferencedGeometricShapeVector XmlModelInternal::readXmlNode(AIMXML::CreferencedGeometricShapeCollectionType& xmlReferencedGeoShapes)
{
	ReferencedGeometricShapeVector referencedGeoShapes;

	if (xmlReferencedGeoShapes.ReferencedGeometricShape.exists())
	{
		for(AIMXML::Iterator<CReferencedGeometricShape> iter = xmlReferencedGeoShapes.ReferencedGeometricShape.all(); iter; ++iter)
		{
			ReferencedGeometricShape referencedGeoShape;
			referencedGeoShape.SetReferencedShapeIdentifier(iter->referencedShapeIdentifier.exists() ? iter->referencedShapeIdentifier : INT_MIN);

			referencedGeoShapes.push_back(referencedGeoShape);
		}
	}
	return referencedGeoShapes;
}

const CalculationDataVector XmlModelInternal::readXmlNode(AIMXML::CcalculationDataCollectionType& xmlCalculationDatum)
{
	CalculationDataVector datum;

	if (xmlCalculationDatum.CalculationData.exists())
	{
		for (AIMXML::Iterator<CCalculationData> iter = xmlCalculationDatum.CalculationData.all(); iter; ++iter)
		{
			CalculationData data;
			data.SetValue(iter->dataValue.exists() ? iter->dataValue : 0.0f);

			if (iter->coordinateCollection.exists())
			{
				CcoordinateCollectionType xmlCoordinates = iter->coordinateCollection.first();
				CoordinateVector coordinates = this->readXmlNode(xmlCoordinates);
				data.SetCoordinateCollection(coordinates);
			}

			datum.push_back(data);
		}
	}
	return datum;
}

const DimensionVector XmlModelInternal::readXmlNode(AIMXML::CdimensionCollectionType& xmlDimensions)
{
	DimensionVector dimensions;

	if (xmlDimensions.Dimension.exists())
	{
		for (AIMXML::Iterator<CDimension> iter = xmlDimensions.Dimension.all(); iter; ++iter)
		{
			Dimension dimension;
			dimension.SetIndex(iter->index.exists() ? (int)iter->index : 0);
			dimension.SetSize(iter->size.exists() ? (int)iter->size : 0);
			dimension.SetLabel(iter->label.exists() ? iter->label : _emptyStr);

			dimensions.push_back(dimension);
		}
	}
	return dimensions;
}

const CoordinateVector XmlModelInternal::readXmlNode(AIMXML::CcoordinateCollectionType& xmlCoordinates)
{
	CoordinateVector coordinates;

	if (xmlCoordinates.Coordinate.exists())
	{
		for (AIMXML::Iterator<CCoordinate> iter = xmlCoordinates.Coordinate.all(); iter; ++iter)
		{
			Coordinate coordinate;
			coordinate.SetDimensionIndex(iter->dimensionIndex.exists() ? (int)iter->dimensionIndex : 0);
			coordinate.SetPosition(iter->position.exists() ? (int)iter->position : 0);

			coordinates.push_back(coordinate);
		}
	}
	return coordinates;
}

const ReferencedAnnotationVector XmlModelInternal::readXmlNode(AIMXML::CreferencedAnnotationCollectionType& xmlReferencedAnnotations)
{
	ReferencedAnnotationVector referencedAnnotations;
	if (xmlReferencedAnnotations.ReferencedAnnotation.exists())
	{
		for (AIMXML::Iterator<CReferencedAnnotation> iter = xmlReferencedAnnotations.ReferencedAnnotation.all(); iter; ++iter)
		{
			ReferencedAnnotation referencedAnnotation;
			referencedAnnotation.SetReferencedAnnotationUID(iter->referencedAnnotationUID.exists() ? iter->referencedAnnotationUID : _emptyStr);

			if (iter->annotationRole.exists() && iter->annotationRole.first().AnnotationRole.exists())
			{
				CAnnotationRole xmlAnnotationRole = iter->annotationRole.first().AnnotationRole.first();

				AnnotationRole annotationRole;
				annotationRole.SetCodeValue(xmlAnnotationRole.codeValue.exists() ? xmlAnnotationRole.codeValue : _emptyStr);
				annotationRole.SetCodeMeaning(xmlAnnotationRole.codeMeaning.exists() ? xmlAnnotationRole.codeMeaning : _emptyStr);
				annotationRole.SetCodingSchemeDesignator(xmlAnnotationRole.codingSchemeDesignator.exists() ? xmlAnnotationRole.codingSchemeDesignator : _emptyStr);
				annotationRole.SetCodingSchemeVersion(xmlAnnotationRole.codingSchemeVersion.exists() ? xmlAnnotationRole.codingSchemeVersion : _emptyStr);
				annotationRole.SetRoleSequenceNumber(xmlAnnotationRole.roleSequenceNumber.exists() ? xmlAnnotationRole.roleSequenceNumber : 0);

				referencedAnnotation.SetAnnotationRole(&annotationRole);
			}

			referencedAnnotations.push_back(referencedAnnotation);
		}
	}
	return referencedAnnotations;
}

const TextAnnotationVector XmlModelInternal::readXmlNode(AIMXML::CtextAnnotationCollectionType& xmlReferencedAnnotations)
{
	TextAnnotationVector textAnnotationVectors;

	if (xmlReferencedAnnotations.TextAnnotation.exists())
	{
		for (AIMXML::Iterator<CTextAnnotation> iter = xmlReferencedAnnotations.TextAnnotation.all(); iter; ++iter)
		{
			TextAnnotation textAnnotation;
			textAnnotation.SetFont(iter->font.exists() ? iter->font : _emptyStr);
			textAnnotation.SetFontColor(iter->fontColor.exists() ? iter->fontColor : _emptyStr);
			textAnnotation.SetFontEffect(iter->fontEffect.exists() ? iter->fontEffect : _emptyStr);
			textAnnotation.SetFontSize(iter->fontSize.exists() ? iter->fontSize : _emptyStr);
			textAnnotation.SetFontStyle(iter->fontStyle.exists() ? iter->fontStyle : _emptyStr);
			textAnnotation.SetText(iter->text.exists() ? iter->text : _emptyStr);
			textAnnotation.SetTextJustify(iter->textJustify.exists() ? iter->textJustify : _emptyStr);
			textAnnotation.SetFontOpacity(iter->fontOpacity.exists() ? iter->fontOpacity : _emptyStr);

			if (iter->multiPoint.exists() && iter->multiPoint.first().MultiPoint.exists())
			{
				CMultiPoint xmlMultiPoint = iter->multiPoint.first().MultiPoint.first();
				
				MultiPoint multiPoint;
				multiPoint.SetIncludeFlag(xmlMultiPoint.includeFlag.exists() ? xmlMultiPoint.includeFlag : true);
				multiPoint.SetShapeIdentifier(xmlMultiPoint.shapeIdentifier.exists() ? xmlMultiPoint.shapeIdentifier : -1);
				multiPoint.SetLineColor(xmlMultiPoint.lineColor.exists() ? xmlMultiPoint.lineColor : _emptyStr);
				multiPoint.SetLineOpacity(xmlMultiPoint.lineOpacity.exists() ? xmlMultiPoint.lineOpacity : _emptyStr);
				multiPoint.SetLineStyle(xmlMultiPoint.lineStyle.exists() ? xmlMultiPoint.lineStyle : _emptyStr);
				multiPoint.SetLineThickness(xmlMultiPoint.lineThickness.exists() ? xmlMultiPoint.lineThickness : _emptyStr);

				if (xmlMultiPoint.spatialCoordinateCollection.exists())
				{
					CspatialCoordinateCollectionType xmlSpatialCoordinates = xmlMultiPoint.spatialCoordinateCollection.first();
					SpatialCoordPtrVector spatialCoordinates = this->readXmlNode(xmlSpatialCoordinates);
					multiPoint.SetSpatialCoordinateCollection(spatialCoordinates);
					while(spatialCoordinates.size() > 0)
					{
						delete spatialCoordinates[spatialCoordinates.size() - 1];
						spatialCoordinates.pop_back();
					}
				}

				textAnnotation.SetConnectorPoints(&multiPoint);
			}

			textAnnotationVectors.push_back(textAnnotation);
		}
	}
	return textAnnotationVectors;
}

const SegmentationVector XmlModelInternal::readXmlNode(CsegmentationCollectionType& xmlSegmentations)
{
	SegmentationVector segmentations;

	if (xmlSegmentations.Segmentation.exists())
	{
		for (AIMXML::Iterator<CSegmentation> iter = xmlSegmentations.Segmentation.all(); iter; ++iter)
		{
			Segmentation segmentation;
			segmentation.SetSopInstanceUID(iter->sopInstanceUID.exists() ? iter->sopInstanceUID : _emptyStr);
			segmentation.SetSopClassUID(iter->sopClassUID.exists() ? iter->sopClassUID : _emptyStr);
			segmentation.SetReferencedSopInstanceUID(iter->referencedSopInstanceUID.exists() ? iter->referencedSopInstanceUID : _emptyStr);
			segmentation.SetSegmentNumber((int)iter->segmentNumber);

			if (iter->imagingObservation.exists() && iter->imagingObservation.first().ImagingObservation.exists())
			{
				CImagingObservation xmlImagingObservation = iter->imagingObservation.first().ImagingObservation.first();

				ImagingObservation imagingObservation;
				imagingObservation.SetCodeMeaning(xmlImagingObservation.codeMeaning.exists() ? xmlImagingObservation.codeMeaning : _emptyStr);
				imagingObservation.SetCodeValue(xmlImagingObservation.codeValue.exists() ? xmlImagingObservation.codeValue : _emptyStr);
				imagingObservation.SetCodingSchemeDesignator(xmlImagingObservation.codingSchemeDesignator.exists() ? xmlImagingObservation.codingSchemeDesignator : _emptyStr);
				imagingObservation.SetCodingSchemeVersion(xmlImagingObservation.codingSchemeVersion.exists() ? xmlImagingObservation.codingSchemeVersion : _emptyStr);
				imagingObservation.SetComment(xmlImagingObservation.comment.exists() ? xmlImagingObservation.comment : _emptyStr);
				imagingObservation.SetLabel(xmlImagingObservation.label.exists() ? xmlImagingObservation.label : _emptyStr);
				imagingObservation.SetIsPresent(xmlImagingObservation.isPresent.exists() ? xmlImagingObservation.isPresent : true);
				if (xmlImagingObservation.annotatorConfidence.exists())
				{
					double val = xmlImagingObservation.annotatorConfidence;
					imagingObservation.SetAnnotatorConfidence(&val);
				}

				if (xmlImagingObservation.imagingObservationCharacteristicCollection.exists())
				{
					CimagingObservationCharacteristicCollectionType xmlImagingObservationChars = xmlImagingObservation.imagingObservationCharacteristicCollection.first();
					ImagingObservationCharacteristicVector imagingObservationChars = this->readXmlNode(xmlImagingObservationChars);
					imagingObservation.SetImagingObservationCharacteristicCollection(imagingObservationChars);
				}

				segmentation.SetImagingObservation(&imagingObservation);
			}

			segmentations.push_back(segmentation);
		}
	}
	return segmentations;
}

const InferenceVector XmlModelInternal::readXmlNode(AIMXML::CinferenceCollectionType& xmlInferences)
{
	InferenceVector inferences;
	if (xmlInferences.Inference.exists())
	{
		for (AIMXML::Iterator<CInference> iter = xmlInferences.Inference.all(); iter; ++iter)
		{
			Inference inference;
			inference.SetCodeMeaning(iter->codeMeaning.exists() ? iter->codeMeaning : _emptyStr);
			inference.SetCodeValue(iter->codeValue.exists() ? iter->codeValue : _emptyStr);
			inference.SetCodingSchemeDesignator(iter->codingSchemeDesignator.exists() ? iter->codingSchemeDesignator : _emptyStr);
			inference.SetCodingSchemeVersion(iter->codingSchemeVersion.exists() ? iter->codingSchemeVersion : _emptyStr);
			if (iter->annotatorConfidence.exists())
			{
				double val = iter->annotatorConfidence;
				inference.SetAnnotatorConfidence(&val);
			}
			inference.SetImageEvidence(iter->imageEvidence.exists() ? iter->imageEvidence : false);

			inferences.push_back(inference);
		}
	}
	return inferences;
}

const GeoShapePtrVector XmlModelInternal::readXmlNode(CgeometricShapeCollectionType& xmlGeometricShapes)
{
	GeoShapePtrVector geoShapes;

	if (xmlGeometricShapes.GeometricShape.exists())
	{
		for (AIMXML::Iterator<CGeometricShape> iter = xmlGeometricShapes.GeometricShape.all(); iter; ++iter)
		{
			GeometricShape* pGeoShape = NULL;
			std::string shapeType = this->GetSubClassType(iter->GetNode());
			if("Circle" == shapeType)
				pGeoShape = new Circle();
			else if ("Point" == shapeType)
				pGeoShape = new Point();
			else if ("Ellipse" == shapeType)
				pGeoShape = new Ellipse();
			else if ("MultiPoint" == shapeType)
				pGeoShape = new MultiPoint();
			else if ("Polyline" == shapeType)
				pGeoShape = new Polyline();
			else
				assert(false);

			// We can treat all classes the same because derived classes have no additional attributes
			if (pGeoShape != NULL)
			{
				pGeoShape->SetIncludeFlag(iter->includeFlag.exists() ? iter->includeFlag : true);
				pGeoShape->SetShapeIdentifier(iter->shapeIdentifier.exists() ? iter->shapeIdentifier : -1);
				pGeoShape->SetLineColor(iter->lineColor.exists() ? iter->lineColor : _emptyStr);
				pGeoShape->SetLineOpacity(iter->lineOpacity.exists() ? iter->lineOpacity : _emptyStr);
				pGeoShape->SetLineStyle(iter->lineStyle.exists() ? iter->lineStyle : _emptyStr);
				pGeoShape->SetLineThickness(iter->lineThickness.exists() ? iter->lineThickness : _emptyStr);

				if (iter->spatialCoordinateCollection.exists())
				{
					CspatialCoordinateCollectionType xmlSpatialCoordinates = iter->spatialCoordinateCollection.first();
					SpatialCoordPtrVector spatialCoordinates = this->readXmlNode(xmlSpatialCoordinates);
					pGeoShape->SetSpatialCoordinateCollection(spatialCoordinates);
					while(spatialCoordinates.size() > 0)
					{
						delete spatialCoordinates[spatialCoordinates.size() - 1];
						spatialCoordinates.pop_back();
					}
				}

				geoShapes.push_back(pGeoShape);
			}
		}
	}
	return geoShapes;
}

const SpatialCoordPtrVector XmlModelInternal::readXmlNode(CspatialCoordinateCollectionType& xmlSpatialCoordinates)
{
	SpatialCoordPtrVector spatialCoords;

	if (xmlSpatialCoordinates.SpatialCoordinate.exists())
	{
		for (AIMXML::Iterator<CSpatialCoordinate> iter = xmlSpatialCoordinates.SpatialCoordinate.all(); iter; ++iter)
		{
			std::string coordType = this->GetSubClassType(iter->GetNode());
			if (coordType == "TwoDimensionSpatialCoordinate")
			{
				CTwoDimensionSpatialCoordinate xmlSpatialCoord(iter->GetNode());

				TwoDimensionSpatialCoordinate spatialCoord2D;
				spatialCoord2D.SetCoordinateIndex(xmlSpatialCoord.coordinateIndex.exists() ? xmlSpatialCoord.coordinateIndex : -1);
				spatialCoord2D.SetImageReferenceUID(xmlSpatialCoord.imageReferenceUID.exists() ? xmlSpatialCoord.imageReferenceUID : _emptyStr);
				spatialCoord2D.SetReferencedFrameNumber(xmlSpatialCoord.referencedFrameNumber.exists() ? (long)xmlSpatialCoord.referencedFrameNumber : 0);
				spatialCoord2D.SetX(xmlSpatialCoord.x.exists() ? xmlSpatialCoord.x : 0.0f);
				spatialCoord2D.SetY(xmlSpatialCoord.y.exists() ? xmlSpatialCoord.y : 0.0f);

				spatialCoords.push_back(spatialCoord2D.Clone());
			}
			else if (coordType == "ThreeDimensionSpatialCoordinate")
			{
				CThreeDimensionSpatialCoordinate xmlSpatialCoord(iter->GetNode());

				ThreeDimensionSpatialCoordinate spatialCoord3D;
				spatialCoord3D.SetCoordinateIndex(xmlSpatialCoord.coordinateIndex.exists() ? xmlSpatialCoord.coordinateIndex : -1);
				spatialCoord3D.SetFrameOfReferenceUID(xmlSpatialCoord.frameOfReferenceUID.exists() ? xmlSpatialCoord.frameOfReferenceUID : _emptyStr);
				spatialCoord3D.SetX(xmlSpatialCoord.x.exists() ? xmlSpatialCoord.x : 0.0f);
				spatialCoord3D.SetY(xmlSpatialCoord.y.exists() ? xmlSpatialCoord.y : 0.0f);
				spatialCoord3D.SetZ(xmlSpatialCoord.z.exists() ? xmlSpatialCoord.z : 0.0f);

				spatialCoords.push_back(spatialCoord3D.Clone());
			}
			else
				assert(false); // Unknown spatial coordinate type

		}
			
		// Sort coordinates according to their CoordianteIndex
		std::sort(spatialCoords.begin(), spatialCoords.end(), SpatialCoordinate::SpatialCoordinateSortPredicate);
	}
	return spatialCoords;
}

const std::string XmlModelInternal::GetSubClassType(xercesc::DOMNode *pNode)
{
	if (pNode == NULL || pNode->getAttributes() == NULL)
		return "";

//	return altova::CNode::GetNodeTextValue(pNode->getAttributes()->getNamedItem(L"xsi:type"));

	std::vector<string_type> nsPrefixes;

	string_type nsPrefix = XercesUnstringTemp(pNode->getPrefix());
	string_type classType = XercesUnstringTemp(pNode->getAttributes()->getNamedItem(XercesStringTemp(_T("xsi:type")))->getNodeValue());

	if (!nsPrefix.empty())
		nsPrefixes.push_back(nsPrefix);

	// Find all xmlns:xyz attributes and collect their local names
	const static string_type xmlns("xmlns");
	xercesc::DOMNamedNodeMap* pAttrs = pNode->getAttributes();
	for(XMLSize_t i=0; i < pAttrs->getLength(); i++)
	{
		xercesc::DOMNode* pAttr = pAttrs->item(i);
		nsPrefix = XercesUnstringTemp(pAttr->getPrefix());
		if (nsPrefix == xmlns)
		{
			string_type localName = XercesUnstringTemp(pAttr->getLocalName());
			nsPrefixes.push_back(localName);
		}
	}

	// Remove namespace prefix from type value
	for (std::vector<string_type>::iterator iter = nsPrefixes.begin(); iter < nsPrefixes.end(); iter++)
	{
		nsPrefix = iter->c_str();
		if (classType.find(nsPrefix) == 0)
			return classType.substr(nsPrefix.size() + 1);
	}

	return classType;
	//return nsPrefix.empty() ? classType : classType.substr(nsPrefix.size() + 1);
}
