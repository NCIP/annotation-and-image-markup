/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
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
