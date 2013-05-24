/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#pragma once
#ifndef _AIMLib_GeneralLesionObservationEntity_Class_
#define _AIMLib_GeneralLesionObservationEntity_Class_

#include <string>
#include <memory>

namespace aim_lib
{
	class AIMLIB_API GeneralLesionObservationEntity : public LesionObservationEntity
	{
	public:
		GeneralLesionObservationEntity(void);
		GeneralLesionObservationEntity(const GeneralLesionObservationEntity& lesionObservationEntity);
		virtual ~GeneralLesionObservationEntity(void);
		GeneralLesionObservationEntity& operator=(const GeneralLesionObservationEntity& lesionObservationEntity);
		virtual GeneralLesionObservationEntity* Clone() const;

		const iso_21090::CD& GetLesionType() const;
		const std::string& GetTrackingIdentifier() const;
		const iso_21090::CD* GetLaterality() const;
		const iso_21090::CD* GetReconstructionInterval() const;

		void SetLesionType(const iso_21090::CD& newVal);
		void SetTrackingIdentifier(const std::string& newVal);
		void SetLaterality(const iso_21090::CD* newVal);
		void SetReconstructionInterval(const iso_21090::CD* newVal);
	protected:
		iso_21090::CD _lesionType;
		std::string _trackingIdentifier;
		std::auto_ptr<iso_21090::CD> _laterality;
		std::auto_ptr<iso_21090::CD> _reconstructionInterval;
	};
}
#endif // _AIMLib_GeneralLesionObservationEntity_Class_
