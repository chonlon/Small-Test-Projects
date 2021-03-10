#pragma once

#include <type_traits>
#include <utility>

namespace lon {
template <typename T>
struct SListNode
{
    SListNode(SListNode<T>* _next = nullptr)
        : next(_next) {
    }

    SListNode(T&& _value, SListNode<T>* _next)
        : value(_value),
          next(_next) {
    }

    SListNode(const T& _value, SListNode<T>* _next)
        : value(_value),
          next(_next) {
    }

    template <typename... Args>
    SListNode(SListNode<T>* _next, Args&&... args)
        : value(std::forward<Args>(args)...),
          next(_next) {
    }

    SListNode<T>* next;
    T value;
};

template <typename T>
class SList
{
public:
    struct SListIterator
    {
        SListIterator(SListNode<T>* _data)
            : data(_data) {
        }

        T& operator*() {
            return data->value;
        }

        SListIterator operator++() {
            this->data = data->next;
            return *this;
        }

        bool operator==(const SListIterator& rhs) {
            return this->data == rhs.data;
        }

        bool operator!=(const SListIterator& rhs) {
            return this->data != rhs.data;
        }

    private:
        SListNode<T>* data;
    };

    SList()
        : begin_(nullptr),
          end_(nullptr),
          size_(0) {
    }

    ~SList() {
        clear();
    }

    // front
    SList& push_back(T&& value) {
        auto node = new SListNode<T>(std::forward<T>(value), nullptr);
        if (end_)
            end_->next = node;
        else
            begin_ = node;
        end_ = node;
        ++size_;
        return *this;
    }

    SList& push_back(const T& value) {
        auto node = new SListNode<T>(value, nullptr);
        if (end_)
            end_->next = node;
        else
            begin_ = node;
        end_ = node;
        ++size_;
        return *this;
    }

    template <typename... Args>
    SList& emplace_back(Args&&... args) {
        auto node = new SListNode<T>(nullptr, std::forward<Args>(args)...);
        if (end_)
            end_->next = node;
        else
            begin_ = node;
        end_ = node;
        ++size_;
        return *this;
    }

    void clear() {
        while (begin_) {
            auto temp = begin_;
            begin_    = begin_->next;
            delete temp;
        }
        size_ = 0;
        end_  = nullptr;
    }

    bool empty() {
        return size_ == 0;
    }

    std::size_t size() {
        return size_;
    }

    SListIterator begin() {
        return SListIterator(begin_);
    }

    SListIterator end() {
        return SListIterator(nullptr);
    }

private:
    SListNode<T>* begin_;
    SListNode<T>* end_;
    std::size_t size_;
};

template <typename T>
class List
{
public:

    struct Node
    {
        Node() = default;

        Node(T&& _value)
            : value(_value) {
        }

        Node(const T& _value)
            : value(_value) {
        }

        template <typename... Args>
        Node(Args&&... args)
            : value(std::forward<Args>(args)...) {
        }

        Node* next = nullptr;
        Node* prev = nullptr;
        T value;
    };

    struct Iterator
    {
        Iterator(Node* _data)
            : data(_data) {
        }

        T& operator*() {
            return data->value;
        }

        Iterator operator++() {
            this->data = data->next;
            return *this;
        }

        Iterator operator--() {
            this->data = data->prev;
            return *this;
        }

        bool operator==(const Iterator& rhs) {
            return this->data == rhs.data;
        }

        bool operator!=(const Iterator& rhs) {
            return this->data != rhs.data;
        }

    private:
        Node* data;
    };

    List() = default;

    List(const List& list) {
        begin_ = list.begin_;
        end_   = list.end_;
        size_  = list.size_;
    }

    ~List() {
        clear();
    }
    void clear() {
        while (begin_) {
            auto temp = begin_;
            begin_    = begin_->next;
            delete temp;
        }
        size_ = 0;
        end_  = nullptr;
    }

    List& push_back(T&& value) {
        auto node = new Node(std::forward<T>(value));
        if (end_)
            end_->next = node;
        else
            begin_ = node;
        node->prev = end_;
        end_       = node;
        ++size_;
        return *this;
    }

    List& push_back(const T& value) {
        auto node = new Node(value);
        if (end_)
            end_->next = node;
        else
            begin_ = node;
        node->prev = end_;
        end_       = node;
        ++size_;
        return *this;
    }

    template <typename... Args>
    List& emplace_back(Args&&... args) {
        auto node = new Node(std::forward<Args>(args)...);
        if (end_)
            end_->next = node;
        else
            begin_ = node;
        node->prev = end_;
        end_       = node;
        ++size_;
        return *this;
    }

    bool empty() const noexcept {
        return size_ == 0;
    }

    std::size_t size() const noexcept {
        return size_;
    }


    Iterator begin() const noexcept {
        return begin_;
    }

    Iterator end() const noexcept {
        return nullptr;
    }

private:
    Node* begin_ = nullptr;
    Node* end_   = nullptr;
    std::size_t size_ = 0;
};

} // namespace lon
