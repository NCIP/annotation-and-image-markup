/*
Copyright (c) 2008-2013, Northwestern University
All rights reserved.
 
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
 
  Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
 
  Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.
 
  Neither the name of the Northwestern University nor the names of its contributors
  may be used to endorse or promote products derived from this software
  without specific prior written permission.
 
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "../stdafx.h"
#include "DcmModelInternal.h"

#include "../AIMUtil.h"
#include "../AIMCodes.h"

#include "BaseModel.h" // for AIM MODEL VERSION

#include "../memdebug.h"

#include <stdexcept>

using namespace aim_lib;

DcmModelInternal::DcmModelInternal(const std::string& uidPrefix) : _pDoc(NULL){
	_uidPrefix = uidPrefix;
}

DcmModelInternal::~DcmModelInternal(void){
	if (_pDoc != NULL)
	{
		delete _pDoc;
		_pDoc = NULL;
	}
}

OFCondition DcmModelInternal::WriteDocToFile(const DSRDocument& dsrdoc, const std::string& fileName){
	assert(!fileName.empty());
	if (fileName.empty())
	{
		printDebug("DICOM SR output file name cannot be empty");
		return EC_IllegalParameter;
	}

	DcmFileFormat fileformat;
	OFCondition result = const_cast<DSRDocument&>(dsrdoc).write(*fileformat.getDataset());
    if (result.good())
        result = fileformat.saveFile(fileName.data(), EXS_LittleEndianExplicit, EET_ExplicitLength, EGL_recalcGL, EPD_withoutPadding);

	return result;
}

DSRDocument* DcmModelInternal::CreateDSRDocument(const AnnotationCollection& annotationCollection, std::ostream* outputFile)
{
	DSRDocument* pDoc = new DSRDocument(DSRTypes::DT_Comprehensive3DSR); // NOTE: we're using Supp162 Comprehensive 3D SR

	if (!pDoc)
		return NULL;

#ifdef _DEBUG
	// Send log messages to the output window
	// DCMTK 3.6.0+ - use filelog.cfg to control output
//	pDoc->setLogStream(&ofConsole);
#endif

	// GENERAL NOTE:
	// Though we claim to support multiple annotations per document, 
	// XML version can really store only one annotation.
	// There is no annotation container element in the model.
	// But the DICOM template is desinged to accomodate multiple annotations.
	// So, while this code continues to support multiple annotations,
	// there should only be one submitted.


	// Set known SR header values
	DicomTagCollection localHeaderValues;
	this->InitilializeHeaderValues(annotationCollection, localHeaderValues);

	// 1. Create document's DICOM headers
	this->CreateDSRDocumentHeaders(*pDoc, localHeaderValues);

	// 2.  Create AIM SR Container
	this->CreateAimSRContainer(annotationCollection, *pDoc);

	// 3. Add annotations to the SR container
	switch(annotationCollection.GetAnnotationCollectionType())
	{
	case AnnotationCollection::ACT_ImageAnnotationCollection:
		{
			const ImageAnnotationCollection* pImgAnnColl = static_cast<const ImageAnnotationCollection*>(&annotationCollection);
			for (ImageAnnotationVector::const_iterator iter = pImgAnnColl->GetImageAnnotations().begin(); iter < pImgAnnColl->GetImageAnnotations().end(); iter++)
				this->PopulateImageAnnotation(*iter, *pDoc);
		}
		break;
	case AnnotationCollection::ACT_AnnotationOfAnnotationCollection:
		{
			const AnnotationOfAnnotationCollection* pAnnOfAnnColl = static_cast<const AnnotationOfAnnotationCollection*>(&annotationCollection);
			for (AnnotationOfAnnotationVector::const_iterator iter = pAnnOfAnnColl->GetAnnotationOfAnnotations().begin(); iter < pAnnOfAnnColl->GetAnnotationOfAnnotations().end(); iter++)
				this->PopulateAnnotationOfAnnotation(*iter, *pDoc);
		}
		break;
	default:
		assert(false); // Unknown annotation
		throw std::invalid_argument(_T("Failed to create DICOM document. Unknown annotation collection type"));
	}

	// Debug Code
	bool validFlag = pDoc->isValid();
	char buf[255];
	sprintf(buf, _T("Document is %sValid"), validFlag ? _T("") : _T("NOT "));
	printDebug(buf);
	//contentTree.dicomToReadableDate printMessage(&ofConsole, buf);
	//pDoc->print(&ofConsole, buf);

	// Dump current doc to the console
	ofCondition = pDoc->print(std::cout);

	// Dump doc's context as XML as well
	if (!outputFile)
	{
		printDebug("");
		printDebug("================= Doc's XML: ==================");
		printDebug("");
		pDoc->writeXML(std::cout);
	}
	else
		pDoc->writeXML(*outputFile);

	return pDoc;
}

// This method tries to give reasonable defaults to some SR Document "header" values
// EX: If it is an Image Annotation Collection and all annotations belong to the same study, SR will belong to the same study
void DcmModelInternal::InitilializeHeaderValues(const AnnotationCollection& annotationCollection, DicomTagCollection& headerValues){
	std::string studyInstanceUid;

	if (annotationCollection.GetEquipment())
	{
		// NOTE: For AnnotationOfAnnotation SetHeaderTag will asssert when mixing annotation from different sources
		this->SetHeaderTag(headerValues, DicomTagCollection::ADT_MANUFACTURE, annotationCollection.GetEquipment()->GetManufacturerName());
		this->SetHeaderTag(headerValues, DicomTagCollection::ADT_MANUFACTURES_MODEL_NAME, annotationCollection.GetEquipment()->GetManufacturerModelName());
		this->SetHeaderTag(headerValues, DicomTagCollection::ADT_DEVICE_SERIAL_NUMBER, annotationCollection.GetEquipment()->GetDeviceSerialNumber());
		this->SetHeaderTag(headerValues, DicomTagCollection::ADT_SOFTWARE_VERSIONS, annotationCollection.GetEquipment()->GetSoftwareVersion());
	}

	if (annotationCollection.GetAnnotationCollectionType() == AnnotationCollection::ACT_ImageAnnotationCollection)
	{
		const ImageAnnotationCollection* pImgAnnColl = static_cast<const ImageAnnotationCollection*>(&annotationCollection);
		const Person* person = pImgAnnColl->GetPerson();
		if (person)
		{
			this->SetHeaderTag(headerValues, DicomTagCollection::ADT_PATIENT_ID, person->GetId());
			this->SetHeaderTag(headerValues, DicomTagCollection::ADT_PATIENTS_NAME, person->GetName());
			if (person->GetBirthDate() != aim_lib::Date())
				this->SetHeaderTag(headerValues, DicomTagCollection::ADT_PATIENTS_BIRTH_DATE, person->GetBirthDate().GetDicomFormatedDate());
			if (!person->GetSex().empty())
				this->SetHeaderTag(headerValues, DicomTagCollection::ADT_PATIENT_SEX, person->GetSex());
			if (!person->GetEthnicGroup().empty())
				this->SetHeaderTag(headerValues, DicomTagCollection::ADT_PATIENT_ETHNIC_GROUP, person->GetEthnicGroup());
		}

		// DICOM NOTE: Study Instance UID of all images must match
		// Find Study Instance UID
		for (ImageAnnotationVector::const_iterator imgAnnIter = pImgAnnColl->GetImageAnnotations().begin(); imgAnnIter < pImgAnnColl->GetImageAnnotations().end(); imgAnnIter++)
		{
			for (ImageReferenceEntityPtrVector::const_iterator imgIter = imgAnnIter->GetImageReferenceEntityCollection().begin(); imgIter < imgAnnIter->GetImageReferenceEntityCollection().end(); imgIter++)
			{
				if ((*imgIter)->GetImageReferenceEntityType() == ImageReferenceEntity::T_DICOM_IMAGE_REF)
				{
					const DicomImageReferenceEntity* pDicomImgRef = (const DicomImageReferenceEntity*)*imgIter;
					if (studyInstanceUid.empty())
						studyInstanceUid = pDicomImgRef->GetImageStudy().GetInstanceUid().toString();
					else
					{
						if (studyInstanceUid != pDicomImgRef->GetImageStudy().GetInstanceUid().toString()) // annotation images have to belong to the same study
						{
							assert(false);
							throw std::runtime_error(_T("All DICOM images in a single Image Annotation Collection must belong to the same Study (have the same Study Instance UID)"));
						}
					}
				}
			}
		}
	}
	else
	{
		// NO-OP
	}

	if (studyInstanceUid.empty())
		studyInstanceUid = AimUidGenerator::GenerateNewUid(_uidPrefix);

	this->SetHeaderTag(headerValues, DicomTagCollection::ADT_STUDY_INSTANCE_UID, studyInstanceUid);


	// -- OLD --
	//bool hasOnlyImgAnnotations = true;

	//// NOTE:
	//// In addition to setting the values, this code includes basic sanity checks.
	//// Though nothing prevents users from creating semanticly invalid objects,
	//// debug builds assert some consistency by going through all available annotations and testing for a few basic things:
	//// - image annotation has to have images from the same study
	//for(AnnotationPtrVector::const_iterator iter = annotations.begin(); iter < annotations.end(); iter++)
	//{
	//	const Annotation* pAnnotation = *iter;

	//	bool isImageAnnotation = pAnnotation->GetAnnotationKind() == Annotation::AK_ImageAnnotation;
	//	hasOnlyImgAnnotations = hasOnlyImgAnnotations && isImageAnnotation;

	//	// Equipment
	//	if (pAnnotation->GetEquipment() != NULL)
	//	{
	//		// NOTE: For AnnotationOfAnnotation SetHeaderTag will asssert when mixing annotation from different sources
	//		this->SetHeaderTag(headerValues, DicomTagCollection::ADT_MANUFACTURE, pAnnotation->GetEquipment()->GetManufacturerName());
	//		this->SetHeaderTag(headerValues, DicomTagCollection::ADT_MANUFACTURES_MODEL_NAME, pAnnotation->GetEquipment()->GetManufacturerModelName());
	//		this->SetHeaderTag(headerValues, DicomTagCollection::ADT_SOFTWARE_VERSIONS, pAnnotation->GetEquipment()->GetSoftwareVersion());
	//	}

	//	if (isImageAnnotation)
	//	{
	//		const ImageAnnotation* pImgAnnotation = (const ImageAnnotation*)pAnnotation;

	//		// Patient Info
	//		//if (pImgAnnotation->GetPatient() != NULL)
	//		{
	//			Person patient = pImgAnnotation->GetPatient();
	//			this->SetHeaderTag(headerValues, DicomTagCollection::ADT_PATIENT_ID, patient.GetId());
	//			this->SetHeaderTag(headerValues, DicomTagCollection::ADT_PATIENTS_NAME, patient.GetName());
	//			if (patient.GetBirthDate() != aim_lib::Date())
	//				this->SetHeaderTag(headerValues, DicomTagCollection::ADT_PATIENTS_BIRTH_DATE, patient.GetBirthDate().GetDicomFormatedDate());
	//			if (!patient.GetSex().empty())
	//				this->SetHeaderTag(headerValues, DicomTagCollection::ADT_PATIENT_SEX, patient.GetSex());
	//			if (!patient.GetEthnicGroup().empty())
	//				this->SetHeaderTag(headerValues, DicomTagCollection::ADT_PATIENT_ETHNIC_GROUP, patient.GetEthnicGroup());
	//		}

	//		// Set Study Instance UID
	//		std::string studyUID;
	//		for (ImageReferencePtrVector::const_iterator imgIter = pImgAnnotation->GetImageReferenceCollection().begin(); imgIter < pImgAnnotation->GetImageReferenceCollection().end(); imgIter++)
	//		{
	//			if ((*imgIter)->GetImageReferenceType() == ImageReference::T_DICOM_IMAGE_REF)
	//			{
	//				const DICOMImageReference* pDicomImgRef = (const DICOMImageReference*)*imgIter;
	//				if (studyUID.empty())
	//					studyUID = pDicomImgRef->GetStudy().GetInstanceUID();
	//				else
	//					assert(studyUID == pDicomImgRef->GetStudy().GetInstanceUID()); //single annotation images have to belong to the same study
	//				if (hasOnlyImgAnnotations)
	//					this->SetHeaderTag(headerValues, DicomTagCollection::ADT_STUDY_INSTANCE_UID, pDicomImgRef->GetStudy().GetInstanceUID());
	//			}
	//		}
	//	}
	//}

	//// Mixed annotaion types have new Study Instance UID
	//if (!hasOnlyImgAnnotations)
	//{
	//	headerValues.RemoveTag(DicomTagCollection::ADT_STUDY_INSTANCE_UID);
	//	headerValues.SetTagValue(DicomTagCollection::ADT_STUDY_INSTANCE_UID, AimUidGenerator::GenerateNewUid(_uidPrefix));
	//}
}

// If available, sets given tag's value in the DicomTagCollection.
// Asserts that the proposed new tag value is not conflicting with an existing value.
void DcmModelInternal::SetHeaderTag(DicomTagCollection& headerValues, const DicomTagCollection::AIM_DCM_TAG& tag, const std::string& tagValue)
{
	if (!tagValue.empty())
	{
		std::string existingTagVal = headerValues.GetTagValue(tag);
		if (existingTagVal.empty())
			headerValues.SetTagValue(tag, tagValue);
		else if (AIMUtil::compareNoCase(existingTagVal, tagValue) != 0)
			assert(false); // inconsistency - differs from the previous value
	}
}

void DcmModelInternal::printDebug(const char* message)
{
#ifdef _DEBUG
	if (message != NULL)
	{
		if (strlen(message) > 0)
			ofConsole.lockCerr() << "AIM Output: " << message << std::endl;
		else
			ofConsole.lockCerr() << std::endl;
		ofConsole.unlockCerr();
	}
#endif
}

void DcmModelInternal::CreateDSRDocumentHeaders(DSRDocument& doc, const DicomTagCollection& headerValues)
{
//	OFCondition setCondition;

	ofCondition = doc.setSpecificCharacterSetType(DSRTypes::CS_Latin1); // TODO
//	ofCondition = doc.setSpecificCharacterSetType(DSRTypes::CS_UTF8);  // UTF-8

	//
	// General Study module headers
	//
	// Study Instance UID
	ofString.assign(headerValues.GetTagValue(DicomTagCollection::ADT_STUDY_INSTANCE_UID).data());
	THROW_IF_EMPTY(ofString); // Type 1
	doc.createNewSeriesInStudy(ofString);
	// Series Description - generated automatically
	ofString = _T("AIM DICOM SR");
	ofString.append(_T(" "));
	ofString.append(BaseModel::AIM_MODEL_VERSION);
	doc.setSeriesDescription(ofString);
	// Series Number - always 1
	ofString.assign(_T("1"));
	doc.setSeriesNumber(ofString);
	// Referring Physician's Name
	ofString.assign(headerValues.GetTagValue(DicomTagCollection::ADT_REFERRING_PHYSICIANS_NAME).data());
	if (!ofString.empty()) doc.setReferringPhysicianName(ofString);
	// Study ID
	ofString.assign(headerValues.GetTagValue(DicomTagCollection::ADT_STUDY_ID).data());
	if (!ofString.empty()) doc.setStudyID(ofString);
	// Accession number
	ofString.assign(headerValues.GetTagValue(DicomTagCollection::ADT_ACCESSION_NUMBER).data());
	if (!ofString.empty()) doc.setAccessionNumber(ofString);
	// Study Description
	ofString.assign(headerValues.GetTagValue(DicomTagCollection::ADT_STUDY_DESCRIPTION).data());
	if (!ofString.empty()) doc.setStudyDescription(ofString);

	//// Date/Time
	////OFDateTime annDateTime = AIMUtil::DateTimeConvert(annotation.GetDateTime());
	////annDateTime = annDateTime.isValid() ? annDateTime : OFDateTime::getCurrentDateTime();
	//OFDateTime annDateTime = OFDateTime::getCurrentDateTime();
	////ofCondition = DcmDateTime::getDicomDateTimeFromOFDateTime(annDateTime, ofString);
	////if (ofCondition.good())
	//if (annDateTime.getDate().getISOFormattedDate(ofString, false)) // YYYYMMDD
	//	ofCondition = doc.setContentDate(ofString);
	//if (annDateTime.getTime().getISOFormattedTime(ofString, true, false, false, false)) // HHMMSS
	//	ofCondition = doc.setContentTime(ofString);

	//
	// Patient module headers
	//
	// Patient Name - Type 2. Empty string is an acceptible value.
	ofString.assign(headerValues.GetTagValue(DicomTagCollection::ADT_PATIENTS_NAME).data());
	doc.setPatientName(ofString);
	// Patient ID - Type 2. Empty string is an acceptible value.
	ofString.assign(headerValues.GetTagValue(DicomTagCollection::ADT_PATIENT_ID).data());
	doc.setPatientID(ofString);
	// Issuer of Patient ID - Type 3
//	ofString.assign(headerValues.GetTagValue(DicomTagCollection::ADT_ISSUER_OF_PATIENT_ID).data());
//	if (ofString.length() > 0)
//	{
//		DcmLongString* pLongText = new DcmLongString(DCM_IssuerOfPatientID);
//		pLongText->putString(ofString.c_str());
////		ofCondition = doc.addElementToDataset(setCondition, doc., pLongText);
//	}
	// Patient's Birth Date
	ofString.assign(headerValues.GetTagValue(DicomTagCollection::ADT_PATIENTS_BIRTH_DATE).data());
	if (!ofString.empty()) ofCondition = doc.setPatientBirthDate(ofString);
	// Patient Sex
	ofString.assign(headerValues.GetTagValue(DicomTagCollection::ADT_PATIENT_SEX).data());
	if (!ofString.empty()) ofCondition = doc.setPatientSex(ofString);
	// Patient Ethnic Group
	ofString.assign(headerValues.GetTagValue(DicomTagCollection::ADT_PATIENT_ETHNIC_GROUP).data());
	if (!ofString.empty()) ofCondition = doc.setEthnicGroup(ofString);

	//
	// General Equipment Module
	//
	ofString.assign(headerValues.GetTagValue(DicomTagCollection::ADT_MANUFACTURE).data());
	if (!ofString.empty()) doc.setManufacturer(ofString);
	// Modified DCMTK for these values:
	ofString.assign(headerValues.GetTagValue(DicomTagCollection::ADT_MANUFACTURES_MODEL_NAME).data());
	if (!ofString.empty()) doc.setManufacturerModelName(ofString);
	ofString.assign(headerValues.GetTagValue(DicomTagCollection::ADT_SOFTWARE_VERSIONS).data());
	if (!ofString.empty()) doc.setSoftwareVersions(ofString);
	ofString.assign(headerValues.GetTagValue(DicomTagCollection::ADT_DEVICE_SERIAL_NUMBER).data());
	if (!ofString.empty()) doc.setDeviceSerialNumber(ofString);
	// Missing from standard DCMTK's dsrdoc.cxx/.h:
	// - Institution Name
	// - Institution Address
	// - Station Name
	// - Intitutional Department Name
	// - Manufacture's Model Name
	// - Device Serial Number
	// - Software Version

}

void DcmModelInternal::CreateAimSRContainer(const AnnotationCollection& annotationCollection, DSRDocument& doc)
{
	// Create Document
	nodeId = doc.getTree().addContentItem(DSRTypes::RT_isRoot, DSRTypes::VT_Container);
	ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz001", "AIM SR Report"));

	// Date Time of the Collection is stored in the container
	OFDateTime annCollDateTime = AIMUtil::DateTimeConvert(annotationCollection.GetDateTime());
	OFString ofDateTime; // YYYYMMDDHHMMSS
	if (annCollDateTime.isValid() && annCollDateTime.getISOFormattedDateTime(ofDateTime, true, false, false, false))
		ofCondition = doc.getTree().getCurrentContentItem().setObservationDateTime(ofDateTime);

	// Unique Identifier
	AddDsrItem(doc, DSRCodedEntryValue("112040", "DCM", "Tracking Unique Identifier"), annotationCollection.GetUniqueIdentifier(), DSRTypes::RT_hasAcqContext, DSRTypes::AM_belowCurrent);

	// AIM Version
	AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz003", "AIM Version"), AimEnum::GetAimVersionString(annotationCollection.GetAimVersion()), DSRTypes::RT_hasAcqContext);

	// Description
	if (!annotationCollection.GetDescription().empty())
		AddDsrItem(doc, DSRCodedEntryValue("C25365", "NCI", "Description"), annotationCollection.GetDescription(), DSRTypes::RT_hasAcqContext);

	// Language of content items and descendants
	// TODO

	// Observer context
	if (annotationCollection.GetUser())
		this->FillObserverInfo(*annotationCollection.GetUser(), doc);


	if (annotationCollection.GetAnnotationCollectionType() == AnnotationCollection::ACT_ImageAnnotationCollection)
	{
		const ImageAnnotationCollection* pImgAnnColl = static_cast<const ImageAnnotationCollection*>(&annotationCollection);
		for(ImageAnnotationVector::const_iterator iter = pImgAnnColl->GetImageAnnotations().begin(); iter < pImgAnnColl->GetImageAnnotations().end(); iter++)
		{
			this->FillImageLibrary((*iter), doc);
		}
	}
}

void DcmModelInternal::FillObserverInfo(const User& user, DSRDocument& doc)
{
	// NOTE: observer is always a person for now

	// Person Observer Type
	AddDsrItem(doc, DSRCodedEntryValue("121005", "DCM", "Observer Type"), DSRCodedEntryValue("121006", "DCM", "Person"), DSRTypes::RT_hasObsContext);

	bool isNested = false; // Flag which indicates if nesting has occured yet or not

	// Name
	ofString.assign(user.GetName().c_str());
	if (ofString.empty())
	{
		assert(false); // Name must be present
	}
	else
	{
		nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasObsContext, DSRTypes::VT_PName, isNested ? DSRTypes::AM_afterCurrent : DSRTypes::AM_belowCurrent);
		ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("121008", "DCM", "Person Observer Name"));
		ofCondition = doc.getTree().getCurrentContentItem().setStringValue(ofString);
		isNested = true;
	}

	// Organization name
	// N/A

	// Pesron Observer's Role in the Organization
	// N/A

	// Person's Role in this procedure
	if (!user.GetRoleInTrial().empty())
	{
		_dsrCode = AIMCodes::GetPerformingRoleValue(user.GetRoleInTrial());
		if (_dsrCode == AIMCodes::EmptyCodedEntryValue)
		{
			std::string errString = std::string("Invalid  observer role: ") + user.GetRoleInTrial() + ".";
			printDebug(errString.c_str());
		}
		else
		{
			AddDsrItem(doc, DSRCodedEntryValue("121011", "DCM", "Person Observer's Role in this Procedure"), _dsrCode, DSRTypes::RT_hasObsContext, isNested ? DSRTypes::AM_afterCurrent : DSRTypes::AM_belowCurrent);
			isNested = true;
		}
	}

	// Observer Login
	ofString.assign(user.GetLoginName().c_str());
	if (ofString.empty())
	{
		assert(false); // login name is required
	}
	else
	{
		AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz026", "Person Observer's Login Name"), ofString, DSRTypes::RT_hasObsContext, isNested ? DSRTypes::AM_afterCurrent : DSRTypes::AM_belowCurrent);
		isNested = true;
	}

	// Observer Role Number in Trial
	if (user.GetNumberWithinRoleOfClinicalTrial() >= 0)
	{
		AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz045", "Identifier within Person Observer's Role"), AIMUtil::IntToString(user.GetNumberWithinRoleOfClinicalTrial()), DSRTypes::RT_hasObsContext, isNested ? DSRTypes::AM_afterCurrent : DSRTypes::AM_belowCurrent);
		isNested = true;
	}

	if(isNested)
		nodeId = doc.getTree().goUp(); // step out of the nesting container
}

void DcmModelInternal::FillImageLibrary(const ImageAnnotation& imgAnnotation, DSRDocument& doc)
{
	const ImageReferenceEntityPtrVector& imgReferences = imgAnnotation.GetImageReferenceEntityCollection();
	assert(imgReferences.size() > 0); // ImageAnnotation must have an image reference

	if (imgReferences.size() < 1)
		return;

	// If multiple annotations are saved in the same SD document,
	// images need to be added to an existing image library.
	size_t initialId = doc.getTree().getNodeID();

	size_t lookedupNode = doc.getTree().gotoNamedNode(DSRCodedEntryValue("111028", "DCM", "Image Library"));
	bool hadExistingImgLib = 0 != lookedupNode;
	if (hadExistingImgLib)
	{
		// Position current node to be the last node in the Image Library
		nodeId = doc.getTree().goDown(); // step into Image Reference container. Assumes that we start at the Image Ref. Container level
		while(nodeId > 0 && doc.getTree().gotoNext() != 0)
			; // move to the last image reference
	}
	else
	{
		// Reset current node - failed gotoNode() resets to the top of the tree
		nodeId = doc.getTree().gotoNode(initialId);
		assert(nodeId == initialId);

		// Add Image Library container
		nodeId = doc.getTree().addContentItem(DSRTypes::RT_contains, DSRTypes::VT_Container);
		ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("111028", "DCM", "Image Library"));
	}

	// NOTE: We are creating 3 different types of image library entries here

	size_t imgContainerId = nodeId;
	for(ImageReferenceEntityPtrVector::const_iterator iter = imgReferences.begin(); iter < imgReferences.end(); iter++)
	{
		// TODO - make sure to add only UNIQUE image references
		if ((*iter)->GetImageReferenceEntityType() == ImageReferenceEntity::T_DICOM_IMAGE_REF)
		{
			const DicomImageReferenceEntity* pDicomImgRef = static_cast<const DicomImageReferenceEntity*>(*iter);

			// 1. make sure that this image reference is not in the image library yet
			//DSRCodedEntryValue("111028", "DCM", "Image Library")
			//DSRImageReferenceValue dsrImage = DSRImageReferenceValue("SOPClassUID", pDicomImgRef->GetDicomSOPInstanceUID().data());
			//nodeId = doc.getTree().gotoNamedNode(dsrImage);

			const ImageStudy& currentStudy = pDicomImgRef->GetImageStudy();
			const ImageSeries& currentSeries = currentStudy.GetImageSeries();
			const ImageVector& images = currentSeries.GetImageCollection();
			for(ImageVector::const_iterator imgIter = images.begin(); imgIter < images.end(); imgIter++)
			{
				// 1. Image Library Entry for DICOM Images
				if (!hadExistingImgLib && iter == imgReferences.begin() && imgIter == images.begin())
					nodeId = doc.getTree().addContentItem(DSRTypes::RT_contains, DSRTypes::VT_Image, DSRTypes::AM_belowCurrent);
				else
					nodeId = doc.getTree().addContentItem(DSRTypes::RT_contains, DSRTypes::VT_Image);
				ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz034", "Image Library Entry"));
				ofCondition = doc.getTree().getCurrentContentItem().setImageReference(DSRImageReferenceValue(imgIter->GetSopClassUid().toString(), imgIter->GetSopInstanceUid().toString()));

				// Only the first inner item should be nested one level deep. The rest are on the same level
				DSRTypes::E_AddMode nextAddMode = DSRTypes::AM_belowCurrent;

				// 2. Image Reference Entity UID
				nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasAcqContext, DSRTypes::VT_UIDRef, nextAddMode);
				ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("112040", "DCM", "Tracking Unique Identifier"));
				ofString.assign((*iter)->GetUniqueIdentifier().toString());
				ofCondition = doc.getTree().getCurrentContentItem().setStringValue(ofString);

				nextAddMode = DSRTypes::AM_afterCurrent;

				// Annotation UID
				AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz152", "Annotation UID"), imgAnnotation.GetUniqueIdentifier(), DSRTypes::RT_hasAcqContext, nextAddMode);

				// Study Instance UID
				nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasAcqContext, DSRTypes::VT_UIDRef, nextAddMode);
				ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("110180", "DCM", "Study Instance UID"));
				ofCondition = doc.getTree().getCurrentContentItem().setStringValue(currentStudy.GetInstanceUid().toString());

				// Study Date
				if (currentStudy.GetStartDate() != Date())
				{
					OFDate ofStartDate = AIMUtil::DateConvert(currentStudy.GetStartDate());
					if (ofStartDate.getISOFormattedDate(ofString, false))
					{
						nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasAcqContext, DSRTypes::VT_Date, nextAddMode);
						ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("111060", "DCM", "Study Date"));
						ofCondition = doc.getTree().getCurrentContentItem().setStringValue(ofString);
					}
				}

				// Study Time
				if (currentStudy.GetStartTime() != Time())
				{
					OFTime ofStartTime = AIMUtil::TimeConvert(currentStudy.GetStartTime());
					if (ofStartTime.getISOFormattedTime(ofString, true, false, false, false))
					{
						nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasAcqContext, DSRTypes::VT_Time, nextAddMode);
						ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("111061", "DCM", "Study Time"));
						ofCondition = doc.getTree().getCurrentContentItem().setStringValue(ofString);
					}
				}

				// Procedure Description
				if (!currentStudy.GetProceduDescription().empty())
				{
					nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasAcqContext, DSRTypes::VT_Text, nextAddMode);
					ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("121065", "DCM", "Procedure Description"));
					ofCondition = doc.getTree().getCurrentContentItem().setStringValue(currentStudy.GetProceduDescription().c_str());
				}

				// Series Instance UID
				nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasAcqContext, DSRTypes::VT_UIDRef, nextAddMode);
				ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("112002", "DCM", "Series Instance UID"));
				ofCondition = doc.getTree().getCurrentContentItem().setStringValue(currentSeries.GetInstanceUid().toString().c_str());

				// Modality
				nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasAcqContext, DSRTypes::VT_Code, nextAddMode);
				ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("121139", "DCM", "Modality"));
				ofCondition = doc.getTree().getCurrentContentItem().setCodeValue(AIMCodes::CreateCodedEntryValueFromCd(currentSeries.GetModality()));

				const GeneralImage* pGenImage = imgIter->GetGeneralImage();
				if (pGenImage)
				{
					// Patient Orientation Row
					ofString.assign(pGenImage->GetPatientOrientationRow());
					if (ofString.length() > 0)
					{
						nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasAcqContext, DSRTypes::VT_Text, nextAddMode);
						ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("111044", "DCM", "Patient Orientation Row"));
						ofCondition = doc.getTree().getCurrentContentItem().setStringValue(ofString);
					}

					// Patient Orientation Column
					ofString.assign(pGenImage->GetPatientOrientationColumn());
					if (ofString.length() > 0)
					{
						nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasAcqContext, DSRTypes::VT_Text, nextAddMode);
						ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("111043", "DCM", "Patient Orientation Column"));
						ofCondition = doc.getTree().getCurrentContentItem().setStringValue(ofString);
					}
				}

				const ImagePlane* pImgPlane = imgIter->GetImagePlane();
				if (pImgPlane)
				{
					// Image Orientaion Row X
					if (pImgPlane->GetRowImageOrientationX())
					{
						nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasAcqContext, DSRTypes::VT_Num, nextAddMode);
						ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz142", "Image Orientation Row X"));
						ofString.assign(AIMUtil::DoubleToString(*pImgPlane->GetRowImageOrientationX()));
						ofCondition = doc.getTree().getCurrentContentItem().setNumericValue(DSRNumericMeasurementValue(ofString, AIMCodes::GetUcumCodeValue("mm")));
					}

					// Image Orientaion Row Y
					if (pImgPlane->GetRowImageOrientationY())
					{
						nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasAcqContext, DSRTypes::VT_Num, nextAddMode);
						ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz143", "Image Orientation Row Y"));
						ofString.assign(AIMUtil::DoubleToString(*pImgPlane->GetRowImageOrientationY()));
						ofCondition = doc.getTree().getCurrentContentItem().setNumericValue(DSRNumericMeasurementValue(ofString, AIMCodes::GetUcumCodeValue("mm")));
					}

					// Image Orientaion Row Z
					if (pImgPlane->GetRowImageOrientationZ())
					{
						nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasAcqContext, DSRTypes::VT_Num, nextAddMode);
						ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz144", "Image Orientation Row Z"));
						ofString.assign(AIMUtil::DoubleToString(*pImgPlane->GetRowImageOrientationZ()));
						ofCondition = doc.getTree().getCurrentContentItem().setNumericValue(DSRNumericMeasurementValue(ofString, AIMCodes::GetUcumCodeValue("mm")));
					}

					// Image Orientaion Column X
					if (pImgPlane->GetColumnImageOrientationX())
					{
						nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasAcqContext, DSRTypes::VT_Num, nextAddMode);
						ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz145", "Image Orientation Column X"));
						ofString.assign(AIMUtil::DoubleToString(*pImgPlane->GetColumnImageOrientationX()));
						ofCondition = doc.getTree().getCurrentContentItem().setNumericValue(DSRNumericMeasurementValue(ofString, AIMCodes::GetUcumCodeValue("mm")));
					}

					// Image Orientaion Column Y
					if (pImgPlane->GetColumnImageOrientationY())
					{
						nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasAcqContext, DSRTypes::VT_Num, nextAddMode);
						ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz146", "Image Orientation Column Y"));
						ofString.assign(AIMUtil::DoubleToString(*pImgPlane->GetColumnImageOrientationY()));
						ofCondition = doc.getTree().getCurrentContentItem().setNumericValue(DSRNumericMeasurementValue(ofString, AIMCodes::GetUcumCodeValue("mm")));
					}

					// Image Orientaion Column Z
					if (pImgPlane->GetColumnImageOrientationZ())
					{
						nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasAcqContext, DSRTypes::VT_Num, nextAddMode);
						ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz147", "Image Orientation Column Z"));
						ofString.assign(AIMUtil::DoubleToString(*pImgPlane->GetColumnImageOrientationZ()));
						ofCondition = doc.getTree().getCurrentContentItem().setNumericValue(DSRNumericMeasurementValue(ofString, AIMCodes::GetUcumCodeValue("mm")));
					}

					// Slice Thickness
					if (pImgPlane->GetSliceThickness())
					{
						nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasAcqContext, DSRTypes::VT_Num, nextAddMode);
						ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("112225", "DCM", "Slice Thickness"));
						ofString.assign(AIMUtil::DoubleToString(*pImgPlane->GetSliceThickness()));
						ofCondition = doc.getTree().getCurrentContentItem().setNumericValue(DSRNumericMeasurementValue(ofString, AIMCodes::GetUcumCodeValue("mm")));
					}

					// Horizontal Pixel Spacing
					if (pImgPlane->GetHorizontalPixelSpacing())
					{
						nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasAcqContext, DSRTypes::VT_Num, nextAddMode);
						ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("111026", "DCM", "Horizontal Pixel Spacing"));
						ofString.assign(AIMUtil::DoubleToString(*pImgPlane->GetHorizontalPixelSpacing()));
						ofCondition = doc.getTree().getCurrentContentItem().setNumericValue(DSRNumericMeasurementValue(ofString, AIMCodes::GetUcumCodeValue("mm")));
					}

					// Vertical Pixel Spacing
					if (pImgPlane->GetVerticalPixelSpacing())
					{
						nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasAcqContext, DSRTypes::VT_Num, nextAddMode);
						ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("111066", "DCM", "Vertical Pixel Spacing"));
						ofString.assign(AIMUtil::DoubleToString(*pImgPlane->GetVerticalPixelSpacing()));
						ofCondition = doc.getTree().getCurrentContentItem().setNumericValue(DSRNumericMeasurementValue(ofString, AIMCodes::GetUcumCodeValue("mm")));
					}

					// Image Position X
					if (pImgPlane->GetImagePositionX())
					{
						nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasAcqContext, DSRTypes::VT_Num, nextAddMode);
						ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz139", "Image Position X"));
						ofString.assign(AIMUtil::DoubleToString(*pImgPlane->GetImagePositionX()));
						ofCondition = doc.getTree().getCurrentContentItem().setNumericValue(DSRNumericMeasurementValue(ofString, AIMCodes::GetUcumCodeValue("mm")));
					}

					// Image Position Y
					if (pImgPlane->GetImagePositionY())
					{
						nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasAcqContext, DSRTypes::VT_Num, nextAddMode);
						ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz140", "Image Position Y"));
						ofString.assign(AIMUtil::DoubleToString(*pImgPlane->GetImagePositionY()));
						ofCondition = doc.getTree().getCurrentContentItem().setNumericValue(DSRNumericMeasurementValue(ofString, AIMCodes::GetUcumCodeValue("mm")));
					}

					// Image Position Z
					if (pImgPlane->GetImagePositionZ())
					{
						nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasAcqContext, DSRTypes::VT_Num, nextAddMode);
						ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz141", "Image Position Z"));
						ofString.assign(AIMUtil::DoubleToString(*pImgPlane->GetImagePositionZ()));
						ofCondition = doc.getTree().getCurrentContentItem().setNumericValue(DSRNumericMeasurementValue(ofString, AIMCodes::GetUcumCodeValue("mm")));
					}
				}

				// Step out to the Image Library container
				nodeId = doc.getTree().goUp();
			}
			const ReferencedDicomObjectVector& refDicomObj = currentStudy.GetReferencedDicomObjectCollection();
			for (ReferencedDicomObjectVector::const_iterator refObjIter = refDicomObj.begin(); refObjIter < refDicomObj.end(); refObjIter++)
			{
				// 1. Image Library Entry for Referenced DICOM objects
				if (!hadExistingImgLib && iter == imgReferences.begin() && images.empty() && refObjIter == refDicomObj.begin())
					nodeId = doc.getTree().addContentItem(DSRTypes::RT_contains, DSRTypes::VT_Container, DSRTypes::AM_belowCurrent);
				else
					nodeId = doc.getTree().addContentItem(DSRTypes::RT_contains, DSRTypes::VT_Container);
				ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz034", "Image Library Entry"));

				// Only the first inner item should be nested one level deep. The rest are on the same level
				DSRTypes::E_AddMode nextAddMode = DSRTypes::AM_belowCurrent;

				// 2. Image Reference Entity UID
				nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasAcqContext, DSRTypes::VT_UIDRef, nextAddMode);
				ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("112040", "DCM", "Tracking Unique Identifier"));
				ofString.assign((*iter)->GetUniqueIdentifier().toString());
				ofCondition = doc.getTree().getCurrentContentItem().setStringValue(ofString);

				nextAddMode = DSRTypes::AM_afterCurrent;

				// Annotation UID
				AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz152", "Annotation UID"), imgAnnotation.GetUniqueIdentifier(), DSRTypes::RT_hasAcqContext, nextAddMode);

				// Study Instance UID
				nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasAcqContext, DSRTypes::VT_UIDRef, nextAddMode);
				ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("110180", "DCM", "Study Instance UID"));
				ofCondition = doc.getTree().getCurrentContentItem().setStringValue(currentStudy.GetInstanceUid().toString());

				// Study Date
				if (currentStudy.GetStartDate() != Date())
				{
					OFDate ofStartDate = AIMUtil::DateConvert(currentStudy.GetStartDate());
					if (ofStartDate.getISOFormattedDate(ofString, false))
					{
						nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasAcqContext, DSRTypes::VT_Date, nextAddMode);
						ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("111060", "DCM", "Study Date"));
						ofCondition = doc.getTree().getCurrentContentItem().setStringValue(ofString);
					}
				}

				// Study Time
				if (currentStudy.GetStartTime() != Time())
				{
					OFTime ofStartTime = AIMUtil::TimeConvert(currentStudy.GetStartTime());
					if (ofStartTime.getISOFormattedTime(ofString, true, false, false, false))
					{
						nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasAcqContext, DSRTypes::VT_Time, nextAddMode);
						ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("111061", "DCM", "Study Time"));
						ofCondition = doc.getTree().getCurrentContentItem().setStringValue(ofString);
					}
				}

				// Procedure Description
				if (!currentStudy.GetProceduDescription().empty())
				{
					nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasAcqContext, DSRTypes::VT_Text, nextAddMode);
					ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("121065", "DCM", "Procedure Description"));
					ofCondition = doc.getTree().getCurrentContentItem().setStringValue(currentStudy.GetProceduDescription());
				}

				// Modality
				nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasAcqContext, DSRTypes::VT_Code, nextAddMode);
				ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("121139", "DCM", "Modality"));
				ofCondition = doc.getTree().getCurrentContentItem().setCodeValue(AIMCodes::CreateCodedEntryValueFromCd(refObjIter->GetModality()));

				// Referenced DICOM Object
				nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasAcqContext, DSRTypes::VT_UIDRef, nextAddMode);
				ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz138", "Referenced DICOM Object"));
				ofCondition = doc.getTree().getCurrentContentItem().setStringValue(refObjIter->GetSopInstanceUid().toString());

				// Step out to the Image Library container
				nodeId = doc.getTree().goUp();
			}
		}
		else if ((*iter)->GetImageReferenceEntityType() == ImageReferenceEntity::T_URI_IMAGE_REF)
		{
			const UriImageReferenceEntity* pUriImgRef = static_cast<const UriImageReferenceEntity*>(*iter);

			// 1. Image Library Entry for URI-referenced images
			if (!hadExistingImgLib && iter == imgReferences.begin())
				nodeId = doc.getTree().addContentItem(DSRTypes::RT_contains, DSRTypes::VT_Container, DSRTypes::AM_belowCurrent);
			else
				nodeId = doc.getTree().addContentItem(DSRTypes::RT_contains, DSRTypes::VT_Container);
			ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz034", "Image Library Entry"));

			// Only the first inner item should be nested one level deep. The rest are on the same level
			DSRTypes::E_AddMode nextAddMode = DSRTypes::AM_belowCurrent;

			// 2. Image Reference Entity UID
			nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasAcqContext, DSRTypes::VT_UIDRef, nextAddMode);
			ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("112040", "DCM", "Tracking Unique Identifier"));
			ofString.assign((*iter)->GetUniqueIdentifier().toString());
			ofCondition = doc.getTree().getCurrentContentItem().setStringValue(ofString);

			nextAddMode = DSRTypes::AM_afterCurrent;

			// Annotation UID
			AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz152", "Annotation UID"), imgAnnotation.GetUniqueIdentifier(), DSRTypes::RT_hasAcqContext, nextAddMode);

			// Add URI
			nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasAcqContext, DSRTypes::VT_Text, nextAddMode);
			ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz148", "URI"));
			ofString.assign(pUriImgRef->GetUri());
			ofCondition = doc.getTree().getCurrentContentItem().setStringValue(ofString);

			// Add MIME Type
			nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasAcqContext, DSRTypes::VT_Text, nextAddMode);
			ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz149", "MIME Type"));
			ofString.assign(pUriImgRef->GetMimeType());
			ofCondition = doc.getTree().getCurrentContentItem().setStringValue(ofString);

			// Step out to the Image Library container
			nodeId = doc.getTree().goUp();
		}
	}

	if (hadExistingImgLib)
	{
		// Reset previous position in the tree
		nodeId = doc.getTree().gotoNode(initialId);
		assert(nodeId == initialId);
	}
	else
	{
		// step out of the new container
		nodeId = doc.getTree().goUp();
	}
}

void DcmModelInternal::PopulateAnnotationEntity(const AnnotationEntity& annotation, DSRDocument& doc)
{
	// Annotation Entity Container
	AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz070", "AIM Annotation Entity"), DSRTypes::RT_contains);

	// Annotation Date Time
	// DateTime is set when the annotation's DateTime is different from the document's only
	OFDateTime annDateTime = AIMUtil::DateTimeConvert(annotation.GetDateTime());
	if (annDateTime.isValid())
	{
		//ofString = doc.getContentDate(ofString) + doc.getContentTime(); // document's DateTime
		// document's Date & Time
		OFString ofContentTime;
		ofCondition = doc.getContentDate(ofString);
		ofCondition = doc.getContentTime(ofContentTime);
		ofString += ofContentTime;
		OFString ofDateTime; // YYYYMMDDHHMMSS
		if (annDateTime.getISOFormattedDateTime(ofDateTime, true, false, false, false) && ofDateTime != ofString)
		{
			ofCondition = doc.getTree().getCurrentContentItem().setObservationDateTime(ofDateTime);

//			nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasObsContext, DSRTypes::VT_Code);
//			ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("121135", "DCM", "Observation Datetime Qualifier"));
//			ofCondition = doc.getTree().getCurrentContentItem().setCodeValue(DSRCodedEntryValue("121136", "DCM", "DateTime Unsynchronized"));
			// OR
			//ofCondition = doc.getTree().getCurrentContentItem().setCodeValue(DSRCodedEntryValue("121137", DCM, "DateTime Estimated");
		}
	}
	// Annotation UID
	AddDsrItem(doc, DSRCodedEntryValue("112040", "DCM", "Tracking Unique Identifier"), annotation.GetUniqueIdentifier(), DSRTypes::RT_hasAcqContext, DSRTypes::AM_belowCurrent);
	// Annotation Type
	AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz005", "Annotation Type"), annotation.GetTypeCode(), DSRTypes::RT_hasAcqContext);
	// Annotation Name
	AddDsrItem(doc, DSRCodedEntryValue("112039", "DCM", "Tracking Identifier"), annotation.GetName(), DSRTypes::RT_hasAcqContext);
	// Annotation Comment
	if (!annotation.GetComment().empty())
		AddDsrItem(doc, DSRCodedEntryValue("121106", "DCM", "Comment"), annotation.GetComment(), DSRTypes::RT_hasObsContext);
	// Precedent Referenced Annotation UID
	if (annotation.GetPrecedentReferencedAnnotationUid())
		AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz068", "Precedent AIM Annotation"), *annotation.GetPrecedentReferencedAnnotationUid(), DSRTypes::RT_hasObsContext);
	// Template UID
	if (annotation.GetTemplateUid())
		AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz103", "Template UID"), *annotation.GetTemplateUid(), DSRTypes::RT_hasObsContext);

	// Audti Trail
	for (AuditTrailVector::const_iterator auditIter = annotation.GetAuditTrailCollection().begin(); auditIter < annotation.GetAuditTrailCollection().end(); auditIter++)
	{
		AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz104", "Audit Status"), auditIter->GetStatusCode(), DSRTypes::RT_hasObsContext);
		AddDsrItem(doc, DSRCodedEntryValue("121125", "DCM", "Datetime of Recording of Log Entry"), auditIter->GetDateTime(), DSRTypes::RT_hasObsContext, DSRTypes::AM_belowCurrent);
		AddDsrItem(doc, DSRCodedEntryValue("C93529", "NCI", "Change Reason"), auditIter->GetChangeReason(), DSRTypes::RT_hasObsContext);
		if (auditIter->GetWorklistSubtaskUid())
			AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz081", "Worklist Subtask UID"), *auditIter->GetWorklistSubtaskUid(), DSRTypes::RT_hasObsContext);
		AddDsrItem(doc, DSRCodedEntryValue("121106", "DCM", "Comment"), auditIter->GetComment(), DSRTypes::RT_hasObsContext);

		// Return to the Annotation Entity level
		nodeId = doc.getTree().goUp();
	}
	// Annotation Role Entity
	for(AnnotationRoleEntityVector::const_iterator roleIter = annotation.GetAnnotationRoleEntityCollection().begin(); roleIter < annotation.GetAnnotationRoleEntityCollection().end(); roleIter++)
	{
		AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz056", "Annotation Role"), roleIter->GetRoleCode(), DSRTypes::RT_hasObsContext);
		AddDsrItem(doc, DSRCodedEntryValue("112040", "DCM", "Tracking Unique Identifier"), roleIter->GetUniqueIdentifier(), DSRTypes::RT_hasObsContext, DSRTypes::AM_belowCurrent);
		AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz057", "Role Sequence Number"), roleIter->GetRoleSequenceNumber(), DSRCodedEntryValue("1", "UCUM", "No units"), DSRTypes::RT_hasProperties);
		if (!roleIter->GetQuestionTypeCode().empty())
			AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz071", "Question Type Code"), roleIter->GetQuestionTypeCode(), DSRTypes::RT_hasProperties);

		nodeId = doc.getTree().goUp(); // up to the Annotation level
	}
	this->PopulateTaskContextEntities(annotation.GetTaskContextEntityCollection(), doc);
	this->PopulateImagingPhysicalEntities(annotation.GetImagingPhysicalEntityCollection(), doc);
	this->PopulateImagingObservations(annotation.GetImagingObservationEntityCollection(), doc);
	this->PopulateCalculations(annotation.GetCalculationEntityCollection(), doc);
	this->PopulateInferences(annotation.GetInferenceEntityCollection(), doc);
	this->PopulateLesionObservations(annotation.GetLesionObservationEntityCollection(), doc);

	// Caller will have to do this!
	//nodeId = doc.getTree().goUp(); // up to the parent level
}

void DcmModelInternal::PopulateImageAnnotation(const ImageAnnotation& imgAnnotation, DSRDocument& doc)
{
	this->PopulateAnnotationEntity(dynamic_cast<const AnnotationEntity&>(imgAnnotation), doc);

	// Add Image Annotation container
	nodeId = doc.getTree().addContentItem(DSRTypes::RT_contains, DSRTypes::VT_Container);
	ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz030", "Image Annotation"));

	size_t containerLevel = doc.getTree().getLevel();

	this->PopulateAnnotationStatements(imgAnnotation.GetImageAnnotationStatementCollection(), doc, true);

	bool nestNext = containerLevel == doc.getTree().getLevel(); // true if no Annotation Statement exist
	this->PopulateSegmentations(imgAnnotation, doc, nestNext);

	nestNext = containerLevel == doc.getTree().getLevel();
	this->PopulateMarkups(imgAnnotation, doc, nestNext);

	nodeId = doc.getTree().goUp(); // up to the parent Annotation Collection level
}

void DcmModelInternal::PopulateAnnotationOfAnnotation(const AnnotationOfAnnotation& annAnnotation, DSRDocument& doc)
{
	this->PopulateAnnotationEntity(dynamic_cast<const AnnotationEntity&>(annAnnotation), doc);

	// Add Annotation Of Annotation container
	AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz031", "Annotation of Annotation"), DSRTypes::RT_contains);

	size_t containerLevel = doc.getTree().getLevel();

	this->PopulateAnnotationStatements(annAnnotation.GetAnnotationOfAnnotationStatementCollection(), doc, true);

	bool nestNext = containerLevel == doc.getTree().getLevel(); // true if no Annotation Statement exist

	// Adjudication Observation
	const AdjudicationObservation* pAdjudicationObs = annAnnotation.GetAdjudicationObservation();
	if (pAdjudicationObs)
	{
		AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz111", "Adjudication Observation"), DSRTypes::RT_contains, nestNext ? DSRTypes::AM_belowCurrent : DSRTypes::AM_afterCurrent);
		nestNext = false;
		// NOTE: Observation UID is set on the container
		doc.getTree().getCurrentContentItem().setObservationUID(pAdjudicationObs->GetObservationUid().toString());
		AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz118", "Observation Scope"), pAdjudicationObs->GetObservationScope(), DSRTypes::RT_hasObsContext, DSRTypes::AM_belowCurrent);
		if (pAdjudicationObs->GetPersonObserversRoleInThisProcedure())
			AddDsrItem(doc, DSRCodedEntryValue("121011", "DCM", "Person Observer's Role in this Procedures"), *pAdjudicationObs->GetPersonObserversRoleInThisProcedure(), DSRTypes::RT_hasObsContext);
		const std::vector<std::string>& idWithinAcceptedObserversRole = pAdjudicationObs->GetIdentifierWithinAcceptedPersonObserversRole();
		for (std::vector<std::string>::const_iterator iter = idWithinAcceptedObserversRole.begin(); iter < idWithinAcceptedObserversRole.end(); iter++)
			AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz113", "Identifier within Accepted Persion Observer's Role"), *iter, DSRTypes::RT_hasObsContext);
		const std::vector<std::string>& idWithinRejectedObserversRole = pAdjudicationObs->GetIdentifierWithinRejectedPersonObserversRole();
		for (std::vector<std::string>::const_iterator iter = idWithinRejectedObserversRole.begin(); iter < idWithinRejectedObserversRole.end(); iter++)
			AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz114", "Identifier within Rejected Persion Observer's Role"), *iter, DSRTypes::RT_hasObsContext);
		//if (!pAdjudicationObs->GetIdentifierWithinAcceptedPersonObserversRole().empty())
		//	AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz113", "Identifier within Accepted Persion Observer's Role"), pAdjudicationObs->GetIdentifierWithinAcceptedPersonObserversRole(), DSRTypes::RT_hasObsContext);
		//if (!pAdjudicationObs->GetIdentifierWithinRejectedPersonObserversRole().empty())
		//	AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz114", "Identifier within Rejected Persion Observer's Role"), pAdjudicationObs->GetIdentifierWithinRejectedPersonObserversRole(), DSRTypes::RT_hasObsContext);
		AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz115", "Reason for Choice"), pAdjudicationObs->GetReasonForChoice(), DSRTypes::RT_hasObsContext);
		if (pAdjudicationObs->GetReasonForDiscordance())
			AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz116", "Reason for Discordance"), *pAdjudicationObs->GetReasonForDiscordance(), DSRTypes::RT_hasObsContext);
		AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz117", "Image Quality Issues Discordance"), AIMCodes::GetBooleanCodeValue(pAdjudicationObs->GetImageQualityIssuesDiscordance()), DSRTypes::RT_hasObsContext);
		if (!pAdjudicationObs->GetComment().empty())
			AddDsrItem(doc, DSRCodedEntryValue("121106", "DCM", "Comment"), pAdjudicationObs->GetComment(), DSRTypes::RT_hasObsContext);

		nodeId = doc.getTree().goUp(); // step out of the Adjudication container
	}

	if (!nestNext)
		nodeId = doc.getTree().goUp(); // step out to the Annotation Entity level

	nodeId = doc.getTree().goUp(); // up to the parent Annotation Collection level
}

void DcmModelInternal::PopulateTaskContextEntities(const TaskContextEntityVector& taskContextEntities, DSRDocument& doc)
{
	for (TaskContextEntityVector::const_iterator iter = taskContextEntities.begin(); iter < taskContextEntities.end(); iter++)
	{
		AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz074", "Worklist Task Name"), iter->GetWorklistTaskName(), DSRTypes::RT_hasObsContext);
		AddDsrItem(doc, DSRCodedEntryValue("112040", "DCM", "Tracking Unique Identifier"), iter->GetUniqueIdentifier(), DSRTypes::RT_hasObsContext, DSRTypes::AM_belowCurrent);
		AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz072", "Worklist Task UID"), iter->GetWorklistTaskUid(), DSRTypes::RT_hasObsContext);
		AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz080", "Worklist Task Version"), iter->GetWorklistTaskVersion(), DSRTypes::RT_hasObsContext);
		AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz074", "Worklist Task Description"), iter->GetWorklistTaskDescription(), DSRTypes::RT_hasObsContext);
		AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz076", "Worklist Task Level"), iter->GetWorklistTaskLevel(), DSRTypes::RT_hasObsContext);
		AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz077", "Worklist Task Type"), iter->GetWorklistTaskType(), DSRTypes::RT_hasObsContext);
		AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz075", "Worklist Task Category"), iter->GetWorklistTaskCategory(), DSRTypes::RT_hasObsContext);
		if (iter->GetWorklistTaskRepeatType())
			AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz078", "Worklist Task Repeat Type"), *iter->GetWorklistTaskRepeatType(), DSRTypes::RT_hasObsContext);
		if (iter->GetWorklistTaskVariabilityType())
			AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz079", "Worklist Task Variability Type"), *iter->GetWorklistTaskVariabilityType(), DSRTypes::RT_hasObsContext);
		AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz082", "Worklist Sub-task Name"), iter->GetWorklistSubtaskName(), DSRTypes::RT_hasObsContext);
		AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz081", "Worklist Sub-task UID"), iter->GetWorklistSubtaskUid(), DSRTypes::RT_hasObsContext);
		AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz083", "Worklist Sub-task Start DateTime"), iter->GetWorklistSubtaskStartDateTime(), DSRTypes::RT_hasObsContext);
		AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz084", "Worklist Sub-task Closed DateTime"), iter->GetWorklistSubtaskClosedDateTime(), DSRTypes::RT_hasObsContext);

		this->PopulateTaskContextEntities(iter->GetTaskContextEntityCollection(), doc);

		nodeId = doc.getTree().goUp(); // up to the initial level
	}
}

void DcmModelInternal::PopulateImagingPhysicalEntities(const ImagingPhysicalEntityVector& imagingPhysicalEnitities, DSRDocument& doc)
{
	for (ImagingPhysicalEntityVector::const_iterator iter = imagingPhysicalEnitities.begin(); iter < imagingPhysicalEnitities.end(); iter++)
	{
		size_t codeNesting = AddDsrItem(doc, DSRCodedEntryValue("G-C0E3", "SRT", "Finding Site"), iter->GetTypeCode(), DSRTypes::RT_hasObsContext, DSRTypes::AM_afterCurrent, true);
		AddDsrItem(doc, DSRCodedEntryValue("112040", "DCM", "Tracking Unique Identifier"), iter->GetUniqueIdentifier(), DSRTypes::RT_hasObsContext, codeNesting > 0 ? DSRTypes::AM_afterCurrent : DSRTypes::AM_belowCurrent);
		if (!iter->GetQuestionTypeCode().empty())
			AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz071", "Question Type Code"), iter->GetQuestionTypeCode(), DSRTypes::RT_hasProperties);
		if (iter->GetQuestionIndex() != -1)
			AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz085", "Question Index"), iter->GetQuestionIndex(), DSRCodedEntryValue("1", "UCUM", "No units"), DSRTypes::RT_hasProperties);
		if (!iter->GetLabel().empty())
			AddDsrItem(doc, DSRCodedEntryValue("C45561", "NCI", "A brief description given for purposes of identification"), iter->GetLabel(), DSRTypes::RT_hasObsContext);
		if (!iter->GetComment().empty())
			 AddDsrItem(doc, DSRCodedEntryValue("121106", "DCM", "Comment"), iter->GetComment(), DSRTypes::RT_hasObsContext);
		if (iter->GetAnnotatorConfidence())
			AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz058", "Annotator Confidence"), *iter->GetAnnotatorConfidence(), DSRCodedEntryValue("%", "UCUM", "%"), DSRTypes::RT_hasObsContext);
		if (iter->GetIsPresent())
			AddDsrItem(doc, DSRCodedEntryValue("G-A203", "SRT", "Present"), AIMCodes::GetBooleanCodeValue(*iter->GetIsPresent()) , DSRTypes::RT_hasObsContext);

		this->PopulateImagingPhysicalEntityCharacteristics(iter->GetImagingPhysicalEntityCharacteristicCollection(), doc);

		this->PopulateImagingObservationCharacteristics(iter->GetImagingObservationCharacteristicCollection(), doc);

		nodeId = doc.getTree().goUp(); // step out of the Imaging Physical Entity container
	}
}

void DcmModelInternal::PopulateImagingPhysicalEntityCharacteristics(const ImagingPhysicalEntityCharacteristicVector& physicalEntityChars, DSRDocument& doc)
{
	for (ImagingPhysicalEntityCharacteristicVector::const_iterator iter = physicalEntityChars.begin(); iter < physicalEntityChars.end(); iter++)
	{
		size_t codeNesting = AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz086", "Imaging Physical Entity Characteristic"), iter->GetTypeCode(), DSRTypes::RT_hasObsContext, DSRTypes::AM_afterCurrent, true);
		DSRTypes::E_AddMode nextAddMode = codeNesting > 0 ? DSRTypes::AM_afterCurrent : DSRTypes::AM_belowCurrent;
		if (!iter->GetQuestionTypeCode().empty())
		{
			AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz071", "Question Type Code"), iter->GetQuestionTypeCode(), DSRTypes::RT_hasProperties, nextAddMode);
			nextAddMode = DSRTypes::AM_afterCurrent;
		}
		if (iter->GetQuestionIndex() != -1)
		{
			AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz085", "Question Index"), iter->GetQuestionIndex(), DSRCodedEntryValue("1", "UCUM", "No units"), DSRTypes::RT_hasProperties, nextAddMode);
			nextAddMode = DSRTypes::AM_afterCurrent;
		}
		if (!iter->GetLabel().empty())
		{
			AddDsrItem(doc, DSRCodedEntryValue("C45561", "NCI", "A brief description given for purposes of identification"), iter->GetLabel(), DSRTypes::RT_hasObsContext, nextAddMode);
			nextAddMode = DSRTypes::AM_afterCurrent;
		}
		if (!iter->GetComment().empty())
		{
			AddDsrItem(doc, DSRCodedEntryValue("121106", "DCM", "Comment"), iter->GetComment(), DSRTypes::RT_hasObsContext, nextAddMode);
			nextAddMode = DSRTypes::AM_afterCurrent;
		}
		if (iter->GetAnnotatorConfidence())
		{
			AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz058", "Annotator Confidence"), *iter->GetAnnotatorConfidence(), DSRCodedEntryValue("%", "UCUM", "%"), DSRTypes::RT_hasProperties, nextAddMode);
			nextAddMode = DSRTypes::AM_afterCurrent;
		}

		if (!iter->GetCharacteristicQuantificationCollection().empty())
		{
			this->PopulateCharacteristicQuantifications(iter->GetCharacteristicQuantificationCollection(), doc, nextAddMode == DSRTypes::AM_belowCurrent);
			nextAddMode = DSRTypes::AM_afterCurrent;
		}

		if (nextAddMode != DSRTypes::AM_belowCurrent)
			nodeId = doc.getTree().goUp(); // step out of the Imaging Physical Entity container
	}
}

void DcmModelInternal::PopulateCharacteristicQuantifications(const CharacteristicQuantificationPtrVector& charQuantifications, DSRDocument& doc, bool nestFirst)
{
	for (CharacteristicQuantificationPtrVector::const_iterator iter = charQuantifications.begin(); iter < charQuantifications.end(); iter++)
	{
		if (!*iter)
			continue;

		if (nestFirst)
		{
			AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz066", "Characteristic Quantification"), AIMCodes::GetCharacteristicQuantificationTypeValue((*iter)->GetQuantificationType()), DSRTypes::RT_hasObsContext, DSRTypes::AM_belowCurrent);
			nestFirst = false;
		}
		else
			AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz066", "Characteristic Quantification"), AIMCodes::GetCharacteristicQuantificationTypeValue((*iter)->GetQuantificationType()), DSRTypes::RT_hasObsContext);
		AddDsrItem(doc, DSRCodedEntryValue("C45561", "NCI", "A brief description given for purposes of identification"), (*iter)->GetLabel(), DSRTypes::RT_hasObsContext, DSRTypes::AM_belowCurrent);
		if ((*iter)->GetAnnotatorConfidence())
			AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz058", "Annotator Confidence"), *(*iter)->GetAnnotatorConfidence(), DSRCodedEntryValue("%", "UCUM", "%"), DSRTypes::RT_hasObsContext);
		if ((*iter)->GetCharacteristicQuantificationIndex() != -1)
			AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz087", "Characteristic Quantification Index"), (*iter)->GetCharacteristicQuantificationIndex(), DSRCodedEntryValue("1", "UCUM", "No units"), DSRTypes::RT_hasProperties);
		if (!(*iter)->GetValueLabel().empty())
			AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz153", "Value Label"), (*iter)->GetValueLabel(), DSRTypes::RT_hasObsContext);
		if (!(*iter)->GetValueDescription().empty())
			AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz154", "Value Description"), (*iter)->GetValueDescription(), DSRTypes::RT_hasObsContext);
		if (!(*iter)->GetComment().empty())
			AddDsrItem(doc, DSRCodedEntryValue("121106", "DCM", "Comment"), (*iter)->GetComment(), DSRTypes::RT_hasObsContext);

		switch((*iter)->GetQuantificationType())
		{
			case CharacteristicQuantification::QT_Numerical:
				{
					const Numerical* pNumerical = dynamic_cast<const Numerical*>(*iter);

					AddDsrItem(doc, DSRCodedEntryValue("C25712", "NCI", "A numerical quantity measured or assigned or computed"), pNumerical->GetValue(), AIMCodes::GetUcumCodeValue(pNumerical->GetUcumString()), DSRTypes::RT_hasProperties);
					if (pNumerical->GetOperator() != aim_lib::None && pNumerical->GetOperator() != aim_lib::InvalidComparisonOperatorType)
					{
						AddDsrItem(doc, DSRCodedEntryValue("C61580", "NCI", "A Boolean operator, a symbol that denotes a logical operation"), AIMCodes::GetComparisonOperatorTypeValue(pNumerical->GetOperator()), DSRTypes::RT_hasObsContext, DSRTypes::AM_belowCurrent);
						nodeId = doc.getTree().goUp(); // step out to Characterisitc Quantification level
					}
				}
				break;
			case CharacteristicQuantification::QT_Quantile:
				{
					const Quantile* pQuantile = dynamic_cast<const Quantile*>(*iter);

					AddDsrItem(doc, DSRCodedEntryValue("C63902", "NCI", "An interval into which a given point does or does not fall"), pQuantile->GetSelectedBin(), DSRCodedEntryValue("1", "UCUM", "No units"), DSRTypes::RT_hasProperties);
					AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz151", "Number of Intervals"), pQuantile->GetBins(), DSRCodedEntryValue("1", "UCUM", "No units"), DSRTypes::RT_hasObsContext, DSRTypes::AM_belowCurrent);
					AddDsrItem(doc, DSRCodedEntryValue("R-404FB", "SRT", "Minimum"), pQuantile->GetMinValue(), DSRCodedEntryValue("1", "UCUM", "No units"), DSRTypes::RT_hasObsContext);
					AddDsrItem(doc, DSRCodedEntryValue("G-A437", "SRT", "Maximum"), pQuantile->GetMaxValue(), DSRCodedEntryValue("1", "UCUM", "No units"), DSRTypes::RT_hasObsContext);
					nodeId = doc.getTree().goUp(); // step out to Characterisitc Quantification level
				}
				break;
			case CharacteristicQuantification::QT_Non_Quantifiable:
				{
					const NonQuantifiable* pNonQuantifiable = dynamic_cast<const NonQuantifiable*>(*iter);

					AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz067", "Non-Quantifiable Code"), pNonQuantifiable->GetTypeCode(), DSRTypes::RT_hasProperties);
				}
				break;
			case CharacteristicQuantification::QT_Scale:
				{
					const Scale* pScale = dynamic_cast<const Scale*>(*iter);

					AddDsrItem(doc, DSRCodedEntryValue("C25712", "NCI", "A numerical quantity measured or assigned or computed"), pScale->GetValue(), DSRTypes::RT_hasProperties);
					AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz088", "Scale Type"), AIMCodes::GetScaleTypeValue(pScale->GetScaleType()), DSRTypes::RT_hasObsContext, DSRTypes::AM_belowCurrent);
					nodeId = doc.getTree().goUp(); // step out to Characterisitc Quantification level
				}
				break;
			case CharacteristicQuantification::QT_Interval:
				{
					const Interval* pInterval = dynamic_cast<const Interval*>(*iter);

					AddDsrItem(doc, DSRCodedEntryValue("G-A437", "SRT", "Maximum"), pInterval->GetMaxValue(), AIMCodes::GetUcumCodeValue(pInterval->GetUcumString()), DSRTypes::RT_hasProperties);
					AddDsrItem(doc, DSRCodedEntryValue("C61580", "NCI", "A Boolean operator, a symbol that denotes a logical operation"), AIMCodes::GetComparisonOperatorTypeValue(pInterval->GetMaxOperator()), DSRTypes::RT_hasObsContext, DSRTypes::AM_belowCurrent);
					nodeId = doc.getTree().goUp(); // step out to Characterisitc Quantification level
					AddDsrItem(doc, DSRCodedEntryValue("R-404FB", "SRT", "Minimum"), pInterval->GetMinValue(), AIMCodes::GetUcumCodeValue(pInterval->GetUcumString()), DSRTypes::RT_hasProperties);
					AddDsrItem(doc, DSRCodedEntryValue("C61580", "NCI", "A Boolean operator, a symbol that denotes a logical operation"), AIMCodes::GetComparisonOperatorTypeValue(pInterval->GetMinOperator()), DSRTypes::RT_hasObsContext, DSRTypes::AM_belowCurrent);
					nodeId = doc.getTree().goUp(); // step out to Characterisitc Quantification level
				}
				break;
			default:
				assert(false); // Unknown Charachteristic Quantification type
		}

		nodeId = doc.getTree().goUp(); // step out of Characterisitc Quantification
	}
}

void DcmModelInternal::PopulateImagingObservations(const ImagingObservationEntityVector& imgObservationEntities, DSRDocument &doc)
{
	for (ImagingObservationEntityVector::const_iterator iter = imgObservationEntities.begin(); iter < imgObservationEntities.end(); iter++)
	{
		size_t codeNesting = AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz099", "Imaging Observation Entity"), iter->GetTypeCode(), DSRTypes::RT_hasObsContext, DSRTypes::AM_afterCurrent, true);
		AddDsrItem(doc, DSRCodedEntryValue("112040", "DCM", "Tracking Unique Identifier"), iter->GetUniqueIdentifier(), DSRTypes::RT_hasObsContext, codeNesting > 0 ? DSRTypes::AM_afterCurrent : DSRTypes::AM_belowCurrent);
		if (!iter->GetQuestionTypeCode().empty())
			AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz071", "Question Type Code"), iter->GetQuestionTypeCode(), DSRTypes::RT_hasProperties);
		if (iter->GetQuestionIndex() != -1)
			AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz085", "Question Index"), iter->GetQuestionIndex(), DSRCodedEntryValue("1", "UCUM", "No units"), DSRTypes::RT_hasProperties);
		if (!iter->GetLabel().empty())
			AddDsrItem(doc, DSRCodedEntryValue("C45561", "NCI", "A brief description given for purposes of identification"), iter->GetLabel(), DSRTypes::RT_hasObsContext);
		if (!iter->GetComment().empty())
			 AddDsrItem(doc, DSRCodedEntryValue("121106", "DCM", "Comment"), iter->GetComment(), DSRTypes::RT_hasObsContext);
		if (iter->GetAnnotatorConfidence())
			AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz058", "Annotator Confidence"), *iter->GetAnnotatorConfidence(), DSRCodedEntryValue("%", "UCUM", "%"), DSRTypes::RT_hasObsContext);
		if (iter->GetIsPresent())
			AddDsrItem(doc, DSRCodedEntryValue("G-A203", "SRT", "Present"), AIMCodes::GetBooleanCodeValue(*iter->GetIsPresent()) , DSRTypes::RT_hasObsContext);

		this->PopulateImagingObservationCharacteristics(iter->GetImagingObservationCharacteristicCollection(), doc);

		nodeId = doc.getTree().goUp(); // step out of the Imaging Observation Entity container
	}
}

void DcmModelInternal::PopulateImagingObservationCharacteristics(const ImagingObservationCharacteristicVector& observationChars, DSRDocument& doc)
{
	for(ImagingObservationCharacteristicVector::const_iterator iter = observationChars.begin(); iter < observationChars.end(); iter++)
	{
		size_t codeNesting = AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz010", "Imaging Observation Characteristic"), iter->GetTypeCode(), DSRTypes::RT_hasObsContext, DSRTypes::AM_afterCurrent, true);
		DSRTypes::E_AddMode nextAddMode = codeNesting > 0 ? DSRTypes::AM_afterCurrent : DSRTypes::AM_belowCurrent;
		if (!iter->GetQuestionTypeCode().empty())
		{
			AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz071", "Question Type Code"), iter->GetQuestionTypeCode(), DSRTypes::RT_hasProperties, nextAddMode);
			nextAddMode = DSRTypes::AM_afterCurrent;
		}
		if (iter->GetQuestionIndex() != -1)
		{
			AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz085", "Question Index"), iter->GetQuestionIndex(), DSRCodedEntryValue("1", "UCUM", "No units"), DSRTypes::RT_hasProperties, nextAddMode);
			nextAddMode = DSRTypes::AM_afterCurrent;
		}
		if (!iter->GetLabel().empty())
		{
			AddDsrItem(doc, DSRCodedEntryValue("C45561", "NCI", "A brief description given for purposes of identification"), iter->GetLabel(), DSRTypes::RT_hasObsContext, nextAddMode);
			nextAddMode = DSRTypes::AM_afterCurrent;
		}
		if (!iter->GetComment().empty())
		{
			 AddDsrItem(doc, DSRCodedEntryValue("121106", "DCM", "Comment"), iter->GetComment(), DSRTypes::RT_hasObsContext, nextAddMode);
			nextAddMode = DSRTypes::AM_afterCurrent;
		}
		if (iter->GetAnnotatorConfidence())
		{
			AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz058", "Annotator Confidence"), *iter->GetAnnotatorConfidence(), DSRCodedEntryValue("%", "UCUM", "%"), DSRTypes::RT_hasProperties, nextAddMode);
			nextAddMode = DSRTypes::AM_afterCurrent;
		}

		if (!iter->GetCharacteristicQuantificationCollection().empty())
		{
			this->PopulateCharacteristicQuantifications(iter->GetCharacteristicQuantificationCollection(), doc, nextAddMode == DSRTypes::AM_belowCurrent);
			nextAddMode = DSRTypes::AM_afterCurrent;
		}

		if (nextAddMode != DSRTypes::AM_belowCurrent)
			nodeId = doc.getTree().goUp(); // step out of the Imaging Observation Characteristic container
	}
}

void DcmModelInternal::PopulateInferences(const InferenceEntityVector& inferences, DSRDocument& doc)
{
	for(InferenceEntityVector::const_iterator iter = inferences.begin(); iter < inferences.end(); ++iter)
	{
		size_t codeNesting = AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz150", "Inference Entity"), iter->GetTypeCode(), DSRTypes::RT_hasObsContext, DSRTypes::AM_afterCurrent, true);
		AddDsrItem(doc, DSRCodedEntryValue("112040", "DCM", "Tracking Unique Identifier"), iter->GetUniqueIdentifier(), DSRTypes::RT_hasObsContext, codeNesting > 0 ? DSRTypes::AM_afterCurrent : DSRTypes::AM_belowCurrent);
		if (!iter->GetQuestionTypeCode().empty())
			AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz071", "Question Type Code"), iter->GetQuestionTypeCode(), DSRTypes::RT_hasProperties);
		if (iter->GetQuestionIndex() != -1)
			AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz085", "Question Index"), iter->GetQuestionIndex(), DSRCodedEntryValue("1", "UCUM", "No units"), DSRTypes::RT_hasProperties);
		if (iter->GetAnnotatorConfidence())
			AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz058", "Annotator Confidence"), *iter->GetAnnotatorConfidence(), DSRCodedEntryValue("%", "UCUM", "%"), DSRTypes::RT_hasObsContext);
		AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz059", "Image Evidence"), AIMCodes::GetBooleanCodeValue(iter->GetIsImageEvidence()) , DSRTypes::RT_hasProperties);
		if (iter->GetIsPresent())
			AddDsrItem(doc, DSRCodedEntryValue("G-A203", "SRT", "Present"), AIMCodes::GetBooleanCodeValue(*iter->GetIsPresent()) , DSRTypes::RT_hasObsContext);
		if (!iter->GetDescription().empty())
			 AddDsrItem(doc, DSRCodedEntryValue("C25365", "NCI", "Description"), iter->GetDescription(), DSRTypes::RT_hasObsContext);
		if (!iter->GetLabel().empty())
			AddDsrItem(doc, DSRCodedEntryValue("C45561", "NCI", "A brief description given for purposes of identification"), iter->GetLabel(), DSRTypes::RT_hasObsContext);
		if (!iter->GetComment().empty())
			 AddDsrItem(doc, DSRCodedEntryValue("121106", "DCM", "Comment"), iter->GetComment(), DSRTypes::RT_hasObsContext);

		nodeId = doc.getTree().goUp(); // step out of the Inference Entity
	}
}

void DcmModelInternal::PopulateCalculations(const CalculationEntityVector& calcEntities, DSRDocument& doc)
{
	for(CalculationEntityVector::const_iterator iter = calcEntities.begin(); iter < calcEntities.end(); iter++)
	{
		size_t codeNesting = AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz090", "Calculation Entity"), iter->GetTypeCode(), DSRTypes::RT_hasObsContext, DSRTypes::AM_afterCurrent, true);
		AddDsrItem(doc, DSRCodedEntryValue("112040", "DCM", "Tracking Unique Identifier"), iter->GetUniqueIdentifier(), DSRTypes::RT_hasObsContext, codeNesting > 0 ? DSRTypes::AM_afterCurrent : DSRTypes::AM_belowCurrent);
		if (!iter->GetQuestionTypeCode().empty())
			AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz071", "Question Type Code"), iter->GetQuestionTypeCode(), DSRTypes::RT_hasProperties);
		if (iter->GetQuestionIndex() != -1)
			AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz085", "Question Index"), iter->GetQuestionIndex(), DSRCodedEntryValue("1", "UCUM", "No units"), DSRTypes::RT_hasProperties);
		if (!iter->GetDescription().empty())
			 AddDsrItem(doc, DSRCodedEntryValue("112034", "DCM", "Calculation Description"), iter->GetDescription(), DSRTypes::RT_hasObsContext);
		if (!iter->GetMathML().empty())
			AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz013", "Calculation MathML"), iter->GetMathML(), DSRTypes::RT_hasObsContext);

		const Algorithm* pAlgorithm = iter->GetAlgorithm();
		if (pAlgorithm)
		{
			AddDsrItem(doc, DSRCodedEntryValue("111001", "DCM", "Algorithm Name"), pAlgorithm->GetName(), DSRTypes::RT_hasObsContext);
			assert(!pAlgorithm->GetType().empty()); // empty algorithm will break nesting
			AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz091", "Algorithm Type"), pAlgorithm->GetType(), DSRTypes::RT_hasObsContext, DSRTypes::AM_belowCurrent);
			if (pAlgorithm->GetUniqueIdentifier())
				AddDsrItem(doc, DSRCodedEntryValue("112040", "DCM", "Tracking Unique Identifier"), *pAlgorithm->GetUniqueIdentifier(), DSRTypes::RT_hasObsContext);
			if (!pAlgorithm->GetVersion().empty())
				AddDsrItem(doc, DSRCodedEntryValue("111003", "DCM", "Algorithm Version"), pAlgorithm->GetVersion(), DSRTypes::RT_hasObsContext);
			if (!pAlgorithm->GetDescription().empty())
				 AddDsrItem(doc, DSRCodedEntryValue("C25365", "NCI", "Description"), pAlgorithm->GetDescription(), DSRTypes::RT_hasObsContext);
			for (ParameterVector::const_iterator paramIter = pAlgorithm->GetParameterCollection().begin(); paramIter < pAlgorithm->GetParameterCollection().end(); paramIter++)
			{
				AddDsrItem(doc, DSRCodedEntryValue("C44175", "NCI", "Parameter"), paramIter->GetName(), DSRTypes::RT_hasObsContext);
				AddDsrItem(doc, DSRCodedEntryValue("C49100", "NCI", "Data Value"), paramIter->GetValue(), DSRTypes::RT_hasObsContext, DSRTypes::AM_belowCurrent);
				AddDsrItem(doc, DSRCodedEntryValue("C42645", "NCI", "Data Type"), paramIter->GetDataType(), DSRTypes::RT_hasObsContext);
				nodeId = doc.getTree().goUp(); // step out to the Algorithm level
			}
			nodeId = doc.getTree().goUp(); // step out to the Calculation Entity level
		}

		for (CalculationResultPtrVector::const_iterator calcIter = iter->GetCalculationResultCollection().begin(); calcIter < iter->GetCalculationResultCollection().end(); calcIter++)
		{
			if (!*calcIter)
				continue;

			const CompactCalculationResult* pCompactCalcResult = dynamic_cast<const CompactCalculationResult*>(*calcIter);
			const ExtendedCalculationResult* pExtendedCalcResult = dynamic_cast<const ExtendedCalculationResult*>(*calcIter);
			assert(pCompactCalcResult || pExtendedCalcResult); // these are the two known calculation result types
			assert(!(*calcIter)->GetDimensionCollection().empty()); // at least one dimension must be set

			// Special case - single numeric value
			if (pCompactCalcResult && 
				pCompactCalcResult->GetType() == CalculationResult::Scalar && 
				!pCompactCalcResult->GetEncoding() &&
				!pCompactCalcResult->GetCompression() &&
				AIMUtil::IsNumeric(pCompactCalcResult->GetValue()))
			//if ((*calcIter)->GetType() == Scalar)
			{
				assert((*calcIter)->GetDimensionCollection().size() == 1);

				ofString.clear();
				//if (pCompactCalcResult && AIMUtil::IsNumeric(pCompactCalcResult->GetValue()))
					ofString.assign(pCompactCalcResult->GetValue());
				//else if (pExtendedCalcResult && pExtendedCalcResult->GetCalculationDataCollection().size() == 1)
				//	ofString.assign(pExtendedCalcResult->GetCalculationDataCollection()[0].GetValue());

				if (ofString.empty())
				{
					assert(false); // there was no numeric value for a Scalar!
					continue;
				}
				nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasObsContext, DSRTypes::VT_Num);
				ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz015", "Calculation Result"));
				ofCondition = doc.getTree().getCurrentContentItem().setNumericValue(DSRNumericMeasurementValue(ofString, AIMCodes::GetUcumCodeValue((*calcIter)->GetUnitOfMeasure())));

				bool hasNestedChildren = false;
				if (!(*calcIter)->GetDimensionCollection().empty())
				{
					AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz018", "Dimension Label"), pCompactCalcResult->GetDimensionCollection()[0].GetLabel(), DSRTypes::RT_hasObsContext, DSRTypes::AM_belowCurrent);
					hasNestedChildren = true;
				}

				AddDsrItem(doc, DSRCodedEntryValue("C42645", "NCI", "Data Type"), (*calcIter)->GetDataType(), DSRTypes::RT_hasObsContext, hasNestedChildren ? DSRTypes::AM_afterCurrent : DSRTypes::AM_belowCurrent);
				hasNestedChildren = true;

				if (hasNestedChildren)
					nodeId = doc.getTree().goUp(); // step out to the Calculation Entity level
				continue;
			}

			// Non-Scalar calculations

			AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz016", "Calculation Result Type"), AIMCodes::GetCalculationResultTypeValue((*calcIter)->GetType()), DSRTypes::RT_hasObsContext);
			AddDsrItem(doc, DSRCodedEntryValue("C42645", "NCI", "Data Type"), (*calcIter)->GetDataType(), DSRTypes::RT_hasObsContext, DSRTypes::AM_belowCurrent);
			AddDsrItem(doc, DSRCodedEntryValue("C25709", "NCI", "Unit of Measure"), AIMCodes::GetUcumCodeValue((*calcIter)->GetUnitOfMeasure()), DSRTypes::RT_hasObsContext);
			// Dimensions
			for (DimensionVector::const_iterator dimIter = (*calcIter)->GetDimensionCollection().begin(); dimIter < (*calcIter)->GetDimensionCollection().end(); dimIter++)
			{
				AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz040", "Dimension Index"), dimIter->GetIndex(),  DSRCodedEntryValue("1", "UCUM", "No units"), DSRTypes::RT_hasObsContext);
				AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz041", "Dimension Size"), dimIter->GetSize(), DSRCodedEntryValue("1", "UCUM", "No units"), DSRTypes::RT_hasObsContext, DSRTypes::AM_belowCurrent);
				AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz018", "Dimension Label"), dimIter->GetLabel(), DSRTypes::RT_hasObsContext);
				nodeId = doc.getTree().goUp(); // step out to the Dimension level
			}

			if (pCompactCalcResult)
			{
				AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz092", "Compact Result Value"), pCompactCalcResult->GetValue(), DSRTypes::RT_hasObsContext);
				bool hasNestedItems = false;
				if (pCompactCalcResult->GetEncoding())
				{
					AddDsrItem(doc, DSRCodedEntryValue("C80216", "NCI", "Encode"), *pCompactCalcResult->GetEncoding(), DSRTypes::RT_hasObsContext, hasNestedItems ? DSRTypes::AM_afterCurrent : DSRTypes::AM_belowCurrent);
					hasNestedItems = true;
				}
				if (pCompactCalcResult->GetCompression())
				{
					AddDsrItem(doc, DSRCodedEntryValue("C41208", "NCI", "Compression"), *pCompactCalcResult->GetCompression(), DSRTypes::RT_hasObsContext, hasNestedItems ? DSRTypes::AM_afterCurrent : DSRTypes::AM_belowCurrent);
					hasNestedItems = true;
				}
				if (hasNestedItems)
					nodeId = doc.getTree().goUp(); // step out to the Calculation Result Type level

				nodeId = doc.getTree().goUp(); // step out to the Calculation Entity level
			}
			else if(pExtendedCalcResult)
			{
				for (CalculationDataVector::const_iterator calcDataIter = pExtendedCalcResult->GetCalculationDataCollection().begin(); calcDataIter < pExtendedCalcResult->GetCalculationDataCollection().end(); calcDataIter++)
				{
					AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz020", "Calculation Result Data"), calcDataIter->GetValue(), DSRTypes::RT_hasObsContext);
					bool hasCoordinate = false;
					for (CoordinateVector::const_iterator coordIter = calcDataIter->GetCoordinateCollection().begin(); coordIter < calcDataIter->GetCoordinateCollection().end(); coordIter++)
					{
						AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz040", "Dimension Index"), coordIter->GetDimensionIndex(), DSRCodedEntryValue("1", "UCUM", "No units"), DSRTypes::RT_hasObsContext, hasCoordinate ? DSRTypes::AM_afterCurrent : DSRTypes::AM_belowCurrent);
						hasCoordinate = true;
						AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz043", "Coordinate Position"), coordIter->GetPosition(), DSRCodedEntryValue("1", "UCUM", "No units"), DSRTypes::RT_hasObsContext, DSRTypes::AM_belowCurrent);
						nodeId = doc.getTree().goUp(); // step out to the Coordinate level
					}
					if (hasCoordinate)
						nodeId = doc.getTree().goUp(); // step out to the Calculation Result Data level
				}

				nodeId = doc.getTree().goUp(); // step out to the Calculation Entity level
			}
		}
		nodeId = doc.getTree().goUp(); // step out of the Calculation Entity
	}
}

void DcmModelInternal::PopulateLesionObservations(const LesionObservationEntityPtrVector& lesionObservations, DSRDocument& doc)
{
	for (LesionObservationEntityPtrVector::const_iterator iter = lesionObservations.begin(); iter < lesionObservations.end(); iter++)
	{
		AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz120", "Lesion Observation"), DSRTypes::RT_contains);
		AddDsrItem(doc, DSRCodedEntryValue("112040", "DCM", "Tracking Unique Identifier"), (*iter)->GetUniqueIdentifier(), DSRTypes::RT_hasObsContext, DSRTypes::AM_belowCurrent);
		AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz121", "Lesion Unique Identifier"), (*iter)->GetLesionUniqueIdentifier(), DSRTypes::RT_hasObsContext);
		if ((*iter)->GetIsAdditionalObservation())
			AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz119", "Is Additional Observation"), AIMCodes::GetBooleanCodeValue(*(*iter)->GetIsAdditionalObservation()), DSRTypes::RT_hasObsContext);

		const GeneralLesionObservationEntity* pGeneralLesionObs = dynamic_cast<const GeneralLesionObservationEntity*>(*iter);
		const TimePointLesionObservationEntity* pTimePointLesionObs = dynamic_cast<const TimePointLesionObservationEntity*>(*iter);
		assert(pGeneralLesionObs || pTimePointLesionObs); // two known types of lesion observations

		if (pGeneralLesionObs)
		{
			AddDsrItem(doc, DSRCodedEntryValue("112039", "DCM", "Tracking Identifier"), pGeneralLesionObs->GetTrackingIdentifier(), DSRTypes::RT_hasObsContext);
			AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz093", "Lesion Type"), pGeneralLesionObs->GetLesionType(), DSRTypes::RT_hasObsContext, DSRTypes::AM_belowCurrent);
			if (pGeneralLesionObs->GetReconstructionInterval())
				AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz094", "Reconstruction Interval"), *pGeneralLesionObs->GetReconstructionInterval(), DSRTypes::RT_hasObsContext);
			if (pGeneralLesionObs->GetLaterality())
				AddDsrItem(doc, DSRCodedEntryValue("G-C171", "SRT", "Laterality"), *pGeneralLesionObs->GetLaterality(), DSRTypes::RT_hasObsContext);
			nodeId = doc.getTree().goUp(); // step out to the Lesion Observation level
		}
		else if (pTimePointLesionObs)
		{
			AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz095", "Calibration"), AIMCodes::GetBooleanCodeValue(pTimePointLesionObs->GetCalibration()), DSRTypes::RT_hasObsContext);
			bool hasNestedItems = false;
			if (pTimePointLesionObs->GetPredecessorLesionTrackingUid())
			{
				AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz096", "Predecessor Lesion Tracking Unique Identifier"), *pTimePointLesionObs->GetPredecessorLesionTrackingUid(), DSRTypes::RT_hasObsContext, hasNestedItems ? DSRTypes::AM_afterCurrent : DSRTypes::AM_belowCurrent);
				hasNestedItems = true;
			}
			if (!pTimePointLesionObs->GetComment().empty())
			{
				AddDsrItem(doc, DSRCodedEntryValue("121106", "DCM", "Comment"), pTimePointLesionObs->GetComment(), DSRTypes::RT_hasObsContext, hasNestedItems ? DSRTypes::AM_afterCurrent : DSRTypes::AM_belowCurrent);
				hasNestedItems = true;
			}
			if (pTimePointLesionObs->GetTherapeuticResponse())
			{
				AddDsrItem(doc, DSRCodedEntryValue("RID11510", "RADLEX", "Therapeutic Response"), *pTimePointLesionObs->GetTherapeuticResponse(), DSRTypes::RT_hasObsContext, hasNestedItems ? DSRTypes::AM_afterCurrent : DSRTypes::AM_belowCurrent);
				hasNestedItems = true;
			}
			if (pTimePointLesionObs->GetQualitativeAssessment())
			{
				AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz097", "Qualitative Assessment"), *pTimePointLesionObs->GetQualitativeAssessment(), DSRTypes::RT_hasObsContext, hasNestedItems ? DSRTypes::AM_afterCurrent : DSRTypes::AM_belowCurrent);
				hasNestedItems = true;
			}
			if (pTimePointLesionObs->GetCanEvaluateLesion())
			{
				AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz098", "Can Evaluate Lesion"), AIMCodes::GetBooleanCodeValue(*pTimePointLesionObs->GetCanEvaluateLesion()), DSRTypes::RT_hasObsContext, hasNestedItems ? DSRTypes::AM_afterCurrent : DSRTypes::AM_belowCurrent);
				hasNestedItems = true;
			}
			if (pTimePointLesionObs->GetReasonUnableToEvaluate())
			{
				AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz099", "Reason Unable to Evaluate"), *pTimePointLesionObs->GetReasonUnableToEvaluate(), DSRTypes::RT_hasObsContext, hasNestedItems ? DSRTypes::AM_afterCurrent : DSRTypes::AM_belowCurrent);
				hasNestedItems = true;
			}
			if (pTimePointLesionObs->GetCanMeasureLesion())
			{
				AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz100", "Can Measure Lesion"), AIMCodes::GetBooleanCodeValue(*pTimePointLesionObs->GetCanMeasureLesion()), DSRTypes::RT_hasObsContext, hasNestedItems ? DSRTypes::AM_afterCurrent : DSRTypes::AM_belowCurrent);
				hasNestedItems = true;
			}
			if (pTimePointLesionObs->GetReasonUnableToMeasure())
			{
				AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz101", "Reason Unable to Measure"), *pTimePointLesionObs->GetReasonUnableToMeasure(), DSRTypes::RT_hasObsContext, hasNestedItems ? DSRTypes::AM_afterCurrent : DSRTypes::AM_belowCurrent);
				hasNestedItems = true;
			}
			if (pTimePointLesionObs->GetIsUnequivocalProgression())
			{
				AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz102", "Unequivocal Progression"), AIMCodes::GetBooleanCodeValue(*pTimePointLesionObs->GetIsUnequivocalProgression()), DSRTypes::RT_hasObsContext, hasNestedItems ? DSRTypes::AM_afterCurrent : DSRTypes::AM_belowCurrent);
				hasNestedItems = true;
			}
			if (hasNestedItems)
				nodeId = doc.getTree().goUp(); // step out to the Lesion Observation level
		}

		nodeId = doc.getTree().goUp(); // step out to the Annotation level
	}
}

void DcmModelInternal::PopulateAnnotationStatements(const std::vector<AnnotationStatement*>& statements, DSRDocument& doc, bool nestFirst)
{
	for (std::vector<AnnotationStatement*>::const_iterator iter = statements.begin(); iter < statements.end(); iter++)
	{
		if (nestFirst && iter == statements.begin())
			AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz106", "Annotation Statement"), AIMCodes::GetStatementPredicateValue((*iter)->GetRelationshipName()), DSRTypes::RT_hasObsContext, DSRTypes::AM_belowCurrent);
		else
			AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz106", "Annotation Statement"), AIMCodes::GetStatementPredicateValue((*iter)->GetRelationshipName()), DSRTypes::RT_hasObsContext);
		AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz107", "Annotation Statement Subject"), AIMCodes::GetEntityValue((*iter)->GetSubjectClassName()), DSRTypes::RT_hasObsContext, DSRTypes::AM_belowCurrent);
		AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz109", "Annotation Statement Subject UID"), (*iter)->GetSubjectUniqueIdentifier(), DSRTypes::RT_hasObsContext, DSRTypes::AM_belowCurrent);
		nodeId = doc.getTree().goUp(); // step out to the Statement level
		AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz108", "Annotation Statement Object"), AIMCodes::GetEntityValue((*iter)->GetObjectClassName()), DSRTypes::RT_hasObsContext);
		AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz110", "Annotation Statement Object UID"), (*iter)->GetObjectUniqueIdentifier(), DSRTypes::RT_hasObsContext, DSRTypes::AM_belowCurrent);
		nodeId = doc.getTree().goUp(); // step out to the Statement level
		
		nodeId = doc.getTree().goUp(); // step out of the Statement level
	}
}

void DcmModelInternal::PopulateSegmentations(const ImageAnnotation& annotation, DSRDocument& doc, bool nestFirst)
{
	const SegmentationEntityPtrVector& segmentations = annotation.GetSegmentationEntityCollection();
	for(SegmentationEntityPtrVector::const_iterator iter = segmentations.begin(); iter < segmentations.end(); iter++)
	{
		const DicomSegmentationEntity* pDicomSegmentation = dynamic_cast<const DicomSegmentationEntity*>(*iter);

		if(!pDicomSegmentation)
		{
			assert(false); // unknown segmentation class
			continue;
		}

		if (nestFirst && iter == segmentations.begin())
			AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz006", "Segmentation"), "Segmentation", DSRTypes::RT_hasObsContext, DSRTypes::AM_belowCurrent);
		else
			AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz006", "Segmentation"), "Segmentation", DSRTypes::RT_hasObsContext);
		AddDsrItem(doc, DSRCodedEntryValue("112040", "DCM", "Tracking Unique Identifier"), pDicomSegmentation->GetUniqueIdentifier(), DSRTypes::RT_hasObsContext, DSRTypes::AM_belowCurrent);

		// Segmentation Storage Reference
		assert(std::string("1.2.840.10008.5.1.4.1.1.66.4").compare(pDicomSegmentation->GetSopClassUid().toString()) == 0);
		//DSRImageReferenceValue dsrImageRefObj("1.2.840.10008.5.1.4.1.1.66.4", iter->GetSopInstanceUid());
		DSRImageReferenceValue dsrImage(pDicomSegmentation->GetSopClassUid().toString(), pDicomSegmentation->GetSopInstanceUid().toString());
		nodeId = doc.getTree().addContentItem(DSRTypes::RT_inferredFrom, DSRTypes::VT_Image);
		ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz006", "Segmentation"));
		ofCondition = doc.getTree().getCurrentContentItem().setImageReference(dsrImage);

		// Segmented Image Reference
		const Image* pImage = this->FindDicomImage(annotation, pDicomSegmentation->GetReferencedSopInstanceUid());
		if (!pImage)
		{
			assert(false); // Image must be referenced in the Annotation
			std::string exMsg = "Segmented image referenced by Segmentation SOP is not part of Image Reference collection. [referencedSopInstanceUID=" + pDicomSegmentation->GetReferencedSopInstanceUid().toString() + "]";
			throw std::runtime_error(exMsg.c_str());
		}
		DSRImageReferenceValue dsrImageRefObj(pImage->GetSopClassUid().toString(), pImage->GetSopInstanceUid().toString());
		nodeId = doc.getTree().addContentItem(DSRTypes::RT_inferredFrom, DSRTypes::VT_Image);
		ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz047", "Segmented Image"));
		ofCondition = doc.getTree().getCurrentContentItem().setImageReference(dsrImageRefObj);

		AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz060", "Segmentation Number"), pDicomSegmentation->GetSegmentNumber(), DSRCodedEntryValue("1", "UCUM", "No units"), DSRTypes::RT_hasObsContext);

		nodeId = doc.getTree().goUp(); // step out of the item
	}
}

void DcmModelInternal::PopulateMarkups(const ImageAnnotation& annotation, DSRDocument &doc, bool nestFirst)
{
	const MarkupEntityPtrVector& markups = annotation.GetMarkupEntityCollection();

	for (MarkupEntityPtrVector::const_iterator iter = markups.begin(); iter < markups.end(); iter++)
	{
		assert(*iter);
		if (!(*iter))
			continue;

		bool isNested = nestFirst && iter == markups.begin();

		const TextAnnotationEntity* pTextAnnotation = dynamic_cast<const TextAnnotationEntity*>(*iter);

		if (pTextAnnotation)
		{
			if (isNested)
				AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz028", "Text Annotation"), DSRTypes::RT_contains, DSRTypes::AM_belowCurrent);
			else
				AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz028", "Text Annotation"), DSRTypes::RT_contains);
			AddDsrItem(doc, DSRCodedEntryValue("112040", "DCM", "Tracking Unique Identifier"), pTextAnnotation->GetUniqueIdentifier(), DSRTypes::RT_hasObsContext, DSRTypes::AM_belowCurrent);
			AddDsrItem(doc, DSRCodedEntryValue("G-D315", "SRT", "Text value"), pTextAnnotation->GetText(), DSRTypes::RT_hasObsContext);
			if (!pTextAnnotation->GetFont().empty())
				AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz125", "Font"), pTextAnnotation->GetFont(), DSRTypes::RT_hasObsContext);
			if (!pTextAnnotation->GetFontColor().empty())
				AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz126", "Font Color"), pTextAnnotation->GetFontColor(), DSRTypes::RT_hasObsContext);
			if (!pTextAnnotation->GetFontEffect().empty())
				AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz127", "Font Effect"), pTextAnnotation->GetFontEffect(), DSRTypes::RT_hasObsContext);
			if (!pTextAnnotation->GetFontSize().empty())
				AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz128", "Font Size"), pTextAnnotation->GetFontSize(), DSRTypes::RT_hasObsContext);
			if (!pTextAnnotation->GetFontStyle().empty())
				AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz129", "Font Style"), pTextAnnotation->GetFontStyle(), DSRTypes::RT_hasObsContext);
			if (!pTextAnnotation->GetTextJustify().empty())
				AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz130", "Text Justify"), pTextAnnotation->GetTextJustify(), DSRTypes::RT_hasObsContext);
			if (!pTextAnnotation->GetFontOpacity().empty())
				AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz131", "Font Opacity"), pTextAnnotation->GetFontOpacity(), DSRTypes::RT_hasObsContext);
			
			if (pTextAnnotation->GetGeometricShapeEntity())
				this->PopulateGeometricShapeEntity(annotation, doc, *pTextAnnotation->GetGeometricShapeEntity(), DSRTypes::RT_contains, false);

			nodeId = doc.getTree().goUp(); // step out to the Text Annotation container
		}
		else
		{
			const GeometricShapeEntity* pGeoShape = dynamic_cast<const GeometricShapeEntity*>(*iter);
			assert(pGeoShape);
			if (!pGeoShape)
				continue;
			this->PopulateGeometricShapeEntity(annotation, doc, *pGeoShape, DSRTypes::RT_contains, isNested);
		}
	}
}

void DcmModelInternal::PopulateGeometricShapeEntity(const ImageAnnotation& annotation, DSRDocument& doc, const GeometricShapeEntity& geoShape, DSRTypes::E_RelationshipType relWithParent, bool isNested)
{
// TODO - use different node type here: we used to have it as VT_Text
	// NOTE: the same code is used for both concept and code payload
	_dsrCode = AIMCodes::CreateAimCodedEntryValue("zzz022", "Geometric Shape");
	if (isNested)
		AddDsrItem(doc, _dsrCode, _dsrCode, relWithParent, DSRTypes::AM_belowCurrent);
	else
		AddDsrItem(doc, _dsrCode, _dsrCode, relWithParent);
	AddDsrItem(doc, DSRCodedEntryValue("112040", "DCM", "Tracking Unique Identifier"), geoShape.GetUniqueIdentifier(), DSRTypes::RT_hasObsContext, DSRTypes::AM_belowCurrent);

	const TwoDimensionGeometricShapeEntity* pTwoDGeoShape = dynamic_cast<const TwoDimensionGeometricShapeEntity*>(&geoShape);
	const ThreeDimensionGeometricShapeEntity* pThreeDGeoShape = dynamic_cast<const ThreeDimensionGeometricShapeEntity*>(&geoShape);
	assert(pTwoDGeoShape || pThreeDGeoShape);

	if (pTwoDGeoShape)
	{
		DSRSpatialCoordinatesValue dsrSpatialCoord;
		switch(pTwoDGeoShape->GetShapeType())
		{
		case TwoDimensionGeometricShapeEntity::Point_2D:
			dsrSpatialCoord = DSRSpatialCoordinatesValue(DSRTypes::GT_Point);
			break;
		case TwoDimensionGeometricShapeEntity::Circle_2D:
			dsrSpatialCoord = DSRSpatialCoordinatesValue(DSRTypes::GT_Circle);
			break;
		case TwoDimensionGeometricShapeEntity::Multipoint_2D:
			dsrSpatialCoord = DSRSpatialCoordinatesValue(DSRTypes::GT_Multipoint);
			break;
		case TwoDimensionGeometricShapeEntity::Polyline_2D:
			dsrSpatialCoord = DSRSpatialCoordinatesValue(DSRTypes::GT_Polyline);
			break;
		case TwoDimensionGeometricShapeEntity::Ellipse_2D:
			dsrSpatialCoord = DSRSpatialCoordinatesValue(DSRTypes::GT_Ellipse);
			break;
		case TwoDimensionGeometricShapeEntity::Unknown:
		default:
			assert(false); // unknown shape type!
		}

		for (TwoDimensionSpatialCoordinateVector::const_iterator coordIter = pTwoDGeoShape->GetTwoDimensionSpatialCoordinateCollection().begin(); coordIter < pTwoDGeoShape->GetTwoDimensionSpatialCoordinateCollection().end(); coordIter++)
		{
			dsrSpatialCoord.getGraphicDataList().addItem((Float32)coordIter->GetX(), (Float32)coordIter->GetY());
		}
		nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasProperties, DSRTypes::VT_SCoord);
		ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz022", "Geometric Shape"));
		ofCondition = doc.getTree().getCurrentContentItem().setSpatialCoordinates(dsrSpatialCoord);

		// TODO - verify that SCOORD works without an image reference!!!
		// Image Reference
		if (pTwoDGeoShape->GetImageReferenceUid())
		{
			const Image* pImage = FindDicomImage(annotation, *pTwoDGeoShape->GetImageReferenceUid());
			assert(pImage != NULL); // We must have the image
			if (!pImage)
			{
				std::string exMsg(_T("Image referenced by 2D Geometric Shape is not part of the Image Reference collection. [SOPClassUID=") + pTwoDGeoShape->GetImageReferenceUid()->toString() + _T("]"));
				throw std::runtime_error(exMsg.c_str());
			}
			DSRImageReferenceValue dsrImage(pImage->GetSopClassUid().toString(), pImage->GetSopInstanceUid().toString());
			if (pTwoDGeoShape->GetReferencedFrameNumber() >= 1)
				dsrImage.getFrameList().addOnlyNewItem(pTwoDGeoShape->GetReferencedFrameNumber());
			nodeId = doc.getTree().addContentItem(DSRTypes::RT_selectedFrom, DSRTypes::VT_Image, DSRTypes::AM_belowCurrent);
			ofCondition = doc.getTree().getCurrentContentItem().setImageReference(dsrImage);
			nodeId = doc.getTree().goUp(); // step out of the Image Reference container
		}

		// URI
		if (!pTwoDGeoShape->GetUri().empty())
			AddDsrItem(doc, DSRCodedEntryValue("C42778", "NCI", "UIR"), pTwoDGeoShape->GetUri(), DSRTypes::RT_hasProperties);
	}
	else if (pThreeDGeoShape)
	{
		DSRSpatialCoordinates3DValue dsrSpatialCoord;
		switch(pThreeDGeoShape->GetShapeType())
		{
		case ThreeDimensionGeometricShapeEntity::Ellipsoid_3D:
			dsrSpatialCoord = DSRSpatialCoordinates3DValue(DSRTypes::GT3_Ellipsoid);
			break;
		case ThreeDimensionGeometricShapeEntity::Ellipse_3D:
			dsrSpatialCoord = DSRSpatialCoordinates3DValue(DSRTypes::GT3_Ellipse);
			break;
		case ThreeDimensionGeometricShapeEntity::Point_3D:
			dsrSpatialCoord = DSRSpatialCoordinates3DValue(DSRTypes::GT3_Point);
			break;
		case ThreeDimensionGeometricShapeEntity::Multipoint_3D:
			dsrSpatialCoord = DSRSpatialCoordinates3DValue(DSRTypes::GT3_Multipoint);
			break;
		case ThreeDimensionGeometricShapeEntity::Polyline_3D:
			dsrSpatialCoord = DSRSpatialCoordinates3DValue(DSRTypes::GT3_Polyline);
			break;
		case ThreeDimensionGeometricShapeEntity::Polygon_3D:
			dsrSpatialCoord = DSRSpatialCoordinates3DValue(DSRTypes::GT3_Polygon);
			break;
		default:
			assert(false); // unknown shape type!
		}

		for (ThreeDimensionSpatialCoordinateVector::const_iterator coordIter = pThreeDGeoShape->GetThreeDimensionSpatialCoordinateCollection().begin(); coordIter < pThreeDGeoShape->GetThreeDimensionSpatialCoordinateCollection().end(); coordIter++)
		{
			dsrSpatialCoord.getGraphicDataList().addItem((Float32)coordIter->GetX(), (Float32)coordIter->GetY(), (Float32)coordIter->GetZ());
		}

		// FrameOfReferenceUID
		if (pThreeDGeoShape->GetFrameOfReferenceUid())
			dsrSpatialCoord.setFrameOfReferenceUID(pThreeDGeoShape->GetFrameOfReferenceUid()->toString());
		// FiducialUID
		if (pThreeDGeoShape->GetFiducialUid())
			dsrSpatialCoord.setFiducialUID(pThreeDGeoShape->GetFiducialUid()->toString());

		nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasProperties, DSRTypes::VT_SCoord3D);
		ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz022", "Geometric Shape"));
		ofCondition = doc.getTree().getCurrentContentItem().setSpatialCoordinates3D(dsrSpatialCoord);
	}

	// Other common GeoShape attributes
	AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz021", "Include Flag"), AIMCodes::GetBooleanCodeValue(geoShape.GetIncludeFlag()), DSRTypes::RT_hasProperties);
	AddDsrItem(doc, DSRCodedEntryValue("112039", "DCM", "Tracking Identifier"), geoShape.GetShapeIdentifier(), DSRCodedEntryValue("1", "UCUM", "No units"), DSRTypes::RT_hasObsContext);
	if (!geoShape.GetQuestionTypeCode().empty())
		AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz071", "Question Type Code"), geoShape.GetQuestionTypeCode(), DSRTypes::RT_hasProperties);
	if (geoShape.GetQuestionIndex() != -1)
		AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz085", "Question Index"), geoShape.GetQuestionIndex(), DSRCodedEntryValue("1", "UCUM", "No units"), DSRTypes::RT_hasProperties);
	if (!geoShape.GetLabel().empty())
		AddDsrItem(doc, DSRCodedEntryValue("C45561", "NCI", "A brief description given for purposes of identification"), geoShape.GetLabel(), DSRTypes::RT_hasObsContext);
	if (!geoShape.GetDescription().empty())
		AddDsrItem(doc, DSRCodedEntryValue("C25365", "NCI", "Description"), geoShape.GetDescription(), DSRTypes::RT_hasObsContext);
	if (!geoShape.GetComment().empty())
		AddDsrItem(doc, DSRCodedEntryValue("121106", "DCM", "Comment"), geoShape.GetComment(), DSRTypes::RT_hasObsContext);
	if (!geoShape.GetLineColor().empty())
		AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz132", "Line Color"), geoShape.GetLineColor(), DSRTypes::RT_hasProperties);
	if (!geoShape.GetLineOpacity().empty())
		AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz133", "Line Opacity"), geoShape.GetLineOpacity(), DSRTypes::RT_hasProperties);
	if (!geoShape.GetLineStyle().empty())
		AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz134", "Line Style"), geoShape.GetLineStyle(), DSRTypes::RT_hasProperties);
	if (!geoShape.GetLineThickness().empty())
		AddDsrItem(doc, AIMCodes::CreateAimCodedEntryValue("zzz135", "Line Thickness"), geoShape.GetLineThickness(), DSRTypes::RT_hasProperties);
	if (geoShape.GetInterpolationMethod())
		AddDsrItem(doc, DSRCodedEntryValue("C81208", "NCI", "Interpolation Imputation Technique"), *geoShape.GetInterpolationMethod(), DSRTypes::RT_hasProperties);

	nodeId = doc.getTree().goUp(); // step out of the Geometric Shape code
}

const Image* DcmModelInternal::FindDicomImage(const ImageAnnotation& annotation, const iso_21090::II& sopInstanceUid)
{
	for(ImageReferenceEntityPtrVector::const_iterator iter = annotation.GetImageReferenceEntityCollection().begin(); iter < annotation.GetImageReferenceEntityCollection().end(); iter++)
	{
		if ((*iter)->GetImageReferenceEntityType() == ImageReferenceEntity::T_DICOM_IMAGE_REF)
		{
			const DicomImageReferenceEntity* pDicomImageRef = static_cast<const DicomImageReferenceEntity*>(*iter);

			const Image* pImage = pDicomImageRef->GetImageStudy().GetImage(sopInstanceUid);
			if (pImage != NULL)
				return pImage;
		}
	}

	return NULL;
}

/*
	Adds tree node of type VT_Container
*/
void DcmModelInternal::AddDsrItem(DSRDocument& doc, const DSRCodedEntryValue& concept, DSRTypes::E_RelationshipType relType, DSRTypes::E_AddMode addMode)
{
	nodeId = doc.getTree().addContentItem(relType, DSRTypes::VT_Container, addMode);
	ofCondition = doc.getTree().getCurrentContentItem().setConceptName(concept);
}

