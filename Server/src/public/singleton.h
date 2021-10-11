#ifndef __TAO_SINGLETON_H__
#define __TAO_SINGLETON_H__

#include <memory>

namespace Tao{

template<class T, class X = void, int N = 0>
class Singleton{
public:
    static T* getInstance(){
        static T v;
        return &v;
    }
};

template<class T, class X = void, int N = 0>
class SingletonPtr{
public:
    static std::shared_ptr<T> getInstance(){
        std::shared_ptr<T> v(new T);
        return v;
    }
};

}
#endif