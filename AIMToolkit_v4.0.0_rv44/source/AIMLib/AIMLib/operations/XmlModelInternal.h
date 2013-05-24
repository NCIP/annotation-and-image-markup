/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

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
		void createXmlNode(AIMXML::CAIMXML& xmlDoc, AnnotationCollection* pAnnotationCollection);

		//
		// Reading XML document back into the model
		//
		ImageAnnotationCollection* readXmlNodeImageAnnotationCollection(AIMXML::CImageAnnotationCollection& xmlImgAnnotationCollection);
		AnnotationOfAnnotationCollection* readXmlNodeAnnotationOfAnnotationCollection(AIMXML::CAnnotationOfAnnotationCollection& xmlAnnOfAnnotationCollection);

	protected:
		//
		// Create XML document based on the given model
		//
		void populateXmlNode(AIMXML::CImageAnnotationCollection& xmlAnnotationColl, const ImageAnnotationCollection& imageAnnotationColl);
		void populateXmlNode(AIMXML::CAnnotationOfAnnotationCollection& xmlAnnotationColl, const AnnotationOfAnnotationCollection& annAnnOfAnnColl);
		void populateXmlNode(AIMXML::CAnnotationCollection& xmlAnnotationColl, const AnnotationCollection& annAnnotationColl);
		
		void populateXmlNode(AIMXML::CAnnotationEntity& xmlAnnotationEntity, const AnnotationEntity& annotationEntity);
		void createXmlNode(AIMXML::CimageAnnotationsType& xmlParent, const ImageAnnotation& imgAnnotation);
		void createXmlNode(AIMXML::CannotationOfAnnotationsType& xmlParent, const AnnotationOfAnnotation& annotationOfAnnotation);

		void createXmlNode(AIMXML::CimagingPhysicalEntityCollectionType& xmlParent, const ImagingPhysicalEntity& imagingPhysEntity);
		void createXmlNode(AIMXML::CimagingPhysicalEntityCharacteristicCollectionType& xmlParent, const ImagingPhysicalEntityCharacteristic& imagingPhysEntChar);
		void createXmlNode(AIMXML::CimagingObservationEntityCollectionType& xmlParent, const ImagingObservationEntity& imagingObsEntity);
		void populateXmlNode(AIMXML::CImagingObservationCharacteristic& xmlImgObsChar, const ImagingObservationCharacteristic& imagingObjChar);

		void createXmlNode(AIMXML::CinferenceEntityCollectionType& xmlParent, const InferenceEntity& inferenceEntity);

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
		void populateXmlNode(AIMXML::CCharacteristicQuantification& xmlCharQuantification, const CharacteristicQuantification& charQuantification);

		// Calculations' collections
		void createXmlNode(AIMXML::CcalculationEntityCollectionType& xmlParent, const CalculationEntity& calculation);
		void populateXmlNode(AIMXML::CAlgorithm& xmlAlgorithm, const Algorithm& algorithm);
		void createXmlNode(AIMXML::CparameterCollectionType& xmlParent, const Parameter& parameter);
		void createXmlNode(AIMXML::CcalculationResultCollectionType& xmlParent, const CalculationResult* calcResult);
		void populateXmlNode(AIMXML::CCalculationResult& xmlCalcResult, const CalculationResult& calcResult);
		void populateXmlNode(AIMXML::CCompactCalculationResult& xmlCompactCalcResult, const CompactCalculationResult& compactCalcResult);
		void populateXmlNode(AIMXML::CExtendedCalculationResult& xmlExtCalcResult, const ExtendedCalculationResult& extCalcResult);
		void createXmlNode(AIMXML::CdimensionCollectionType& xmlParent, const Dimension& dimension);
		void createXmlNode(AIMXML::CcalculationDataCollectionType& xmlParent, const CalculationData& data);
		void createXmlNode(AIMXML::CcoordinateCollectionType& xmlParent, const Coordinate& coordinate);

		// Lesion Observations
		void createXmlNode(AIMXML::ClesionObservationEntityCollectionType& xmlParent, const LesionObservationEntity* pLesionObsEntity);
		void populateXmlNode(AIMXML::CLesionObservationEntity& xmlLesionObsEntity, const LesionObservationEntity& lesionObsEntity);
		void populateXmlNode(AIMXML::CGeneralLesionObservationEntity& xmlGenLesionObsEnt, const GeneralLesionObservationEntity& genLesionObsEntity);
		void populateXmlNode(AIMXML::CTimePointLesionObservationEntity& xmlTimePointLesionObsEnt, const TimePointLesionObservationEntity& timepointLesionObsEntity);

		void populateXmlNode(AIMXML::CTaskContextEntity& xmlTaskContextEntity, const TaskContextEntity& taskContextEntity);
		void createXmlNode(AIMXML::CannotationRoleEntityCollectionType& xmlParent, const AnnotationRoleEntity& annRoleEntity);
		void createXmlNode(AIMXML::CauditTrailCollectionType& xmlParent, const AuditTrail& auditTrail);

		void createXmlNode(AIMXML::CsegmentationEntityCollectionType& xmlParent, const SegmentationEntity* pSegmentationEntity);

		// Markups
		void createXmlNode(AIMXML::CmarkupEntityCollectionType& xmlParent, const MarkupEntity* pMarkupEntity);
		void populateXmlNode(AIMXML::CTextAnnotationEntity& xmlTextAnnEntity, const TextAnnotationEntity& textAnnEntity);
		void populateXmlNode(AIMXML::CGeometricShapeEntity& xmlGeoShapeEntity, const GeometricShapeEntity& geoShapeEntity);
		void populateXmlNode(AIMXML::CTwoDimensionGeometricShapeEntity& xmlGeoShapeEntity2D, const TwoDimensionGeometricShapeEntity& geoShapeEntity2D);
		void populateXmlNode(AIMXML::CThreeDimensionGeometricShapeEntity& xmlGeoShapeEntity3D, const ThreeDimensionGeometricShapeEntity& geoShapeEntity3D);
		AIMXML::_altova_typeinfo_indices getShapeNodeType(const TwoDimensionGeometricShapeEntity* pGeoShapeEntity2D);
		AIMXML::_altova_typeinfo_indices getShapeNodeType(const ThreeDimensionGeometricShapeEntity* pGeoShapeEntity3D);

		// Annotation Statements
		void createXmlNode(AIMXML::CimageAnnotationStatementCollectionType& xmlParent, const AnnotationStatement* pAnnStmt);
		void createXmlNode(AIMXML::CannotationOfAnnotationStatementCollectionType& xmlParent, const AnnotationStatement* pAnnStmt);
		AIMXML::_altova_typeinfo_indices getAnnotationStatementNodeType(const AnnotationStatement* pAnnStmt);

		// Image References
		void createXmlNode(AIMXML::CimageReferenceEntityCollectionType& xmlParent, const ImageReferenceEntity* pImageRefEntity);
		void populateXmlNode(AIMXML::CImageStudy& xmlImageStudy, const ImageStudy& imageStudy);
		void populateXmlNode(AIMXML::CImageSeries& xmlImageSeries, const ImageSeries& imageSeries);
		void createXmlNode(AIMXML::CimageCollectionType& xmlParent, const Image& image);
		void createXmlNode(AIMXML::CreferencedDicomObjectCollectionType& xmlParent, const ReferencedDicomObject& refDicomObj);
		
		void populateXmlNode(AIMXML::CAdjudicationObservation& xmlAdjudicationObs, const AdjudicationObservation& adjudicationObs);

		void populateXmlNode(AIMXML::CUser& xmlParent, const User& user);
		void populateXmlNode(AIMXML::CEquipment& xmlParent, const Equipment& equipment);
		void populateXmlNode(AIMXML::CPerson& xmlParent, const Person& person);

		void populateXmlNode(AIMXML::iso::CST& isoStr, const std::string& strVal);
		void populateXmlNode(AIMXML::iso::CBL& isoBool, const bool boolVal);
		void populateXmlNode(AIMXML::iso::CINT& isoInt, const int intVal);
		void populateXmlNode(AIMXML::iso::CREAL& isoReal, const double dblVal);
		void populateXmlNode(AIMXML::iso::CTS& isoTs, const aim_lib::DateTime& dtVal);
		void populateXmlNode(AIMXML::iso::CTS& isoTs, const aim_lib::Date& dateVal);
		void populateXmlNode(AIMXML::iso::CTS& isoTs, const aim_lib::Time& timeVal);
		void populateXmlNode(AIMXML::iso::CCD& isoCd, const iso_21090::CD& cdVal);
		void populateXmlNode(AIMXML::iso::CII& isoII, const iso_21090::II& iiVal);


		//
		// Reading XML document back into the model
		//
		void readXmlNode(AnnotationCollection& annotationCollection, AIMXML::CAnnotationCollection& xmlAnnColl);
		void readXmlNode(AnnotationEntity& annotationEntity, AIMXML::CAnnotationEntity& xmlAnnEntity);
		// Collections
		const ImageAnnotationVector readXmlNode(AIMXML::CimageAnnotationsType& xmlImageAnnotations);
		const AnnotationOfAnnotationVector readXmlNode(AIMXML::CannotationOfAnnotationsType& xmlAnnOfAnnotations);
		const ImagingPhysicalEntityVector readXmlNode(AIMXML::CimagingPhysicalEntityCollectionType& xmlImgPhysEntities);
		const ImagingPhysicalEntityCharacteristicVector readXmlNode(AIMXML::CimagingPhysicalEntityCharacteristicCollectionType& xmlImgPhysEntityChars);
		const ImagingObservationEntityVector readXmlNode(AIMXML::CimagingObservationEntityCollectionType& xmlImagingObsEntities);
		const ImagingObservationCharacteristicVector readXmlNode(AIMXML::CimagingObservationCharacteristicCollectionType& xmlImagingObsCharacteristics);
		const ImagingObservationCharacteristicVector readXmlNode(AIMXML::CimagingObservationCharacteristicCollectionType2& xmlImagingObsCharacteristics);
		const ImagingObservationCharacteristic readXmlNode(AIMXML::CImagingObservationCharacteristic& xmlImgObsChar);
		const CharacteristicQuantificationPtrVector readXmlNode(AIMXML::CcharacteristicQuantificationCollectionType& xmlCharQuantifications);
		const CharacteristicQuantificationPtrVector readXmlNode(AIMXML::CcharacteristicQuantificationCollectionType2& xmlCharQuantifications);
		CharacteristicQuantification* readXmlNode(AIMXML::CCharacteristicQuantification& xmlCharQuantification);
		const InferenceEntityVector readXmlNode(AIMXML::CinferenceEntityCollectionType& xmlInferenceEntities);
		const AnnotationRoleEntityVector readXmlNode(AIMXML::CannotationRoleEntityCollectionType& xmlAnnotationRoleEntities);
		const TaskContextEntityVector readXmlNode(AIMXML::CtaskContextEntityCollectionType& xmlTaskContextEntities);
		const TaskContextEntityVector readXmlNode(AIMXML::CtaskContextEntityCollectionType2& xmlTaskContextEntities);
		const TaskContextEntity readXmlNode(AIMXML::CTaskContextEntity& xmlTaskContextEntity);
		const AuditTrailVector readXmlNode(AIMXML::CauditTrailCollectionType& xmlAuditTrails);
		const CalculationEntityVector readXmlNode(AIMXML::CcalculationEntityCollectionType& xmlCalculationEntities);
		const Algorithm readXmlNode(AIMXML::CAlgorithm& xmlAlgorithm);
		const ParameterVector readXmlNode(AIMXML::CparameterCollectionType& xmlParameters);
		const CalculationResultPtrVector readXmlNode(AIMXML::CcalculationResultCollectionType& xmlCalculationResults);
		const DimensionVector readXmlNode(AIMXML::CdimensionCollectionType& xmlDimensions);
		const CalculationDataVector readXmlNode(AIMXML::CcalculationDataCollectionType& xmlCalcData);
		const CoordinateVector readXmlNode(AIMXML::CcoordinateCollectionType& xmlCoordiantes);
		const LesionObservationEntityPtrVector readXmlNode(AIMXML::ClesionObservationEntityCollectionType& xmlLesionObsEntities);
		const SegmentationEntityPtrVector readXmlNode(AIMXML::CsegmentationEntityCollectionType& xmlSegmentationEntities);
		const MarkupEntityPtrVector readXmlNode(AIMXML::CmarkupEntityCollectionType& xmlMarkupEntities);
		const TextAnnotationEntity readXmlNode(AIMXML::CTextAnnotationEntity& xmlTextAnnEntity);
		GeometricShapeEntity* readXmlNode(AIMXML::CMarkupEntity& xmlMarkupEntity);
		void readXmlNode(TwoDimensionGeometricShapeEntity& twoDimGeoShapeEntity, AIMXML::CTwoDimensionGeometricShapeEntity& xmlTwoDimGeoShapeEntity);
		void readXmlNode(ThreeDimensionGeometricShapeEntity& threeDimGeoShapeEntity, AIMXML::CThreeDimensionGeometricShapeEntity& xmlThreeDimGeoShapeEntity);
		const ImageReferenceEntityPtrVector readXmlNode(AIMXML::CimageReferenceEntityCollectionType& xmlImageRefereneceEntities);
		const ImageStudy readXmlNode(AIMXML::CImageStudy& xmlImageStudy);
		const ImageSeries readXmlNode(AIMXML::CImageSeries& xmlImageSeries);
		const ReferencedDicomObjectVector readXmlNode(AIMXML::CreferencedDicomObjectCollectionType& xmlRefDicomObjects);
		const ImageVector readXmlNode(AIMXML::CimageCollectionType& xmlImages);
		const ImageAnnotationStatementPtrVector readXmlNode(AIMXML::CimageAnnotationStatementCollectionType& xmlImgAnnStatements);
		const AnnotationOfAnnotationStatementPtrVector readXmlNode(AIMXML::CannotationOfAnnotationStatementCollectionType& xmlAnnOfAnnStatements);
		// Single classes
		const AdjudicationObservation readXmlNode(AIMXML::CAdjudicationObservation& xmlAdjudicationObs);
		const User readXmlNode(AIMXML::CUser& xmlUser);
		const Equipment readXmlNode(AIMXML::CEquipment& xmlEquipment);
		const Person readXmlNode(AIMXML::CPerson& xmlPerson);

		// Helpers
		// Reads xsi:type attribute of the given node. Node ex: <GeomatricShape xsi:type="Circle">
		const std::string GetSubClassType(xercesc::DOMNode* pNode);

		const iso_21090::II readXmlNode(AIMXML::iso::CII xmlIi);
		const iso_21090::CD readXmlNode(AIMXML::iso::CCD xmlCd);
		const iso_21090::CDVector readXmlNode(AIMXML::Iterator<AIMXML::iso::CCD> xmlCdIter);
		const std::string readXmlNode(AIMXML::iso::CST xmlSt);
		const std::vector<std::string> readXmlNode(AIMXML::Iterator<AIMXML::iso::CST> xmlStIter);
		const bool readXmlNode(AIMXML::iso::CBL xmlBl);
		const int readXmlNode(AIMXML::iso::CINT xmlInt);
		const double readXmlNode(AIMXML::iso::CREAL xmlReal);
		const DateTime xmlNodeToDateTime(AIMXML::iso::CTS xmlTs);
		const Date xmlNodeToDate(AIMXML::iso::CTS xmlTs);
		const Time xmlNodeToTime(AIMXML::iso::CTS xmlTs);
	};
}

#endif // XmlModelInternal