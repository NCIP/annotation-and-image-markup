/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"
#include "DcmModelInternal.h"

#include "../AIMUtil.h"
#include "../AIMCodes.h"

#include <vector>
#include <memory>
#include <algorithm>

#include "../memdebug.h"

using namespace aim_lib;

#define DSR_CDE(Code, Schema, CodeValue) DSRCodedEntryValue((Code), (Schema), (CodeValue))
#define DSR_AIM_CDE(Code, CodeValue) AIMCodes::CreateAimCodedEntryValue((Code), (CodeValue))

// macros for: doc.getTree().gotoNamedNode(DSRCodedEntryValue(...))
#define GO_TO_NAMED_NODE1(dsr_cde) _pDoc->getTree().gotoNamedNode(dsr_cde)
#define GO_TO_NAMED_NODE2(Code, CodeValue) _pDoc->getTree().gotoNamedNode(DSR_AIM_CDE((Code), (CodeValue)))
#define GO_TO_NAMED_NODE3(Code, CodingSchemeDesignator, CodeValue) _pDoc->getTree().gotoNamedNode(DSR_CDE((Code), (CodingSchemeDesignator), (CodeValue)))
// macros for: doc.getTree().gotoNextNamedNode(DSRCodedEntryValue(...))
#define GO_TO_NEXT_NAMED_NODE1(dsr_cde) _pDoc->getTree().gotoNextNamedNode(dsr_cde)
#define GO_TO_NEXT_NAMED_NODE2(Code, CodeValue) _pDoc->getTree().gotoNextNamedNode(DSR_AIM_CDE((Code), (CodeValue)))
#define GO_TO_NEXT_NAMED_NODE3(Code, CodingSchemeDesignator, CodeValue) _pDoc->getTree().gotoNextNamedNode(DSR_CDE((Code), (CodingSchemeDesignator), (CodeValue)))

OFCondition DcmModelInternal::ReadDocFromFile(Annotation** ppAnnotation, const std::string& fileName)
{
	assert(ppAnnotation != NULL);
	if (ppAnnotation == NULL)
	{
		printDebug(std::string(__FILE__).append(": Output Annotation parameter cannot be NULL").data());
		return EC_IllegalParameter;
	}

	*ppAnnotation = NULL;
	AnnotationPtrVector annotations;

	if (this->ReadDocFromFile(annotations, fileName) > 0)
	{
		assert(annotations.size() == 1);
		*ppAnnotation = annotations[0];
		annotations[0] = NULL;
		annotations.clear();

		return makeOFCondition(OFM_aimlib, 100, OF_ok, "");
	}

	std::string err = std::string("Failed to load SR from file <").append(fileName).append(">");
	printDebug(std::string(__FILE__).append(": ").append(err).data());
	return makeOFCondition(OFM_aimlib, 100, OF_error, err.data());
}

int DcmModelInternal::ReadDocFromFile(AnnotationPtrVector& annotations, const std::string& fileName)
{
	while (annotations.size() > 0)
	{
		delete annotations[annotations.size() - 1];
		annotations.pop_back();
	}

	assert(fileName.length() > 0);
	if (fileName.length() < 1)
	{
		printDebug(std::string(__FILE__).append(": DICOM SR input file name cannot be empty").data());
		return 0;
	}

	DcmFileFormat fileformat;
	OFCondition openCondition(SR_EC_InvalidValue);
	openCondition = fileformat.loadFile(fileName.c_str());
	if(openCondition.good())
	{
		_pDoc = new DSRDocument();
		openCondition = _pDoc->read(*fileformat.getDataset());
		if (openCondition.good())
		{
#ifdef _DEBUG
			// Send log messages to the output window
			// DCMTK 3.6.0+ - use filelog.cfg to control output
//			_pDoc->setLogStream(&ofConsole);
#endif

			openCondition = LoadAnnotationsFromDSRDocument(annotations);
		}
		else
		{
			std::string err = std::string("Failed to load SR from file <").append(fileName).append(">");
			printDebug(std::string(__FILE__).append(": ").append(err).data());
			openCondition = makeOFCondition(OFM_aimlib, 100, OF_error, err.data());
		}
	}

	return (int)annotations.size();
}


OFCondition DcmModelInternal::LoadAnnotationsFromDSRDocument(AnnotationPtrVector& annotations)
{
	while (annotations.size() > 0)
	{
		delete annotations[annotations.size() - 1];
		annotations.pop_back();
	}

	// make sure that the doc is valid and SR container is present
	assert(_pDoc->isValid());
	if (!_pDoc->isValid())
	{
		return makeOFCondition(OFM_aimlib, 101, OF_error, "Provided SR document is not valid");
	}
	_dsrCode = DSR_AIM_CDE("zzz001", "AIM SR Report");
	assert(GO_TO_NAMED_NODE1(_dsrCode) > 0);
	if (GO_TO_NAMED_NODE1(_dsrCode) < 1)
	{
		return makeOFCondition(OFM_aimlib, 102, OF_error, "No SR container is found in the provided document");
	}

	// TODO VK
	// 1. Figure out annotation type
	//size_t searchNode;
	//int cnt = 0;
	//searchNode = doc.getTree().gotoRoot();
	//while(searchNode = doc.getTree().iterate(true))
	//{
	//	printDebug(string("Reading node").append(AIMUtil::IntToString(++cnt)).c_str());
	//}
	//searchNode =  doc.getTree().gotoNamedNode(DSR_AIM_CDE("zzz030", "Image Annotation"));


	// 2. read SR headers


	// 3. read SR container
	_dsrCode = DSR_AIM_CDE("zzz002", "AIM Annotation");
	size_t annotationsContainerId = GO_TO_NAMED_NODE1(_dsrCode);
	if (annotationsContainerId > 0/* && _pDoc->getTree().goDown() > 0*/)
	{
		// NOTE: Reading annotation is based on the fact that SR Tree
		// has unique _ordered_ nodeId for each node in the tree.
		// This allows us to assume that all nodes which satisfy
		// (annotationNodeId < nodeId < nextAnnotationNodeId)
		// belong to the current annotation.

		// Store node IDs of all annotations in the document
		std::vector<size_t> annotationIds;
		do
		{
			assert(this->GetConceptName().isValid() && this->GetConceptName().getCodeValue() == "zzz002");
			annotationIds.push_back(_pDoc->getTree().getNodeID());
		}
		while (_pDoc->getTree().gotoNextNamedNode(_dsrCode, false) > 0);

		for(std::vector<size_t>::size_type i = 0; i < annotationIds.size(); i++)
		{
			size_t nextAnnotationId = i+1 < annotationIds.size() ? annotationIds[i+1] : 0; // 0 means that this is the last annotation
			Annotation::AnnotationKind atKind = FindAnnotationKind(annotationIds[i], nextAnnotationId);
			Annotation* pAnnotation = NULL;

			switch(atKind)
			{
			case Annotation::AK_ImageAnnotation:
				{
					pAnnotation = ReadImageAnnotation(annotationIds[i], nextAnnotationId);
					break;
				}
			case Annotation::AK_AnnotationOfAnnotation:
				{
					pAnnotation = ReadAnnotationOfAnnotation(annotationIds[i]);
					break;
				}
			case Annotation::AK_Unknown:
				assert(false); // could not find annotation type information from the document
				break;
			}

			if(pAnnotation != NULL)
				annotations.push_back(pAnnotation);
		}
	}
	else
	{
		return makeOFCondition(OFM_aimlib, 103, OF_error, "No Annotations are present in the document");
	}

	return makeOFCondition(OFM_aimlib, 1, OF_ok, "");
}

// Searches for annotation kind information for the given Annotation
// Search is based on the fact that the information we're after should have nodeId such as: annotationId < nodeId < nextAnnotationId
// When nextAnnotationId is 0, any nodeId after the annotationId is valid (i.e. search till the end of the document)
Annotation::AnnotationKind DcmModelInternal::FindAnnotationKind(size_t annotationNodeId, size_t nextAnnotationNodeId)
{
	assert(annotationNodeId < nextAnnotationNodeId || nextAnnotationNodeId == 0);

	size_t curNodeId = _pDoc->getTree().gotoNode(annotationNodeId);
	curNodeId = _pDoc->getTree().gotoNextNamedNode(DSR_AIM_CDE("zzz030", "Image Annotation"));
	if (curNodeId > 0 && (nextAnnotationNodeId == 0 || curNodeId < nextAnnotationNodeId))
		return Annotation::AK_ImageAnnotation;

	curNodeId = _pDoc->getTree().gotoNode(annotationNodeId);
	curNodeId = _pDoc->getTree().gotoNextNamedNode(DSR_AIM_CDE("zzz031", "Annotation of Annotation"));
	if (curNodeId > 0 && (nextAnnotationNodeId == 0 || curNodeId < nextAnnotationNodeId))
		return Annotation::AK_AnnotationOfAnnotation;

	return Annotation::AK_Unknown;
}

