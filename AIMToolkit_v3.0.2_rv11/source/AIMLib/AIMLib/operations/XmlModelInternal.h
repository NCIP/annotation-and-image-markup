/*
  Classname: XmlModelInternal

*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#if !defined(_AIMLib_XmlModelInternal_Class)
#define _AIMLib_XmlModelInternal_Class

#include <string>

// Xerces C includes
#include "xercesc/dom/DOM.hpp"
#include "xercesc/util/PlatformUtils.hpp"
#include "xercesc/sax/HandlerBase.hpp"
#include "xercesc/framework/LocalFileFormatTarget.hpp"

// AIM XML includes
#pragma warning ( disable : 4996 )	// This function or variable may be unsafe. Consider using _sprintf_s instead

#include "../../Altova/Altova.h"
#include "../../Altova/SchemaTypes.h"
#include "../../Altova/AltovaException.h"
#include "../../AltovaXML/XmlException.h"
#include "../../AltovaXML/Node.h"

#include "../../AIMXML/AIMXML.h"


namespace aim_lib
{
	class XmlModelInternal
	{
	public:
		XmlModelInternal(void);
		~XmlModelInternal(void);

		//
		// Create XML document based on the given model
		//
		void createXmlNode(AIMXML::CAIMXML& xmlDoc, Annotation* pAnnotation);

		//
		// Craete XML document 
		void createXmlNodes(AIMXML::CAIMXML& xmlDoc, const AnnotationPtrVector& aAnnotations);

		//
		// Reading XML document back into the model
		//
		ImageAnnotation* readXmlNodeImageAnnotation(AIMXML::CImageAnnotation& xmlImgAnnotation);
		AnnotationOfAnnotation* readXmlNodeAnnotationOfAnnotation(AIMXML::CAnnotationOfAnnotation& xmlAnnOfAnnotation);

	protected:
		//
		// Create XML document based on the given model
		//
		void createXmlNodeImageAnnotation(AIMXML::CImageAnnotation& xmlAnnotation, const ImageAnnotation& imageAnnotation);
		void createXmlNodeAnnotationOfAnnotation(AIMXML::CAnnotationOfAnnotation xmlAnnotation, const AnnotationOfAnnotation& annAnnotation);
		

		void createXmlNode(AIMXML::CanatomicEntityCollectionType& xmlParent, const AnatomicEntity& anatomicEntity);
		void createXmlNode(AIMXML::CanatomicEntityCharacteristicCollectionType& xmlParent, const AnatomicEntityCharacteristic& anatomicEntityCharacteristic);
		void createXmlNode(AIMXML::CimagingObservationCollectionType& xmlParent, const ImagingObservation& imagingObservation);
		void createXmlNode(AIMXML::CimagingObservationCharacteristicCollectionType& xmlParent, const ImagingObservationCharacteristic& imagingObsCharacteristic);

		// Quantification
		// A single class to deal with two similar types
		class CharacteristicQuantificationWrapper
		{
		public:
			CharacteristicQuantificationWrapper(AIMXML::CcharacteristicQuantificationCollectionType* cqct) : _cqct(cqct), _cqct2(NULL) {}
			CharacteristicQuantificationWrapper(AIMXML::CcharacteristicQuantificationCollectionType2* cqct2) : _cqct(NULL), _cqct2(cqct2) {}

			AIMXML::CCharacteristicQuantification appendSpecial(unsigned DesiredMemberIndex)
			{
				assert(_cqct != NULL || _cqct2 != NULL);

				if (_cqct != NULL)
					return AIMXML::CCharacteristicQuantification(_cqct->CharacteristicQuantification.appendSpecial(DesiredMemberIndex));
				return AIMXML::CCharacteristicQuantification(_cqct2->CharacteristicQuantification.appendSpecial(DesiredMemberIndex));
			}
			AIMXML::CCharacteristicQuantification last()
			{
				assert(_cqct != NULL || _cqct2 != NULL);

				if (_cqct != NULL)
					return AIMXML::CCharacteristicQuantification(_cqct->CharacteristicQuantification.last());
				return AIMXML::CCharacteristicQuantification(_cqct2->CharacteristicQuantification.last());
			}
			bool exists()
			{
				assert(_cqct != NULL || _cqct2 != NULL);

				if (_cqct != NULL)
					return _cqct->CharacteristicQuantification.exists();
				return _cqct2->CharacteristicQuantification.exists();
			}
			AIMXML::Iterator<AIMXML::CCharacteristicQuantification> all()
			{
				assert(_cqct != NULL || _cqct2 != NULL);

				if (_cqct != NULL)
					return _cqct->CharacteristicQuantification.all();
				return _cqct2->CharacteristicQuantification.all();
			}
		private:
			AIMXML::CcharacteristicQuantificationCollectionType* _cqct;
			AIMXML::CcharacteristicQuantificationCollectionType2* _cqct2;
		};

		void createXmlNode(CharacteristicQuantificationWrapper& parentObj, const CharacteristicQuantification& charQuantification);

		// Calculations' collections
		void createXmlNode(AIMXML::CcalculationCollectionType& xmlParent, const Calculation& calculation);
		void createXmlNode(AIMXML::CreferencedCalculationCollectionType& xmlParent, const ReferencedCalculation& refCalculation);
		void createXmlNode(AIMXML::CreferencedGeometricShapeCollectionType& xmlParent, const ReferencedGeometricShape& refGeoShape);
		void createXmlNode(AIMXML::CcalculationResultCollectionType& xmlParent, const CalculationResult& calcResult);
		void createXmlNode(AIMXML::CdimensionCollectionType& xmlParent, const Dimension& dimension);
		void createXmlNode(AIMXML::CcalculationDataCollectionType& xmlParent, const CalculationData& data);
		void createXmlNode(AIMXML::CcoordinateCollectionType& xmlParent, const Coordinate& coordinate);
		// Text Annotation collection
		void createXmlNode(AIMXML::CtextAnnotationCollectionType& xmlParent, const TextAnnotation& textAnnotation);
		// SpatialCoordinate collection
		void createXmlNode(AIMXML::CspatialCoordinateCollectionType& xmlParent, const SpatialCoordinate& spatialCoordinate);
		// Geometric Shape collection
		void createXmlNode(AIMXML::CgeometricShapeCollectionType& xmlParent, const GeometricShape& geometricShape);
		// Image Reference collections
		void createXmlNode(AIMXML::CimageReferenceCollectionType& xmlParent, const ImageReference& imageReference);
		void createXmlNode(AIMXML::CimageCollectionType& xmlParent, const Image& image);
		void createXmlNode(AIMXML::CpresentationStateCollectionType& xmlParent, const PresentationState& presentationState);
		// Segmentation collection
		void createXmlNode(AIMXML::CsegmentationCollectionType& xmlParent, const Segmentation& segmentation);
		// Inference collection
		void createXmlNode(AIMXML::CinferenceCollectionType& xmlParent, const Inference& inference);
		// Referenced Annotation collection
		void createXmlNode(AIMXML::CreferencedAnnotationCollectionType& xmlParent, const ReferencedAnnotation& referencedAnnotation);
		// Single classes
		void createXmlNode(AIMXML::CuserType& xmlParent, const User* pUser);
		void createXmlNode(AIMXML::CequipmentType& xmlParent, const Equipment* pEquipment);
		void createXmlNode(AIMXML::CaimStatusType& xmlParent, const AimStatus* pAimStatus);


		//
		// Reading XML document back into the model
		//
		// Collections
		const AnatomicEntityVector readXmlNode(AIMXML::CanatomicEntityCollectionType& xmlAnatomicEntities);
		const AnatomicEntityCharacteristicVector readXmlNode(AIMXML::CanatomicEntityCharacteristicCollectionType& xmlAnatomicEntityCharacteristics);
		const ImagingObservationVector readXmlNode(AIMXML::CimagingObservationCollectionType& xmlImagingObservations);
		const ImagingObservationCharacteristicVector readXmlNode(AIMXML::CimagingObservationCharacteristicCollectionType& xmlImagingObsCharacteristics);
		const ImageReferencePtrVector readXmlNode(AIMXML::CimageReferenceCollectionType& xmlImageReferences);
		const ImageVector readXmlNode(AIMXML::CimageCollectionType& xmlImages);
		const PresentationStateVector readXmlNode(AIMXML::CpresentationStateCollectionType& xmlPresentationStates);
		const CalculationVector readXmlNode(AIMXML::CcalculationCollectionType& xmlCalculations);
		const CalcResultVector readXmlNode(AIMXML::CcalculationResultCollectionType& xmlCalculationResults);
		const ReferencedCalcVector readXmlNode(AIMXML::CreferencedCalculationCollectionType& xmlReferencedCalculations);
		const ReferencedGeometricShapeVector readXmlNode(AIMXML::CreferencedGeometricShapeCollectionType& xmlReferencedGeoShapes);
		const CalculationDataVector readXmlNode(AIMXML::CcalculationDataCollectionType& xmlDatas);
		const DimensionVector readXmlNode(AIMXML::CdimensionCollectionType& xmlDimensions);
		const CoordinateVector readXmlNode(AIMXML::CcoordinateCollectionType& xmlCoordinates);
		const ReferencedAnnotationVector readXmlNode(AIMXML::CreferencedAnnotationCollectionType& xmlReferencedAnnotations);
		const TextAnnotationVector readXmlNode(AIMXML::CtextAnnotationCollectionType& xmlReferencedAnnotations);
		const SegmentationVector readXmlNode(AIMXML::CsegmentationCollectionType& xmlSegmentations);
		const InferenceVector readXmlNode(AIMXML::CinferenceCollectionType& xmlInferences);
		const GeoShapePtrVector readXmlNode(AIMXML::CgeometricShapeCollectionType& xmlGeometricShapes);
		const SpatialCoordPtrVector readXmlNode(AIMXML::CspatialCoordinateCollectionType& xmlSpatialCoordinates);
		// Single classes
		const User readXmlNode(AIMXML::CUser& xmlUser);
		const Equipment readXmlNode(AIMXML::CEquipment& xmlEquipment);
		const AimStatus readXmlNode(AIMXML::CAimStatus& xmlAimStatus);
		// Characteristic Quantifications
		const CharacteristicQuantificationPtrVector readXmlNode(CharacteristicQuantificationWrapper& parentObj);
		const Numerical readXmlNode(AIMXML::CNumerical& xmlNumerical) const;
		const Quantile readXmlNode(AIMXML::CQuantile& xmlQuantile) const;
		const NonQuantifiable readXmlNode(AIMXML::CNonQuantifiable& xmlNonQuantifiable) const;
		const Scale readXmlNode(AIMXML::CScale& xmlScale) const;
		const Interval readXmlNode(AIMXML::CInterval& xmlInterval) const;
		void readXmlNode(CharacteristicQuantification& charQuantification, AIMXML::CCharacteristicQuantification& xmlCharQuantification) const;
//		const ImageView readXmlNode(AIMXML::CImageView& xmlImageView);
//		const CodeSequence readXmlNode(AIMXML::CCodeSequence& xmlCodeSequence);


		// Helpers
		// Reads xsi:type attribute of the given node. Node ex: <GeomatricShape xsi:type="Circle">
		const std::string GetSubClassType(xercesc::DOMNode* pNode);

	};
}

#endif // XmlModelInternal