#include "MyString.h"

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <algorithm>

MyStringNS::MyString::MyString(const char* rawString) {
    _type.stringType.longString._size = 0;
    _type.isLong = false;
    if (rawString == nullptr) {
        return;
    }
    size_t len = strlen(rawString);
    if (len >= sizeof(MyStringNS::StringRepresentation::Type::Long) - sizeof(char)) {
        _type.isLong = true;
        _type.stringType.longString._size = len;
        _type.stringType.longString._data = new char[size()];
    }
    else {
        _type.isLong = false;
        _type.stringType.shortString._size = len;
    }
    for (unsigned int i = 0; i < size(); ++i) {
        (*this)[i] = rawString[i];
    }
}

MyStringNS::MyString::MyString(const MyString& other) {
    if (this == &other) {
        _type.stringType.shortString._size = 0;
        _type.isLong = false;
        return;
    }
    _type.isLong = other._type.isLong;
    if (_type.isLong) {
        _type.stringType.longString._data = new char[size()];
        _type.stringType.longString._size = other.size();
    }
    else {
        _type.stringType.shortString._size = other.size();
    }
    for (unsigned int i = 0; i < size(); ++i) {
        (*this)[i] = other[i];
    }
}

MyStringNS::MyString::MyString(MyString&& other) noexcept {
    std::swap(_type.isLong, other._type.isLong);
    if (_type.isLong) {
        std::swap(_type.stringType.longString._size,
                  other._type.stringType.longString._size);
        std::swap(_type.stringType.longString._data,
                  other._type.stringType.longString._data);
    }
    else {
        std::swap(_type.stringType.shortString._size,
                  _type.stringType.shortString._size);
        for (unsigned int i = 0; i < size(); ++i) {
            std::swap((*this)[i],
                      other[i]);
        }
    }
}

MyStringNS::MyString& MyStringNS::MyString::operator=(const MyString& other) {
    _type.isLong = other._type.isLong;
    if (_type.isLong) {
        _type.stringType.longString._size = other.size();
        _type.stringType.longString._data = new char[size()];
    }
    else {
        _type.stringType.shortString._size = other.size();
    }
    for (unsigned int i = 0; i < size(); ++i) {
        (*this)[i] = other[i];
    }
    return *this;
}

MyStringNS::MyString& MyStringNS::MyString::operator=(MyString&& other) noexcept {
    if (other._type.isLong) {
        std::swap(_type.stringType.longString._size, other._type.stringType.longString._size);
        std::swap(_type.stringType.longString._data, other._type.stringType.longString._data);
        if (other._type.isLong) {
            delete[] other._type.stringType.longString._data;
            other._type.stringType.longString._data = nullptr;
        }
        _type.isLong = true;
    }
    else {
        _type.isLong = false;
        _type.stringType.shortString._size = other.size();
        for (unsigned int i = 0; i < size(); ++i) {
            (*this)[i] = other[i];
        }
    }
    other._type.stringType.shortString._size = 0;
    other._type.isLong = false;
    return *this;
}

MyStringNS::MyString::~MyString() {
    _type.stringType.shortString._size = 0;
    if (_type.isLong) {
        delete[] _type.stringType.longString._data;
        _type.stringType.longString._data = nullptr;
    }
    _type.isLong = false;
}

void MyStringNS::MyString::append(const MyString& appendedString) {
    insert(size(), appendedString);
}

void MyStringNS::MyString::insert(unsigned int pos, const MyString& insertedString) {
    assert(pos <= size());
    if (size() + insertedString.size() >= sizeof(MyStringNS::StringRepresentation::Type::Long) - sizeof(char)){
        char* newData = new char[size() + insertedString.size()];
        unsigned int i = 0, endPos = pos + insertedString.size();
        for (; i < pos; ++i) {
            newData[i] = (*this)[i];
        }
        for (; i < endPos; ++i) {
            newData[i] = insertedString[i - pos];
        }
        for (; i < size() + insertedString.size(); ++i) {
            newData[i] = (*this)[i - insertedString.size()];
        }
        if (_type.isLong) {
            delete[] _type.stringType.longString._data;
        }
        _type.stringType.longString._size = size() + insertedString.size();
        _type.stringType.longString._data = newData;
        _type.isLong = true;
    }
    else {
        _type.stringType.shortString._size += insertedString.size();
        unsigned int endPos = pos + insertedString.size();
        for (unsigned int i = endPos; i < size(); ++i) {
            (*this)[i] = (*this)[i - insertedString.size()];
        }
        for (unsigned int i = pos; i < endPos; ++i) {
            (*this)[i] = insertedString[i - pos];
        }
    }
}

void MyStringNS::MyString::clear() {
    _type.stringType.shortString._size = 0;
    if (_type.isLong) {
        delete[] _type.stringType.longString._data;
        _type.stringType.longString._data = nullptr;
    }
    _type.isLong = false;
}

