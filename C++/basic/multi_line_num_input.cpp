#include <sstream>
#include <string>
#include <vector>
#include <iostream>

int main(int argc, char** argv) {
    using std::vector;
    using std::string;
    using std::cin;

    string s_line;
    int num;
    vector<vector<int>> nums;
    while(getline(cin, s_line)) {
        std::istringstream iss(s_line);
        vector<int> v;
        while(iss >> num) {
            v.push_back(num);
        }
        nums.emplace_back(std::move(v));
    }

//...your code here...
}