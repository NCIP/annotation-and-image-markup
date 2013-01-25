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

#if !defined(_AIMLib_AimResultValidator_Class)
#define _AIMLib_AimResultValidator_Class

namespace aim_lib
{
#ifdef _DEBUG
	class AimOFCondition
	{
	public:
		AimOFCondition();
		AimOFCondition(const OFCondition& ofCondition);
		virtual ~AimOFCondition(void);
	
		inline OFBool good() const
		{
			return _condition.good();
		}

	private:
		OFCondition _condition;
	};

	class AimOFNode
	{
	public:
		AimOFNode();
		AimOFNode(size_t nodeId);
		virtual ~AimOFNode(void);
		operator size_t() { return _nodeId; };

	private:
		size_t _nodeId;
	};

#else

#define AimOFCondition OFCondition
#define AimOFNode size_t

#endif

}
#endif // _AIMLib_AimResultValidator_Class

//#define (AimResultValidator(OFCondition ofCondition)) (OFCondition ofCondition);
//#define (AimResultValidator(size_t nodeId)) (size_t nodeId);

