/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "StdAfx.h"
#include "../Altova/Altova.h"
#include "../Altova/AltovaException.h"
#include "XmlException.h"
#include "Node.h"

#include "XercesString.h"
#include <stdio.h>
#include <string.h>
#include <sstream>

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/framework/Wrapper4InputSource.hpp>
#include <xercesc/framework/MemBufFormatTarget.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/PlatformUtils.hpp>

#define X(str) XStr(str).unicodeForm()

#if defined(UNICODE) || defined(_UNICODE)

bool XercesTreeOperations::IsEqualString(const XMLCh* a, const char_type* b)
{
	if ((const char_type*)a == b) return true;
	if (a == 0) a = (const XMLCh*)L"\0";
	if (b == 0) b = L"";
	return _tcscmp((const char_type*)a, b) == 0;
}

void UTF16ToUTF8(const std::wstring& utf16, std::string& utf8)
{
	for (unsigned int i = 0; i < utf16.size();++i) {
		unsigned int uch = utf16[i];
		if (uch < 0x80) {
			utf8.append( 1, static_cast<char>(uch));
		} else if (uch < 0x800) {
			utf8.append( 1, static_cast<char>(0xC0 | (uch >> 6)) );
			utf8.append( 1, static_cast<char>(0x80 | (uch & 0x3f)));
		} else if ((uch >= 0xD800) &&
			(uch <= 0xDFFF)) {
			i++;
			unsigned int xch = 0x10000 + ((uch & 0x3ff) << 10) + (utf16[i] & 0x3ff);
			utf8.append( 1, static_cast<char>(0xF0 | (xch >> 18)) );
			utf8.append( 1, static_cast<char>(0x80 | (xch >> 12) & 0x3f) );
			utf8.append( 1, static_cast<char>(0x80 | ((xch >> 6) & 0x3f)) );
			utf8.append( 1, static_cast<char>(0x80 | (xch & 0x3f)) );
		} else {
			utf8.append( 1, static_cast<char>(0xE0 | (uch >> 12)) );
			utf8.append( 1, static_cast<char>(0x80 | ((uch >> 6) & 0x3f)) );
			utf8.append( 1, static_cast<char>(0x80 | (uch & 0x3f)) );
		}
	}
}
 
FILE* altovawfopen( const std::wstring& filename, const std::wstring& modes)
{
	std::string afilename;
    std::string amodes;
	UTF16ToUTF8( filename, afilename);
    UTF16ToUTF8( modes, amodes);
 
	return fopen( afilename.c_str(), amodes.c_str());
}

#else

bool XercesTreeOperations::IsEqualString(const XMLCh* a, const char_type* b)
{
	if (a == 0) a = (const XMLCh*)"\0";
	if (b == 0) b = "";
	while (*a && *b)
	{
		if (*a != *b)
			return false;
		++a, ++b;
	}
	return (*a == *b);	// terminator	
}

#endif


static string_type GetTextContent(const xercesc::DOMNode* pNode)
{
	short nodeType = pNode->getNodeType();
	switch (nodeType)
	{
	case xercesc::DOMNode::ATTRIBUTE_NODE:
	case xercesc::DOMNode::PROCESSING_INSTRUCTION_NODE:
	case xercesc::DOMNode::COMMENT_NODE:
	case xercesc::DOMNode::TEXT_NODE:
	case xercesc::DOMNode::CDATA_SECTION_NODE:
		return string_type(XercesUnstringTemp(pNode->getNodeValue()));

	case xercesc::DOMNode::DOCUMENT_NODE:
	case xercesc::DOMNode::DOCUMENT_FRAGMENT_NODE:
	case xercesc::DOMNode::ELEMENT_NODE:
	case xercesc::DOMNode::ENTITY_REFERENCE_NODE:
		{
			string_type result;
			for (xercesc::DOMNode* pChild = pNode->getFirstChild(); pChild != 0; pChild = pChild->getNextSibling())
			{
				short childNodeType = pChild->getNodeType();
				switch (childNodeType)
				{
				case xercesc::DOMNode::TEXT_NODE:
				case xercesc::DOMNode::CDATA_SECTION_NODE:
				case xercesc::DOMNode::ELEMENT_NODE:
				case xercesc::DOMNode::ENTITY_REFERENCE_NODE:
					result += GetTextContent(pChild);
					break;
				}
			}
			return result;
		}		
	}
	return string_type();
}

static void FindDeclarationsForNamespace(xercesc::DOMNode* pNode, const string_type& uri, std::vector<xercesc::DOMNode*>& declarations)
{
	if (pNode->getParentNode() != 0)
		FindDeclarationsForNamespace(pNode->getParentNode(), uri, declarations);

	xercesc::DOMNamedNodeMap* attrs = pNode->getAttributes();
	if (attrs == 0)
		return;
	
	XMLSize_t length = attrs->getLength();
	for (XMLSize_t index = 0; index != length; ++index)
	{		
		xercesc::DOMNode* att = attrs->item(index);
		if (string_type(XercesUnstringTemp(att->getPrefix())) == string_type(_T("xmlns")))
		{
			if (string_type(XercesUnstringTemp(att->getNodeValue())) == uri)
			{
				declarations.push_back(att);								
			}
			else 
			{
				for (std::vector<xercesc::DOMNode*>::iterator it = declarations.begin(); it != declarations.end(); )
				{
					xercesc::DOMNode* cur = *it;
					
					if (xercesc::XMLString::compareString(cur->getLocalName(), att->getLocalName()) == 0)	
						declarations.erase(it);
					else
						++it;
				}
			}
		}
	}
}

