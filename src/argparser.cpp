#include <iostream>
#include <cstring>
#include <string>

#include "argparser.h"


ArgParser::ArgParser(int argc, char** argv){

    std::cout<<"Parameters: "<<std::endl;
    po::options_description desc("The manager exchange \n short description: ");

    desc.add_options()
           ("help,h","help \n")
           ("mode,m",po::value<std::string>()->default_value(MODE_DEFINE),"Mode of work")
           ("size,s",po::value<uint32_t>()->default_value(SIZE_SHARED_MEMORY),"Size of shared memory")
           ("frequency,f",po::value<int>()->default_value(FREQUENCY),"Frequency of the program")
           ("interface,s",po::value<std::string>()->default_value("udp"),"Interface of net")
           ("inIPAddress,I",po::value<std::string>()->default_value("127.0.0.1"),"Input address of the manager exchange")
           ("outIPAddress,O",po::value<std::string>()->default_value("127.0.0.1"),"Output address of the manager exchange")
           ("inPort,i",po::value<uint16_t>()->default_value(IN_PORT),"Input port for in address  ")
           ("outPort,o",po::value<uint16_t>()->default_value(OUT_PORT),"Output port for out address")
           ("verbose,v","Verbose option")
    ;

    po::variables_map vm;

    try{
          po::store(po::parse_command_line(argc, argv, desc), vm);
          po::notify(vm);
          _isInit = true;
    }
    catch(po::error& e){
         _isInit = false;
         std::cerr<<"*** ERROR *** "<<e.what()<<std::endl;
    }

    if (vm.count("help")){
          std::cout<<desc<<std::endl;
          _isInit = false;
    }

    if(vm.count("mode")){
        this->_modeString = vm["mode"].as<std::string>();

        if( _modeString == "local"){
            this->_mode = MODE_LOCAL;
        }
        else if(_modeString == "net_1"){
            this->_mode = MODE_NET_1;
        }
        else if(_modeString == "net_2"){
            this->_mode = MODE_NET_2;
        }
        else if(_modeString == "net_3"){
            this->_mode = MODE_NET_3;
        }
    }

    if(vm.count("size")){
        this->_sizeShmem = vm["size"].as<uint32_t>();
    }

    if(vm.count("frequency")){
        this->_frequency = vm["frequency"].as<int>();
    }


    if( vm.count("interface") ){

        this->_interface = vm["interface"].as<std::string>();
    }

    if( vm.count("inIPAddress") ){

        this->_inputIPAddress = vm["inIPAddress"].as<std::string>();
    }

    if( vm.count("outIPAddress") ){

        this->_outputIPAddress = vm["outIPAddress"].as<std::string>();
    }

    if( vm.count("inPort") ){
        this->_inPort = vm["inPort"].as<uint16_t>();
    }
    if( vm.count("outPort") ){
        this->_outPort = vm["outPort"].as<uint16_t>();
    }

    if(vm.count("verbose")){
        this->_verbose = true;
    }
    else this->_verbose = false;
}

ArgParser::~ArgParser(){

}




