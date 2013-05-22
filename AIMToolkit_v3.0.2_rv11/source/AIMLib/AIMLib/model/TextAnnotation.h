/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#if !defined(EA_05EAA3AC_2C35_449f_8F51_8457072AA732__INCLUDED_)
#define EA_05EAA3AC_2C35_449f_8F51_8457072AA732__INCLUDED_

#include <string>
#include <vector>
#include <memory>

namespace aim_lib
{
	class AIMLIB_API TextAnnotation
	{
	public:
		TextAnnotation();
		TextAnnotation(const TextAnnotation& textAnnotation);
		virtual ~TextAnnotation();
		virtual TextAnnotation* Clone() const;
		TextAnnotation& operator=(const TextAnnotation& textAnnotation); // need to have it here; otherwise the auto_ptr template will break the build because of the const in the copy constructor

		const std::string& GetFont() const;
		const std::string& GetFontColor() const;
		const std::string& GetFontEffect() const;
		const std::string& GetFontOpacity() const;
		const std::string& GetFontSize() const;
		const std::string& GetFontStyle() const;
		const std::string& GetText() const;
		const std::string& GetTextJustify() const;
		const MultiPoint* GetConnectorPoints() const;
		void SetFont(const std::string& newVal);
		void SetFontColor(const std::string& newVal);
		void SetFontEffect(const std::string& newVal);
		void SetFontOpacity(const std::string& newVal);
		void SetFontSize(const std::string& newVal);
		void SetFontStyle(const std::string& newVal);
		void SetText(const std::string& newVal);
		void SetTextJustify(const std::string& newVal);
		void SetConnectorPoints(const MultiPoint* connectorPoints);

	protected:
		int _cagridId;
		std::string _text;
		std::string _textJustify;
		std::string _font;
		std::string _fontColor;
		std::string _fontEffect;
		std::string _fontOpacity;
		std::string _fontSize;
		std::string _fontStyle;

		mutable std::auto_ptr<MultiPoint> _connectorPoints;
	};

	typedef std::vector<TextAnnotation> TextAnnotationVector;

}
#endif // !defined(EA_05EAA3AC_2C35_449f_8F51_8457072AA732__INCLUDED_)