string_type FindPrefixForNamespace(xercesc::DOMNode* node, const string_type& uri)
{
	if (uri == string_type(_T("http://www.w3.org/XML/1998/namespace")))
		return string_type(_T("xml"));
		
	if (uri == string_type(_T("http://www.w3.org/2000/xmlns/")))
		return string_type(_T("xmlns"));

	// VK - added to make sure that we get this prefix instead of "n0"
	if (uri == string_type(_T("http://www.w3.org/2001/XMLSchema-instance")))
		return string_type(_T("xsi"));

	// VK: enable 'aim' prefix on all AIM elements
	if (uri == string_type(_T("http://www.radiology.northwestern.edu/aim/1")))
		return string_type(_T("aim"));

	string_type prefix;

	std::vector<xercesc::DOMNode*> declarations;
	FindDeclarationsForNamespace(node, uri, declarations);
	if (!declarations.empty())
		prefix = string_type(XercesUnstringTemp(declarations.front()->getLocalName()));
	else
		prefix = string_type(_T(""));
	return prefix;
}

static string_type FindNamespaceUriForPrefix(const xercesc::DOMNode* node, const string_type& prefix)
{
	if (node->getNodeType() != xercesc::DOMNode::ELEMENT_NODE)
		return string_type(_T(""));

	string_type ns = _T("xmlns:");
	ns += prefix;

	xercesc::DOMNode* item = node->getAttributes()->getNamedItemNS(XercesStringTemp(_T("http://www.w3.org/2000/xmlns/")), XercesStringTemp(prefix));

	if (item)
		return GetTextContent(item);

	if (node->getParentNode())
		return FindNamespaceUriForPrefix(node->getParentNode(), prefix);

	return string_type(_T(""));
}

static string_type GetUnusedPrefixForNode(xercesc::DOMNode* node, int n, const string_type& prefixHint = _T("") )
{
	string_type pp = _T("n");
	if (!prefixHint.empty())
		pp = prefixHint;

	while (true)
	{
		n++;
		if (n > 0 || prefixHint.empty())
		{	
            tstringstream sspp( pp );
            sspp << n;
            pp += sspp.str();
		}

		if (node->getNodeType() != xercesc::DOMNode::ELEMENT_NODE)
			return pp;
	
		if (node->getAttributes()->getNamedItemNS(XercesStringTemp(_T("http://www.w3.org/2000/xmlns/")), XercesStringTemp(pp)) != 0)
			continue;

		if (node->getParentNode())
			return GetUnusedPrefixForNode(node->getParentNode(), n-1, prefixHint);
		else
			return _T("");
	}
}

string_type GetUnusedPrefix(xercesc::DOMNode* node, const string_type& prefixHint)
{
	return GetUnusedPrefixForNode(node, -1, prefixHint);
}


static string_type FindUnusedPrefix(xercesc::DOMNode* node, const string_type& prefixHint = _T(""))
{
	return GetUnusedPrefixForNode(node, -1, prefixHint);
}


void XercesTreeOperations::CopyAll(const xercesc::DOMNode* src, xercesc::DOMNode* tgt)
{
	// nodes
	for(xercesc::DOMNode* node = src->getFirstChild(); node != 0; node = node->getNextSibling())
		tgt->appendChild(tgt->getOwnerDocument()->importNode(node, true));
	// attributes
	xercesc::DOMNamedNodeMap* attrz = src->getAttributes();
	for (size_t i=0; i< attrz->getLength(); i++)
		((xercesc::DOMElement*)tgt)->setAttributeNode((xercesc::DOMAttr*)tgt->getOwnerDocument()->importNode(attrz->item(i), true));
}

bool XercesTreeOperations::IsMember( xercesc::DOMNode* pNode, const altova::MemberInfo* pMember )
{
	if (*pMember->LocalName == 0)
		return pNode->getNodeType() == xercesc::DOMNode::TEXT_NODE ||
		pNode->getNodeType() == xercesc::DOMNode::CDATA_SECTION_NODE;

	if (pNode->getNodeType() != xercesc::DOMNode::ELEMENT_NODE)
		return false;

	const XMLCh* pName = pNode->getLocalName();
	if (pName == 0)
		pName = pNode->getNodeName();

	return IsEqualString(pName, pMember->LocalName) &&
		IsEqualString(pNode->getNamespaceURI(), pMember->NamespaceURI);			
}


bool XercesTreeOperations::IsValid(xercesc::DOMNode* pNode) 
{ 
	return pNode != 0; 
}

XercesTreeOperations::AllIterator XercesTreeOperations::GetElements(xercesc::DOMNode* pNode)
{
	return AllIterator(pNode->getFirstChild());
}

