/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"
#include "DcmModelInternal.h"

#include "../AIMUtil.h"
#include "../AIMCodes.h"

#include "BaseModel.h" // for AIM MODEL VERSION

#include "../memdebug.h"

using namespace aim_lib;

DcmModelInternal::DcmModelInternal(const std::string& uidPrefix) : _pDoc(NULL)
{
	_uidPrefix = uidPrefix;
}

DcmModelInternal::~DcmModelInternal(void)
{
	if (_pDoc != NULL)
	{
		delete _pDoc;
		_pDoc = NULL;
	}
}

OFCondition DcmModelInternal::WriteDocToFile(const DSRDocument& dsrdoc, const std::string& fileName)
{
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

DSRDocument* DcmModelInternal::CreateDSRDocument(const AnnotationPtrVector& annotations, std::ostream* outputFile)
//DSRDocument* DcmModelInternal::CreateDSRDocument(const AnnotationPtrVector& annotations, const DicomTagCollection& headerValues, ostream* outputFile)
{
	// Make sure that we work with a dense annotations vector
	AnnotationPtrVector realAnnotations;
	for(AnnotationPtrVector::const_iterator iter = annotations.begin(); iter < annotations.end(); iter++)
	{
		if (*iter != NULL)
			realAnnotations.push_back(*iter);
	}
	if (realAnnotations.empty())
		return NULL;

	DSRDocument* pDoc = new DSRDocument(DSRTypes::DT_ComprehensiveSR);
	//DSRDocumentTreeNode* node;

	if (pDoc == NULL)
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
	this->InitilializeHeaderValues(realAnnotations, localHeaderValues);

	// 1. Create document's DICOM headers
	this->CreateDSRDocumentHeaders(*pDoc, localHeaderValues);

	// 2.  Create AIM SR Container
	this->CreateAimSRContainer(realAnnotations, *pDoc);

	// 3. Add annotations to the SR container
	for(AnnotationPtrVector::const_iterator iter = realAnnotations.begin(); iter < realAnnotations.end(); iter++)
	{
		this->PopulateAnnotationEntity(**iter, *pDoc);
	}

	realAnnotations.clear();

	// Debug Code
	bool validFlag = pDoc->isValid();
	char buf[255];
	sprintf(buf, "Document is %sValid", validFlag ? "" : "NOT ");
	printDebug(buf);
	//contentTree.dicomToReadableDate printMessage(&ofConsole, buf);
	//pDoc->print(&ofConsole, buf);

	// Dump current doc to the console
	ofCondition = pDoc->print(std::cout);

	// Dump doc's context as XML as well
	if (outputFile == NULL)
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
// EX: If all annotations are Image Annotations and the annotations belong to the same study, SR will belong to the same study
void DcmModelInternal::InitilializeHeaderValues(const AnnotationPtrVector& annotations, DicomTagCollection& headerValues)
{
	bool hasOnlyImgAnnotations = true;

	// NOTE:
	// In addition to setting the values, this code includes basic sanity checks.
	// Though nothing prevents users from creating semanticly invalid objects,
	// debug builds assert some consistency by going through all available annotations and testing for a few basic things:
	// - image annotation has to have images from the same study
	for(AnnotationPtrVector::const_iterator iter = annotations.begin(); iter < annotations.end(); iter++)
	{
		const Annotation* pAnnotation = *iter;

		bool isImageAnnotation = pAnnotation->GetAnnotationKind() == Annotation::AK_ImageAnnotation;
		hasOnlyImgAnnotations = hasOnlyImgAnnotations && isImageAnnotation;

		// Equipment
		if (pAnnotation->GetEquipment() != NULL)
		{
			// NOTE: For AnnotationOfAnnotation SetHeaderTag will asssert when mixing annotation from different sources
			this->SetHeaderTag(headerValues, DicomTagCollection::ADT_MANUFACTURE, pAnnotation->GetEquipment()->GetManufacturerName());
			this->SetHeaderTag(headerValues, DicomTagCollection::ADT_MANUFACTURES_MODEL_NAME, pAnnotation->GetEquipment()->GetManufacturerModelName());
			this->SetHeaderTag(headerValues, DicomTagCollection::ADT_SOFTWARE_VERSIONS, pAnnotation->GetEquipment()->GetSoftwareVersion());
		}

		if (isImageAnnotation)
		{
			const ImageAnnotation* pImgAnnotation = (const ImageAnnotation*)pAnnotation;

			// Patient Info
			//if (pImgAnnotation->GetPatient() != NULL)
			{
				Person patient = pImgAnnotation->GetPatient();
				this->SetHeaderTag(headerValues, DicomTagCollection::ADT_PATIENT_ID, patient.GetId());
				this->SetHeaderTag(headerValues, DicomTagCollection::ADT_PATIENTS_NAME, patient.GetName());
				if (patient.GetBirthDate() != aim_lib::Date())
					this->SetHeaderTag(headerValues, DicomTagCollection::ADT_PATIENTS_BIRTH_DATE, patient.GetBirthDate().GetDicomFormatedDate());
				if (!patient.GetSex().empty())
					this->SetHeaderTag(headerValues, DicomTagCollection::ADT_PATIENT_SEX, patient.GetSex());
				if (!patient.GetEthnicGroup().empty())
					this->SetHeaderTag(headerValues, DicomTagCollection::ADT_PATIENT_ETHNIC_GROUP, patient.GetEthnicGroup());
			}

			// Set Study Instance UID
			std::string studyUID;
			for (ImageReferencePtrVector::const_iterator imgIter = pImgAnnotation->GetImageReferenceCollection().begin(); imgIter < pImgAnnotation->GetImageReferenceCollection().end(); imgIter++)
			{
				if ((*imgIter)->GetImageReferenceType() == ImageReference::T_DICOM_IMAGE_REF)
				{
					const DICOMImageReference* pDicomImgRef = (const DICOMImageReference*)*imgIter;
					if (studyUID.empty())
						studyUID = pDicomImgRef->GetStudy().GetInstanceUID();
					else
						assert(studyUID == pDicomImgRef->GetStudy().GetInstanceUID()); //single annotation images have to belong to the same study
					if (hasOnlyImgAnnotations)
						this->SetHeaderTag(headerValues, DicomTagCollection::ADT_STUDY_INSTANCE_UID, pDicomImgRef->GetStudy().GetInstanceUID());
				}
			}
		}
	}

	// Mixed annotaion types have new Study Instance UID
	if (!hasOnlyImgAnnotations)
	{
		headerValues.RemoveTag(DicomTagCollection::ADT_STUDY_INSTANCE_UID);
		headerValues.SetTagValue(DicomTagCollection::ADT_STUDY_INSTANCE_UID, AimUidGenerator::GenerateNewUID(_uidPrefix));
	}
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
	ofString = "AIM DICOM SR";
	ofString.append(" ");
	ofString.append(BaseModel::AIM_MODEL_VERSION);
	doc.setSeriesDescription(ofString);
	// Series Number - always 1
	ofString.assign("1");
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
	// Patient Name - Type 2
	ofString.assign(headerValues.GetTagValue(DicomTagCollection::ADT_PATIENTS_NAME).data());
	if (!ofString.empty()) doc.setPatientName(ofString);
	// Patient ID - Type 2
	ofString.assign(headerValues.GetTagValue(DicomTagCollection::ADT_PATIENT_ID).data());
	if (!ofString.empty()) doc.setPatientID(ofString);
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
	// Missing from standard DCMTK's dsrdoc.cxx/.h:
	// - Institution Name
	// - Institution Address
	// - Station Name
	// - Intitutional Department Name
	// - Manufacture's Model Name
	// - Device Serial Number
	// - Software Version

}

void DcmModelInternal::CreateAimSRContainer(const AnnotationPtrVector& annotations, DSRDocument& doc)
//void DcmModelInternal::CreateAimSRContainer(Annotation& annotation, DSRDocument& doc)
{
	//bool isImageAnnotation = dynamic_cast<ImageAnnotation*>(&annotation) != NULL;
	//bool isAnnotationOfAnnotation = dynamic_cast<AnnotationOfAnnotation*>(&annotation) != NULL;
	//assert(isImageAnnotation || isAnnotationOfAnnotation); // one of these needs to be true
	//assert(!(isImageAnnotation && isAnnotationOfAnnotation)); // only one of these can be true

	assert(!annotations.empty());

	Annotation* pAnnotation = annotations[0]; // 1st annotation

	// Create Document
	nodeId = doc.getTree().addContentItem(DSRTypes::RT_isRoot, DSRTypes::VT_Container);
	ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz001", "AIM SR Report"));

	// AIM Version
	nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasAcqContext, DSRTypes::VT_Text, DSRTypes::AM_belowCurrent);
	ofString.assign(pAnnotation->GetAimVersion().data());
	ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz003", "AIM Version"));
	ofCondition = doc.getTree().getCurrentContentItem().setStringValue(ofString);

	// Language of content items and descendants
	// TODO

	// Observer context
	this->FillObserverInfo(*pAnnotation, doc);


	for(AnnotationPtrVector::size_type ann=0; ann < annotations.size(); ann++)
	{
		bool isImageAnnotation = annotations[ann] != NULL && annotations[ann]->GetAnnotationKind() == Annotation::AK_ImageAnnotation;
		// Image Library
		if (isImageAnnotation)
			this->FillImageLibrary((ImageAnnotation&)*annotations[ann], doc);
	}

	//// Annotations Container
	//nodeId = doc.getTree().addContentItem(DSRTypes::RT_contains, DSRTypes::VT_Container);
	//ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz007", "Annotations"));
}

void DcmModelInternal::FillObserverInfo(Annotation& annotation, DSRDocument& doc)
{
	const User* pUser = annotation.GetUser();
	if (pUser == NULL)
		return;

	// NOTE: observer is always a person for now

	// Person Observer Type
	nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasObsContext, DSRTypes::VT_Code);
	ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("121005", "DCM", "Observer Type"));
	ofCondition = doc.getTree().getCurrentContentItem().setCodeValue(DSRCodedEntryValue("121006", "DCM", "Person"));

	bool isNested = false; // Flag which indicates if nesting has occured yet or not

	// Name
	ofString.assign(pUser->GetName().data());
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
	if (!pUser->GetRoleInTrial().empty())
	{
		_dsrCode = AIMCodes::GetPerformingRoleValue(pUser->GetRoleInTrial());
		if (_dsrCode == AIMCodes::EmptyCodedEntryValue)
		{
			std::string errString = std::string("Invalid  observer role: ") + pUser->GetRoleInTrial() + ".";
			printDebug(errString.c_str());
		}
		else
		{
			nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasObsContext, DSRTypes::VT_Code, isNested ? DSRTypes::AM_afterCurrent : DSRTypes::AM_belowCurrent);
			ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("121011", "DCM", "Person Observer's Role in this Procedure"));
			ofCondition = doc.getTree().getCurrentContentItem().setCodeValue(_dsrCode);
			isNested = true;
		}
	}

	// Observer Login
	ofString.assign(pUser->GetLoginName().data());
	if (ofString.empty())
	{
		assert(false); // login name is required
	}
	else
	{
		nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasObsContext, DSRTypes::VT_Text, isNested ? DSRTypes::AM_afterCurrent : DSRTypes::AM_belowCurrent);
		ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz026", "Person Observer's Login Name"));
		ofCondition = doc.getTree().getCurrentContentItem().setStringValue(ofString);
		isNested = true;
	}

	// Observer Role Number in Trial
	if (pUser->GetNumberWithinRoleOfClinicalTrial() >= 0)
	{
		nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasObsContext, DSRTypes::VT_Text, isNested ? DSRTypes::AM_afterCurrent : DSRTypes::AM_belowCurrent);
		ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz045", "Person Observer's Number within Role of Clinical Trial"));
		ofString.assign(AIMUtil::IntToString(pUser->GetNumberWithinRoleOfClinicalTrial()).data());
		ofCondition = doc.getTree().getCurrentContentItem().setStringValue(ofString);
		isNested = true;
	}

	if(isNested)
		nodeId = doc.getTree().goUp(); // step out of the nesting container
}

