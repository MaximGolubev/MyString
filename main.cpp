#include "MyString.h"
#include <iostream>

int main() {
    MyString a("123123");
    MyString b("123");
    std::cout << b[3];
    return 0;
}
