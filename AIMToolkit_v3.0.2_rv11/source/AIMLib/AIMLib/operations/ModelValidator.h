/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#if !defined(_AIMLib_ModelValidator_Class)
#define _AIMLib_ModelValidator_Class

#include <string>
#include <vector>

namespace aim_lib
{
	class ModelValidator
	{
	public:
		ModelValidator(void);
		~ModelValidator(void);

		bool isValid(const ImageAnnotation& imgAnnotation);
		bool isValid(const AnnotationOfAnnotation& annOfAnnotation);

		// List of errors recorded during validation
		const std::vector<std::string>& GetValidationErrors();

	protected:
		bool isValid(const Annotation& annotation, bool allowDefaults = false);
		bool isValid(const AnatomicEntity& anatomicEntity, bool allowDefaults = false);
		bool isValid(const AnatomicEntityCharacteristic& anatomicEntityChar, bool allowDefaults = false);
		bool isValid(const ImagingObservation& imagingObservation, bool allowDefaults = false);
		bool isValid(const ImagingObservationCharacteristic& imagingObsChar, bool allowDefaults = false);
		bool isValid(const Equipment& equipment, bool allowDefaults = false);
		bool isValid(const User& user, bool allowDefaults = false);
		bool isValid(const Person& patient, bool allowDefaults = false);
		bool isValid(const Inference& inference, bool allowDefaults = false);
		bool isValid(const TextAnnotation& textAnnotation, bool allowDefaults = false);
		bool isValid(const Segmentation& segmentation, bool allowDefaults = false);
		bool isValid(const GeometricShape& geoShape, bool allowDefaults = false);
		bool isValid(const SpatialCoordinate& spatialCoordinate, bool allowDefaults = false);
		bool isValid(const AimStatus& aimStatus, bool allowDefaults = false);

		bool isValid(const CharacteristicQuantification& characteristicQuantification, bool allowDefaults = false);
		bool isValid(const Numerical& numerical, bool allowDefaults = false);
		bool isValid(const Quantile& quantile, bool allowDefaults = false);
		bool isValid(const NonQuantifiable& nonQuantifiable, bool allowDefaults = false);
		bool isValid(const Scale& scale, bool allowDefaults = false);
		bool isValid(const Interval& interval, bool allowDefaults = false);

		bool isValid(const Coordinate& coordinate, bool allowDefaults = false);
		bool isValid(const aim_lib::CalculationData& data, bool allowDefaults = false);
		bool isValid(const Dimension& dimension, bool allowDefaults = false);
		bool isValid(const CalculationResult& calcResult, bool allowDefaults = false);
		bool isValid(const ReferencedCalculation& referencedCalc, bool allowDefaults = false);
		bool isValid(const ReferencedGeometricShape& referencedGeoShape, bool allowDefaults = false);
		bool isValid(const Calculation& calculation, bool allowDefaults = false);

		bool isValid(const ImageReference& imageRef, bool allowDefaults = false);
		bool isValid(const ImageStudy& study, bool allowDefaults = false);
		bool isValid(const ImageSeries& series, bool allowDefaults = false);
		bool isValid(const Image& image, bool allowDefaults = false);
		bool isValid(const PresentationState& presentationState, bool allowDefaults = false);

		bool isValid(const ReferencedAnnotation& referencedAnnotation, bool allowDefaults = false);
		bool isValid(const AnnotationRole& annotationRole, bool allowDefaults = false);

		bool isValid(const Date& date, bool allowDefaults = false);
		bool isValid(const Time& time, bool allowDefaults = false);
		bool isValid(const DateTime& dateTime, bool allowDefaults = false);

		bool isUIDValid(const std::string& uid);

		std::vector<std::string> _errors;
	};
}

#endif //_AIMLib_ModelValidator_Class
