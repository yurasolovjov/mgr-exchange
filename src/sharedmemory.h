#ifndef SHAREDMEMORY_H
#define SHAREDMEMORY_H
#include <boost/interprocess/managed_shared_memory.hpp>
#include <cstdlib>
#include <cstddef>
#include <cassert>
#include <utility>
#include <memory>


using namespace boost::interprocess;

#define DEFAULT_SHMEM_SIZE 1024

class SharedMemory
{
public:
    explicit SharedMemory( std::string name, uint32_t size = DEFAULT_SHMEM_SIZE);
    ~SharedMemory();

public:

private:
    /** Структура управления памятью */
    std::unique_ptr<managed_shared_memory> _segment;

    /** Имя разделяемой памяти */
    std::string _name;

    /** Размер разделяемой памяти */
    std::uint32_t _size;

};

#endif // SHAREDMEMORY_H
