#include "MyString.h"

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <stdexcept>

MyString::MyString(const char* rawString) {
    if (rawString != nullptr) {
        size_t length = std::strlen(rawString);
        _data.resize(length);
        for (size_t i = 0; i < this->size(); i++) {
            this->at(i) = rawString[i];
        }
    }
}

MyString::MyString(const MyString& other) {
    _data.resize(other.size());
    for (size_t i = 0; i < this->size(); i++) {
        this->at(i) = other[i];
    }
}

MyString::MyString(MyString&& other) noexcept {
    _data = std::move(other._data);
}

MyString::~MyString() {
    this->clear();
}

MyString& MyString::operator=(const MyString& other) {
    _data.resize(other.size());
    if (!other.isEmpty()) {
        for (size_t i = 0; i < this->size(); i++) {
            this->at(i) = other[i];
        }
    }
    return *this;
}

MyString& MyString::operator=(MyString&& other) noexcept {
    if (*this != other) {
        _data = std::move(other._data);
    }
    return *this;
}

char& MyString::at(const unsigned int idx) {
    if (idx >= this->size()) {
        throw std::out_of_range("At out of range");
    }
    return _data.at(idx);
}

const char& MyString::at(const unsigned int idx) const {
    if (idx >= this->size()) {
        throw std::out_of_range("At out of range");
    }
    return _data.at(idx);
}


void MyString::append(const MyString& appendedString) {
    this->insert(size(), appendedString);
}

void MyString::insert(unsigned int pos, const MyString& insertedString) {
    if (pos > this->size()) {
        throw std::out_of_range("Insert out of range");
    }
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
    _data.resize(this->size() + insertedString.size());
    for (size_t i = 0; i < this->size(); i++) {
        this->at(i) = newData[i];
    }
    delete[] newData;
}

void MyString::clear() {
    _data.resize(0);
}

void MyString::erase(unsigned int pos, unsigned int count) {
    if (pos > this->size()) {
        throw std::out_of_range("Erase out of range");
    }
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
    _data.resize(this->size() - realCount);
    if (this->size() != 0) {
        for (size_t i = 0; i < this->size(); i++) {
            this->at(i) = newData[i];
        }
    }
    delete[] newData;
}
    
unsigned int MyString::size() const { 
    return _data.size();
}

bool MyString::isEmpty() const {
    return size() == 0;
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
    if (pos > this->size()) {
        throw std::out_of_range("Find out of range");
    }
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
