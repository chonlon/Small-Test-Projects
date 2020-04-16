#include <iostream>
#include <string>
using namespace std;

class Date {
public:
    string str;
};

istream& operator <<(istream& s, Date& date) {
    date.str = s.get();
}

int main() {
}