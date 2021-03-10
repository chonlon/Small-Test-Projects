#include <chrono>
#include <iostream>
#include <string>

namespace lon {
using namespace std::chrono;

template <typename ClockType>
milliseconds::rep getTimeSpanMs(const time_point<ClockType>& time_point_begin,
                                const time_point<ClockType>& time_point_end) {
    return duration_cast<milliseconds>(time_point_end - time_point_begin)
        .count();
}

namespace measure {
/**
 * @brief 直接输出的RAII计时类
 *
 * @tparam ClockType chrono中定义的时钟类型
 */
template <typename ClockType = steady_clock>
struct TimeSpan
{
    TimeSpan() noexcept : begin(ClockType::now()) {}

    TimeSpan(const std::string& name)
        : begin(ClockType::now()), case_name(name) {}

    ~TimeSpan() {
        std::cout << case_name
                  << " cost: " << getTimeSpanMs(begin, ClockType::now())
                  << '\n';
    }


    time_point<ClockType> begin;
    std::string case_name;
};

/**
 * @brief 返回'参数'的RAII计时类
 *
 * @tparam ClockType chrono中定义的时钟类型
 */
template <typename ClockType = steady_clock>
struct GetTimeSpan
{
    /**
     * @brief Get the Time Span object
     *
     * @param _total 传入int* 指针, 将会被赋值为在作用域中经过时间, 单位为ms.
     */
    GetTimeSpan(int* _total) noexcept
        : begin(ClockType::now()), total(_total) {}

    ~GetTimeSpan() {
        *total = getTimeSpanMs(begin, ClockType::now());
    }

    time_point<ClockType> begin;
    int* total;
};

/**
 * @brief 测试函数调用需要时长
 *
 * @tparam F
 * @tparam Args
 * @param func
 * @param args
 * @return milliseconds::rep 时长, 单位为毫秒
 */
template <typename F, typename... Args>
milliseconds::rep invokeAndMeasure(F func, Args&&... args) {
    int result;
    {
        GetTimeSpan<> span(&result);
        func(std::forward<Args>(args)...);
    }
    return result;
}

}  // namespace measure
}  // namespace lon