XercesTreeOperations::MemberIterator XercesTreeOperations::GetElements(xercesc::DOMNode* pNode, const altova::MemberInfo* pMemberInfo)
{
	return MemberIterator(pNode->getFirstChild(), pMemberInfo);
}

void XercesTreeOperations::SetTextValue(xercesc::DOMNode* pNode, const string_type& sText)
{
	while (pNode->getFirstChild())
	{
		pNode->removeChild(pNode->getFirstChild())->release();
	}

	pNode->appendChild(pNode->getOwnerDocument()->createTextNode(XercesStringTemp(sText)));
//	pNode->setNodeValue(XercesStringTemp(sText));
}

string_type XercesTreeOperations::GetTextValue(xercesc::DOMNode* pNode)
{	
	return GetTextContent(pNode);
}


void XercesTreeOperations::SetValue(xercesc::DOMNode* pNode, const altova::MemberInfo* pMemberInfo, const XMLCh* bValue)
{
	if (*pMemberInfo->LocalName != 0)
	{
		string_type prefix;
		if (*pMemberInfo->NamespaceURI)
		{
			prefix = FindPrefixForNamespace(pNode, pMemberInfo->NamespaceURI);
			if (prefix.empty())
				prefix = FindUnusedPrefix(pNode) + _T(":");
			else
				prefix += _T(":");
		}

		xercesc::DOMNode* pAttr = pNode->getOwnerDocument()->createAttributeNS(
			XercesStringTemp(pMemberInfo->NamespaceURI),
			XercesStringTemp(prefix + pMemberInfo->LocalName));
		pAttr->setNodeValue(bValue);
		pNode->getAttributes()->setNamedItemNS(pAttr);
	}
	else
	{
		while (pNode->hasChildNodes())
		{
			pNode->removeChild(pNode->getFirstChild())->release();
		}

		pNode->appendChild(pNode->getOwnerDocument()->createTextNode(bValue));
	}			
}

void XercesTreeOperations::SetValue(xercesc::DOMNode* pNode, const altova::MemberInfo* pMemberInfo, const string_type& sValue)
{
	SetValue(pNode, pMemberInfo, XercesStringTemp(sValue));
}

void XercesTreeOperations::SetValue(xercesc::DOMNode* pNode, const altova::MemberInfo* pMemberInfo, const altova::QName& qname)
{
	if (qname.Uri.empty())
	{
		SetValue(pNode, pMemberInfo, XercesStringTemp(qname.LocalName));
		return;
	}

	string_type prefix = FindPrefixForNamespace(pNode, qname.Uri);
	
	if (prefix.empty())
	{
		prefix = FindUnusedPrefix(pNode, qname.Prefix);
		xercesc::DOMElement* el = static_cast<xercesc::DOMElement*>(pNode);
		string_type ns = _T("xmlns:");
		ns += prefix;
		el->setAttributeNS(XercesStringTemp(_T("http://www.w3.org/2000/xmlns/")), XercesStringTemp(ns), XercesStringTemp(qname.Uri));
	}

	SetValue(pNode, pMemberInfo, XercesStringTemp(prefix + _T(":") + qname.LocalName));
}

inline altova::XmlFormatter* GetFormatter(const altova::MemberInfo* pMember)
{
	if (((pMember->Binder->Types + pMember->DataType)->Formatter))
		return static_cast<altova::XmlFormatter*>(*((pMember->Binder->Types + pMember->DataType)->Formatter));
	else
		return static_cast<altova::XmlFormatter*>(altova::AnySimpleTypeFormatter);
}


void XercesTreeOperations::SetValue(xercesc::DOMNode* pNode, const altova::MemberInfo* pMemberInfo, bool b)
{
	SetValue(pNode, pMemberInfo, GetFormatter(pMemberInfo)->Format(b));
}

void XercesTreeOperations::SetValue(xercesc::DOMNode* pNode, const altova::MemberInfo* pMemberInfo, int b)
{
	SetValue(pNode, pMemberInfo, GetFormatter(pMemberInfo)->Format((__int64)b));
}

void XercesTreeOperations::SetValue(xercesc::DOMNode* pNode, const altova::MemberInfo* pMemberInfo, unsigned b)
{
	SetValue(pNode, pMemberInfo, GetFormatter(pMemberInfo)->Format((unsigned __int64)b));
}

void XercesTreeOperations::SetValue(xercesc::DOMNode* pNode, const altova::MemberInfo* pMemberInfo, __int64 b)
{
	SetValue(pNode, pMemberInfo, GetFormatter(pMemberInfo)->Format(b));
}

void XercesTreeOperations::SetValue(xercesc::DOMNode* pNode, const altova::MemberInfo* pMemberInfo, unsigned __int64 b)
{
	SetValue(pNode, pMemberInfo, GetFormatter(pMemberInfo)->Format(b));
}

void XercesTreeOperations::SetValue(xercesc::DOMNode* pNode, const altova::MemberInfo* pMemberInfo, double b)
{
	SetValue(pNode, pMemberInfo, GetFormatter(pMemberInfo)->Format(b));
}

