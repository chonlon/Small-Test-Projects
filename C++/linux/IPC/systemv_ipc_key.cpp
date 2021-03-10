#include "header.h"

int main() {
    for(int i = 0; i < 10; ++i) {
        std::cout << msgget(IPC_PRIVATE, IPC_CREAT) << "\n";
    }

    return 0;
}