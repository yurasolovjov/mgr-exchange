#include <iostream>
#include <cstring>
#include <argparser.h>
#include <signal.h>
#include <memory>
#include <boost/interprocess/managed_shared_memory.hpp>

using namespace boost::interprocess;
typedef std::pair<double, int> MyType;

int main(int argc, char** argv)
{

    std::cout<<"shread <<<<<<<<<<<<<<<<<<<<<< " <<std::endl;
    managed_shared_memory segment(open_read_only, "MySharedMemory");

    /* Список имён в РП*/

    for(auto itr = segment.named_begin(); itr != segment.named_end(); ++itr){
        const managed_shared_memory::char_type *name = itr->name();

        std::cout<<"name object: "<<name<<std::endl;
    }

    std::pair<MyType*, managed_shared_memory::size_type> res;

    //Find the array
//    res = segment.find<MyType> ("MyType array");
    //Length should be 10
  //  if(res.second != 10) return 1;

    //Find the object
    res = segment.find<MyType> ("MyType instance");

    //Length should be 1
    if(res.second == 1){
        std::cout<<" first: "<<res.first->first<<" second: "<<res.first->second<<std::endl;
    }
    else std::cout<<" Not found"<<std::endl;

    res = segment.find<MyType> ("asd");

    try{
        if(res.second == 1){
                std::cout<<" first: "<<res.first->first<<" second: "<<res.first->second<<std::endl;
        }
        else std::cout<<" Not found"<<std::endl;
    }
    catch(interprocess_exception &ex){
        std::cout << ex.what() << std::endl;
        return 1;
     }

return 0;

    /*
    //Find the array constructed from iterators
    res = segment.find<MyType> ("MyType array from it");
    //Length should be 3
    if(res.second != 3) return 1;

    //We're done, delete all the objects
    segment.destroy<MyType>("MyType instance");
    segment.destroy<MyType>("MyType array from it");
    */
    //std::this_thread::sleep_for(std::chrono::milliseconds(frequency));

    segment.destroy<MyType>("MyType array");
    return 0;
}
