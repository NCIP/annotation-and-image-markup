/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#pragma once
#ifndef _AIMLib_MarkupEntity_Class_
#define _AIMLib_MarkupEntity_Class_

#include <vector>

namespace aim_lib
{
	class AIMLIB_API MarkupEntity : public Entity
	{
	public:
		virtual ~MarkupEntity(void);
		virtual MarkupEntity* Clone() const = 0;

	protected:
		MarkupEntity(void);
		MarkupEntity(const MarkupEntity& markupEntity);
	};

	typedef std::vector<MarkupEntity*> MarkupEntityPtrVector;
}
#endif // _AIMLib_MarkupEntity_Class_
