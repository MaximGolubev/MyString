#include "MyString.h"

#include <cassert>
#include <cstring>
#include <utility>

// >> StringData implementation
StringData::StringData() {
    memset(&data, '\0', maxShortSize);
}

void StringData::save(const char* rawString, size_t size) {
    if (size > maxShortSize) {
        flag = _longFlag;
        data._long.size = size;
        data._long.data = new char[size];
        memcpy(data._long.data, rawString, size);
    }
    else {
        flag = _shortFlag;
        data._short.size = size;
        memcpy(data._short.data, rawString, size);
    }
}


size_t StringData::getSize() const {
    if (flag == _shortFlag) {
        return data._short.size;
    }
    return data._long.size;
}

const char* StringData::getString() const {
    return flag == _shortFlag ? data._short.data : data._long.data;
}

char* StringData::getString() {
    return flag == _shortFlag ? data._short.data : data._long.data;
}

void StringData::remove() {
    if (flag == _longFlag) {
        delete[] data._long.data;
        data._long.data = nullptr;
        data._long.size = 0;
    }
    else {
        memset(data._short.data, '\0', maxShortSize);
        data._short.size = 0;
    }
}
// << StringData implementation


MyString::MyString(const char* rawString) {
    if (rawString) {
        _data.save(rawString, strlen(rawString));
    }
}

MyString::MyString(const MyString& other) {
    _data.save(other._data.getString(),
               other._data.getSize());
}

MyString::MyString(MyString&& other) noexcept {
    _data = other._data;
    other._data.save("");
    other._data.remove();
}

MyString& MyString::operator=(const MyString& other) {
    if (this != &other) {
        MyString copy(other);
        std::swap(_data, copy._data);
    }
    return *this;
}

MyString& MyString::operator=(MyString&& other) noexcept {
    if (this != &other) {
        _data.remove();
        _data = other._data;
        other._data.save("");
        other._data.remove();
    }
    return *this;
}

char& MyString::at(const unsigned int idx) {
    assert(idx < size());
    return (_data.getString()[idx]);
}

const char& MyString::at(const unsigned int idx) const {
    assert(idx < size());
    return _data.getString()[idx];
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

void MyString::append(const MyString& appendedString) {
    this->insert(size(), appendedString);
}

MyString::~MyString() {
    _data.remove();
}

void MyString::insert(unsigned int pos, const MyString& insertedString) {
    StringData str;
    str.save(_data.getString(), size() + insertedString.size());
    memcpy(str.getString() + pos, insertedString._data.getString(), insertedString.size());
    memcpy(str.getString() + pos + insertedString.size(), _data.getString() + pos, size() - pos);
    std::swap(str, _data);
}

void MyString::clear() {
    _data.remove();
}

void MyString::erase(unsigned int pos, unsigned int count) {
    unsigned int newSize = size() > count ? size() - count : pos - 1;
    for (size_t i = pos; i < newSize; ++i) {
        (*this)[i] = (*this)[i + count];
    }
    StringData str;
    str.save(_data.getString(), newSize);
    std::swap(str, _data);
}

unsigned int MyString::size() const {
    return _data.getSize();
}

bool MyString::isEmpty() const {
    return !size();
}

// TODO: Перегрузить оператор <<
//  Тут никак не избавиться от выделения памяти?
//  Кроме как подменивать data у this на новый StringData объект.
const char* MyString::rawString() const {
    char* str = new char[size() + 1];
    memcpy(str, _data.getString(), size());
    str[size()] = '\0';
    return str;
}

unsigned int MyString::find(const MyString& substring, unsigned int pos) {
    if (this->isEmpty() || substring.isEmpty()) {
        return -1;
    }
    unsigned int res = -1;
    size_t count = 0;
    const size_t substrSize = substring.size();
    const size_t strSize = this->size();
    for (int i = strSize - (substrSize - 1) - 1; i >= (int)pos; --i) {
        for (int j = i; j < strSize; ++j) {
            if ((*this)[j] == substring[count]) {
                count++;
            }
            else {
                break;
            }
        }
        if (count == substrSize) {
            res = i;
            break;
        }
        count = 0;
    }
    return res;

}

int MyString::compare(const MyString& comparableString) const {
    size_t minSize =  size() > comparableString.size()
                      ? comparableString.size()
                      : size();

    for (size_t i = 0; i < minSize; ++i) {
        if ((*this)[i] < comparableString[i]) {
            return -1;
        }
        else if ((*this)[i] > comparableString[i]) {
            return 1;
        }
    }
    return size() - comparableString.size();

}

bool MyString::operator!=(const MyString& comparableString) const {
    return !(*this == comparableString);
}

bool MyString::operator==(const MyString& comparableString) const {
    return this->compare(comparableString) == 0;
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