void DcmModelInternal::FillImageLibrary(ImageAnnotation& imgAnnotation, DSRDocument& doc)
{
	const ImageReferencePtrVector& imgReferences = imgAnnotation.GetImageReferenceCollection();
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
		nodeId = doc.getTree().goDown(); // step into Image Reference container. Assumes that before we're at the Image Ref. Container level
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

	size_t imgContainerId = nodeId;
	for(ImageReferencePtrVector::const_iterator iter = imgReferences.begin(); iter < imgReferences.end(); iter++)
	{
		// TODO - make sure to add only UNIQUE image references
		if ((*iter)->GetImageReferenceType() == ImageReference::T_DICOM_IMAGE_REF)
		{
			DICOMImageReference* pDicomImgRef = (DICOMImageReference*)(*iter);

			// 1. make sure that this image reference is not in the image library yet
			//DSRCodedEntryValue("111028", "DCM", "Image Library")
			//DSRImageReferenceValue dsrImage = DSRImageReferenceValue("SOPClassUID", pDicomImgRef->GetDicomSOPInstanceUID().data());
			//nodeId = doc.getTree().gotoNamedNode(dsrImage);

			const ImageStudy& currentStudy = pDicomImgRef->GetStudy();
			const ImageSeries& currentSeries = currentStudy.GetSeries();
			const ImageVector& images = currentSeries.GetImageCollection();
			for(ImageVector::const_iterator imgIter = images.begin(); imgIter < images.end(); imgIter++)
			{
				// 2. Add image reference to the image library
				if (!hadExistingImgLib && iter == imgReferences.begin() && imgIter == images.begin())
					nodeId = doc.getTree().addContentItem(DSRTypes::RT_contains, DSRTypes::VT_Image, DSRTypes::AM_belowCurrent);
				else
					nodeId = doc.getTree().addContentItem(DSRTypes::RT_contains, DSRTypes::VT_Image);
				ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz034", "Image Library Entry"));
				ofCondition = doc.getTree().getCurrentContentItem().setImageReference(DSRImageReferenceValue(imgIter->GetSopClassUID().c_str(), imgIter->GetSopInstanceUID().c_str()));

				// Only first item should be nested one level deep. The rest are on the same level
				DSRTypes::E_AddMode nextAddMode = DSRTypes::AM_belowCurrent;

				// Study Instance UID
				nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasAcqContext, DSRTypes::VT_UIDRef, nextAddMode);
				ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("110180", "DCM", "Study Instance UID"));
				ofCondition = doc.getTree().getCurrentContentItem().setStringValue(currentStudy.GetInstanceUID().c_str());

				nextAddMode = DSRTypes::AM_afterCurrent;

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

				// Series Instance UID
				nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasAcqContext, DSRTypes::VT_UIDRef, nextAddMode);
				ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("112002", "DCM", "Series Instance UID"));
				ofCondition = doc.getTree().getCurrentContentItem().setStringValue(currentSeries.GetInstanceUID().c_str());

				// Presentation State
				// NOTE: This is duplicated for each image. Reader will collapse all PS references back into a single collection.
				for(PresentationStateVector::const_iterator psIter = pDicomImgRef->GetPresentationStateCollection().begin(); psIter < pDicomImgRef->GetPresentationStateCollection().end(); psIter++)
				{
					nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasAcqContext, DSRTypes::VT_UIDRef, nextAddMode);
					ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz069", "Presentation State Instance UID"));
					ofCondition = doc.getTree().getCurrentContentItem().setStringValue(psIter->GetSopInstanceUID().c_str());
				}

				// Step out to the Image container
				nodeId = doc.getTree().goUp();
			}

		}
		else if ((*iter)->GetImageReferenceType() == ImageReference::T_WEB_IMAGE_REF)
		{
			WebImageReference* pWebImgRef = (WebImageReference*)(*iter);

			// TODO - what happens here for SR?
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

void DcmModelInternal::PopulateAnnotationEntity(Annotation& annotation, DSRDocument& doc)
{
	bool isImageAnnotation = dynamic_cast<ImageAnnotation*>(&annotation) != NULL;
	bool isAnnotationOfAnnotation = dynamic_cast<AnnotationOfAnnotation*>(&annotation) != NULL;

	// Annotation Entity Container
	nodeId = doc.getTree().addContentItem(DSRTypes::RT_contains, DSRTypes::VT_Container/*, DSRTypes::AM_belowCurrent*/);
	ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz002", "AIM Annotation"));

	// Annotation Date Time
	// DateTime is set when the annotation's DateTime is different from the document's only
	OFDateTime annDateTime = AIMUtil::DateTimeConvert(annotation.GetDateTime());
	if (annDateTime.isValid())
	{
		ofString = doc.getContentDate(ofString) + doc.getContentTime(); // document's DateTime
		OFString ofDateTime; // YYYYMMDDHHMMSS
		if (annDateTime.getISOFormattedDateTime(ofDateTime, true, false, false, false) && ofDateTime != ofString)
		{
			ofCondition = doc.getTree().getCurrentContentItem().setObservationDateTime(ofDateTime);
			//nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasObsContext, DSRTypes::VT_DateTime);
			//ofCondition = doc.getTree().getCurrentContentItem().setStringValue(ofDateTime);
			//ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("121125", "DCM", "Datetime of Recording of Log Entry"));

//			nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasObsContext, DSRTypes::VT_Code);
//			ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("121135", "DCM", "Observation Datetime Qualifier"));
//			ofCondition = doc.getTree().getCurrentContentItem().setCodeValue(DSRCodedEntryValue("121136", "DCM", "DateTime Unsynchronized"));
			// OR
			//ofCondition = doc.getTree().getCurrentContentItem().setCodeValue(DSRCodedEntryValue("121137", DCM, "DateTime Estimated");
		}
	}

	// Annotation UID
	nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasAcqContext, DSRTypes::VT_UIDRef, DSRTypes::AM_belowCurrent);
	ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("112040", "DCM", "Tracking Unique Identifier"));
	ofString.assign(annotation.GetUniqueIdentifier().data());
	ofCondition = doc.getTree().getCurrentContentItem().setStringValue(ofString);

	// Annotation Type
	nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasAcqContext, DSRTypes::VT_Code);
	ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz005", "Annotation Type"));
	ofCondition = doc.getTree().getCurrentContentItem().setCodeValue(AIMCodes::CreateCodedEntryValue(annotation.GetCodeValue(), annotation.GetCodeMeaning(), annotation.GetCodingSchemeDesignator(), annotation.GetCodingSchemeVersion()));

	// Annotation Name
	nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasAcqContext, DSRTypes::VT_Text);
	ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("112039", "DCM", "Tracking Identifier"));
	//ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("zzz035", AIM_CODING_SCHEME_DESIGNATOR, "Annotation Name"));
	ofString.assign(annotation.GetName().data());
	ofCondition = doc.getTree().getCurrentContentItem().setStringValue(ofString);

	// Annotation Comment
	if (!annotation.GetComment().empty())
	{
		nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasObsContext, DSRTypes::VT_Text);
		ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("121106", "DCM", "Comment"));
		ofString.assign(annotation.GetComment().data());
		ofCondition = doc.getTree().getCurrentContentItem().setStringValue(ofString);
	}

	// Precedent Referenced Annotation UID
	if (!annotation.GetPrecedentReferencedAnnotationUID().empty())
	{
		nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasObsContext, DSRTypes::VT_UIDRef);
		ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz068", "Precedent AIM Annotation"));
		ofString.assign(annotation.GetPrecedentReferencedAnnotationUID().data());
		ofCondition = doc.getTree().getCurrentContentItem().setStringValue(ofString);
	}

	// AIM Status
	if (annotation.GetAimStatus() != NULL)
	{
		const AimStatus* pAimStatus = annotation.GetAimStatus();
		// AIM Status
		assert(!pAimStatus->GetCodeValue().empty());
		assert(!pAimStatus->GetCodeMeaning().empty());
		assert(!pAimStatus->GetCodingSchemeDesignator().empty());
		assert(!pAimStatus->GetCodingSchemeVersion().empty());
		nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasAcqContext, DSRTypes::VT_Code);
		ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz063", "AIM Status"));
		ofCondition = doc.getTree().getCurrentContentItem().setCodeValue(AIMCodes::CreateCodedEntryValue(pAimStatus->GetCodeValue(), pAimStatus->GetCodeMeaning(), pAimStatus->GetCodingSchemeDesignator(), pAimStatus->GetCodingSchemeVersion()));

		// Annotation Version
		nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasObsContext, DSRTypes::VT_Num, DSRTypes::AM_belowCurrent);
		ofString.assign(AIMUtil::DoubleToString(pAimStatus->GetAnnotationVersion()).c_str());
		ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz064", "Annotation Version"));
		ofCondition = doc.getTree().getCurrentContentItem().setNumericValue(DSRNumericMeasurementValue(ofString, DSRCodedEntryValue("1", "UCUM", "No units")));

		// Authorized By
		if (!pAimStatus->GetAuthorizedBy().empty())
		{
			nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasObsContext, DSRTypes::VT_Text);
			ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz065", "Authorized By"));
			ofString.assign(pAimStatus->GetAuthorizedBy().data());
			ofCondition = doc.getTree().getCurrentContentItem().setStringValue(ofString);
		}

		nodeId = doc.getTree().goUp(); // up to the Annotation level
	}

	this->PopulateAnatomicEntityContainer(annotation, doc);
	this->PopulateImagingObservationContainer(annotation, doc);

	this->PopulateCalculationEntries(annotation, doc);

	this->PopulateInferenceContainer(annotation, doc, false);

	// Do annotation-specific operations
	if (isImageAnnotation)
		PopulateImageAnnotation(annotation, doc);
	if(isAnnotationOfAnnotation)
	   PopulateAnnotationOfAnnotation(annotation, doc);

	nodeId = doc.getTree().goUp(); // up to the Annotation level
