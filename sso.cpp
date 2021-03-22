#include "sso.h"
#include <cassert>
#include <utility>

sso::string::string() {
    _type = StringType::Short;
    memset(&_data, '\0', _maxShortSize);
}

sso::string::string(const char* rawString, size_t size) {
    _type = StringType::Short;
    save(rawString, size);
}

sso::string& sso::string::operator=(string&& other) noexcept {
    if (this != &other) {
        remove();
        _data.l.size = std::exchange(other._data.l.size, 0);
        _data.l.data = std::exchange(other._data.l.data, nullptr);
        _type        = std::exchange(other._type, StringType::Short);
    }
    return *this;
}

void sso::string::save(const char* rawString, size_t size) {
    if (_data.l.data) {
        remove();
    }
    if (size > _maxShortSize) {
        _type = StringType::Long;
        _data.l.size = size;
        _data.l.data = new char[size];
        memcpy(_data.l.data, rawString, size);
    }
    else {
        _type = StringType::Short;
        _data.s.size = size;
        memcpy(_data.s.data, rawString, size);
    }
}

size_t sso::string::getSize() const {
    if (_type == StringType::Short) {
        return _data.s.size;
    }
    return _data.l.size;
}

char* sso::string::_getString() {
    return _type == StringType::Short ? _data.s.data : _data.l.data;
}

const char* sso::string::_getString() const {
    return _type == StringType::Short ? _data.s.data : _data.l.data;
}

void sso::string::remove() {
    if (_type == StringType::Long) {
        delete[] _data.l.data;
        _data.l.data = nullptr;
        _data.l.size = 0;
    }
    else {
        memset(_data.s.data, '\0', _maxShortSize);
        _data.s.size = 0;
    }
    _type = StringType::Short;
}

const char& sso::string::operator[](size_t i) const {
    return _getString()[i];
}

char& sso::string::operator[](size_t i) {
    return _getString()[i];
}
