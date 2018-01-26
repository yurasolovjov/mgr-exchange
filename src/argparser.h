#ifndef ARG_PASRSER_H
#define ARG_PASRSER_H

#include <boost/program_options.hpp>


namespace po = boost::program_options;

#define SIZE_SHARED_MEMORY 65535
#define FREQUENCY  0
#define IN_PORT  45451
#define OUT_PORT 45452
#define MODE_LOCAL 0
#define MODE_NET_1 1
#define MODE_NET_2 2
#define MODE_NET_3 3


class ArgParser{

    public:

    /** Конструктор */
    ArgParser(int argc, char** argv);

    /* Деструктор */
    ~ArgParser();
  

    public:

    bool isInit(){return _isInit;}
    bool isVerbose(){return _verbose;}
    uint8_t isMode(){return _mode;}
    uint8_t  getMode(){ return _mode;}
    uint16_t getInPort(){ return _inPort; }
    uint16_t getOutPort(){ return _outPort;}
    uint16_t getFrequency(){ return _frequency;}
    uint32_t getSizeShmem(){ return _sizeShmem;}
    std::string modeName(){return _modeString;}
    std::string inputAddress(){return _inputIPAddress;}
    std::string outputAddress(){return _outputIPAddress;}
    std::string getInterface(){ return _interface;}


    private:
        bool        _isInit;
        bool        _verbose;
        uint8_t     _mode;
        uint16_t    _frequency;
        uint16_t    _inPort;
        uint16_t    _outPort;
        uint32_t    _sizeShmem;
        std::string _modeString;
        std::string _inputIPAddress;
        std::string _outputIPAddress;
        std::string _interface;
};
		
#endif // ARG_PASRSER_H
