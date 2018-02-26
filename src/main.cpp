#include <iostream>
#include <cstring>
#include <argparser.h>
#include <signal.h>
#include "argparser.h"
#include <memory>
#include "interface.h"
#include "asiointerface.h"
#include "sharedmemory.h"
#include "signals/shsignals.h"
#include "protocol.h"
#include "serialize.h"

static bool isRun = true;

void signalHandler(int signo) {

    std::cerr << "Signal Handler get signal: ";

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

using boost::asio::ip::udp;
int main(int argc, char** argv)
{

    signal(SIGABRT, signalHandler);
    signal(SIGTERM, signalHandler);
    signal(SIGINT,  signalHandler);



    ShSignals::Analog as1(0xffff,0.0);

    uint32_t sizep = sizeof(ShSignals::Analog::first) + sizeof(ShSignals::Analog::second);

    Serialize srial;
    srial << as1;

    srial.print();
//    srial.add<ShSignals::Analog>(as, ass1);


    /*
    ProtocolExchange::TSignal<ShSignals::Analog> ts("asdf");
    ShSignals::Analog a1(3,9.3);
    ts.setData(a1);
    uint8_t asdb[255] = {0};
    size_t sz = sizeof(asdb);
    std::cout<<ts.getBuffer(asdb, sz)<<std::endl;

    uint16_t* as1 = reinterpret_cast<uint16_t*>(&asdb[9]);
    double* as2 = reinterpret_cast<double*>(&asdb[11]);
    printf(" %x %x %x %x %x %x %x %x \n", asdb[11],asdb[12], asdb[13], asdb[14], asdb[15], asdb[16], asdb[17], asdb[18], asdb[19] );
    printf("%d %f \n", *as1, *as2);
    */


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

    if(mode == MODE_NET_1){

        std::unique_ptr<InputInterface> intr = InputInterface::CreateInterface(0,45452);
        intr.get()->exec();

        while(true){}
    }
    else if(mode == MODE_NET_2){

        std::unique_ptr<OutputInterface> intr2 = OutputInterface::CreateInterface(0,inputIPAddress,45452);
        intr2.get()->exec();
        while(true){}
       // intr2.get()->send(bif,si);
    }


//    SharedMemory shm("microservice", 1280123);




    while (isRun) {

    //    std::this_thread::sleep_for(std::chrono::milliseconds(25));
    }


    return 0;
}
