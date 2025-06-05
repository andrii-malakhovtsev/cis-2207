#ifndef DICTIONARY_INTERFACE_H
#define DICTIONARY_INTERFACE_H

#include "NotFoundException.h"

template<class KeyType, class ValueType>
class DictionaryInterface {
public:
    virtual ~DictionaryInterface() {}
    virtual bool isEmpty() const = 0;
    virtual int getNumberOfEntries() const = 0;
    virtual bool add(const KeyType& searchKey, const ValueType& newValue) = 0;
    virtual bool remove(const KeyType& searchKey) = 0;
    virtual void clear() = 0;
    virtual ValueType getValue(const KeyType& searchKey) const throw(NotFoundException) = 0;
    virtual bool contains(const KeyType& searchKey) const = 0;
    virtual void traverse(void visit(ValueType&)) const = 0;
};

#endif