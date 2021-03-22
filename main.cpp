#include "MyString.h"
#include <iostream>

int main() {
    MyString a("123456781231231231");
    MyString b("21312312dsadasdasdasdas");
    a.insert(3,b);
    std::cout << a.rawString();
    return 0;
}
