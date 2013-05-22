/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#pragma once
#ifndef _AIMLib_ImagePlane_Class_
#define _AIMLib_ImagePlane_Class_

#include <memory>

namespace aim_lib
{
	class AIMLIB_API ImagePlane
	{
	public:
		ImagePlane(void);
		ImagePlane(const ImagePlane& imagePlane);
		virtual ~ImagePlane(void);
		ImagePlane& operator=(const ImagePlane& imagePlane); // need to have it here; otherwise the auto_ptr template will break the build because of the const in the copy constructor
		ImagePlane* Clone() const;

		double* GetRowImageOrientationX() const;
		double* GetRowImageOrientationY() const;
		double* GetRowImageOrientationZ() const;
		double* GetColumnImageOrientationX() const;
		double* GetColumnImageOrientationY() const;
		double* GetColumnImageOrientationZ() const;
		double* GetVerticalPixelSpacing() const;
		double* GetHorizontalPixelSpacing() const;
		double* GetSliceThickness() const;
		double* GetImagePositionX() const;
		double* GetImagePositionY() const;
		double* GetImagePositionZ() const;

		void SetRowImageOrientationX(double* newVal);
		void SetRowImageOrientationY(double* newVal);
		void SetRowImageOrientationZ(double* newVal);
		void SetColumnImageOrientationX(double* newVal);
		void SetColumnImageOrientationY(double* newVal);
		void SetColumnImageOrientationZ(double* newVal);
		void SetVerticalPixelSpacing(double* newVal);
		void SetHorizontalPixelSpacing(double* newVal);
		void SetSliceThickness(double* newVal);
		void SetImagePositionX(double* newVal);
		void SetImagePositionY(double* newVal);
		void SetImagePositionZ(double* newVal);

	protected:
		std::auto_ptr<double> _rowImageOrientationX;
		std::auto_ptr<double> _rowImageOrientationY;
		std::auto_ptr<double> _rowImageOrientationZ;
		std::auto_ptr<double> _columnImageOrientationX;
		std::auto_ptr<double> _columnImageOrientationY;
		std::auto_ptr<double> _columnImageOrientationZ;
		std::auto_ptr<double> _verticalPixelSpacing;
		std::auto_ptr<double> _horizontalPixelSpacing;
		std::auto_ptr<double> _sliceThickness;
		std::auto_ptr<double> _imagePositionX;
		std::auto_ptr<double> _imagePositionY;
		std::auto_ptr<double> _imagePositionZ;
	};
}
#endif // _AIMLib_ImagePlane_Class_
