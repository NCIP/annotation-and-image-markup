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
