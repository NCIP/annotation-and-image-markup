/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#pragma once
#ifndef _AIMLib_LesionObservationEntity_Class_
#define _AIMLib_LesionObservationEntity_Class_

#include <vector>
#include <memory>

namespace aim_lib
{
	class AIMLIB_API LesionObservationEntity : public Entity
	{
	public:
		virtual ~LesionObservationEntity(void);
		LesionObservationEntity& operator=(const LesionObservationEntity& lesionObservationEntity);
		virtual LesionObservationEntity* Clone() const = 0;

		const iso_21090::II& GetLesionUniqueIdentifier() const;
		bool* GetIsAdditionalObservation() const;

		void SetLesionUniqueIdentifier(const iso_21090::II& newVal);
		void SetIsAdditionalObservation(bool* newVal);
	protected:
		LesionObservationEntity(void);
		LesionObservationEntity(const LesionObservationEntity& lesionObservationEntity);

		iso_21090::II _lesionUniqueIdentifier;
		std::auto_ptr<bool> _isAdditionalObservation; // default: false
	};

	typedef std::vector<LesionObservationEntity*> LesionObservationEntityPtrVector;
}
#endif // _AIMLib_LesionObservationEntity_Class_
