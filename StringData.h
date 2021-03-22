#pragma once

struct Long {
    unsigned int size;
    char* data;
};

struct Short {
    unsigned char size;
    char data[sizeof(Long) - 1];
};

union StringRepresentation{
    Long lStr;
    Short sStr;
};

class StringData {
public:
    StringData();

    StringData& edit(const char* rawString, unsigned int size);

    const char* get() const;
    unsigned int size() const;
    unsigned int capacity() const;

    void clear();

    char& operator[](unsigned int idx);
    const char& operator[](unsigned int idx) const;

    ~StringData();
private:
    bool _isShort;
    StringRepresentation _info;
};