void XercesTreeOperations::SetValue(xercesc::DOMNode* pNode, const altova::MemberInfo* pMemberInfo, altova::DateTime b)
{
	SetValue(pNode, pMemberInfo, GetFormatter(pMemberInfo)->Format(b));
}

void XercesTreeOperations::SetValue(xercesc::DOMNode* pNode, const altova::MemberInfo* pMemberInfo, altova::Duration b)
{
	SetValue(pNode, pMemberInfo, GetFormatter(pMemberInfo)->Format(b));
}

void XercesTreeOperations::SetValue(xercesc::DOMNode* pNode, const altova::MemberInfo* pMemberInfo, const std::vector<unsigned char>& b)
{
	SetValue(pNode, pMemberInfo, GetFormatter(pMemberInfo)->Format(b));
}


void XercesTreeOperations::SetValue(xercesc::DOMNode* pNode, const altova::MemberInfo* pMemberInfo, const xercesc::DOMNode* b)
{
	SetValue(pNode, pMemberInfo, GetTextContent(b));
}



xercesc::DOMNode* XercesTreeOperations::AddElement(xercesc::DOMNode* pNode, const altova::MemberInfo* pMemberInfo)
{
	string_type prefix;
	if (*pMemberInfo->NamespaceURI)
	{
		prefix = FindPrefixForNamespace(pNode, pMemberInfo->NamespaceURI);
		if (!prefix.empty())
			prefix += _T(":");
	}

	xercesc::DOMDocument* pDoc = pNode->getOwnerDocument();
	if ( pDoc == 0 )
		pDoc = ( xercesc::DOMDocument* )pNode;
	xercesc::DOMNode* pNewNode = pDoc->createElementNS(
		XercesStringTemp(pMemberInfo->NamespaceURI), 
		XercesStringTemp(prefix + pMemberInfo->LocalName));
	pNode->appendChild(pNewNode);
	return pNewNode;
}


// VK: Added this method to enable adding "xsi:type" attribute to the node declaration
xercesc::DOMNode* XercesTreeOperations::AddElementSpecial(xercesc::DOMNode* pNode, const altova::MemberInfo* pBaseMemberInfo, const altova::TypeInfo* pTypeInfo)
{
	string_type prefix;
	if (*pBaseMemberInfo->NamespaceURI)
	{
		prefix = FindPrefixForNamespace(pNode, pBaseMemberInfo->NamespaceURI);
		if (!prefix.empty())
			prefix += _T(":");
	}

	xercesc::DOMDocument* pDoc = pNode->getOwnerDocument();
	if ( pDoc == 0 )
		pDoc = ( xercesc::DOMDocument* )pNode;
	xercesc::DOMElement* pNewNode = pDoc->createElementNS(
		XercesStringTemp(pBaseMemberInfo->NamespaceURI), 
 		XercesStringTemp(prefix + pBaseMemberInfo->LocalName));

	XercesTreeOperations::SetAttribute(pNewNode, _T("type"), _T("http://www.w3.org/2001/XMLSchema-instance"), prefix + pTypeInfo->LocalName);

	pNode->appendChild(pNewNode);
	return pNewNode;
}


double XercesTreeOperations::CastToDouble(const xercesc::DOMNode* pNode, const altova::MemberInfo* pMemberInfo)
{
	return altova::CoreTypes::CastToDouble(GetTextContent(pNode));
}


string_type XercesTreeOperations::CastToString(const xercesc::DOMNode* pNode, const altova::MemberInfo* pMemberInfo)
{
	return altova::CoreTypes::CastToString(GetTextContent(pNode));
}


__int64 XercesTreeOperations::CastToInt64(const xercesc::DOMNode* pNode, const altova::MemberInfo* pMemberInfo)
{
	return altova::CoreTypes::CastToInt64(GetTextContent(pNode));
}

unsigned __int64 XercesTreeOperations::CastToUInt64(const xercesc::DOMNode* pNode, const altova::MemberInfo* pMemberInfo)
{
	return altova::CoreTypes::CastToUInt64(GetTextContent(pNode));
}

unsigned XercesTreeOperations::CastToUInt(const xercesc::DOMNode* pNode, const altova::MemberInfo* pMemberInfo)
{
	return altova::CoreTypes::CastToUInt(GetTextContent(pNode));
}

int XercesTreeOperations::CastToInt(const xercesc::DOMNode* pNode, const altova::MemberInfo* pMemberInfo)
{
	return altova::CoreTypes::CastToInt(GetTextContent(pNode));
}


bool XercesTreeOperations::CastToBool(const xercesc::DOMNode* pNode, const altova::MemberInfo* pMemberInfo)
{
	return altova::CoreTypes::CastToBool(GetTextContent(pNode));
}

altova::DateTime XercesTreeOperations::CastToDateTime(const xercesc::DOMNode* pNode, const altova::MemberInfo* pMemberInfo)
{
	return altova::CoreTypes::CastToDateTime(GetTextContent(pNode));
}

