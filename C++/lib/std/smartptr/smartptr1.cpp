#include <iostream>
#include <memory>
#include <string>

class res
{
public:
    res()
    {
        static int ii{0};
        i = ++ii;
        std::cout << "ctor " << i << "\n";
    }

    ~res()
    {
        std::cout << "dtor " << i << "\n";
    }

    friend std::ostream& operator <<(std::ostream& out, const res& r)
    {
        out << r.i << " printing\n";
        return out;
    }

private:
    int i;
};

void sptrfoo(std::shared_ptr<res> p)
{
    std::cout << "owner count" << p.use_count() << "\n";
    std::cout << *p;
}

void uptrfoo(std::unique_ptr<res> p)
{
    std::cout << *p;
}


int main()
{
    std::cout << "<------------------------------------------------->\n";

    std::shared_ptr<res> s_res{nullptr};
    s_res = std::make_shared<res>();

    sptrfoo(s_res);
    std::cout << "<------------------------------------------------->\n";

    sptrfoo(std::move(s_res));
    //after move s_res will be destory before reset.
    std::cout << "<------------------------------------------------->\n";
    s_res.reset();

    std::unique_ptr<res> u_res = std::make_unique<res>();

    uptrfoo(std::move(u_res));
    std::cout << "<------------------------------------------------->\n";
    u_res.release();
}
