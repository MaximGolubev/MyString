#include <cstdlib>

class StringData {
private:
    struct StringRepresentation {
        union {
            struct {
                char* _data;
                size_t _size;
            } Long;
            struct {
                char _data[sizeof(Long) - 1];
                unsigned char _size;
            } Short;
        } String;
        bool flag;
    };
    StringRepresentation _data;
public:
    StringData();
    ~StringData();

    unsigned int size() const;
    void resize(const unsigned int length);
    char& at(const unsigned int idx);
    const char& at(const unsigned int idx) const;
};
