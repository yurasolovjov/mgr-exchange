#include "sharedmemory.h"
#include "shmem-api.hpp"

SharedMemory::SharedMemory( std::string name, uint32_t size )
{


   _segment = ShSignals::created(name, size);
    ShSignals::SignalPairInt a(100, 1000);
    ShSignals::Analog d(100, 1000.1);


    ShSignals::write<ShSignals::SignalPairInt>("asd1", _segment.get(), a);
    ShSignals::write<ShSignals::SignalPairInt>("asd2", _segment.get(), a);
    ShSignals::write<ShSignals::SignalPairInt>("asd3", _segment.get(), a);
    ShSignals::write<ShSignals::SignalPairInt>("asd4", _segment.get(), a);
    ShSignals::write<ShSignals::SignalPairInt>("asd5", _segment.get(), a);
    ShSignals::write<ShSignals::SignalPairInt>("asd6", _segment.get(), a);
    ShSignals::write<ShSignals::SignalPairInt>("asd7", _segment.get(), a);
    ShSignals::write<ShSignals::SignalPairInt>("asd8", _segment.get(), a);
    ShSignals::write<ShSignals::SignalPairInt>("asd9", _segment.get(), a);
    ShSignals::write<ShSignals::SignalPairInt>("asd10", _segment.get(), a);
    ShSignals::write<ShSignals::Analog>("asd10", _segment.get(), d);
}

SharedMemory::~SharedMemory(){
    struct shm_remove
     {
        shm_remove() { shared_memory_object::remove("MySharedMemory"); }
        ~shm_remove(){ shared_memory_object::remove("MySharedMemory"); }
     } remover;
}
