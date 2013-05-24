/*
  Classname: Inference

*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#if !defined(_AIMLIB_INFERENCE_INCLUDED_)
#define _AIMLIB_INFERENCE_INCLUDED_

#include <memory>
#include <string>
#include <vector>

namespace aim_lib
{
	class AIMLIB_API Inference
	{
	public:
		Inference(void);
		Inference(const Inference& inference);
		~Inference(void);
		Inference& operator=(const Inference& inference); // need to have it here; otherwise the auto_ptr template will break the build because of the const in the copy constructor

		const std::string& GetCodeMeaning() const;
		const std::string& GetCodeValue() const;
		const std::string& GetCodingSchemeDesignator() const;
		const std::string& GetCodingSchemeVersion() const;
		double* GetAnnotatorConfidence() const;
		bool GetImageEvidence() const;

		void SetCodeMeaning(const std::string& newVal);
		void SetCodeValue(const std::string& newVal);
		void SetCodingSchemeDesignator(const std::string& newVal);
		void SetCodingSchemeVersion(const std::string& newVal);
		void SetAnnotatorConfidence(double* newVal);
		void SetImageEvidence(bool newVal);

	protected:
		int _cagridId;
		std::string _codeMeaning;
		std::string _codeValue;
		std::string _codingSchemeDesignator;
		std::string _codingSchemeVersion;
		std::auto_ptr<double> _annotatorConfidence;
		bool _imageEvidence; // ground truth
	};

	typedef std::vector<Inference> InferenceVector;
}
#endif // !defined(_AIMLIB_INFERENCE_INCLUDED_)
