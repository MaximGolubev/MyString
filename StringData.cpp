#include "StringData.h"

#include <cstring>
#include <algorithm>

StringData::StringData() {
    _data.flag = false;
    _data.String.Short._size = 0;
}

StringData::~StringData() {
    if (_data.flag == true) {
        delete[] _data.String.Long._data;
        _data.String.Long._data = nullptr;
        _data.String.Long._size = 0;
        _data.flag = false;
    }
    else {
        _data.String.Short._size = 0;
    }
}

unsigned int StringData::size() const {
    if (_data.flag == true) {
        return _data.String.Long._size;
    }
    else {
        return _data.String.Short._size;
    }
}

void StringData::resize(const unsigned int length) {
    if (_data.flag == true) {
        delete[] _data.String.Long._data;
        _data.String.Long._data = nullptr;
        _data.String.Long._size = 0;
    }

    _data.flag = (length > sizeof(_data.String.Long) - 1);
    if (_data.flag == true) {
        _data.String.Long._size = length;
        _data.String.Long._data = new char[length];
    }
    else {
        _data.String.Short._size = length; 
    }
}

char& StringData::at(const unsigned int idx) {
    if (_data.flag == true) {
        return _data.String.Long._data[idx];
    }
    else {
        return _data.String.Short._data[idx];
    }
}

const char& StringData::at(const unsigned int idx) const {
    if (_data.flag == true) {
        return _data.String.Long._data[idx];
    }
    else {
        return _data.String.Short._data[idx];
    }
}

StringData& StringData::operator=(StringData&& other) noexcept {
    if (_data.flag == true) {
        std::swap(_data.String.Long._data, other._data.String.Long._data);
        delete[] other._data.String.Long._data;
        other._data.String.Long._data = nullptr;
        other._data.String.Long._size = 0;
    }
    else {
        memcpy(_data.String.Short._data, other._data.String.Short._data,
                sizeof(char) * other._data.String.Short._size);
        _data.String.Short._size = other._data.String.Short._size;
        other._data.String.Short._size = 0;
    }
}
