#include "interface.h"
#include <asiointerface.h>
Interface::Interface()
{

}

std::unique_ptr<Interface> Interface::CreateInterface(uint8_t type, uint16_t port){

    std::unique_ptr<Interface> abstruct ;

    switch(type){
        case 0 :
             abstruct = std::make_unique<AsioInterface>(port);
        break;

        case 1 :
        break;

        default:
        break;
    }

    return std::move(abstruct);
}
