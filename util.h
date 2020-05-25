#ifndef __UTIL_H__
#define __UTIL_H__

#include<iostream>
#include<thread>

namespace lirui{

pid_t GetThreadId(); //获取线程ID
uint32_t GetFiberId(); //获取协程ID

}


#endif