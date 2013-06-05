/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#pragma once
#ifndef _AIMLib_SegmentationEntity_Class_
#define _AIMLib_SegmentationEntity_Class_

#include <vector>

namespace aim_lib
{
	class AIMLIB_API SegmentationEntity : public Entity
	{
	public:
		SegmentationEntity& operator=(const SegmentationEntity& segmentationEntity);
		virtual SegmentationEntity* Clone() const = 0;
		virtual ~SegmentationEntity(void);

	protected:
		SegmentationEntity(void);
		SegmentationEntity(const SegmentationEntity& segmentationEnity);
	};

	typedef std::vector<SegmentationEntity*> SegmentationEntityPtrVector;
}
#endif // _AIMLib_SegmentationEntity_Class_