ImageAnnotation* DcmModelInternal::ReadImageAnnotation(size_t imgAnnotationNodeId, size_t nextAnnotationNodeId)
{
	ImageAnnotation* pImgAnnotation = new ImageAnnotation();

	// AIM Version
	nodeId = GO_TO_NAMED_NODE2("zzz003", "AIM Version");
	_stdString = GetStringValue();
	pImgAnnotation->SetAimVersion(_stdString);

	// Image References
	ImageReferencePtrVector imageReferences = ReadImageLibrary(imgAnnotationNodeId, nextAnnotationNodeId);

	// TODO:
	// Delay setting Image References.
	// We need to set only those Image References that are referenced by GeoShapes, Probability Maps and Text Annotations.
	// If we have multiple annotations in the same SR doc, some of the image references can belong to other annotations.
	pImgAnnotation->SetImageReferenceCollection(imageReferences);
	while(imageReferences.size() > 0)
	{
		delete imageReferences[imageReferences.size() - 1];
		imageReferences.pop_back();
	}

	// User Info
	size_t userNodeId = GO_TO_NAMED_NODE3("121005", "DCM", "Observer Type");
	if (userNodeId > 0)
	{
		_dsrCode = GetCode();
		if (_dsrCode.isValid() && _dsrCode.getCodeValue() == "121006" &&
			_pDoc->getTree().goDown() > 0) // if non-empty Person
		{
			User user = this->ReadUser();
			pImgAnnotation->SetUser(&user);
		}
	}

	// Equipment
	Equipment equipment;
	_pDoc->getManufacturer(ofString);
	if (ofString.length() > 0)
		equipment.SetManufacturerName(ofString.c_str());
	_pDoc->getManufacturerModelName(ofString);
	if (ofString.length() > 0)
		equipment.SetManufacturerModelName(ofString.c_str());
	_pDoc->getSoftwareVersions(ofString);
	if (ofString.length() > 0)
		equipment.SetSoftwareVersion(ofString.c_str());
	if (equipment.GetManufacturerName().length() > 0) // if Equipment is valid
		pImgAnnotation->SetEquipment(&equipment);

	// Patient
	Person patient;
	_pDoc->getPatientID(ofString);
	if (ofString.length() > 0)
		patient.SetId(ofString.c_str());
	_pDoc->getPatientName(ofString);
	patient.SetName(ofString.c_str());
	_pDoc->getPatientSex(ofString);
	patient.SetSex(ofString.c_str());
	_pDoc->getPatientBirthDate(ofString);
	Date birthDate(ofString.c_str());
	if (birthDate != Date())
		patient.SetBirthDate(birthDate);
	_pDoc->getEthnicGroup(ofString);
	if (ofString.length() > 0)
		patient.SetEthnicGroup(ofString.c_str());
	if (patient.GetId().length() > 0 && patient.GetName().length() > 0) // if Patient is valid
		pImgAnnotation->SetPatient(patient);


	// Annotation-level collections
	AnatomicEntityVector anatomicEntities;
	ImagingObservationVector imagingObservations;
	CalculationVector calculations;
	InferenceVector inferences;

	// IMPORTANT: From this point on, the code assumes that all nodes are read in order.

	// Annotation container
	nodeId = _pDoc->getTree().gotoNode(imgAnnotationNodeId);

	// Annotation DateTime
	ofString = _pDoc->getTree().getCurrentContentItem().getObservationDateTime();
	DateTime creationDateTime(ofString.c_str());
	if (creationDateTime != DateTime())
		pImgAnnotation->SetDateTime(creationDateTime);

	size_t containerNodeId = _pDoc->getTree().goDown();
	while(containerNodeId > 0)
	{
		_dsrCode = this->GetConceptName();
		ofString = _dsrCode.getCodeValue();
		if (ofString == "zzz005")
		{
			// Annotation Type
			_dsrCode = this->GetCode();
			pImgAnnotation->SetCodeValue(_dsrCode.getCodeValue().c_str());
			pImgAnnotation->SetCodeMeaning(_dsrCode.getCodeMeaning().c_str());
			pImgAnnotation->SetCodingSchemeDesignator(_dsrCode.getCodingSchemeDesignator().c_str());
			pImgAnnotation->SetCodingSchemeVersion(_dsrCode.getCodingSchemeVersion().c_str());
		}
		else if (ofString == "112040")
		{
			// Tracking Unique Identifier - Annotation UID
			_stdString = this->GetStringValue();
			pImgAnnotation->SetUniqueidentifier(_stdString);
		}
		else if (ofString == "112039")
		{
			// Annotation Name
			_stdString = this->GetStringValue();
			pImgAnnotation->SetName(_stdString);
		}
		else if (ofString == "121106")
		{
			// Annotation Comment
			_stdString = this->GetStringValue();
			pImgAnnotation->SetComment(_stdString);
		}
		else if (ofString == "zzz068")
		{
			// Precedent AIM Annotation
			_stdString = this->GetStringValue();
			pImgAnnotation->SetPrecedentReferencedAnnotationUID(_stdString);
		}
		else if (ofString == "zzz063")
		{
			// AIM Status
			AimStatus aimStatus = this->ReadAimStatus();
			pImgAnnotation->SetAimStatus(&aimStatus);
		}
		else if (ofString == "zzz008")
		{
			// Anatomic Entity Entry
			AnatomicEntity anatomicEntity = this->ReadAnatomicEntityEntry();
			anatomicEntities.push_back(anatomicEntity);
		}
		else if (ofString == "zzz009")
		{
			// Imaging Observation Entry
			ImagingObservation imagingObservation = this->ReadImagingObservationEntry();
			imagingObservations.push_back(imagingObservation);
		}
		else if (ofString == "zzz011")
		{
			// Calculation Entry
			Calculation calculation;
			calculation = this->ReadCalculationEntry();
			calculations.push_back(calculation);
		}
		else if (ofString == "zzz054")
		{
			// Inference Entry
			Inference inference = this->ReadInferenceEntry();
			inferences.push_back(inference);
		}
		else if (ofString == "zzz030")
		{
			// Image Annotation container
			this->ReadImageAnnotationContainer(*pImgAnnotation);
		}
		else if (ofString == "zzz031")
		{
			// Annotation Of Annotation container
			assert(false); // this must be an image annotation
		}
		else
			assert(false); // unknown image template tag

		containerNodeId = _pDoc->getTree().gotoNext();
	}

	// Set filled collections
	if (anatomicEntities.size() > 0)
		pImgAnnotation->SetAnatomicEntityCollection(anatomicEntities);
	if (imagingObservations.size() > 0)
		pImgAnnotation->SetImagingObservationCollection(imagingObservations);
	if(calculations.size() > 0)
		pImgAnnotation->SetCalculationCollection(calculations);
	if (inferences.size() > 0)
		pImgAnnotation->SetInferenceCollection(inferences);

	return pImgAnnotation;
}

