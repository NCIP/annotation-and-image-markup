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
