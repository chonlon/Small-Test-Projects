#include <fcntl.h>
#include <unistd.h>
#include <iostream>

int main(int argc, char** argv) {
    if(argc != 2){
        std::cerr << "usage: <apthname>\n";
        exit(-1);
    }
    if(access(argv[1], R_OK) < 0) {
        std::cerr << "access error for " << argv[1] << '\n';
        //exit(-1);
    } else {
        std::cout << "read access OK\n";
    }

    if(open(argv[1], O_RDONLY) < 0) {
        std::cerr << "open error for " << argv[1] << '\n';
        
    } else {
        std::cout << "open for reading OK\n";
    }


    return 0;
}