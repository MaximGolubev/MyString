#include "MyString.h"
#include <iostream>

int main() {
    MyString a("1234567890123456");
    a.erase(0,2);
    std::cout << a.rawString();
    return 0;
}
