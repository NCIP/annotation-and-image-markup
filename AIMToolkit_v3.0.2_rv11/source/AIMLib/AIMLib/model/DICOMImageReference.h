/*
  Classname: DICOMImageReference

*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#if !defined(EA_C478B177_C5B5_4a65_9D4C_43F8A195539C__INCLUDED_)
#define EA_C478B177_C5B5_4a65_9D4C_43F8A195539C__INCLUDED_

namespace aim_lib
{
	class AIMLIB_API DICOMImageReference : public ImageReference
	{
	public:
		DICOMImageReference();
		DICOMImageReference(const DICOMImageReference& imageReference);
		virtual ~DICOMImageReference();
		virtual ImageReference* Clone() const;

		const ImageStudy& GetStudy() const;
		const PresentationStateVector& GetPresentationStateCollection() const;
		void SetStudy(const ImageStudy& study);
		void SetPresentationStateCollection(const PresentationStateVector& presentationStates);

	private:
		ImageStudy _study;
		PresentationStateVector _presentationStateCollection;
	};
}
#endif // !defined(EA_C478B177_C5B5_4a65_9D4C_43F8A195539C__INCLUDED_)
