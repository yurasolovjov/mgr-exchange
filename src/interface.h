#ifndef INTERFACE_H
#define INTERFACE_H
#include <iostream>
#include <cstring>
#include <memory>

#define ASIO_PORT_DEF 45454

/** @brief Абстрактный класс интерфейса ввода данных */
class InputInterface
{
public:
    InputInterface();
    virtual ~InputInterface(){ std::cout<<"virtual ~interface() "<<std::endl; }

    virtual size_t receive(void* buffer, size_t size) = 0;
    virtual bool isInit() = 0;
    static std::unique_ptr<InputInterface> CreateInterface(uint8_t type = 0, uint16_t port = ASIO_PORT_DEF);

};

/** @brief Абстрактный класс интерфейса вывода данных*/
class OutputInterface
{
public:
    OutputInterface();
    virtual ~OutputInterface(){ std::cout<<"virtual ~interface() "<<std::endl; }

    virtual size_t send(void* buffer, size_t size) = 0;
    virtual bool isInit() = 0;
    static std::unique_ptr<OutputInterface> CreateInterface(uint8_t type = 0,std::string address = "", uint16_t port = ASIO_PORT_DEF);

};

#endif // INTERFACE_H
