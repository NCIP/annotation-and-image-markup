/*
Copyright (c) 2008-2013, Northwestern University
All rights reserved.
 
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
 
  Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
 
  Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.
 
  Neither the name of the Northwestern University nor the names of its contributors
  may be used to endorse or promote products derived from this software
  without specific prior written permission.
 
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