//	nodeId = doc.getTree().goUp(); // up to the Annotations level
}

void DcmModelInternal::PopulateImageAnnotation(Annotation& annotation, DSRDocument& doc)
{
	ImageAnnotation& imgAnnotation = (ImageAnnotation&)annotation;

	// Add Image Annotation container
	nodeId = doc.getTree().addContentItem(DSRTypes::RT_contains, DSRTypes::VT_Container);
	ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz030", "Image Annotation"));

	size_t containerLevel = doc.getTree().getLevel();

	// nest here because this is the first entry in the parent container
	this->PopulateSegmentationContainer(imgAnnotation, doc, true);

	bool nestNext = containerLevel == doc.getTree().getLevel(); // true if no Segmentations exist
	this->PopulateGeometricShapeContainer(imgAnnotation, doc, nestNext);

	// Need to nest inside the container if no Segmentations and GeoShapes are present
	nestNext = containerLevel == doc.getTree().getLevel();
	TextAnnotationVector textAnnotations = imgAnnotation.GetTextAnnotationCollection();
	for(TextAnnotationVector::iterator iterTextAnnot = textAnnotations.begin(); iterTextAnnot < textAnnotations.end(); iterTextAnnot++)
	{
		// Text Annotation Container
		if (nestNext && iterTextAnnot == textAnnotations.begin())
			nodeId = doc.getTree().addContentItem(DSRTypes::RT_contains, DSRTypes::VT_Container, DSRTypes::AM_belowCurrent);
		else
			nodeId = doc.getTree().addContentItem(DSRTypes::RT_contains, DSRTypes::VT_Container);
		ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz028", "Text Annotation"));

		// Annotation Text
		nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasObsContext, DSRTypes::VT_Text, DSRTypes::AM_belowCurrent);
		ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateCodedEntryValue("G-D315", "SRT", "Text value"));
		ofString.assign(iterTextAnnot->GetText().c_str());
		ofCondition = doc.getTree().getCurrentContentItem().setStringValue(ofString);

		// GeoShape - Multipoint
		const MultiPoint* connectPoints = iterTextAnnot->GetConnectorPoints();
		if (connectPoints != NULL && connectPoints->GetSpatialCoordinateCollection().size() > 0)
			PopulateGeometricShapeEntry(imgAnnotation, doc, *connectPoints, DSRTypes::RT_contains, false);

		nodeId = doc.getTree().goUp(); // step out to the Text Annotation container
	}

	if (containerLevel != doc.getTree().getLevel())
		nodeId = doc.getTree().goUp(); // step out to the Image Annotation container level
}

void DcmModelInternal::PopulateAnnotationOfAnnotation(Annotation& annotation, DSRDocument& doc)
{
	AnnotationOfAnnotation& annAnnotation = (AnnotationOfAnnotation&)annotation;

	// Annotation Of Annotation
	nodeId = doc.getTree().addContentItem(DSRTypes::RT_contains, DSRTypes::VT_Container);
	ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz031", "Annotation of Annotation"));

	ReferencedAnnotationVector referencedAnnotations = annAnnotation.GetReferencedAnnotationCollection();
	if (referencedAnnotations.size() > 0)
	{
		for(ReferencedAnnotationVector::iterator iter = referencedAnnotations.begin(); iter < referencedAnnotations.end(); iter++)
		{
			// Referenced Annotation
			if (iter == referencedAnnotations.begin())
				nodeId = doc.getTree().addContentItem(DSRTypes::RT_contains, DSRTypes::VT_Container, DSRTypes::AM_belowCurrent);
			else
				nodeId = doc.getTree().addContentItem(DSRTypes::RT_contains, DSRTypes::VT_Container);
			ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz062", "Referenced Annotation"));

			// Referenced Annotation UID
			nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasAcqContext, DSRTypes::VT_UIDRef, DSRTypes::AM_belowCurrent);
			ofString.assign(iter->GetReferencedAnnotationUID().c_str());
			ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("112040", "DCM", "Tracking Unique Identifier"));
			ofCondition = doc.getTree().getCurrentContentItem().setStringValue(ofString);

			// Annotation Role
			if (iter->GetAnnotationRole() != NULL)
			{
				AnnotationRole* pAnnotationRole = iter->GetAnnotationRole();
				nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasObsContext, DSRTypes::VT_Code);
				ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz056", "Annotation Role"));
				ofCondition = doc.getTree().getCurrentContentItem().setCodeValue(AIMCodes::CreateCodedEntryValue(
					pAnnotationRole->GetCodeValue(), pAnnotationRole->GetCodeMeaning(), pAnnotationRole->GetCodingSchemeDesignator(), pAnnotationRole->GetCodingSchemeVersion()));

				// Role Sequence Number
				nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasProperties, DSRTypes::VT_Num, DSRTypes::AM_belowCurrent);
				ofString.assign(AIMUtil::IntToString(pAnnotationRole->GetRoleSequenceNumber()).c_str());
				ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz057", "Role Sequence Number"));
				ofCondition = doc.getTree().getCurrentContentItem().setNumericValue(DSRNumericMeasurementValue(ofString, DSRCodedEntryValue("1", "UCUM", "No units")));

				nodeId = doc.getTree().goUp(); // step out to the Annotation Role level
			}

			nodeId = doc.getTree().goUp(); // step out to the Referenced Annotation container level
		}

		nodeId = doc.getTree().goUp(); // step out to the Annotation of Annotation level
	}

	nodeId = doc.getTree().goUp(); // step out to the container level
}

void DcmModelInternal::PopulateAnatomicEntityContainer(Annotation& annotation, DSRDocument& doc)
{
	AnatomicEntityVector anatomicEntities = annotation.GetAnatomicEntityCollection();

	// Add AnatomicEntities container
	//nodeId = doc.getTree().addContentItem(DSRTypes::RT_contains, DSRTypes::VT_Container);
	//ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz008", "Anatomic Entity"));

	if (anatomicEntities.size() > 0)
	{
		for(AnatomicEntityVector::iterator iter = anatomicEntities.begin(); iter < anatomicEntities.end(); iter++)
		{
			//if (iter == anatomicEntities.begin())
			//	nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasObsContext, DSRTypes::VT_Code, DSRTypes::AM_belowCurrent);
			//else
				nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasObsContext, DSRTypes::VT_Code);
			ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz008", "Anatomic Entity"));
			ofCondition = doc.getTree().getCurrentContentItem().setCodeValue(AIMCodes::CreateCodedEntryValue(
				iter->GetCodeValue(), iter->GetCodeMeaning(), iter->GetCodingSchemeDesignator(), iter->GetCodingSchemeVersion()));

			// Label
			nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasObsContext, DSRTypes::VT_Text, DSRTypes::AM_belowCurrent);
			ofString.assign(iter->GetLabel().c_str());
			ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("C45561", "NCI", "A brief description given for purposes of identification"));
			ofCondition = doc.getTree().getCurrentContentItem().setStringValue(ofString);

			bool hasOptionalAttrs = true; // Label takes care of nesting AE children now

			// Annotator Confidence
			if (iter->GetAnnotatorConfidence() != NULL)
			{
				nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasProperties, DSRTypes::VT_Num, hasOptionalAttrs ? DSRTypes::AM_afterCurrent : DSRTypes::AM_belowCurrent);
				ofString.assign(AIMUtil::DoubleToString(*iter->GetAnnotatorConfidence()).c_str());
				ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz058", "Annotator Confidence"));
				ofCondition = doc.getTree().getCurrentContentItem().setNumericValue(DSRNumericMeasurementValue(ofString, DSRCodedEntryValue("%", "UCUM", "%")));
				hasOptionalAttrs = true;
			}

			// IsPresent
			if (iter->GetIsPresent()) // it's true by default
			{
				nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasObsContext, DSRTypes::VT_Code, hasOptionalAttrs ? DSRTypes::AM_afterCurrent : DSRTypes::AM_belowCurrent);
				ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("G-A203", "SRT", "Present"));
				ofCondition = doc.getTree().getCurrentContentItem().setCodeValue(AIMCodes::GetBooleanCodeValue(iter->GetIsPresent()));
				hasOptionalAttrs = true;
			}

			// Anatomic Enity Characteristic
			AnatomicEntityCharacteristicVector anatomicEnitytChars = iter->GetAnatomicEntityCharacteristicCollection();
			for(AnatomicEntityCharacteristicVector::iterator charIter = anatomicEnitytChars.begin(); charIter < anatomicEnitytChars.end(); charIter++)
			{
				DSRTypes::E_AddMode addMode = hasOptionalAttrs ? DSRTypes::AM_afterCurrent : DSRTypes::AM_belowCurrent;
				this->PopulateAnatomicEntityCharEntry(*charIter, doc, addMode);
				hasOptionalAttrs = true;
			}

			if (hasOptionalAttrs)
				nodeId = doc.getTree().goUp(); // step out of the Anotomic Entity container
		}
