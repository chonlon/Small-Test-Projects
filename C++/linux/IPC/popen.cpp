#include "header.h"
#include <iostream>
#include <string>

int main() {
    std::string command{"cat -n "};
    std::string input;
    std::cin >> input;
    command.append(std::move(input));
    FILE* fp = popen(command.data(), "r");
    char buff[1024];
    while(fgets(buff, 1024, fp))
        fputs(buff, stdout);
    fclose(fp);

    return 0;
}