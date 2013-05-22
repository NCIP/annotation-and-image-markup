/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "../stdafx.h"
#include "DicomTagCollection.h"

using namespace aim_lib;

const std::string DicomTagCollection::_emptyStr = std::string("");

DicomTagCollection::DicomTagCollection(void)
{

}

DicomTagCollection::DicomTagCollection(const DicomTagCollection& tagCollection)
{
	_tagValues.clear();
	_tagValues.insert(tagCollection._tagValues.begin(), tagCollection._tagValues.end());
}

DicomTagCollection::~DicomTagCollection(void)
{
	_tagValues.clear();
}

void DicomTagCollection::SetTagValue(AIM_DCM_TAG tag, const std::string& tagValue)
{
	// remove the existing item
	this->RemoveTag(tag);
	// save the new value
	_tagValues[tag] = tagValue;
}

const std::string& DicomTagCollection::GetTagValue(AIM_DCM_TAG tag) const
{
	MapDcmValues::const_iterator existingTags = _tagValues.find(tag);
	if (existingTags == _tagValues.end())
		return _emptyStr;
	else
		return existingTags->second;
}

void DicomTagCollection::RemoveTag(AIM_DCM_TAG tag)
{
	MapDcmValues::iterator existingTags = _tagValues.find(tag);
	if (existingTags != _tagValues.end())
		_tagValues.erase(existingTags);
}

bool DicomTagCollection::HasTag(AIM_DCM_TAG tag) const
{
	return _tagValues.find(tag) != _tagValues.end();
}