void MyStringNS::MyString::erase(unsigned int pos, unsigned int charCount) {
    assert(pos <= size());
    if (pos == 0 && (charCount >= size())) {
        clear();
        return;
    }
    if (charCount > (size() - pos)) {
        charCount = size() - pos;
    }
    if ((size() - charCount) > sizeof(MyStringNS::StringRepresentation::Type::Long) - sizeof(char)) {
        char* newData = new char[size() - charCount];
        for (unsigned int i = 0; i < pos; ++i) {
            newData[i] = (*this)[i];
        }
        for (unsigned int i = pos + charCount; i < size(); ++i) {
            newData[i - charCount] = (*this)[i];
        }
        _type.stringType.longString._size -= charCount;
        delete[] _type.stringType.longString._data;
        _type.stringType.longString._data = newData;
    }
    else {
        if (_type.isLong) {
            std::size_t oldSize = size();
            _type.isLong = false;
            _type.stringType.shortString._size = oldSize - charCount;
            char* oldData = _type.stringType.longString._data;
            for (unsigned int i = 0; i < pos; ++i) {
                (*this)[i] = oldData[i];
            }
            for (unsigned int i = pos + charCount; i < oldSize; ++i) {
                (*this)[i - charCount] = oldData[i];
            }
            delete[] oldData;
        }
        else {
            for (unsigned int i = pos + charCount; i < size(); ++i) {
                (*this)[i - charCount] = (*this)[i];
            }
            _type.stringType.shortString._size -= charCount;
        }
    }
}

char& MyStringNS::MyString::at(const unsigned int idx) {
    assert(idx < size());
    if (_type.isLong) {
        return _type.stringType.longString._data[idx];
    }
    else {
        return _type.stringType.shortString._data[idx];
    }
}

const char& MyStringNS::MyString::at(const unsigned int idx) const {
    assert(idx < size());
    if (_type.isLong) {
        return _type.stringType.longString._data[idx];
    }
    else {
        return _type.stringType.shortString._data[idx];
    }
}

unsigned int MyStringNS::MyString::size() const {
    if (_type.isLong) {
        return _type.stringType.longString._size;
    }
    else {
        return _type.stringType.shortString._size;
    }
}

bool MyStringNS::MyString::isEmpty() const {
    return !(size());
}

const char* MyStringNS::MyString::rawString() const {
    char* result = new char[size() + 1];
    for (unsigned int i = 0; i < size(); ++i) {
        result[i] = (*this)[i];
    }
    result[size()] = '\0';
    return result;
}

unsigned int MyStringNS::MyString::find(const MyString& substring, unsigned int pos) {
    if (substring.size() == 0) {
        return 0;
    }
    unsigned int tempSize = size() - substring.size();
    for (unsigned int i = pos; i <= tempSize; ++i) {
        unsigned int endSub = i + substring.size();
        for (unsigned int j = i; j < endSub; ++j) {
            if ((*this)[j] != substring[j - i]) {
                break;
            }
            if (j == endSub - 1) {
                return i;
            }
        }
    }
    return -1;
}

int MyStringNS::MyString::compare(const MyString& comparableString) const {
    if (size() > comparableString.size()) {
        return 1;
    }
    else if (size() < comparableString.size()) {
        return -1;
    }
    for (unsigned int i = 0; i < size(); ++i) {
        if ((*this)[i] > comparableString[i]) {
            return 1;
        }
        if ((*this)[i] < comparableString[i]) {
            return -1;
        }
    }
    return 0;
}

char& MyStringNS::MyString::operator[](const unsigned int idx) {
    return at(idx);
}

const char& MyStringNS::MyString::operator[](const unsigned int idx) const {
    return at(idx);
}

MyStringNS::MyString& MyStringNS::MyString::operator+(const MyString& appendedString) {
    this->append(appendedString);
    return *this;
}

bool MyStringNS::MyString::operator==(const MyString& comparableString) const {
    return !(this->compare(comparableString));
}

bool MyStringNS::MyString::operator!=(const MyString& comparableString) const {
    return this->compare(comparableString);
}

bool MyStringNS::MyString::operator>(const MyString& comparableString) const {
    return (this->compare(comparableString) == 1);
}

bool MyStringNS::MyString::operator<(const MyString& comparableString) const {
    return (this->compare(comparableString) == -1);
}

bool MyStringNS::MyString::operator>=(const MyString& comparableString) const {
    return (this->compare(comparableString) == 1
          || this->compare(comparableString) == 0);
}

bool MyStringNS::MyString::operator<=(const MyString& comparableString) const {
    return (this->compare(comparableString) == -1
          || this->compare(comparableString) == 0);
}


