#pragma once

#include "StringData.h"

class MyString {
public:
    MyString(const char* rawString = nullptr);
    explicit MyString(const MyString& other);
    MyString(MyString&& other) noexcept;
    MyString& operator=(const MyString& other);
    MyString& operator=(MyString&& other) noexcept;

    void insert(unsigned int pos, const MyString& insertedString);
    void append(const MyString& appendedString);
    void clear();
    void erase(unsigned int pos, unsigned int count);
    unsigned int size() const;

    char& at(unsigned int idx);
    const char& at(unsigned int idx) const;

    bool isEmpty() const;

    const char* rawString() const;

    unsigned int find(const MyString& substring, unsigned int pos = 0);

    int compare(const MyString& comparableString) const;

    char& operator[](unsigned int idx);
    const char& operator[](unsigned int idx) const;
    MyString& operator+(const MyString& appendedString);
    bool operator==(const MyString& comparableString) const;
    bool operator!=(const MyString& comparableString) const;
    bool operator>(const MyString& comparableString) const;
    bool operator<(const MyString& comparableString) const;
    bool operator>=(const MyString& comparableString) const;
    bool operator<=(const MyString& comparableString) const;

    ~MyString() = default;
private:
    StringData _value;
};

