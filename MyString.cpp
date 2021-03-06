#include "MyString.h"

#include <cassert>
#include <cstring>
#include <utility>

// >> StringData implementation
StringData::StringData() {
    memset(&data, '\0', maxShortSize);
}

void StringData::save(const char* rawString, size_t size) {
    if (size > maxShortSize) {
        flag = _longFlag;
        data._long.size = size;
        data._long.data = new char[size];
        memcpy(data._long.data, rawString, size);
    }
    else {
        flag = _shortFlag;
        data._short.size = size;
        memcpy(data._short.data, rawString, size);
    }
}


size_t StringData::getSize() const {
    if (flag == _shortFlag) {
        return data._short.size;
    }
    return data._long.size;
}

const char* StringData::getString() const {
    return flag == _shortFlag ? data._short.data : data._long.data;
}

char* StringData::getString() {
    return flag == _shortFlag ? data._short.data : data._long.data;
}

void StringData::remove() {
    if (flag == _longFlag) {
        delete[] data._long.data;
        data._long.data = nullptr;
        data._long.size = 0;
    }
    else {
        memset(data._short.data, '\0', maxShortSize);
        data._short.size = 0;
    }
}
// << StringData implementation


MyString::MyString(const char* rawString) {
    if (rawString) {
        _size = strlen(rawString);
        _data = new char[_size];
        memcpy(_data, rawString, _size);
    }
}

MyString::MyString(const MyString& other) {
    _size = other._size;
    _data = new char[_size];
    memcpy(_data, other._data, _size);
}

MyString::MyString(MyString&& other) noexcept {
    _data = std::exchange(other._data, nullptr);
    _size = std::exchange(other._size, 0);
}

MyString& MyString::operator=(const MyString& other) {
    if (this != &other) {
        MyString copy(other);
        std::swap(_size, copy._size);
        std::swap(_data, copy._data);
    }
    return *this;
}

MyString& MyString::operator=(MyString&& other) noexcept {
    if (this != &other) {
        delete[] _data;
        _data = std::exchange(other._data, nullptr);
        _size = std::exchange(other._size, 0);
    }
    return *this;
}

char& MyString::at(const unsigned int idx) {
    assert(idx < size());
    return _data[idx];
}

const char& MyString::at(const unsigned int idx) const {
    assert(idx < size());
    return _data[idx];
}

char& MyString::operator[](const unsigned int idx) {
    return at(idx);
}

const char& MyString::operator[](const unsigned int idx) const {
    return at(idx);
}

MyString& MyString::operator+(const MyString& appendedString) {
    this->append(appendedString);
    return *this;
}

void MyString::append(const MyString& appendedString) {
    this->insert(_size, appendedString);
}

MyString::~MyString() {
    delete[] _data;
}

void MyString::insert(unsigned int pos, const MyString& insertedString) {
    char* newStr = new char[_size + insertedString._size];
    memcpy(newStr, _data, pos);
    memcpy(newStr + pos, insertedString._data, insertedString._size);
    memcpy(newStr + pos + insertedString._size, _data + pos, _size - pos);
    std::swap(newStr, _data);
    delete[] newStr;
    _size += insertedString._size;
}

void MyString::clear() {
    _size = 0;
    delete[] _data;
    _data = nullptr;
}

void MyString::erase(unsigned int pos, unsigned int count) {
    unsigned int newSize = _size > count ? _size - count : pos - 1;
    for (size_t i = pos; i < newSize; ++i) {
        _data[i] = _data[i + count];
    }
    char* newData = new char[newSize];
    memcpy(newData, _data, newSize);
    std::swap(newData, _data);
    _size = newSize;
    delete[] newData;
}

unsigned int MyString::size() const {
    return _size;
}

bool MyString::isEmpty() const {
    return !_size;
}

const char* MyString::rawString() const {
    char* str = new char[_size + 1];
    memcpy(str, _data, _size);
    str[_size] = '\0';
    return str;
}

unsigned int MyString::find(const MyString& substring, unsigned int pos) {
    if (this->isEmpty() || substring.isEmpty()) {
        return -1;
    }
    unsigned int res = -1;
    size_t count = 0;
    const size_t substrSize = substring._size;
    const size_t strSize = this->_size;
    for (int i = strSize - (substrSize - 1) - 1; i >= (int)pos; --i) {
        for (int j = i; j < strSize; ++j) {
            if (_data[j] == substring[count]) {
                count++;
            }
            else {
                break;
            }
        }
        if (count == substrSize) {
            res = i;
            break;
        }
        count = 0;
    }
    return res;

}

int MyString::compare(const MyString& comparableString) const {
    if (_size != comparableString._size) {
        return _size - comparableString._size;
    }
    else {
        for (size_t i = 0; i < _size; ++i) {
            if (_data[i] < comparableString[i]) {
                return -1;
            }
            else if (_data[i] > comparableString[i]) {
                return 1;
            }
        }
        return 0;
    }
}

bool MyString::operator!=(const MyString& comparableString) const {
    return !(*this == comparableString);
}

bool MyString::operator==(const MyString& comparableString) const {
    return this->compare(comparableString) == 0;
}

bool MyString::operator>(const MyString& comparableString) const {
    return this->compare(comparableString) > 0;
}

bool MyString::operator<(const MyString& comparableString) const {
    return this->compare(comparableString) < 0;
}

bool MyString::operator>=(const MyString& comparableString) const {
    return this->compare(comparableString) >= 0;
}

bool MyString::operator<=(const MyString& comparableString) const {
    return this->compare(comparableString) <= 0;
}
