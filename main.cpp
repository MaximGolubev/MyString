#include <iostream>
#include <D:/Study/24.02.2021/MyString/MyString.h>
#include <string>

int main()
{
    std::cout << "Constructors" << std::endl;
    MyString first("Hello world!"), second(""),
             third(first), fourth(MyString("New world!"));
    std::cout << "first = " << first.rawString() << std::endl;
    std::cout << "second = " << second.rawString() << std::endl;
    std::cout << "third = " << third.rawString() << std::endl;
    std::cout << "fourth = " << fourth.rawString() << std::endl << std::endl;

    std::cout << "Append and =" << std::endl;
    first.append(fourth);
    second = fourth;
    third = MyString("Welcome to the club?");
    fourth.append(MyString("Hold"));
    std::cout << "first.append(fourth) = " << first.rawString() << std::endl;
    std::cout << "second = fourth = " << second.rawString() << std::endl;
    std::cout << "third = MyString(\"Welcome to the club?\") = " << third.rawString() << std::endl;
    std::cout << "fourth.append(MyString(\"Hold\")) = " << fourth.rawString() << std::endl << std::endl;

    std::cout << "Clear, at, insert, erase" << std::endl;
    first.clear();
    third.insert(third.size(), MyString(")))))"));
    fourth.erase(10, 4);
    std::cout << "first.clear() = " << first.rawString() << std::endl;
    std::cout << "second.at(2) = " << second.at(2) << std::endl;
    std::cout << "third.insert(third.size(), MyString(\")))))\")) = " << third.rawString() << std::endl;
    std::cout << "fourth.erase(10, 4) = " << fourth.rawString() << std::endl << std::endl;

    std::cout << "Size" << std::endl;
    std::cout << "first.size() = " << first.size() << std::endl;
    std::cout << "second.size() = " << second.size() << std::endl;
    std::cout << "third.size() = " << third.size() << std::endl;
    std::cout << "fourth.size() = " << fourth.size() << std::endl << std::endl;

    std::cout << "IsEmpty" << std::endl;
    std::cout << "first.isEmpty() = " << first.isEmpty() << std::endl;
    std::cout << "fourth.isEmpty() = " << fourth.isEmpty() << std::endl << std::endl;

    std::cout << "Find" << std::endl;
    std::cout << "third.find(MyString(\"club\")) = " << third.find(MyString("club")) << std::endl;
    std::cout << "third.find(MyString("")) = " << third.find(MyString("")) << std::endl;
    std::cout << "third.find(MyString(\"Welcome\", 10) = " << third.find(MyString("Welcome"), 10) << std::endl;
    std::cout << "third.find(MyString(\"club\", 10) = " << third.find(MyString("club"), 10) << std::endl << std::endl;

    std::cout << "Compare" << std::endl;
    std::cout << "first.compare(second) = " << first.compare(second) << std::endl;
    std::cout << "second.compare(fourth) = " << second.compare(fourth) << std::endl;
    std::cout << "third.compare(second) = " << third.compare(second) << std::endl;
    std::cout << "second.compare(MyString(\"Naw world!\")) = " << second.compare(MyString("Naw world!")) << std::endl;
    std::cout << "second.compare(MyString(\"Nqr world!\")) = " << second.compare(MyString("Nqr world!")) << std::endl << std::endl;

    std::cout << "second[2] = ";
    std::cout << second[2] << std::endl << std::endl;

    std::cout << "first + third = ";
    first + third;
    std::cout << first.rawString() << std::endl << std::endl;

    std::cout << "first = " << first.rawString() << std::endl;
    std::cout << "second = " << second.rawString() << std::endl;
    std::cout << "third = " << third.rawString() << std::endl;
    std::cout << "fourth = " << fourth.rawString() << std::endl << std::endl;

    std::cout << "Operation == " << std::endl;
    std::cout << "first == third = " << (first == third) << std::endl;
    std::cout << "first == second = " << (first == second) << std::endl << std::endl;

    std::cout << "Operation !=" << std::endl;
    std::cout << "first != third = " << (first != third) << std::endl;
    std::cout << "first != second = " << (first != second) << std::endl << std::endl;

    std::cout << "Operation >" << std::endl;
    std::cout << "second > MyString(\"Naw world!\") = " << (second > MyString("Naw world!")) << std::endl;
    std::cout << "second > fourth = " << (second > fourth) << std::endl;
    std::cout << "second > MyString(\"Nqr world!\") = " << (second > MyString("Nqw world!")) << std::endl << std::endl;

    std::cout << "Operation >=" << std::endl;
    std::cout << "second >= MyString(\"Naw world!\") = " << (second >= MyString("Naw world!")) << std::endl;
    std::cout << "second >= fourth = " << (second >= fourth) << std::endl;
    std::cout << "second >= MyString(\"Nqr world!\") = " << (second >= MyString("Nqw world!")) << std::endl << std::endl;

    std::cout << "Operation <" << std::endl;
    std::cout << "second < MyString(\"Naw world!\") = " << (second < MyString("Naw world!")) << std::endl;
    std::cout << "second < fourth = " << (second < fourth) << std::endl;
    std::cout << "second < MyString(\"Nqr world!\") = " << (second < MyString("Nqw world!")) << std::endl << std::endl;

    std::cout << "Operation <=" << std::endl;
    std::cout << "second <= MyString(\"Naw world!\") = " << (second <= MyString("Naw world!")) << std::endl;
    std::cout << "second <= fourth = " << (second <= fourth) << std::endl;
    std::cout << "second <= MyString(\"Nqr world!\") = " << (second <= MyString("Nqw world!")) << std::endl << std::endl;
    return 0;
}
