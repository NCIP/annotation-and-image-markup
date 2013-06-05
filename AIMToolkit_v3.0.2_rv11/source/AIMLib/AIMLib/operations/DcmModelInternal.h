/*
  Classname: DcmModelInternal

*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#if !defined(_AIMLib_DcmModelInternal_Class)
#define _AIMLib_DcmModelInternal_Class

#include <string>
#include <vector>

// AIM Model
#include "../model/AimHeaders.h"
#include "../model/DicomTagCollection.h"

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
		//DSRDocument* CreateDSRDocument(const AnnotationPtrVector& annotations, const DicomTagCollection& headerValues, ostream* outputFile = NULL);
		DSRDocument* CreateDSRDocument(const AnnotationPtrVector& annotations, std::ostream* outputFile = NULL);

		//
		// DICOM SR Reading
		//
		OFCondition ReadDocFromFile(Annotation** pAnnotation, const std::string& fileName);
		int ReadDocFromFile(AnnotationPtrVector& annotations, const std::string& fileName);

		// Debug helpers:
		void printDebug(const char* message);
	private:
		//
		// DICOM SR Writng:
		//
		void CreateDSRDocumentHeaders(DSRDocument& doc, const DicomTagCollection& headerValues);
		void CreateAimSRContainer(const AnnotationPtrVector& annotations, DSRDocument& doc);
		void InitilializeHeaderValues(const AnnotationPtrVector& annotations, DicomTagCollection& headerValues);
		void SetHeaderTag(DicomTagCollection& headerValues, const DicomTagCollection::AIM_DCM_TAG& tag, const std::string& tagValue);

		void FillObserverInfo(Annotation& annotation, DSRDocument& doc);
		void FillImageLibrary(ImageAnnotation& imgAnnotation, DSRDocument& doc);

		void PopulateAnnotationEntity(Annotation& annotation, DSRDocument& doc);
		void PopulateImageAnnotation(Annotation& annotation, DSRDocument& doc);
		void PopulateAnnotationOfAnnotation(Annotation& annotation, DSRDocument& doc);

		// Calculation
		void PopulateReferencedCalculation(const ReferencedCalcVector& referencedCalc, DSRDocument& doc);
		void PopulateReferencedGeometricShapes(const ReferencedGeometricShapeVector& refGeoShape, DSRDocument& doc, bool nestFirst);
		void PopulateCalculationResultEntries(const CalcResultVector& calcResult, DSRDocument& doc);

		// ImageAnnotation
		void PopulateSegmentationContainer(ImageAnnotation& annotation, DSRDocument& doc, bool nestFirst);
		void PopulateGeometricShapeContainer(ImageAnnotation& annotation, DSRDocument& doc, bool nestFirst);
		void PopulateGeometricShapeEntry(ImageAnnotation& annotation, DSRDocument& doc, const GeometricShape& geoShape, DSRTypes::E_RelationshipType relWithParent, bool isNested);
//		void PopulateImageReferenceItem(ImageAnnotation& annotation, DSRDocument& doc, const std::string& imageReferenceUID, DSRTypes::E_AddMode addMode);

		// Annotation
		void PopulateAnatomicEntityContainer(Annotation& annotation, DSRDocument& doc);
		void PopulateAnatomicEntityCharEntry(const AnatomicEntityCharacteristic& anatomicEntityChar, DSRDocument& doc, DSRTypes::E_AddMode addMode = DSRTypes::AM_afterCurrent);
		void PopulateCharacteristicQuantificationEntries(const CharacteristicQuantificationPtrVector& charQuantifications, DSRDocument& doc, bool nestFirst);
		void PopulateImagingObservationContainer(Annotation& annotation, DSRDocument& doc);
		void PopulateImagingObservationEntry(const ImagingObservation& imgObservation, DSRDocument& doc, DSRTypes::E_AddMode addMode = DSRTypes::AM_afterCurrent);
		void PopulateImagingObservationCharEntry(const ImagingObservationCharacteristic& imgObsCharacteristic, DSRDocument& doc, DSRTypes::E_AddMode addMode = DSRTypes::AM_afterCurrent);
		void PopulateCalculationEntries(Annotation& annotation, DSRDocument& doc);
		void PopulateInferenceContainer(Annotation& annotation, DSRDocument& doc, bool nestFirst);

		// Helpers
		const Image* FindDICOMImage(const ImageAnnotation& annotation, const std::string& sopInstanceUID);

		//
		// DICOM SR Reading
		//
		OFCondition LoadAnnotationsFromDSRDocument(AnnotationPtrVector& annotations);
		ImageAnnotation* ReadImageAnnotation(size_t imgAnnotationNodeId, size_t nextAnnotationNodeId);
		AnnotationOfAnnotation* ReadAnnotationOfAnnotation(size_t annAnnotationNodeId);
		User ReadUser(); // reads user info. assumes that the tree is positioned on the first Persno Observer node
		ImageReferencePtrVector ReadImageLibrary(size_t annotationNodeId, size_t nextAnnotationNodeId);
		AnatomicEntity ReadAnatomicEntityEntry();
		AnatomicEntityCharacteristic ReadAnatomicEntityCharacteristicEntry();
		ImagingObservation ReadImagingObservationEntry();
		ImagingObservationCharacteristic ReadImagingObservationCharacteristicEntry();
		CharacteristicQuantification* ReadCharacteristicQuantification();
		Calculation ReadCalculationEntry();
		CalculationResult ReadCalculationResultEntry();
		// Imaging Annotation container
		void ReadImageAnnotationContainer(ImageAnnotation& imgAnnotation);
		Segmentation ReadSegmentationEntry();
		Inference ReadInferenceEntry();
		AimStatus ReadAimStatus();
		GeometricShape* ReadGeoShape();
		GeometricShape* Read2dScoord();
		GeometricShape* Read3dScoord();
		TextAnnotation ReadTextAnnotationContainer();
		ImageStudy ReadStudyFromImageRefValue(const DSRImageReferenceValue& imgReference, PresentationStateVector& presentationStates);
		// AnnotationOfAnnotation container
		void ReadAnnotationOfAnnotationContainer(AnnotationOfAnnotation& annAnnotation);


		//
		// Helper methods
		//

		// Determins annotation kind of the given annotation 
		Annotation::AnnotationKind FindAnnotationKind(size_t annotationNodeId, size_t nextAnnotationNodeId);

		// Reads string value from the current TEXT, DATETIME, DATE, TIME, UIDREF or PNAME node of the document
		const std::string GetStringValue(const std::string& defaultValue = "") const;

		// Reads code value from the current CODE node of the document
		const DSRCodedEntryValue& GetCode() const;

		// Reads NUM value from the current NUM node of the document
		const DSRNumericMeasurementValue& GetNumericValue() const;

		// Reads concept name from the current node of the document
		const DSRCodedEntryValue& GetConceptName() const;

		// Reads spatial coordinate from the current node of the document
		const DSRSpatialCoordinatesValue& GetSpatialCoordinate() const;

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