/*
	Adds tree node of type VT_Text
*/
void DcmModelInternal::AddDsrItem(DSRDocument& doc, const DSRCodedEntryValue& concept, const std::string& value, DSRTypes::E_RelationshipType relType, DSRTypes::E_AddMode addMode)
{
	nodeId = doc.getTree().addContentItem(relType, DSRTypes::VT_Text, addMode);
	ofCondition = doc.getTree().getCurrentContentItem().setConceptName(concept);
	ofCondition = doc.getTree().getCurrentContentItem().setStringValue(value);
}

/*
	Adds tree node of type VT_Num with INT value
*/
void DcmModelInternal::AddDsrItem(DSRDocument& doc, const DSRCodedEntryValue& concept, int value, const DSRCodedEntryValue& units, DSRTypes::E_RelationshipType relType, DSRTypes::E_AddMode addMode)
{
	nodeId = doc.getTree().addContentItem(relType, DSRTypes::VT_Num, addMode);
	ofCondition = doc.getTree().getCurrentContentItem().setConceptName(concept);
	ofString.assign(AIMUtil::IntToString(value));
	ofCondition = doc.getTree().getCurrentContentItem().setNumericValue(DSRNumericMeasurementValue(ofString, units));
}

/*
	Adds tree node of type VT_Num with DOUBLE value
*/
void DcmModelInternal::AddDsrItem(DSRDocument& doc, const DSRCodedEntryValue& concept, double value, const DSRCodedEntryValue& units, DSRTypes::E_RelationshipType relType, DSRTypes::E_AddMode addMode)
{
	nodeId = doc.getTree().addContentItem(relType, DSRTypes::VT_Num, addMode);
	ofCondition = doc.getTree().getCurrentContentItem().setConceptName(concept);
	ofString.assign(AIMUtil::DoubleToString(value));
	ofCondition = doc.getTree().getCurrentContentItem().setNumericValue(DSRNumericMeasurementValue(ofString, units));
}

