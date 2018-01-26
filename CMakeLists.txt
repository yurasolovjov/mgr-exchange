project( mgr-exchange )

cmake_minimum_required( VERSION 3.6 )

set(isInit on)
set(BOOST_ROOT "C:/boost_1_64_0/boost_mingw_link_static")
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

set (SOURCE_FILES src/main.cpp
                  src/interface.cpp
                  src/interface.h
                  src/asiointerface.cpp
                  src/asiointerface.h
                  src/argparser.cpp
                  src/argparser.h
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
    endif()

    target_link_libraries( ${PROJECT_NAME} ${Boost_LIBRARIES}
                                           ${DEPENDENCY_LIB}
                                           -static -static-libgcc -static-libstdc++ )
else()
    message(STATUS "*** ERROR *** Build is down")
endif()
