#include "interface.h"
#include <asiointerface.h>

/** @brief*/
InputInterface::InputInterface()
{

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


/** @brief*/
OutputInterface::OutputInterface(){

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
