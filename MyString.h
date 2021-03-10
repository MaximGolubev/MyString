#pragma once

#include <cstring>

class MyString;

namespace {
    class StringData {
        struct Long {
            char* data;
            size_t size;
        };
        struct Short {
            char data[sizeof(Long) - 1];
            unsigned char size;
        };
        union Data {
            Long l;
            Short s;
        } _data;

        enum {
            shortFlag = 1,
            longFlag = 0
        } _flag;
        const static size_t _maxShortSize = sizeof(Long) - 1;

        const char* _getString() const;
        char* _getString();
    public:
        StringData();
        void save(const char* rawString, size_t size = sizeof(Long) - 1);
        size_t getSize() const;
        char& operator[](size_t i);
        const char& operator[](size_t i) const;
        void remove();
    };
}


class MyString {
public:
    /// c-tor
    MyString(const char* rawString = nullptr);

    /// the rule of five
    explicit MyString(const MyString& other);
    MyString(MyString&& other) noexcept;

    MyString& operator=(const MyString& other);
    MyString& operator=(MyString&& other) noexcept;

    ~MyString();
    ///

    /// Modifiers
    /*!
        appends string to source
        \param appendedString - string that is inserted at the end
    */
    void append(const MyString& appendedString);

    /*!
        inserts string at the passed position <br>
        \param pos - insertion index
        \param insertedString - string that is inserted at the pos
    */
    void insert(unsigned int pos, const MyString& insertedString);

    /*!
        clear string
    */
    void clear();

    /*!
        removes count characters from the string starting from pos index. <br>
        if count > size - pos then count := size - pos
        \param pos - erasing index
        \param count - count of characters to remove
    */
    void erase(unsigned int pos, unsigned int count);
    ///

    /// Accessors
    /*!
        access to character at the idx
        \param idx - character index
        \return reference to character
    */
    char& at(unsigned int idx);
    const char& at(unsigned int idx) const;

    /*!
        get string sise
        \return count of characters
    */
    unsigned int size() const;

    /*!
        check that string is empty
        \return true if string is empty else false
    */
    bool isEmpty() const;

    /*!
        get non-modified raw string
        \return c-style string
    */
    const char* rawString() const;
    ///

    /// Search
    unsigned int find(const MyString& substring, unsigned int pos = 0);
    ///

    /// Compares
    /*!
        analogue of strcmp
    */
    int compare(const MyString& comparableString) const;
    ///

    /// Overloads
    /*!
        see at-methods
    */
    char& operator[](unsigned int idx);
    const char& operator[](unsigned int idx) const;

    /*!
        see append-method
    */
    MyString& operator+(const MyString& appendedString);

    /*!
        see compares section
    */
    bool operator==(const MyString& comparableString) const;
    bool operator!=(const MyString& comparableString) const;
    bool operator>(const MyString& comparableString) const;
    bool operator<(const MyString& comparableString) const;
    bool operator>=(const MyString& comparableString) const;
    bool operator<=(const MyString& comparableString) const;
private:
    StringData _data;
};
