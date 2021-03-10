#pragma once
#include <cstdint>
#include <memory>

namespace lon {
// 类模板原型, 没有定义特化的类型使用hash会报错(没有operator()函数)
template <typename Key>
struct hash
{
};

// 指针偏特化
template <typename Key>
struct hash<Key*>
{
    size_t operator()(Key* p) const noexcept {
        return reinterpret_cast<size_t>(p);
    }
};

#define LON_HASH_SPECIFICATION(KEY)               \
    template<> struct hash<KEY> {                 \
        size_t operator()(KEY key) const noexcept { \
            return static_cast<size_t>(key);      \
        }                                         \
    };

LON_HASH_SPECIFICATION(bool)

LON_HASH_SPECIFICATION(char)

LON_HASH_SPECIFICATION(signed char)

LON_HASH_SPECIFICATION(unsigned char)

LON_HASH_SPECIFICATION(int16_t)

LON_HASH_SPECIFICATION(uint16_t)

LON_HASH_SPECIFICATION(int32_t)

LON_HASH_SPECIFICATION(uint32_t)

LON_HASH_SPECIFICATION(int64_t)

LON_HASH_SPECIFICATION(uint64_t)


#undef LON_HASH_SPECIFICATION


// float pointing type hash is quite complex
// see https://stackoverflow.com/questions/7403210/hashing-floating-point-values


inline size_t bitwise_hash(const unsigned char* first, size_t count) {
#if (_MSC_VER && _WIN64) || ((__GNUC__ || __clang__) &&__SIZEOF_POINTER__ == 8)
    const size_t fnv_offset = 14695981039346656037ull;
    const size_t fnv_prime  = 1099511628211ull;
#else
        const size_t fnv_offset = 2166136261u;
        const size_t fnv_prime = 16777619u;
#endif
    size_t result = fnv_offset;
    for (size_t i = 0; i < count; ++i) {
        result ^= (size_t)first[i];
        result *= fnv_prime;
    }
    return result;
}

template <>
struct hash<float>
{
    size_t operator()(const float& val) {
        return val == 0.0f
            ? 0
            : bitwise_hash((const unsigned char*)&val, sizeof(float));
    }
};

template <>
struct hash<double>
{
    size_t operator()(const double& val) {
        return val == 0.0f
            ? 0
            : bitwise_hash((const unsigned char*)&val, sizeof(double));
    }
};

template<typename T>
struct EqualTo
{
    bool operator()(const T& lhs, const T& rhs) {
        return lhs == rhs;
    }
};



template <typename Key, typename Hash = hash<Key>, typename KeyEqual = EqualTo<Key>>
class unordered_set
{
public:


private:
};

}
