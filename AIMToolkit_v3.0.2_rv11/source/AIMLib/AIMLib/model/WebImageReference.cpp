/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "../stdafx.h"

#include "AimBase.h"
#include "ImageReference.h"
#include "WebImageReference.h"

#include "../memdebug.h"

using std::string;
using namespace aim_lib;

WebImageReference::WebImageReference() : ImageReference(C_WEB_IMAGE_NAME){

}

WebImageReference::WebImageReference(const WebImageReference& imageReference) : ImageReference(imageReference) {
	_uri = imageReference._uri;
}

WebImageReference::~WebImageReference(){

}

ImageReference* WebImageReference::Clone() const{
	return new WebImageReference(*this);
}

const string& WebImageReference::GetURI() const{

	return _uri;
}

void WebImageReference::SetURI(const string& newVal){

	_uri = newVal;
}
