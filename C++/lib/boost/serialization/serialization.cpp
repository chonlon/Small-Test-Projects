#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;
class Address {
public:
    string street;
    string city;
    int suite;
private:
    friend class boost::serialization::access;
    template<class Ar> void serialize(Ar& ar, const unsigned int version) {
        ar & street;
        ar & city;
        ar & suite;
    }
};

class Contact {
public:
    string name;
    Address* address = nullptr;
private:
    friend class boost::serialization::access;
    template<class Ar> void serialize(Ar& ar, const unsigned int version) {
        ar & name;
        ar & address;
    }
};

int main() {
    ostringstream oss;
    boost::archive::text_oarchive oa(oss);
    Contact c;
    c.name = "jojo";
    c.address = new Address{"Don Road", "Tokyo", 100};
    oa << c;
    string s = oss.str();

    cout << s << '\n';

    istringstream iss(oss.str());
    boost::archive::text_iarchive ia(iss);

    Contact result;
    ia >> result;
    return 0;
}