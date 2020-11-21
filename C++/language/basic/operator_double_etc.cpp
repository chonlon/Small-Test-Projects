#include <iostream>


class Rational {
    public:
    Rational(int numerator = 0, int denominator = 1) :
        numerator_(numerator),
        denominator_(denominator)
    {
    }

    operator double() const {
        return numerator_ * 1.0 / denominator_;
    }
    private:
    int numerator_;
    int denominator_;
};

int main() {
    std::cout << Rational(1, 2)<<'\n';
    return 0;
}