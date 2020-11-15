#include <folly/Synchronized.h>

#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <shared_mutex>

using namespace folly;


int main() {
    Synchronized<std::vector<int>> sync_vec;
    std::vector<int> vec;
    vec.reserve(200000);// alloc here, otherwise two thread will race on alloc and **may** make error

    auto push_func = [](std::vector<int>* vec) {
        for (int i = 0; i < 100000; ++i)
            vec->push_back(1);
    };

    auto sync_push_func = [](Synchronized<std::vector<int>>* vec) {
        {
            auto locked = vec->wlock(); //如果这里是rlock, 会有编译期错误, 是通过返回两种不同的访问指针来限定'写' 操作.
            for (int i = 0; i < 100000; ++i)
                locked->push_back(1);
        }
    };


    std::thread t1(push_func, &vec);
    std::thread t2(push_func, &vec);

    t1.join();
    t2.join();

    int count = 0;
    for (auto item : vec) {
        if (item != 1) {
            ++count;
        }
    }
    std::cout << "no protect error count: " << count << '\n';

    std::thread t3(sync_push_func, &sync_vec);
    std::thread t4(sync_push_func, &sync_vec);
    t3.join();
    t4.join();

    count = 0;
    auto locked = sync_vec.rlock();
    for(auto item : *locked) {
        if(item != 1) {
            ++count;
        }
    }

    std::cout << "rwlock: error count: " << count << '\n';

    return 0;
}