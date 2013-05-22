/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#pragma once
#ifndef _AIMLib_ImageSeries_Class_
#define _AIMLib_ImageSeries_Class_

#include <vector>

namespace aim_lib
{
	class AIMLIB_API ImageSeries
	{
	public:
		ImageSeries(void);
		ImageSeries(const ImageSeries& series);
		virtual ~ImageSeries(void);

		const iso_21090::II& GetInstanceUid() const;
		const iso_21090::CD& GetModality() const;
		const ImageVector& GetImageCollection() const;
		void SetInstanceUid(const iso_21090::II& newVal);
		void SetModality(const iso_21090::CD& newVal);
		void SetImageCollection(const ImageVector& images);

	protected:
		iso_21090::II _instanceUid; // Series Instance UID
		iso_21090::CD _modality;
		ImageVector _imageCollection;
	};
}

#endif // _AIMLib_ImageSeries_Class_