/*
	Adds tree node of type VT_DateTime
*/
void DcmModelInternal::AddDsrItem(DSRDocument& doc, const DSRCodedEntryValue& concept, const DateTime& value, DSRTypes::E_RelationshipType relType, DSRTypes::E_AddMode addMode)
{
	OFDateTime ofDateTime = AIMUtil::DateTimeConvert(value);
	ofDateTime = ofDateTime.isValid() ? ofDateTime : OFDateTime::getCurrentDateTime();

	std::string formattedDateTime; // YYYYMMDDHHMMSS
	if (ofDateTime.getISOFormattedDateTime(formattedDateTime, true, false, false, false))
	{
		nodeId = doc.getTree().addContentItem(relType, DSRTypes::VT_DateTime, addMode);
		ofCondition = doc.getTree().getCurrentContentItem().setConceptName(concept);
		ofCondition = doc.getTree().getCurrentContentItem().setStringValue(formattedDateTime);

	//	nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasObsContext, DSRTypes::VT_Code);
	//	ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("121135", "DCM", "Observation Datetime Qualifier"));
	//	ofCondition = doc.getTree().getCurrentContentItem().setCodeValue(DSRCodedEntryValue("121136", "DCM", "DateTime Unsynchronized"));
	// OR
	//ofCondition = doc.getTree().getCurrentContentItem().setCodeValue(DSRCodedEntryValue("121137", DCM, "DateTime Estimated");
	}
	else
	{
		assert(false); // invlaid DateTime
	}
}

