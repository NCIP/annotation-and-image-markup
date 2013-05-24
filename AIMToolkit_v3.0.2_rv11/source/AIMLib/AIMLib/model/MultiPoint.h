/*
  Classname: MultiPoint

*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#if !defined(EA_97243C0C_15A4_4a08_A179_DC12EE182224__INCLUDED_)
#define EA_97243C0C_15A4_4a08_A179_DC12EE182224__INCLUDED_

namespace aim_lib
{
	class AIMLIB_API MultiPoint : public GeometricShape
	{

	public:
		MultiPoint();
		virtual ~MultiPoint();
		virtual MultiPoint* Clone() const;
	};
}
#endif // !defined(EA_97243C0C_15A4_4a08_A179_DC12EE182224__INCLUDED_)
