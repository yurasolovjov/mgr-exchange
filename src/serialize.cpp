#include "serialize.h"
#include "signals/shsignals.h"

Serialize::Serialize(uint16_t size)
{

    if( size > 0){
        _sizeBuffer = size;
    }
    else return;

    _buffer = std::make_unique<uint8_t[]>(_sizeBuffer);

    _offset = 0;
}

Serialize::~Serialize(){

}

template< typename T, typename ...Args>
void Serialize::add(std::string& signal, Args& ...value ){

    if(std::is_same<T,ShSignals::SignalPairInt>::value){
    }
    else if( std::is_same<T,ShSignals::swAnalog>::value){

        ProtocolExchange::TSignal<T> ts(signal);

        if(!signal.empty()){
            ts.signalName = signal.c_str();
        }

        ts.sizeElement = sizeof(ShSignals::swAnalog);
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


}
