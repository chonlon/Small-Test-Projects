#include "../../header/base.h"
#include <folly/executors/DrivableExecutor.h>
#include <folly/executors/InlineExecutor.h>
#include <folly/executors/ManualExecutor.h>
#include <folly/futures/Future.h>
#include <iostream>
using namespace folly;
using std::cout;
using std::boolalpha;
using std::endl;
void viafoo1() {
    //auto future = makeFuture(std::move(1)).thenTry([](Try<int>&& t){ return t.value == 1;});
    auto future =  makeFuture(std::move(1)).thenTry([](Try<int>&& t) {
        return t.value() == 1;
    });

    cout << boolalpha << future.value() << endl;
}

void multiThenTryFoo1() {
    struct Worker {
        Future<std::string> doWork(Try<std::string>&& t) {
            return makeFuture(t.value() + ";class");
        }
        static Future<std::string> doWorkStatic(Try<std::string>&& t) {
            return makeFuture(t.value() + ";class-static");
        }
    } w;

    auto f = makeFuture(std::string("start")).thenTry(Worker::doWorkStatic).then(&Worker::doWork, &w);
    cout << f.value() << endl;
}

int main() {
    printDividing();
    viafoo1();
    printDividing();
    multiThenTryFoo1();
    printDividing();
}