/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#pragma once
#ifndef _AIMLib_external_II
#define _AIMLib_external_II

#include <string>
#include <ostream>

namespace aim_lib
{
	namespace iso_21090
	{
		class AIMLIB_API II
		{
		public:
			II(void);
			II(const std::string& uid);
			II(const II& ii);
			virtual ~II(void);

			II& operator=(const II& ii);
			bool operator==(const II& ii) const;
			bool operator!=(const II& ii) const;

			const std::string toString() const;

			static const II generate(bool createUid = true);

		protected:
	//		friend std::ostream& operator<<(std::ostream&, const II&);

			std::string _uid; // DICOM UID
		};

		//std::ostream& operator<<(std::ostream &strm, const II& ii) {
		//	return strm << ii._uid;
		//}
	}
}

#endif // _AIMLib_external_II
