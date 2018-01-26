#ifndef ASIOINTERFACE_H
#define ASIOINTERFACE_H
#include "interface.h"
#include <boost/asio.hpp>
#include <memory>

using namespace boost::asio;

class AsioInterface: public Interface
{
public:
    AsioInterface(uint16_t port = ASIO_PORT_DEF);
    ~AsioInterface();

    bool isInit();
    size_t receive(void *buffer, size_t size);
private:
    io_service service;
    std::unique_ptr<ip::udp::socket> rsock;
    ip::udp::endpoint senderEp;
};

#endif // ASIOINTERFACE_H
