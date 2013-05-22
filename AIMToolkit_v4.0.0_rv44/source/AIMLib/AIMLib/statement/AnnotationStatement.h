/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
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
