/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#pragma once
#ifndef _AIMLib_NonQuantifiable_Class_
#define _AIMLib_NonQuantifiable_Class_

#include <string>

namespace aim_lib
{
	class AIMLIB_API NonQuantifiable : public CharacteristicQuantification
	{
	public:
		NonQuantifiable(void);
		NonQuantifiable(const NonQuantifiable& nonQuantifiable);
		virtual ~NonQuantifiable(void);
		NonQuantifiable& operator=(const NonQuantifiable& nonQuantifiable);
		virtual NonQuantifiable* Clone() const;

		const QuantificationType GetQuantificationType() const;

		const iso_21090::CD& GetTypeCode() const;
		void SetTypeCode(const iso_21090::CD& newVal);

	protected:
		iso_21090::CD _typeCode;
	};
}
#endif // _AIMLib_NonQuantifiable_Class_
