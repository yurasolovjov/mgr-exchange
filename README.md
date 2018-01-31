# mgr-exchange
# Менеджер обмена данными по сети #

## Зависимости менеджера обмена ##

1. Boost версии 1.66.0 
1.1 Библиотека program_option для разбора входных параметров
1.2 Заголовочная библиотека shared_memory для работы с рп


### Инструкция по сборке boost 
1. [скачать boost версии 1.66.0]( http://www.boost.org/user/history/version_1_66_0.html)
2. Распаковать скаченный архив командой zcat "архив boost" | tar -xv
3. Перейти в корневой каталог boost и выполнить список команд:
3.1 ./bootstrap.sh gcc
3.2 ./b2 instal --prefix=/usr/lib/boost_1_66