//		nodeId = doc.getTree().goUp();
	}

	//nodeId = doc.getTree().goUp(); // step out of the Anotomic Entities container
}

void DcmModelInternal::PopulateAnatomicEntityCharEntry(const AnatomicEntityCharacteristic& anatomicEntityChar, DSRDocument& doc, DSRTypes::E_AddMode addMode)
{
	nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasObsContext, DSRTypes::VT_Code, addMode);
	ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz052", "Anatomic Entity Characteristic"));
	ofCondition = doc.getTree().getCurrentContentItem().setCodeValue(AIMCodes::CreateCodedEntryValue(
		anatomicEntityChar.GetCodeValue(), anatomicEntityChar.GetCodeMeaning(), anatomicEntityChar.GetCodingSchemeDesignator(), anatomicEntityChar.GetCodingSchemeVersion()));

	// Label
	nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasObsContext, DSRTypes::VT_Text, DSRTypes::AM_belowCurrent);
	ofString.assign(anatomicEntityChar.GetLabel().c_str());
	ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("C45561", "NCI", "A brief description given for purposes of identification"));
	ofCondition = doc.getTree().getCurrentContentItem().setStringValue(ofString);

	bool hasOptionalAttrs = true; // label takes care of nesting AEC children now

	// Annotator Confidence
	if (anatomicEntityChar.GetAnnotatorConfidence() != NULL)
	{
		nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasProperties, DSRTypes::VT_Num, hasOptionalAttrs ? DSRTypes::AM_afterCurrent : DSRTypes::AM_belowCurrent);
		ofString.assign(AIMUtil::DoubleToString(*anatomicEntityChar.GetAnnotatorConfidence()).c_str());
		ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz058", "Annotator Confidence"));
		ofCondition = doc.getTree().getCurrentContentItem().setNumericValue(DSRNumericMeasurementValue(ofString, DSRCodedEntryValue("%", "UCUM", "%")));
		hasOptionalAttrs = true;
	}

	// Characteristic Quantification
	if (anatomicEntityChar.GetCharacteristicQuantificationCollection().size() > 0)
	{
		this->PopulateCharacteristicQuantificationEntries(anatomicEntityChar.GetCharacteristicQuantificationCollection(), doc, !hasOptionalAttrs);
		hasOptionalAttrs = true; // NOTE: it's assumed that all Characteristic Quantifications are not NULL
	}

	if (hasOptionalAttrs)
		nodeId = doc.getTree().goUp(); // step out to the Anatomic Enitity Char level

	// NOTE: Parent node should take care of this
	//if (addMode == DSRTypes::AM_belowCurrent)
	//	nodeId = doc.getTree().goUp(); // step out of the Anotomic Entity Char container
}

void DcmModelInternal::PopulateCharacteristicQuantificationEntries(const CharacteristicQuantificationPtrVector& charQuantifications, DSRDocument& doc, bool nestFirst)
{
	if (charQuantifications.size() > 0)
	{
		for (CharacteristicQuantificationPtrVector::const_iterator iter = charQuantifications.begin(); iter < charQuantifications.end(); iter++)
		{
			assert(*iter);

			if (nestFirst && iter == charQuantifications.begin())
				nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasObsContext, DSRTypes::VT_Code, DSRTypes::AM_belowCurrent);
			else
				nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasObsContext, DSRTypes::VT_Code);
			ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz066", "Characteristic Quantification"));
			ofCondition = doc.getTree().getCurrentContentItem().setCodeValue(AIMCodes::GetCharacteristicQuantificationTypeValue((*iter)->GetQuantificationType()));

			// Name
			nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasObsContext, DSRTypes::VT_Text, DSRTypes::AM_belowCurrent);
			ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("112039", "DCM", "Tracking Identifier"));
			ofString.assign((*iter)->GetName().c_str());
			ofCondition = doc.getTree().getCurrentContentItem().setStringValue(ofString);

			// Annotator Confidence
			if ((*iter)->GetAnnotatorConfidence() != NULL)
			{
				nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasObsContext, DSRTypes::VT_Num);
				ofString.assign(AIMUtil::DoubleToString(*(*iter)->GetAnnotatorConfidence()).c_str());
				ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz058", "Annotator Confidence"));
				ofCondition = doc.getTree().getCurrentContentItem().setNumericValue(DSRNumericMeasurementValue(ofString, DSRCodedEntryValue("%", "UCUM", "%")));
			}

			switch((*iter)->GetQuantificationType())
			{
			case CharacteristicQuantification::QT_Numerical:
				{
					Numerical* pNumerical = dynamic_cast<Numerical*>(*iter);

					// Value
					nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasProperties, DSRTypes::VT_Num);
					ofString.assign(AIMUtil::DoubleToString(pNumerical->GetValue()).c_str());
					ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("C25712", "NCI", "A numerical quantity measured or assigned or computed"));
					ofCondition = doc.getTree().getCurrentContentItem().setNumericValue(DSRNumericMeasurementValue(ofString, AIMCodes::GetUcumCodeValue(pNumerical->GetUcumString())));

					// Operator
					if (pNumerical->GetOperator() != aim_lib::None)
					{
						nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasObsContext, DSRTypes::VT_Code, DSRTypes::AM_belowCurrent);
						ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("C61580", "NCI", "A Boolean operator, a symbol that denotes a logical operation"));
						ofCondition = doc.getTree().getCurrentContentItem().setCodeValue(AIMCodes::GetComparisonOperatorTypeValue(pNumerical->GetOperator()));

						nodeId = doc.getTree().goUp(); // step out to Characterisitc Quantification level
					}
				}
				break;
			case CharacteristicQuantification::QT_Quantile:
				{
					Quantile* pQuantile = dynamic_cast<Quantile*>(*iter);

					// Bin
					nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasProperties, DSRTypes::VT_Num);
					ofString.assign(AIMUtil::IntToString(pQuantile->GetBin()).c_str());
					ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("C63902", "NCI", "An interval into which a given point does or does not fall"));
					ofCondition = doc.getTree().getCurrentContentItem().setNumericValue(DSRNumericMeasurementValue(ofString, DSRCodedEntryValue("1", "UCUM", "No units")));
				}
				break;
			case CharacteristicQuantification::QT_Non_Quantifiable:
				{
					NonQuantifiable* pNonQuantifiable = dynamic_cast<NonQuantifiable*>(*iter);

					// Code
					nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasProperties, DSRTypes::VT_Code);
					ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz067", "Non-Quantifiable Code"));
					ofCondition = doc.getTree().getCurrentContentItem().setCodeValue(AIMCodes::CreateCodedEntryValue(
						pNonQuantifiable->GetCodeValue(), pNonQuantifiable->GetCodeMeaning(), pNonQuantifiable->GetCodingSchemeDesignator(), pNonQuantifiable->GetCodingSchemeVersion()));
				}
				break;
			case CharacteristicQuantification::QT_Scale:
				{
					Scale* pScale = dynamic_cast<Scale*>(*iter);

					// Value
					nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasProperties, DSRTypes::VT_Text);
					ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("C25712", "NCI", "A numerical quantity measured or assigned or computed"));
					ofString.assign(pScale->GetValue().c_str());
					ofCondition = doc.getTree().getCurrentContentItem().setStringValue(ofString);

					// Comment
					bool hasOptionalAttrs = false;
					if (!pScale->GetComment().empty())
					{
						nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasObsContext, DSRTypes::VT_Text, DSRTypes::AM_belowCurrent);
						ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("121106", "DCM", "Comment"));
						ofString.assign(pScale->GetComment().c_str());
						ofCondition = doc.getTree().getCurrentContentItem().setStringValue(ofString);
						hasOptionalAttrs = true;
					}

					// Description
					if (!pScale->GetDescription().empty())
					{
						nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasObsContext, DSRTypes::VT_Text, hasOptionalAttrs ? DSRTypes::AM_afterCurrent : DSRTypes::AM_belowCurrent);
						ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("C25365", "NCI", "A written or verbal statement or explanation of something"));
						ofString.assign(pScale->GetDescription().c_str());
						ofCondition = doc.getTree().getCurrentContentItem().setStringValue(ofString);
						hasOptionalAttrs = true;
					}

					if (hasOptionalAttrs)
						nodeId = doc.getTree().goUp(); // step out to Characterisitc Quantification level
				}
				break;
			case CharacteristicQuantification::QT_Interval:
				{
					Interval* pInterval = dynamic_cast<Interval*>(*iter);

					// Max Value
					nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasProperties, DSRTypes::VT_Num);
					ofString.assign(AIMUtil::DoubleToString(pInterval->GetMaxValue()).c_str());
					ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("G-A437", "SRT", "Maximum"));
					ofCondition = doc.getTree().getCurrentContentItem().setNumericValue(DSRNumericMeasurementValue(ofString, AIMCodes::GetUcumCodeValue(pInterval->GetUcumString())));

					// Max Operator
					nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasObsContext, DSRTypes::VT_Code, DSRTypes::AM_belowCurrent);
					ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("C61580", "NCI", "A Boolean operator, a symbol that denotes a logical operation"));
					ofCondition = doc.getTree().getCurrentContentItem().setCodeValue(AIMCodes::GetComparisonOperatorTypeValue(pInterval->GetMaxOperator()));

					nodeId = doc.getTree().goUp(); // step out to Characterisitc Quantification level

					// Min Value
					nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasProperties, DSRTypes::VT_Num);
					ofString.assign(AIMUtil::DoubleToString(pInterval->GetMinValue()).c_str());
					ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("R-404FB", "SRT", "Minimum"));
					ofCondition = doc.getTree().getCurrentContentItem().setNumericValue(DSRNumericMeasurementValue(ofString, AIMCodes::GetUcumCodeValue(pInterval->GetUcumString())));

					// Min Operator
					nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasObsContext, DSRTypes::VT_Code, DSRTypes::AM_belowCurrent);
					ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("C61580", "NCI", "A Boolean operator, a symbol that denotes a logical operation"));
					ofCondition = doc.getTree().getCurrentContentItem().setCodeValue(AIMCodes::GetComparisonOperatorTypeValue(pInterval->GetMinOperator()));

					nodeId = doc.getTree().goUp(); // step out to Characterisitc Quantification level
				}
				break;
			default:
				assert(false); // Unknown Charachteristic Quantification type
			}

			nodeId = doc.getTree().goUp(); // step out of Characterisitc Quantification
		}
	}
}

