#include "serialize.h"
#include "signals/shsignals.h"

Serialize::Serialize(uint16_t size)
{

    if( size > 0){
        _sizeBuffer = size;
    }
    else return;

    _buffer = std::make_unique<uint8_t[]>(_sizeBuffer);
    std::memset(_buffer.get(), 0 ,_sizeBuffer);
    _offset = SIZE_HEADER_SHE;

}

Serialize::~Serialize(){

}

template< typename T, typename ...Args>
bool Serialize::add(std::string signal, Args& ...value ){
/*
    if( signal.empty() ) return;

    if(std::is_same<T,ShSignals::SignalPairInt>::value){
    }
    else if( std::is_same<T,ShSignals::swAnalog>::value){

        ProtocolExchange::TSignal<T> ts(signal);
//        T v(value...);
        //ts.setData(v);

        size_t off = 0;
        ts.getBuffer(_buffer.get() + _offset, off);
        _offset += off;

    }
    else if( std::is_same<T,ShSignals::Analog>::value){
    }
    else if( std::is_same<T,ShSignals::Discret>::value){
    }
    else if( std::is_same<T,ShSignals::Hardware>::value){
    }
    else if( std::is_same<T,ShSignals::Software>::value){
    }
    else{
    }
    */
}
