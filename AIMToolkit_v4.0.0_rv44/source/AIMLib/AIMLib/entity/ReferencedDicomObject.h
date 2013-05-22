/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#pragma once
#ifndef _AIMLib_ReferencedDicomObject_Class_
#define _AIMLib_ReferencedDicomObject_Class_

#include <vector>

namespace aim_lib
{
	class AIMLIB_API ReferencedDicomObject
	{
	public:
		ReferencedDicomObject(void);
		ReferencedDicomObject(const ReferencedDicomObject& refDicomObject);
		virtual ~ReferencedDicomObject(void);
		ReferencedDicomObject& operator=(const ReferencedDicomObject& refDicomObject); // need to have it here; otherwise the auto_ptr template will break the build because of the const in the copy constructor
		ReferencedDicomObject* Clone() const;

		const iso_21090::CD& GetModality() const;
		const iso_21090::II& GetSopInstanceUid() const;

		void SetModality(const iso_21090::CD& newVal);
		void SetSopInstanceUid(const iso_21090::II& newVal);

	protected:
		iso_21090::CD _modality;     
		iso_21090::II _sopInstanceUid;
	};

	typedef std::vector<ReferencedDicomObject> ReferencedDicomObjectVector;
}
#endif // _AIMLib_ReferencedDicomObject_Class_
