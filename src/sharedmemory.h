#ifndef SHAREDMEMORY_H
#define SHAREDMEMORY_H
#include <boost/interprocess/managed_shared_memory.hpp>
#include <cstdlib>
#include <cstddef>
#include <cassert>
#include <utility>
#include <memory>

#define BOOST_DATE_TIME_NO_LIB 1;

using namespace boost::interprocess;

class SharedMemory
{
public:
    SharedMemory();
    ~SharedMemory();


public:
    template<typename T, typename... Args>
    bool registrated(std::string  name, Args& ...args);

private:
    std::unique_ptr<managed_shared_memory> segment;

};

#endif // SHAREDMEMORY_H
