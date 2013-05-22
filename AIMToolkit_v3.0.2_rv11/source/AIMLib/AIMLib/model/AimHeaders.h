/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

//////////////////////////////////
//Public Headers
//////////////////////////////////
#include "../AimEnum.h"
#include "AimBase.h"
#include "DateTime.h"
#include "User.h"
#include "Equipment.h"
#include "AimStatus.h"
#include "ReferencedGeometricShape.h"
#include "CharacteristicQuantification.h"
#include "Numerical.h"
#include "Quantile.h"
#include "NonQuantifiable.h"
#include "Scale.h"
#include "Interval.h"
#include "AnatomicEntityCharacteristic.h"
#include "AnatomicEntity.h"
#include "ImagingObservationCharacteristic.h"
#include "ImagingObservation.h"
#include "ImageReference.h"
#include "ReferencedCalculation.h"
#include "Dimension.h"
#include "Coordinate.h"
#include "CalculationData.h"
#include "CalculationResult.h"
#include "Calculation.h"
#include "Segmentation.h"
#include "Inference.h"
#include "Annotation.h"
#include "Person.h"
#include "WebImageReference.h"
#include "Image.h"
#include "ImageSeries.h"
#include "ImageStudy.h"
#include "PresentationState.h"
#include "DICOMImageReference.h"
#include "SpatialCoordinate.h"
#include "GeometricShape.h"
#include "Circle.h"
#include "Point.h"
#include "MultiPoint.h"
#include "Ellipse.h"
#include "Polyline.h"
#include "TextAnnotation.h"
#include "ImageAnnotation.h"
#include "AnnotationRole.h"
#include "ReferencedAnnotation.h"
#include "AnnotationOfAnnotation.h"

#include "TwoDimensionSpatialCoordinate.h"
#include "ThreeDimensionSpatialCoordinate.h"

#include "../util/AimUidGenerator.h"
