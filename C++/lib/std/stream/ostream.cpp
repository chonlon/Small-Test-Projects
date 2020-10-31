#include <iostream>
#include "../../../header/ChronoHelper.h"

const char* str = "an rather than long but useless string\n";
constexpr int outter_looptime = 1;
constexpr int inner_looptime = 10000;

void doOut()
{
    for (int j = 0; j < outter_looptime; j++)
    {
        for (int i = 0; i < inner_looptime; i++)
        {
            std::cout << str;
        }
    }
}

void doPrintf()
{
    for (int j = 0; j < outter_looptime; j++)
    {
        for (int i = 0; i < inner_looptime; i++)
        {
            printf("%s", str);
        }
    }
}

int main(int argc, char** argv)
{
    auto begin = std::chrono::steady_clock::now();
    {
        std::ios::sync_with_stdio(true);
        doOut();
    }

    auto time_point1 = std::chrono::steady_clock::now();

    {
        std::ios::sync_with_stdio(false);
        doOut();
    }

    auto time_point2 = std::chrono::steady_clock::now();

    {
        std::ios::sync_with_stdio(false);
        doPrintf();
    }

    auto time_point3 = std::chrono::steady_clock::now();

    std::cout << "with sync on take " << lon::getTimeSpanMs(begin, time_point1) << " ms\n";
    std::cout << "with sync off take " << lon::getTimeSpanMs(time_point1, time_point2) << " ms\n";
    std::cout << "with sync off take " << lon::getTimeSpanMs(time_point2, time_point3) << " ms\n";


    return 0;
}
