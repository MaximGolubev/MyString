#include "MyString.h"
#include <iostream>

int main() {
    MyString a("12321312312312312312312");
    MyString b("SDASDASDASDASDASDASDASDASDAD");
    a = std::move(b);
    return 0;
}
