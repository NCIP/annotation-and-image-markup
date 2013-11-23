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
#ifndef _AIMLib_TextAnnotationEntity_Class_
#define _AIMLib_TextAnnotationEntity_Class_

#include <string>
#include <vector>
#include <memory>

namespace aim_lib
{
	class AIMLIB_API TextAnnotationEntity : public MarkupEntity
	{
	public:
		TextAnnotationEntity();
		TextAnnotationEntity(const TextAnnotationEntity& textAnnotationEntity);
		virtual ~TextAnnotationEntity();
		virtual TextAnnotationEntity* Clone() const;
		TextAnnotationEntity& operator=(const TextAnnotationEntity& textAnnotationEntity); // need to have it here; otherwise the auto_ptr template will break the build because of the const in the copy constructor

		const std::string& GetText() const;
		const std::string& GetFont() const;
		const std::string& GetFontColor() const;
		const std::string& GetFontEffect() const;
		const std::string& GetFontOpacity() const;
		const std::string& GetFontSize() const;
		const std::string& GetFontStyle() const;
		const std::string& GetTextJustify() const;
		const GeometricShapeEntity* GetGeometricShapeEntity() const;

		void SetText(const std::string& newVal);
		void SetFont(const std::string& newVal);
		void SetFontColor(const std::string& newVal);
		void SetFontEffect(const std::string& newVal);
		void SetFontOpacity(const std::string& newVal);
		void SetFontSize(const std::string& newVal);
		void SetFontStyle(const std::string& newVal);
		void SetTextJustify(const std::string& newVal);
		void SetGeometricShapeEntity(const GeometricShapeEntity* newVal);                                                               

	protected:
		std::string _text;
		std::string _textJustify;
		std::string _font;
		std::string _fontColor;
		std::string _fontEffect;
		std::string _fontOpacity;
		std::string _fontSize;
		std::string _fontStyle;
		std::auto_ptr<GeometricShapeEntity> _geometricShapeEntity;
	};
}
#endif // _AIMLib_TextAnnotationEntity_Class_
