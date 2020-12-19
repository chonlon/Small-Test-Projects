#include <iostream>
#include <queue>
#include <string>
#include <cstdlib>
#include <ctime>
#include <pthread.h>
#include <unistd.h>

double getProduceTime() noexcept {
    return std::rand() % 10 / 10.0 + 0.5;
};
void syncPrint(const std::string& str) noexcept {
    static pthread_mutex_t _mutex = PTHREAD_MUTEX_INITIALIZER;
    try
    {
        /* code */
        pthread_mutex_lock(&_mutex);
        std::cout << str;
        pthread_mutex_unlock(&_mutex);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
};

std::queue<std::string> product{};
pthread_cond_t produced = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main() {
    std::srand(std::time(nullptr));

    pthread_t producer, customer;
    pthread_create(
        &producer,
        nullptr,
        [](void*) noexcept -> void* {
            int n = 0;
            while(true) {
                syncPrint("Producting...\n");
                sleep(getProduceTime());
                //std::cout << getProduceTime() << '\n';
                auto prod = "product " + std::to_string(++n);
                pthread_mutex_lock(&mutex);
                product.push(prod);
                pthread_mutex_unlock(&mutex);
                syncPrint("Product Finished with " + prod + "\n");
                pthread_cond_signal(&produced);
            }
            return nullptr;
        },
        nullptr);
    pthread_create(
        &customer,
        nullptr,
        [](void*) noexcept -> void* {
            while(true) {
                pthread_mutex_lock(&mutex);
                while(product.empty())
                    pthread_cond_wait(&produced, &mutex);
                auto prod = product.front();
                product.pop();
                //if(!product.empty()) pthread_cond_signal(&produced);
                pthread_mutex_unlock(&mutex);
                syncPrint("customed " + prod +"\n");
            }
            return nullptr;
        },
        nullptr);

    pthread_join(producer, nullptr);
    pthread_join(customer, nullptr);
}