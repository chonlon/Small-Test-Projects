#include <benchmark/benchmark.h>
#include <cstring>


std::string remove_ctrl(const std::string& s) {
    std::string result;
    result.reserve(s.length());
    for (int i = s.length() - 1; i >= 0; --i)
    {
        if (s[i] >= 0x20)
            result += s[i];
    }
    return result;
}

std::string remove_ctrl_it(const std::string& s) {
    std::string result;
    result.reserve(s.length());
    for (auto i = s.begin(), end = s.end(); i != end; ++i)
    {
        if (*i >= 0x20)
            result += *i;
    }
    return result;
}

void remove_ctrl_cstrings(char* destp, const char* srcp, size_t size) {
    for(size_t i = 0; i < size; ++i) {
        if(srcp[i] >= 0x20)
            *destp++ = srcp[i];
    }
    *destp = 0;
}

static void StringIter(benchmark::State& state) {
    std::string s{"rather than longer string for test"};

    for (auto _ : state) {
        auto ss = remove_ctrl_it(s);
        benchmark::DoNotOptimize(ss);
    }
}
BENCHMARK(StringIter);

static void StringSubscript(benchmark::State& state) {
    std::string s{"rather than longer string for test"};

    for(auto _ : state) {
        auto ss = remove_ctrl(s);
        benchmark::DoNotOptimize(ss);
    }
}
BENCHMARK(StringSubscript);

static void StringCString(benchmark::State& state) {
    const char* src = "rather than longer string for test";
    char s[100];
    std::strcpy(s, src);

    for (auto _ : state)
    {
        char buffer[100];
        size_t len = std::strlen(s);
        char* dest = buffer;
        remove_ctrl_cstrings(buffer, src, len);
        //benchmark::DoNotOptimize(ss);
    }
}
BENCHMARK(StringCString);

BENCHMARK_MAIN();