#include "MyString.h"
#include <iostream>

int main() {
    MyString a("123");
    MyString b(std::move(a));
    std::cout << b.rawString();
    return 0;
}
