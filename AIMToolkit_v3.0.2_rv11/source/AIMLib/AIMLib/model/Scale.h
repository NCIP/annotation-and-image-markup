/*
  Classname: Scale

*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#if !defined(_AIMLib_Scale_Class)
#define _AIMLib_Scale_Class

#include <string>

namespace aim_lib
{
	class AIMLIB_API Scale : public CharacteristicQuantification
	{
	public:
		Scale(void);
		Scale(const Scale& scale);
		virtual ~Scale(void);
		Scale& operator=(const Scale& scale);
		virtual Scale* Clone() const;

		const std::string& GetValue() const;
		const std::string& GetComment() const;
		const std::string& GetDescription() const;
		void SetValue(const std::string& newVal);
		void SetComment(const std::string& newVal);
		void SetDescription(const std::string& newVal);

	protected:
		std::string _value;
		std::string _comment;
		std::string _description;
	};
}
#endif // _AIMLib_Scale_Class
