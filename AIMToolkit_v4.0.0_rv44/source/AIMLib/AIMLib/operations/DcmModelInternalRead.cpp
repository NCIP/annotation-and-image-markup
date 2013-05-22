/*L
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
#include "../statement/StatementFactory.h"

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

OFCondition DcmModelInternal::ReadDocFromFile(AnnotationCollection** ppAnnotationCollection, const std::string& fileName)
{
	assert(ppAnnotationCollection != NULL);
	if (!ppAnnotationCollection)
	{
		printDebug(std::string(__FILE__).append(": Output AnnotationCollection parameter cannot be NULL").c_str());
		return EC_IllegalParameter;
	}

	assert(fileName.length() > 0);
	if (fileName.length() < 1)
	{
		std::string err = std::string("DICOM SR input file name cannot be empty");
		printDebug(std::string(__FILE__).append(": ").append(err).c_str());
		return makeOFCondition(OFM_aimlib, 100, OF_error, err.c_str());
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

			openCondition = LoadAnnotationsFromDSRDocument(ppAnnotationCollection);
		}
		else
		{
			std::string err = std::string("Failed to load SR from file <").append(fileName).append(">");
			printDebug(std::string(__FILE__).append(": ").append(err).data());
			openCondition = makeOFCondition(OFM_aimlib, 100, OF_error, err.data());
		}
	}

	return makeOFCondition(OFM_aimlib, 100, OF_ok, "");
}

OFCondition DcmModelInternal::LoadAnnotationsFromDSRDocument(AnnotationCollection** ppAnnotationCollection)
{
	if (*ppAnnotationCollection)
	{
		(*ppAnnotationCollection)->ClearAnnotations();
	}

	// make sure that the doc is valid and SR container is present
	assert(_pDoc->isValid());
	if (!_pDoc->isValid())
	{
		return makeOFCondition(OFM_aimlib, 101, OF_error, "Provided SR document is not valid");
	}
	_dsrCode = DSR_AIM_CDE("zzz001", "AIM SR Report");
	size_t srRootNodeId = GO_TO_NAMED_NODE1(_dsrCode);
	assert(srRootNodeId > 0);
	if (srRootNodeId < 1)
	{
		return makeOFCondition(OFM_aimlib, 102, OF_error, "No SR container is found in the provided document");
	}

	// Read SR container
	if (GO_TO_NAMED_NODE1(DSR_AIM_CDE("zzz070", "AIM Annotation Entity")) > 0/* && _pDoc->getTree().goDown() > 0*/)
	{
		// NOTE: Reading annotation is based on the fact that SR Tree 
		// has unique _ordered_ nodeId for each node in the tree.
		// This allows us to assume that all nodes which satisfy
		// (annotationNodeId < nodeId < nextAnnotationNodeId) 
		// belong to the current annotation.

		// Locate Annotation Entity nodes
		std::vector<size_t> annotationEntityIds; // Node IDs of all annotation entities in the SR
		std::vector<std::string> annotationEntityPositions; // Positions of the Annotation Entity nodes in the SR
		do
		{
			assert(this->GetConceptName().isValid() && this->GetConceptName().getCodeValue() == "zzz070");
			annotationEntityIds.push_back(_pDoc->getTree().getNodeID()); // Node ID
			annotationEntityPositions.push_back(_pDoc->getTree().getPosition(_stdString)); // Node Position
		}
		while (_pDoc->getTree().gotoNextNamedNode(_dsrCode, false) > 0);

		// Figure out annotation collection type
		AnnotationEntity::AnnotationType aeType = AnnotationEntity::AT_Unknown;
		for(std::vector<size_t>::size_type i = 0; i < annotationEntityIds.size(); i++)
		{
			size_t nextAnnotationId = i+1 < annotationEntityIds.size() ? annotationEntityIds[i+1] : 0; // 0 means that this is the last annotation
			AnnotationEntity::AnnotationType aet = FindAnnotationType(annotationEntityIds[i], nextAnnotationId);
			if (aet == AnnotationEntity::AT_Unknown)
				return makeOFCondition(OFM_aimlib, 103, OF_error, "Encountered unknown Annotation Entity type in the document.");

			if (aeType != AnnotationEntity::AT_Unknown && aeType != aet)
				return makeOFCondition(OFM_aimlib, 104, OF_error, "Annotation Entity Types in the document do not match");

			aeType = aet;
		}
		if (aeType == AnnotationEntity::AT_Unknown)
				return makeOFCondition(OFM_aimlib, 105, OF_error, "Annotation Entity Types in the document are unknown");
		// Ensure that we have a valid Annotation Collection
		if (*ppAnnotationCollection)
		{
			// Validate collection type of the given collection
			switch((*ppAnnotationCollection)->GetAnnotationCollectionType())
			{
			case AnnotationCollection::ACT_ImageAnnotationCollection:
				if (aeType != AnnotationEntity::AT_ImageAnnotation)
					return makeOFCondition(OFM_aimlib, 106, OF_error, "Annotation Collection Type missmatch: given ACT_ImageAnnotationCollection collection but Annotation Entities are not of type AT_ImageAnnotation in the document");
				break;
			case AnnotationCollection::ACT_AnnotationOfAnnotationCollection:
				if (aeType != AnnotationEntity::AT_AnnotationOfAnnotation)
					return makeOFCondition(OFM_aimlib, 107, OF_error, "Annotation Collection Type missmatch: given ACT_AnnotationOfAnnotationCollection collection but Annotation Entities are not of type AT_AnnotationOfAnnotation in the document");
				break;
			default:
				assert(false);
			}
		}
		else
		{
			// Create Annotation Collection of the required type
			switch(aeType)
			{
			case AnnotationEntity::AT_ImageAnnotation:
				*ppAnnotationCollection = new ImageAnnotationCollection();
				break;
			case AnnotationEntity::AT_AnnotationOfAnnotation:
				*ppAnnotationCollection = new AnnotationOfAnnotationCollection();
				break;
			default:
				assert(false);
			}
		}

		///////////////////////////////////////////////////////////////////////
		// Read AIM Document Root
		///////////////////////////////////////////////////////////////////////
		MapAnnotationUidToImageReferences annotationToImageReferenceCollectionMap; // stores Image References for each annotation; keyed off Annotation UID
		nodeId = _pDoc->getTree().gotoNamedNode(DSR_AIM_CDE("zzz001", "AIM SR Report"));
		assert(nodeId == srRootNodeId);

		// IMPORTANT: From this point on, the code assumes that all nodes are read in order.

		// AIM DateTime
		ofString = _pDoc->getTree().getCurrentContentItem().getObservationDateTime();
		if (!ofString.empty())
		{
			OFDateTime ofDateTime;
			if (ofDateTime.setISOFormattedDateTime(ofString))
			{
				DateTime dateTime = AIMUtil::DateTimeConvert(ofDateTime);
				(*ppAnnotationCollection)->SetDateTime(dateTime);
			}
		}

		if (_pDoc->getTree().goDown())
		{
			do
			{
				ofString = this->GetConceptName().getCodeValue();
				if (ofString == "112040") // Annotation Collection UID
				{
					(*ppAnnotationCollection)->SetUniqueIdentifier(GetStringValue());
				}
				else if(ofString == "zzz003") // AIM Version
				{
					_stdString = GetStringValue();
					assert(AimEnum::GetAimVersionString((*ppAnnotationCollection)->GetAimVersion()) == _stdString); // default should match
				}
				else if (ofString == "C25365") // Description
				{
					(*ppAnnotationCollection)->SetDescription(GetStringValue());
				}
				else if (ofString == "121005") // User
				{
					_dsrCode = GetCode();
					if (_dsrCode.isValid() && _dsrCode.getCodeValue() == "121006" && 
						_pDoc->getTree().goDown() > 0) // if non-empty Person
					{
						User user = this->ReadUser();
						(*ppAnnotationCollection)->SetUser(&user);
						nodeId = _pDoc->getTree().goUp(); // step out of the User node
					}
				}
				else if (ofString == "111028") // Image Library
				{
					assert(annotationToImageReferenceCollectionMap.empty()); // there is only one image library in the AIM SR doc
					ReadImageLibrary(annotationToImageReferenceCollectionMap);
				}
				else if (ofString == "zzz070") // Annotation Entity
				{
					// NO-OP
					// Annotation Entity is read outside of the loop to make sure every node above is read prior to reading Annotation Entities
				}
				else
					assert(false); // unknown image template tag
			}
			while(_pDoc->getTree().gotoNext());
		}
		else
			assert(false); // cannot step into AIM SR container node

		// Save position for later
		//std::string curPosition = _pDoc->getTree().getPosition(_stdString);

		// Read Annotation Entities
		for (std::vector<std::string>::iterator iter = annotationEntityPositions.begin(); iter < annotationEntityPositions.end(); iter ++)
		{
			// Go to the current AnnotationEntity node
			nodeId = _pDoc->getTree().gotoNode(*iter);

			AnnotationEntity* pAnnEntity = ReadAnnotationEntity(aeType);

			if (pAnnEntity)
			{
				switch(pAnnEntity->GetAnnotationType())
				{
				case AnnotationEntity::AT_ImageAnnotation:
					{
						ImageAnnotation* pImgAnnotation = dynamic_cast<ImageAnnotation*>(pAnnEntity);
						if (pImgAnnotation)
						{
							// Current annotation has to have at least one Image Reference Entity stored in the Image Library
							assert(!annotationToImageReferenceCollectionMap.empty()); // Image Library has to be read already
							assert(annotationToImageReferenceCollectionMap.find(pImgAnnotation->GetUniqueIdentifier().toString()) != annotationToImageReferenceCollectionMap.end());
							ImageReferenceEntityPtrVector imgRefEntities = annotationToImageReferenceCollectionMap[pImgAnnotation->GetUniqueIdentifier().toString()];
							pImgAnnotation->SetImageReferenceEntityCollection(imgRefEntities);

							ImageAnnotationCollection* pImgAnnotationColl = dynamic_cast<ImageAnnotationCollection*>(*ppAnnotationCollection);
							assert(pImgAnnotationColl);
							if (pImgAnnotationColl)
							{
								// Store Annotation into collection
								ImageAnnotationVector imgAnnotations = pImgAnnotationColl->GetImageAnnotations();
								imgAnnotations.push_back(*pImgAnnotation);
								pImgAnnotationColl->SetImageAnnotations(imgAnnotations);

								Person person = ReadPerson(); // Person
								if (person.GetId().length() > 0 && person.GetName().length() > 0) // if Person is valid
									pImgAnnotationColl->SetPerson(&person);
							}
						}
						else
							assert(false); // somehow this is not an image annontation
						break;
					}
				case AnnotationEntity::AT_AnnotationOfAnnotation:
					{
						AnnotationOfAnnotation* pAnnOfAnn = dynamic_cast<AnnotationOfAnnotation*>(pAnnEntity);
						if (pAnnOfAnn)
						{
							AnnotationOfAnnotationCollection* pAnnOfAnnColl = dynamic_cast<AnnotationOfAnnotationCollection*>(*ppAnnotationCollection);
							assert(pAnnOfAnnColl);
							if (pAnnOfAnnColl)
							{
								// Store Annotation into collection
								AnnotationOfAnnotationVector annOfAnnotations = pAnnOfAnnColl->GetAnnotationOfAnnotations();
								annOfAnnotations.push_back(*pAnnOfAnn);
								pAnnOfAnnColl->SetAnnotationOfAnnotations(annOfAnnotations);
							}
						}
						else
							assert(false); // somehow this is not an annotation of annotation
						break;
					}
				case AnnotationEntity::AT_Unknown:
					assert(false); // unknown annotation type
					break;
				}
			}

			delete pAnnEntity;
		}

		nodeId = _pDoc->getTree().goUp(); // step out of the SR container

		// Return back to the last node we processed
		//nodeId = _pDoc->getTree().gotoNode(curPosition);

		// Free Image Reference Entities
		for (MapAnnotationUidToImageReferences::iterator iter = annotationToImageReferenceCollectionMap.begin(); iter != annotationToImageReferenceCollectionMap.end(); iter++)
		{
			while(iter->second.size() > 0)
			{
				delete iter->second[iter->second.size() - 1];
				iter->second.pop_back();
			}
		}
		annotationToImageReferenceCollectionMap.clear();

		// Equipment
		Equipment equipment = ReadEquipment();
		if (equipment.GetManufacturerName().length() > 0) // if Equipment is valid
			(*ppAnnotationCollection)->SetEquipment(&equipment);
	}
	else
	{
		return makeOFCondition(OFM_aimlib, 103, OF_error, "No Annotations are found in the document");
	}

	return makeOFCondition(OFM_aimlib, 1, OF_ok, "");
}

