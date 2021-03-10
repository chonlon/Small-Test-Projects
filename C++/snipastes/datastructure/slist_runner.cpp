#include "list.hpp"
#include <iostream>
#include <base.h>

#include <fmt/os.h>
#include <fmt/format.h>



struct T {
    int no;
    static int time;
    std::string nostr;
    T(int _no) {
        no = _no;
        ++time;
        nostr = std::to_string(_no);
    }
    T(const T& v) {
        no = v.no;
        nostr = v.nostr;
        ++time;
    };
    T& operator=(const T&) = default;
    T(T&&) = delete;
    T& operator=(T&&) = delete;
};
int T::time = 0;

std::ostream& operator<<(std::ostream& out, const T& value) {
    out << '[' << value.no << ',' <<value.nostr << ']';
    return out;
}

int main() {
using namespace lon;
    SList<int> l1;
    SList<T> l2;
    SList<T> l3;
    for(int i = 0; i < 100; ++i) {
        l1.push_back(i);
        l2.emplace_back(i);
    }
    
    for(int i = 0; i < 10; ++i) {
        l3.push_back(i);
    }
    std::cout << "time: "<< T::time << '\n';
    for(auto i = l1.begin(); i != l1.end(); ++i) {
        std::cout << *i << '\n';
    }

    for(auto i : l2) {
        std::cout << i << '\n';
    }

    std::cout << T::time;

}