/*
  Classname: Equipment

*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#if !defined(_AIMLib_Equipment_Class)
#define _AIMLib_Equipment_Class

#include <string>

namespace aim_lib
{
	class AIMLIB_API Equipment
	{
	public:
		Equipment();
		Equipment(const Equipment& equipment);
		virtual ~Equipment();
		virtual Equipment* Clone() const;

		const std::string& GetManufacturerName() const;
		const std::string& GetManufacturerModelName() const;
		const std::string& GetSoftwareVersion() const;
		void SetManufacturerName(const std::string& newVal);
		void SetManufacturerModelName(const std::string& newVal);
		void SetSoftwareVersion(const std::string& newVal);

	private:
		int _cagridId;
		std::string _manufacturerName;
		std::string _manufacturerModelName;
		std::string _softwareVersion;
	};
}

#endif // _AIMLib_Equipment_Class