altova::Duration XercesTreeOperations::CastToDuration(const xercesc::DOMNode* pNode, const altova::MemberInfo* pMemberInfo)
{
	return altova::CoreTypes::CastToDuration(GetTextContent(pNode));
}

std::vector<unsigned char> XercesTreeOperations::CastToBinary(const xercesc::DOMNode* pNode, const altova::MemberInfo* pMemberInfo)
{
	return GetFormatter(pMemberInfo)->ParseBinary(GetTextContent(pNode));
}

altova::QName XercesTreeOperations::CastToQName(const xercesc::DOMNode* pNode, const altova::MemberInfo* pMemberInfo)
{
	string_type value = GetTextContent(pNode);
	size_t i =  value.find(_T(':'));
	if (i == string_type::npos)
	{
		string_type defaultNsUri = XercesUnstringTemp(pNode->lookupNamespaceURI(0));
		
		return altova::QName(defaultNsUri, value);
	}	

	string_type prefix = value.substr(0, i);
	string_type local = value.substr(i+1);

	string_type uri;
	if (pNode->getNodeType() == xercesc::DOMNode::ATTRIBUTE_NODE)
		uri = FindNamespaceUriForPrefix(static_cast<const xercesc::DOMAttr*> (pNode)->getOwnerElement(), prefix);
	else
		uri = FindNamespaceUriForPrefix(pNode, prefix);

	return altova::QName(uri, prefix, local);
}

xercesc::DOMNode* XercesTreeOperations::FindAttribute(
	xercesc::DOMNode* pNode, const altova::MemberInfo* member)
{
	return pNode->getAttributes()->getNamedItemNS(XercesStringTemp(member->NamespaceURI), XercesStringTemp(member->LocalName));
}


xercesc::DOMNode* XercesTreeOperations::GetParent(xercesc::DOMNode* pNode)
{
	return pNode->getParentNode();
}

void XercesTreeOperations::SetValue(xercesc::DOMNode* pNode, const string_type& sValue)
{
	pNode->setNodeValue(XercesStringTemp(sValue.c_str()));
}

void XercesTreeOperations::RemoveAttribute(xercesc::DOMNode* pNode, const altova::MemberInfo* member)
{
	if (*member->LocalName)
	{
		if (pNode->hasAttributes())
			pNode->getAttributes()->removeNamedItemNS(XercesStringTemp(member->NamespaceURI), XercesStringTemp(member->LocalName));
	}
	else
	{
		for (xercesc::DOMNode* pChild = pNode->getFirstChild(); pChild; )
		{
			xercesc::DOMNode* cur = pChild;
			pChild = pChild->getNextSibling();
			if (cur->getNodeType() == xercesc::DOMNode::TEXT_NODE ||
				cur->getNodeType() == xercesc::DOMNode::CDATA_SECTION_NODE)
			{
				pNode->removeChild(cur);
			}			
		}
	}
}

void XercesTreeOperations::RemoveElements(xercesc::DOMNode* pNode, const altova::MemberInfo* member)
{
	for (xercesc::DOMNode* pChild = pNode->getFirstChild(); pChild; )
	{
		xercesc::DOMNode* cur = pChild;
		pChild = pChild->getNextSibling();
		if (IsMember(cur, member))
			pNode->removeChild(cur);
	}
}

void XercesTreeOperations::RemoveElement(xercesc::DOMNode* pNode, const altova::MemberInfo* member, unsigned index)
{
	for (xercesc::DOMNode* pChild = pNode->getFirstChild(); pChild; )
	{
		xercesc::DOMNode* cur = pChild;
		pChild = pChild->getNextSibling();
		if (IsMember(cur, member) && index-- == 0)
		{
			pNode->removeChild(cur);
			break;
		}
	}	
}


XercesTreeOperations::DocumentType XercesTreeOperations::LoadDocument(
	const string_type& filename)
{
	try 
	{
		xercesc::XercesDOMParser parser;
		xercesc::DefaultHandler defaultHandler;
		parser.setErrorHandler(&defaultHandler);
		parser.setDoNamespaces(true);
		parser.parse(XercesStringTemp(filename));
		DocumentType doc = parser.adoptDocument();
		return doc;
	}
	catch (xercesc::XMLException& error)
	{
		throw altova::DataSourceUnavailableException(filename + _T(": Xerces XML error while loading: ") + string_type(XercesUnstringTemp(error.getMessage())));
	}
	catch (xercesc::SAXException& error)
	{
		throw altova::DataSourceUnavailableException(filename + _T(": Xerces SAX error while loading: ") + string_type(XercesUnstringTemp(error.getMessage())));
	}
	catch (xercesc::DOMException&)
	{
		throw altova::DataSourceUnavailableException(filename + _T(": Xerces DOM error while loading"));
	}
}

void XercesTreeOperations::FreeDocument(DocumentType& document)
{
	document->release();
	document = 0;
}

void XercesTreeOperations::FreeDocument(xercesc::DOMNode*& document)
{
	document->release();
	document = 0;
}

void XercesTreeOperations::SaveDocument( const DocumentType& document, const string_type& filename, bool prettyPrint )
{
	SaveDocument( document, filename, prettyPrint, _T("UTF-8"), false, false );
}

