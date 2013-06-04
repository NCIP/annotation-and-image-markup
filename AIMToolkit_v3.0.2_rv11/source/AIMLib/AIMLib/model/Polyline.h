/*
  Classname: Polyline

*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#if !defined(EA_9FC29CA2_F373_4d19_B446_54C089371B5C__INCLUDED_)
#define EA_9FC29CA2_F373_4d19_B446_54C089371B5C__INCLUDED_

namespace aim_lib
{
	class AIMLIB_API Polyline : public GeometricShape
	{

	public:
		Polyline();
		virtual ~Polyline();
		virtual Polyline* Clone() const;

	};
}
#endif // !defined(EA_9FC29CA2_F373_4d19_B446_54C089371B5C__INCLUDED_)