AnnotationOfAnnotation* DcmModelInternal::ReadAnnotationOfAnnotation(size_t annAnnotationNodeId)
{
	AnnotationOfAnnotation* pAnnOfAnnotation = new AnnotationOfAnnotation();

	// AIM Version
	nodeId = GO_TO_NAMED_NODE2("zzz003", "AIM Version");
	_stdString = GetStringValue();
	pAnnOfAnnotation->SetAimVersion(_stdString);

	// User Info
	size_t userNodeId = GO_TO_NAMED_NODE3("121005", "DCM", "Observer Type");
	if (userNodeId > 0)
	{
		_dsrCode = GetCode();
		if (_dsrCode.isValid() && _dsrCode.getCodeValue() == "121006" &&
			_pDoc->getTree().goDown() > 0) // if non-empty Person
		{
			User user = this->ReadUser();
			pAnnOfAnnotation->SetUser(&user);
		}
	}

	// Equipment
	Equipment equipment;
	_pDoc->getManufacturer(ofString);
	if (ofString.length() > 0)
		equipment.SetManufacturerName(ofString.c_str());
	_pDoc->getManufacturerModelName(ofString);
	if (ofString.length() > 0)
		equipment.SetManufacturerModelName(ofString.c_str());
	_pDoc->getSoftwareVersions(ofString);
	if (ofString.length() > 0)
		equipment.SetSoftwareVersion(ofString.c_str());
	if (equipment.GetManufacturerName().length() > 0) // if Equipment is valid
		pAnnOfAnnotation->SetEquipment(&equipment);

	//// Patient
	//Patient patient;
	//_pDoc->getPatientID(ofString);
	//	patient.SetPatientID(ofString.c_str());
	//_pDoc->getPatientsName(ofString);
	//patient.SetName(ofString.c_str());
	//_pDoc->getPatientsSex(ofString);
	//patient.SetSex(ofString.c_str());
	//_pDoc->getPatientsBirthDate(ofString);
	//Date birthDate(ofString.c_str());
	//if (birthDate != Date())
	//	patient.SetBirthDate(birthDate);
	//_pDoc->getEthnicGroup(ofString);
	//if (ofString.length() > 0)
	//	patient.SetEthnicGroup(ofString.c_str());
	//if (patient.GetPatientID().length() > 0 && patient.GetName().length() > 0) // if Patient is valid
	//	pAnnOfAnnotation->SetPatient(&patient);


	// Annotation-level collections
	AnatomicEntityVector anatomicEntities;
	ImagingObservationVector imagingObservations;
	CalculationVector calculations;
	InferenceVector inferences;

	// IMPORTANT: From this point on, the code assumes that all nodes are read in order.

	// Annotation container
	nodeId = _pDoc->getTree().gotoNode(annAnnotationNodeId);

	// Annotation DateTime
	ofString = _pDoc->getTree().getCurrentContentItem().getObservationDateTime();
	DateTime creationDateTime(ofString.c_str());
	if (creationDateTime != DateTime())
		pAnnOfAnnotation->SetDateTime(creationDateTime);

	size_t containerNodeId = _pDoc->getTree().goDown();
	while(containerNodeId > 0)
	{
		_dsrCode = this->GetConceptName();
		ofString = _dsrCode.getCodeValue();
		if (ofString == "zzz005")
		{
			// Annotation Type
			_dsrCode = this->GetCode();
			pAnnOfAnnotation->SetCodeValue(_dsrCode.getCodeValue().c_str());
			pAnnOfAnnotation->SetCodeMeaning(_dsrCode.getCodeMeaning().c_str());
			pAnnOfAnnotation->SetCodingSchemeDesignator(_dsrCode.getCodingSchemeDesignator().c_str());
			pAnnOfAnnotation->SetCodingSchemeVersion(_dsrCode.getCodingSchemeVersion().c_str());
		}
		else if (ofString == "112040")
		{
			// Tracking Unique Identifier - Annotation UID
			_stdString = this->GetStringValue();
			pAnnOfAnnotation->SetUniqueidentifier(_stdString);
		}
		else if (ofString == "112039")
		{
			// Annotation Name
			_stdString = this->GetStringValue();
			pAnnOfAnnotation->SetName(_stdString);
		}
		else if (ofString == "121106")
		{
			// Annotation Comment
			_stdString = this->GetStringValue();
			pAnnOfAnnotation->SetComment(_stdString);
		}
		else if (ofString == "zzz068")
		{
			// Precedent AIM Annotation
			_stdString = this->GetStringValue();
			pAnnOfAnnotation->SetPrecedentReferencedAnnotationUID(_stdString);
		}
		else if (ofString == "zzz063")
		{
			// AIM Status
			AimStatus aimStatus = this->ReadAimStatus();
			pAnnOfAnnotation->SetAimStatus(&aimStatus);
		}
		else if (ofString == "zzz008")
		{
			// Anatomic Entity Entry
			AnatomicEntity anatomicEntity = this->ReadAnatomicEntityEntry();
			anatomicEntities.push_back(anatomicEntity);
		}
		else if (ofString == "zzz009")
		{
			// Imaging Observation Entry
			ImagingObservation imagingObservation = this->ReadImagingObservationEntry();
			imagingObservations.push_back(imagingObservation);
		}
		else if (ofString == "zzz011")
		{
			// Calculation Entry
			Calculation calculation;
			calculation = this->ReadCalculationEntry();
			calculations.push_back(calculation);
		}
		else if (ofString == "zzz054")
		{
			// Inference Entry
			Inference inference = this->ReadInferenceEntry();
			inferences.push_back(inference);
		}
		else if (ofString == "zzz030")
		{
			// Image Annotation container
			assert(false); // this must be an annotation of annotation
		}
		else if (ofString == "zzz031")
		{
			// Annotation Of Annotation container
			this->ReadAnnotationOfAnnotationContainer(*pAnnOfAnnotation);
		}
		else
			assert(false); // unknown image template tag

		containerNodeId = _pDoc->getTree().gotoNext();
	}

	// Set filled collections
	if (anatomicEntities.size() > 0)
		pAnnOfAnnotation->SetAnatomicEntityCollection(anatomicEntities);
	if (imagingObservations.size() > 0)
		pAnnOfAnnotation->SetImagingObservationCollection(imagingObservations);
	if(calculations.size() > 0)
		pAnnOfAnnotation->SetCalculationCollection(calculations);
	if (inferences.size() > 0)
		pAnnOfAnnotation->SetInferenceCollection(inferences);

	return pAnnOfAnnotation;
}

// read string value from the CurrentContentItem
const std::string DcmModelInternal::GetStringValue(const std::string& defaultValue) const
{
	assert(_pDoc->getTree().getCurrentContentItem().getValueType() == DSRTypes::VT_Text ||
		_pDoc->getTree().getCurrentContentItem().getValueType() == DSRTypes::VT_DateTime ||
		_pDoc->getTree().getCurrentContentItem().getValueType() == DSRTypes::VT_Date ||
		_pDoc->getTree().getCurrentContentItem().getValueType() == DSRTypes::VT_Time ||
		_pDoc->getTree().getCurrentContentItem().getValueType() == DSRTypes::VT_UIDRef ||
		_pDoc->getTree().getCurrentContentItem().getValueType() == DSRTypes::VT_PName);

	return _pDoc->getTree().getNodeID() > 0 ? _pDoc->getTree().getCurrentContentItem().getStringValue().data() : defaultValue;
}

// Reads NUM value from the current NUM node of the document
const DSRNumericMeasurementValue& DcmModelInternal::GetNumericValue() const
{
	assert(_pDoc->getTree().getCurrentContentItem().getValueType() == DSRTypes::VT_Num);

	if (_pDoc->getTree().getCurrentContentItem().getNumericValuePtr() == NULL)
		return AIMCodes::EmptyNumericMeasurementValue;
	else
		return _pDoc->getTree().getCurrentContentItem().getNumericValue();
}

// read code value from the CurrentContentItem
const DSRCodedEntryValue& DcmModelInternal::GetCode() const
{
	assert(_pDoc->getTree().getCurrentContentItem().getValueType() == DSRTypes::VT_Code);

	if (_pDoc->getTree().getCurrentContentItem().getCodeValue().isValid())
		return _pDoc->getTree().getCurrentContentItem().getCodeValue();
	else
		return AIMCodes::EmptyCodedEntryValue;
}

// read concept name from the CurrentContentItem
const DSRCodedEntryValue& DcmModelInternal::GetConceptName() const
{
	if (_pDoc->getTree().getCurrentContentItem().getConceptNamePtr() == NULL)
		return AIMCodes::EmptyCodedEntryValue;
	else
		return _pDoc->getTree().getCurrentContentItem().getConceptName();
}

// read spatial coordinate from the CurrentContentItem
const DSRSpatialCoordinatesValue& DcmModelInternal::GetSpatialCoordinate() const
{
	if (_pDoc->getTree().getCurrentContentItem().getSpatialCoordinatesPtr() == NULL)
		return AIMCodes::EmptySpatialCoordinateValue;
	else
		return _pDoc->getTree().getCurrentContentItem().getSpatialCoordinates();
}

// read image reference from the CurrentContentItem
const DSRImageReferenceValue& DcmModelInternal::GetImageReference() const
{
	if (_pDoc->getTree().getCurrentContentItem().getImageReferencePtr() == NULL)
		return AIMCodes::EmptyImageReferenceValue;
	else
		return _pDoc->getTree().getCurrentContentItem().getImageReference();
}

// Reads boolean value from the current CODE node: ("R-0038D", "SRT", "Yes")("R-00339", "SRT", "No")
const bool DcmModelInternal::GetBooleanValue(const bool defaultValue/* = true*/) const
{
	OFString codeValue = this->GetCode().getCodeValue();

	assert(codeValue == "R-0038D" || codeValue == "R-00339");

	if (codeValue == "R-0038D")
		return true;
	else if (codeValue == "R-00339")
		return false;

	return defaultValue;
}

User DcmModelInternal::ReadUser()
{
	User user;

	// Read Observer container
	do
	{
		_dsrCode = GetConceptName();
		if (_dsrCode.isValid())
		{
			_stdString = _dsrCode.getCodeValue().data();
			if("121008" == _stdString) // Name
				user.SetName(GetStringValue());
			else if ("121011" == _stdString) // Role In Procedure
				user.SetRoleInTrial(GetCode().getCodeMeaning().c_str());
			else if ("zzz026" == _stdString) // Login Name
				user.SetLoginName(GetStringValue());
			else if ("zzz045" == _stdString) // number within Role of Clinical Trial
			{
				_stdString = GetStringValue();
				user.SetNumberWithinRoleOfClinicalTrial(AIMUtil::StringToInt(_stdString));
			}
			else
				assert(false); // unexpected tag
		}
	} while(_pDoc->getTree().gotoNext() > 0);

	return user;
}

bool PSEqual(const PresentationState& first, const PresentationState& second)
{
	return first.GetSopInstanceUID() == second.GetSopInstanceUID();
}

