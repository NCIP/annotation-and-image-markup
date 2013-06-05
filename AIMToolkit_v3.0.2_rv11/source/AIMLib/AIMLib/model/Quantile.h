/*
  Classname: Quantile

*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#if !defined(_AIMLib_Quantile_Class)
#define _AIMLib_Quantile_Class

#include <string>

namespace aim_lib
{
	class AIMLIB_API Quantile : public CharacteristicQuantification
	{
	public:
		Quantile(void);
		Quantile(const Quantile& quantile);
		virtual ~Quantile(void);
		Quantile& operator=(const Quantile& quantile);
		virtual Quantile* Clone() const;

		int GetBin() const;
		void SetBin(int newVal);

	protected:
		int _bin;
	};
}
#endif // _AIMLib_Quantile_Class
