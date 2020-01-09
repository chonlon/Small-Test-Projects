#include <folly/futures/Future.h>
#include <folly/executors/ThreadedExecutor.h>
#include <iostream>

using namespace std;
using namespace folly;

void foo(int x)
{
    cout << "foo(" << x << ")" << endl;
}

int main()
{
    ThreadedExecutor executor;
    cout << "making Promise" << endl;
    Promise<int> p;
    Future<int> f = p.getSemiFuture().via(&executor);
    auto f2 = move(f).thenValue(foo);
    cout << "Future chain made" << endl;

    cout << "fulfilling Promise" << endl;
    p.setValue(42);
    move(f2).get();
    cout << "Promise fulfilled" << endl;
}