ImageReferencePtrVector DcmModelInternal::ReadImageLibrary(size_t annotationNodeId, size_t nextAnnotationNodeId)
{
	ImageReferencePtrVector imageReferences;

	// Find Image library of the current annotation
	DSRCodedEntryValue dsrImgLib = DSR_CDE("111028", "DCM", "Image Library");
	size_t imgLibraryNodeId = GO_TO_NAMED_NODE1(dsrImgLib);
	// There is only one Image Library in the AIM SR document
	//while (imgLibraryNodeId > 0 &&
	//	imgLibraryNodeId < annotationNodeId && imgLibraryNodeId > nextAnnotationNodeId)
	//{
	//	imgLibraryNodeId = GO_TO_NEXT_NAMED_NODE1(dsrImgLib);
	//}

	// If Image Library Exists
	if (imgLibraryNodeId > 0 /*&& imgLibraryNodeId < annotationNodeId && imgLibraryNodeId > nextAnnotationNodeId*/)
	{
		size_t imgReferenceNodeId = _pDoc->getTree().goDown();
		while(imgReferenceNodeId > 0)
		{
			const DSRImageReferenceValue& imgReference = this->GetImageReference();
			if (imgReference.isValid())
			{
				// NOTE: Presentation States are stored within each image reference
				PresentationStateVector presentationStates;
				ImageStudy newStudy = this->ReadStudyFromImageRefValue(imgReference, presentationStates);

				// We expect at least one image in the study
				assert(newStudy.GetSeries().GetImageCollection().size() > 0);

				// Either create a new study/series if one doesn't exist,
				// or add image information to an existing study/series
				bool bAdded = false;
				for(ImageReferencePtrVector::iterator iter = imageReferences.begin(); !bAdded && iter < imageReferences.end(); iter++)
				{
					if ((*iter)->GetImageReferenceType() == ImageReference::T_DICOM_IMAGE_REF)
					{
						DICOMImageReference* pDicomImageRef = dynamic_cast<DICOMImageReference*>(*iter);
						if (pDicomImageRef != NULL)
						{
							ImageStudy currentStudy = pDicomImageRef->GetStudy();
							ImageSeries currentSeries = currentStudy.GetSeries();
							if (currentStudy.GetInstanceUID() == newStudy.GetInstanceUID() && currentSeries.GetInstanceUID() == newStudy.GetSeries().GetInstanceUID())
							{
								if (newStudy.GetSeries().GetImageCollection().size() > 0)
								{
									ImageVector imgVector = currentSeries.GetImageCollection();
									imgVector.push_back(newStudy.GetSeries().GetImageCollection()[0]); // only one image ?
									currentSeries.SetImageCollection(imgVector);
									currentStudy.SetSeries(currentSeries);
									pDicomImageRef->SetStudy(currentStudy);
									// Add only new Presentation States
									if (presentationStates.size() > 0)
									{
										if (pDicomImageRef->GetPresentationStateCollection().size() > 0)
										{
											// Insert only unique PS objects
											PresentationStateVector existingPresentationStates = pDicomImageRef->GetPresentationStateCollection();
											PresentationStateVector newPresentationStates;
											for(PresentationStateVector::iterator psIter = presentationStates.begin(); psIter < presentationStates.end(); psIter++)
											{
												bool isPresent = std::includes(existingPresentationStates.begin(), existingPresentationStates.end(), psIter, psIter, PSEqual);

												if (!isPresent)
													newPresentationStates.push_back(*psIter);
											}
											existingPresentationStates.insert(existingPresentationStates.end(), newPresentationStates.begin(), newPresentationStates.end());
											pDicomImageRef->SetPresentationStateCollection(existingPresentationStates);
										}
										else
										{
											pDicomImageRef->SetPresentationStateCollection(presentationStates);
										}
									}
									bAdded = true;
								}
							}
						}
					}
				}
				if (!bAdded)
				{
					// The image belongs to a not-seen-before study - needs new DIOCMImageReference
					DICOMImageReference dicomImageReference;

					dicomImageReference.SetStudy(newStudy);
					dicomImageReference.SetPresentationStateCollection(presentationStates);
					imageReferences.push_back(dicomImageReference.Clone());
				}
			}

			// Next Image Reference
			imgReferenceNodeId = _pDoc->getTree().gotoNext();
		}
	}

	return imageReferences;
}

AnatomicEntity DcmModelInternal::ReadAnatomicEntityEntry()
{
	AnatomicEntity anatomicEntity;
	AnatomicEntityCharacteristicVector anatomicEntityChars;

	// Anatomic Entity
	assert(this->GetConceptName().getCodeValue() == "zzz008");
	_dsrCode = GetCode();
	assert(_dsrCode.isValid());
	anatomicEntity.SetCodeValue(_dsrCode.getCodeValue().c_str());
	anatomicEntity.SetCodeMeaning(_dsrCode.getCodeMeaning().c_str());
	anatomicEntity.SetCodingSchemeDesignator(_dsrCode.getCodingSchemeDesignator().c_str());
	anatomicEntity.SetCodingSchemeVersion(_dsrCode.getCodingSchemeVersion().c_str());

	if (_pDoc->getTree().goDown() > 0)
	{
		do
		{
			ofString = this->GetConceptName().getCodeValue();
			if (ofString == "C45561")
			{
				// Label
				anatomicEntity.SetLabel(GetStringValue());
			}
			else if (ofString == "zzz058")
			{
				// Annotator Confidence
				ofString = this->GetNumericValue().getNumericValue();
				double confidence = AIMUtil::StringToDouble(ofString.c_str());
				anatomicEntity.SetAnnotatorConfidence(&confidence);
			}
			else if(ofString == "G-A203")
			{
				// Is Present
				anatomicEntity.SetIsPresent(this->GetBooleanValue());
			}
			else if(ofString == "zzz052")
			{
				// Anatomic Entity Characteristic
				AnatomicEntityCharacteristic anatomicEntityChar = this->ReadAnatomicEntityCharacteristicEntry();
				anatomicEntityChars.push_back(anatomicEntityChar);
			}
			else
			{
				assert(false); // unknown content node
			}
		}
		while(_pDoc->getTree().gotoNext() > 0);

		if (anatomicEntityChars.size() > 0)
			anatomicEntity.SetAnatomicEntityCharacteristicCollection(anatomicEntityChars);

		nodeId = _pDoc->getTree().goUp();
	}

	return anatomicEntity;
}

AnatomicEntityCharacteristic DcmModelInternal::ReadAnatomicEntityCharacteristicEntry()
{
	AnatomicEntityCharacteristic anatomicEntityChar;
	CharacteristicQuantificationPtrVector charQuantifications;

	// Anatomic Entity Characteristic
	assert(this->GetConceptName().getCodeValue() == "zzz052");
	_dsrCode = GetCode();
	assert(_dsrCode.isValid());
	anatomicEntityChar.SetCodeValue(_dsrCode.getCodeValue().c_str());
	anatomicEntityChar.SetCodeMeaning(_dsrCode.getCodeMeaning().c_str());
	anatomicEntityChar.SetCodingSchemeDesignator(_dsrCode.getCodingSchemeDesignator().c_str());
	anatomicEntityChar.SetCodingSchemeVersion(_dsrCode.getCodingSchemeVersion().c_str());

	if (_pDoc->getTree().goDown() > 0)
	{
		do
		{
			ofString = this->GetConceptName().getCodeValue();
			if (ofString == "C45561")
			{
				// Label
				anatomicEntityChar.SetLabel(GetStringValue());
			}
			else if (ofString == "zzz058")
			{
				// Confidence
				ofString = this->GetNumericValue().getNumericValue();
				double confidence = AIMUtil::StringToDouble(ofString.c_str());
				anatomicEntityChar.SetAnnotatorConfidence(&confidence);
			}
			else if(ofString == "zzz066")
			{
				// Characteristic Quantification
				CharacteristicQuantification* pCharQuantification = this->ReadCharacteristicQuantification();
				if (pCharQuantification != NULL)
					charQuantifications.push_back(pCharQuantification);
			}
			else
			{
				assert(false); // unknown content node
			}
		}
		while(_pDoc->getTree().gotoNext() > 0);

		nodeId = _pDoc->getTree().goUp();
	}

	if (charQuantifications.size() > 0)
	{
		anatomicEntityChar.SetCharacteristicQuantificationCollection(charQuantifications);
		while(charQuantifications.size() > 0)
		{
			delete charQuantifications[charQuantifications.size() - 1];
			charQuantifications.pop_back();
		}
	}

	return anatomicEntityChar;
}

