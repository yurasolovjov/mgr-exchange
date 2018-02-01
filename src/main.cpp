#include <iostream>
#include <cstring>
#include <argparser.h>
#include <signal.h>
#include "argparser.h"
#include <memory>
#include "interface.h"
#include "asiointerface.h"
#include "sharedmemory.h"

static bool isRun = true;

void signalHandler(int signo) {

    std::cout << "Signal Handler get signal: ";

    switch( signo ) {
        case SIGABRT:
            std::cerr << "SIGABRT" << std::endl;
        break;

        case SIGTERM:
            std::cerr << "SIGTERM" << std::endl;
        break;

        case SIGINT:
            std::cerr << "SIGINT" << std::endl;
        break;
    };

    isRun = false;
}

int main(int argc, char** argv)
{

    signal(SIGABRT, signalHandler);
    signal(SIGTERM, signalHandler);
    signal(SIGINT,  signalHandler);


    ArgParser args(argc,argv);

    if(!args.isInit()){
        std::cout<<"*** ERROR *** Parameters not found "<<std::endl;
    }

    bool verbose = args.isVerbose();
    uint8_t     mode = args.getMode();
    uint16_t    frequency = args.getFrequency();
    uint16_t    inPort 	  = args.getInPort();
    uint16_t    outPort   = args.getOutPort();
    uint32_t    sizeShmem = args.getSizeShmem();
    std::string modeString = args.modeName();
    std::string inputIPAddress = args.inputAddress();
    std::string outputIPAddress = args.outputAddress();
    std::string interface = args.getInterface();


    if( verbose ){

        std::cout<<" ============================================================================== "<<std::endl;
        std::cout<<" *** DEBUG *** Option --verbose       = "<<(verbose ? "true" : "false" )<<std::endl;
        std::cout<<" *** DEBUG *** Option --mode	      = "<<modeString<<std::endl;
        std::cout<<" *** DEBUG *** Option --frequency     = "<<frequency<<std::endl;
        std::cout<<" *** DEBUG *** Option --inPort        = "<<inPort<<std::endl;
        std::cout<<" *** DEBUG *** Option --outPort       = "<<outPort<<std::endl;
        std::cout<<" *** DEBUG *** Option --sizeShmem     = "<<sizeShmem<<std::endl;
        std::cout<<" *** DEBUG *** Option --inIPAddress	  = "<<inputIPAddress<<std::endl;
        std::cout<<" *** DEBUG *** Option --outIPAddress  = "<<outputIPAddress<<std::endl;
        std::cout<<" *** DEBUG *** Option --interface     = "<<interface<<std::endl;
        std::cout<<" ============================================================================== "<<std::endl;
        std::cout<<std::endl;
    }

    /**/
    switch(mode){
        case MODE_LOCAL:
        break;
        case MODE_NET_1:
           // std::unique_ptr<Interface> intr = Interface::CreateInterface();
        break;
        case MODE_NET_2:
        break;
        case MODE_NET_3:
        break;
    }


    SharedMemory shm("microservice", 1280123);


    while (isRun) {

    //    std::this_thread::sleep_for(std::chrono::milliseconds(25));
    }


    return 0;
}
