#include "MyString.h"

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <algorithm>

MyString::MyString(const char* rawString) {
    _size = 0;
    _data = nullptr;
    if (rawString == nullptr) {
        return;
    }
    for (int i = 0; rawString[i] != '\0'; ++i) {
        ++_size;
    }
    _data = new char[_size];
    for (unsigned int i = 0; i < _size; ++i) {
        _data[i] = rawString[i];
    }
}

MyString::MyString(const MyString& other) {
    if (this == &other) {
        _size = 0;
        _data = nullptr;
    }
    _size = other._size;
    _data = new char[_size];
    for (unsigned int i = 0; i < _size; ++i) {
        _data[i] = other._data[i];
    }
}

MyString::MyString(MyString&& other) noexcept {
    std::swap(_size, other._size);
    std::swap(_data, other._data);
}

MyString& MyString::operator=(const MyString& other) {
    _size = other._size;
    _data = new char[_size];
    for (unsigned int i = 0; i < _size; ++i) {
        _data[i] = other._data[i];
    }
    return *this;
}

MyString& MyString::operator=(MyString&& other) noexcept {
    std::swap(_size, other._size);
    std::swap(_data, other._data);
    other._size = 0;
    delete[] other._data;
    other._data = nullptr;
    return *this;
}

MyString::~MyString() {
    _size = 0;
    delete[] _data;
    _data = nullptr;
}

void MyString::append(const MyString& appendedString) {
    insert(_size, appendedString);
}

void MyString::insert(unsigned int pos, const MyString& insertedString) {
    assert(pos <= size());
    _size += insertedString._size;
    char* newData = new char[_size];
    for (unsigned int i = 0; i < pos; ++i) {
        newData[i] = _data[i];
    }
    unsigned int endPos = pos + insertedString._size;
    for (unsigned int i = pos; i < endPos; ++i) {
        newData[i] = insertedString._data[i - pos];
    }
    for (unsigned int i = endPos; i < _size; ++i) {
        newData[i] = _data[i - insertedString._size];
    }
    delete[] _data;
    _data = newData;
}

void MyString::clear() {
    _size = 0;
    delete[] _data;
    _data = nullptr;
}

void MyString::erase(unsigned int pos, unsigned int charCount) {
    assert(pos <= size());
    if (pos == 0 && charCount >= _size) {
        clear();
        return;
    }
    if (charCount > _size - pos) {
        charCount = _size - pos;
    }
    char* newData = new char[_size - charCount];
    for (unsigned int i = 0; i < pos; ++i) {
        newData[i] = _data[i];
    }
    for (unsigned int i = pos + charCount; i < _size; ++i) {
        newData[i - charCount] = _data[i];
    }
    _size -= charCount;
    delete[] _data;
    _data = newData;
}

char& MyString::at(const unsigned int idx) {
    assert(idx < size());
    return _data[idx];
}

const char& MyString::at(const unsigned int idx) const {
    assert(idx < size());
    return _data[idx];
}

unsigned int MyString::size() const {
    return _size;
}

bool MyString::isEmpty() const {
    return !(_size);
}

const char* MyString::rawString() const {
    char* result = new char[_size + 1];
    for (unsigned int i = 0; i < _size; ++i) {
        result[i] = _data[i];
    }
    result[_size] = '\0';
    return result;
}

unsigned int MyString::find(const MyString& substring, unsigned int pos) {
    if (substring._size == 0) {
        return 0;
    }
    unsigned int tempSize = _size - substring._size;
    for (unsigned int i = pos; i <= tempSize; ++i) {
        unsigned int endSub = i + substring._size;
        for (unsigned int j = i; j < endSub; ++j) {
            if (_data[j] != substring._data[j - i]) {
                break;
            }
            if (j == endSub - 1) {
                return i;
            }
        }
    }
    return -1;
}

int MyString::compare(const MyString& comparableString) const {
    if (_size > comparableString._size) {
        return 1;
    }
    else if (_size < comparableString._size) {
        return -1;
    }
    for (unsigned int i = 0; i < _size; ++i) {
        if (_data[i] > comparableString[i]) {
            return 1;
        }
        if (_data[i] < comparableString[i]) {
            return -1;
        }
    }
    return 0;
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

bool MyString::operator==(const MyString& comparableString) const {
    return !(this->compare(comparableString));
}

bool MyString::operator!=(const MyString& comparableString) const {
    return this->compare(comparableString);
}

bool MyString::operator>(const MyString& comparableString) const {
    return (this->compare(comparableString) == 1);
}

bool MyString::operator<(const MyString& comparableString) const {
    return (this->compare(comparableString) == -1);
}

bool MyString::operator>=(const MyString& comparableString) const {
    return (this->compare(comparableString) == 1
          || this->compare(comparableString) == 0);
}

bool MyString::operator<=(const MyString& comparableString) const {
    return (this->compare(comparableString) == -1
          || this->compare(comparableString) == 0);
}

