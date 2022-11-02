#ifndef S21_QUEUE_H_
#define S21_QUEUE_H_

#include <initializer_list>
#include <algorithm>
// HACK: Replace this with s21::list<T>
#include <list>

namespace s21 {

// HACK: Replace this with s21::list<T>
template <typename T, typename Container = std::list<T>>
class Queue {
  public:
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using size_type = std::size_t;

    // Member functions
  public:
    Queue() noexcept : q{} {
    }

    // Constructors below may look weird but, they will call the required
    // constructor of the Container, assuming the Container implements it.
    explicit Queue(std::initializer_list<value_type> const &items) : q{items} {
    }

    Queue(const Queue &rhs) : q{rhs.q} {
    }

    Queue(Queue &&rhs) noexcept : q{std::move(rhs.q)} {
    }

    ~Queue() noexcept = default;

    Queue &operator=(const Queue &other) {
        q = other.q;
        return *this;
    }

    Queue &operator=(Queue &&other) noexcept {
        q = std::move(other.q);
        return *this;
    }

    // Element access
  public:
    reference front() noexcept {
        return q.front();
    }

    const_reference front() const noexcept {
        return q.front();
    }

    reference back() noexcept {
        return q.back();
    }

    const_reference back() const noexcept {
        return q.back();
    }
    // Capacity
  public:
    [[nodiscard]] bool empty() const noexcept {
        return q.empty();
    }

    size_type size() const noexcept {
        return q.size();
    }
    // Stack Modifiers
    void push(const_reference value) {
        q.push_back(value);
    }

    void push(value_type &&value) {
        q.push_back(std::move(value));
    }

    void pop() noexcept {
        q.pop_front();
    }

    void swap(Queue &other) noexcept {
        std::swap(q, other.q);
    }

    template <typename... Args>
    decltype(auto) emplace_front(Args &&...args) {
        return q.emplace_back(std::forward<Args>(args)...);
    }

  private:
    Container q;
};

}  // namespace s21

#endif  // S21_QUEUE_H_
