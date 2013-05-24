/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

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

