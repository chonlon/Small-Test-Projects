#include <iostream>
#include <productVersion.h>

int main() {
    std::cout << "hello world\n";
    std::cout
        << "git branch: " << GIT_BRANCH << '\n'
        << "git commit hash: " << GIT_COMMIT_HASH << '\n'
        << "git commit time: " << GIT_COMMIT_TIME << '\n'
        << "build time: " << CURRENTTIME << '\n';
    return 0;
}
