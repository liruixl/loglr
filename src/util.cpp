#include "util.h"

#include<iostream>
#include<thread>

namespace liuri {

//获取当前线程Id
pid_t GetThreadId(){
    std::thread::id tid = std::this_thread::get_id();
}


}