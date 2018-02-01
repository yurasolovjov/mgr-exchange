project( mgr-exchange )

cmake_minimum_required( VERSION 3.6 )

set(isInit on)

if( ${BOOST_ROOT} NOT STREQUAL )
    message(STATUS "NOT BOOST ROOT")
    if(WIN32)
        set(BOOST_ROOT "C:/boost_1_64_0/boost_mingw_link_static")
    else(UNIX)
        set(BOOST_ROOT "/usr/lib/boost_1_66")
    endif()
endif()

set(BOOST_DIR ${BOOST_ROOT})
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_DEBUG ON)

#Поиск компонетнов boost
find_package(Boost 1.64.0 REQUIRED program_options system COMPONENTS)

set( CMAKE_CXX_STANDARD 14 )
set( CMAKE_INCLUDE_CURRENT_DIR ON )
set( CMAKE_AUTOMOC ON )

include_directories( ${CMAKE_SOURCE_DIR}/src )
include_directories( ${CMAKE_SOURCE_DIR}/include )

set (SOURCE_FILES src/main.cpp
                  src/interface.cpp
                  src/interface.h
                  src/asiointerface.cpp
                  src/asiointerface.h
                  src/argparser.cpp
                  src/argparser.h
                  src/sharedmemory.cpp
                  src/sharedmemory.h
                  include/signals/shsignals.h
                  include/shmem-api.hpp
    )

#Включение директории Boost
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
else()
    set(isInit off)
endif()



#Сборка компонета ПО
if( isInit )

    add_executable( ${PROJECT_NAME} ${SOURCE_FILES} )

    if(WIN32)
        set(DEPENDENCY_LIB ws2_32 wsock32)
    else(UNIX)
        set(DEPENDENCY_LIB rt pthread )
    endif()

    target_link_libraries( ${PROJECT_NAME} ${Boost_LIBRARIES} ${DEPENDENCY_LIB})

#                                           "/usr/lib/x86_64-linux-gnu/librt.so")
else()
    message(STATUS "*** ERROR *** Build is down")
endif()


# Сборка утилиты для работы с разделяемой памятью
if(BUILD_UTILITY)

    # Имя утилиты для работы с РП
    set(UTILITY_NAME shctl)

    #Исходные коды для сборки утилиты управления РП
    set (SOURCE_FILES_UTILITY utility/main.cpp
                              include/shmem-api.hpp
         )

    add_executable( ${UTILITY_NAME} ${SOURCE_FILES_UTILITY} )

    target_link_libraries( ${UTILITY_NAME} ${Boost_LIBRARIES} ${DEPENDENCY_LIB} )
endif()
