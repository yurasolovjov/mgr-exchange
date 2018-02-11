#ifndef SERIALIZE_H
#define SERIALIZE_H

#include <memory>
#include "protocol.h"


class Serialize
{
public:

    Serialize(uint16_t size = 255);
    ~Serialize();

    template< typename T, typename ...Args>
    void add(std::string& signal, Args& ...value );
    std::unique_ptr<uint8_t[]> get(){ return std::move(_buffer); }

private:
    std::unique_ptr<uint8_t[]> _buffer;
    uint16_t _sizeBuffer;
    uint16_t _offset;
};

#endif // SERIALIZE_H
