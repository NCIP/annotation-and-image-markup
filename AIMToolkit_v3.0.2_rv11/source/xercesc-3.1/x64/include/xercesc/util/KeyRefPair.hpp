/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: KeyRefPair.hpp 527149 2007-04-10 14:56:39Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_KEYREFPAIR_HPP)
#define XERCESC_INCLUDE_GUARD_KEYREFPAIR_HPP


#include <xercesc/util/XMemory.hpp>

XERCES_CPP_NAMESPACE_BEGIN

template <class TKey, class TValue> class KeyRefPair : public XMemory
{
    public  :
        // -------------------------------------------------------------------
        //  Constructors and Destructor
        // -------------------------------------------------------------------
        KeyRefPair();
        KeyRefPair(TKey* key, TValue* value);
        KeyRefPair(const KeyRefPair<TKey,TValue>* toCopy);
        KeyRefPair(const KeyRefPair<TKey,TValue>& toCopy);
        ~KeyRefPair();


        // -------------------------------------------------------------------
        //  Getters
        // -------------------------------------------------------------------
        const TKey* getKey() const;
        TKey* getKey();
        const TValue* getValue() const;
        TValue* getValue();


        // -------------------------------------------------------------------
        //  Setters
        // -------------------------------------------------------------------
        TKey* setKey(TKey* newKey);
        TValue* setValue(TValue* newValue);


    private :
        // unimplemented:        
        KeyRefPair<TKey,TValue>& operator=(const KeyRefPair<TKey,TValue>&);
        // -------------------------------------------------------------------
        //  Private data members
        //
        //  fKey
        //      The object that represents the key of the pair
        //
        //  fValue
        //      The object that represents the value of the pair
        // -------------------------------------------------------------------
        TKey*    fKey;
        TValue*  fValue;
};

XERCES_CPP_NAMESPACE_END

#if !defined(XERCES_TMPLSINC)
#include <xercesc/util/KeyRefPair.c>
#endif

#endif
