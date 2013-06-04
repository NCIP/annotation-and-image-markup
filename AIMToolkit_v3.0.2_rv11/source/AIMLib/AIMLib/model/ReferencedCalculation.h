/*
  Classname: ReferencedCalculation

*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#if !defined(EA_5636AF95_4798_4b34_A84A_646382B3D517__INCLUDED_)
#define EA_5636AF95_4798_4b34_A84A_646382B3D517__INCLUDED_

#include <string>
#include <vector>

namespace aim_lib
{
	class AIMLIB_API ReferencedCalculation
	{
	public:
		ReferencedCalculation();
		ReferencedCalculation(const ReferencedCalculation& referencedCalculation);
		ReferencedCalculation& operator=(const ReferencedCalculation& referencedCalculation);
		virtual ~ReferencedCalculation();

		const std::string& GetUniqueIdentifier() const; // Referenced calculation's unique identifier
		void SetUniqueIdentifier(const std::string& newVal);

	private:
		int _cagridId;
		std::string _uniqueIdentifier;
	};

	typedef std::vector<ReferencedCalculation> ReferencedCalcVector;

}
#endif // !defined(EA_5636AF95_4798_4b34_A84A_646382B3D517__INCLUDED_)