// Searches for annotation type information for the given AnnotationEntity
// Search is based on the fact that the information we're after should have nodeId such as: annotationId < nodeId < nextAnnotationId
// When nextAnnotationId is 0, any nodeId after the annotationId is valid (i.e. search till the end of the document)
AnnotationEntity::AnnotationType DcmModelInternal::FindAnnotationType(size_t annotationNodeId, size_t nextAnnotationNodeId)
{
	assert(annotationNodeId < nextAnnotationNodeId || nextAnnotationNodeId == 0);

	size_t curNodeId = _pDoc->getTree().gotoNode(annotationNodeId);
	curNodeId = _pDoc->getTree().gotoNextNamedNode(DSR_AIM_CDE("zzz030", "Image Annotation"));
	if (curNodeId > 0 && (nextAnnotationNodeId == 0 || curNodeId < nextAnnotationNodeId))
		return AnnotationEntity::AT_ImageAnnotation;

	curNodeId = _pDoc->getTree().gotoNode(annotationNodeId);
	curNodeId = _pDoc->getTree().gotoNextNamedNode(DSR_AIM_CDE("zzz031", "Annotation of Annotation"));
	if (curNodeId > 0 && (nextAnnotationNodeId == 0 || curNodeId < nextAnnotationNodeId))
		return AnnotationEntity::AT_AnnotationOfAnnotation;

	return AnnotationEntity::AT_Unknown;
}

void DcmModelInternal::ReadImageLibrary(MapAnnotationUidToImageReferences& annotationToImageEntitiesMap)
{
	assert(this->GetConceptName().getCodeValue() == "111028"); // we're at the Image Library node

	size_t imgLibraryEntryNodeId = _pDoc->getTree().goDown();
	if (imgLibraryEntryNodeId < 1)
		return; // image library is empty

	assert(this->GetConceptName().getCodeValue() == "zzz034"); // we're at the Image Library Entry node

	while(imgLibraryEntryNodeId > 0)
	{
		std::string annotationUid;
		switch(_pDoc->getTree().getCurrentContentItem().getValueType())
		{
		case DSRTypes::VT_Image:
			// DICOM Referenced Entity
			{
				// 1. Read new DicomImageReferenceEntity from the doc
				DicomImageReferenceEntity dicomImgRefEntity;
				ReadDicomImageReferenceEntity(dicomImgRefEntity, annotationUid);

				// 2. Store returned values
				assert(!annotationUid.empty());
				assert(dicomImgRefEntity.GetUniqueIdentifier() != iso_21090::II());
				ImageReferenceEntityPtrVector imageReferences = annotationToImageEntitiesMap[annotationUid];
				bool isStored = false;
				for (ImageReferenceEntityPtrVector::iterator iter = imageReferences.begin(); iter != imageReferences.end(); iter++)
				{
					// If current DICOM Image Reference already exists, store newly read Image into the existing Image Collection
					if (*iter && (*iter)->GetUniqueIdentifier() == dicomImgRefEntity.GetUniqueIdentifier())
					{
						assert((*iter)->GetImageReferenceEntityType() == ImageReferenceEntity::T_DICOM_IMAGE_REF); // we better have the right type of image reference
						DicomImageReferenceEntity* pStoredDicomImgRef = dynamic_cast<DicomImageReferenceEntity*>(*iter);
						if (pStoredDicomImgRef)
						{
							assert(pStoredDicomImgRef->GetImageStudy().GetInstanceUid() == dicomImgRefEntity.GetImageStudy().GetInstanceUid());

							ImageStudy imageStudy = pStoredDicomImgRef->GetImageStudy();
							ImageSeries imageSeries = imageStudy.GetImageSeries();
							ImageVector images = imageSeries.GetImageCollection();
							// TODO - verify uniqueness ?
							images.insert(images.end(), dicomImgRefEntity.GetImageStudy().GetImageSeries().GetImageCollection().begin(), dicomImgRefEntity.GetImageStudy().GetImageSeries().GetImageCollection().end());
							imageSeries.SetImageCollection(images);
							imageStudy.SetImageSeries(imageSeries);
							pStoredDicomImgRef->SetImageStudy(imageStudy);
							isStored = true;
							break;
						}
						else
							assert(false); // should not be here
					}
				}
				if (!isStored)
				{
					// This must be a new DICOM Image Reference Entity
					imageReferences.push_back(dicomImgRefEntity.Clone());
				}
				// Store back all images references for the annotation
				annotationToImageEntitiesMap[annotationUid] = imageReferences;
			}
			break;
		case DSRTypes::VT_Container:
			// Referenced DICOM Object or URI Image Reference (both are in a container)
			{
				size_t curNodeId = imgLibraryEntryNodeId;
				
				if (_pDoc->getTree().goDown() > 0)
				{
					// 1. Figure out which object we are reading now: ReferencedDicomObject or UriImageReferenceEntity
					bool isReferencedDicomObject = false;
					bool isUriImageRef = false;

					do
					{
						ofString = this->GetConceptName().getCodeValue();
						if (ofString == "110180") // Study Instance UID
						{
							isReferencedDicomObject = true;
							break;
						}
						if (ofString == "zzz148") // URI
						{
							isUriImageRef = true;
							break;
						}
					} while (_pDoc->getTree().gotoNext() > 0);

					assert(isReferencedDicomObject || isUriImageRef); // Entity Type should be known by now
					nodeId = _pDoc->getTree().goUp();
					assert(curNodeId == nodeId);

					if (isReferencedDicomObject)
					{
						// 2. Read new DicomImageReferenceEntity with ReferencedDicomObject from the doc
						DicomImageReferenceEntity dicomImgRefEntity;
						ReadReferencedDicomObject(dicomImgRefEntity, annotationUid);

						// 3. Store returned values
						assert(!annotationUid.empty());
						assert(dicomImgRefEntity.GetUniqueIdentifier() != iso_21090::II());
						ImageReferenceEntityPtrVector imageReferences = annotationToImageEntitiesMap[annotationUid];
						bool isStored = false;
						for (ImageReferenceEntityPtrVector::iterator iter = imageReferences.begin(); iter != imageReferences.end(); iter++)
						{
							// If current DICOM Image Reference already exists, store newly read ReferencedDicomObject into the existing ReferencedDicomObject Collection
							if (*iter && (*iter)->GetUniqueIdentifier() == dicomImgRefEntity.GetUniqueIdentifier())
							{
								assert((*iter)->GetImageReferenceEntityType() == ImageReferenceEntity::T_DICOM_IMAGE_REF); // we better have the right type of image reference
								DicomImageReferenceEntity* pStoredDicomImgRef = dynamic_cast<DicomImageReferenceEntity*>(*iter);
								if (pStoredDicomImgRef)
								{
									assert(pStoredDicomImgRef->GetImageStudy().GetInstanceUid() == dicomImgRefEntity.GetImageStudy().GetInstanceUid());
									// TODO - verify uniqueness ?
									ImageStudy imageStudy = pStoredDicomImgRef->GetImageStudy();
									ReferencedDicomObjectVector refDicomObjects = imageStudy.GetReferencedDicomObjectCollection();
									refDicomObjects.insert(refDicomObjects.end(), dicomImgRefEntity.GetImageStudy().GetReferencedDicomObjectCollection().begin(), dicomImgRefEntity.GetImageStudy().GetReferencedDicomObjectCollection().end());
									imageStudy.SetReferencedDicomObjectCollection(refDicomObjects);
									pStoredDicomImgRef->SetImageStudy(imageStudy);
									isStored = true;
									break;
								}
								else
									assert(false); // should not be here
							}
						}
						if (!isStored)
						{
							// This must be a new DICOM Image Reference Entity
							imageReferences.push_back(dicomImgRefEntity.Clone());
						}
						// Store back all images references for the annotation
						annotationToImageEntitiesMap[annotationUid] = imageReferences;
					}
					else if (isUriImageRef)
					{
						// 2. Read new UriImageReferenceEntity from the doc
						UriImageReferenceEntity uriImgRefEntity;
						ReadUriImageReferenceEntity(uriImgRefEntity, annotationUid);

						// 3. Store returned values
						assert(!annotationUid.empty());
						assert(uriImgRefEntity.GetUniqueIdentifier() != iso_21090::II());
						ImageReferenceEntityPtrVector imageReferences = annotationToImageEntitiesMap[annotationUid];
						bool isStored = false;
						for (ImageReferenceEntityPtrVector::iterator iter = imageReferences.begin(); iter != imageReferences.end(); iter++)
						{
							// If current URI Image Reference already exists, ignore it
							if (*iter && (*iter)->GetUniqueIdentifier() == uriImgRefEntity.GetUniqueIdentifier())
							{
								assert((*iter)->GetImageReferenceEntityType() == ImageReferenceEntity::T_URI_IMAGE_REF); // we better have the right type of image reference
								isStored = true;
								break;
							}
						}
						if (!isStored)
						{
							// This must be a new URI Image Reference Entity
							imageReferences.push_back(uriImgRefEntity.Clone());
						}
						// Store back all images references for the annotation
						annotationToImageEntitiesMap[annotationUid] = imageReferences;
					}
					else
						assert(false); // failed to recognize the node content
				}
				else
					assert(false); // empty container - this should not happen
			}
			break;
		default:
			assert(false); // unexpected Value Type for this node
		}

		imgLibraryEntryNodeId = _pDoc->getTree().gotoNext();
	}

	nodeId = _pDoc->getTree().goUp();
}

