#include "Entry.h"

#include <iostream>

using namespace std;

template<class KeyType, class ValueType>
Entry<KeyType, ValueType>::Entry() {}

template<class KeyType, class ValueType>
Entry<KeyType, ValueType>::Entry(const KeyType& searchKey, const ValueType& newValue)
    : key(searchKey), value(newValue) {
}

template<class KeyType, class ValueType>
ValueType Entry<KeyType, ValueType>::getValue() const {
    return value;
}

template<class KeyType, class ValueType>
KeyType Entry<KeyType, ValueType>::getKey() const {
    return key;
}

template<class KeyType, class ValueType>
void Entry<KeyType, ValueType>::setValue(const ValueType& newValue) {
    value = newValue;
}

template<class KeyType, class ValueType>
void Entry<KeyType, ValueType>::setKey(const KeyType& searchKey) {
    key = searchKey;
}

template<class KeyType, class ValueType>
bool Entry<KeyType, ValueType>::operator==(const Entry<KeyType, ValueType>& rightHandValue) const {
    return (key == rightHandValue.key);
}

template<class KeyType, class ValueType>
bool Entry<KeyType, ValueType>::operator>(const Entry<KeyType, ValueType>& rightHandValue) const {
    return (key > rightHandValue.key);
}

template class Entry<string, string>;
template class Entry<int, string>;