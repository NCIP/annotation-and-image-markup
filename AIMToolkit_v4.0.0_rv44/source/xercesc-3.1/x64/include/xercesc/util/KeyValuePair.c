/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: KeyValuePair.c 471747 2006-11-06 14:31:56Z amassari $
 */


// ---------------------------------------------------------------------------
//  Include
// ---------------------------------------------------------------------------
#if defined(XERCES_TMPLSINC)
#include <xercesc/util/KeyValuePair.hpp>
#endif

XERCES_CPP_NAMESPACE_BEGIN

// ---------------------------------------------------------------------------
//  KeyValuePair: Constructors and Destructor
// ---------------------------------------------------------------------------
template <class TKey, class TValue> KeyValuePair<TKey,TValue>::KeyValuePair()
{
}

template <class TKey, class TValue> KeyValuePair<TKey,TValue>::
KeyValuePair(const TKey& key, const TValue& value) :

    fKey(key)
    , fValue(value)
{
}

template <class TKey, class TValue> KeyValuePair<TKey,TValue>::
KeyValuePair(const KeyValuePair<TKey,TValue>& toCopy) :

    fKey(toCopy.fKey)
    , fValue(toCopy.fValue)
{
}

template <class TKey, class TValue> KeyValuePair<TKey,TValue>::~KeyValuePair()
{
}


// ---------------------------------------------------------------------------
//  KeyValuePair: Getters
// ---------------------------------------------------------------------------
template <class TKey, class TValue> const TKey&
KeyValuePair<TKey,TValue>::getKey() const
{
    return fKey;

}

template <class TKey, class TValue> TKey& KeyValuePair<TKey,TValue>::getKey()
{
    return fKey;
}

template <class TKey, class TValue> const TValue&
KeyValuePair<TKey,TValue>::getValue() const
{
    return fValue;
}

template <class TKey, class TValue> TValue& KeyValuePair<TKey,TValue>::getValue()
{
    return fValue;
}


// ---------------------------------------------------------------------------
//  KeyValuePair: Setters
// ---------------------------------------------------------------------------
template <class TKey, class TValue> TKey&
KeyValuePair<TKey,TValue>::setKey(const TKey& newKey)
{
    fKey = newKey;
    return fKey;
}

template <class TKey, class TValue> TValue&
KeyValuePair<TKey,TValue>::setValue(const TValue& newValue)
{
    fValue = newValue;
    return fValue;
}

XERCES_CPP_NAMESPACE_END