void XercesTreeOperations::SaveDocument( const DocumentType& document, const string_type& filename, bool prettyPrint, const string_type& encoding, bool bBigEndian, bool bBOM )
{
	std::vector<unsigned char> bytes;
	SaveToBinary( bytes, document, prettyPrint, encoding, bBigEndian, bBOM );

	FILE *f = _tfopen( filename.c_str(), _T("wb") );
	if( !f )
		throw altova::DataTargetUnavailableException( _T("Could not open file ") + filename + _T(" for writing.") );

	fwrite( &bytes[0], bytes.size(), 1, f );
	fclose( f );
}

XercesTreeOperations::DocumentType XercesTreeOperations::LoadXml(const string_type& xml)
{
	try
	{
		xercesc::XercesDOMParser parser;
		xercesc::DefaultHandler defaultHandler;
		parser.setErrorHandler(&defaultHandler);
		parser.setDoNamespaces(true);

		xercesc::MemBufInputSource source( 
			( XMLByte* ) xml.data(), 
			xml.size() * sizeof( char_type ), 
			XercesStringTemp( _T("String")));
		
		#ifdef _UNICODE
		source.setEncoding( XercesStringTemp( _T("UTF-16")) );
		#endif
		parser.parse(source);
		DocumentType doc = parser.adoptDocument();
		return doc;		
	}
	catch (xercesc::XMLException& error)
	{
		throw altova::DataSourceUnavailableException(_T("Xerces XML error while loading: ") + string_type(XercesUnstringTemp(error.getMessage())));
	}
	catch (xercesc::SAXException& error)
	{
		throw altova::DataSourceUnavailableException(_T("Xerces SAX error while loading: ") + string_type(XercesUnstringTemp(error.getMessage())));
	}
	catch (xercesc::DOMException&)
	{
		throw altova::DataSourceUnavailableException(_T("Xerces DOM error while loading"));
	}
}

XercesTreeOperations::DocumentType XercesTreeOperations::LoadFromBinary(const std::vector<unsigned char>& binary)
{
	try
	{
		xercesc::XercesDOMParser parser;
		xercesc::DefaultHandler defaultHandler;
		parser.setErrorHandler(&defaultHandler);
		parser.setDoNamespaces(true);

		xercesc::MemBufInputSource source( 
			( XMLByte* ) &*binary.begin(), 
			binary.size(), 
			"String");

		parser.parse(source);
		DocumentType doc = parser.adoptDocument();
		return doc;		
	}
	catch (xercesc::XMLException& error)
	{
		throw altova::DataSourceUnavailableException(_T("Xerces XML error while loading: ") + string_type(XercesUnstringTemp(error.getMessage())));
	}
	catch (xercesc::SAXException& error)
	{
		throw altova::DataSourceUnavailableException(_T("Xerces SAX error while loading: ") + string_type(XercesUnstringTemp(error.getMessage())));
	}
	catch (xercesc::DOMException&)
	{
		throw altova::DataSourceUnavailableException(_T("Xerces DOM error while loading"));
	}
}


namespace
{
	class HoldXMLString
	{
		XMLCh* data;
	public:
		HoldXMLString(XMLCh* str) : data(str) {}
		~HoldXMLString() { xercesc::XMLPlatformUtils::fgMemoryManager->deallocate(data); data = 0; }
		operator const XMLCh*() const { return data; }
	};


	class HoldDOMLSSerializer
	{
		xercesc::DOMLSSerializer* data;
	public:
		HoldDOMLSSerializer(xercesc::DOMLSSerializer* serializer) : data(serializer) {}
		~HoldDOMLSSerializer() { data->release(); }
		xercesc::DOMLSSerializer* operator->() { return data; }
	};

}


string_type XercesTreeOperations::SaveXml(const DocumentType& document, bool prettyPrint)
{
	try
	{

		HoldDOMLSSerializer pLSSerializer(xercesc::DOMImplementation::getImplementation()->createLSSerializer());
		if (prettyPrint && pLSSerializer->getDomConfig()->canSetParameter(xercesc::XMLUni::fgDOMWRTFormatPrettyPrint, true))
		{
			pLSSerializer->getDomConfig()->setParameter(xercesc::XMLUni::fgDOMWRTFormatPrettyPrint, true);
		}
		HoldXMLString resultXML(pLSSerializer->writeToString(document));    

		string_type result = XercesUnstringTemp(resultXML);
		return result;
	}
	catch (xercesc::XMLException& error)
	{
		throw altova::DataTargetUnavailableException(_T("Xerces XML error while saving: ") + string_type(XercesUnstringTemp(error.getMessage())));
	}
	catch (xercesc::SAXException& error)
	{
		throw altova::DataTargetUnavailableException(_T("Xerces SAX error while saving: ") + string_type(XercesUnstringTemp(error.getMessage())));
	}
	catch (xercesc::DOMException&)
	{
		throw altova::DataTargetUnavailableException(_T("Xerces DOM error while saving"));
	}
}

