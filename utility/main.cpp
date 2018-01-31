#include <iostream>
#include <cstring>
#include <argparser.h>
#include <signal.h>
#include <memory>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/program_options.hpp>
#include "shsignals.h"

using namespace boost::interprocess;
namespace po = boost::program_options;

int main(int argc, char** argv)
{

    po::options_description desc("The manager exchange \n short description: ");

    desc.add_options()
           ("help,h","help \n")
           ("shmem,m",    po::value<std::string>(),"Name of shared memory")
           ("signal,s",   po::value<std::string>(),"Name of signal")
           ("value,v",    po::value<std::string>(),"Value of signal in shared memory")
           ("type,t",     po::value<std::string>(),"Type of signal")
           ("read,r","Operation: read of signal in shared memory")
           ("write,w","Operation: write of signal in shared memory")
           ("destroy,d", po::value<std::string>(),"Destroy signal")
           ("list,l","Show list stored in shared memory")
    ;

    po::variables_map vm;

    std::string shmem  = "";
    std::string signal = "";
    std::string value  = "";
    std::string destroy = "";
    bool        operationRead  = false;
    bool        operationWrite = false;
    bool        operationList  = false;

    try{
          po::store(po::parse_command_line(argc, argv, desc), vm);
          po::notify(vm);
    }
    catch(po::error& e){
         std::cerr<<"*** ERROR *** "<<e.what()<<std::endl;
    }

    if (vm.count("help")){
          std::cout<<desc<<std::endl;
    }

    /** Имя разделяемой памяти */
    if(vm.count("shmem")){
        shmem = vm["shmem"].as<std::string>();
    }
    else{
        std::cout<<"*** ERROR *** Shared memory name is not set"<<std::endl;
        return 0;
    }
    /** Имя сигнала */
    if(vm.count("signal")){
        signal = vm["signal"].as<std::string>();
    }

    /** Значение сигнала */
    if(vm.count("value")){
        value = vm["value"].as<std::string>();
    }

    /** Типы выполняемых операций над сигналом "Чтение"*/
    if(vm.count("read")){
        operationRead = true;
    }

    /** Типы выполняемых операций над сигналом "Запись"*/
    if(vm.count("write")){
        operationWrite = true;
    }

    /** Отображение сигналов в разделяемой памяти */
    if(vm.count("list")){
        operationList = true;
    }

    if(vm.count("destroy")){
        destroy = vm["destroy"].as<std::string>();
    }

    try{

        managed_shared_memory segment(open_only, shmem.c_str());

        /** @brief Чтение сигнала из разделяемой памяти */
        if(!signal.empty() && operationRead){
            std::pair<SignalPairInt*, managed_shared_memory::size_type> res;
            res = segment.find<SignalPairInt> (signal.c_str());

            if( res.second == 1){
                std::cout<<" *** SIGNAL *** "<<signal<<" : "<<res.first->first<<" "<<res.first->second<<std::endl;
            }
            else{
                std::cerr<<"*** SIGNAL: "<<signal<<" *** not found"<<std::endl;
            }
        }

        /** @brief Запись сигнала в разделяемую память */
        if(!signal.empty() && operationWrite){
            std::pair<SignalPairInt*, managed_shared_memory::size_type> res;
            res = segment.find<SignalPairInt>(signal.c_str());

            if( res.second == 1){
                res.first->first = 0.0;
                res.first->second = 0;
                std::cout<<" *** SIGNAL *** "<<signal<<" : "<<res.first->first<<" "<<res.first->second<<std::endl;
            }
        }

        /* Список имён в РП*/
        if(operationList){
            for(auto itr = segment.named_begin(); itr != segment.named_end(); ++itr){
                static int i = 0;
                const managed_shared_memory::char_type *name = itr->name();
                std::cout<<"Signal "<<i<<" : "<<name<<std::endl;
                i++;
            }
        }

        if(!destroy.empty()){
            bool r = segment.destroy<SignalPairInt>(destroy.c_str());

            if( r ){
                std::cout<<"*** SIGNAL: "<<destroy<<" has been destroyed"<<std::endl;
            }
        }
    }
    catch(interprocess_exception& ex){
        std::cout<<"*** Exception *** "<<ex.what()<<std::endl;
        return 0;
    }


    return 0;
}
