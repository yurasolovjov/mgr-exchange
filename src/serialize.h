#ifndef SERIALIZE_H
#define SERIALIZE_H

#include <memory>
#include "protocol.h"


class Serialize
{
public:

    Serialize(uint16_t size = 255);
    ~Serialize();


    std::unique_ptr<uint8_t[]> get(){ return std::move(_buffer); }

    void print();

    template< typename T>
    friend Serialize& operator <<(Serialize& serial, T& element){

        if(std::is_same<T,ShSignals::SignalPairInt>::value){
        }
        else if( std::is_same<T,ShSignals::swAnalog>::value){
        }
        else if( std::is_same<T,ShSignals::Analog>::value){

            if(serial._buffer.get() != NULL){

                std::memcpy(serial._buffer.get() + serial._offset, &element, sizeof(T::first) + sizeof(T::second));
                serial._offset += sizeof(T::first) + sizeof(T::second);

            }

        }
        else if( std::is_same<T,ShSignals::Discret>::value){
        }
        else if( std::is_same<T,ShSignals::Hardware>::value){
        }
        else if( std::is_same<T,ShSignals::Software>::value){
        }
        else{
        }

        return serial;
    }

private:
    std::unique_ptr<uint8_t[]> _buffer;
    uint32_t _sizeBuffer;
    uint32_t _offset;
    uint32_t _limit;
};

#endif // SERIALIZE_H
