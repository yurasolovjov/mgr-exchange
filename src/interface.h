#ifndef INTERFACE_H
#define INTERFACE_H
#include <iostream>
#include <cstring>
#include <memory>

#define ASIO_PORT_DEF 45454

class Interface
{
public:
    Interface();
    virtual ~Interface(){ std::cout<<"virtual ~interface() "<<std::endl; }

    virtual size_t receive(void* buffer, size_t size) = 0;
    virtual bool isInit() = 0;
    static std::unique_ptr<Interface> CreateInterface(uint8_t type = 0, uint16_t port = ASIO_PORT_DEF);

};

#endif // INTERFACE_H
