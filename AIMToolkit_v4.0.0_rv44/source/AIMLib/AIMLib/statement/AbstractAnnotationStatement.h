/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#pragma once
#ifndef _AIMLib_AbstractAnnotationStatement_Class_
#define _AIMLib_AbstractAnnotationStatement_Class_

#include "AnnotationStatementRelationship.h"

namespace aim_lib
{
	// Annotation Statement declaration macro
#define AIM_STMT_DECL(name, subj_name, obj_name, rel_type, base) \
	class AIMLIB_API name : public base \
	{ \
	public: \
		name(void) : base(){} \
		name(const iso_21090::II& subjectUid, const iso_21090::II& objectUid) : base(objectUid, subjectUid){} \
		name(const name& statement) : base(statement){} \
		virtual name* Clone() const{ return new name(*this); } \
		virtual ~name(void){} \
		static AnnotationStatement* NewInstance() { return new name(); } \
		virtual const std::string& GetSubjectClassName() const { static const std::string _subj_name(#subj_name); return _subj_name; } \
		virtual const std::string& GetObjectClassName() const { static const std::string _obj_name(#obj_name); return _obj_name; } \
		/*virtual const std::string GetRelationshipName(){ return rel_type::GetRelationshipName(); }*/ \
		virtual const std::string& GetRelationshipName() const { static const std::string _rel_class_name(#rel_type); return _rel_class_name; } \
		virtual const std::string& GetStatementClassName() const { static const std::string _stmt_class_name(#name); return _stmt_class_name; } \
	};

	// Annotation statements
	AIM_STMT_DECL(AnnotationEntityHasPerformedTaskContextEntityStatement, AnnotationEntity, TaskContextEntity, HasPerformedAnnotationStatementRelationship, AnnotationStatement)
	AIM_STMT_DECL(AnnotationEntityHasPlannedTaskContextEntityStatement, AnnotationEntity, TaskContextEntity, HasPlannedAnnotationStatementRelationship, AnnotationStatement)
	AIM_STMT_DECL(CalculationEntityReferencesCalculationEntityStatement, CalculationEntity, CalculationEntity, ReferencesAnnotationStatementRelationship, AnnotationStatement)
	AIM_STMT_DECL(CalculationEntityUsesCalculationEntityStatement, CalculationEntity, CalculationEntity, UsesAnnotationStatementRelationship, AnnotationStatement)
	AIM_STMT_DECL(ImagingObservationEntityHasCalculationEntityStatement, ImagingObservationEntity, CalculationEntity, HasAnnotationStatementRelationship, AnnotationStatement)
	AIM_STMT_DECL(ImagingObservationEntityIsFoundInImagingPhysicalEntityStatement, ImagingObservationEntity, ImagingPhysicalEntity, IsFoundInAnnotationStatementRelationship, AnnotationStatement)
	AIM_STMT_DECL(ImagingPhysicalEntityHasCalculationEntityStatement, ImagingPhysicalEntity, CalculationEntity, HasAnnotationStatementRelationship, AnnotationStatement)
	AIM_STMT_DECL(ImagingPhysicalEntityHasImagingObservationEntityStatement, ImagingPhysicalEntity, ImagingObservationEntity, HasAnnotationStatementRelationship, AnnotationStatement)
}
#endif // _AIMLib_AbstractAnnotationStatement_Class_
