#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <memory>
#include <iostream>
#include <stdio.h>
#include <cstring>
#include "signals/shsignals.h"

#define UNIQUE_SHMEM 0x1A2B


namespace ProtocolExchange {

#pragma pack(push,1)
    struct ShmemExchange{

        /** @param Уникальное число сигнализирующее начало пакета*/
        uint16_t unique = UNIQUE_SHMEM;

        /** @param Идентификатор фрейма */
        uint32_t id;

        /** @param Количество частей в фрейме*/
        uint16_t countParts;

        /** @param Номер части в фрейме*/
        uint16_t numParts;

        /** @param Размер текущего пакета */
        uint16_t size;

        /** @param Тип пакета данных */
        uint8_t  type;

        /** @param количество сигналов в пакете */
        uint16_t countSignals;

        /** @param */
        /** @param */
        /** @param */
        /** @param */
        /** @param */
        /** @param */
    };

#pragma pack(pop)



    template<typename T, typename ...Args>
    struct TSignal{

        TSignal(){
        }

        TSignal(std::string signal):TSignal(){


            if(!signal.empty()){

                signalName = std::make_unique<char>(signal.size() + 1);
                std::copy(signal.begin(), signal.end(), signalName.get());
                signalName.get()[signal.size()] = '\0';
            }
        }

        void setData(T value){

            if(std::is_same<T,ShSignals::SignalPairInt>::value){
            }
            else if( std::is_same<T,ShSignals::swAnalog>::value){
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
        }


        /** @param signalName  - Имя сигнала */
        std::unique_ptr<char>    signalName;

        /** @param Размер одного элемента сигнала.
         *
         *  Примечание: первый байт зарезервирован под общий размер сигнала
         * 	sizeElement[0] - ЗАРЕЗЕРВИРОВАН !
         *
        */
        std::unique_ptr<uint8_t[]>  sizeElement;

        /** @param Количество элементов в сигнале*/
        uint16_t countElements;

        /** @param  буффер сигнала */
        std::unique_ptr<uint8_t[]> data;

        /** @param */

    };

    #define SIZE_HEADER_SHE sizeof(ProtocolExchange::ShmemExchange)
}

#endif // PROTOCOL_H