ImagingObservation DcmModelInternal::ReadImagingObservationEntry()
{
	ImagingObservation imagingObservation;
	ImagingObservationCharacteristicVector imagingObsCharacteristics;

	// Imaging Observation
	assert(this->GetConceptName().getCodeValue() == "zzz009");
	_dsrCode = GetCode();
	assert(_dsrCode.isValid());
	imagingObservation.SetCodeValue(_dsrCode.getCodeValue().c_str());
	imagingObservation.SetCodeMeaning(_dsrCode.getCodeMeaning().c_str());
	imagingObservation.SetCodingSchemeDesignator(_dsrCode.getCodingSchemeDesignator().c_str());
	imagingObservation.SetCodingSchemeVersion(_dsrCode.getCodingSchemeVersion().c_str());

	if (_pDoc->getTree().goDown() > 0)
	{
		do
		{
			ofString = this->GetConceptName().getCodeValue();
			if (ofString == "C45561")
			{
				// Label
				imagingObservation.SetLabel(GetStringValue());
			}
			else if (ofString == "121106")
			{
				// Comment
				imagingObservation.SetComment(GetStringValue());
			}
			else if (ofString == "zzz058")
			{
				// Annotator Confidence
				ofString = this->GetNumericValue().getNumericValue();
				double confidence = AIMUtil::StringToDouble(ofString.c_str());
				imagingObservation.SetAnnotatorConfidence(&confidence);
			}
			else if(ofString == "G-A203")
			{
				// Is Present
				imagingObservation.SetIsPresent(this->GetBooleanValue());
			}
			else if(ofString == "zzz010")
			{
				// Imaging Observation Characteristics
				ImagingObservationCharacteristic imgObsChar = this->ReadImagingObservationCharacteristicEntry();
				imagingObsCharacteristics.push_back(imgObsChar);
			}
			else if (ofString == "zzz055")
			{
				// Referenced Geometric Shape
				ReferencedGeometricShape refGeoShape;
				refGeoShape.SetReferencedShapeIdentifier(AIMUtil::StringToInt(GetStringValue()));
				imagingObservation.SetReferencedGeometricShape(&refGeoShape);
			}
			else
			{
				assert(false); // unknown content node
			}
		}
		while(_pDoc->getTree().gotoNext() > 0);

		if (imagingObsCharacteristics.size() > 0)
			imagingObservation.SetImagingObservationCharacteristicCollection(imagingObsCharacteristics);

		nodeId = _pDoc->getTree().goUp();
	}

	return imagingObservation;
}

ImagingObservationCharacteristic DcmModelInternal::ReadImagingObservationCharacteristicEntry()
{
	ImagingObservationCharacteristic imagingObsChar;
	CharacteristicQuantificationPtrVector charQuantifications;

	// Imaging Observation Characteristic
	assert(this->GetConceptName().getCodeValue() == "zzz010");
	_dsrCode = GetCode();
	assert(_dsrCode.isValid());
	imagingObsChar.SetCodeValue(_dsrCode.getCodeValue().c_str());
	imagingObsChar.SetCodeMeaning(_dsrCode.getCodeMeaning().c_str());
	imagingObsChar.SetCodingSchemeDesignator(_dsrCode.getCodingSchemeDesignator().c_str());
	imagingObsChar.SetCodingSchemeVersion(_dsrCode.getCodingSchemeVersion().c_str());
	if(_pDoc->getTree().goDown() > 0)
	{
		do
		{
			ofString = this->GetConceptName().getCodeValue();
			if (ofString == "C45561")
			{
				// Label
				imagingObsChar.SetLabel(GetStringValue());
			}
			else if (ofString == "121106")
			{
				// Comment
				imagingObsChar.SetComment(GetStringValue());
			}
			else if (ofString == "zzz058")
			{
				// Annotator Confidence
				ofString = this->GetNumericValue().getNumericValue();
				double confidence = AIMUtil::StringToDouble(ofString.c_str());
				imagingObsChar.SetAnnotatorConfidence(&confidence);
			}
			else if(ofString == "zzz066")
			{
				// Characteristic Quantification
				CharacteristicQuantification* pCharQuantification = this->ReadCharacteristicQuantification();
				if (pCharQuantification != NULL)
					charQuantifications.push_back(pCharQuantification);
			}
			else
			{
				assert(false); // unknown content node
			}
		}
		while(_pDoc->getTree().gotoNext() > 0);

		nodeId = _pDoc->getTree().goUp();
	}

	if (charQuantifications.size() > 0)
	{
		imagingObsChar.SetCharacteristicQuantificationCollection(charQuantifications);
		while(charQuantifications.size() > 0)
		{
			delete charQuantifications[charQuantifications.size() - 1];
			charQuantifications.pop_back();
		}
	}

	return imagingObsChar;
}

CharacteristicQuantification* DcmModelInternal::ReadCharacteristicQuantification()
{
	assert(this->GetConceptName().getCodeValue() == "zzz066");

	CharacteristicQuantification* pCharQuantification = NULL;
	Numerical* pNumerical = NULL;
	Quantile* pQuantile = NULL;
	NonQuantifiable* pNonQuantifiable = NULL;
	Scale* pScale = NULL;
	Interval* pInterval = NULL;

	ofString = this->GetCode().getCodeValue();
	if (ofString == "chq001")
		pCharQuantification = pNumerical = new Numerical();
	else if(ofString == "chq002")
		pCharQuantification = pQuantile = new Quantile();
	else if(ofString == "chq003")
		pCharQuantification = pNonQuantifiable = new NonQuantifiable();
	else if(ofString == "chq004")
		pCharQuantification = pScale = new Scale();
	else if (ofString == "chq005")
		pCharQuantification = pInterval = new Interval();
	else
	{
		assert(false); // Unknown Quantification Characteristic
		return NULL;
	}

	assert(pCharQuantification != NULL);

	if(_pDoc->getTree().goDown() > 0)
	{
		do
		{
			ofString = GetConceptName().getCodeValue();
			if (ofString == "112039")
			{
				pCharQuantification->SetName(this->GetStringValue());
			}
			else if (ofString == "zzz058")
			{
				// Annotator Confidence
				ofString = this->GetNumericValue().getNumericValue();
				double confidence = AIMUtil::StringToDouble(ofString.c_str());
				pCharQuantification->SetAnnotatorConfidence(&confidence);
			}
			else if (ofString == "C25712" && pNumerical != NULL) // Numerical
			{
				assert(pNumerical != NULL);

				// Value
				DSRNumericMeasurementValue dsrNumValue = this->GetNumericValue();

				ofString = dsrNumValue.getNumericValue();
				pNumerical->SetValue(AIMUtil::StringToDouble(ofString.c_str()));

				_dsrCode = dsrNumValue.getMeasurementUnit();
				if (_dsrCode.isValid())
				{
					ofString.assign(_dsrCode.getCodeMeaning());
					pNumerical->SetUcumString(ofString.c_str());
				}

				if(_pDoc->getTree().goDown() > 0)
				{
					assert(GetConceptName().getCodeValue() == "C61580"); // Operator

					// Operator
					pNumerical->SetOperator(AIMCodes::GetComparisonOperatorType(GetCode()));

					nodeId = _pDoc->getTree().goUp();
				}
			}
			else if (ofString == "C63902") // Quantile
			{
				assert(pQuantile != NULL);

				// Bin
				pQuantile->SetBin(AIMUtil::StringToInt(GetNumericValue().getNumericValue().c_str()));
			}
			else if (ofString == "zzz067") // Non-Quantifiable
			{
				assert(pNonQuantifiable != NULL);

				// Code
				_dsrCode = GetCode();
				pNonQuantifiable->SetCodeValue(_dsrCode.getCodeValue().c_str());
				pNonQuantifiable->SetCodeMeaning(_dsrCode.getCodeMeaning().c_str());
				pNonQuantifiable->SetCodingSchemeDesignator(_dsrCode.getCodingSchemeDesignator().c_str());
				pNonQuantifiable->SetCodingSchemeVersion(_dsrCode.getCodingSchemeVersion().c_str());
			}
			else if (ofString == "C25712" && pScale != NULL) // Scale
			{
				assert(pScale != NULL);

				// Value
				pScale->SetValue(GetStringValue());

				if(_pDoc->getTree().goDown() > 0)
				{
					do
					{
						ofString = this->GetConceptName().getCodeValue();
						if (ofString == "121106")
						{
							// Comment
							pScale->SetComment(GetStringValue());
						}
						else if (ofString == "C25365")
						{
							// Description
							pScale->SetDescription(GetStringValue());
						}
						else
							assert(false); // Unknown Scale tag
					}
					while(_pDoc->getTree().gotoNext() > 0);

					nodeId = _pDoc->getTree().goUp();
				}
			}
			else if (ofString == "G-A437") // Interval
			{
				assert(pInterval != NULL);

				// Maximum
				DSRNumericMeasurementValue dsrNumValue = this->GetNumericValue();
				pInterval->SetMaxValue(AIMUtil::StringToDouble(dsrNumValue.getNumericValue().c_str()));
				pInterval->SetUcumString(dsrNumValue.getMeasurementUnit().getCodeMeaning().c_str());

				if (_pDoc->getTree().goDown() > 0)
				{
					// Maximum Operator
					if (this->GetConceptName().getCodeValue() == "C61580")
						pInterval->SetMaxOperator(AIMCodes::GetComparisonOperatorType(GetCode()));
					else
						assert(false); // required operator is missing

					nodeId = _pDoc->getTree().goUp();
				}
			}
			else if (ofString == "R-404FB") // Interval
			{
				assert(pInterval != NULL);

				// Minimum
				DSRNumericMeasurementValue dsrNumValue = this->GetNumericValue();
				pInterval->SetMinValue(AIMUtil::StringToDouble(dsrNumValue.getNumericValue().c_str()));
				pInterval->SetUcumString(dsrNumValue.getMeasurementUnit().getCodeMeaning().c_str());

				if (_pDoc->getTree().goDown() > 0)
				{
					// Minimum Operator
					if (this->GetConceptName().getCodeValue() == "C61580")
						pInterval->SetMinOperator(AIMCodes::GetComparisonOperatorType(GetCode()));
					else
						assert(false); // required operator is missing

					nodeId = _pDoc->getTree().goUp();
				}
			}
			else
				assert(false); // unknown Characteristic Quantification tag
		}
		while(_pDoc->getTree().gotoNext() > 0);

		nodeId = _pDoc->getTree().goUp();
	}
	else
		assert(false); // Characteristic Quantification data is missing

	return pCharQuantification;
}