/*
	Adds tree node of type VT_Code for given CodedEntryValue
*/
void DcmModelInternal::AddDsrItem(DSRDocument& doc, const DSRCodedEntryValue& concept, const DSRCodedEntryValue& value, DSRTypes::E_RelationshipType relType, DSRTypes::E_AddMode addMode)
{
	nodeId = doc.getTree().addContentItem(relType, DSRTypes::VT_Code, addMode);
	ofCondition = doc.getTree().getCurrentContentItem().setConceptName(concept);
	ofCondition = doc.getTree().getCurrentContentItem().setCodeValue(value);
}

/*
	Adds tree node of type VT_UIDRef
*/
void DcmModelInternal::AddDsrItem(DSRDocument& doc, const DSRCodedEntryValue& concept, const iso_21090::II& value, DSRTypes::E_RelationshipType relType, DSRTypes::E_AddMode addMode)
{
	nodeId = doc.getTree().addContentItem(relType, DSRTypes::VT_UIDRef, addMode);
	ofCondition = doc.getTree().getCurrentContentItem().setConceptName(concept);
	ofCondition = doc.getTree().getCurrentContentItem().setStringValue(value.toString());
}

/*
	Adds tree node of type VT_Code for the given CD value
*/
void DcmModelInternal::AddDsrItem(DSRDocument& doc, const DSRCodedEntryValue& concept, const iso_21090::CD& value, DSRTypes::E_RelationshipType relType, DSRTypes::E_AddMode addMode)
{
	nodeId = doc.getTree().addContentItem(relType, DSRTypes::VT_Code, addMode);
	ofCondition = doc.getTree().getCurrentContentItem().setConceptName(concept);
	ofCondition = doc.getTree().getCurrentContentItem().setCodeValue(AIMCodes::CreateCodedEntryValueFromCd(value));
}

