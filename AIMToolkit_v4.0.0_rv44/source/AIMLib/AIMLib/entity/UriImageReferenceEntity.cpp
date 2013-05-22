/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "../stdafx.h"

#include "Entity.h"
#include "ImageReferenceEntity.h"
#include "UriImageReferenceEntity.h"

#include "../memdebug.h"

using std::string;
using namespace aim_lib;

UriImageReferenceEntity::UriImageReferenceEntity() : ImageReferenceEntity(C_URI_IMAGE_REFERENCE_NAME){
}

UriImageReferenceEntity::UriImageReferenceEntity(const UriImageReferenceEntity& imageReference) : ImageReferenceEntity(imageReference) {
	_uri		= imageReference._uri;
	_mimeType	= imageReference._mimeType;
}

UriImageReferenceEntity::~UriImageReferenceEntity(){
}

UriImageReferenceEntity* UriImageReferenceEntity::Clone() const{
	return new UriImageReferenceEntity(*this);
}

ImageReferenceEntity::ImageReferenceEntityType UriImageReferenceEntity::GetImageReferenceEntityType() const{
	return T_URI_IMAGE_REF;
}

const string& UriImageReferenceEntity::GetUri() const{
	return _uri;
}

const string& UriImageReferenceEntity::GetMimeType() const{
	return _mimeType;
}

void UriImageReferenceEntity::SetUri(const string& newVal){
	_uri = newVal;
}

void UriImageReferenceEntity::SetMimeType(const string& newVal){
	_mimeType = newVal;
}
