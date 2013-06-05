/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#pragma once
#ifndef _AIMLib_DicomSegmentationEntity_Class_
#define _AIMLib_DicomSegmentationEntity_Class_

namespace aim_lib
{
	class AIMLIB_API DicomSegmentationEntity : public SegmentationEntity
	{
	public:
		DicomSegmentationEntity(void);
		DicomSegmentationEntity(const DicomSegmentationEntity& segmentationEnity);
		DicomSegmentationEntity& operator=(const DicomSegmentationEntity& segmentationEntity);
		virtual DicomSegmentationEntity* Clone() const;
		virtual ~DicomSegmentationEntity(void);

		const iso_21090::II& GetSopInstanceUid() const;
		const iso_21090::II& GetSopClassUid() const;
		const iso_21090::II& GetReferencedSopInstanceUid() const;
		int GetSegmentNumber() const;

		void SetSopInstanceUid(const iso_21090::II& newVal);
		void SetSopClassUid(const iso_21090::II& newVal);
		void SetReferencedSopInstanceUid(const iso_21090::II& newVal);
		void SetSegmentNumber(int newVal);

	protected:
		iso_21090::II _sopInstanceUid;
		iso_21090::II _sopClassUid;
		iso_21090::II _referencedSopInstanceUid;
		int _segmentNumber;
	};
}
#endif // _AIMLib_DicomSegmentationEntity_Class_
