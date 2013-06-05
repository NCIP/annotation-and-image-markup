/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#pragma once
#ifndef _AIMLib_AnnotationOfAnnotationStatement_Class_
#define _AIMLib_AnnotationOfAnnotationStatement_Class_

#include <vector>

namespace aim_lib
{
	class AIMLIB_API AnnotationOfAnnotationStatement : public AnnotationStatement
	{
	public:
		virtual ~AnnotationOfAnnotationStatement(void){
		}
	protected:
		AnnotationOfAnnotationStatement(void){
		}

		AnnotationOfAnnotationStatement(const iso_21090::II& subjectUid, const iso_21090::II& objectUid) : AnnotationStatement(subjectUid, objectUid){
		}

		AnnotationOfAnnotationStatement(const AnnotationOfAnnotationStatement& statement) : AnnotationStatement(statement){
		}
	};

	typedef std::vector<AnnotationStatement*> AnnotationOfAnnotationStatementPtrVector;

	class ImageAnnotation;
	class AnnotationOfAnnotation;

	// Using macro
	AIM_STMT_DECL(AnnotationOfAnnotationHasAnnotationOfAnnotationStatement, AnnotationOfAnnotation, AnnotationOfAnnotation, HasAnnotationStatementRelationship, AnnotationOfAnnotationStatement)
	AIM_STMT_DECL(AnnotationOfAnnotationHasAnnotationRoleEntityStatement, AnnotationOfAnnotation, AnnotationRoleEntity, HasAnnotationStatementRelationship, AnnotationOfAnnotationStatement)
	AIM_STMT_DECL(AnnotationOfAnnotationHasCalculationEntityStatement, AnnotationOfAnnotation, CalculationEntity, HasAnnotationStatementRelationship, AnnotationOfAnnotationStatement)
	AIM_STMT_DECL(AnnotationOfAnnotationHasGeneralLesionObservationEntityStatement, AnnotationOfAnnotation, GeneralLesionObservationEntity, HasAnnotationStatementRelationship, AnnotationOfAnnotationStatement)
	AIM_STMT_DECL(AnnotationOfAnnotationHasImageAnnotationStatement, AnnotationOfAnnotation, ImageAnnotation, HasAnnotationStatementRelationship, AnnotationOfAnnotationStatement)
	AIM_STMT_DECL(AnnotationOfAnnotationHasImagingObservationEntityStatement, AnnotationOfAnnotation, ImagingObservationEntity, HasAnnotationStatementRelationship, AnnotationOfAnnotationStatement)
	AIM_STMT_DECL(AnnotationOfAnnotationHasImagingPhysicalEntityStatement, AnnotationOfAnnotation, ImagingPhysicalEntity, HasAnnotationStatementRelationship, AnnotationOfAnnotationStatement)
	AIM_STMT_DECL(AnnotationOfAnnotationHasInferenceEntityStatement, AnnotationOfAnnotation, InferenceEntity, HasAnnotationStatementRelationship, AnnotationOfAnnotationStatement)
	AIM_STMT_DECL(AnnotationOfAnnotationHasTimePointLesionObservationEntityStatement, AnnotationOfAnnotation, TimePointLesionObservationEntity, HasAnnotationStatementRelationship, AnnotationOfAnnotationStatement)
	AIM_STMT_DECL(AnnotationOfAnnotationIsComparedWithAnnotationOfAnnotationStatement, AnnotationOfAnnotation, AnnotationOfAnnotation, IsComparedWithAnnotationStatementRelationship, AnnotationOfAnnotationStatement)
	AIM_STMT_DECL(AnnotationOfAnnotationIsComparedWithImageAnnotationStatement, AnnotationOfAnnotation, ImageAnnotation, IsComparedWithAnnotationStatementRelationship, AnnotationOfAnnotationStatement)
	AIM_STMT_DECL(CalculationEntityIsComparedWithCalculationEntityStatement, CalculationEntity, CalculationEntity, IsComparedWithAnnotationStatementRelationship, AnnotationOfAnnotationStatement)

	AIM_STMT_DECL(ImageAnnotationHasAnnotationRoleEntityStatement, ImageAnnotation, AnnotationRoleEntity, HasAnnotationStatementRelationship, AnnotationOfAnnotationStatement)
	AIM_STMT_DECL(ImageAnnotationIsComparedWithImageAnnotationStatement, ImageAnnotation, ImageAnnotation, IsComparedWithAnnotationStatementRelationship, AnnotationOfAnnotationStatement)
	AIM_STMT_DECL(ImageAnnotationIsComparedWithAnnotationOfAnnotationStatement, ImageAnnotation, AnnotationOfAnnotation, IsComparedWithAnnotationStatementRelationship, AnnotationOfAnnotationStatement)
}
#endif // _AIMLib_AnnotationOfAnnotationStatement_Class_
