#include "asiointerface.h"

/** @brief Конструктор интерфейса ввода данных boost::asio
 *  @param port - порт ввода данных
*/
AsioInputInterface::AsioInputInterface(uint16_t port)
{
    ip::udp::endpoint listenEp(ip::address_v4::any(), port);
    rsock = std::make_unique<ip::udp::socket>(service);
    rsock -> open(listenEp.protocol());
    rsock -> set_option(ip::udp::socket::reuse_address(true));
    rsock -> set_option(socket_base::broadcast(true));
    rsock -> bind(listenEp);
    std::cout<<" AsioInputInterface"<<std::endl;
};

/** @brief Деструктор интерфейса ввода данных */
AsioInputInterface::~AsioInputInterface(){
    std::cout<<" ~AsioInputInterface"<<std::endl;
};

/** @brief Метод проверки инициализации интерфейса
 *  @return true - интерфейс инициализован
 *  @return false - интерфейс не инициализован
*/
bool AsioInputInterface::isInit(){
    return false;
};

/** @brief Метод приёма данных от источника
 *  @param buf - буффер приёма данных
 *  @param size - размер принимаемых данных
 *  @return r -  размер принятых данных
*/
size_t AsioInputInterface::receive(void *buf, size_t size){
    std::cout<<"receive"<<std::endl;
    size_t r = rsock -> receive_from(buffer(buf, size), senderEp);

    return r;
};

/** @brief Конструктор интерфейса вывода данных boost::asio
 *  @param port - порт ввода данных
 *  @param address - адрес - приёмник данных
*/
AsioOutputInterface::AsioOutputInterface(std::string& address, uint16_t port)
{
    if( !address.empty() ){
        ip::address_v4 add  = ip::make_address_v4(address);
        endpoint = std::make_unique<ip::udp::endpoint>(add, port);
        socket = std::make_unique<ip::udp::socket>(context);
        socket->open(ip::udp::v4());
    }
    else return;
}

/** @brief Деструктор интерфейса вывода данных */
AsioOutputInterface::~AsioOutputInterface(){
    std::cout<<" ~AsioOutputInterface"<<std::endl;
}

bool AsioOutputInterface::isInit(){
    return true;
}

size_t AsioOutputInterface::send(void *buffer, size_t size){

//    boost::array<char, 1> sd_buf  = {{ 0 }};


//    socket->send_to(boost::asio::buffer(sd_buf), endpoint);

    socket->send_to(boost::asio::buffer(buffer,size), *endpoint.get());
    return 0;
}
