#include "sharedmemory.h"

SharedMemory::SharedMemory()
{

    managed_shared_memory segment(create_only, "MySharedMemory", 65536);

    MyType *instance = segment.construct<MyType>
            ("MyType instance")  //name of the object
            (100.0, 20);            //ctor first argument
    /*
         //Create an array of 10 elements of MyType initialized to {0.0, 0}
         MyType *array = segment.construct<MyType>
            ("MyType array")     //name of the object
            [10]                 //number of elements
            (0.0, 0);            //Same two ctor arguments for all objects

     //Create an array of 3 elements of MyType initializing each one
     //to a different value {0.0, 0}, {1.0, 1}, {2.0, 2}...
     float float_initializer[3] = { 0.0, 1.0, 2.0 };
     int   int_initializer[3]   = { 0, 1, 2 };

     MyType *array_it = segment.construct_it<MyType>
        ("MyType array from it")   //name of the object
        [3]                        //number of elements
        ( &float_initializer[0]    //Iterator for the 1st ctor argument
        , &int_initializer[0]);    //Iterator for the 2nd ctor argument
*/
}

SharedMemory::~SharedMemory(){
    struct shm_remove
     {
        shm_remove() { shared_memory_object::remove("MySharedMemory"); }
        ~shm_remove(){ shared_memory_object::remove("MySharedMemory"); }
     } remover;
}