// Returns populated DicomImageReferenceEntity and annotation UID that entity belongs to
void DcmModelInternal::ReadDicomImageReferenceEntity(DicomImageReferenceEntity& dicomImgRefEntity, std::string& annotationUid)
{
	assert(_pDoc->getTree().getCurrentContentItem().getValueType() == DSRTypes::VT_Image);

	ImageStudy imageStudy;
	ImageSeries imageSeries;
	Image image;

	DSRImageReferenceValue imgRefValue = GetImageReference();
	image.SetSopClassUid(imgRefValue.getSOPClassUID());
	image.SetSopInstanceUid(imgRefValue.getSOPInstanceUID());

	size_t imgLibNodeId = _pDoc->getTree().goDown();
	if (imgLibNodeId > 0)
	{
		do
		{
			ofString = this->GetConceptName().getCodeValue();
			if (ofString == "112040") // Image Reference Entity UID
			{
				dicomImgRefEntity.SetUniqueIdentifier(this->GetStringValue());
			}
			else if (ofString == "zzz152") // Annotation UID
			{
				annotationUid = this->GetStringValue();
			}
			else if (ofString == "110180") // Study Instance UID
			{
				imageStudy.SetInstanceUid(this->GetStringValue());
			}
			else if (ofString == "111060") // Study Start Date
			{
				_stdString = this->GetStringValue();
				OFDate ofDate;
				if (ofDate.setISOFormattedDate(_stdString))
				{
					Date date = AIMUtil::DateConvert(ofDate);
					imageStudy.SetStartDate(date);
				}
			}
			else if (ofString == "111061") // Study Start Time
			{
				_stdString = this->GetStringValue();
				OFTime ofTime;
				if (ofTime.setISOFormattedTime(_stdString))
				{
					Time time = AIMUtil::TimeConvert(ofTime);
					imageStudy.SetStartTime(time);
				}
			}
			else if (ofString == "121065") // Procedure Description
			{
				imageStudy.SetProcedureDescription(this->GetStringValue());
			}
			else if (ofString == "112002") // Series Instance UID
			{
				imageSeries.SetInstanceUid(this->GetStringValue());
			}
			else if (ofString == "121139") // Modality
			{
				imageSeries.SetModality(this->GetIsoCode());
			}
			else if (ofString == "111044") // Patient Orientation Row
			{
				GeneralImage generalImage;
				if (image.GetGeneralImage())
					generalImage = *image.GetGeneralImage();
				generalImage.SetPatientOrientationRow(this->GetStringValue());
				image.SetGeneralImage(&generalImage);
			}
			else if (ofString == "111043") // Patient Orientation Column
			{
				GeneralImage generalImage;
				if (image.GetGeneralImage())
					generalImage = *image.GetGeneralImage();
				generalImage.SetPatientOrientationColumn(this->GetStringValue());
				image.SetGeneralImage(&generalImage);
			}
			else if (ofString == "zzz142") // Image Orientation Row X
			{
				ImagePlane imagePlane;
				if (image.GetImagePlane())
					imagePlane = *image.GetImagePlane();
				double value = AIMUtil::StringToDouble(this->GetNumericValueString());
				imagePlane.SetRowImageOrientationX(&value);
				image.SetImagePlane(&imagePlane);
			}
			else if (ofString == "zzz143") // Image Orientation Row Y
			{
				ImagePlane imagePlane;
				if (image.GetImagePlane())
					imagePlane = *image.GetImagePlane();
				double value = AIMUtil::StringToDouble(this->GetNumericValueString());
				imagePlane.SetRowImageOrientationY(&value);
				image.SetImagePlane(&imagePlane);
			}
			else if (ofString == "zzz144") // Image Orientation Row Z
			{
				ImagePlane imagePlane;
				if (image.GetImagePlane())
					imagePlane = *image.GetImagePlane();
				double value = AIMUtil::StringToDouble(this->GetNumericValueString());
				imagePlane.SetRowImageOrientationZ(&value);
				image.SetImagePlane(&imagePlane);
			}
			else if (ofString == "zzz145") // Image Orientation Column X
			{
				ImagePlane imagePlane;
				if (image.GetImagePlane())
					imagePlane = *image.GetImagePlane();
				double value = AIMUtil::StringToDouble(this->GetNumericValueString());
				imagePlane.SetColumnImageOrientationX(&value);
				image.SetImagePlane(&imagePlane);
			}
			else if (ofString == "zzz146") // Image Orientation Column Y
			{
				ImagePlane imagePlane;
				if (image.GetImagePlane())
					imagePlane = *image.GetImagePlane();
				double value = AIMUtil::StringToDouble(this->GetNumericValueString());
				imagePlane.SetColumnImageOrientationY(&value);
				image.SetImagePlane(&imagePlane);
			}
			else if (ofString == "zzz147") // Image Orientation Column Z
			{
				ImagePlane imagePlane;
				if (image.GetImagePlane())
					imagePlane = *image.GetImagePlane();
				double value = AIMUtil::StringToDouble(this->GetNumericValueString());
				imagePlane.SetColumnImageOrientationZ(&value);
				image.SetImagePlane(&imagePlane);
			}
			else if (ofString == "112225") // Slice Thickness
			{
				ImagePlane imagePlane;
				if (image.GetImagePlane())
					imagePlane = *image.GetImagePlane();
				double value = AIMUtil::StringToDouble(this->GetNumericValueString());
				imagePlane.SetSliceThickness(&value);
				image.SetImagePlane(&imagePlane);
			}
			else if (ofString == "111026") // Horizontal Pixel Spacing
			{
				ImagePlane imagePlane;
				if (image.GetImagePlane())
					imagePlane = *image.GetImagePlane();
				double value = AIMUtil::StringToDouble(this->GetNumericValueString());
				imagePlane.SetHorizontalPixelSpacing(&value);
				image.SetImagePlane(&imagePlane);
			}
			else if (ofString == "111066") // Vertical Pixel Spacing
			{
				ImagePlane imagePlane;
				if (image.GetImagePlane())
					imagePlane = *image.GetImagePlane();
				double value = AIMUtil::StringToDouble(this->GetNumericValueString());
				imagePlane.SetVerticalPixelSpacing(&value);
				image.SetImagePlane(&imagePlane);
			}
			else if (ofString == "zzz139") // Image Position X
			{
				ImagePlane imagePlane;
				if (image.GetImagePlane())
					imagePlane = *image.GetImagePlane();
				double value = AIMUtil::StringToDouble(this->GetNumericValueString());
				imagePlane.SetImagePositionX(&value);
				image.SetImagePlane(&imagePlane);
			}
			else if (ofString == "zzz140") // Image Position Y
			{
				ImagePlane imagePlane;
				if (image.GetImagePlane())
					imagePlane = *image.GetImagePlane();
				double value = AIMUtil::StringToDouble(this->GetNumericValueString());
				imagePlane.SetImagePositionY(&value);
				image.SetImagePlane(&imagePlane);
			}
			else if (ofString == "zzz141") // Image Position Z
			{
				ImagePlane imagePlane;
				if (image.GetImagePlane())
					imagePlane = *image.GetImagePlane();
				double value = AIMUtil::StringToDouble(this->GetNumericValueString());
				imagePlane.SetImagePositionZ(&value);
				image.SetImagePlane(&imagePlane);
			}

			imgLibNodeId = _pDoc->getTree().gotoNext();
		}
		while(imgLibNodeId > 0);

		ImageVector images;
		images.push_back(image);
		imageSeries.SetImageCollection(images);
		imageStudy.SetImageSeries(imageSeries);
		dicomImgRefEntity.SetImageStudy(imageStudy);

		nodeId = _pDoc->getTree().goUp();
	}
	else
		assert(false); // failed to read entity values
}

// Returns DicomImageReferenceEntity populated with ReferencedDicomObject and annotation UID the entity belongs to
void DcmModelInternal::ReadReferencedDicomObject(DicomImageReferenceEntity& dicomImgRefEntity, std::string& annotationUid)
{
	assert(_pDoc->getTree().getCurrentContentItem().getValueType() == DSRTypes::VT_Container);

	ImageStudy imageStudy;
	ReferencedDicomObject refDicomObject;

	size_t imgLibNodeId = _pDoc->getTree().goDown();
	if (imgLibNodeId > 0)
	{
		do
		{
			ofString = this->GetConceptName().getCodeValue();
			if (ofString == "112040") // Image Reference Entity UID
			{
				dicomImgRefEntity.SetUniqueIdentifier(this->GetStringValue());
			}
			else if (ofString == "zzz152") // Annotation UID
			{
				annotationUid = this->GetStringValue();
			}
			else if (ofString == "110180") // Study Instance UID
			{
				imageStudy.SetInstanceUid(this->GetStringValue());
			}
			else if (ofString == "111060") // Study Start Date
			{
				_stdString = this->GetStringValue();
				OFDate ofDate;
				if (ofDate.setISOFormattedDate(_stdString))
				{
					Date date = AIMUtil::DateConvert(ofDate);
					imageStudy.SetStartDate(date);
				}
			}
			else if (ofString == "111061") // Study Start Time
			{
				_stdString = this->GetStringValue();
				OFTime ofTime;
				if (ofTime.setISOFormattedTime(_stdString))
				{
					Time time = AIMUtil::TimeConvert(ofTime);
					imageStudy.SetStartTime(time);
				}
			}
			else if (ofString == "121065") // Procedure Description
			{
				imageStudy.SetProcedureDescription(this->GetStringValue());
			}
			else if (ofString == "121139") // Modality
			{
				refDicomObject.SetModality(this->GetIsoCode());
			}
			else if (ofString == "zzz138") // Referenced DICOM Object UID
			{
				refDicomObject.SetSopInstanceUid(this->GetStringValue());
			}
			else
				assert(false); // unexpected doc node

			imgLibNodeId = _pDoc->getTree().gotoNext();
		}
		while(imgLibNodeId > 0);

		ReferencedDicomObjectVector refDicomObjects;
		refDicomObjects.push_back(refDicomObject);
		imageStudy.SetReferencedDicomObjectCollection(refDicomObjects);
		dicomImgRefEntity.SetImageStudy(imageStudy);

		nodeId = _pDoc->getTree().goUp();
	}
	else
		assert(false); // failed to read entity values
}

// Returns populated UrilImageReferenceEntity and annotation UID the entity belongs to
void DcmModelInternal::ReadUriImageReferenceEntity(UriImageReferenceEntity& uriImgRefEntity, std::string& annotationUid)
{
	assert(_pDoc->getTree().getCurrentContentItem().getValueType() == DSRTypes::VT_Container);

	size_t imgLibNodeId = _pDoc->getTree().goDown();
	if (imgLibNodeId > 0)
	{
		do
		{
			ofString = this->GetConceptName().getCodeValue();
			if (ofString == "112040") // Image Reference Entity UID
			{
				uriImgRefEntity.SetUniqueIdentifier(this->GetStringValue());
			}
			else if (ofString == "zzz152") // Annotation UID
			{
				annotationUid = this->GetStringValue();
			}
			else if (ofString == "zzz148") // URI
			{
				uriImgRefEntity.SetUri(this->GetStringValue());
			}
			else if (ofString == "zzz149") // MIME Type
			{
				uriImgRefEntity.SetMimeType(this->GetStringValue());
			}
			else
				assert(false); // unexpected doc node

			imgLibNodeId = _pDoc->getTree().gotoNext();
		}
		while(imgLibNodeId > 0);

		nodeId = _pDoc->getTree().goUp();
	}
	else
		assert(false); // failed to read entity values
}

// Creates required Annotaion and reads AnnotationEntity values that are common to both ImageAnnotation and AnnotationOfAnnotation
AnnotationEntity* DcmModelInternal::ReadAnnotationEntity(AnnotationEntity::AnnotationType aeType)
{
	assert(this->GetConceptName().getCodeValue() == "zzz070"); // we're at the Annotation Entity node

	ImageAnnotation* pImgAnnotation = NULL;
	AnnotationOfAnnotation* pAnnOfAnn = NULL;
	AnnotationEntity* pAnnEnt = NULL;

	switch(aeType)
	{
	case AnnotationEntity::AT_ImageAnnotation:
		pImgAnnotation = new ImageAnnotation();
		pAnnEnt = pImgAnnotation;
		break;
	case AnnotationEntity::AT_AnnotationOfAnnotation:
		pAnnOfAnn = new AnnotationOfAnnotation();
		pAnnEnt = pAnnOfAnn;
		break;
	default:
		assert(false); // Unknown annotation type
	}
	assert(pAnnEnt);
	if (!pAnnEnt)
		return NULL;

	// Read Annotation Entity Container
	AuditTrailVector auditTrails;
	AnnotationRoleEntityVector annotationRoles;
	TaskContextEntityVector taskContextEntities;
	ImagingPhysicalEntityVector imagingPhysicalEntities;
	ImagingObservationEntityVector imagingObservations;
	CalculationEntityVector calculationEntities;
	InferenceEntityVector inferences;
	LesionObservationEntityPtrVector lesionObservations;

	// DateTime
	ofString = _pDoc->getTree().getCurrentContentItem().getObservationDateTime();
	if (ofString.empty())
	{
		// By default, dateTime of the annotation is the same as the dateTime of the document
		OFString tmpTime;
		ofCondition = _pDoc->getContentDate(ofString);
		ofCondition = _pDoc->getContentTime(tmpTime);
		ofString += tmpTime;
	}
	if (!ofString.empty())
	{
		OFDateTime ofDateTime;
		if (ofDateTime.setISOFormattedDateTime(ofString))
		{
			DateTime dateTime = AIMUtil::DateTimeConvert(ofDateTime);
			pAnnEnt->SetDateTime(dateTime);
		}
	}

	size_t annEntNodeId = _pDoc->getTree().goDown();
	if (annEntNodeId > 0)
	{
		do
		{
			ofString = this->GetConceptName().getCodeValue();
			if (ofString == "112040") // Annotation UID
			{
				pAnnEnt->SetUniqueIdentifier(this->GetStringValue());
			}
			else if (ofString == "zzz005") // Annotation type code
			{
				pAnnEnt->SetTypeCode(this->GetIsoCodeVector());
			}
			else if (ofString == "112039") // Annotation Name
			{
				pAnnEnt->SetName(this->GetStringValue());
			}
			else if (ofString == "121106") // Comment
			{
				pAnnEnt->SetComment(this->GetStringValue());
			}
			else if (ofString == "zzz068") // Precedent Annotation UID
			{
				iso_21090::II uid(this->GetStringValue());
				pAnnEnt->SetPrecedentReferencedAnnotationUid(&uid);
			}
			else if (ofString == "zzz103") // Template UID
			{
				iso_21090::II uid(this->GetStringValue());
				pAnnEnt->SetTemplateUid(&uid);
			}
			else if (ofString == "zzz104") // Audit Status
			{
				AuditTrail auditTrail = ReadAuditTrail();
				auditTrails.push_back(auditTrail);
			}
			else if (ofString == "zzz056") // Annotation Role Entity
			{
				AnnotationRoleEntity annRole = ReadAnnotationRoleEntity();
				annotationRoles.push_back(annRole);
			}
			else if (ofString == "zzz074") // Task Context Entity
			{
				TaskContextEntity taskContext = ReadTaskContextEntity();
				taskContextEntities.push_back(taskContext);
			}
			else if (ofString == "G-C0E3") // Imaging Physical Entity
			{
				ImagingPhysicalEntity imagingPhysEntity = ReadImagingPhysicalEntity();
				imagingPhysicalEntities.push_back(imagingPhysEntity);
			}
			else if (ofString == "zzz099") // Imaging Observation Entity
			{
				ImagingObservationEntity imagingObsEntity = ReadImagingObservationEntity();
				imagingObservations.push_back(imagingObsEntity);
			}
			else if (ofString == "zzz090") // Calculation Entity
			{
				CalculationEntity calcEntity = ReadCalculationEntity();
				calculationEntities.push_back(calcEntity);
			}
			else if (ofString == "zzz150") // Inference Entity
			{
				InferenceEntity inference = ReadInferenceEntity();
				inferences.push_back(inference);
			}
			else if (ofString == "zzz120") // Lesion Observation Entity
			{
				LesionObservationEntity* pLesionObservation = ReadLesionObservationEntity();
				if (pLesionObservation)
					lesionObservations.push_back(pLesionObservation);
			}
			else if (ofString == "zzz030") // Image Annotation
			{
				assert(pImgAnnotation); // This must be an Image Annotation
				ReadImageAnnotation(*pImgAnnotation);

			}
			else if (ofString == "zzz031") // Annotation Of Annotation
			{
				assert(pAnnOfAnn); // This must be an Annotation of Annotations
				ReadAnnotationOfAnnotation(*pAnnOfAnn);
			}
			else
				assert(false); // unexpected doc node

			annEntNodeId = _pDoc->getTree().gotoNext();
		}
		while(annEntNodeId > 0);

		nodeId = _pDoc->getTree().goUp();
	}
	else
		assert(false); // failed to read entity values

	// Store collections
	if (!auditTrails.empty())
		pAnnEnt->SetAuditTrailCollection(auditTrails);
	if (!annotationRoles.empty())
		pAnnEnt->SetAnnotationRoleEntityCollection(annotationRoles);
	if (!taskContextEntities.empty())
		pAnnEnt->SetTaskContextEntityCollection(taskContextEntities);
	if (!imagingPhysicalEntities.empty())
		pAnnEnt->SetImagingPhysicalEntityCollection(imagingPhysicalEntities);
	if (!imagingObservations.empty())
		pAnnEnt->SetImagingObservationEntityCollection(imagingObservations);
	if (!calculationEntities.empty())
		pAnnEnt->SetCalculationEntityCollection(calculationEntities);
	if (!inferences.empty())
		pAnnEnt->SetInferenceEntityCollection(inferences);
	if (!lesionObservations.empty())
	{
		pAnnEnt->SetLesionOservationEntityCollection(lesionObservations);
		while(lesionObservations.size() > 0)
		{
			delete lesionObservations[lesionObservations.size() - 1];
			lesionObservations.pop_back();
		}
	}

	return pAnnEnt;
}

