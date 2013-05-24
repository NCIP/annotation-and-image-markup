/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#if !defined(_AIMLib_DcmModelInternal_Class)
#define _AIMLib_DcmModelInternal_Class

#include <string>
#include <vector>

// AIM Model
#include "../AimHeaders.h"
#include "DicomTagCollection.h"

// DCMTK
#include "dcmtk/ofstd/ofcond.h"
#include "dcmtk/dcmsr/dsrdoc.h"

// Debug helpers
#include "../AimResultValidator.h"


// Macros
#define THROW_IF_EMPTY(strValue)	if (strValue.length() < 1) std::runtime_error(_T("Required value is missing"))
#define WARN_IF_EMPTY(strValue)		if (strValue.length() < 1) printDebug(_T("Required value is empty"))

// AIMLib module code. DCMTK reserves codes > 1023 for custom modules
#define OFM_aimlib 1024

namespace aim_lib
{
	class DcmModelInternal
	{
	public:
		DcmModelInternal(const std::string& uidPrefix);
		~DcmModelInternal(void);
		
		//
		// DICOM SR Writng
		//
		OFCondition WriteDocToFile(const DSRDocument& dsrdoc, const std::string& fileName);
		DSRDocument* CreateDSRDocument(const AnnotationCollection& annotationCollection, std::ostream* outputFile = NULL);

		//
		// DICOM SR Reading
		//
		OFCondition ReadDocFromFile(AnnotationCollection** pAnnotationCollection, const std::string& fileName);

		// Debug helpers:
		void printDebug(const char* message);
	private:
		//
		// DICOM SR Writing:
		//
		void CreateDSRDocumentHeaders(DSRDocument& doc, const DicomTagCollection& headerValues);
		void CreateAimSRContainer(const AnnotationCollection& annotationCollection, DSRDocument& doc);
		void InitilializeHeaderValues(const AnnotationCollection& annotationCollection, DicomTagCollection& headerValues);
		void SetHeaderTag(DicomTagCollection& headerValues, const DicomTagCollection::AIM_DCM_TAG& tag, const std::string& tagValue);

		void FillObserverInfo(const User& user, DSRDocument& doc);
		void FillImageLibrary(const ImageAnnotation& imgAnnotation, DSRDocument& doc);

		void PopulateAnnotationEntity(const AnnotationEntity& annotationEntity, DSRDocument& doc);
		void PopulateImageAnnotation(const ImageAnnotation& imageAnnotation, DSRDocument& doc);
		void PopulateAnnotationOfAnnotation(const AnnotationOfAnnotation& annotationOfAnnotation, DSRDocument& doc);

		// Annotation
		void PopulateTaskContextEntities(const TaskContextEntityVector& taskContextEntities, DSRDocument& doc);
		void PopulateImagingPhysicalEntities(const ImagingPhysicalEntityVector& imagingPhysicalEnitities, DSRDocument& doc);
		void PopulateImagingPhysicalEntityCharacteristics(const ImagingPhysicalEntityCharacteristicVector& physicalEntityChars, DSRDocument& doc);
		void PopulateCharacteristicQuantifications(const CharacteristicQuantificationPtrVector& charQuantifications, DSRDocument& doc, bool nestFirst);
		void PopulateImagingObservations(const ImagingObservationEntityVector& imgObservationEntities, DSRDocument &doc);
		void PopulateImagingObservationCharacteristics(const ImagingObservationCharacteristicVector& observationChars, DSRDocument& doc);
		void PopulateInferences(const InferenceEntityVector& inferences, DSRDocument& doc);
		void PopulateLesionObservations(const LesionObservationEntityPtrVector& lesionObservations, DSRDocument& doc);

		// Calculation
		void PopulateCalculations(const CalculationEntityVector& calcEntities, DSRDocument& doc);

		// ImageAnnotation
		void PopulateAnnotationStatements(const std::vector<AnnotationStatement*>& statements, DSRDocument& doc, bool nestFirst);
		void PopulateSegmentations(const ImageAnnotation& annotation, DSRDocument& doc, bool nestFirst);
		void PopulateMarkups(const ImageAnnotation& annotation, DSRDocument& doc, bool nestFirst);
		void PopulateGeometricShapeEntity(const ImageAnnotation& annotation, DSRDocument& doc, const GeometricShapeEntity& geoShape, DSRTypes::E_RelationshipType relWithParent, bool isNested);

		// Helpers
		const Image* FindDicomImage(const ImageAnnotation& annotation, const iso_21090::II& sopInstanceUid);

		void AddDsrItem(DSRDocument& doc, const DSRCodedEntryValue& concept, DSRTypes::E_RelationshipType relType, DSRTypes::E_AddMode addMode = DSRTypes::AM_afterCurrent);
		void AddDsrItem(DSRDocument& doc, const DSRCodedEntryValue& concept, const std::string& value, DSRTypes::E_RelationshipType relType, DSRTypes::E_AddMode addMode = DSRTypes::AM_afterCurrent);
		void AddDsrItem(DSRDocument& doc, const DSRCodedEntryValue& concept, int value, const DSRCodedEntryValue& units, DSRTypes::E_RelationshipType relType, DSRTypes::E_AddMode addMode = DSRTypes::AM_afterCurrent);
		void AddDsrItem(DSRDocument& doc, const DSRCodedEntryValue& concept, double value, const DSRCodedEntryValue& units, DSRTypes::E_RelationshipType relType, DSRTypes::E_AddMode addMode = DSRTypes::AM_afterCurrent);
		void AddDsrItem(DSRDocument& doc, const DSRCodedEntryValue& concept, const DateTime& value, DSRTypes::E_RelationshipType relType, DSRTypes::E_AddMode addMode = DSRTypes::AM_afterCurrent);
		void AddDsrItem(DSRDocument& doc, const DSRCodedEntryValue& concept, const DSRCodedEntryValue& value, DSRTypes::E_RelationshipType relType, DSRTypes::E_AddMode addMode = DSRTypes::AM_afterCurrent);
		void AddDsrItem(DSRDocument& doc, const DSRCodedEntryValue& concept, const iso_21090::II& value, DSRTypes::E_RelationshipType relType, DSRTypes::E_AddMode addMode = DSRTypes::AM_afterCurrent);
		void AddDsrItem(DSRDocument& doc, const DSRCodedEntryValue& concept, const iso_21090::CD& value, DSRTypes::E_RelationshipType relType, DSRTypes::E_AddMode addMode = DSRTypes::AM_afterCurrent);
		size_t AddDsrItem(DSRDocument& doc, const DSRCodedEntryValue& concept, const iso_21090::CDVector& value, DSRTypes::E_RelationshipType relType, DSRTypes::E_AddMode addMode = DSRTypes::AM_afterCurrent, bool doNotStepOut = false);

