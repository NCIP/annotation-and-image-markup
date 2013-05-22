/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/**
 * $Id: KeyRefPair.c 471747 2006-11-06 14:31:56Z amassari $
 */


// ---------------------------------------------------------------------------
//  Include
// ---------------------------------------------------------------------------
#if defined(XERCES_TMPLSINC)
#include <xercesc/util/KeyRefPair.hpp>
#endif

XERCES_CPP_NAMESPACE_BEGIN

// ---------------------------------------------------------------------------
//  KeyRefPair: Constructors and Destructor
// ---------------------------------------------------------------------------
template <class TKey, class TValue> KeyRefPair<TKey,TValue>::KeyRefPair()
{
}

template <class TKey, class TValue> KeyRefPair<TKey,TValue>::
KeyRefPair(TKey* key, TValue* value) :

    fKey(key)
    , fValue(value)
{
}

template <class TKey, class TValue> KeyRefPair<TKey,TValue>::
KeyRefPair(const KeyRefPair<TKey,TValue>* toCopy) :

    fKey(toCopy->fKey)
    , fValue(toCopy->fValue)
{
}

template <class TKey, class TValue> KeyRefPair<TKey,TValue>::
KeyRefPair(const KeyRefPair<TKey,TValue>& toCopy) :

    fKey(toCopy.fKey)
    , fValue(toCopy.fValue)
{
}


template <class TKey, class TValue> KeyRefPair<TKey,TValue>::~KeyRefPair()
{
}


// ---------------------------------------------------------------------------
//  KeyRefPair: Getters
// ---------------------------------------------------------------------------
template <class TKey, class TValue> const TKey*
KeyRefPair<TKey,TValue>::getKey() const
{
    return fKey;

}

template <class TKey, class TValue> TKey* KeyRefPair<TKey,TValue>::getKey()
{
    return fKey;
}

template <class TKey, class TValue> const TValue*
KeyRefPair<TKey,TValue>::getValue() const
{
    return fValue;
}

template <class TKey, class TValue> TValue* KeyRefPair<TKey,TValue>::getValue()
{
    return fValue;
}


// ---------------------------------------------------------------------------
//  KeyRefPair: Setters
// ---------------------------------------------------------------------------
template <class TKey, class TValue> TKey*
KeyRefPair<TKey,TValue>::setKey(TKey* newKey)
{
    fKey = newKey;
    return fKey;
}

template <class TKey, class TValue> TValue*
KeyRefPair<TKey,TValue>::setValue(TValue* newValue)
{
    fValue = newValue;
    return fValue;
}

XERCES_CPP_NAMESPACE_END
