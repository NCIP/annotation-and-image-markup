/*
  Classname: PresentationState

*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#if !defined(_AIMLib_PresentationState_Class)
#define _AIMLib_PresentationState_Class

#include <string>
#include <vector>

namespace aim_lib
{
	class AIMLIB_API PresentationState
	{
	public:
		PresentationState(void);
		PresentationState(const PresentationState& presentationState);
		~PresentationState(void);

		const std::string& GetSopInstanceUID() const;
		void SetSopInstanceUID(const std::string& newVal);

	private:
		int _cagridId;
		std::string _sopInstanceUID;
	};

	typedef std::vector<PresentationState> PresentationStateVector;
}

#endif // _AIMLib_PresentationState_Class
