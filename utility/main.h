#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <cstring>
#include <argparser.h>
#include <signal.h>
#include <memory>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/program_options.hpp>



/** Пространство для работы с РП и обработкой входного массива данных */
using namespace boost::interprocess;
namespace po = boost::program_options;

/** @brief шаблонная функция чтения
 *  @param name - имя сигнала разделяемой памяти
 */
template<typename T>
bool read(std::string  signal, managed_shared_memory& segment);

/** @brief шаблонная функция записи
 *  @param name - имя сигнала разделяемой памяти
 *  @param value - строка содержащая значения signal
 */
template<typename T>

bool write(std::string  signal, std::string value, managed_shared_memory& segment);

/** @brief шаблонная функция обработки сигнала
 *  @param name - имя сигнала разделяемой памяти
 *  @param value - строка содержащая значения signal
 */
template<typename T>
bool process(std::string  signal, std::string value, managed_shared_memory& segment);

#endif // MAIN_H
