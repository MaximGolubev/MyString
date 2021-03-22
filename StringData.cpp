#include "StringData.h"
#include <cstring>
#include <stdexcept>
#include <utility>

StringData::StringData() {
    this->_isShort = true;
    this->_info.sStr.size = 0;
}

StringData::StringData(const StringData& other) {
    this->_isShort = other._isShort;
    if (this->_isShort) {
        this->_info.sStr.size = other._info.sStr.size;
        memcpy(this->_info.sStr.data, other._info.sStr.data, this->_info.sStr.size);
    }
    else {
        this->_info.lStr.size = other._info.lStr.size;
        if (this->_info.lStr.size == 0) {
            this->_info.lStr.data = nullptr;
        }
        else {
            this->_info.lStr.data = new char[this->_info.lStr.size];
            memcpy(this->_info.lStr.data, other._info.lStr.data, this->_info.lStr.size);
        }
    }
}

StringData::StringData(StringData&& other) noexcept {
    this->_isShort = std::exchange(other._isShort, true);
    if (this->_isShort) {
        this->_info.sStr.size = std::exchange(other._info.sStr.size, 0);
        std::swap(this->_info.sStr.data, other._info.sStr.data);
    }
    else {
        this->_info.lStr.size = std::exchange(other._info.lStr.size, 0);
        this->_info.lStr.data = std::exchange(other._info.lStr.data, nullptr);
    }
}

StringData& StringData::operator=(const StringData& other) {
    StringData copy(other);
    std::swap(this->_isShort, copy._isShort);
    if (this->_isShort) {
        std::swap(this->_info.sStr.size, copy._info.sStr.size);
        std::swap(this->_info.sStr.data, copy._info.sStr.data);
    }
    else {
        std::swap(this->_info.lStr.size, copy._info.lStr.size);
        std::swap(this->_info.lStr.data, copy._info.lStr.data);
    }
    return *this;
}

StringData& StringData::operator=(StringData&& other) noexcept {
    if (this != &other) {
        if (!this->_isShort) {
            delete[] this->_info.lStr.data;
            this->_info.lStr.data = nullptr;
        }
        this->_isShort = std::exchange(other._isShort, true);
        if (this->_isShort) {
            this->_info.sStr.size = std::exchange(other._info.sStr.size, 0);
            std::swap(this->_info.sStr.data, other._info.sStr.data);
        }
        else {
            this->_info.lStr.size = std::exchange(other._info.lStr.size, 0);
            this->_info.lStr.data = std::exchange(other._info.lStr.data, nullptr);
        }
    }
    return *this;
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
