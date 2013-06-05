/*
  Classname: WebImageReference

*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#if !defined(EA_A654280B_DBED_46da_9BD4_5BC524D52B15__INCLUDED_)
#define EA_A654280B_DBED_46da_9BD4_5BC524D52B15__INCLUDED_

#include <string>

namespace aim_lib
{
	class AIMLIB_API WebImageReference : public ImageReference
	{
	public:
		WebImageReference();
		WebImageReference(const WebImageReference& imageReference);
		virtual ~WebImageReference();
		virtual ImageReference* Clone() const;

		const std::string& GetURI() const;
		void SetURI(const std::string& newVal);

	private:
		std::string _uri;

	};
}
#endif // !defined(EA_A654280B_DBED_46da_9BD4_5BC524D52B15__INCLUDED_)
