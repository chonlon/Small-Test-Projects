#include <functional>
#include <type_traits>
#include <iostream>

using namespace std;

template <typename T>
class Task;

template <typename R, typename... Args>
class Task<R(Args...)>
{
public:
    Task(std::function<R(Args...)>&& f) : m_fn(std::move(f)) {}
    Task(std::function<R(Args...)>& f) : m_fn(f) {  }

    R run(Args&&... args)
    {
        return m_fn(std::forward<Args>(args)...);
    }

    template <typename F>
    auto Then(F&& f)
    {
        using return_type = typename std::invoke_result_t<F(R)>;

        auto func = std::move(m_fn);
        return Task<return_type(Args...)>([func, &f](Args&&... args)
        {
            return f(func(std::forward<Args>(args)...));
        });
    }
private:
    std::function<R(Args...)> m_fn;
};
