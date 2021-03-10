#include "MyString.h"

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <algorithm>

MyString::MyString(const char* rawString) {
    this->_size = 0;
    this->_data = nullptr;
    if (rawString != nullptr) {
        this->_size = std::strlen(rawString);
        this->_data = new char[this->size()];
        for (size_t i = 0; i < this->size(); i++) {
            this->at(i) = rawString[i];
        }
    }
}

MyString::MyString(const MyString& other) {
    this->_size = other.size();
    this->_data = new char[other.size()];
    for (size_t i = 0; i < this->size(); i++) {
        this->at(i) = other[i];
    }
}

MyString::MyString(MyString&& other) noexcept {
    this->_size = other.size();
    this->_data = other._data;
    other._size = 0;
    other._data = nullptr;
}

MyString& MyString::operator=(const MyString& other) {
    this->_size = other.size();
    delete[] this->_data;
    this->_data = nullptr;
    if (!other.isEmpty()) {
        this->_data = new char[other.size()];
        for (size_t i = 0; i < this->size(); i++) {
            this->at(i) = other[i];
        }
    }
    return *this;
}

MyString& MyString::operator=(MyString&& other) noexcept {
    this->_size = other.size();
    std::swap(this->_data, other._data);
    delete[] other._data; 
    other._data = nullptr;
    other._size = 0;
    return *this;
}
    
MyString::~MyString() {
    this->_size = 0;
    delete[] this->_data;
    this->_data = nullptr;
}

char& MyString::at(const unsigned int idx) {
    assert(idx < size());
    return _data[idx];
}

const char& MyString::at(const unsigned int idx) const {
    assert(idx < size());
    return _data[idx];
}


void MyString::append(const MyString& appendedString) {
    this->insert(size(), appendedString);
}

void MyString::insert(unsigned int pos, const MyString& insertedString) {
    assert(pos <= this->size());
    char* newData = new char[this->size() + insertedString.size()];
    for (size_t i = 0; i < this->size(); i++) {
        newData[i] = this->at(i);
    }
    for (int i = (int)(this->size() + insertedString.size()) - 1; i >= (int)(pos + insertedString.size()); i--) {
        newData[i] = this->at(i - insertedString.size());
    }
    for (size_t i = pos; i < pos + insertedString.size(); i++) {
        newData[i] = insertedString[i - pos];
    }
    this->_size += insertedString.size();
    delete[] this->_data;
    this->_data = newData;
}

void MyString::clear() {
    delete[] this->_data;
    this->_size = 0;
    this->_data = nullptr;
}

void MyString::erase(unsigned int pos, unsigned int count) {
    assert(pos <= this->size());
    size_t realCount = count;
    if (count > this->size() - pos) {
        realCount = this->size() - pos;
    }
    char* newData = new char[this->size() - realCount];
    for (size_t i = 0; i < this->size() - realCount; i++) {
        newData[i] = this->at(i);
    }
    for (int i = (int)(this->size() - realCount) - 1; i >= (int)pos; i--) {
        newData[i] = this->at(i + realCount);
    }
    this->_size -= realCount;
    delete[] this->_data;
    this->_data = nullptr;
    if (this->size() != 0) {
        this->_data = newData;
    }
}
    
unsigned int MyString::size() const { 
    return this->_size;
}

bool MyString::isEmpty() const {
    return this->_size == 0;
}

const char* MyString::rawString() const {
    char* resString = new char[this->size() + 1];
    for (size_t i = 0; i < this->size(); i++) {
        resString[i] = this->at(i);
    }
    resString[this->size()] = '\0';
    return resString;
}

unsigned int MyString::find(const MyString& substring, const unsigned int pos) {
    assert(pos <= this->size());
    for (size_t i = pos; i < this->size() - substring.size() + 1; i++) {
        bool equal = true;
        for (size_t j = i; j < i + substring.size(); j++) {
            if (this->at(j) != substring[j - i]) {
                equal = false;
                break;
            }
        }
        if (equal) {
            return i;
        }
    }
    return -1;
}
    
int MyString::compare(const MyString& comparableString) const {
    size_t count = comparableString.size();
    if (this->size() != comparableString.size()) {
        return this->size() < comparableString.size() ? -1 : 1;
    }
    for (size_t i = 0; i < count; i++) {
        if (this->at(i) < comparableString[i]) {
            return -1;
        }
        else if (this->at(i) > comparableString[i]) {
            return 1;
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
    return (this->compare(comparableString) == 0);
}
bool MyString::operator!=(const MyString& comparableString) const {
    return !(*this == comparableString);
}
bool MyString::operator>(const MyString& comparableString) const {
    return (this->compare(comparableString) > 0);
}
bool MyString::operator<(const MyString& comparableString) const {
    return (this->compare(comparableString) < 0);
}
bool MyString::operator>=(const MyString& comparableString) const {
    return (*this > comparableString || *this == comparableString);
}
bool MyString::operator<=(const MyString& comparableString) const {
    return !(*this >= comparableString);
}
