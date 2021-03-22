#include "MyString.h"
#include <iostream>

int main() {
    MyString a("1231231241242341234123");
    MyString b("ASD");
    a.insert(0,b);
    std::cout << a.rawString();
    return 0;
}
