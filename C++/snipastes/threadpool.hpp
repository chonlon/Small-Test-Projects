#include <queue>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <exception>
#include <iostream>
#include <sstream>

///fixme 如果只有一个核心, 所有线程都不会被条件变量唤醒, 导致所有线程都在阻塞.

void sync_print(const std::string& str) {
    static std::mutex mutex;
    {
        std::lock_guard<std::mutex> lock(mutex);
        std::cout << str;
    }
}

class ThreadPool {
public:
    using TaskFunc = std::function<void()>;
    ThreadPool(int thread_num = 4) {
        for(int i = 0; i < thread_num; ++i) {
            threads_.emplace_back([this]() mutable {
                TaskFunc func = nullptr;
                while(true) {
                    {
                        std::unique_lock<std::mutex> lock{mutex_};
                        cond_.wait(lock);
                        if(tasks_.empty()) continue;
                        func = tasks_.front();
                        tasks_.pop();
                    }
                    try
                    {
                        func();
                    }
                    catch (std::exception &e)
                    {
                        std::stringstream ss;
                        ss << "got expection in threadpool while exec func, expection: " << e.what() << '\n';
                        sync_print(ss.str());
                    }
                    {
                        {
                            std::lock_guard<std::mutex> lock(mutex_);
                            if(!tasks_.empty())
                                cond_.notify_one();
                        }
                    }
                }
                
            });
        }
    }

    void addTask(TaskFunc func) {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            tasks_.push(std::move(func));
        }
        cond_.notify_one();
    }

    std::size_t leftTask() {
        std::lock_guard<std::mutex> lock(mutex_);
        return tasks_.size();
    }
    std::size_t threadCount() {
        return threads_.size();
    }

private:
    std::queue<TaskFunc> tasks_{}; // guard by mutex
    std::vector<std::thread> threads_{};
    std::condition_variable cond_{};
    std::mutex mutex_{};
};