void DcmModelInternal::PopulateImagingObservationContainer(Annotation& annotation, DSRDocument& doc)
{
	ImagingObservationVector imgObservation = annotation.GetImagingObservationCollection();

	for(ImagingObservationVector::iterator iter = imgObservation.begin(); iter < imgObservation.end(); iter++)
	{
		this->PopulateImagingObservationEntry(*iter, doc);
	}
}

void DcmModelInternal::PopulateImagingObservationEntry(const ImagingObservation &imgObservation, DSRDocument &doc, DSRTypes::E_AddMode addMode)
{
	// Imaging Observation Type
	nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasObsContext, DSRTypes::VT_Code, addMode);
	ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz009", "Imaging Observation"));
	ofCondition = doc.getTree().getCurrentContentItem().setCodeValue(AIMCodes::CreateCodedEntryValue(
		imgObservation.GetCodeValue(), imgObservation.GetCodeMeaning(), imgObservation.GetCodingSchemeDesignator(), imgObservation.GetCodingSchemeVersion()));

	// Label
	nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasObsContext, DSRTypes::VT_Text, DSRTypes::AM_belowCurrent);
	ofString.assign(imgObservation.GetLabel().c_str());
	ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("C45561", "NCI", "A brief description given for purposes of identification"));
	ofCondition = doc.getTree().getCurrentContentItem().setStringValue(ofString);

	bool hasOptionalAttrs = true; // label takes care of nesting IO children now

	// Comment
	if(!imgObservation.GetComment().empty())
	{
		nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasObsContext, DSRTypes::VT_Text, hasOptionalAttrs ? DSRTypes::AM_afterCurrent : DSRTypes::AM_belowCurrent);
		ofString.assign(imgObservation.GetComment().c_str());
		ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("121106", "DCM", "Comment"));
		ofCondition = doc.getTree().getCurrentContentItem().setStringValue(ofString);
		hasOptionalAttrs = true;
	}

	// Annotator Confidence
	if (imgObservation.GetAnnotatorConfidence() != NULL)
	{
		nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasProperties, DSRTypes::VT_Num, hasOptionalAttrs ? DSRTypes::AM_afterCurrent : DSRTypes::AM_belowCurrent);
		ofString.assign(AIMUtil::DoubleToString(*imgObservation.GetAnnotatorConfidence()).c_str());
		ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz058", "Annotator Confidence"));
		ofCondition = doc.getTree().getCurrentContentItem().setNumericValue(DSRNumericMeasurementValue(ofString, DSRCodedEntryValue("%", "UCUM", "%")));
		hasOptionalAttrs = true;
	}

	// IsPresent
	if (imgObservation.GetIsPresent()) // it's true by default
	{
		nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasObsContext, DSRTypes::VT_Code, hasOptionalAttrs ? DSRTypes::AM_afterCurrent : DSRTypes::AM_belowCurrent);
		ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("G-A203", "SRT", "Present"));
		ofCondition = doc.getTree().getCurrentContentItem().setCodeValue(AIMCodes::GetBooleanCodeValue(imgObservation.GetIsPresent()));
		hasOptionalAttrs = true;
	}

	// Imaging Observation Characteristic
	ImagingObservationCharacteristicVector imgObservationChars = imgObservation.GetImagingObservationCharacteristicCollection();
	for(ImagingObservationCharacteristicVector::iterator charIter = imgObservationChars.begin(); charIter < imgObservationChars.end(); charIter++)
	{
		this->PopulateImagingObservationCharEntry(*charIter, doc, hasOptionalAttrs ? DSRTypes::AM_afterCurrent : DSRTypes::AM_belowCurrent);
		hasOptionalAttrs = true;
	}

	// Referenced Geometric Shape
	if (imgObservation.GetReferencedGeometricShape() != NULL)
	{
		ReferencedGeometricShapeVector refShapes;
		refShapes.push_back(*imgObservation.GetReferencedGeometricShape());
		this->PopulateReferencedGeometricShapes(refShapes, doc, !hasOptionalAttrs);
		hasOptionalAttrs = true;
	}

	if (hasOptionalAttrs)
		nodeId = doc.getTree().goUp();

	if (addMode == DSRTypes::AM_belowCurrent)
		nodeId = doc.getTree().goUp();
}

void DcmModelInternal::PopulateImagingObservationCharEntry(const ImagingObservationCharacteristic& imgObsCharacteristic, DSRDocument& doc, DSRTypes::E_AddMode addMode)
{
	nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasObsContext, DSRTypes::VT_Code, addMode);
	ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz010", "Imaging Observation Characteristic"));
	ofCondition = doc.getTree().getCurrentContentItem().setCodeValue(AIMCodes::CreateCodedEntryValue(
		imgObsCharacteristic.GetCodeValue(), imgObsCharacteristic.GetCodeMeaning(), imgObsCharacteristic.GetCodingSchemeDesignator(), imgObsCharacteristic.GetCodingSchemeVersion()));

	// Label
	nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasObsContext, DSRTypes::VT_Text, DSRTypes::AM_belowCurrent);
	ofString.assign(imgObsCharacteristic.GetLabel().c_str());
	ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("C45561", "NCI", "A brief description given for purposes of identification"));
	ofCondition = doc.getTree().getCurrentContentItem().setStringValue(ofString);

	bool hasOptionalAttrs = true; // Label takes care of nesting IOC children now

	// comment
	ofString.assign(imgObsCharacteristic.GetComment().c_str());
	if(!ofString.empty())
	{
		nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasObsContext, DSRTypes::VT_Text, hasOptionalAttrs ? DSRTypes::AM_afterCurrent : DSRTypes::AM_belowCurrent);
		ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("121106", "DCM", "Comment"));
		ofCondition = doc.getTree().getCurrentContentItem().setStringValue(ofString);
		hasOptionalAttrs = true;
	}

	// Annotator Confidence
	if (imgObsCharacteristic.GetAnnotatorConfidence() != NULL)
	{
		nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasProperties, DSRTypes::VT_Num, hasOptionalAttrs ? DSRTypes::AM_afterCurrent : DSRTypes::AM_belowCurrent);
		ofString.assign(AIMUtil::DoubleToString(*imgObsCharacteristic.GetAnnotatorConfidence()).c_str());
		ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz058", "Annotator Confidence"));
		ofCondition = doc.getTree().getCurrentContentItem().setNumericValue(DSRNumericMeasurementValue(ofString, DSRCodedEntryValue("%", "UCUM", "%")));
		hasOptionalAttrs = true;
	}

	// Characteristic Quantification
	if (imgObsCharacteristic.GetCharacteristicQuantificationCollection().size() > 0)
	{
		this->PopulateCharacteristicQuantificationEntries(imgObsCharacteristic.GetCharacteristicQuantificationCollection(), doc, !hasOptionalAttrs);
		hasOptionalAttrs = true; // NOTE: it's assumed that all Characteristic Quantifications are not NULL
	}

	if (hasOptionalAttrs)
		nodeId = doc.getTree().goUp(); // step out to the Imaging Observation Characteristic

	// NOTE: Parent element takes care of setting current node to itself
	//if (addMode == DSRTypes::AM_belowCurrent)
	//	nodeId = doc.getTree().goUp(); // step out to the parent element
}

