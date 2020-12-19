#include <cstdlib>
#include <ctime>
#include <iostream>
#include <pthread.h>
#include <queue>
#include <semaphore.h>
#include <string>
#include <unistd.h>

double getProduceTime() noexcept {
    return std::rand() % 10 / 10.0 + 0.5;
};
void syncPrint(const std::string& str) noexcept {
    static pthread_mutex_t _mutex = PTHREAD_MUTEX_INITIALIZER;
    try {
        /* code */
        pthread_mutex_lock(&_mutex);
        std::cout << str;
        pthread_mutex_unlock(&_mutex);
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
};

std::queue<std::string> product{};
sem_t produced_sem;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main() {
    std::srand(std::time(nullptr));

    pthread_t producer, customer;

    sem_init(&produced_sem, 0, 0);
    pthread_create(
        &producer,
        nullptr,
        [](void*) noexcept -> void* {
            int n = 0;
            while (true) {
                syncPrint("Producting...\n");
                sleep(getProduceTime());
                // std::cout << getProduceTime() << '\n';
                auto prod = "product " + std::to_string(++n);
                pthread_mutex_lock(&mutex);
                product.push(prod);
                pthread_mutex_unlock(&mutex);
                syncPrint("Product Finished with " + prod + "\n");
                //pthread_cond_signal(&produced);
                sem_post(&produced_sem);
            }
            return nullptr;
        },
        nullptr);
    pthread_create(
        &customer,
        nullptr,
        [](void*) noexcept -> void* {
            while (true) {
                sem_wait(&produced_sem);
                pthread_mutex_lock(&mutex);
                auto prod = product.front();
                product.pop();
                // if(!product.empty()) pthread_cond_signal(&produced);
                pthread_mutex_unlock(&mutex);
                syncPrint("customed " + prod + "\n");
            }
            return nullptr;
        },
        nullptr);

    pthread_join(producer, nullptr);
    pthread_join(customer, nullptr);
}