/*
	Adds tree node of type VT_Code and its children of type VT_Code for the given CDVector value
*/
size_t DcmModelInternal::AddDsrItem(DSRDocument& doc, const DSRCodedEntryValue& concept, const iso_21090::CDVector& value, DSRTypes::E_RelationshipType relType, DSRTypes::E_AddMode addMode, bool doNotStepOut)
{
	size_t initialNestingLevel = doc.getTree().getLevel();

	bool isFirstSubValue = true;
	// CDVector nodes (i>1) are nested 1 level with HAS OBS CONTEXT relationship type
	for (iso_21090::CDVector::const_iterator iter = value.begin(); iter < value.end(); iter++)
	{
		if (iter == value.begin())
			nodeId = doc.getTree().addContentItem(relType, DSRTypes::VT_Code, addMode);
		else
		{
			nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasObsContext, DSRTypes::VT_Code, isFirstSubValue ? DSRTypes::AM_belowCurrent : DSRTypes::AM_afterCurrent);
			isFirstSubValue = false;
		}
		ofCondition = doc.getTree().getCurrentContentItem().setConceptName(concept);
		ofCondition = doc.getTree().getCurrentContentItem().setCodeValue(AIMCodes::CreateCodedEntryValueFromCd(*iter));
	}

	// Returns to the 1-st Code's level
	if (!doNotStepOut && !isFirstSubValue)
		nodeId = doc.getTree().goUp();

	return doc.getTree().getLevel() - initialNestingLevel;
}
