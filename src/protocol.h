#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <memory>
#include <iostream>
#include <stdio.h>
#include <cstring>
#include "signals/shsignals.h"

#define UNIQUE_SHMEM 0x1A2B


namespace ProtocolExchange {

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

    template<typename T>
    struct TSignal{

        TSignal(){
            uint16_t size = 0;

            if(std::is_same<T,ShSignals::SignalPairInt>::value){
            }
            else if( std::is_same<T,ShSignals::swAnalog>::value){
                size = sizeof(T);
            }
            else if( std::is_same<T,ShSignals::Analog>::value){

                countElements = 1+2;
                size = sizeof(ShSignals::Analog::first) + sizeof( ShSignals::Analog::second);
                sizeElement = std::make_unique<uint8_t[]>(countElements);

                sizeElement[1] = sizeof(ShSignals::Analog::first);
                sizeElement[2] = sizeof(ShSignals::Analog::second);
                sizeElement[0] = sizeElement[1] + sizeElement[2];
            }
            else if( std::is_same<T,ShSignals::Discret>::value){
            }
            else if( std::is_same<T,ShSignals::Hardware>::value){
            }
            else if( std::is_same<T,ShSignals::Software>::value){
            }
            else{
            }

            data = std::make_unique<uint8_t[]>( size );
        }

        TSignal(std::string signal):TSignal(){


            if(!signal.empty()){

                signalName = std::make_unique<char>(signal.size() + 1);
                std::copy(signal.begin(), signal.end(), signalName.get());
                signalName.get()[signal.size()] = '\0';
            }
        }


        /** @brief Метод формирования буффера сигнала
         *  @param buffer - буффер сигнала
         *  @param size  - размер буффера
         *  @return size - размер буффера в случае успеха, и -1 в противном случае.
        */
        size_t getBuffer(void* buffer, size_t& size){

            uint16_t offset  = 0;

            if(buffer == NULL) return -1;

            /** @param Копироание имени сигнала в буффер*/
            std::memcpy(buffer + offset, signalName.get(), std::strlen(signalName.get()));
            offset = std::strlen(signalName.get());

            /** @param коприрование размеры элементов хранящиеся в буффере*/
            std::memcpy(buffer + offset, sizeElement.get(), sizeElement[0]);
            offset += countElements;

            /** @param копирование количество элементов в сигнале */
            std::memcpy(buffer + offset, &countElements, sizeof(countElements));
            offset += sizeof(countElements);

            /** @param  копирование данных сигнала */
            if(data.get() != NULL){
                std::memcpy(buffer + offset, data.get(), sizeElement[0]);
                offset += sizeElement[0];
            }

            return size = offset;
        }

        /** @param signalName  - Имя сигнала */
        std::unique_ptr<char>    signalName;

        /** @param Размер одного элемента сигнала.
         *
         *  Примечание: первый байт зарезервирован под общий размер элемента
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


    #define SIZE_HEADER_SHE sizeof(ShmemExchange)
}

#endif // PROTOCOL_H
