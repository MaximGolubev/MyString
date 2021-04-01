#include "MyString.h"

#include <iostream>

MyStringNS::StringException::StringException(unsigned int index,
                                             unsigned int size,
                                             MyStringNS::ExceptionType type) {
    _index = index;
    _size = size;
    _type = type;
}

const char* MyStringNS::StringException::what() const noexcept{
    char* s = new char[256];
    switch(_type) {
        case MyStringNS::ExceptionType::At:
            sprintf(s, "Called at(`%d`) on string of size `%d`", _index, _size);
            break;
        case MyStringNS::ExceptionType::Erase:
            sprintf(s, "Called erase(`%d`) on string of size `%d`", _index, _size);
            break;
        case MyStringNS::ExceptionType::Insert:
            sprintf(s, "Called insert(`%d`) on string of size `%d`", _index, _size);
            break;
    }
    return s;
}
