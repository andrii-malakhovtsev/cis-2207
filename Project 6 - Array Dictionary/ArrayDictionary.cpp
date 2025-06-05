#include "ArrayDictionary.h"

#include <iostream> 

using namespace std;

template<class KeyType, class ValueType>
ArrayDictionary<KeyType, ValueType>::ArrayDictionary() 
    : entryCount(0), maxEntries(DEFAULT_CAPACITY) {
    entries = make_unique<Entry<KeyType, ValueType>[]>(DEFAULT_CAPACITY);
}

template<class KeyType, class ValueType>
ArrayDictionary<KeyType, ValueType>::ArrayDictionary(int maxNumberOfEntries)
    : entryCount(0), maxEntries(maxNumberOfEntries) {
    entries = make_unique<Entry<KeyType, ValueType>[]>(maxNumberOfEntries);
}

template<class KeyType, class ValueType>
ArrayDictionary<KeyType, ValueType>::ArrayDictionary(const ArrayDictionary<KeyType, ValueType>& dictionary)
    : entryCount(dictionary.entryCount), maxEntries(dictionary.maxEntries) {
    entries = make_unique<Entry<KeyType, ValueType>[]>(maxEntries);
    for (int i = 0; i < entryCount; i++) {
        entries[i] = dictionary.entries[i];
    }
}

template<class KeyType, class ValueType>
ArrayDictionary<KeyType, ValueType>::~ArrayDictionary() {
    destroyDictionary();
}

template<class KeyType, class ValueType>
void ArrayDictionary<KeyType, ValueType>::destroyDictionary() {
    clear();
}

template<class KeyType, class ValueType>
bool ArrayDictionary<KeyType, ValueType>::isEmpty() const {
    return entryCount == 0;
}

template<class KeyType, class ValueType>
int ArrayDictionary<KeyType, ValueType>::getNumberOfEntries() const {
    return entryCount;
}

template<class KeyType, class ValueType>
bool ArrayDictionary<KeyType, ValueType>::add(const KeyType& searchKey, const ValueType& newValue) throw(PrecondViolatedExcept) {
    bool ableToAdd = (entryCount < maxEntries);

    if (ableToAdd) {
        if (contains(searchKey)) {
            throw PrecondViolatedExcept("Attempt to add entry with duplicate key.");
        }

        entries[entryCount] = Entry<KeyType, ValueType>(searchKey, newValue);
        entryCount++;

        sort(entries.get(), entries.get() + entryCount,
            [](const Entry<KeyType, ValueType>& a, const Entry<KeyType, ValueType>& b) {
                return a.getKey() < b.getKey();
            });

        return true;
    }
    return false;
}

template<class KeyType, class ValueType>
bool ArrayDictionary<KeyType, ValueType>::remove(const KeyType& searchKey) {
    int foundIndex = findEntryIndex(0, entryCount - 1, searchKey);
    bool ableToRemove = (foundIndex >= 0);

    if (ableToRemove) {
        for (int i = foundIndex; i < entryCount - 1; i++) {
            entries[i] = entries[i + 1];
        }
        entryCount--;
        return true;
    }
    return false;
}

template<class KeyType, class ValueType>
void ArrayDictionary<KeyType, ValueType>::clear() {
    entryCount = 0;
}

template<class KeyType, class ValueType>
ValueType ArrayDictionary<KeyType, ValueType>::getValue(const KeyType& searchKey) const throw(NotFoundException) {
    int foundIndex = findEntryIndex(0, entryCount - 1, searchKey);

    if (foundIndex >= 0) {
        return entries[foundIndex].getValue();
    }
    else {
        throw NotFoundException("Entry not found in the dictionary.");
    }
}

template<class KeyType, class ValueType>
bool ArrayDictionary<KeyType, ValueType>::contains(const KeyType& searchKey) const {
    return findEntryIndex(0, entryCount - 1, searchKey) >= 0;
}

template<class KeyType, class ValueType>
void ArrayDictionary<KeyType, ValueType>::traverse(void visit(ValueType&)) const {
    for (int i = 0; i < entryCount; i++) {
        ValueType value = entries[i].getValue();
        visit(value);
    }
}

template<class KeyType, class ValueType>
int ArrayDictionary<KeyType, ValueType>::findEntryIndex(int firstIndex, int lastIndex, const KeyType& searchKey) const {
    while (firstIndex <= lastIndex) {
        int mid = firstIndex + (lastIndex - firstIndex) / 2;
        if (entries[mid].getKey() == searchKey) {
            return mid;
        }
        else if (entries[mid].getKey() > searchKey) {
            lastIndex = mid - 1;
        }
        else {
            firstIndex = mid + 1;
        }
    }
    return -1;
}

template class ArrayDictionary<string, string>;
template class ArrayDictionary<int, string>;