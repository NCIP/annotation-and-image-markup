/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#pragma once
#ifndef _AIMLib_Algorithm_Class_
#define _AIMLib_Algorithm_Class_

#include <string>
#include <vector>
#include <memory>

namespace aim_lib
{
	class AIMLIB_API Algorithm
	{
	public:
		Algorithm(void);
		Algorithm(const Algorithm& algorithm);
		virtual ~Algorithm(void);

		const std::string& GetName() const;
		const iso_21090::CDVector& GetType() const;
		const iso_21090::II* GetUniqueIdentifier() const;
		const std::string& GetVersion() const;
		const std::string& GetDescription() const;
		const ParameterVector& GetParameterCollection() const;

		void SetName(const std::string& newVal);
		void SetType(const iso_21090::CDVector& newVal);
		void SetUniqueIdentifier(const iso_21090::II* newVal);
		void SetVersion(const std::string& newVal);
		void SetDescription(const std::string& newVal);
		void SetParameterCollection(const ParameterVector& parameters);
	protected:
		std::string _name;
		iso_21090::CDVector _type;
		std::auto_ptr<iso_21090::II> _uniqueIdentifier;
		std::string _version;
		std::string _description;

		ParameterVector _parameterCollection;
	};
}
#endif // _AIMLib_Algorithm_Class_