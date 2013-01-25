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

#include "AimEnum.h"
#include "util/DateTime.h"

#include "entity/Entity.h"
#include "entity/AuditTrail.h"
#include "entity/CharacteristicQuantification.h"
#include "entity/Numerical.h"
#include "entity/Quantile.h"
#include "entity/NonQuantifiable.h"
#include "entity/Scale.h"
#include "entity/Interval.h"
#include "entity/ImagingObservationCharacteristic.h"
#include "entity/ImagingPhysicalEntityCharacteristic.h"
#include "entity/ImagingPhysicalEntity.h"
#include "entity/ImagingObservationEntity.h"
#include "entity/InferenceEntity.h"
#include "entity/Parameter.h"
#include "entity/Algorithm.h"
#include "entity/Dimension.h"
#include "entity/CalculationResult.h"
#include "entity/CalculationEntity.h"
#include "entity/CompactCalculationResult.h"
#include "entity/Coordinate.h"
#include "entity/CalculationData.h"
#include "entity/ExtendedCalculationResult.h"
#include "entity/AnnotationRoleEntity.h"
#include "entity/LesionObservationEntity.h"
#include "entity/GeneralLesionObservationEntity.h"
#include "entity/TimepointLesionObservationEntity.h"
#include "entity/TaskContextEntity.h"
#include "entity/AdjudicationObservation.h"
#include "entity/AnnotationEntity.h"
#include "entity/ReferencedDicomObject.h"
#include "entity/GeneralImage.h"
#include "entity/ImagePlane.h"
#include "entity/Image.h"
#include "entity/ImageSeries.h"
#include "entity/ImageStudy.h"
#include "entity/ImageReferenceEntity.h"
#include "entity/DicomImageReferenceEntity.h"
#include "entity/UriImageReferenceEntity.h"
#include "entity/MarkupEntity.h"
#include "entity/SegmentationEntity.h"
#include "entity/DicomSegmentationEntity.h"
#include "entity/GeometricShapeEntity.h"
#include "entity/TextAnnotationEntity.h"
#include "entity/TwoDimensionSpatialCoordinate.h"
#include "entity/TwoDimensionGeometricShapeEntity.h"
#include "entity/TwoDimensionEllipse.h"
#include "entity/TwoDimensionPoint.h"
#include "entity/TwoDimensionCircle.h"
#include "entity/TwoDimensionPolyline.h"
#include "entity/TwoDimensionMultiPoint.h"
#include "entity/ThreeDimensionSpatialCoordinate.h"
#include "entity/ThreeDimensionGeometricShapeEntity.h"
#include "entity/ThreeDimensionPoint.h"
#include "entity/ThreeDimensionEllipse.h"
#include "entity/ThreeDimensionEllipsoid.h"
#include "entity/ThreeDimensionPolyline.h"
#include "entity/ThreeDimensionPolygon.h"
#include "entity/ThreeDimensionMultiPoint.h"

#include "statement/AnnotationStatement.h"
#include "statement/AbstractAnnotationStatement.h"
#include "statement/AnnotationOfAnnotationStatement.h"
#include "statement/ImageAnnotationStatement.h"
#include "entity/ImageAnnotation.h"
#include "entity/AnnotationOfAnnotation.h"

#include "entity/User.h"
#include "entity/Equipment.h"
#include "entity/Person.h"
#include "entity/AnnotationCollection.h"
#include "entity/ImageAnnotationCollection.h"
#include "entity/AnnotationOfAnnotationCollection.h"

#include "util/AimUidGenerator.h"
