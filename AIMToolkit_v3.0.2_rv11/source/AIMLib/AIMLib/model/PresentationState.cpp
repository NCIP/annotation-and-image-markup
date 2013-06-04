/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"

#include "PresentationState.h"

using std::string;
using namespace aim_lib;

PresentationState::PresentationState(void)
{
}

PresentationState::PresentationState(const PresentationState& presentationState)
{
	_cagridId		= presentationState._cagridId;
	_sopInstanceUID	= presentationState._sopInstanceUID;
}

PresentationState::~PresentationState(void)
{
}

const string& PresentationState::GetSopInstanceUID() const
{
	return _sopInstanceUID;
}

void PresentationState::SetSopInstanceUID(const string& newVal)
{
	_sopInstanceUID = newVal;
}