Calculation DcmModelInternal::ReadCalculationEntry()
{
	Calculation calculation;
	CalcResultVector calcResults;
	ReferencedCalcVector referencedCalculations;
	ReferencedGeometricShapeVector referencedGeoShapes;

	assert(this->GetConceptName().getCodeValue() == "zzz011");

	// Step into calculation container
	if (_pDoc->getTree().goDown() > 0)
	{
		do
		{
			ofString = GetConceptName().getCodeValue();
			if(ofString == "G-C036")
			{
				// Calculation Type
				_dsrCode = GetCode();
				calculation.SetCodeValue(_dsrCode.getCodeValue().c_str());
				calculation.SetCodeMeaning(_dsrCode.getCodeMeaning().c_str());
				calculation.SetCodingSchemeDesignator(_dsrCode.getCodingSchemeDesignator().c_str());
				calculation.SetCodingSchemeVersion(_dsrCode.getCodingSchemeVersion().c_str());
			}
			else if(ofString == "112040")
			{
				// Calculation UID
				calculation.SetUID(GetStringValue());
			}
			else if(ofString == "112034")
			{
				// Calculation Description
				calculation.SetDescription(GetStringValue());
			}
			else if(ofString == "zzz013")
			{
				// Calculation MathML
				calculation.SetMathML(GetStringValue());
			}
			else if(ofString == "111001")
			{
				// Algorithm Name
				calculation.SetAlgorithmName(GetStringValue());
			}
			else if(ofString == "111003")
			{
				// Algorithm Version
				calculation.SetAlgorithmVersion(GetStringValue());
			}
			else if(ofString == "zzz014")
			{
				// Referenced Calculation
				if (_pDoc->getTree().goDown() > 0)
				{
					do
					{
						assert(this->GetConceptName().getCodeValue() == "112040");

						ReferencedCalculation referencedCalc;
						referencedCalc.SetUniqueIdentifier(GetStringValue());
						referencedCalculations.push_back(referencedCalc);
					}
					while(_pDoc->getTree().gotoNext() > 0);

					nodeId = _pDoc->getTree().goUp();
				}

				assert(referencedCalculations.size() > 0); // at least one item in this container must exist
			}
			else if(ofString == "zzz015")
			{
				// Calculation result
				CalculationResult calcResult = this->ReadCalculationResultEntry();
				calcResults.push_back(calcResult);
			}
			else if(ofString == "zzz055")
			{
				// Referenced Geometric Shapes
				ReferencedGeometricShape refGeoShape;
				refGeoShape.SetReferencedShapeIdentifier(AIMUtil::StringToInt(this->GetStringValue()));
				referencedGeoShapes.push_back(refGeoShape);
			}
			else
				assert(false); // unknown calculation template entry
		}
		while(_pDoc->getTree().gotoNext() > 0);

		nodeId = _pDoc->getTree().goUp();
	}

	if (referencedCalculations.size() > 0)
		calculation.SetReferencedCalculationCollection(referencedCalculations);

	if(calcResults.size() > 0)
		calculation.SetCalculationResultCollection(calcResults);

	if (referencedGeoShapes.size() > 0)
		calculation.SetReferencedGeometricShapeCollection(referencedGeoShapes);

	return calculation;
}

CalculationResult DcmModelInternal::ReadCalculationResultEntry()
{
	CalculationResult calcResult;

	assert(this->GetConceptName().getCodeValue() == "zzz015");

	// Special case - Scalar Value
	if (_pDoc->getTree().getCurrentContentItem().getValueType() == DSRTypes::VT_Num)
	{
		DSRNumericMeasurementValue dsrNumValue = this->GetNumericValue();

		CalculationDataVector datum;
		CoordinateVector coordinates;
		Coordinate coordinate;
		CalculationData data;
		DimensionVector dimensions;
		Dimension dim;

		dim.SetIndex(0);
		dim.SetSize(1);
		if (_pDoc->getTree().goDown() > 0)
		{
			dim.SetLabel(GetStringValue());

			nodeId = _pDoc->getTree().goUp();
		}
		dimensions.push_back(dim);

		coordinate.SetDimensionIndex(0);
		coordinate.SetPosition(0);
		coordinates.push_back(coordinate);
		data.SetCoordinateCollection(coordinates);
		data.SetValue(AIMUtil::StringToDouble(dsrNumValue.getNumericValue().c_str()));
		datum.push_back(data);

		calcResult.SetType(Scalar);
		calcResult.SetNumberOfDimensions(1);
		_dsrCode = dsrNumValue.getMeasurementUnit();
		assert(_dsrCode.isValid());
		calcResult.SetUnitOfMeasure(_dsrCode.getCodeMeaning().c_str());
		calcResult.SetDimensionCollection(dimensions);
		calcResult.SetCalculationDataCollection(datum);

		return calcResult;
	}

	assert(_pDoc->getTree().getCurrentContentItem().getValueType() == DSRTypes::VT_Container);

	DimensionVector dimensions;

	if (_pDoc->getTree().goDown() > 0)
	{
		do
		{
			ofString = GetConceptName().getCodeValue();
			if(ofString == "zzz016")
			{
				// Calculation Result Type
				calcResult.SetType(CalculationResult::StringToCalculationResultType(GetCode().getCodeMeaning().c_str()));
			}
			else if (ofString == "zzz017")
			{
				// Number of Dimensions
				calcResult.SetNumberOfDimensions(AIMUtil::StringToInt(GetNumericValue().getNumericValue().c_str()));
			}
			else if (ofString == "zzz039")
			{
				// Calculation Dimension
				if (_pDoc->getTree().goDown() > 0)
				{
					Dimension dim;
					do
					{
						ofString = GetConceptName().getCodeValue();
						if (ofString == "zzz040")
						{
							// Dimension Index
							dim.SetIndex(AIMUtil::StringToInt(GetNumericValue().getNumericValue().c_str()));
						}
						else if (ofString == "zzz041")
						{
							//Dimension Size
							dim.SetSize(AIMUtil::StringToInt(GetNumericValue().getNumericValue().c_str()));
						}
						else if (ofString == "zzz018")
						{
							// Calculation Result Dimension Label
							dim.SetLabel(GetStringValue());
						}
						else
							assert(false); // unknown dimension template item
					}
					while(_pDoc->getTree().gotoNext() > 0);

					dimensions.push_back(dim);

					nodeId = _pDoc->getTree().goUp();
				}
			}
			else if (ofString == "zzz019")
			{
				// CalculationDatum container
				CalculationDataVector datum;

				if (_pDoc->getTree().goDown() > 0)
				{
					assert(GetConceptName().getCodeValue() == "zzz020");
					do
					{
						CalculationData data;

						// Data Value
						ofString.assign(GetNumericValue().getNumericValue());
						if (ofString.length() > 0)
							data.SetValue(AIMUtil::StringToDouble(ofString.c_str()));

						// Data Unit - they are all the same for the entire calculation
						_dsrCode = GetNumericValue().getMeasurementUnit();
						if (_dsrCode.isValid())
						{
							ofString.assign(_dsrCode.getCodeMeaning());
							calcResult.SetUnitOfMeasure(ofString.c_str());
						}

						// Coordinates container
						size_t coordNodeId = _pDoc->getTree().goDown();
						if(coordNodeId > 0)
						{
							assert(GetConceptName().getCodeValue() == "zzz042");

							CoordinateVector coordinates;

							while(coordNodeId > 0)
							{
								// Calculation Result Coordinate
								size_t coordItemId = _pDoc->getTree().goDown();
								if (coordItemId > 0)
								{
									Coordinate coord;
									while(coordItemId > 0)
									{
										ofString = GetConceptName().getCodeValue();
										if (ofString == "zzz040")
										{
											// Dimension Index
											coord.SetDimensionIndex(AIMUtil::StringToInt(GetNumericValue().getNumericValue().c_str()));
										}
										else if (ofString == "zzz043")
										{
											// Coordinate Position
											coord.SetPosition(AIMUtil::StringToInt(GetNumericValue().getNumericValue().c_str()));
										}
										else
											assert(false); // unknown coordinate template item

										coordItemId = _pDoc->getTree().gotoNext();
									}

									coordinates.push_back(coord);

									nodeId = _pDoc->getTree().goUp();
								}

								coordNodeId = _pDoc->getTree().gotoNext();
							}

							assert(coordinates.size() > 0);
							if (coordinates.size() > 0)
								data.SetCoordinateCollection(coordinates);

							nodeId = _pDoc->getTree().goUp();
						}

						datum.push_back(data);
					}
					while(_pDoc->getTree().gotoNext() > 0);

					nodeId = _pDoc->getTree().goUp();
				}

				assert(datum.size() > 0);
				if (datum.size() > 0)
					calcResult.SetCalculationDataCollection(datum);
			}
			else
				assert(false);

		}
		while(_pDoc->getTree().gotoNext() > 0);

		assert(dimensions.size() > 0); // there must be at least one dimension for each Calculation Result
		if(dimensions.size() > 0)
			calcResult.SetDimensionCollection(dimensions);


		nodeId = _pDoc->getTree().goUp();
	}

	return calcResult;
}

