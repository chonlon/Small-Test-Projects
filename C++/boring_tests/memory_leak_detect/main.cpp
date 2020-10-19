#include <memory>

int main() {
    ::operator new(100);
    return 0;
}