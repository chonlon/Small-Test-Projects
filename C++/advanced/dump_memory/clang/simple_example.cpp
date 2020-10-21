class Base {
protected:
    int foo;
public:
    int method(int p) {
        return foo + p;
    }
};

struct Point {
    double cx, cy;
};

class Derived : public Base {
public:
    int method(int p) {
        return foo + bar + p;
    }
    
    static void staticFunc() {}
protected:
    int bar, baz;
    Point a_point;
    //static char c;
};

int main(int argc, char** argv) {
    return sizeof(Derived);
}