// Reads string value from the CurrentContentItem
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

// Reads string portion of the NUM value from the current NUM node of the document
const std::string DcmModelInternal::GetNumericValueString() const
{
	return GetNumericValue().getNumericValue();
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

// read code value as an ISO21090 code from the CurrentContentItem
const iso_21090::CD DcmModelInternal::GetIsoCode() const
{
	DSRCodedEntryValue code = GetCode();
	return iso_21090::CD(code.getCodeValue(), code.getCodeMeaning(), code.getCodingSchemeDesignator(), code.getCodingSchemeVersion());
}

// Reads post-coordinated code values as an ISO21090 code vector from the current CODE node of the document and the node's CODE children
const iso_21090::CDVector DcmModelInternal::GetIsoCodeVector() const
{
	iso_21090::CDVector codes;

	codes.push_back(GetIsoCode());
	DSRCodedEntryValue parentConcept = GetConceptName();
	if (_pDoc->getTree().goDown() > 0)
	{
		// assumes that all child codes with the same concept are part of the post-coordinated term
		do
		{
			if (parentConcept == GetConceptName() &&
				_pDoc->getTree().getCurrentContentItem().getValueType() == DSRTypes::VT_Code &&
				_pDoc->getTree().getCurrentContentItem().getRelationshipType() == DSRTypes::RT_hasObsContext)
				codes.push_back(GetIsoCode());
			else
				break;
		}
		while (_pDoc->getTree().gotoNext() > 0);

		_pDoc->getTree().goUp();
	}

	return codes;
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

// read 3D spatial coordinate from the CurrentContentItem
const DSRSpatialCoordinates3DValue& DcmModelInternal::GetSpatialCoordinate3D() const
{
	if (_pDoc->getTree().getCurrentContentItem().getSpatialCoordinates3DPtr() == NULL)
		return AIMCodes::EmptySpatialCoordinate3DValue;
	else
		return _pDoc->getTree().getCurrentContentItem().getSpatialCoordinates3D();
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
				user.SetRoleInTrial(GetCode().getCodeMeaning());
			else if ("zzz026" == _stdString) // Login Name
				user.SetLoginName(GetStringValue());
			else if ("zzz045" == _stdString) // Identifier within Person Observer's Role
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

ImagingPhysicalEntity DcmModelInternal::ReadImagingPhysicalEntity()
{
	assert(this->GetConceptName().getCodeValue() == "G-C0E3");

	ImagingPhysicalEntity imgPhysEntity;
	ImagingPhysicalEntityCharacteristicVector imgPhysEntChars;
	ImagingObservationCharacteristicVector imgObsChars;

	// Imaging Physical Entity
	imgPhysEntity.SetTypeCode(GetIsoCodeVector());

	if (_pDoc->getTree().goDown() > 0)
	{
		do
		{
			ofString = this->GetConceptName().getCodeValue();
			if (ofString == "G-C0E3") // value is read above as part of post coordinated type code
			{ // NO-OP
			}
			else if (ofString == "112040") // Unique Identifier
			{
				imgPhysEntity.SetUniqueIdentifier(GetStringValue());
			}
			else if (ofString == "zzz071") // Question Type Code
			{
				imgPhysEntity.SetQuestionTypeCode(GetIsoCodeVector());
			}
			else if (ofString == "zzz085") // Question Index
			{
				imgPhysEntity.SetQuestionIndex(AIMUtil::StringToInt(GetNumericValueString()));
			}
			else if (ofString == "C45561") // Label
			{
				imgPhysEntity.SetLabel(GetStringValue());
			}
			else if (ofString == "121106") // Comment
			{
				imgPhysEntity.SetComment(GetStringValue());
			}
			else if (ofString == "zzz058") // Annotator Confidence
			{
				ofString = this->GetNumericValueString();
				double confidence = AIMUtil::StringToDouble(ofString);
				imgPhysEntity.SetAnnotatorConfidence(&confidence);
			}
			else if(ofString == "G-A203") // Is Present
			{
				bool isPresent = this->GetBooleanValue();
				imgPhysEntity.SetIsPresent(&isPresent);
			}
			else if(ofString == "zzz086") // Imaging Physical Characterisitc
			{
				ImagingPhysicalEntityCharacteristic imgPhysEntChar = ReadImagingPhysicalEntityCharacteristic();
				imgPhysEntChars.push_back(imgPhysEntChar);
			}
			else if (ofString == "zzz010") // Imaging Observation Characteristic
			{
				ImagingObservationCharacteristic imgObsChar = ReadImagingObservationCharacteristic();
				imgObsChars.push_back(imgObsChar);
			}
			else
				assert(false); // unknown content node
		} 
		while(_pDoc->getTree().gotoNext() > 0);

		if (imgPhysEntChars.size() > 0)
			imgPhysEntity.SetImagingPhysicalEntityCharacteristicCollection(imgPhysEntChars);
		if (imgObsChars.size() > 0)
			imgPhysEntity.SetImagingObservationCharacteristicCollection(imgObsChars);
		
		nodeId = _pDoc->getTree().goUp();
	}

	return imgPhysEntity;
}

ImagingPhysicalEntityCharacteristic DcmModelInternal::ReadImagingPhysicalEntityCharacteristic()
{
	assert(this->GetConceptName().getCodeValue() == "zzz086");

	ImagingPhysicalEntityCharacteristic imgPhysEntChar;
	CharacteristicQuantificationPtrVector charQuantifications;

	// Imaging Physical Entity
	imgPhysEntChar.SetTypeCode(GetIsoCodeVector());

	if (_pDoc->getTree().goDown() > 0)
	{
		do
		{
			ofString = this->GetConceptName().getCodeValue();
			if (ofString == "zzz086") // value is read above as part of post coordinated type code
			{ // NO-OP
			}
			else if (ofString == "zzz071") // Question Type Code
			{
				imgPhysEntChar.SetQuestionTypeCode(GetIsoCodeVector());
			}
			else if (ofString == "zzz085") // Question Index
			{
				imgPhysEntChar.SetQuestionIndex(AIMUtil::StringToInt(GetNumericValueString()));
			}
			else if (ofString == "C45561") // Label
			{
				imgPhysEntChar.SetLabel(GetStringValue());
			}
			else if (ofString == "121106") // Comment
			{
				imgPhysEntChar.SetComment(GetStringValue());
			}
			else if (ofString == "zzz058") // Annotator Confidence
			{
				ofString = this->GetNumericValueString();
				double confidence = AIMUtil::StringToDouble(ofString);
				imgPhysEntChar.SetAnnotatorConfidence(&confidence);
			}
			else if(ofString == "zzz066") // Characteristic Quantification
			{
				CharacteristicQuantification* pCharQuantification = this->ReadCharacteristicQuantification();
				if (pCharQuantification != NULL)
					charQuantifications.push_back(pCharQuantification);
			}
			else
				assert(false); // unknown content node
		} 
		while(_pDoc->getTree().gotoNext() > 0);
		
		nodeId = _pDoc->getTree().goUp();
	}

	if (charQuantifications.size() > 0)
	{
		imgPhysEntChar.SetCharacteristicQuantificationCollection(charQuantifications);
		while(charQuantifications.size() > 0)
		{
			delete charQuantifications[charQuantifications.size() - 1];
			charQuantifications.pop_back();
		}
	}

	return imgPhysEntChar;
}

ImagingObservationEntity DcmModelInternal::ReadImagingObservationEntity()
{
	assert(this->GetConceptName().getCodeValue() == "zzz099");

	ImagingObservationEntity imagingObservation;
	ImagingObservationCharacteristicVector imagingObsCharacteristics;

	// Imaging Observation Entity
	imagingObservation.SetTypeCode(GetIsoCodeVector());

	if (_pDoc->getTree().goDown() > 0)
	{
		do
		{
			ofString = this->GetConceptName().getCodeValue();
			if (ofString == "zzz099") // value is read above as part of post coordinated type code
			{ // NO-OP
			}
			else if (ofString == "112040") // Unique Identifier
			{
				imagingObservation.SetUniqueIdentifier(GetStringValue());
			}
			else if (ofString == "zzz071") // Question Type Code
			{
				imagingObservation.SetQuestionTypeCode(GetIsoCodeVector());
			}
			else if (ofString == "zzz085") // Question Index
			{
				imagingObservation.SetQuestionIndex(AIMUtil::StringToInt(GetNumericValueString()));
			}
			else if (ofString == "C45561") // Label
			{
				imagingObservation.SetLabel(GetStringValue());
			}
			else if (ofString == "121106") // Comment
			{
				imagingObservation.SetComment(GetStringValue());
			}
			else if (ofString == "zzz058") // Annotator Confidence
			{
				ofString = this->GetNumericValueString();
				double confidence = AIMUtil::StringToDouble(ofString);
				imagingObservation.SetAnnotatorConfidence(&confidence);
			}
			else if(ofString == "G-A203") // Is Present
			{
				bool isPresent = this->GetBooleanValue();
				imagingObservation.SetIsPresent(&isPresent);
			}
			else if (ofString == "zzz010") // Imaging Observation Characteristic
			{
				ImagingObservationCharacteristic imgObsChar = ReadImagingObservationCharacteristic();
				imagingObsCharacteristics.push_back(imgObsChar);
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

ImagingObservationCharacteristic DcmModelInternal::ReadImagingObservationCharacteristic()
{
	assert(this->GetConceptName().getCodeValue() == "zzz010");

	ImagingObservationCharacteristic imagingObsChar;
	CharacteristicQuantificationPtrVector charQuantifications;

	// Imaging Observation Characteristic
	imagingObsChar.SetTypeCode(GetIsoCodeVector());

	if(_pDoc->getTree().goDown() > 0)
	{
		do
		{
			ofString = this->GetConceptName().getCodeValue();
			if (ofString == "zzz010") // value is read above as part of post coordinated type code
			{ // NO-OP
			}
			else if (ofString == "zzz071") // Question Type Code
			{
				imagingObsChar.SetQuestionTypeCode(GetIsoCodeVector());
			}
			else if (ofString == "zzz085") // Question Index
			{
				imagingObsChar.SetQuestionIndex(AIMUtil::StringToInt(GetNumericValueString()));
			}
			else if (ofString == "C45561") // Label
			{
				imagingObsChar.SetLabel(GetStringValue());
			}
			else if (ofString == "121106") // Comment
			{
				imagingObsChar.SetComment(GetStringValue());
			}
			else if (ofString == "zzz058") // Annotator Confidence
			{
				ofString = this->GetNumericValueString();
				double confidence = AIMUtil::StringToDouble(ofString);
				imagingObsChar.SetAnnotatorConfidence(&confidence);
			}
			else if(ofString == "zzz066") // Characteristic Quantification
			{
				CharacteristicQuantification* pCharQuantification = this->ReadCharacteristicQuantification();
				if (pCharQuantification != NULL)
					charQuantifications.push_back(pCharQuantification);
			}
			else
				assert(false); // unknown content node
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
			if (ofString == "C45561") // Label
			{
				pCharQuantification->SetLabel(this->GetStringValue());
			}
			else if (ofString == "zzz058") // Annotator Confidence
			{
				ofString = this->GetNumericValueString();
				double confidence = AIMUtil::StringToDouble(ofString);
				pCharQuantification->SetAnnotatorConfidence(&confidence);
			}
			else if (ofString == "zzz087") // Characteristic Quantification Index
			{
				pCharQuantification->SetCharacteristicQuantificationIndex(AIMUtil::StringToInt(GetNumericValueString()));
			}
			else if (ofString == "zzz153") // Value Label
			{
				pCharQuantification->SetValueLabel(GetStringValue());
			}
			else if (ofString == "zzz154") // Value Description
			{
				pCharQuantification->SetValueDescription(GetStringValue());
			}
			else if (ofString == "121106") // Comment
			{
				pCharQuantification->SetComment(GetStringValue());
			}
			else if (ofString == "C25712" && pNumerical != NULL) // Numerical
			{
				assert(pNumerical != NULL);

				// Value
				DSRNumericMeasurementValue dsrNumValue = this->GetNumericValue();

				ofString = dsrNumValue.getNumericValue();
				pNumerical->SetValue(AIMUtil::StringToDouble(ofString));

				_dsrCode = dsrNumValue.getMeasurementUnit();
				if (_dsrCode.isValid())
				{
					ofString.assign(_dsrCode.getCodeMeaning());
					pNumerical->SetUcumString(ofString);
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

				// Selected Bin
				pQuantile->SetSelectedBin(AIMUtil::StringToInt(GetNumericValueString()));
				if(_pDoc->getTree().goDown() > 0)
				{
					do
					{
						ofString = GetConceptName().getCodeValue();
						if (ofString == "zzz151") // Number of Intervals
						{
							pQuantile->SetBins(AIMUtil::StringToInt(GetNumericValueString()));
						}
						else if (ofString == "R-404FB") // Minimum
						{
							pQuantile->SetMinValue(AIMUtil::StringToDouble(GetNumericValueString()));
						}
						else if (ofString == "G-A437") // Maximum
						{
							pQuantile->SetMaxValue(AIMUtil::StringToDouble(GetNumericValueString()));
						}
						else
							assert(false); // unexpected node
					}
					while (_pDoc->getTree().gotoNext() > 0);

					nodeId = _pDoc->getTree().goUp();
				}
			}
			else if (ofString == "zzz067") // Non-Quantifiable
			{
				assert(pNonQuantifiable != NULL);

				pNonQuantifiable->SetTypeCode(GetIsoCode());
			}
			else if (ofString == "C25712" && pScale != NULL) // Scale
			{
				assert(pScale != NULL);

				// Value
				pScale->SetValue(GetStringValue());

				if(_pDoc->getTree().goDown() > 0)
				{
					assert(GetConceptName().getCodeValue() == "zzz088"); // Scale Type

					pScale->SetScaleType(AIMCodes::GetScaleType(GetCode()));

					nodeId = _pDoc->getTree().goUp();
				}
			}
			else if (ofString == "G-A437") // Interval
			{
				assert(pInterval != NULL);

				// Maximum
				DSRNumericMeasurementValue dsrNumValue = this->GetNumericValue();
				pInterval->SetMaxValue(AIMUtil::StringToDouble(dsrNumValue.getNumericValue()));
				pInterval->SetUcumString(dsrNumValue.getMeasurementUnit().getCodeMeaning());

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
				pInterval->SetMinValue(AIMUtil::StringToDouble(dsrNumValue.getNumericValue()));
				pInterval->SetUcumString(dsrNumValue.getMeasurementUnit().getCodeMeaning());

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

InferenceEntity DcmModelInternal::ReadInferenceEntity()
{
	assert(this->GetConceptName().getCodeValue() == "zzz150");

	InferenceEntity inference;

	inference.SetTypeCode(GetIsoCodeVector());

	if (_pDoc->getTree().goDown() > 0)
	{
		do
		{
			ofString = this->GetConceptName().getCodeValue();
			if (ofString == "zzz150") // value is read above as part of post coordinated type code
			{ // NO-OP
			}
			else if (ofString == "112040") // Unique Identifier
			{
				inference.SetUniqueIdentifier(GetStringValue());
			}
			else if (ofString == "zzz071") // Question Type Code
			{
				inference.SetQuestionTypeCode(GetIsoCodeVector());
			}
			else if (ofString == "zzz085") // Question Index
			{
				inference.SetQuestionIndex(AIMUtil::StringToInt(GetNumericValueString()));
			}
			else if (ofString == "zzz058") // Annotator Confidence
			{
				ofString = this->GetNumericValueString();
				double confidence = AIMUtil::StringToDouble(ofString);
				inference.SetAnnotatorConfidence(&confidence);
			}
			else if(ofString == "zzz059") // Image Evidence
			{
				inference.SetImageEvidence(this->GetBooleanValue());
			}
			else if(ofString == "G-A203") // Is Present
			{
				bool isPresent = this->GetBooleanValue();
				inference.SetIsPresent(&isPresent);
			}
			else if (ofString == "C25365") // Description
			{
				inference.SetDescription(GetStringValue());
			}
			else if (ofString == "C45561") // Label
			{
				inference.SetLabel(GetStringValue());
			}
			else if (ofString == "121106") // Comment
			{
				inference.SetComment(GetStringValue());
			}
			else
				assert(false); // unknown content node
		} 
		while(_pDoc->getTree().gotoNext() > 0);

		nodeId = _pDoc->getTree().goUp();
	}

	return inference;
}

CalculationEntity DcmModelInternal::ReadCalculationEntity()
{
	assert(this->GetConceptName().getCodeValue() == "zzz090");

	CalculationEntity calculation;
	CalculationResultPtrVector calcResults;

	// Calculation Entity
	calculation.SetTypeCode(GetIsoCodeVector());

	// Step into calculation container
	if (_pDoc->getTree().goDown() > 0)
	{
		do
		{
			ofString = GetConceptName().getCodeValue();
			if (ofString == "zzz090") // value is read above as part of post coordinated type code
			{ //NO-OP
			}
			else if (ofString == "112040") // Unique Identifier
			{
				calculation.SetUniqueIdentifier(GetStringValue());
			}
			else if (ofString == "zzz071") // Question Type Code
			{
				calculation.SetQuestionTypeCode(GetIsoCodeVector());
			}
			else if (ofString == "zzz085") // Question Index
			{
				calculation.SetQuestionIndex(AIMUtil::StringToInt(GetNumericValueString()));
			}
			else if (ofString == "112034") // Calculation Description
			{
				calculation.SetDescription(GetStringValue());
			}
			else if (ofString == "zzz013") // Calculation MathML
			{
				calculation.SetMathML(GetStringValue());
			}
			else if (ofString == "111001") // Algorithm
			{
				Algorithm algorithm = ReadAlgorithm();
				calculation.SetAlgorithm(&algorithm);
			}
			else if (ofString == "zzz015") // Compact Calculation Result (Numeric only)
			{
				CalculationResult* pCalcResult = this->ReadCalculationResult();
				calcResults.push_back(pCalcResult);
			}
			else if (ofString == "zzz016") // Other Calculation Result
			{
				CalculationResult* pCalcResult = this->ReadCalculationResult();
				calcResults.push_back(pCalcResult);
			}
			else
				assert(false); // unknown calculation template entry
		}
		while(_pDoc->getTree().gotoNext() > 0);

		nodeId = _pDoc->getTree().goUp();
	}

	if(calcResults.size() > 0)
	{
		calculation.SetCalculationResultCollection(calcResults);
		while(calcResults.size() > 0)
		{
			delete calcResults[calcResults.size() - 1];
			calcResults.pop_back();
		}
	}

	return calculation;
}

CalculationResult* DcmModelInternal::ReadCalculationResult()
{
	assert(this->GetConceptName().getCodeValue() == "zzz015" || this->GetConceptName().getCodeValue() == "zzz016");

	if (this->GetConceptName().getCodeValue() == "zzz015") // Compact Calculation Results - special case
	{
		CompactCalculationResult compactCalcResult;

		compactCalcResult.SetType(CalculationResult::Scalar); // Always Scalar
		DSRNumericMeasurementValue dsrNumValue = this->GetNumericValue();
		compactCalcResult.SetUnitOfMeasure(dsrNumValue.getMeasurementUnit().getCodeMeaning());
		compactCalcResult.SetValue(dsrNumValue.getNumericValue());

		if (_pDoc->getTree().goDown() > 0)
		{
			do
			{
				ofString = GetConceptName().getCodeValue();
				if (ofString == "zzz018") // Dimension Label
				{
					Dimension dim;
					dim.SetLabel(GetStringValue());
					dim.SetIndex(1);
					dim.SetSize(1);
					DimensionVector dims;
					dims.push_back(dim);
					compactCalcResult.SetDimensionCollection(dims);
				}
				else if (ofString == "C42645") // Data Type
				{
					compactCalcResult.SetDataType(GetIsoCode());
				}
				else
					assert(false); // Unexpected node

			}
			while (_pDoc->getTree().gotoNext() > 0);

			nodeId = _pDoc->getTree().goUp();
		}

		return compactCalcResult.Clone();
	}
	else if (this->GetConceptName().getCodeValue() == "zzz016")
	{
		CompactCalculationResult* pCompactCalcResult = NULL;
		ExtendedCalculationResult* pExtendedCalcResult = NULL;
		DimensionVector dimensions;
		iso_21090::CD dataType;
		CalculationResult::CalculationResultType calcResultType;
		std::string unitOfMeasure;
		CalculationDataVector calcData;

		// Result Type
		calcResultType = CalculationResult::StringToCalculationResultType(GetCode().getCodeMeaning());

		if (_pDoc->getTree().goDown() > 0)
		{
			do
			{
				ofString = GetConceptName().getCodeValue();
				if (ofString == "C42645") // Data Type
				{
					dataType = GetIsoCode();
				}
				else if (ofString == "C25709") // Unit of Measure
				{
					unitOfMeasure = GetCode().getCodeMeaning();
				}
				else if (ofString == "zzz040") // Dimension Index
				{
					Dimension dim;

					dim.SetIndex(AIMUtil::StringToInt(GetNumericValueString()));
					if (_pDoc->getTree().goDown() > 0)
					{
						do
						{
							ofString = GetConceptName().getCodeValue();
							if (ofString == "zzz041") // Dimension Size
							{
								dim.SetSize(AIMUtil::StringToInt(GetNumericValueString()));
							}
							else if (ofString == "zzz018") // Dimension Label
							{
								dim.SetLabel(GetStringValue());
							}
							else
								assert(false); // Unexpected node
						}
						while (_pDoc->getTree().gotoNext() > 0);

						nodeId = _pDoc->getTree().goUp();
					}
					else
						assert(false); // incomplete Dimension data
					dimensions.push_back(dim);
				}
				else if (ofString == "zzz092") // Compact Calculation Result
				{
					pCompactCalcResult = new CompactCalculationResult();

					// Value
					pCompactCalcResult->SetValue(GetStringValue());

					if (_pDoc->getTree().goDown() > 0)
					{
						do
						{
							ofString = GetConceptName().getCodeValue();
							if (ofString == "C80216") // Encoding
							{
								iso_21090::CD code(GetIsoCode());
								pCompactCalcResult->SetEncoding(&code);
							}
							else if (ofString == "C41208") // Compression
							{
								iso_21090::CD code(GetIsoCode());
								pCompactCalcResult->SetCompression(&code);
							}
							else
								assert(false); // Unexpected node
						}
						while (_pDoc->getTree().gotoNext() > 0);

						nodeId = _pDoc->getTree().goUp();
					}

				}
				else if (ofString == "zzz020") // Calculation Data - Extended Caclulation results
				{
					if (!pExtendedCalcResult) // we can have multiple nodes
						pExtendedCalcResult = new ExtendedCalculationResult();

					CalculationData calcDatum;
					CoordinateVector coordinates;

					// Value
					calcDatum.SetValue(GetStringValue());

					if (_pDoc->getTree().goDown() > 0)
					{
						do
						{
							ofString = GetConceptName().getCodeValue();
							if (ofString == "zzz040") // Coordinate
							{
								Coordinate coord;

								// Dimension Index
								coord.SetDimensionIndex(AIMUtil::StringToInt(GetNumericValueString()));
								if (_pDoc->getTree().goDown() > 0)
								{
									// Coordinate Position
									assert(GetConceptName().getCodeValue() == "zzz043");

									coord.SetPosition(AIMUtil::StringToInt(GetNumericValueString()));

									nodeId = _pDoc->getTree().goUp();
								}

								coordinates.push_back(coord);
							}
							else
								assert(false); // Unexpected node
						}
						while (_pDoc->getTree().gotoNext() > 0);

						nodeId = _pDoc->getTree().goUp();
					}

					if (coordinates.size() > 0)
						calcDatum.SetCoordinateCollection(coordinates);
					calcData.push_back(calcDatum);
				}
				else
					assert(false); // Unexpected node
			}
			while (_pDoc->getTree().gotoNext() > 0);

			nodeId = _pDoc->getTree().goUp();
		}

		assert(!pCompactCalcResult || !pExtendedCalcResult); // only one should be set
		
		if (pCompactCalcResult)
		{
			pCompactCalcResult->SetType(calcResultType);
			pCompactCalcResult->SetDataType(dataType);
			pCompactCalcResult->SetUnitOfMeasure(unitOfMeasure);
			if (dimensions.size() > 0)
				pCompactCalcResult->SetDimensionCollection(dimensions);

			return pCompactCalcResult;
		}

		if (pExtendedCalcResult)
		{
			pExtendedCalcResult->SetType(calcResultType);
			pExtendedCalcResult->SetDataType(dataType);
			pExtendedCalcResult->SetUnitOfMeasure(unitOfMeasure);
			pExtendedCalcResult->SetCalculationDataCollection(calcData);
			if (dimensions.size() > 0)
				pExtendedCalcResult->SetDimensionCollection(dimensions);

			return pExtendedCalcResult;
		}
	}

	return NULL;
}

Algorithm DcmModelInternal::ReadAlgorithm()
{
	assert(this->GetConceptName().getCodeValue() == "111001");

	Algorithm algorithm;
	ParameterVector params;

	// Algorithm Name
	algorithm.SetName(GetStringValue());

	if (_pDoc->getTree().goDown() > 0)
	{
		do
		{
			ofString = this->GetConceptName().getCodeValue();
			if (ofString == "zzz091") // Algorithm Type
			{
				algorithm.SetType(GetIsoCodeVector());
			}
			else if (ofString == "112040") // Algorithm Unique Identifier
			{
				iso_21090::II uid(GetStringValue());
				algorithm.SetUniqueIdentifier(&uid);
			}
			else if (ofString == "111003") // Algorithm Version
			{
				algorithm.SetVersion(GetStringValue());
			}
			else if (ofString == "C25365") // Description
			{
				algorithm.SetDescription(GetStringValue());
			}
			else if (ofString == "C44175") // Parameter
			{
				Parameter param;
				param.SetName(GetStringValue());
				if (_pDoc->getTree().goDown() > 0)
				{
					do
					{
						ofString = this->GetConceptName().getCodeValue();
						if (ofString == "C49100") // Data Value
						{
							param.SetValue(GetStringValue());
						}
						else if (ofString == "C42645") // Data Type
						{
							param.SetDataType(GetIsoCode());
						}
						else
							assert(false); // Unexpected node
					}
					while(_pDoc->getTree().gotoNext() > 0);

					nodeId = _pDoc->getTree().goUp();
				}

				params.push_back(param);
			}
		}
		while(_pDoc->getTree().gotoNext() > 0);

		nodeId = _pDoc->getTree().goUp();
	}

	if (params.size() > 0)
		algorithm.SetParameterCollection(params);

	return algorithm;
}

TaskContextEntity DcmModelInternal::ReadTaskContextEntity()
{
	assert(this->GetConceptName().getCodeValue() == "zzz074");

	TaskContextEntity taskContext;
	taskContext.SetWorklistTaskName(GetStringValue());

	if (_pDoc->getTree().goDown() > 0)
	{
		do
		{
			_dsrCode = this->GetConceptName();
			ofString = _dsrCode.getCodeValue();
			if (ofString == "112040") // Unique Identifier
			{
				taskContext.SetUniqueIdentifier(GetStringValue());
			}
			else if (ofString == "zzz072") // Worklist Task UID
			{
				taskContext.SetWorklistTaskUid(GetStringValue());
			}
			else if (ofString == "zzz080") // Worklist Task Version
			{
				taskContext.SetWorklistTaskVersion(GetStringValue());
			}
			else if (ofString == "zzz074") // Worklist Task Description
			{
				taskContext.SetWorklistTaskDescription(GetStringValue());
			}
			else if (ofString == "zzz076") // Worklist Task Level
			{
				taskContext.SetWorklistTaskLevel(GetIsoCode());
			}
			else if (ofString == "zzz077") // Worklist Task Type
			{
				taskContext.SetWorklistTaskType(GetIsoCode());
			}
			else if (ofString == "zzz075") // Worklist Task Category
			{
				taskContext.SetWorklistTaskCategory(GetIsoCode());
			}
			else if (ofString == "zzz078") // Worklist Task Repeat Type
			{
				iso_21090::CD code = GetIsoCode();
				taskContext.SetWorklistTaskRepeatType(&code);
			}
			else if (ofString == "zzz079") // Worklist Task Variability Type
			{
				iso_21090::CD code = GetIsoCode();
				taskContext.SetWorklistTaskVariabilityType(&code);
			}
			else if (ofString == "zzz082") // Worklist Sub-task Name
			{
				taskContext.SetWorklistSubtaskName(GetStringValue());
			}
			else if (ofString == "zzz081") // Worklist Sub-task UID
			{
				taskContext.SetWorklistSubtaskUid(GetStringValue());
			}
			else if (ofString == "zzz083") // Worklist Sub-task Start DateTime
			{
				OFDateTime ofDateTime;
				if (ofDateTime.setISOFormattedDateTime(GetStringValue()))
				{
					DateTime dateTime = AIMUtil::DateTimeConvert(ofDateTime);
					taskContext.SetWorklistSubtaskStartDateTime(dateTime);
				}
			}
			else if (ofString == "zzz084") // Worklist Sub-task Closed DateTime
			{
				OFDateTime ofDateTime;
				if (ofDateTime.setISOFormattedDateTime(GetStringValue()))
				{
					DateTime dateTime = AIMUtil::DateTimeConvert(ofDateTime);
					taskContext.SetWorklistSubtaskClosedDateTime(dateTime);
				}
			}
			else
				assert(false); // unknown content node
		}
		while (_pDoc->getTree().gotoNext() > 0);

		nodeId = _pDoc->getTree().goUp();
	}

	return taskContext;
}

AuditTrail DcmModelInternal::ReadAuditTrail()
{
	assert(this->GetConceptName().getCodeValue() == "zzz104");

	AuditTrail auditTrail;
	auditTrail.SetStatusCode(GetIsoCode());

	if (_pDoc->getTree().goDown() > 0)
	{
		do
		{
			_dsrCode = this->GetConceptName();
			ofString = _dsrCode.getCodeValue();
			if (ofString == "121125") // DateTime
			{
				OFDateTime ofDateTime;
				if (ofDateTime.setISOFormattedDateTime(GetStringValue()))
				{
					DateTime dateTime = AIMUtil::DateTimeConvert(ofDateTime);
					auditTrail.SetDateTime(dateTime);
				}
			}
			else if (ofString == "C93529") // Change Reason
			{
				auditTrail.SetChangeReason(GetIsoCode());
			}
			else if (ofString == "zzz081") // Worklist Subtask UID
			{
				iso_21090::II uid(GetStringValue());
				auditTrail.SetWorklistSubtaskUid(&uid);
			}
			else if (ofString == "121106") // Comment
			{
				auditTrail.SetComment(GetStringValue());
			}
			else
				assert(false); // unknown content node
		}
		while (_pDoc->getTree().gotoNext() > 0);

		nodeId = _pDoc->getTree().goUp();
	}

	return auditTrail;
}

AnnotationRoleEntity DcmModelInternal::ReadAnnotationRoleEntity()
{
	assert(this->GetConceptName().getCodeValue() == "zzz056");

	AnnotationRoleEntity annRoleEntity;
	annRoleEntity.SetRoleCode(GetIsoCode());

	if (_pDoc->getTree().goDown() > 0)
	{
		do
		{
			ofString = this->GetConceptName().getCodeValue();
			if (ofString == "112040") // Unique Identifier
			{
				annRoleEntity.SetUniqueIdentifier(GetStringValue());
			}
			else if (ofString == "zzz057") // Role Sequence Number
			{
				annRoleEntity.SetRoleSequenceNumber(AIMUtil::StringToInt(GetNumericValueString()));
			}
			else if (ofString == "zzz071") // Question Type Code
			{
				annRoleEntity.SetQuestionTypeCode(GetIsoCodeVector());
			}
			else
				assert(false); // unknown content node
		}
		while (_pDoc->getTree().gotoNext() > 0);

		nodeId = _pDoc->getTree().goUp();
	}

	return annRoleEntity;
}

LesionObservationEntity* DcmModelInternal::ReadLesionObservationEntity()
{
	assert(this->GetConceptName().getCodeValue() == "zzz120");

	LesionObservationEntity* pLesionObs = NULL;
	std::string entityUid;
	std::string lesionUid;
	int additionalObservation = 0; // 0 - not set; 1 - true; -1 false

	if (_pDoc->getTree().goDown() > 0)
	{
		do
		{
			ofString = this->GetConceptName().getCodeValue();
			if (ofString == "112040") // Unique Identifier
			{
				entityUid = GetStringValue();
			}
			else if (ofString == "zzz121") // Lesion Unique Identifier
			{
				lesionUid = GetStringValue();
			}
			else if (ofString == "zzz119") // Is Additional Observation
			{
				additionalObservation = GetBooleanValue() ? 1 : -1;
			}
			else if (ofString == "112039") // Tracking Identifier
			{
				// General Lesion Observation
				GeneralLesionObservationEntity genLesionObs;

				genLesionObs.SetTrackingIdentifier(GetStringValue());

				if (_pDoc->getTree().goDown() > 0)
				{
					do
					{
						ofString = this->GetConceptName().getCodeValue();
						if (ofString == "zzz093") // Lesion Type
						{
							genLesionObs.SetLesionType(GetIsoCode());
						}
						else if (ofString == "zzz094") // Reconstruction Interval
						{
							iso_21090::CD code = GetIsoCode();
							genLesionObs.SetReconstructionInterval(&code);
						}
						else if (ofString == "G-C171") // Laterality
						{
							iso_21090::CD code = GetIsoCode();
							genLesionObs.SetLaterality(&code);
						}
						else
							assert(false); // unknown content node
					}
					while (_pDoc->getTree().gotoNext() > 0);

					nodeId = _pDoc->getTree().goUp();

					assert(!pLesionObs);
					pLesionObs = genLesionObs.Clone();
				}
				else
					assert(false); // missing General Lesion Observation data
			}
			else if (ofString == "zzz095") // Calibration
			{
				// Time Point Lesion Observation
				TimePointLesionObservationEntity timePtLesionObs;

				timePtLesionObs.SetCalibration(GetBooleanValue());

				if (_pDoc->getTree().goDown() > 0)
				{
					iso_21090::CD code;
					bool flag;

					do
					{
						ofString = this->GetConceptName().getCodeValue();
						if (ofString == "zzz096") // Predecessor Lesion Tracking UID
						{
							iso_21090::II uid(GetStringValue());
							timePtLesionObs.SetPredecessorLesionTrackingUid(&uid);
						}
						else if (ofString == "121106") // Comment
						{
							timePtLesionObs.SetComment(GetStringValue());
						}
						else if (ofString == "RID11510") // Therapeutic Response
						{
							timePtLesionObs.SetTherapeuticResponse(&(code = GetIsoCode()));
						}
						else if (ofString == "zzz097") // Qualitative Assessment
						{
							timePtLesionObs.SetQualitativeAssessment(&(code = GetIsoCode()));
						}
						else if (ofString == "zzz098") // Can Evaluate Lesion
						{
							timePtLesionObs.SetCanEvaluateLesion(&(flag = GetBooleanValue()));
						}
						else if (ofString == "zzz099") // Reason Unable to Evaluate
						{
							timePtLesionObs.SetReasonUnableToEvaluate(&(code = GetIsoCode()));
						}
						else if (ofString == "zzz100") // Can Evaluate Measure
						{
							timePtLesionObs.SetCanMeasureLesion(&(flag = GetBooleanValue()));
						}
						else if (ofString == "zzz101") // Reason Unable to Measure
						{
							timePtLesionObs.SetReasonUnableToMeasure(&(code = GetIsoCode()));
						}
						else if (ofString == "zzz102") // Unequivocal Progression
						{
							timePtLesionObs.SetIsUnequivocalProgression(&(flag = GetBooleanValue()));
						}
						else
							assert(false); // unknown content node
					}
					while (_pDoc->getTree().gotoNext() > 0);

					nodeId = _pDoc->getTree().goUp();

					assert(!pLesionObs);
					pLesionObs = timePtLesionObs.Clone();
				}
			}
			else
				assert(false); // unknown content node
		}
		while (_pDoc->getTree().gotoNext() > 0);

		nodeId = _pDoc->getTree().goUp();

		if (pLesionObs)
		{
			pLesionObs->SetUniqueIdentifier(entityUid);
			pLesionObs->SetLesionUniqueIdentifier(lesionUid);
			if (additionalObservation != 0)
			{
				bool isAdditionalObs = additionalObservation == 1;
				pLesionObs->SetIsAdditionalObservation(&isAdditionalObs);
			}
		}
	}

	return pLesionObs;
}

AnnotationStatement* DcmModelInternal::ReadAnnotationStatement()
{
	assert(this->GetConceptName().getCodeValue() == "zzz106");

	AnnotationStatement* pAnnotationStatement = NULL;

	std::string predicateClassName;
	std::string subjClassName;
	std::string subjUid;
	std::string objClassName;
	std::string objUid;

	// Predicate Class Name
	predicateClassName = AIMCodes::GetStatementPredicateClassName(GetCode());

	if (_pDoc->getTree().goDown())
	{
		do
		{
			ofString = this->GetConceptName().getCodeValue();
			if (ofString == "zzz107") // Annotation Statement Subject
			{
				subjClassName = AIMCodes::GetEntityClassName(GetCode());
				if (_pDoc->getTree().goDown())
				{
					// Subject UID
					assert(this->GetConceptName().getCodeValue() == "zzz109");
					subjUid = GetStringValue();
					nodeId = _pDoc->getTree().goUp();
				}
				else
					assert(false); // Subject UID is missing
			}
			else if (ofString == "zzz108") // Annotation Statement Object
			{
				objClassName = AIMCodes::GetEntityClassName(GetCode());
				if (_pDoc->getTree().goDown())
				{
					// Object UID
					assert(this->GetConceptName().getCodeValue() == "zzz110");
					objUid = GetStringValue();
					nodeId = _pDoc->getTree().goUp();
				}
				else
					assert(false); // Object UID is missing
			}
			else
				assert(false); // Unexpected node
		}
		while(_pDoc->getTree().gotoNext());

		nodeId = _pDoc->getTree().goUp();

		// Try to create statement with the data we have
		pAnnotationStatement = StatementFactory::Create(subjClassName, objClassName, predicateClassName);
		if (pAnnotationStatement)
		{
			if (!subjUid.empty())
				pAnnotationStatement->SetSubjectUniqueIdentifier(subjUid);
			if (!objUid.empty())
				pAnnotationStatement->SetObjectUniqueIdentifier(objUid);
		}
	}
	else
		assert(false); // cannot read statement data

	return pAnnotationStatement;
}

Equipment DcmModelInternal::ReadEquipment()
{
	Equipment equipment;
	_pDoc->getManufacturer(ofString);
	if (ofString.length() > 0)
		equipment.SetManufacturerName(ofString);
	_pDoc->getManufacturerModelName(ofString);
	if (ofString.length() > 0)
		equipment.SetManufacturerModelName(ofString);
	_pDoc->getSoftwareVersions(ofString);
	if (ofString.length() > 0)
		equipment.SetSoftwareVersion(ofString);
	_pDoc->getDeviceSerialNumber(ofString);
	if (ofString.length() > 0)
		equipment.SetDeviceSerialNumber(ofString);

	return equipment;
}

void DcmModelInternal::ReadImageAnnotation(ImageAnnotation& imgAnnotation)
{
	assert(this->GetConceptName().getCodeValue() == "zzz030");

	if (_pDoc->getTree().goDown() > 0)
	{
		ImageAnnotationStatementPtrVector annotationStmts;
		MarkupEntityPtrVector markups;
		SegmentationEntityPtrVector segmentations;

		do
		{
			ofString = this->GetConceptName().getCodeValue();
			if (ofString == "zzz106") // Annotation Statement
			{
				AnnotationStatement* pAnnotationStmt = this->ReadAnnotationStatement();
				if (pAnnotationStmt)
					annotationStmts.push_back(pAnnotationStmt);
			}
			else if (ofString == "zzz006") // Segmentation
			{
				SegmentationEntity* pSegmentation = this->ReadSegmentationEntity();
				if (pSegmentation)
					segmentations.push_back(pSegmentation);
			}
			else if (ofString == "zzz022") // Geometric Shapes
			{
				GeometricShapeEntity* pGeoShape = this->ReadGeoShapeEntity();
				if (pGeoShape)
					markups.push_back(pGeoShape);
			}
			else if (ofString == "zzz028") // Text Annotations
			{
				TextAnnotationEntity* pTextAnnotation = this->ReadTextAnnotationEntity();
				if (pTextAnnotation)
					markups.push_back(pTextAnnotation);
			}
			else
				assert(false); // unexpected
		}
		while(_pDoc->getTree().gotoNext() > 0);

		if (annotationStmts.size() > 0)
		{
			imgAnnotation.SetImageAnnotationStatementCollection(annotationStmts);
			while(annotationStmts.size() > 0)
			{
				delete annotationStmts[annotationStmts.size() - 1];
				annotationStmts.pop_back();
			}
		}

		if (markups.size() > 0)
		{
			imgAnnotation.SetMarkupEntityCollection(markups);
			while(markups.size() > 0)
			{
				delete markups[markups.size() - 1];
				markups.pop_back();
			}
		}

		if (segmentations.size() > 0)
		{
			imgAnnotation.SetSegmentationEntityCollection(segmentations);
			while(segmentations.size() > 0)
			{
				delete segmentations[segmentations.size() - 1];
				segmentations.pop_back();
			}
		}

		nodeId = _pDoc->getTree().goUp();
	}
}

SegmentationEntity* DcmModelInternal::ReadSegmentationEntity()
{
	assert(this->GetConceptName().getCodeValue() == "zzz006");

	// Only DICOM Segmentation objects are supported for now
	DicomSegmentationEntity segmentation;

	if (_pDoc->getTree().goDown() > 0)
	{
		do
		{
			ofString = GetConceptName().getCodeValue();
			if (ofString == "112040") // Segmentation Entity Unique Identifier
			{
				segmentation.SetUniqueIdentifier(GetStringValue());
			}
			else if (ofString == "zzz006") // Segmentation Object
			{
				DSRImageReferenceValue dsrImgRef = _pDoc->getTree().getCurrentContentItem().getImageReference();

				if (dsrImgRef.isValid() && dsrImgRef.getSOPClassUID() == "1.2.840.10008.5.1.4.1.1.66.4")
				{
					segmentation.SetSopClassUid(dsrImgRef.getSOPClassUID());
					segmentation.SetSopInstanceUid(dsrImgRef.getSOPInstanceUID());
				}
				else
					assert(false); // invalid DSRImageReferenceValue or unexpected segmentation SOP class UID
			}
			else if (ofString == "zzz047") // Segmented Image reference
			{
				DSRImageReferenceValue dsrImgRef = _pDoc->getTree().getCurrentContentItem().getImageReference();

				if (dsrImgRef.isValid())
					segmentation.SetReferencedSopInstanceUid(dsrImgRef.getSOPInstanceUID());
				else
					assert(false); // invalid image reference
			}
			else if (ofString == "zzz060") // segment number
			{
				segmentation.SetSegmentNumber(AIMUtil::StringToInt(GetNumericValue().getNumericValue()));
			}
			else
				assert(false); // unexpected entry
		}
		while(_pDoc->getTree().gotoNext() > 0);

		nodeId = _pDoc->getTree().goUp();
	}
	else
		assert(false); // Segmentation data is missing

	return segmentation.Clone();
}

GeometricShapeEntity* DcmModelInternal::ReadGeoShapeEntity()
{
	assert(this->GetConceptName().getCodeValue() == "zzz022");

	GeometricShapeEntity* pGeoShape = NULL;
	TwoDimensionGeometricShapeEntity* pGeoShape2D = NULL;

	_dsrCode = GetConceptName(); // zzz022
	if(_pDoc->getTree().goDown() > 0)
	{
		// Find Shape Data and create the shape of the correct type.
		// Shape Data node is one of the nodes at this level and has the same concept name as the parent node.
		std::string curPosition = _pDoc->getTree().getPosition(_stdString);
		if (_pDoc->getTree().gotoNamedNode(_dsrCode, false, false) > 0)
		{
			// 1. Create the correct shape type
			if (_pDoc->getTree().getCurrentContentItem().getValueType() == DSRTypes::VT_SCoord)
			{
				// SCOORD 2D
				pGeoShape2D = this->ReadScoord2D();
				pGeoShape = pGeoShape2D;
			}
			else if (_pDoc->getTree().getCurrentContentItem().getValueType() == DSRTypes::VT_SCoord3D)
			{
				// SCOORD 3D
				pGeoShape = this->ReadScoord3D();
			}
			else
				assert(false); // unexpected node type

			// Reset to the node we had before shape type shearch
			nodeId = _pDoc->getTree().gotoNode(curPosition);
			//while(_pDoc->getTree().gotoPrevious() > 0)
			//	; // Reset to the first node at this level

			// 2. Read the rest of the shape data
			if (pGeoShape)
			{
				do
				{
					ofString = GetConceptName().getCodeValue();
					if (ofString == "112040") // Unique Identifier
					{
						pGeoShape->SetUniqueIdentifier(GetStringValue());
					}
					else if (ofString == "zzz022") // Shape Data
					{
						// Node data should be already read

						if (_pDoc->getTree().getCurrentContentItem().getValueType() == DSRTypes::VT_SCoord)
						{
							// SCOORD 2D
							assert(dynamic_cast<TwoDimensionGeometricShapeEntity*>(pGeoShape) != NULL);
						}
						else if (_pDoc->getTree().getCurrentContentItem().getValueType() == DSRTypes::VT_SCoord3D)
						{
							// SCOORD 3D
							assert(dynamic_cast<ThreeDimensionGeometricShapeEntity*>(pGeoShape) != NULL);
						}
						else
							assert(false); // unexpected value type
					}
					else if (ofString == "C42778") // URI
					{
						if (pGeoShape2D)
							pGeoShape2D->SetUri(GetStringValue());
						else
							assert(false); // URI is 2D only
					}
					else if (ofString == "zzz021") // Include Flag
					{
						pGeoShape->SetIncludeFlag(this->GetBooleanValue());
					}
					else if (ofString == "112039") // Shape Identifier
					{
						pGeoShape->SetShapeIdentifier(AIMUtil::StringToInt(GetNumericValueString()));
					}
					else if (ofString == "zzz071") // Question Type Code
					{
						pGeoShape->SetQuestionTypeCode(GetIsoCodeVector());
					}
					else if (ofString == "zzz085") // Question Index
					{
						pGeoShape->SetQuestionIndex(AIMUtil::StringToInt(GetNumericValueString()));
					}
					else if (ofString == "C45561") // Label
					{
						pGeoShape->SetLabel(GetStringValue());
					}
					else if (ofString == "C25365") // Description
					{
						pGeoShape->SetDescription(GetStringValue());
					}
					else if (ofString == "121106") // Comment
					{
						pGeoShape->SetComment(GetStringValue());
					}
					else if (ofString == "zzz132") // Line Color
					{
						pGeoShape->SetLineColor(GetStringValue());
					}
					else if (ofString == "zzz133") // Line Opacity
					{
						pGeoShape->SetLineOpacity(GetStringValue());
					}
					else if (ofString == "zzz134") // Line Style
					{
						pGeoShape->SetLineStyle(GetStringValue());
					}
					else if (ofString == "zzz135") // Line Thickness
					{
						pGeoShape->SetLineThickness(GetStringValue());
					}
					else if (ofString == "C81208") // Interpolation
					{
						iso_21090::CD code(GetIsoCode());
						pGeoShape->SetInterpolationMethod(&code);
					}
					else
						assert(false); // unknown Geo Shape tag
				}
				while(_pDoc->getTree().gotoNext() > 0);
			}
			else
				assert(false); // failed to find geometric shape type
		}
		else
			assert(false); // failed to get shape data node

		nodeId = _pDoc->getTree().goUp();
	}
	else
		assert(false); // Geo Shape data is missing

	return pGeoShape;
}

TwoDimensionGeometricShapeEntity* DcmModelInternal::ReadScoord2D()
{
	assert(this->GetConceptName().getCodeValue() == "zzz022");
	assert(_pDoc->getTree().getCurrentContentItem().getValueType() == DSRTypes::VT_SCoord);

	TwoDimensionGeometricShapeEntity* pGeoShape = NULL;

	// 2D  SCOORD
	DSRSpatialCoordinatesValue spatialCoord = this->GetSpatialCoordinate();
	if (spatialCoord.isValid())
	{
		switch(spatialCoord.getGraphicType())
		{
		case DSRTypes::GT_Point:
			pGeoShape = new TwoDimensionPoint();
			break;
		case DSRTypes::GT_Circle:
			pGeoShape = new TwoDimensionCircle();
			break;
		case DSRTypes::GT_Ellipse:
			pGeoShape = new TwoDimensionEllipse();
			break;
		case DSRTypes::GT_Polyline:
			pGeoShape = new TwoDimensionPolyline();
			break;
		case DSRTypes::GT_Multipoint:
			pGeoShape = new TwoDimensionMultiPoint();
			break;
		default:
			assert(false); // unexpected 2D Geo Type
		}

		if (pGeoShape)
		{
			TwoDimensionSpatialCoordinateVector spatialCoords;
			iso_21090::II sopInstanceUID/*, sopClassUID*/;
			Sint32 referencedFrameNumber = 1;

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
					coord.SetCoordinateIndex(listIdx - 1); // zero-base index
					spatialCoords.push_back(coord);
				}
			}

			// Sort coordinates according to their CoordianteIndex
			std::sort(spatialCoords.begin(), spatialCoords.end(), TwoDimensionSpatialCoordinate::SpatialCoordinateSortPredicate);

			pGeoShape->SetTwoDimensionSpatialCoordinateCollection(spatialCoords);

			// Get Image Reference information
			if (_pDoc->getTree().goDown())
			{
				DSRImageReferenceValue imageRef = this->GetImageReference();
				if (imageRef.isValid())
				{
					sopInstanceUID = imageRef.getSOPInstanceUID();
					//sopClassUID = imageRef.getSOPClassUID();
					pGeoShape->SetImageReferenceUid(&sopInstanceUID);
					if (!imageRef.getFrameList().isEmpty())
					{
						ofCondition = imageRef.getFrameList().getItem(1, referencedFrameNumber);
						if (ofCondition.good())
							pGeoShape->SetReferencedFrameNumber(referencedFrameNumber);
					}
				}
				nodeId = _pDoc->getTree().goUp();
			}
		}
	}

	return pGeoShape;
}

ThreeDimensionGeometricShapeEntity* DcmModelInternal::ReadScoord3D()
{
	assert(this->GetConceptName().getCodeValue() == "zzz022");
	assert(_pDoc->getTree().getCurrentContentItem().getValueType() == DSRTypes::VT_SCoord3D);

	ThreeDimensionGeometricShapeEntity* pGeoShape = NULL;

	DSRSpatialCoordinates3DValue spatialCoord = this->GetSpatialCoordinate3D();
	if (spatialCoord.isValid())
	{
		switch(spatialCoord.getGraphicType())
		{
		case DSRTypes::GT3_Ellipsoid:
			pGeoShape = new ThreeDimensionEllipsoid();
			break;
		case DSRTypes::GT3_Ellipse:
			pGeoShape = new ThreeDimensionEllipse();
			break;
		case DSRTypes::GT3_Point:
			pGeoShape = new ThreeDimensionPoint();
			break;
		case DSRTypes::GT3_Multipoint:
			pGeoShape = new ThreeDimensionMultiPoint();
			break;
		case DSRTypes::GT3_Polyline:
			pGeoShape = new ThreeDimensionPolyline();
			break;
		case DSRTypes::GT3_Polygon:
			pGeoShape = new ThreeDimensionPolygon();
			break;
		default:
			assert(false); // unexpected 3D Geo Type
		}

		if (pGeoShape)
		{
			ThreeDimensionSpatialCoordinateVector spatialCoords;
			iso_21090::II uid;

			// Get Spatial Coordinates
			// NOTE: Index starts at 1
			for(size_t listIdx=1; listIdx <= spatialCoord.getGraphicDataList().getNumberOfItems(); listIdx++)
			{
				float fX, fY, fZ;
				ofCondition = spatialCoord.getGraphicDataList().getItem(listIdx, fX, fY, fZ);
				if (ofCondition.good())
				{
					ThreeDimensionSpatialCoordinate coord;
					coord.SetX(fX);
					coord.SetY(fY);
					coord.SetZ(fZ);
					coord.SetCoordinateIndex(listIdx - 1); // zero-base index
					spatialCoords.push_back(coord);
				}
			}

			// Sort coordinates according to their CoordianteIndex
			std::sort(spatialCoords.begin(), spatialCoords.end(), ThreeDimensionSpatialCoordinate::SpatialCoordinateSortPredicate);

			pGeoShape->SetThreeDimensionSpatialCoordinateCollection(spatialCoords);

			_stdString = spatialCoord.getFrameOfReferenceUID();
			if (!_stdString.empty())
				pGeoShape->SetFrameOfReferenceUid(&(uid = _stdString));
			_stdString = spatialCoord.getFiducialUID();
			if (!_stdString.empty())
				pGeoShape->SetFiducialUid(&(uid = _stdString));
		}
	}

	return pGeoShape;
}

TextAnnotationEntity* DcmModelInternal::ReadTextAnnotationEntity()
{
	assert(this->GetConceptName().getCodeValue() == "zzz028");

	TextAnnotationEntity textAnnotation;

	if (_pDoc->getTree().goDown())
	{
		do
		{
			ofString = GetConceptName().getCodeValue();
			if (ofString == "G-D315") // Text
			{
				textAnnotation.SetText(GetStringValue());
			}
			else if (ofString == "112040") // Unique Identifier
			{
				textAnnotation.SetUniqueIdentifier(GetStringValue());
			}
			else if (ofString == "zzz125") // Font
			{
				textAnnotation.SetFont(GetStringValue());
			}
			else if (ofString == "zzz126") // Font Color
			{
				textAnnotation.SetFontColor(GetStringValue());
			}
			else if (ofString == "zzz127") // Font Effect
			{
				textAnnotation.SetFontEffect(GetStringValue());
			}
			else if (ofString == "zzz128") // Font Size
			{
				textAnnotation.SetFontSize(GetStringValue());
			}
			else if (ofString == "zzz129") // Font Style
			{
				textAnnotation.SetFontStyle(GetStringValue());
			}
			else if (ofString == "zzz130") // Text Justify
			{
				textAnnotation.SetTextJustify(GetStringValue());
			}
			else if (ofString == "zzz131") // Font Opacity
			{
				textAnnotation.SetFontOpacity(GetStringValue());
			}
			else if (ofString == "zzz022")
			{
				// GeoShape - Multipoint
				GeometricShapeEntity* pGeoShape = this->ReadGeoShapeEntity();
				if(pGeoShape)
				{
					textAnnotation.SetGeometricShapeEntity(pGeoShape);

#if _DEBUG
					// We need a multipoint with one or two points here
					TwoDimensionGeometricShapeEntity* pGeoShape2D = dynamic_cast<TwoDimensionGeometricShapeEntity*>(pGeoShape);
					ThreeDimensionGeometricShapeEntity* pGeoShape3D = dynamic_cast<ThreeDimensionGeometricShapeEntity*>(pGeoShape);
					assert(
						(pGeoShape2D && pGeoShape2D->GetShapeType() == TwoDimensionGeometricShapeEntity::Multipoint_2D &&
						pGeoShape2D->GetTwoDimensionSpatialCoordinateCollection().size() > 0 &&
						pGeoShape2D->GetTwoDimensionSpatialCoordinateCollection().size() <= 2) ||
						(pGeoShape3D && pGeoShape3D->GetShapeType() == ThreeDimensionGeometricShapeEntity::Multipoint_3D &&
						pGeoShape3D->GetThreeDimensionSpatialCoordinateCollection().size() > 0 &&
						pGeoShape3D->GetThreeDimensionSpatialCoordinateCollection().size() <= 2));
#endif
					delete pGeoShape;
				}
			}
			else
				assert(false); // unexpected
		}
		while(_pDoc->getTree().gotoNext() > 0);

		nodeId = _pDoc->getTree().goUp();
	}

	return textAnnotation.Clone();
}

Person DcmModelInternal::ReadPerson()
{
	// Person (aka Patient)
	Person patient;
	_pDoc->getPatientID(ofString);
	if (ofString.length() > 0)
		patient.SetId(ofString);
	_pDoc->getPatientName(ofString);
	patient.SetName(ofString);
	_pDoc->getPatientSex(ofString);
	patient.SetSex(ofString);
	_pDoc->getPatientBirthDate(ofString);
	Date birthDate(ofString);
	if (birthDate != Date())
		patient.SetBirthDate(birthDate);
	_pDoc->getEthnicGroup(ofString);
	if (ofString.length() > 0)
		patient.SetEthnicGroup(ofString);

	return patient;
}

void DcmModelInternal::ReadAnnotationOfAnnotation(AnnotationOfAnnotation& annOfAnnotation)
{
	assert(this->GetConceptName().getCodeValue() == "zzz031");

	if (_pDoc->getTree().goDown() > 0)
	{
		AnnotationOfAnnotationStatementPtrVector annotationStmts;
		do
		{
			ofString = this->GetConceptName().getCodeValue();
			if (ofString == "zzz106") // Annotation Statement
			{
				AnnotationStatement* pAnnotationStmt = this->ReadAnnotationStatement();
				annotationStmts.push_back(pAnnotationStmt);
			}
			else if (ofString == "zzz111") // Adjudication Observation
			{
				AdjudicationObservation adjudicationObs = this->ReadAdjudicationObservation();
				annOfAnnotation.SetAdjudicationObservation(&adjudicationObs);
			}
			else
				assert(false); // Unknow element in the annotaiton of annotation
		}
		while(_pDoc->getTree().gotoNext() > 0);

		if (annotationStmts.size() > 0)
		{
			annOfAnnotation.SetAnnotationOfAnnotationStatementCollection(annotationStmts);
			while(annotationStmts.size() > 0)
			{
				delete annotationStmts[annotationStmts.size() - 1];
				annotationStmts.pop_back();
			}
		}

		nodeId = _pDoc->getTree().goUp();
	}
	else
		assert(false); // missing content of Annotation of Annotaitons
}

AdjudicationObservation DcmModelInternal::ReadAdjudicationObservation()
{
	assert(this->GetConceptName().getCodeValue() == "zzz111");

	AdjudicationObservation adjudicationObs;

	adjudicationObs.SetObservationUid(_pDoc->getTree().getCurrentContentItem().getObservationUID());

	if (_pDoc->getTree().goDown() > 0)
	{
		iso_21090::CD code;
		do
		{
			ofString = this->GetConceptName().getCodeValue();
			if (ofString == "zzz118") // Observation Scope
			{
				adjudicationObs.SetObservationScope(GetIsoCode());
			}
			else if (ofString == "121011") // Person Observer's Role in this Procedures
			{
				adjudicationObs.SetPersonObserversRoleInThisProcedure(&(code = GetIsoCode()));
			}
			else if (ofString == "zzz113") // Identifier within Accepted Persion Observer's Role
			{
				std::vector<std::string> idWithingAcceptedObserversRole = adjudicationObs.GetIdentifierWithinAcceptedPersonObserversRole();
				idWithingAcceptedObserversRole.push_back(GetStringValue());
				adjudicationObs.SetIdentifierWithinAcceptedPersonObserversRole(idWithingAcceptedObserversRole);
				//adjudicationObs.SetIdentifierWithinAcceptedPersonObserversRole(GetStringValue());
			}
			else if (ofString == "zzz114") // Identifier within Rejected Persion Observer's Role
			{
				std::vector<std::string> idWithingRejectedObserversRole = adjudicationObs.GetIdentifierWithinRejectedPersonObserversRole();
				idWithingRejectedObserversRole.push_back(GetStringValue());
				adjudicationObs.SetIdentifierWithinRejectedPersonObserversRole(idWithingRejectedObserversRole);
				//adjudicationObs.SetIdentifierWithinRejectedPersonObserversRole(GetStringValue());
			}
			else if (ofString == "zzz115") // Reason for Choice
			{
				adjudicationObs.SetReasonForChoice(GetIsoCode());
			}
			else if (ofString == "zzz116") // Reason for Discordance
			{
				adjudicationObs.SetReasonForDiscordance(&(code = GetIsoCode()));
			}
			else if (ofString == "zzz117") // Image Quality Issues Discordance
			{
				adjudicationObs.SetImageQualityIssuesDiscordance(GetBooleanValue());
			}
			else if (ofString == "121106") // Comment
			{
				adjudicationObs.SetComment(GetStringValue());
			}
			else
				assert(false); // Unknow element
		}
		while(_pDoc->getTree().gotoNext() > 0);

		nodeId = _pDoc->getTree().goUp();
	}
	else
		assert(false); // missing content of AdjudicationObservation

	return adjudicationObs;
}
