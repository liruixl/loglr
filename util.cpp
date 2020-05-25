#include "util.h"

#include<iostream>
#include<thread>

namespace lirui {

//获取当前线程Id
pid_t GetThreadId(){
    //std::thread::id tid = std::this_thread::get_id();
    auto i = std::hash<std::thread::id>{}(std::this_thread::get_id());
    return i;
}

uint32_t GetFiberId() {
    return 0;
}



}