void DcmModelInternal::PopulateCalculationEntries(Annotation& annotation, DSRDocument& doc)
{
	OFString codeMeaning, codeValue, codingScheme;

	CalculationVector calculations = annotation.GetCalculationCollection();

	//if (calculations.size() > 0)
	//{
		// Add Calculations container
		//nodeId = doc.getTree().addContentItem(DSRTypes::RT_contains, DSRTypes::VT_Container);
		//ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("CalculationCollection", AIM_CODING_SCHEME_DESIGNATOR, "Calculation Collection"));

		for(CalculationVector::const_iterator iter = calculations.begin(); iter < calculations.end(); iter++)
		{
			// Calculation container
			nodeId = doc.getTree().addContentItem(DSRTypes::RT_contains, DSRTypes::VT_Container);
			ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz011", "Calculation"));

			// Calculation type
			nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasConceptMod, DSRTypes::VT_Code, DSRTypes::AM_belowCurrent);
			ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("G-C036", "SRT", "Measurement Method"));
			ofCondition = doc.getTree().getCurrentContentItem().setCodeValue(AIMCodes::CreateCodedEntryValue(
				iter->GetCodeValue(), iter->GetCodeMeaning(), iter->GetCodingSchemeDesignator(), iter->GetCodingSchemeVersion()));

			// Calculation UID
			nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasAcqContext, DSRTypes::VT_UIDRef);
			ofString.assign(iter->GetUID().data());
			ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("112040", "DCM", "Tracking Unique Identifier"));
			ofCondition = doc.getTree().getCurrentContentItem().setStringValue(ofString);

			// Calculation Description
			if (!iter->GetDescription().empty())
			{
				nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasAcqContext, DSRTypes::VT_Text);
				ofString.assign(iter->GetDescription().c_str());
				ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("112034", "DCM", "Calculation Description"));
				ofCondition = doc.getTree().getCurrentContentItem().setStringValue(ofString);
			}

			// Calculation MathML
			if (!iter->GetMathML().empty())
			{
				nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasAcqContext, DSRTypes::VT_Text);
				ofString.assign(iter->GetMathML().c_str());
				ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz013", "Calculation MathML"));
				ofCondition = doc.getTree().getCurrentContentItem().setStringValue(ofString);
			}

			// Algorithm Name
			if (!iter->GetAlgorithmName().empty())
			{
				nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasObsContext, DSRTypes::VT_Text);
				ofString.assign(iter->GetAlgorithmName().c_str());
				ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("111001", "DCM", "Algorithm Name"));
				ofCondition = doc.getTree().getCurrentContentItem().setStringValue(ofString);
			}

			// Algorithm Version
			if (!iter->GetAlgorithmVersion().empty())
			{
				nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasObsContext, DSRTypes::VT_Text);
				ofString.assign(iter->GetAlgorithmVersion().c_str());
				ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("111003", "DCM", "Algorithm Version"));
				ofCondition = doc.getTree().getCurrentContentItem().setStringValue(ofString);
			}

			// Go up to the Calculation container level
//			nodeId = doc.getTree().goUp();

			// Referenced Calculations
			this->PopulateReferencedCalculation(iter->GetReferencedCalculationCollection(), doc);

			// Calculation Results
			this->PopulateCalculationResultEntries(iter->GetCalculationResultCollection(), doc);

			// Referenced Geometric Shapes
			this->PopulateReferencedGeometricShapes(iter->GetReferencedGeometricShapeCollection(), doc, false);

			// Go up to parent container
			nodeId = doc.getTree().goUp();
		}
	//}
}

void DcmModelInternal::PopulateReferencedCalculation(const ReferencedCalcVector& referencedCalc, DSRDocument& doc)
{
	if (referencedCalc.size() > 0)
	{
		// Add Referenced Calculation container
		nodeId = doc.getTree().addContentItem(DSRTypes::RT_contains, DSRTypes::VT_Container);
		ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz014", "Referenced Calculation"));

		for(ReferencedCalcVector::const_iterator iter = referencedCalc.begin(); iter < referencedCalc.end(); iter++)
		{
			// Referenced Calculation UID
			if (iter == referencedCalc.begin())
				nodeId = doc.getTree().addContentItem(DSRTypes::RT_contains, DSRTypes::VT_UIDRef, DSRTypes::AM_belowCurrent);
			else
				nodeId = doc.getTree().addContentItem(DSRTypes::RT_contains, DSRTypes::VT_UIDRef);
			ofString.assign(iter->GetUniqueIdentifier().c_str());
			ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("112040", "DCM", "Tracking Unique Identifier"));
			ofCondition = doc.getTree().getCurrentContentItem().setStringValue(ofString);
		}

		// Go Back to the initial level
		nodeId = doc.getTree().goUp();
	}
}

void DcmModelInternal::PopulateReferencedGeometricShapes(const ReferencedGeometricShapeVector& refGeoShapes, DSRDocument& doc, bool nestFirst)
{
	if (refGeoShapes.size() > 0)
	{
		_dsrCode = AIMCodes::CreateAimCodedEntryValue("zzz055", "Referenced Geometric Shape");
		for(ReferencedGeometricShapeVector::const_iterator iter = refGeoShapes.begin(); iter < refGeoShapes.end(); iter++)
		{
			// Referenced Geometric Shape ID
			if (nestFirst && iter == refGeoShapes.begin())
				nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasObsContext, DSRTypes::VT_Text, DSRTypes::AM_belowCurrent);
			else
				nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasObsContext, DSRTypes::VT_Text);
			ofString.assign(AIMUtil::IntToString(iter->GetReferencedShapeIdentifier()).c_str());
			ofCondition = doc.getTree().getCurrentContentItem().setConceptName(_dsrCode);
			ofCondition = doc.getTree().getCurrentContentItem().setStringValue(ofString);
		}

		// Go back up to the initial level
		if (nestFirst)
			nodeId = doc.getTree().goUp();
	}
}

void DcmModelInternal::PopulateCalculationResultEntries(const CalcResultVector& calcResult, DSRDocument& doc)
{
	for(CalcResultVector::const_iterator iter = calcResult.begin(); iter < calcResult.end(); iter++)
	{
		// scalar calculation result is a special case
		if (iter->GetType() == Scalar)
		{
			assert(iter->GetCalculationDataCollection().size() == 1); // scalar has one value
			assert(iter->GetNumberOfDimensions() == 1);

			// Calculation result
			nodeId = doc.getTree().addContentItem(DSRTypes::RT_contains, DSRTypes::VT_Num);
			ofString.assign(AIMUtil::DoubleToString(iter->GetCalculationDataCollection()[0].GetValue()).c_str());
			ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz015", "Calculation Result"));
			ofCondition = doc.getTree().getCurrentContentItem().setNumericValue(DSRNumericMeasurementValue(ofString, AIMCodes::GetUcumCodeValue(iter->GetUnitOfMeasure())));

			// Label
			nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasAcqContext, DSRTypes::VT_Text, DSRTypes::AM_belowCurrent);
			ofString.assign(iter->GetDimensionCollection()[0].GetLabel().c_str());
			ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz018", "Dimension Label"));
			ofCondition = doc.getTree().getCurrentContentItem().setStringValue(ofString);

			nodeId = doc.getTree().goUp();

			continue;
		}

		assert(iter->GetType() != Scalar); // scalar is a special case above

		// Calculation Result container
		nodeId = doc.getTree().addContentItem(DSRTypes::RT_contains, DSRTypes::VT_Container);
		ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz015", "Calculation Result"));

		// Calculation Result Type
		nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasObsContext, DSRTypes::VT_Code, DSRTypes::AM_belowCurrent);
		DSRCodedEntryValue dsrValue = AIMCodes::GetCalculationResultTypeValue(iter->GetType());
		ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz016", "Calculation Result Type"));
		ofCondition = doc.getTree().getCurrentContentItem().setCodeValue(dsrValue);

		// Number Of Dimensions
		nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasObsContext, DSRTypes::VT_Num);
		ofString.assign(AIMUtil::IntToString(iter->GetNumberOfDimensions()).c_str());
		ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz017", "Number of Dimensions"));
		ofCondition = doc.getTree().getCurrentContentItem().setNumericValue(DSRNumericMeasurementValue(ofString, DSRCodedEntryValue("1", "UCUM", "No units")));

		//// Calculation Dimensions container
		//nodeId = doc.getTree().addContentItem(DSRTypes::RT_contains, DSRTypes::VT_Container);
		//ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz038", "Calculation Dimensions"));

		DimensionVector dimensions = iter->GetDimensionCollection();
		for(DimensionVector::iterator dimIter = dimensions.begin(); dimIter < dimensions.end(); dimIter++)
		{
			// Calculation Dimension container
			nodeId = doc.getTree().addContentItem(DSRTypes::RT_contains, DSRTypes::VT_Container/*, DSRTypes::AM_belowCurrent*/);
			ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz039", "Calculation Dimension"));

			// Dimension Index
			nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasAcqContext, DSRTypes::VT_Num, DSRTypes::AM_belowCurrent);
			ofString.assign(AIMUtil::IntToString(dimIter->GetIndex()).c_str());
			ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz040", "Dimension Index"));
			ofCondition = doc.getTree().getCurrentContentItem().setNumericValue(DSRNumericMeasurementValue(ofString, DSRCodedEntryValue("1", "UCUM", "No units")));

			// Dimension Size
			nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasAcqContext, DSRTypes::VT_Num);
			ofString.assign(AIMUtil::IntToString(dimIter->GetSize()).c_str());
			ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz041", "Dimension Size"));
			ofCondition = doc.getTree().getCurrentContentItem().setNumericValue(DSRNumericMeasurementValue(ofString, DSRCodedEntryValue("1", "UCUM", "No units")));

			// Dimension Label
			nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasAcqContext, DSRTypes::VT_Text);
			ofString.assign(dimIter->GetLabel().c_str());
			ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz018", "Dimension Label"));
			ofCondition = doc.getTree().getCurrentContentItem().setStringValue(ofString);

			//nodeId = doc.getTree().goUp(); // step out of the dimension index container
			nodeId = doc.getTree().goUp(); // step out of the dimension container
		}

		CalculationDataVector datum = iter->GetCalculationDataCollection();
		if (datum.size() > 0)
		{
			// Calculation Result Datum container
			nodeId = doc.getTree().addContentItem(DSRTypes::RT_contains, DSRTypes::VT_Container);
			ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz019", "Calculation Result Datum"));

			for(CalculationDataVector::iterator dataIter = datum.begin(); dataIter < datum.end(); dataIter++)
			{
				// Calculation Result Data
				nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasObsContext, DSRTypes::VT_Num, DSRTypes::AM_belowCurrent);
				ofString.assign(AIMUtil::DoubleToString(dataIter->GetValue()).c_str());
				DSRCodedEntryValue unitCode = AIMCodes::GetUcumCodeValue(iter->GetUnitOfMeasure());
				ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz020", "Calculation Result Data"));
				ofCondition = doc.getTree().getCurrentContentItem().setNumericValue(DSRNumericMeasurementValue(ofString, unitCode));

				// Coordinates
				CoordinateVector coordinates = dataIter->GetCoordinateCollection();
				for(CoordinateVector::iterator coordIter = coordinates.begin(); coordIter < coordinates.end(); coordIter++)
				{
					// Calculation Result Coordinate
					nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasAcqContext, DSRTypes::VT_Container, DSRTypes::AM_belowCurrent);
					ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz042", "Calculation Result Coordinate"));

					// Coordinate Dimension Index
					nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasObsContext, DSRTypes::VT_Num, DSRTypes::AM_belowCurrent);
					ofString.assign(AIMUtil::IntToString(coordIter->GetDimensionIndex()).c_str());
					ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz040", "Dimension Index"));
					ofCondition = doc.getTree().getCurrentContentItem().setNumericValue(DSRNumericMeasurementValue(ofString, DSRCodedEntryValue("1", "UCUM", "No units")));

					// Coordinate Position
					nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasObsContext, DSRTypes::VT_Num);
					ofString.assign(AIMUtil::IntToString(coordIter->GetPosition()).c_str());
					ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz043", "Coordinate Position"));
					ofCondition = doc.getTree().getCurrentContentItem().setNumericValue(DSRNumericMeasurementValue(ofString, DSRCodedEntryValue("1", "UCUM", "No units")));

					nodeId = doc.getTree().goUp(); // step out to the Coordinate container
					nodeId = doc.getTree().goUp(); // step out of the Coordinate container
				}
				nodeId = doc.getTree().goUp(); // step out of the Calculation Result Data container
			}
		}
		nodeId = doc.getTree().goUp(); // step out of the Type container
	}
}

