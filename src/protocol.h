#ifndef PROTOCOL_H
#define PROTOCOL_H

#define UNIQUE_SHMEM 0x1A2B
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

    /** @param */
    /** @param */
    /** @param */
    /** @param */
    /** @param */
    /** @param */
};

#define SIZE_HEADER_SHE sizeof(ShmemExchange)

#endif // PROTOCOL_H
