#include <folly/io/IOBuf.h>
using namespace folly;

int main() {
    IOBuf::create(100);
    IOBuf::create(2000);
    return 0;
}