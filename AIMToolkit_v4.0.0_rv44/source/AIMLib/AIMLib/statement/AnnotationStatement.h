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
#ifndef _AIMLib_AnnotationStatement_Class_
#define _AIMLib_AnnotationStatement_Class_

#include <vector>

namespace aim_lib
{
	class AIMLIB_API AnnotationStatement
	{
	public:
		typedef AnnotationStatement* (*InstanceCreator)(void);

		virtual ~AnnotationStatement(void){
		}

		virtual AnnotationStatement* Clone() const = 0;
		virtual const std::string& GetSubjectClassName() const = 0;
		virtual const std::string& GetObjectClassName() const = 0;
		virtual const std::string& GetRelationshipName() const = 0;
		virtual const std::string& GetStatementClassName() const = 0;

		const iso_21090::II& GetSubjectUniqueIdentifier() const{
			return _subjectUniqueIdentifier;
		}

		const iso_21090::II& GetObjectUniqueIdentifier() const{
			return _objectUniqueIdentifier;
		}

		void SetSubjectUniqueIdentifier(const iso_21090::II& newVal){
			_subjectUniqueIdentifier = newVal;
		}

		void SetObjectUniqueIdentifier(const iso_21090::II& newVal){
			_objectUniqueIdentifier = newVal;
		}

	protected:
		AnnotationStatement(void){
		}

		AnnotationStatement(const iso_21090::II& subjectUid, const iso_21090::II& objectUid) :
			_subjectUniqueIdentifier(subjectUid), _objectUniqueIdentifier(objectUid) {
		}

		AnnotationStatement(const AnnotationStatement& statement){
			_subjectUniqueIdentifier	= statement._subjectUniqueIdentifier;
			_objectUniqueIdentifier		= statement._objectUniqueIdentifier;
		}

		iso_21090::II _subjectUniqueIdentifier;
		iso_21090::II _objectUniqueIdentifier;
	};
}
#endif // _AIMLib_AnnotationStatement_Class_
