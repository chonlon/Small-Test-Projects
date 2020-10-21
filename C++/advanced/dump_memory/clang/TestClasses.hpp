class Base {
public:
    virtual void foo() = 0;
};

class SimpleInherit : public Base {
public:
    void foo() override {}
private:
    int var;
};

class Base2 {
public:
    virtual void foo2() = 0;
};

class MultiInherit : public Base, public Base2 {
public:
    void foo() override {}
    void foo2() override {}
private:
    int var;
};

class BaseWithData {
public:
    virtual int method() { return var; }

    int var;
};

class InheritWithData1 : virtual public BaseWithData {
public:
    int method() override { return var1; }
    int var1;
};

class InheritWithData2 : virtual public BaseWithData {
public:
    int method() override { return var2; }
    int var2;
};

class MultiInheritWithData : public InheritWithData1, public InheritWithData2 {
public:
    int method() override { return InheritWithData1::var1; }
    int var3;
};
