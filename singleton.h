#ifndef __SINGLETON_H__
#define __SINGLETON_H__

#include <memory>

namespace lirui {


template<class T, class X = void, int N = 0>
class Singleton {
public:
    static T* GetInstance() {
        static T v;
        return &v;
    }
};

template<class T, class X = void, int N = 0>
class SingletonPtr {
public:
    static std::shared_ptr<T> GetInstance() {
        static std::shared_ptr<T> v = std::make_shared<T>();
        return v;
    }
};


}


#endif