XercesTreeOperations::DocumentType XercesTreeOperations::CreateDocument()
{
	xercesc::DOMDocument* doc = xercesc::DOMImplementation::getImplementation()->createDocument();
	return doc;
}

void XercesTreeOperations::AddProcessingInstruction(xercesc::DOMNode* node, const string_type& target, const string_type& value)
{
	xercesc::DOMDocument* doc = node->getOwnerDocument();
	if (doc == 0)
		doc = (xercesc::DOMDocument*)node;

	node->appendChild(doc->createProcessingInstruction(XercesStringTemp(target), XercesStringTemp(value)));
}

std::vector<unsigned char> XercesTreeOperations::SaveToBinary(const DocumentType& document, bool prettyPrint)
{
	std::vector<unsigned char> result;
	SaveToBinary( result, document, prettyPrint, _T(""), false, false, false );
	return result;
}

void XercesTreeOperations::SaveToBinary( std::vector<unsigned char>& result, const DocumentType& document, bool prettyPrint, const string_type& encoding, bool bBigEndian, bool bBOM, bool bIncludeEncoding )
{
	try 
	{
		// this is going to leak on exception:

		HoldDOMLSSerializer pLSSerializer( xercesc::DOMImplementation::getImplementation()->createLSSerializer() );

		if (prettyPrint && pLSSerializer->getDomConfig()->canSetParameter(xercesc::XMLUni::fgDOMWRTFormatPrettyPrint, true))
		{
			pLSSerializer->getDomConfig()->setParameter(xercesc::XMLUni::fgDOMWRTFormatPrettyPrint, true);
		}

		xercesc::MemBufFormatTarget target;
		xercesc::DOMLSOutput* pLSOutput = xercesc::DOMImplementation::getImplementation()->createLSOutput();
		pLSOutput->setByteStream( &target);

		if( bIncludeEncoding )
			pLSOutput->setEncoding( XercesStringTemp(encoding));
			//pLSSerializer->getDomConfig()->setParameter(xercesc::XMLUni::fgEncodingString, XercesStringTemp(encoding));
		bool bRet = pLSSerializer->write(document, pLSOutput);
		result.clear();
		result.insert(result.end(), target.getRawBuffer(), target.getRawBuffer() + target.getLen());

		pLSOutput->release();

		if( bIncludeEncoding )
			CorrectByteOrderAndBOM( result, encoding, bBigEndian, bBOM );

		if( !bRet )
			throw altova::DataTargetUnavailableException( _T("Xerces XML error while saving.") );
	}
	catch (xercesc::XMLException& error)
	{
		throw altova::DataTargetUnavailableException(_T("Xerces XML error while saving: ") + string_type(XercesUnstringTemp(error.getMessage())));
	}
	catch (xercesc::SAXException& error)
	{
		throw altova::DataTargetUnavailableException(_T("Xerces SAX error while saving: ") + string_type(XercesUnstringTemp(error.getMessage())));
	}
	catch (xercesc::DOMException&)
	{
		throw altova::DataTargetUnavailableException(_T("Xerces DOM error while saving"));
	}
}

void XercesTreeOperations::CorrectByteOrderAndBOM( std::vector<unsigned char>& bytes, const string_type& encoding, bool bBigEndian, bool bBOM )
{
	if( bytes.size() == 0 || encoding.empty() )
		return;

	int unisize = GetUnicodeSizeFromEncodingName( encoding );
	if( unisize == 0 )
		return;

	if( unisize < 2 )
		bBigEndian = false;

	int encbo = GetEncodingAndByteOrderFromXml( bytes );

	bool bHasBOM = (encbo & 0x10) != 0;
	bool bIsBigEndian = (encbo & 0x20) != 0;

	if( bBOM == bHasBOM && bBigEndian == bIsBigEndian )
		return;

	int off = 0;
	int len = (int) bytes.size();

	if( unisize > 0 && bBOM && !bHasBOM )
	{
		if( unisize == 1 )
		{
			bytes.insert( bytes.begin(), 3, 0 );
			bytes[0] = 0xef;
			bytes[1] = 0xbb;
			bytes[2] = 0xbf;
			off = 3;
		}
		else
		if( unisize == 2 )
		{
			if( bBigEndian ) {
				bytes.insert( bytes.begin(), 2, 0 );
				bytes[0] = 0xfe;
				bytes[1] = 0xff;
				off = 2;
			} else {
				bytes.insert( bytes.begin(), 2, 0 );
				bytes[0] = 0xff;
				bytes[1] = 0xfe;
				off = 2;
			}
		}
	}

	if( !bBOM && bHasBOM )
	{
		int bomsize = (encbo & 0xf00) >> 8;
		off += bomsize;
		len -= bomsize;
	}

	if( bBigEndian != bIsBigEndian && unisize >= 2 )
	{
		unsigned char* ptr = &bytes[0];
		ptr += off;
		int count = (len / unisize) * unisize;
		for( int i = 0 ; i < count ; i += unisize, ptr += unisize )
		{
			unsigned char h = ptr[1];
			ptr[1] = ptr[0];
			ptr[0] = h;
		}
	}
	else if( off > 0 )
		bytes.erase( bytes.begin(), bytes.begin() + off );
}

