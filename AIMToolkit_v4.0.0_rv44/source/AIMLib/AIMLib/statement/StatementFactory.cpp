/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"

#include "../AimHeaders.h"
#include "StatementFactory.h"

using namespace aim_lib;

// Macro for adding Statement classes to the factory
#define ADD_STMT_TO_FACTORY(name) { name stmt; theMap[#name] = &name::NewInstance; aliasMap[stmt.GetSubjectClassName() + stmt.GetRelationshipName() + stmt.GetObjectClassName()] = #name; }

bool StatementFactory::InitializeFactory()
{
	// NOTE: Every Statement must be added here

	StmtFactoryMap& theMap = GetStatementFactoryMap();
	StmtAliasMap& aliasMap = GetStatementAliasMap();

	// Annotation Statements
	ADD_STMT_TO_FACTORY(AnnotationEntityHasPerformedTaskContextEntityStatement)
	ADD_STMT_TO_FACTORY(AnnotationEntityHasPlannedTaskContextEntityStatement)
	ADD_STMT_TO_FACTORY(CalculationEntityReferencesCalculationEntityStatement)
	ADD_STMT_TO_FACTORY(CalculationEntityUsesCalculationEntityStatement)
	ADD_STMT_TO_FACTORY(ImagingObservationEntityHasCalculationEntityStatement)
	ADD_STMT_TO_FACTORY(ImagingObservationEntityIsFoundInImagingPhysicalEntityStatement)
	ADD_STMT_TO_FACTORY(ImagingPhysicalEntityHasCalculationEntityStatement)
	ADD_STMT_TO_FACTORY(ImagingPhysicalEntityHasImagingObservationEntityStatement)

	// Image Annotation Statements
	ADD_STMT_TO_FACTORY(DicomImageReferenceEntityHasCalculationEntityStatement)
	ADD_STMT_TO_FACTORY(DicomImageReferenceEntityHasImagingObservationEntityStatement)
	ADD_STMT_TO_FACTORY(DicomImageReferenceEntityHasImagingPhysicalEntityStatement)
	ADD_STMT_TO_FACTORY(DicomSegmentationEntityHasImagingObservationEntityStatement)
	ADD_STMT_TO_FACTORY(GeneralLesionObservationEntityHasImagingPhysicalEntityStatement)
	ADD_STMT_TO_FACTORY(ImageAnnotationHasCalculationEntityStatement)
	ADD_STMT_TO_FACTORY(ImageAnnotationHasChildImageAnnotationStatement)
	
	ADD_STMT_TO_FACTORY(ImageAnnotationHasDicomImageReferenceEntityStatement)
	ADD_STMT_TO_FACTORY(ImageAnnotationHasDicomSegmentationEntityStatement)
	ADD_STMT_TO_FACTORY(ImageAnnotationHasGeneralLesionObservationEntityStatement)
	ADD_STMT_TO_FACTORY(ImageAnnotationHasImagingObservationEntityStatement)
	ADD_STMT_TO_FACTORY(ImageAnnotationHasImagingPhysicalEntityStatement)
	ADD_STMT_TO_FACTORY(ImageAnnotationHasInferenceEntityStatement)
	ADD_STMT_TO_FACTORY(ImageAnnotationHasTextAnnotationEntityStatement)
	ADD_STMT_TO_FACTORY(ImageAnnotationHasThreeDimensionGeometricShapeEntityStatement)
	ADD_STMT_TO_FACTORY(ImageAnnotationHasTwoDimensionGeometricShapeEntityStatement)
	ADD_STMT_TO_FACTORY(ImageAnnotationHasTimePointLesionObservationEntityStatement)
	ADD_STMT_TO_FACTORY(ImageAnnotationHasUriImageReferenceEntityStatement)
	
	ADD_STMT_TO_FACTORY(ImagingObservationEntityIsIdentifiedByThreeDimensionGeometricShapeEntityStatement)
	ADD_STMT_TO_FACTORY(ImagingObservationEntityIsIdentifiedByTwoDimensionGeometricShapeEntityStatement)
	ADD_STMT_TO_FACTORY(ImagingObservationEntityIsIdentifiedByTextAnnotationEntityStatement)
	
	ADD_STMT_TO_FACTORY(ImagingPhysicalEntityHasThreeDimensionGeometricShapeEntityStatement)
	ADD_STMT_TO_FACTORY(ImagingPhysicalEntityHasTwoDimensionGeometricShapeEntityStatement)
	ADD_STMT_TO_FACTORY(ImagingPhysicalEntityHasTextAnnotationEntityStatement)
	
	ADD_STMT_TO_FACTORY(ThreeDimensionGeometricShapeEntityIsComprisedOfThreeDimensionGeometricShapeEntityStatement)
	ADD_STMT_TO_FACTORY(ThreeDimensionGeometricShapeEntityExcludesThreeDimensionGeometricShapeEntityStatement)
	
	ADD_STMT_TO_FACTORY(TimePointLesionObservationEntityHasImagingPhysicalEntityStatement)

	ADD_STMT_TO_FACTORY(TwoDimensionGeometricShapeEntityIsComprisedOfTwoDimensionGeometricShapeEntityStatement)
	ADD_STMT_TO_FACTORY(TwoDimensionGeometricShapeEntityExcludesTwoDimensionGeometricShapeEntityStatement)
	
	ADD_STMT_TO_FACTORY(UriImageReferenceEntityHasImagingObservationEntityStatement)
	ADD_STMT_TO_FACTORY(UriImageReferenceEntityHasImagingPhysicalEntityStatement)
	ADD_STMT_TO_FACTORY(UriImageReferenceEntityHasCalculationEntityStatement)

	// Annotation of Annotation Statements
	ADD_STMT_TO_FACTORY(AnnotationOfAnnotationHasAnnotationOfAnnotationStatement)
	ADD_STMT_TO_FACTORY(AnnotationOfAnnotationHasAnnotationRoleEntityStatement)
	ADD_STMT_TO_FACTORY(AnnotationOfAnnotationHasCalculationEntityStatement)
	ADD_STMT_TO_FACTORY(AnnotationOfAnnotationHasGeneralLesionObservationEntityStatement)
	ADD_STMT_TO_FACTORY(AnnotationOfAnnotationHasImageAnnotationStatement)
	ADD_STMT_TO_FACTORY(AnnotationOfAnnotationHasImagingObservationEntityStatement)
	ADD_STMT_TO_FACTORY(AnnotationOfAnnotationHasImagingPhysicalEntityStatement)
	ADD_STMT_TO_FACTORY(AnnotationOfAnnotationHasInferenceEntityStatement)
	ADD_STMT_TO_FACTORY(AnnotationOfAnnotationHasTimePointLesionObservationEntityStatement)
	ADD_STMT_TO_FACTORY(AnnotationOfAnnotationIsComparedWithAnnotationOfAnnotationStatement)
	ADD_STMT_TO_FACTORY(AnnotationOfAnnotationIsComparedWithImageAnnotationStatement)
	ADD_STMT_TO_FACTORY(CalculationEntityIsComparedWithCalculationEntityStatement)

	ADD_STMT_TO_FACTORY(ImageAnnotationHasAnnotationRoleEntityStatement)
	ADD_STMT_TO_FACTORY(ImageAnnotationIsComparedWithImageAnnotationStatement)
	ADD_STMT_TO_FACTORY(ImageAnnotationIsComparedWithAnnotationOfAnnotationStatement)

	return true;
}

