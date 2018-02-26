#include "serialize.h"
#include "signals/shsignals.h"

Serialize::Serialize(uint16_t size)
{

    if( size > 0){
        _sizeBuffer = size;
        _limit = size;
    }
    else return;

    _buffer = std::make_unique<uint8_t[]>(_sizeBuffer);
    std::memset(_buffer.get(), 0 ,_sizeBuffer);
    _offset = SIZE_HEADER_SHE;

}

Serialize::~Serialize(){

}

void Serialize::print(){

    if( _buffer.get() != NULL){

        for(uint8_t i = 0; i < _offset; i++){
            printf("[%d]:%x ", i,_buffer.get()[i]);
        }
        printf("\n");
    }
}
