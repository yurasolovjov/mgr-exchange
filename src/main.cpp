#include <iostream>
#include <cstring>
#include <argparser.h>
#include <signal.h>
#include "argparser.h"
#include <memory>
#include "interface.h"
#include "asiointerface.h"
#include "pycomposition.h"

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
    uint16_t    inPort;
    uint16_t    outPort;
    uint32_t    sizeShmem;
    std::string modeString;
    std::string inputIPAddress;
    std::string outputIPAddress;
    std::string interface;


    if( verbose ){

        std::cout<<" ============================================================================== "<<std::endl;
        std::cout<<" *** DEBUG *** Option --path	      = "<<args.getModulePath()<<std::endl;
        std::cout<<" *** DEBUG *** Option --interface     = "<<args.getInterface()<<std::endl;
        std::cout<<" *** DEBUG *** Option --frequency     = "<<args.getFrequency()<<std::endl;
        std::cout<<" *** DEBUG *** Option --port          = "<<args.getPort()<<std::endl;
        std::cout<<" *** DEBUG *** Option --size_buffer   = "<<args.getSizeBuffer()<<std::endl;
        std::cout<<" *** DEBUG *** Option --module        = "<<args.getModule()<<std::endl;
        std::cout<<" *** DEBUG *** Option --verbose       = "<<(verbose ? "true" : "false" )<<std::endl;
        std::cout<<" ============================================================================== "<<std::endl;
        std::cout<<std::endl;
    }


    std::string libraryPath = args.getModulePath();
    std::string module = args.getModule();
    PyComposition pc(libraryPath, module);
    tuple_t arg;
    std::vector<double> a,b;
    a.push_back(1.0);
    a.push_back(2.0);
    a.push_back(3.0);
    a.push_back(4.0);
    a.push_back(5.0);
    a.push_back(6.0);

    b = a;

    arg.push_back(a);
    arg.push_back(b);

    pc.setArgs(arg);

    pc.CallPythonFunction(static_cast<std::string>("func3"), NULL, NULL);

    std::unique_ptr<Interface> net = Interface::CreateInterface();

    //std::this_thread::sleep_for(std::chrono::milliseconds(frequency));

    return 0;
}
