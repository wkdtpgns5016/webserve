#include "Buffer.hpp"

Buffer::Buffer()
{

}

Buffer::Buffer(const std::string& str) : _pos(0)
{
    _buffer = str;
}

Buffer::Buffer(const Buffer& buffer)
{
    _buffer = buffer._buffer;
    _pos = buffer._pos;
}

Buffer::~Buffer()
{

}

Buffer& Buffer::operator=(const Buffer& buffer)
{
    _buffer = buffer._buffer;
    _pos = buffer._pos;
    return (*this);
}

void Buffer::appendBuffer(const std::string& str)
{
    _buffer += str;
}

void Buffer::cutBuffer(size_t pos)
{
    _pos += pos;
}

void Buffer::clearBuffer(void)
{
    _buffer.clear();
    _pos = 0;
}

const char* Buffer::getBuffer(void) const
{
    return (_buffer.c_str() + _pos);
}