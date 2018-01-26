#include "asiointerface.h"

AsioInterface::AsioInterface(uint16_t port)
{
    ip::udp::endpoint listenEp(ip::address_v4::any(), port);
    rsock = std::make_unique<ip::udp::socket>(service);
    rsock -> open(listenEp.protocol());
    rsock -> set_option(ip::udp::socket::reuse_address(true));
    rsock -> set_option(socket_base::broadcast(true));
    rsock -> bind(listenEp);
    std::cout<<" AsioInterface"<<std::endl;
};

AsioInterface::~AsioInterface(){
    std::cout<<" ~AsioInterface"<<std::endl;
};

bool AsioInterface::isInit(){
    return false;
};

size_t AsioInterface::receive(void *buf, size_t size){
    std::cout<<"receive"<<std::endl;
    size_t r = rsock -> receive_from(buffer(buf, size), senderEp);

    return r;
};
