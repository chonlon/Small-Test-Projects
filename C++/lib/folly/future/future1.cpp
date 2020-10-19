// 在官方示例中稍作修改的小栗子

#include <folly/executors/ThreadedExecutor.h>
#include <folly/futures/Future.h>
#include <iostream>

using namespace std;
using namespace folly;

int foo(int x) {
    cout << "foo(" << x << ")" << endl;
    return x + 1;
}

int main() {
    ThreadedExecutor executor;
    cout << "making Promise" << endl;
    Promise<int> p;
    Future<int>  f =
        p.getSemiFuture().via(&executor);
    auto f2 = move(f).thenValue(foo);
    cout << "Future chain made" << endl;

    cout << "fulfilling Promise" << endl;
    p.setValue(42);
    // move(f2).get();

    auto f3 = move(f2).thenValue(
        [](int a) -> int { return a * a; });

    cout << "value:" << move(f3).get() << endl;

    cout << "Promise fulfilled" << endl;
}