// Returns
//	bits 0-3:		encoding char size in bytes (1 = UTF-8, 2 = UTF-16 or UCS-2)
//	bit  4:			if BOM is included
//	bit  5:			if BigEndian (set) or LittleEndian (cleared)
//  bits 8-11:		BOM size in bytes
int XercesTreeOperations::GetEncodingAndByteOrderFromXml( std::vector<unsigned char>& sourceBytes )
{
	return sourceBytes.size() > 0 ?
		GetEncodingAndByteOrderFromXml( &sourceBytes[0], (int) sourceBytes.size() ) : 0;
}

// Returns
//	bits 0-3:		encoding char size in bytes (1 = UTF-8, 2 = UTF-16 or UCS-2)
//	bit  4:			if BOM is included
//	bit  5:			if BigEndian (set) or LittleEndian (cleared)
//  bits 8-11:		BOM size in bytes
int XercesTreeOperations::GetEncodingAndByteOrderFromXml( unsigned char* sourceBytes, int sourceLength )
{
	if( sourceBytes == NULL ) return 0;
	if( sourceLength < 2 ) return 0;

	if( ((sourceBytes[0] & 0xff) == 0xfe) && ((sourceBytes[1] & 0xff) == 0xff) )
		return 0x232;	// UTF-16BE with BOM

	if( ((sourceBytes[0] & 0xff) == 0xff) && ((sourceBytes[1] & 0xff) == 0xfe) )
		return 0x212;	// UTF-16LE with BOM

	if( ((sourceBytes[0] & 0xff) == 0x00) && ((sourceBytes[1] & 0xff) == 0x3c) )	// checks for "<" character
		return 0x022;	// UTF-16BE without BOM

	if( ((sourceBytes[0] & 0xff) == 0x3c) && ((sourceBytes[1] & 0xff) == 0x00) )	// checks for "<" character
		return 0x002;	// UTF-16LE without BOM

	if( sourceLength < 3 ) return 0;

	if( ((sourceBytes[0] & 0xff) == 0xef)
			&& ((sourceBytes[1] & 0xff) == 0xbb) && ((sourceBytes[2] & 0xff) == 0xbf) )
		return 0x311;	// UTF-8 with BOM

	return 0;
}

int XercesTreeOperations::GetUnicodeSizeFromEncodingName( const string_type& encodingIn )
{
	string_type encoding = Uppercase( encodingIn );

	if( encoding.find(_T("UTF-8")) != string_type::npos )
		return 1;

	if( encoding.find(_T("UTF-16")) != string_type::npos || encoding.find(_T("UCS-2")) != string_type::npos )
		return 2;

	return 0;
}

string_type XercesTreeOperations::Uppercase( const string_type& str )
{
	string_type result;
	result.reserve( str.length() );
	for (string_type::const_iterator it = str.begin(); it != str.end(); ++it)
		result.append( 1, _totupper(*it) );
	return result;
}

void XercesTreeOperations::SetAttribute(xercesc::DOMNode* node, const string_type& name, const string_type& namespaceURI, const string_type& value)
{
	string_type prefix;
	xercesc::DOMElement* el = (xercesc::DOMElement*) node;

	string_type localName = name;

	size_t i = name.find(_T(":"));
	if (i != string_type::npos)
	{
		localName = name.substr(i+1);
		prefix = name.substr(0, i);
	}

	if (!namespaceURI.empty() && name != _T("xmlns"))
	{
		string_type prefix2 = FindPrefixForNamespace(node, namespaceURI);
		if (prefix2.empty())
		{
			if (prefix.empty())
				prefix = FindUnusedPrefix(node);

			string_type qPrefix = _T("xmlns:") + prefix;
			el->setAttributeNS(XercesStringTemp(_T("http://www.w3.org/2000/xmlns/")), XercesStringTemp(qPrefix), XercesStringTemp(namespaceURI));
		}
		else
			prefix = prefix2;
	}
	
	if (!prefix.empty())
		prefix += _T(":");

	el->setAttributeNS(XercesStringTemp(namespaceURI), XercesStringTemp(prefix+localName), XercesStringTemp(value));
}


void XercesTreeOperations::SetAttribute(xercesc::DOMNode* node, const string_type& localName, const string_type& namespaceURI, const string_type& valueLocalName, const string_type& valueNamespaceURI)
{
	string_type prefix;
	if (!valueNamespaceURI.empty())
	{
		prefix = FindPrefixForNamespace(node, valueNamespaceURI);
		if (prefix.empty())
		{
			prefix = FindUnusedPrefix(node);
			xercesc::DOMElement* el = (xercesc::DOMElement*) node;
			string_type qPrefix = _T("xmlns:") + prefix;
			el->setAttributeNS(XercesStringTemp(_T("http://www.w3.org/2000/xmlns/")), XercesStringTemp(qPrefix), XercesStringTemp(valueNamespaceURI));
		}
		prefix += _T(":");
	}

	SetAttribute(node, localName, namespaceURI, prefix+valueLocalName);
}


