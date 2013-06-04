/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#pragma once
#ifndef _AIMLib_Scale_Class_
#define _AIMLib_Scale_Class_

#include <string>

namespace aim_lib
{
	class AIMLIB_API Scale : public CharacteristicQuantification
	{
	public:
		enum ScaleType
		{
			InvalidScaleType = -2,
			Nominal = -1,
			Ordinal = 0,
			Ratio = 1,
		};

	public:
		Scale(void);
		Scale(const Scale& scale);
		virtual ~Scale(void);
		Scale& operator=(const Scale& scale);
		virtual Scale* Clone() const;

		const QuantificationType GetQuantificationType() const;

		const std::string& GetValue() const;
		const ScaleType GetScaleType() const;
		void SetValue(const std::string& newVal);
		void SetScaleType(ScaleType newVal);

		static const std::string ScaleTypeToString(const ScaleType& type);
		static const ScaleType StringToScaleType(const std::string& scaleType);

	protected:
		std::string _value;
		ScaleType _scaleType;
	};
}
#endif // _AIMLib_Scale_Class_
