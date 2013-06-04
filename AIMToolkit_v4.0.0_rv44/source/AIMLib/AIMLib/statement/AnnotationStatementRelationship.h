/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#pragma once
#ifndef _AIMLib_AnnotationStatementRelationship_Class_
#define _AIMLib_AnnotationStatementRelationship_Class_

#include <cassert>

namespace aim_lib
{
	#define _stringify( name ) # name

	enum StatementRelationshipType
	{
		Excludes,
		Has,
		HasChild,
		HasPerformed,
		HasPlanned,
		References,
		Uses,
		IsComparedWith,
		IsComprisedOf,
		IsFoundIn,
		IsIdentifiedBy
	};

	template<StatementRelationshipType R>
	class AIMLIB_API AnnotationStatementRelationship
	{
	public:
		static const StatementRelationshipType GetRelationship(){
			return R;
		}

		static const std::string GetRelationshipName(){
			switch(AnnotationStatementRelationship<R>::GetRelationship())
			{
			case Excludes:
				return "Excludes";
			case Has:
				return "Has";
			case HasChild:
				return "HasChild";
			case HasPerformed:
				return "HasPerformed";
			case HasPlanned:
				return "HasPlanned";
			case References:
				return "References";
			case Uses:
				return "Uses";
			case IsComparedWith:
				return "IsComparedWith";
			case IsComprisedOf:
				return "IsComprisedOf";
			case IsFoundIn:
				return "IsFoundIn";
			case IsIdentifiedBy:
				return "IsIdentifiedBy";
			default:
				assert(false);
				return "Undefined";
			}
		}
	};

	// Defined relationships:
	typedef AnnotationStatementRelationship<Excludes> ExcludesAnnotationStatementRelationship;
	typedef AnnotationStatementRelationship<Has> HasAnnotationStatementRelationship;
	typedef AnnotationStatementRelationship<HasChild> HasChildAnnotationStatementRelationship;
	typedef AnnotationStatementRelationship<HasPerformed> HasPerformedAnnotationStatementRelationship;
	typedef AnnotationStatementRelationship<HasPlanned> HasPlannedAnnotationStatementRelationship;
	typedef AnnotationStatementRelationship<References> ReferencesAnnotationStatementRelationship;
	typedef AnnotationStatementRelationship<Uses> UsesAnnotationStatementRelationship;
	typedef AnnotationStatementRelationship<IsComparedWith> IsComparedWithAnnotationStatementRelationship;
	typedef AnnotationStatementRelationship<IsComprisedOf> IsComprisedOfAnnotationStatementRelationship;
	typedef AnnotationStatementRelationship<IsFoundIn> IsFoundInAnnotationStatementRelationship;
	typedef AnnotationStatementRelationship<IsIdentifiedBy> IsIdentifiedByAnnotationStatementRelationship;
}
#endif // _AIMLib_AnnotationStatementRelationship_Class_
