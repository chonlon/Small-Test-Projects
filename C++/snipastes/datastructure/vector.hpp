#pragma once

#include <cstring>
#include <utility>

namespace lon {

struct Alloctor
{
    static void* alloc(std::size_t size) {
        return malloc(size);
    }

    static void dealloc(void* p) {
        free(p);
    }
};

template <typename T, typename Alloc = Alloctor>
class Vector
{
public:
    using value_type = T;
    using size_type = std::size_t;

    // not necessary
    // you can using Iterator = value_type*;
    class Iterator
    {
    private:
        friend class Vector;
        value_type* data;

        Iterator(value_type* _data)
            : data(_data) {
        }

    public:
        Iterator operator++() {
            ++data;
            return data;
        }

        Iterator operator--() {
            --data;
            return data;
        }

        Iterator operator+=(size_type size) {
            data += size;
            return data;
        }

        Iterator operator-=(size_type size) {
            data -= size;
            return data;
        }

        Iterator operator-(size_type size) {
            return data - size;
        }

        Iterator operator+(size_type size) {
            return data + size;
        }

        bool operator==(const Iterator& rhs) {
            return data == rhs.data;
        }

        bool operator!=(const Iterator rhs) {
            return data != rhs.data;
        }

        value_type& operator*() {
            return *data;
        }
    };

    ~Vector() {
        clear();
    }

    Iterator begin() const noexcept {
        return begin_;
    }

    Iterator end() const noexcept {
        return end_;
    }

    [[nodiscard]] size_type size() const noexcept {
        return end_ - begin_;
    }

    [[nodiscard]] bool empty() const noexcept {
        return size() == 0;
    }

    [[nodiscard]] bool capacity() const noexcept {
        return buffer_end_ - begin_;
    }

    Vector& push_back(value_type&& r_value) {
        auto p = getNextBufferAddress();
        new(p) value_type(std::forward<value_type>(r_value));
        ++end_;

        return *this;
    }

    Vector& push_back(const value_type& value) {
        auto p = getNextBufferAddress();
        new(p) value_type(value);
        ++end_;

        return *this;
    }

    template <typename... Args>
    Vector& emplace_back(Args&&... args) {
        auto p = getNextBufferAddress();
        new(p) value_type(std::forward<Args>(args)...);
        ++end_;

        return *this;
    }

    void clear() {
        auto* begin = begin_;
        while (begin != end_) {
            begin->~value_type();
            ++begin;
        }
        end_ = begin_;
    }

private:
    bool full() {
        return end_ == buffer_end_;
    }

    size_type getAllocSize() {
        auto _capacity = capacity();
        if (_capacity == 0) {
            return sizeof(value_type) * 4;
        } else if (_capacity < 4096) {
            return _capacity * 2;
        } else {
            return _capacity * 1.5;
        }
    }

    value_type* getNextBufferAddress() {
        if (!full()) {
            return end_;
        } else {
            value_type* new_address =
                static_cast<value_type*>(Alloc::alloc(getAllocSize()));

            auto step = end_ - begin_;
            moveOrMemCpy(new_address);
            Alloc::dealloc(begin_);

            begin_ = new_address;
            end_   = begin_ + step;
            return new_address;
        }
    }

    void moveOrMemCpy(value_type* new_address) {
        if constexpr (std::is_pod<value_type>::value) {
            memcpy(new_address, begin_, end_ - begin_);
        } else {
            auto begin   = begin_;
            auto current = new_address;

            while (begin != end_) {
                new(current) value_type(std::move(*begin));
                ++current;
                ++begin;
            }
            while (begin != end_) {
                begin->~value_type();
                ++begin;
            }
        }
    }

    value_type* begin_ = nullptr;
    value_type* end_   = nullptr;

    value_type* buffer_end_ = nullptr;
};

}
