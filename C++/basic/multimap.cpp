#include <iostream>
#include <map>

using namespace std;
int main() {
    multimap<string, string> map;
    map.insert(make_pair("12", "12"));
    cout << "1";
    string s{"1"};
    cout << s;
    terminate_with<std::logic_error>(
        "setCallback unexpected state");
}
