#include "sso.h"
#include <cassert>

sso::string::string() {
    memset(&_data, '\0', _maxShortSize);
}

sso::string::string(const char* rawString, size_t size) {
    save(rawString, size);
}

void sso::string::save(const char* rawString, size_t size) {
    if (_data.l.data) {
        remove();
    }
    if (size > _maxShortSize) {
        _flag = longFlag;
        _data.l.size = size;
        _data.l.data = new char[size];
        memcpy(_data.l.data, rawString, size);
    }
    else {
        _flag = shortFlag;
        _data.s.size = size;
        memcpy(_data.s.data, rawString, size);
    }
}

size_t sso::string::getSize() const {
    if (_flag == shortFlag) {
        return _data.s.size;
    }
    return _data.l.size;
}

char* sso::string::_getString() {
    return _flag == shortFlag ? _data.s.data : _data.l.data;
}

const char* sso::string::_getString() const {
    return _flag == shortFlag ? _data.s.data : _data.l.data;
}

void sso::string::remove() {
    if (_flag == longFlag) {
        delete[] _data.l.data;
        _data.l.data = nullptr;
        _data.l.size = 0;
    }
    else {
        memset(_data.s.data, '\0', _maxShortSize);
        _data.s.size = 0;
    }
}

const char& sso::string::operator[](size_t i) const {
    assert(i < getSize());
    return _getString()[i];
}

char& sso::string::operator[](size_t i) {
    assert(i < getSize());
    return _getString()[i];
}

void sso::string::unleash() {
    if (_flag == longFlag) {
        _data.l.data = nullptr;
    }
}
