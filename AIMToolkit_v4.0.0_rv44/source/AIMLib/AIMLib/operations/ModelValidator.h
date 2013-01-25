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

		// Validate is the given Annotation Collection has all required elements
		// allowDefauls = true - will skip validation of optional model attributes
		bool isValid(const AnnotationCollection& annotationCollection, bool allowDefaults = false);

		// List of errors recorded during validation (reverse order)
		const std::vector<std::string>& GetValidationErrors(); // FIXME: errors are in the revers order for now

	protected:
		bool isValid(const ImageAnnotationCollection& imgAnnotationColl, bool allowDefaults = false);
		bool isValid(const AnnotationOfAnnotationCollection& annOfAnnotationColl, bool allowDefaults = false);
		bool isValid(const AnnotationEntity& annotationEntity, bool allowDefaults = false);
		bool isValid(const ImageAnnotation& imgAnnotation, bool allowDefaults = false);
		bool isValid(const AnnotationOfAnnotation& annotationofAnn, bool allowDefaults = false);
		bool isValid(const ImagingPhysicalEntity& imgPhysEntity, bool allowDefaults = false);
		bool isValid(const ImagingPhysicalEntityCharacteristic& imgPhysEntityChar, bool allowDefaults = false);
		bool isValid(const ImagingObservationEntity& imagingObservationEntity, bool allowDefaults = false);
		bool isValid(const ImagingObservationCharacteristic& imagingObsCharEntity, bool allowDefaults = false);
		bool isValid(const InferenceEntity& inferenceEntity, bool allowDefaults = false);
		bool isValid(const Equipment& equipment, bool allowDefaults = false);
		bool isValid(const User& user, bool allowDefaults = false);
		bool isValid(const Person& patient, bool allowDefaults = false);

		bool isValid(const SegmentationEntity* const pSegmentationEntity, bool allowDefaults = false);
		bool isValid(const MarkupEntity* const pMarkupEntity, bool allowDefaults = false);
		bool isValid(const TextAnnotationEntity& textAnnotationEntity, bool allowDefaults = false);
		bool isValid(const GeometricShapeEntity* const pGeoShapeEntity, bool allowDefaults = false);
		bool isValid(const TwoDimensionSpatialCoordinate& spatialCoordinate2d, bool allowDefaults = false);
		bool isValid(const ThreeDimensionSpatialCoordinate& spatialCoordinate3d, bool allowDefaults = false);

		bool isValid(const CharacteristicQuantification& characteristicQuantification, bool allowDefaults = false);
		bool isValid(const Numerical& numerical, bool allowDefaults = false);
		bool isValid(const Quantile& quantile, bool allowDefaults = false);
		bool isValid(const NonQuantifiable& nonQuantifiable, bool allowDefaults = false);
		bool isValid(const Scale& scale, bool allowDefaults = false);
		bool isValid(const Interval& interval, bool allowDefaults = false);

		bool isValid(const CalculationEntity& calcEntity, bool allowDefaults = false);
		bool isValid(const CalculationResult* const pCalcResult, bool allowDefaults = false);
		bool isValid(const CompactCalculationResult& compactCalcResult, bool allowDefaults = false);
		bool isValid(const ExtendedCalculationResult& extendedCalcResult, bool allowDefaults = false);
		bool isValid(const Coordinate& coordinate, bool allowDefaults = false);
		bool isValid(const aim_lib::CalculationData& data, bool allowDefaults = false);
		bool isValid(const Dimension& dimension, bool allowDefaults = false);
		bool isValid(const Algorithm& algorithm, bool allowDefaults = false);
		bool isValid(const Parameter& parameter, bool allowDefaults = false);

		bool isValid(const ImageReferenceEntity& imageRefEntity, bool allowDefaults = false);
		bool isValid(const ImageStudy& study, bool allowDefaults = false);
		bool isValid(const ImageSeries& series, bool allowDefaults = false);
		bool isValid(const Image& image, bool allowDefaults = false);
		bool isValid(const ReferencedDicomObject& refDicomObj, bool allowDefaults = false);
		bool isValid(const GeneralImage& generalImage, bool allowDefaults = false);
		bool isValid(const ImagePlane& imagePlane, bool allowDefaults = false);

		bool isValid(const TaskContextEntity& taskContextEntity, bool allowDefaults = false);
		bool isValid(const AnnotationRoleEntity& annotationRoleEntity, bool allowDefaults = false);
		bool isValid(const LesionObservationEntity* const lesionObsEntity, bool allowDefaults = false);
		bool isValid(const AuditTrail& auditTrail, bool allowDefaults = false);
		bool isValid(const AdjudicationObservation& adjudicationObs, bool allowDefaults = false);

		bool isValid(const AnnotationStatement& annotationStatement, bool allowDefaults = false);

		bool isValid(const Date& date, bool allowDefaults = false);
		bool isValid(const Time& time, bool allowDefaults = false);
		bool isValid(const DateTime& dateTime, bool allowDefaults = false);

		bool isValid(const iso_21090::CD& cd, bool allowDefaults = false);
		bool isValid(const iso_21090::CDVector& cdVector, bool allowDefaults = false);
		bool isValid(const iso_21090::II& ii, bool allowDefaults = false);
		bool isUIDValid(const std::string& uid);

		std::vector<std::string> _errors;
	};
}

#endif //_AIMLib_ModelValidator_Class