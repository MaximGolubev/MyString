#include "StringData.h"
#include <cstring>
#include <stdexcept>

StringData::StringData() {
    this->_isShort = true;
    this->_info.sStr.size = 0;
}

StringData& StringData::edit(const char* rawString, unsigned int size) {
    if (!this->_isShort) {
        delete[] this->_info.lStr.data;
        this->_info.lStr.data = nullptr;
    }
    if (rawString == nullptr) {
        this->_isShort = true;
        this->_info.sStr.size = 0;
    }
    else {
        if (size <= (sizeof(this->_info) - 1)) {
            this->_isShort = true;
            this->_info.sStr.size = size;
            memcpy(this->_info.sStr.data, rawString, size);
        }
        else {
            this->_isShort = false;
            this->_info.lStr.size = size;
            this->_info.lStr.data = new char[size];
            memcpy(this->_info.lStr.data, rawString, size);
        }
    }
    return *this;
}

const char* StringData::get() const {
    return (this->_isShort) ? this->_info.sStr.data : this->_info.lStr.data;
}

unsigned int StringData::size() const {
    return (this->_isShort) ? this->_info.sStr.size : this->_info.lStr.size;
}

unsigned int StringData::capacity() const {
    return (sizeof(this->_info) - 1);
}

void StringData::clear() {
    this->_isShort = true;
    this->_info.sStr.size = 0;
}

char& StringData::operator[](unsigned int idx) {
    if (idx >= this->size()) {
        throw std::range_error("Array index out of bounds");
    }
    return this->_isShort ? this->_info.sStr.data[idx] : this->_info.lStr.data[idx];
}

const char& StringData::operator[](unsigned int idx) const {
    if (idx >= this->size()) {
        throw std::range_error("Array index out of bounds");
    }
    return this->_isShort ? this->_info.sStr.data[idx] : this->_info.lStr.data[idx];
}

StringData::~StringData() {
    if (!this->_isShort) {
        delete[] this->_info.lStr.data;
    }
}
