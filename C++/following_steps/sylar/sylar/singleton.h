#pragma once
#include <memory>

namespace sylar {



template <typename T, size_t N = 1>
class Singleton
{
public:
    static T* getInstance() {
        static T t;

        return &t;
    }

    static std::shared_ptr<T> getInstancePtr() {
        static std::shared_ptr<T> ptr(std::make_shared<T>());
        return ptr;
    }
};

}