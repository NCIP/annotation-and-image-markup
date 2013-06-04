/*
  Classname: Person

*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#if !defined(_AIMLib_Person_Class)
#define _AIMLib_Person_Class

#include <string>
#include <ctime>

namespace aim_lib
{
	class AIMLIB_API Person
	{
	public:
		Person();
		Person(const Person& person);
		virtual ~Person(void);
		Person* Clone() const;

		const std::string& GetId() const;
		const std::string& GetName() const;
		const Date& GetBirthDate() const;
		const std::string& GetSex() const;
		const std::string& GetEthnicGroup() const;
		void SetId(const std::string& newVal);
		void SetName(const std::string& newVal);
		void SetBirthDate(const Date& newVal);
		void SetSex(const std::string& newVal);
		void SetEthnicGroup(const std::string& newVal);


	private:
		int _cagridId;
		std::string _id;
		std::string _name;
		Date _birthDate;
		std::string _sex;
		std::string _ethnicGroup;
	};
}

#endif // _AIMLib_Person_Class