void DcmModelInternal::PopulateSegmentationContainer(ImageAnnotation& annotation, DSRDocument& doc, bool nestFirst)
{
	SegmentationVector segmentations = annotation.GetSegmentationCollection();

	if (segmentations.size() > 0)
	{
		// Segmentation container
//		nodeId = doc.getTree().addContentItem(DSRTypes::RT_contains, DSRTypes::VT_Container, DSRTypes::AM_belowCurrent); // nest here because this is the first entry in the parent container
	//	nodeId = doc.getTree().addContentItem(DSRTypes::RT_contains, DSRTypes::VT_Container);
	//	ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz006", "Segmentation"));

		for(SegmentationVector::iterator iter = segmentations.begin(); iter < segmentations.end(); ++iter)
		{
			// Segmentation item
			if (nestFirst && iter == segmentations.begin())
				nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasAcqContext, DSRTypes::VT_Text, DSRTypes::AM_belowCurrent);
			else
				nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasAcqContext, DSRTypes::VT_Text);
			ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz006", "Segmentation"));
			ofCondition = doc.getTree().getCurrentContentItem().setStringValue("Segmentation");

			// Segmentation Storage Reference
			assert(std::string("1.2.840.10008.5.1.4.1.1.66.4").compare(iter->GetSopClassUID()) == 0);
			//DSRImageReferenceValue dsrImageRefObj("1.2.840.10008.5.1.4.1.1.66.4", iter->GetSopInstanceUID().c_str());
			DSRImageReferenceValue dsrImage(iter->GetSopClassUID().c_str(), iter->GetSopInstanceUID().c_str());
			nodeId = doc.getTree().addContentItem(DSRTypes::RT_inferredFrom, DSRTypes::VT_Image, DSRTypes::AM_belowCurrent);
			ofCondition = doc.getTree().getCurrentContentItem().setImageReference(dsrImage);

			// Segmented Image Reference
			const Image* pImage = this->FindDICOMImage(annotation, iter->GetReferencedSopInstanceUID());
			if (pImage == NULL)
			{
				std::string exMsg = "Segmented image referenced by Segmentation SOP is not part of Image Reference collection. [referencedSopInstanceUID=" + iter->GetReferencedSopInstanceUID() + "]";
				std::runtime_error(exMsg.c_str());
			}
			//assert(pImage != NULL); // Image must be referenced in the Annotation
			DSRImageReferenceValue dsrImageRefObj(pImage->GetSopClassUID().c_str(), pImage->GetSopInstanceUID().c_str());
			nodeId = doc.getTree().addContentItem(DSRTypes::RT_inferredFrom, DSRTypes::VT_Image);
			ofCondition = doc.getTree().getCurrentContentItem().setImageReference(dsrImageRefObj);

			// Segmentation Number
			nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasProperties, DSRTypes::VT_Num);
			ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz060", "Segmentation Number"));
			ofString.assign(AIMUtil::IntToString(iter->GetSegmentNumber()).c_str());
			ofCondition = doc.getTree().getCurrentContentItem().setNumericValue(DSRNumericMeasurementValue(ofString, DSRCodedEntryValue("1", "UCUM", "No units")));

			if (iter->GetImagingObservation() != NULL)
				this->PopulateImagingObservationEntry(*(iter->GetImagingObservation()), doc);

			nodeId = doc.getTree().goUp(); // step out of the item
		}

		//nodeId = doc.getTree().goUp(); // step out of the Segmentation container -
	}
}

void DcmModelInternal::PopulateInferenceContainer(Annotation& annotation, DSRDocument& doc, bool nestFirst)
{
	InferenceVector inferences = annotation.GetInferenceCollection();

	if (inferences.size() > 0)
	{
		// Inference container
//		nodeId = doc.getTree().addContentItem(DSRTypes::RT_contains, DSRTypes::VT_Container, DSRTypes::AM_belowCurrent); // nest here because this is the first entry in the parent container
	//	nodeId = doc.getTree().addContentItem(DSRTypes::RT_contains, DSRTypes::VT_Container);
	//	ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz054", "Inference"));

		for(InferenceVector::iterator iter = inferences.begin(); iter < inferences.end(); ++iter)
		{
			// Inference item
			if (nestFirst && iter == inferences.begin())
				nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasAcqContext, DSRTypes::VT_Code, DSRTypes::AM_belowCurrent);
			else
				nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasAcqContext, DSRTypes::VT_Code);
			ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz054", "Inference"));
			ofCondition = doc.getTree().getCurrentContentItem().setCodeValue(AIMCodes::CreateCodedEntryValue(iter->GetCodeValue(), iter->GetCodeMeaning(), iter->GetCodingSchemeDesignator(), iter->GetCodingSchemeVersion()));

			bool hasConfidence = false;

			// Annotator Confidence
			if (iter->GetAnnotatorConfidence())
			{
				nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasObsContext, DSRTypes::VT_Num, DSRTypes::AM_belowCurrent);
				ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz058", "Annotator Confidence"));
				ofString.assign(AIMUtil::DoubleToString(*(iter->GetAnnotatorConfidence())).c_str());
				ofCondition = doc.getTree().getCurrentContentItem().setNumericValue(DSRNumericMeasurementValue(ofString, DSRCodedEntryValue("%", "UCUM", "%")));

				hasConfidence = true;
			}

			nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasProperties, DSRTypes::VT_Code, hasConfidence ? DSRTypes::AM_afterCurrent : DSRTypes::AM_belowCurrent);
			ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz059", "Image Evidence"));
			ofCondition = doc.getTree().getCurrentContentItem().setCodeValue(DSRCodedEntryValue(AIMCodes::GetBooleanCodeValue(iter->GetImageEvidence())));

//			nodeId = doc.getTree().goUp(); // step out of the item
			nodeId = doc.getTree().goUp(); // step out of the Inference container
		}
	}
}

void DcmModelInternal::PopulateGeometricShapeContainer(ImageAnnotation &annotation, DSRDocument &doc, bool nestFirst)
{
	GeoShapePtrVector geoShapes = annotation.GetGeometricShapeCollection();

	if (geoShapes.size() > 0)
	{
		//DSRCodedEntryValue conceptName = AIMCodes::CreateAimCodedEntryValue("zzz022", "Geometric Shape");

		//// Geometric Shapes container
		//nodeId = doc.getTree().addContentItem(DSRTypes::RT_contains, DSRTypes::VT_Container);
		//ofCondition = doc.getTree().getCurrentContentItem().setConceptName(conceptName);

		for (GeoShapePtrVector::iterator iter = geoShapes.begin(); iter < geoShapes.end(); iter++)
		{
			assert(*iter);
			bool isNested = nestFirst && iter == geoShapes.begin();
			this->PopulateGeometricShapeEntry(annotation, doc, **iter, DSRTypes::RT_contains, isNested);
		}
	}
}

