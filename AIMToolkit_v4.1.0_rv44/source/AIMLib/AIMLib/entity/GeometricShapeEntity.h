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
#ifndef _AIMLib_GeometricShapeEntity_Class_
#define _AIMLib_GeometricShapeEntity_Class_

#include <string>
#include <memory>
#include <vector>

namespace aim_lib
{
	class AIMLIB_API GeometricShapeEntity : public MarkupEntity
	{
	public:
		GeometricShapeEntity& operator=(const GeometricShapeEntity& shape);
		virtual ~GeometricShapeEntity();
		virtual GeometricShapeEntity* Clone() const = 0;

		int GetShapeIdentifier() const;
		const iso_21090::CDVector& GetQuestionTypeCode() const;
		const std::string& GetLabel() const;
		const std::string& GetDescription() const;
		bool GetIncludeFlag() const;
		const std::string& GetComment() const;
		const std::string& GetLineColor() const;
		const std::string& GetLineOpacity() const;
		const std::string& GetLineStyle() const;
		const std::string& GetLineThickness() const;
		int GetQuestionIndex() const;
		const iso_21090::CD* GetInterpolationMethod() const;

		void SetShapeIdentifier(int shapeIdentifier);
		void SetQuestionTypeCode(const iso_21090::CDVector& newVal);
		void SetLabel(const std::string& newVal);
		void SetDescription(const std::string& newVal);
		void SetIncludeFlag(bool newVal);
		void SetComment(const std::string& newVal);
		void SetLineColor(const std::string& newVal);
		void SetLineOpacity(const std::string& newVal);
		void SetLineStyle(const std::string& newVal);
		void SetLineThickness(const std::string& newVal);
		void SetQuestionIndex(int newVal);
		void SetInterpolationMethod(const iso_21090::CD* newVal);

	protected:
		GeometricShapeEntity(const std::string& typeName);
		GeometricShapeEntity(const GeometricShapeEntity& shape);

		int _shapeIdetifier;
		iso_21090::CDVector _questionTypeCode;
		std::string _label;
		std::string _description;
		bool _includeFlag;
		std::string _comment;
		int _questionIndex; // Default: -1
		std::string _lineColor;
		std::string _lineOpacity;
		std::string _lineStyle;
		std::string _lineThickness;
		std::auto_ptr<iso_21090::CD> _interpolationMethod;

		std::string _shapeTypeName; // internal
	};

	typedef std::vector<GeometricShapeEntity*> GeometricShapePtrVector;
}
#endif // _AIMLib_GeometricShapeEntity_Class_
