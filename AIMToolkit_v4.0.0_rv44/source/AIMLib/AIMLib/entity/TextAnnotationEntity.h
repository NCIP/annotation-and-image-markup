/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
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
