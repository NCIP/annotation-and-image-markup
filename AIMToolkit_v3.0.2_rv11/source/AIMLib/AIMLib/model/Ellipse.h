/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#if !defined(EA_1BDC5970_3C15_4479_B81A_1F85C05649CD__INCLUDED_)
#define EA_1BDC5970_3C15_4479_B81A_1F85C05649CD__INCLUDED_

namespace aim_lib
{
	class AIMLIB_API Ellipse : public GeometricShape
	{

	public:
		Ellipse();
		virtual ~Ellipse();
		virtual Ellipse* Clone() const;

		const SpatialCoordPtrVector& GetEllipseCollection();
		void SetEllipseCollection(const SpatialCoordPtrVector& ellipseCollection);
	};
}
#endif // !defined(EA_1BDC5970_3C15_4479_B81A_1F85C05649CD__INCLUDED_)