void DcmModelInternal::PopulateGeometricShapeEntry(aim_lib::ImageAnnotation &annotation, DSRDocument &doc, const GeometricShape &geoShape, DSRTypes::E_RelationshipType relWithParent, bool isNested)
{
	// Geometric Shape item
	_dsrCode = AIMCodes::CreateAimCodedEntryValue("zzz022", "Geometric Shape");
	nodeId = doc.getTree().addContentItem(relWithParent, DSRTypes::VT_Text, isNested ? DSRTypes::AM_belowCurrent : DSRTypes::AM_afterCurrent);
	ofCondition = doc.getTree().getCurrentContentItem().setConceptName(_dsrCode);
	// NOTE: This is not in the model. If we ever need to add shape name, this is the place to do that.
	ofCondition = doc.getTree().getCurrentContentItem().setStringValue("Geometric Shape");

	// TODO - Modify code to deal with 3D coordinates

	//if (pGeoShape->Is2DShape())
	//{
		//ofCondition = doc.getTree().getCurrentContentItem().setCodeValue(DSRCodedEntryValue("zzz023", AIM_CODING_SCHEME_DESIGNATOR, "2D Geometric Shape"));

		// SCOORD
		DSRSpatialCoordinatesValue dsrSpatialCoord;
		switch(geoShape.GetShapeType())
		{
		case GeometricShape::SHT_Point:
			dsrSpatialCoord = DSRSpatialCoordinatesValue(DSRTypes::GT_Point);
			break;
		case GeometricShape::SHT_Circle:
			dsrSpatialCoord = DSRSpatialCoordinatesValue(DSRTypes::GT_Circle);
			break;
		case GeometricShape::SHT_Multipoint:
			dsrSpatialCoord = DSRSpatialCoordinatesValue(DSRTypes::GT_Multipoint);
			break;
		case GeometricShape::SHT_Polyline:
			dsrSpatialCoord = DSRSpatialCoordinatesValue(DSRTypes::GT_Polyline);
			break;
		case GeometricShape::SHT_Ellipse:
			dsrSpatialCoord = DSRSpatialCoordinatesValue(DSRTypes::GT_Ellipse);
			break;
		case GeometricShape::SHT_Unknown:
		default:
			assert(false); // unknown shape type!
		}

		nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasProperties, DSRTypes::VT_SCoord, DSRTypes::AM_belowCurrent);
		ofCondition = doc.getTree().getCurrentContentItem().setConceptName(_dsrCode);

		const SpatialCoordPtrVector& spatialCoords = geoShape.GetSpatialCoordinateCollection();
		std::string imageReferenceUID;
		long referencedFrameNumber = 1; // 1 - default
		assert(spatialCoords.size() > 0); // at least one coordinate is required
		for(SpatialCoordPtrVector::const_iterator iterCoords=spatialCoords.begin(); iterCoords < spatialCoords.end(); iterCoords++)
		{
			switch((*iterCoords)->GetCoordinateType())
			{
			case SpatialCoordinate::T_2D_SPCOORD:
				{
					TwoDimensionSpatialCoordinate* p2DSpatialCoord = dynamic_cast<TwoDimensionSpatialCoordinate*>(*iterCoords);
					assert(p2DSpatialCoord != NULL);
					dsrSpatialCoord.getGraphicDataList().addItem((Float32)p2DSpatialCoord->GetX(), (Float32)p2DSpatialCoord->GetY());

					if (imageReferenceUID.empty())
					{
						imageReferenceUID.assign(p2DSpatialCoord->GetImageReferenceUID());
						referencedFrameNumber = p2DSpatialCoord->GetReferencedFrameNumber();
					}
				}
				break;
			case SpatialCoordinate::T_3D_SPCOORD:
				{
					ThreeDimensionSpatialCoordinate* p3DSpatialCoord = dynamic_cast<ThreeDimensionSpatialCoordinate*>(*iterCoords);
					assert(p3DSpatialCoord != NULL);

					// NOTE: All code in this method only works with 2D shapes/coordinates only

					//if (imageReferenceUID.empty())
					//	imageReferenceUID.assign(p3DSpatialCoord->GetFrameOfReferenceUID());

					//dsrSpatialCoord.getGraphicDataList().addItem(p3DSpatialCoord->GetX(), p3DSpatialCoord->GetY(), (float)p3DSpatialCoord->GetZ());

					assert(false);
					std::runtime_error(_T("Writing 3D Spatial Coordinates is not implemented at this time. Waiting for DICOM to finalize 3D SCOORDs"));
				}
				break;
			}
		}
		ofCondition = doc.getTree().getCurrentContentItem().setSpatialCoordinates(dsrSpatialCoord);

		// Image Reference - 2D only
		const Image* pImage = FindDICOMImage(annotation, imageReferenceUID);
		assert(pImage != NULL); // We must have the image
		if (pImage == NULL)
		{
			std::string exMsg(_T("Image referenced by Geometric Shape is not part of Image Reference collection. [SOPClassUID=") + imageReferenceUID + _T("]"));
			std::runtime_error(exMsg.c_str());
		}
		DSRImageReferenceValue dsrImage(pImage->GetSopClassUID().c_str(), pImage->GetSopInstanceUID().c_str());
		if (referencedFrameNumber != 1)
			dsrImage.getFrameList().addOnlyNewItem(referencedFrameNumber);
		nodeId = doc.getTree().addContentItem(DSRTypes::RT_selectedFrom, DSRTypes::VT_Image, DSRTypes::AM_belowCurrent);
		ofCondition = doc.getTree().getCurrentContentItem().setImageReference(dsrImage);

		nodeId = doc.getTree().goUp(); // step out of the Image Reference container

//		nodeId = doc.getTree().goUp(); // step out of the Scoord container

	//}
	//else
	//{
	//	assert(pGeoShape->Is3DShape());

	//	ofCondition = doc.getTree().getCurrentContentItem().setCodeValue(DSRCodedEntryValue("zzz024", AIM_CODING_SCHEME_DESIGNATOR, "3D Geometric Shape"));
	//}


	// Include Flag
	nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasProperties, DSRTypes::VT_Code/*, DSRTypes::AM_belowCurrent*/);
	ofCondition = doc.getTree().getCurrentContentItem().setConceptName(AIMCodes::CreateAimCodedEntryValue("zzz021", "Include Flag"));
	ofCondition = doc.getTree().getCurrentContentItem().setCodeValue(AIMCodes::GetBooleanCodeValue(geoShape.GetIncludeFlag()));

	// Shape ID
	nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasProperties, DSRTypes::VT_Text);
	ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("112039", "DCM", "Tracking Identifier"));
	ofString.assign(AIMUtil::IntToString(geoShape.GetShapeIdentifier()).c_str());
	ofCondition = doc.getTree().getCurrentContentItem().setStringValue(ofString);

//	nodeId = doc.getTree().goUp(); // step out to the Geometric Shape code
	nodeId = doc.getTree().goUp(); // step out of the Geometric Shape code

}

const Image* DcmModelInternal::FindDICOMImage(const ImageAnnotation &annotation, const std::string &sopInstanceUID)
{
	for(ImageReferencePtrVector::const_iterator iter = annotation.GetImageReferenceCollection().begin(); iter < annotation.GetImageReferenceCollection().end(); iter++)
	{
		if ((*iter)->GetImageReferenceType() == ImageReference::T_DICOM_IMAGE_REF)
		{
			const DICOMImageReference* pDicomImageRef = (const DICOMImageReference*)(*iter);

			const Image* pImage = pDicomImageRef->GetStudy().GetImage(sopInstanceUID);
			if (pImage != NULL)
				return pImage;
		}
	}

	return NULL;
}

//void DcmModelInternal::PopulateImageReferenceItem(ImageAnnotation& annotation, DSRDocument& doc, const std::string& imageReferenceUID, DSRTypes::E_AddMode addMode)
//{
//	assert(imageReferenceUID.length() > 0);
//	if (imageReferenceUID.length() < 1)
//		return;
//
//	ImageReferencePtrVector imgRefs = annotation.GetImageReferenceCollection();
//	ImageReference* pImgRef;
//	bool isFound = false;
//
//	for(ImageReferencePtrVector::iterator iter = imgRefs.begin(); !isFound && iter < imgRefs.end(); iter++)
//	{
//		pImgRef = *iter;
//		assert(pImgRef != NULL);
//		if (pImgRef != NULL)
//		{
//			const DICOMImageReference* pDicomImgRef = dynamic_cast<const DICOMImageReference*>(pImgRef);
//			const WebImageReference* pWebImgRef = dynamic_cast<const WebImageReference*>(pImgRef);
//			if (pDicomImgRef != NULL)
//			{
//				for(StudyVector::const_iterator studyIter = pDicomImgRef->GetStudyCollection().begin(); !isFound && studyIter < pDicomImgRef->GetStudyCollection().end(); studyIter++)
//				{
//					for(SeriesVector::const_iterator seriesIter = studyIter->GetSeriesCollection().begin(); !isFound && seriesIter < studyIter->GetSeriesCollection().end(); seriesIter++)
//					{
//						for(ImageVector::const_iterator imgIter = seriesIter->GetImageCollection().begin(); !isFound && imgIter < seriesIter->GetImageCollection().end(); imgIter++)
//						{
//							if (imgIter->GetSOPInstanceUID() != imageReferenceUID)
//								continue;
//
//							// Image SOP Class UID and SOP Instance UID
//							nodeId = doc.getTree().addContentItem(DSRTypes::RT_selectedFrom, DSRTypes::VT_Image, addMode);
//							ofCondition = doc.getTree().getCurrentContentItem().setImageReference(DSRImageReferenceValue(imgIter->GetSOPClassUID().data(), imgIter->GetSOPInstanceUID().data()));
//
//							// Study Instance UID
//							nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasAcqContext, DSRTypes::VT_UIDRef, DSRTypes::AM_belowCurrent);
//							ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("110180", "DCM", "Study Instance UID"));
//							ofCondition = doc.getTree().getCurrentContentItem().setStringValue(studyIter->GetStudyInstanceUID().data());
//
//							// Series Instance UID
//							nodeId = doc.getTree().addContentItem(DSRTypes::RT_hasAcqContext, DSRTypes::VT_UIDRef);
//							ofCondition = doc.getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("112002", "DCM", "Series Instance UID"));
//							ofCondition = doc.getTree().getCurrentContentItem().setStringValue(seriesIter->GetSeriesInstanceUID().data());
//
//							// Step out to the Image container
//							nodeId = doc.getTree().goUp();
//
//							if (addMode == DSRTypes::AM_belowCurrent)
//								nodeId = doc.getTree().goUp(); // step out of the Image container
//
//							isFound = true;
//						}
//					}
//				}
//			}
//			else if (pWebImgRef != NULL)
//			{
//				if (pWebImgRef->GetURI() != imageReferenceUID)
//					continue;
//				assert(false); // not implemented - what's the SR format for this image type?
//
//				isFound = true;
//			}
//		}
//	}
//
//	assert(isFound); // Referenced image is not found in the Image Reference Collection! It got to be there!
//}
