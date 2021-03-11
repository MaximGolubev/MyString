#pragma once

#include <cstring>

namespace sso {
    class string {
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

        enum class StringType{
            Short = 1,
            Long = 0
        } _type;
        const static size_t _maxShortSize = sizeof(Long) - 1;

        const char* _getString() const;
        char* _getString();
    public:
        string();
        string(const char* rawString, size_t size);
        void save(const char* rawString, size_t size = sizeof(Long) - 1);
        size_t getSize() const;
        char& operator[](size_t i);
        const char& operator[](size_t i) const;
        void remove();

        // Закидывает nullptr в указатель длинной строки
        void unleash();
    };
}

