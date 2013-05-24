/*
  Classname: User

*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#if !defined(EA_D31E12FB_FB6A_4632_B904_B4EE9BD17484__INCLUDED_)
#define EA_D31E12FB_FB6A_4632_B904_B4EE9BD17484__INCLUDED_

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
		int _cagridId;
		std::string _name; // DICOM Pname
		std::string _loginName;
		std::string _roleInTrial;
		int	_numberWithinRoleOfClinicalTrial;
	};
}
#endif // !defined(EA_D31E12FB_FB6A_4632_B904_B4EE9BD17484__INCLUDED_)
