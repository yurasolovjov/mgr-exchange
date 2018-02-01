#ifndef SHMEM_API_H
#define SHMEM_API_H

#include <iostream>
#include <cstring>
#include <argparser.h>
#include <signal.h>
#include <memory>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/program_options.hpp>
#include <memory>
#include "signals/shsignals.h"


namespace ShSignals {

    static const uint32_t default_size_shmem = 1024;

    /** Пространство для работы с РП и обработкой входного массива данных */
    using namespace boost::interprocess;
    namespace po = boost::program_options;


    /** Создание разделяемой памяти*/
    std::unique_ptr<managed_shared_memory> created(std::string shmem, uint32_t size){

        if( !shmem.empty() && size > 0){

            try{
                return std::make_unique<managed_shared_memory>(open_or_create,shmem.c_str(),size);
            }
            catch(interprocess_exception& ex){
                return nullptr;
            }
        }
        else return nullptr;
    }

    /** Подключение к разделяемой памяти*/
    std::unique_ptr<managed_shared_memory> connect(std::string shmem){

        if( !shmem.empty() ){

            try{
                return std::make_unique<managed_shared_memory>(open_or_create, shmem.c_str(), ShSignals::default_size_shmem );
            }
            catch(interprocess_exception& ex){
                return nullptr;
            }
        }
        else return nullptr;

    }

    /** @brief шаблонная функция чтения
     *  @param name - имя сигнала разделяемой памяти
     */
    template<typename T>
    bool read(std::string  signal, managed_shared_memory* segment){

        if(signal.empty()){
            std::cout<<" Signal name is empty"<<std::endl;
            return false;
        }

        std::pair<T*, managed_shared_memory::size_type> res;

        res = segment->find<T>(signal.c_str());

        if(res.second != 1){
            std::cerr<<"*** SIGNAL: "<<signal<<" *** not found"<<std::endl;
            return false;
        }

        if(std::is_same<T,ShSignals::SignalPairInt>::value){
            std::cout<<"Signal "<<signal<<" value: "<<res.first->first<<" | "<<res.first->second<<std::endl;
        }
        else if( std::is_same<T,ShSignals::Analog>::value){
        }
        else if( std::is_same<T,ShSignals::Discret>::value){
        }
        else if( std::is_same<T,ShSignals::Hardware>::value){
        }
        else if( std::is_same<T,ShSignals::Software>::value){
        }
        else{
        }
        return true;
    }

    /** @brief шаблонная функция записи
     *  @param name - имя сигнала разделяемой памяти
     *  @param value - строка содержащая значения signal
     */
    template<typename T, typename ...Args>
    bool write(std::string  signal, managed_shared_memory* segment, Args& ...value){

        if(signal.empty()){
            std::cout<<" Signal name is empty"<<std::endl;
            return false;
        }

        T* obj = segment->find_or_construct<T>(signal.c_str())(value...);

        if(std::is_same<T,ShSignals::SignalPairInt>::value){
        }
        else if( std::is_same<T,ShSignals::Analog>::value){
        }
        else if( std::is_same<T,ShSignals::Discret>::value){
        }
        else if( std::is_same<T,ShSignals::Hardware>::value){
        }
        else if( std::is_same<T,ShSignals::Software>::value){
        }
        else{
        }
        return true;
    }

    /** @brief шаблонная функция обработки сигнала
     *  @param name - имя сигнала разделяемой памяти
     *  @param value - строка содержащая значения signal
     */
    template<typename T>
    bool process(std::string  signal, std::string value, managed_shared_memory& segment);

    /** @brief шаблонная функция обработки сигнала
     *  @param name - имя сигнала разделяемой памяти
     *  @param segment - управляющая структура памяти
     */
    template<typename T>
    bool remove(std::string  signal, managed_shared_memory* segment){
        if( !signal.empty()){
            return segment->destroy<T>(signal.c_str());
        }
        else return false;
    }
}
#endif // SHMEM_API_H
