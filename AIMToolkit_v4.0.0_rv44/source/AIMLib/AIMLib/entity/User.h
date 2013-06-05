/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#pragma once
#ifndef _AIMLib_User_Class_
#define _AIMLib_User_Class_

#include <string>

namespace aim_lib
{
	class AIMLIB_API User
	{
	public:
		User();
		User(const User& user);
		virtual ~User();
		virtual User* Clone() const;

		const std::string& GetName() const;
		const std::string& GetLoginName() const;
		const std::string& GetRoleInTrial() const;
		int GetNumberWithinRoleOfClinicalTrial() const;
		void SetName(const std::string& newVal);
		void SetLoginName(const std::string& newVal);
		void SetRoleInTrial(const std::string& newVal);
		void SetNumberWithinRoleOfClinicalTrial(int newVal);

	private:
		std::string _name; // DICOM Pname
		std::string _loginName;
		std::string _roleInTrial;
		int	_numberWithinRoleOfClinicalTrial; // Default: -1
	};
}
#endif // _AIMLib_User_Class_