		////
		//// DICOM SR Reading
		////
		typedef std::map<std::string, ImageReferenceEntityPtrVector> MapAnnotationUidToImageReferences;
		OFCondition LoadAnnotationsFromDSRDocument(AnnotationCollection** ppAnnotationCollection);
		User ReadUser(); // reads user info. assumes that the tree is positioned on the first Person Observer node
		void ReadImageLibrary(MapAnnotationUidToImageReferences& annotationToImageEntitiesMap);
		void ReadDicomImageReferenceEntity(DicomImageReferenceEntity& dicomImgRefEntity, std::string& annotationUid);
		void ReadReferencedDicomObject(DicomImageReferenceEntity& dicomImgRefEntity, std::string& annotationUid);
		void ReadUriImageReferenceEntity(UriImageReferenceEntity& uriImgRefEntity, std::string& annotationUid);
		AnnotationEntity* ReadAnnotationEntity(AnnotationEntity::AnnotationType aeType);
		ImagingPhysicalEntity ReadImagingPhysicalEntity();
		ImagingPhysicalEntityCharacteristic ReadImagingPhysicalEntityCharacteristic();
		ImagingObservationEntity ReadImagingObservationEntity();
		ImagingObservationCharacteristic ReadImagingObservationCharacteristic();
		CharacteristicQuantification* ReadCharacteristicQuantification();
		InferenceEntity ReadInferenceEntity();
		CalculationEntity ReadCalculationEntity();
		CalculationResult* ReadCalculationResult();
		Algorithm ReadAlgorithm();
		TaskContextEntity ReadTaskContextEntity();
		AuditTrail ReadAuditTrail();
		AnnotationRoleEntity ReadAnnotationRoleEntity();
		LesionObservationEntity* ReadLesionObservationEntity();
		AnnotationStatement* ReadAnnotationStatement();
		Equipment ReadEquipment();
		// Image Annotation
		void ReadImageAnnotation(ImageAnnotation& imgAnnotation);
		SegmentationEntity* ReadSegmentationEntity();
		GeometricShapeEntity* ReadGeoShapeEntity();
		TwoDimensionGeometricShapeEntity* ReadScoord2D();
		ThreeDimensionGeometricShapeEntity* ReadScoord3D();
		TextAnnotationEntity* ReadTextAnnotationEntity();
		Person ReadPerson();
		// AnnotationOfAnnotation
		void ReadAnnotationOfAnnotation(AnnotationOfAnnotation& annAnnotation);
		AdjudicationObservation ReadAdjudicationObservation();


		//
		// Helper methods
		//

		// Determins annotation type of the given annotation 
		AnnotationEntity::AnnotationType FindAnnotationType(size_t annotationNodeId, size_t nextAnnotationNodeId);

		// Reads string value from the current TEXT, DATETIME, DATE, TIME, UIDREF or PNAME node of the document
		const std::string GetStringValue(const std::string& defaultValue = "") const;

		// Reads code value from the current CODE node of the document
		const DSRCodedEntryValue& GetCode() const;

		// Reads code value as an ISO21090 code from the current CODE node of the document
		const iso_21090::CD GetIsoCode() const;

		// Reads post-coordinated code values as an ISO21090 code vector from the current CODE node of the document and the node's CODE children
		const iso_21090::CDVector GetIsoCodeVector() const;

		// Reads NUM value from the current NUM node of the document
		const DSRNumericMeasurementValue& GetNumericValue() const;

		// Reads string portion of the NUM value from the current NUM node of the document
		const std::string GetNumericValueString() const;

		// Reads concept name from the current node of the document
		const DSRCodedEntryValue& GetConceptName() const;

		// Reads 2D spatial coordinate from the current node of the document
		const DSRSpatialCoordinatesValue& GetSpatialCoordinate() const;

		// Reads 3D spatial coordinate from the current node of the document
		const DSRSpatialCoordinates3DValue& GetSpatialCoordinate3D() const;

		// Reads image reference from the current node of the document
		const DSRImageReferenceValue& GetImageReference() const;

		// Reads boolean value from the current CODE node: ("R-0038D", "SRT", "Yes")("R-00339", "SRT", "No")
		const bool GetBooleanValue(const bool defaultValue = true) const;

		DSRDocument* _pDoc; // current document

		std::string _uidPrefix;

		// Temp vars for us to use. NOTE: Their values are (most likely) overwriten with every method call
		AimOFCondition ofCondition;
		OFString ofString;
		AimOFNode nodeId;
		DSRCodedEntryValue _dsrCode;
		std::string _stdString;
	};
}
#endif // _AIMLib_DcmModelInternal_Class