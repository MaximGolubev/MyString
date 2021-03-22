#include "MyString.h"
#include <cstring>
#include <utility>

MyString::MyString(const char* rawString) {
    unsigned int size;
    if (rawString == nullptr) {
        size = 0;
    }
    else {
        size = strlen(rawString);
    }
    this->_value.edit(rawString, size);
}

MyString::MyString(const MyString& other) {
    this->_value.edit(other._value.get(), other.size());
}

MyString::MyString(MyString&& other) noexcept {
    this->_value = std::move(other._value);
}

MyString& MyString::operator=(const MyString& other) {
    MyString copy(other);
    std::swap(this->_value, copy._value);
    return *this;
}

MyString& MyString::operator=(MyString&& other) noexcept {
    if (this != &other) {
        this->_value = std::move(other._value);
    }
    return *this;
}

void MyString::insert(unsigned int pos, const MyString& insertedString) {
    unsigned int size = this->size();
    if (pos > size) {
        pos = size;
    }
    size += insertedString.size();
    char* result = new char[size];
    memcpy(result, this->_value.get(), pos);
    unsigned temp = pos + insertedString.size();
    for (unsigned int i = pos; i < temp; i++) {
        result[i] = insertedString[i - pos];
    }
    for (unsigned int i = temp; i < size; i++) {
        result[i] = (*this)[i - insertedString.size()];
    }
    this->_value.edit(result, size);
    delete[] result;
}

void MyString::append(const MyString& appendedString) {
    this->insert(this->size(), appendedString);
}

void MyString::clear() {
    this->_value.edit(nullptr, 0);
}

void MyString::erase(unsigned int pos, unsigned int count) {
    if (pos < this->size()) {
        if (count > (this->size() - pos)) {
            count = this->size() - pos;
        }
        if ((pos == 0) && (count == this->size())) {
            this->clear();
        }
        else {
            unsigned int size = this->size() - count;
            char* result = new char[size];
            memcpy(result, this->_value.get(), pos);
            for (unsigned int i = pos + count; i < this->size(); i++) {
                result[i - count] = (*this)[i];
            }
            this->_value.edit(result, size);
            delete[] result;
        }
    }
}

unsigned int MyString::size() const {
    return this->_value.size();
}

char& MyString::at(const unsigned int idx) {
    return this->_value[idx];
}

const char& MyString::at(const unsigned int idx) const {
    return this->_value[idx];
}

bool MyString::isEmpty() const {
    return (this->size() == 0);
}

const char* MyString::rawString() const {
    char* result;
    if (this->isEmpty()) {
        result = nullptr;
    }
    else {
        result = new char[this->size() + 1];
        memcpy(result, this->_value.get(), this->size());
        result[this->size()] = '\0';
    }
    return result;
}

unsigned int MyString::find(const MyString& substring, unsigned int pos) {
    unsigned int result = 0;
    if (pos < this->size()) {
        if ((pos + substring.size()) <= this->size()) {
            for (unsigned int i = pos; i < (pos + substring.size()); i++) {
                if ((*this)[i] != substring[i - pos]) {
                    result = 0;
                    return result;
                }
            }
            result = 1;
        }
    }
    return result;
}

int MyString::compare(const MyString& comparableString) const {
    int result = 0;
    unsigned int minSize;
    if (this->size() < comparableString.size()) {
        minSize = this->size();
    }
    else {
        minSize = comparableString.size();
    }
    for (unsigned int i = 0; i < minSize; i++) {
        result = (*this)[i] - comparableString[i];
        if (result != 0) {
            return result;
        }
    }
    if ((minSize == this->size()) && (minSize != comparableString.size())) {
        result = -comparableString[minSize];
    }
    if ((minSize != this->size()) && (minSize == comparableString.size())) {
        result = (*this)[minSize];
    }
    return result;
}

char& MyString::operator[](const unsigned int idx) {
    return at(idx);
}

const char& MyString::operator[](unsigned int idx) const {
    return at(idx);
}

MyString& MyString::operator+(const MyString& appendedString) {
    this->append(appendedString);
    return* this;
}

bool MyString::operator==(const MyString& comparableString) const {
    return this->compare(comparableString) == 0;
}

bool MyString::operator!=(const MyString& comparableString) const {
    return this->compare(comparableString) != 0;
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