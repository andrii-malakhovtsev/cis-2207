// Andrii Malakhovtsev
// CIS 2207 501
// 03.30.2025
// Array Dictionary

#ifndef ARRAY_DICTIONARY_H
#define ARRAY_DICTIONARY_H

#include "DictionaryInterface.h"
#include "Entry.h"
#include "NotFoundException.h"
#include "PrecondViolatedExcept.h"

#include <memory>
#include <algorithm>

using namespace std;

template <class KeyType, class ValueType>
class ArrayDictionary : public DictionaryInterface<KeyType, ValueType> {
private:
    static const int DEFAULT_CAPACITY = 21;
    unique_ptr<Entry<KeyType, ValueType>[]> entries;
    int entryCount;
    int maxEntries;

    void destroyDictionary();
    int findEntryIndex(int firstIndex, int lastIndex, const KeyType& searchKey) const;

public:
    ArrayDictionary();
    ArrayDictionary(int maxNumberOfEntries);
    ArrayDictionary(const ArrayDictionary<KeyType, ValueType>& dictionary);
    virtual ~ArrayDictionary();

    bool isEmpty() const override;
    int getNumberOfEntries() const override;
    bool add(const KeyType& searchKey, const ValueType& newValue) throw(PrecondViolatedExcept)override;
    bool remove(const KeyType& searchKey) override;
    void clear() override;
    ValueType getValue(const KeyType& searchKey) const throw(NotFoundException)override;
    bool contains(const KeyType& searchKey) const override;
    void traverse(void visit(ValueType&)) const override;
};

extern template class ArrayDictionary<string, string>;
extern template class ArrayDictionary<int, string>;

#endif