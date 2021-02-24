#include "MyString.h"

#include <cassert>
#include <cstdlib>
#include <cstring>

MyString::MyString(const char* rawString) {
    size = 0;
    for (int i = 0; rawString[i] != '\0'; ++i) {
        ++size;
    }
    _data = new char[size];
    for (int i = 0; i < size; ++i) {
        _data[i] = rawString[i];
    }
}

MyString::MyString(const MyString& other) {
    size = other._size;
    _data = new char[size];
    for (int i = 0; i < size; ++i) {
        _data[i] = other._data[i];
    }
}

MyString::MyString(MyString&& other) noexcept {
    std::swap(_size, other._size);
    std::swap(_data, other._data);
}

MyString& MyString::operator=(const MyString& other) {
    size = other._size;
    _data = new char[size];
    for (int i = 0; i < size; ++i) {
        _data[i] = other._data[i];
    }
    return *this;
}

MyString& MyString::operator=(MyString&& other) noexcept {
    std::swap(_size, other._size);
    std::swap(_data, other._data);
    return *this;
}

MyString::~MyString() {
    _size = 0;
    delete[] _data;
}

void MyString::append(const MyString& appendedString) {
    int i = 0;
    char* newData = new char[_size + appendedString._size];
    for (; i < _size; ++i) {
        newData[i] = _data[i];
    }
    for (; i < _size + appendedString._size; ++i) {
        newData[i] = appendedString[i - _size];
    }
    _size += appendedString._size;
    delete[] _data;
    _data = newData;
}

void MyString::insert(unsigned int pos, const MyString& insertedString) {
    //TODO
    for (unsigned int i = pos; i < pos + insertedString)
}

void MyString::clear() {
    _size = 0;
    delete[] _data;
}

void MyString::erase(unsigned int pos, unsigned int count) {

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
    return nullptr;
}

unsigned int MyString::find(const MyString& substring, unsigned int pos = 0) {
    //TODO
    return 0;
}

int MyString::compare(const MyString& comparableString) const {
    //TODO
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
    //TODO
    return false;
}

bool MyString::operator!=(const MyString& comparableString) const {
    //TODO
    return false;
}

bool MyString::operator>(const MyString& comparableString) const {
    //TODO
    return false;
}

bool MyString::operator<(const MyString& comparableString) const {
    //TODO
    return false;
}

bool MyString::operator>=(const MyString& comparableString) const {
    //TODO
    return false;
}

bool MyString::operator<=(const MyString& comparableString) const {
    //TODO
    return false;
}

