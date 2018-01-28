#ifndef SHAREDMEMORY_H
#define SHAREDMEMORY_H
#include <boost/interprocess/managed_shared_memory.hpp>
#include <cstdlib>
#include <cstddef>
#include <cassert>
#include <utility>

#define BOOST_DATE_TIME_NO_LIB 1;

    using namespace boost::interprocess;
    typedef std::pair<double, int> MyType;
class SharedMemory
{
public:
    SharedMemory();
    ~SharedMemory();
};

#endif // SHAREDMEMORY_H
