project (AIMLib_AIMLib)

# Set include directories for compiler
include_directories ("${CMAKE_CURRENT_SOURCE_DIR}")
include_directories ("${DCMTK_INCLUDE_DIRECTORIES}")
include_directories ("${XERCES_INCLUDE_DIR}")

# Define list of files to be compiled
set (AIMLIB_SRC
  AIMCodes.cpp
  AimEnum.cpp
  AIMLib.cpp
  AimResultValidator.cpp
  AIMUtil.cpp
  entity/AdjudicationObservation.cpp
  entity/Algorithm.cpp
  entity/AnnotationCollection.cpp
  entity/AnnotationEntity.cpp
  entity/AnnotationOfAnnotationCollection.cpp
  entity/AnnotationOfAnnotation.cpp
  entity/AnnotationRoleEntity.cpp
  entity/AuditTrail.cpp
  entity/CalculationData.cpp
  entity/CalculationEntity.cpp
  entity/CalculationResult.cpp
  entity/CharacteristicQuantification.cpp
  entity/CompactCalculationResult.cpp
  entity/Coordinate.cpp
  entity/DicomImageReferenceEntity.cpp
  entity/DicomSegmentationEntity.cpp
  entity/Dimension.cpp
  entity/Entity.cpp
  entity/Equipment.cpp
  entity/ExtendedCalculationResult.cpp
  entity/GeneralImage.cpp
  entity/GeneralLesionObservationEntity.cpp
  entity/GeometricShapeEntity.cpp
  entity/ImageAnnotationCollection.cpp
  entity/ImageAnnotation.cpp
  entity/Image.cpp
  entity/ImagePlane.cpp
  entity/ImageReferenceEntity.cpp
  entity/ImageSeries.cpp
  entity/ImageStudy.cpp
  entity/ImagingObservationCharacteristic.cpp
  entity/ImagingObservationEntity.cpp
  entity/ImagingPhysicalEntityCharacteristic.cpp
  entity/ImagingPhysicalEntity.cpp
  entity/InferenceEntity.cpp
  entity/Interval.cpp
  entity/LesionObservationEntity.cpp
  entity/MarkupEntity.cpp
  entity/NonQuantifiable.cpp
  entity/Numerical.cpp
  entity/Parameter.cpp
  entity/Person.cpp
  entity/Quantile.cpp
  entity/ReferencedDicomObject.cpp
  entity/Scale.cpp
  entity/SegmentationEntity.cpp
  entity/TaskContextEntity.cpp
  entity/TextAnnotationEntity.cpp
  entity/ThreeDimensionEllipse.cpp
  entity/ThreeDimensionEllipsoid.cpp
  entity/ThreeDimensionGeometricShapeEntity.cpp
  entity/ThreeDimensionMultiPoint.cpp
  entity/ThreeDimensionPoint.cpp
  entity/ThreeDimensionPolygon.cpp
  entity/ThreeDimensionPolyline.cpp
  entity/ThreeDimensionSpatialCoordinate.cpp
  entity/TimePointLesionObservationEntity.cpp
  entity/TwoDimensionCircle.cpp
  entity/TwoDimensionEllipse.cpp
  entity/TwoDimensionGeometricShapeEntity.cpp
  entity/TwoDimensionMultiPoint.cpp
  entity/TwoDimensionPoint.cpp
  entity/TwoDimensionPolyline.cpp
  entity/TwoDimensionSpatialCoordinate.cpp
  entity/UriImageReferenceEntity.cpp
  entity/User.cpp
  external/CD.cpp
  external/II.cpp
  operations/BaseModel.cpp
  operations/DcmModel.cpp
  operations/DcmModelInternalRead.cpp
  operations/DcmModelInternalWrite.cpp
  operations/DicomTagCollection.cpp
  operations/ModelValidator.cpp
  operations/XmlModel.cpp
  operations/XmlModelInternalRead.cpp
  operations/XmlModelInternalWrite.cpp
  statement/StatementFactory.cpp
  util/AimUidGenerator.cpp
  util/DateTime.cpp
  )

# Set additional directory path for linker
link_directories ("${CMAKE_BINARY_DIR}/DCMTK-prefix/lib")

# Create a build target
add_library (${AIMLIB_LIBRARY} ${AIMLIB_SRC})

# Set the preprocessor symbol used for declspec import / export 
set_target_properties (${AIMLIB_LIBRARY} 
  PROPERTIES DEFINE_SYMBOL "AIMLIB_EXPORTS")

# Set shared library version, such as libAIM.so.4.0
set (AIM_SOVERSION "${AIM_VERSION_MAJOR}.${AIM_VERSION_MINOR}")
set_target_properties (${AIMLIB_LIBRARY} 
  PROPERTIES SOVERSION ${AIM_SOVERSION})

# Set list of libraries that AIMLib will be linked against
target_link_libraries (${AIMLIB_LIBRARY} 
  AIMXML AltovaXML Altova ${DCMTK_LIBRARIES})
target_link_libraries (${AIMLIB_LIBRARY} 
  debug ${XERCES_DEBUG_LIBRARIES})
target_link_libraries (${AIMLIB_LIBRARY} 
  optimized ${XERCES_RELEASE_LIBRARIES})

# Add AIMLib library into installer package
if (WIN32)
  # For windows, we package only dll, not lib
  install (TARGETS ${AIMLIB_LIBRARY} 
    RUNTIME DESTINATION bin COMPONENT Runtime)
else ()
  install (TARGETS ${AIMLIB_LIBRARY} 
    DESTINATION lib)
endif ()

# Make sure DCMTK target gets built before AIMLib target
add_dependencies (${AIMLIB_LIBRARY} DCMTK)
