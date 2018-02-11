#include "interface.h"
#include <asiointerface.h>
#include <protocol.h>


/** @brief*/
InputInterface::InputInterface()
{

    sizeBuffer = 1025;
    _buffer = std::make_unique<uint8_t[]>(sizeBuffer);

}

/** @brief*/
std::unique_ptr<InputInterface> InputInterface::CreateInterface(uint8_t type, uint16_t port){

    std::unique_ptr<InputInterface> abstruct ;

    switch(type){
        case 0 :
             abstruct = std::make_unique<AsioInputInterface>(port);
        break;

        case 1 :
        break;

        default:
        break;
    }

    return std::move(abstruct);
}

bool InputInterface::exec(){

    std::thread t1( &InputInterface::receive_loop, this);
    t1.detach();

    return true;

}

void InputInterface::receive_loop(){

    while(true){
        int r = this->receive(_buffer.get(), sizeBuffer);


        /*
        for( int i = 0; i <= r; i++){
            printf(" %x ", _buffer.get()[i]);
        }
        */
//        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

}

/** @brief*/
OutputInterface::OutputInterface(){

    sizeBuffer = 1025;
    _buffer = std::make_unique<uint8_t[]>(sizeBuffer);
}

/** @brief*/
std::unique_ptr<OutputInterface> OutputInterface::CreateInterface(uint8_t type, std::string address, uint16_t port ){

    std::unique_ptr<OutputInterface> abstruct ;

    switch(type){
        case 0 :
             abstruct = std::make_unique<AsioOutputInterface>(address,port);

        break;

        case 1 :
        break;

        default:
        break;
    }

    return std::move(abstruct);
}

bool OutputInterface::exec(){

    std::thread t1( &OutputInterface::send_loop, this);
    t1.detach();

    return true;

}

void OutputInterface::send_loop(){


    while(true){
        int r = this->send(_buffer.get(), sizeBuffer);

//        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

}
