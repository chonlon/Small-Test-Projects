#include <iostream>
#include <fstream>
#include <chrono>

void writelnWithFulsh(std::ostream& os, const std::string& str) {
    os << str << std::endl;
}

void writeln(std::ostream& os, const std::string& str) {
    os << str << '\n';
}

int main() {
    auto start = std::chrono::steady_clock::now();
    {
        std::ofstream outfile("output.txt", std::ios_base::trunc);
        for(int i = 0; i < 1000; ++i) {
            writelnWithFulsh(outfile, "hello world");
        }
    }
    
    auto stop1 = std::chrono::steady_clock::now();
    
    std::cout << "using endl take " << std::chrono::duration_cast<std::chrono::milliseconds>(stop1 - start).count() << " ms.\n";
    {
        std::ofstream outfile("output.txt", std::ios_base::trunc);
        for (int i = 0; i < 1000; ++i) {
            writeln(outfile, "hello world");
        }
        outfile << std::flush;
    }
    
    auto stop2 = std::chrono::steady_clock::now();
    std::cout << "using \\n take " << std::chrono::duration_cast<std::chrono::milliseconds>(stop2 - stop1).count() << " ms.\n";
    
    return 0;
}