void DcmModelInternal::ReadImageAnnotationContainer(ImageAnnotation& imgAnnotation)
{
	assert(this->GetConceptName().getCodeValue() == "zzz030");

	if (_pDoc->getTree().goDown() > 0)
	{
		TextAnnotationVector textAnnotations;
		SegmentationVector segmentations;
		GeoShapePtrVector geoShapes;

		do
		{
			ofString = this->GetConceptName().getCodeValue();
			if (ofString == "zzz006")
			{
				// Segmentation
				Segmentation segmentation = this->ReadSegmentationEntry();
				segmentations.push_back(segmentation);
			}
			else if (ofString == "zzz022")
			{
				// Geometric Shapes
				GeometricShape* pGeoShape = this->ReadGeoShape();
				if (pGeoShape != NULL)
				{
					geoShapes.push_back(pGeoShape);
				}
			}
			else if (ofString == "zzz028")
			{
				// Text Annotations
				TextAnnotation textAnnotation = this->ReadTextAnnotationContainer();
				textAnnotations.push_back(textAnnotation);
			}
			else
				assert(false); // unexpected
		}
		while(_pDoc->getTree().gotoNext() > 0);

		if (textAnnotations.size() > 0)
			imgAnnotation.SetTextAnnotationCollection(textAnnotations);

		if (segmentations.size() > 0)
			imgAnnotation.SetSegmentationCollection(segmentations);

		if (geoShapes.size() > 0)
		{
			imgAnnotation.SetGeometricShapeCollection(geoShapes);
			while(geoShapes.size() > 0)
			{
				delete geoShapes[geoShapes.size() - 1];
				geoShapes.pop_back();
			}
		}

		nodeId = _pDoc->getTree().goUp();
	}
}

Segmentation DcmModelInternal::ReadSegmentationEntry()
{
	assert(this->GetConceptName().getCodeValue() == "zzz006");

	Segmentation segmentation;

	if (_pDoc->getTree().goDown() > 0)
	{
		do
		{
			if (_pDoc->getTree().getCurrentContentItem().getValueType() == DSRTypes::VT_Image)
			{
				DSRImageReferenceValue dsrImgRef = _pDoc->getTree().getCurrentContentItem().getImageReference();

				if (dsrImgRef.getSOPClassUID() == "1.2.840.10008.5.1.4.1.1.66.4")
				{
					segmentation.SetSopClassUID(dsrImgRef.getSOPClassUID().c_str());
					segmentation.SetSopInstanceUID(dsrImgRef.getSOPInstanceUID().c_str());
				}
				else
				{
					// NOTE: The image must be already in the Image Library
					segmentation.SetReferencedSopInstanceUID(dsrImgRef.getSOPInstanceUID().c_str());
				}
			}
			else
			{
				ofString = GetConceptName().getCodeValue();
				if (ofString == "zzz060")
				{
					segmentation.SetSegmentNumber(AIMUtil::StringToInt(GetNumericValue().getNumericValue().c_str()));
				}
				else if (ofString == "zzz009")
				{
					// Imaging Observation
					ImagingObservation imagingObs = this->ReadImagingObservationEntry();
					segmentation.SetImagingObservation(&imagingObs);
				}
				else
					assert(false); // unexpected entry
			}
		}
		while(_pDoc->getTree().gotoNext() > 0);

		nodeId = _pDoc->getTree().goUp();
	}
	else
	{
		assert(false); // Segmentation data is missing
	}

	return segmentation;
}

Inference DcmModelInternal::ReadInferenceEntry()
{
	assert(this->GetConceptName().getCodeValue() == "zzz054");

	Inference inference;

	_dsrCode = GetCode();
	assert(_dsrCode.isValid());
	inference.SetCodeValue(_dsrCode.getCodeValue().c_str());
	inference.SetCodeMeaning(_dsrCode.getCodeMeaning().c_str());
	inference.SetCodingSchemeDesignator(_dsrCode.getCodingSchemeDesignator().c_str());
	inference.SetCodingSchemeVersion(_dsrCode.getCodingSchemeVersion().c_str());

	if (_pDoc->getTree().goDown() > 0)
	{
		do
		{
			ofString = this->GetConceptName().getCodeValue();
			if (ofString == "zzz058")
			{
				// Annotator Confidence
				ofString = this->GetNumericValue().getNumericValue();
				double confidence = AIMUtil::StringToDouble(ofString.c_str());
				inference.SetAnnotatorConfidence(&confidence);
			}
			else if(ofString == "zzz059")
			{
				// Image Evidence
				inference.SetImageEvidence(this->GetBooleanValue());
			}
			else
			{
				assert(false); // unknown content node
			}
		}
		while(_pDoc->getTree().gotoNext() > 0);

		nodeId = _pDoc->getTree().goUp();
	}

	return inference;
}

AimStatus DcmModelInternal::ReadAimStatus()
{
	assert(this->GetConceptName().getCodeValue() == "zzz063");

	AimStatus aimStatus;

	_dsrCode = GetCode();
	assert(_dsrCode.isValid());
	aimStatus.SetCodeValue(_dsrCode.getCodeValue().c_str());
	aimStatus.SetCodeMeaning(_dsrCode.getCodeMeaning().c_str());
	aimStatus.SetCodingSchemeDesignator(_dsrCode.getCodingSchemeDesignator().c_str());
	aimStatus.SetCodingSchemeVersion(_dsrCode.getCodingSchemeVersion().c_str());

	if (_pDoc->getTree().goDown() > 0)
	{
		do
		{
			ofString = this->GetConceptName().getCodeValue();
			if (ofString == "zzz064")
			{
				// Annotation Version
				ofString = this->GetNumericValue().getNumericValue();
				double confidence = AIMUtil::StringToDouble(ofString.c_str());
				aimStatus.SetAnnotationVersion(confidence);
			}
			else if(ofString == "zzz065")
			{
				// Authorized By
				aimStatus.SetAuthorizedBy(GetStringValue());
			}
			else
			{
				assert(false); // unknown content node
			}
		}
		while(_pDoc->getTree().gotoNext() > 0);

		nodeId = _pDoc->getTree().goUp();
	}

	return aimStatus;
}

GeometricShape* DcmModelInternal::ReadGeoShape()
{
	assert(this->GetConceptName().getCodeValue() == "zzz022");

	GeometricShape* pGeoShape = NULL;
	bool includeFlag = true;
	std::string shapeIdentifier;

	if(_pDoc->getTree().goDown() > 0)
	{
		do
		{
			ofString = GetConceptName().getCodeValue();
			if (ofString == "zzz022")
			{
				assert(_pDoc->getTree().getCurrentContentItem().getValueType() == DSRTypes::VT_SCoord);
				// 2D  SCOORD
				pGeoShape = this->Read2dScoord();
			}
			//else if (_pDoc->getTree().getCurrentContentItem().getValueType() == DSRTypes::VT_3DSCoord)
			//{
			//	// 3D SCOORD
			//	pGeoShape = this->Read3dScoord();
			//}
			else if (ofString == "zzz021")
			{
				// Include Flag
				includeFlag = this->GetBooleanValue();
			}
			else if (ofString == "112039")
			{
				// Shape Identifier
				shapeIdentifier = GetStringValue();
			}
			else
				assert(false); // unknown Geo Shape tag
		}
		while(_pDoc->getTree().gotoNext() > 0);

		nodeId = _pDoc->getTree().goUp();
	}
	else
		assert(false); // Geo Shape data is missing

	if (pGeoShape != NULL)
	{
		pGeoShape->SetIncludeFlag(includeFlag);
		if (shapeIdentifier.length() > 0)
			pGeoShape->SetShapeIdentifier(AIMUtil::StringToInt(shapeIdentifier));
	}

	return pGeoShape;
}

