#ifndef ENTRY_H
#define ENTRY_H

#include <iostream>

using namespace std;

template<class KeyType, class ValueType>
class Entry {
private:
    KeyType key;
    ValueType value;

protected:
    void setKey(const KeyType& searchKey);

public:
    Entry();
    Entry(const KeyType& searchKey, const ValueType& newValue);
    ValueType getValue() const;
    KeyType getKey() const;
    void setValue(const ValueType& newValue);

    bool operator==(const Entry<KeyType, ValueType>& rightHandValue) const;
    bool operator>(const Entry<KeyType, ValueType>& rightHandValue) const;
};

extern template class Entry<string, string>;
extern template class Entry<int, string>;

#endif