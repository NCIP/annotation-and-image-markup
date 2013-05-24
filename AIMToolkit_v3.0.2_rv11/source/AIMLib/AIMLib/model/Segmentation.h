/*
  Classname: Segmentation

*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#if !defined(EA_AB0E9BDB_0D6C_4f66_A6CA_72CFC0EDF1D0__INCLUDED_)
#define EA_AB0E9BDB_0D6C_4f66_A6CA_72CFC0EDF1D0__INCLUDED_

#include <string>
#include <vector>

namespace aim_lib
{
	class AIMLIB_API Segmentation
	{
	public:
		Segmentation();
		Segmentation(const Segmentation& segmentation);
		virtual ~Segmentation();
		Segmentation& operator=(const Segmentation& segmentation); // need to have it here; otherwise the auto_ptr template will break the build because of the const in the copy constructor

		const std::string& GetSopInstanceUID() const;
		const std::string& GetSopClassUID() const;
		const std::string& GetReferencedSopInstanceUID() const;
		int GetSegmentNumber() const;
		const ImagingObservation* GetImagingObservation() const;

		void SetSopInstanceUID(const std::string& newVal);
		void SetSopClassUID(const std::string& newVal);
		void SetReferencedSopInstanceUID(const std::string& newVal);
		void SetSegmentNumber(int newVal);
		void SetImagingObservation(const ImagingObservation* pImagingObservation);

	private:
		int _cagridId;
		std::string _sopInstanceUID;
		std::string _sopClassUID;
		std::string _referencedSopInstanceUID;
		int _segmentNumber;
		std::auto_ptr<ImagingObservation> _imagingObservation;
	};

	typedef std::vector<Segmentation> SegmentationVector;
}
#endif // !defined(EA_AB0E9BDB_0D6C_4f66_A6CA_72CFC0EDF1D0__INCLUDED_)
