# mgr-exchange
# Менеджер обмена данными по сети #

## Зависимости менеджера обмена ##

1. Boost версии 1.66.0 
* Библиотека program_option для разбора входных параметров
* Заголовочная библиотека shared_memory для работы с рп


### Инструкция по сборке boost 
1. [скачать boost версии 1.66.0]( http://www.boost.org/users/history/version_1_66_0.html)
2. Распаковать скаченный архив командой zcat "архив boost" | tar -xv
3. Перейти в корневой каталог boost и выполнить список команд:
* ./bootstrap.sh gcc
* ./b2 instal --prefix=/usr/lib/boost_1_66
