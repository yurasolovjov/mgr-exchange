#ifndef ASIOINTERFACE_H
#define ASIOINTERFACE_H
#include "interface.h"
#include <boost/asio.hpp>
#include <memory>

using namespace boost::asio;

/** @brief Класс интерфейса ввода данных на основе boost::asio*/
class AsioInputInterface: public InputInterface
{
public:
    AsioInputInterface(uint16_t port = ASIO_PORT_DEF);
    ~AsioInputInterface();

    bool isInit();
    size_t receive(void *buffer, size_t size);

private:
    io_service service;
    std::unique_ptr<ip::udp::socket> rsock;
    ip::udp::endpoint senderEp;
};

/** @brief Класс интерфейса вывода данных на основе boost::asio*/
class AsioOutputInterface: public OutputInterface
{
public:
    AsioOutputInterface(std::string& address, uint16_t port = ASIO_PORT_DEF);
    ~AsioOutputInterface();

    bool isInit();
    size_t send(void *buffer, size_t size);

private:
    io_context context;
    std::unique_ptr<ip::udp::socket> socket;
    std::unique_ptr<ip::udp::endpoint> endpoint;
};
#endif // ASIOINTERFACE_H