GeometricShape* DcmModelInternal::Read2dScoord()
{
	GeometricShape* pGeoShape = NULL;

	// 2D  SCOORD
	DSRSpatialCoordinatesValue spatialCoord = this->GetSpatialCoordinate();
	if (spatialCoord.isValid())
	{
		switch(spatialCoord.getGraphicType())
		{
		case DSRTypes::GT_Point:
			pGeoShape = new Point();
			break;
		case DSRTypes::GT_Circle:
			pGeoShape = new Circle();
			break;
		case DSRTypes::GT_Ellipse:
			pGeoShape = new Ellipse();
			break;
		case DSRTypes::GT_Polyline:
			pGeoShape = new Polyline();
			break;
		case DSRTypes::GT_Multipoint:
			pGeoShape = new MultiPoint();
			break;
		}

		if (pGeoShape != NULL)
		{
			SpatialCoordPtrVector spatialCoords;
			std::string sopInstanceUID/*, sopClassUID*/;
			Sint32 referencedFrameNumber = 1;

			// Get Image Reference information
			if (_pDoc->getTree().goDown())
			{
				DSRImageReferenceValue imageRef = this->GetImageReference();
				if (imageRef.isValid())
				{
					sopInstanceUID = imageRef.getSOPInstanceUID().data();
					//sopClassUID = imageRef.getSOPClassUID();
					if (!imageRef.getFrameList().isEmpty())
						ofCondition = imageRef.getFrameList().getItem(1, referencedFrameNumber);
				}
				nodeId = _pDoc->getTree().goUp();
			}

			// Get Spatial Coordinates
			// NOTE: Index starts at 1
			for(size_t listIdx=1; listIdx <= spatialCoord.getGraphicDataList().getNumberOfItems(); listIdx++)
			{
				float fX, fY;
				ofCondition = spatialCoord.getGraphicDataList().getItem(listIdx, fX, fY);
				if (ofCondition.good())
				{
					TwoDimensionSpatialCoordinate coord;
					coord.SetX(fX);
					coord.SetY(fY);
					coord.SetImageReferenceUID(sopInstanceUID);
					coord.SetReferencedFrameNumber(referencedFrameNumber);
					coord.SetCoordinateIndex(listIdx - 1); // zero-base index
					spatialCoords.push_back(coord.Clone());
				}
			}

			// Sort coordinates according to their CoordianteIndex
			std::sort(spatialCoords.begin(), spatialCoords.end(), SpatialCoordinate::SpatialCoordinateSortPredicate);

			pGeoShape->SetSpatialCoordinateCollection(spatialCoords);
			// Clean up
			while(spatialCoords.size() > 0)
			{
				delete spatialCoords[spatialCoords.size() - 1];
				spatialCoords.pop_back();
			}
		}
	}

	return pGeoShape;
}

GeometricShape* DcmModelInternal::Read3dScoord()
{
	GeometricShape* pGeoShape = NULL;

	// Not implemented - no DICOM 3D coordinates yet
	assert(false);

	return NULL;
}

TextAnnotation DcmModelInternal::ReadTextAnnotationContainer()
{
	assert(this->GetConceptName().getCodeValue() == "zzz028");

	TextAnnotation textAnnotation;

	if (_pDoc->getTree().goDown())
	{
		do
		{
			ofString = GetConceptName().getCodeValue();
			if (ofString == "G-D315")
			{
				// Text
				textAnnotation.SetText(GetStringValue());
			}
			else if(ofString == "zzz022")
			{
				// GeoShape - Multipoint
				std::auto_ptr<GeometricShape> pGeoShape(this->ReadGeoShape());
				if(pGeoShape.get() != NULL)
				{
					assert(pGeoShape->GetShapeType() == GeometricShape::SHT_Multipoint &&
						pGeoShape->GetSpatialCoordinateCollection().size() > 0 &&
						pGeoShape->GetSpatialCoordinateCollection().size() <= 2);

					if(pGeoShape->GetShapeType() == GeometricShape::SHT_Multipoint)
					{
						textAnnotation.SetConnectorPoints((MultiPoint*)pGeoShape.get());
					}
					else
						assert(false); // unexpected shape type - we need multipoint with two points here
				}
			}
			else
				assert(false); // unexpected
		}
		while(_pDoc->getTree().gotoNext() > 0);

		nodeId = _pDoc->getTree().goUp();
	}

	return textAnnotation;
}

// Returns Study->Series->Image heirarchy from the given DSRImageReferenceValue
ImageStudy DcmModelInternal::ReadStudyFromImageRefValue(const DSRImageReferenceValue& imgReference, PresentationStateVector& presentationStates)
{
	assert(imgReference.isValid());

	Image image;
	ImageSeries series;
	ImageStudy study;
	image.SetSopClassUID(imgReference.getSOPClassUID().c_str());
	image.SetSopInstanceUID(imgReference.getSOPInstanceUID().c_str());

	// Read Study Instance UID and Series Instance UID
	if (_pDoc->getTree().goDown() > 0)
	{
		do
		{
			ofString = GetConceptName().getCodeValue();
			if (ofString =="zzz025") // Web Image URI
			{
				assert(false); // this should never happen - we're reading DICOMImageReference
				_stdString = GetStringValue();
			}
			else if (ofString == "110180") // Study Instance UID
			{
				_stdString = GetStringValue();
				study.SetInstanceUID(_stdString);
			}
			else if (ofString =="111060") // Start Date
			{
				_stdString = this->GetStringValue();
				OFDate ofDate;
				ofString.assign(_stdString.c_str());
				if (ofDate.setISOFormattedDate(ofString))
				{
					Date date = AIMUtil::DateConvert(ofDate);
					study.SetStartDate(date);
				}
			}
			else if (ofString =="111061") // Start Time
			{
				_stdString = this->GetStringValue();
				OFTime ofTime;
				ofString.assign(_stdString.c_str());
				if (ofTime.setISOFormattedTime(ofString))
				{
					Time winTime = AIMUtil::TimeConvert(ofTime);
					study.SetStartTime(winTime);
				}
			}
			else if (ofString == "112002") // Series Instance UID
			{
				_stdString = GetStringValue();
				series.SetInstanceUID(_stdString);
			}
			else if (ofString == "zzz069") // Presentation State Instance UID
			{
				PresentationState ps;
				ps.SetSopInstanceUID(GetStringValue());
				presentationStates.push_back(ps);
			}
			else
			{
				assert(false); // unknown image tag
			}
		}
		while(_pDoc->getTree().gotoNext() > 0);

		nodeId = _pDoc->getTree().goUp();
	}
	else
	{
		assert(false); // Image Library is empty
	}

	ImageVector imgColl;

	imgColl.push_back(image);
	series.SetImageCollection(imgColl);
	study.SetSeries(series);

	return study;
}

void DcmModelInternal::ReadAnnotationOfAnnotationContainer(AnnotationOfAnnotation& annAnnotation)
{
	assert(this->GetConceptName().getCodeValue() == "zzz031");

	if (_pDoc->getTree().goDown() > 0)
	{
		ReferencedAnnotationVector referencedAnnotations;
		do
		{
			ofString = this->GetConceptName().getCodeValue();
			if (ofString == "zzz062")
			{
				if (_pDoc->getTree().goDown() > 0)
				{
					// Referenced Annotation
					ReferencedAnnotation referencedAnnotation;
					do
					{
						ofString = this->GetConceptName().getCodeValue();
						if (ofString == "112040")
						{
							// Referenced Annotation UID
							referencedAnnotation.SetReferencedAnnotationUID(this->GetStringValue());
						}
						else if (ofString == "zzz056")
						{
							// Annotation Role
							AnnotationRole annotationRole;
							assert(referencedAnnotation.GetAnnotationRole() == NULL); // there should be only one role

							_dsrCode = GetCode();
							annotationRole.SetCodeValue(_dsrCode.getCodeValue().c_str());
							annotationRole.SetCodeMeaning(_dsrCode.getCodeMeaning().c_str());
							annotationRole.SetCodingSchemeDesignator(_dsrCode.getCodingSchemeDesignator().c_str());
							annotationRole.SetCodingSchemeVersion(_dsrCode.getCodingSchemeVersion().c_str());

							if (_pDoc->getTree().goDown() > 0)
							{
								// Role Sequence Number
								assert(this->GetConceptName().getCodeValue() == "zzz057");
								annotationRole.SetRoleSequenceNumber(AIMUtil::StringToInt(GetNumericValue().getNumericValue().c_str()));

								nodeId = _pDoc->getTree().goUp();
							}
							else
								assert(false); // missing Role Sequence number

							referencedAnnotation.SetAnnotationRole(&annotationRole);
						}
						else
							assert(false); // unknown content node
					}
					while(_pDoc->getTree().gotoNext() > 0);

					referencedAnnotations.push_back(referencedAnnotation);

					nodeId = _pDoc->getTree().goUp();
				}
				else
					assert(false); // empty Referenced Annotation
			}
			else
				assert(false); // Unknow element in the annotaiton of annotation
		}
		while(_pDoc->getTree().gotoNext() > 0);

		if (referencedAnnotations.size() > 0)
			annAnnotation.SetReferencedAnnotationCollection(referencedAnnotations);

		nodeId = _pDoc->getTree().goUp();
	}
	else
		assert(false); // missing content of Annotation of Annotaitons
}
