#ifndef SHSIGNALS_H
#define SHSIGNALS_H

#include <vector>
#include <deque>
#include <string>
#include <map>
#include <set>

namespace ShSignals {

#pragma pack(push,1)

    /** @breif произвольный сигнал */
    typedef std::pair<int,int> SignalPairInt;

    /** @brief Аналоговый сигнал
     *  @param uint16_t - код аналогового сигнала
     *  @param double   - Пересчитаное значение
     */
    typedef std::pair<uint16_t, double> Analog;

    /** @brief Программно - аналоговый сигнал(без кода АЦП)
     *  @param double   - Пересчитаное значение
     */
    typedef double swAnalog;

    /** @brief Дискретный сигнал
     *  @param bool - значение дискретного сигнала
     */
    typedef bool Discret;

    /** @brief Программный сигнал
     *  @param bool - состояние процесса (true - активен, false - незапущен)
     *  @param map  - Полезные данные запущенного процесса
    */
    typedef std::pair<bool, std::map<std::string, uint32_t>> Software;

    /** @brief Аппаратный сигнал
     *  @param bool - состояние устройства (true - активен, false - незапущен)
     *  @param map  - Полезные данные устройства
    */
    typedef std::pair<bool, std::map<std::string, uint32_t>> Hardware;

#pragma pack(pop)
}

#endif // SHSIGNALS_H
