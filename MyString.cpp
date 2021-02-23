#include "MyString.h"

#include <cassert>
#include <cstdlib>
#include <cstring>

MyString::MyString(const char* rawString) {
    // TODO
}

MyString::MyString(const MyString& other) {
    // TODO
}

MyString::MyString(MyString&& other) {

}

MyString& MyString::operator=(const MyString& other) {
    // TODO
    return *this;
}

MyString& MyString::operator=(MyString&& other) {
    // TODO
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

char& MyString::operator[](const unsigned int idx) const {
    return at(idx);
}

MyString& MyString::operator+(const MyString& appendedString) {
    this->append(appendedString);
    return *this;
}