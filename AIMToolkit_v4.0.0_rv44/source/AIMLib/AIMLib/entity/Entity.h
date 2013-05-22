/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#pragma once
#ifndef _AIMLib_Entity_Class_
#define _AIMLib_Entity_Class_

#include <vector>

namespace aim_lib
{
	class AIMLIB_API Entity
	{
	public:
		virtual ~Entity(void);
		Entity& operator=(const Entity& entity);

		const iso_21090::II GetUniqueIdentifier() const;
		void SetUniqueIdentifier(const iso_21090::II& uniqueIdentifier);

	protected:
		Entity();
		Entity(const Entity& entity);

		// --------------------------------------------------------------------------------------------------
		// Template helper methods for working with vectors of pointers
		template<class T>
		void FreePtrVector(std::vector<T*>& daVector){
			while(daVector.size() > 0){
				delete daVector.back();
				daVector.pop_back();
			}
		}

		template<class T>
		void ClonePtrVector(const std::vector<T*>& srcVector, std::vector<T*>& destVector){
			destVector.reserve(srcVector.size());
			for(typename std::vector<T*>::size_type i = 0; i < srcVector.size(); i++){
				if (srcVector[i])
					destVector.push_back(srcVector[i]->Clone());
				else
					destVector.push_back(NULL);
			}
		}
		// --------------------------------------------------------------------------------------------------

		iso_21090::II _uniqueIdentifier;
	};
}

#endif // _AIMLib_Entity_Class_
