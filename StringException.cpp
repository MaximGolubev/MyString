#include "MyString.h"

#include <cstdio>

MyString::StringException::StringException(unsigned int size,
                                           unsigned int idx)
{
    _size = size;
    _idx = idx;
}

MyString::InsertException::InsertException(unsigned int size,
                                           unsigned int idx) 
    : MyString::StringException(size, idx) {}

const char* MyString::InsertException::what() const noexcept {
    char* s = new char[256];
    sprintf(s, "Called insert(`%d`) on string of size `%d`", _idx, _size);
    return s;

}
        
MyString::EraseException::EraseException(unsigned int size,
                                         unsigned int idx)
    : MyString::StringException(size, idx) {} 

const char* MyString::EraseException::what() const noexcept {
    char* s = new char[256];
    sprintf(s, "Called erase(`%d`) on string of size `%d`", _idx, _size);
    return s;
}


MyString::AtException::AtException(unsigned int size, unsigned int idx) 
    : MyString::StringException(size, idx) {}

const char* MyString::AtException::what() const noexcept {
    char* s = new char[256];
    sprintf(s, "Called at(`%d`) on string of size `%d`", _idx, _size);
    return s;
}
