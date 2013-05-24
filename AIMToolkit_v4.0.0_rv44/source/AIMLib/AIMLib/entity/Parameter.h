/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#pragma once
#ifndef _AIMLib_Parameter_Class_
#define _AIMLib_Parameter_Class_

#include <string>
#include <vector>

namespace aim_lib
{
	class AIMLIB_API Parameter
	{
	public:
		Parameter(void);
		Parameter(const Parameter& parameter);
		virtual ~Parameter(void);

		const std::string& GetName() const;
		const std::string& GetValue() const;
		const iso_21090::CD& GetDataType() const;

		void SetName(const std::string& newVal);
		void SetValue(const std::string& newVal);
		void SetDataType(const iso_21090::CD& newVal);
	protected:
		std::string _name;
		std::string _value;
		iso_21090::CD _dataType;
	};

	typedef std::vector<Parameter> ParameterVector;
}
#endif // _AIMLib_Parameter_Class_