AnnotationStatement* StatementFactory::Create(const std::string& stmtClassName)
{
	static bool isInit = StatementFactory::IsInitialized(); // make sure that maps are initialized
	const StmtFactoryMap& theMap = StatementFactory::GetStatementFactoryMap();

	StmtFactoryMap::const_iterator instanceInitializer = theMap.find(stmtClassName);
	if (instanceInitializer != theMap.end())
		return instanceInitializer->second();

	return NULL;
}

AnnotationStatement* StatementFactory::Create(const std::string& stmtSubjectClassName, const std::string& stmtObjectClassName, const std::string& stmtRelationshipClassName)
{
	static bool isInit = StatementFactory::IsInitialized(); // make sure that maps are initialized
	const StmtAliasMap& aliasMap = StatementFactory::GetStatementAliasMap();

	StmtAliasMap::const_iterator aliasIter = aliasMap.find(stmtSubjectClassName + stmtRelationshipClassName + stmtObjectClassName);
	if (aliasIter != aliasMap.end())
		return StatementFactory::Create(aliasIter->second);

	return NULL;
}

bool StatementFactory::IsInitialized()
{
	static bool isInitialized = StatementFactory::InitializeFactory();
	return isInitialized;
}

StatementFactory::StmtFactoryMap& StatementFactory::GetStatementFactoryMap()
{
	// Why local static map? See http://stackoverflow.com/questions/8057682/accessing-a-static-map-from-a-static-member-function-segmentation-fault-c
	static StmtFactoryMap theMap;
	return theMap;
}

StatementFactory::StmtAliasMap& StatementFactory::GetStatementAliasMap()
{
	static StmtAliasMap theMap;
	return theMap;
}
