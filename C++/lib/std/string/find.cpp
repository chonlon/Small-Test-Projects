#include <string>
#include <iostream>
using namespace std;

int main() {
    string s1 = "123";
    string s2 = "12345";
    string s3 = "345";

    cout << s2.find(s1) << ' ' << (s1.find(s2) == string::npos) << ' ' << s2.rfind(s3);
    return 0;
}