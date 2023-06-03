#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <iostream>

class Buffer
{
    private:
    std::string _buffer;
    size_t      _pos;

    public:
    Buffer();
    Buffer(std::string str);
    Buffer(const Buffer& buffer);
    ~Buffer();
    Buffer& operator=(const Buffer& buffer);

    void appendBuffer(std::string str);
    void cutBuffer(size_t pos);
    void clearBuffer(void);

    const char* getBuffer(void) const;
};

#endif