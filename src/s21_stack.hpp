#ifndef S21_STACK_H_
#define S21_STACK_H_

#include <initializer_list>
#include <algorithm>
// HACK: Replace this with s21::list<T>
#include <list>

namespace s21 {

// HACK: Replace this with s21::list<T>
template <typename T, typename Container = std::list<T>>
class Stack {
  public:
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using size_type = std::size_t;

    // Member functions
  public:
    Stack() noexcept : s{} {
    }

    // Constructors below may look weird but, they will call the required
    // constructor of the Container, assuming the Container implements it.
    explicit Stack(std::initializer_list<value_type> const &items) : s{items} {
    }

    Stack(const Stack &rhs) : s{rhs.s} {
    }

    Stack(Stack &&rhs) noexcept : s{std::move(rhs.s)} {
    }

    ~Stack() noexcept = default;

    Stack &operator=(const Stack &other) {
        s = other.s;
        return *this;
    }

    Stack &operator=(Stack &&other) noexcept {
        s = std::move(other.s);
        return *this;
    }

    // Element access
  public:
    reference top() noexcept {
        return s.back();
    }

    const_reference top() const noexcept {
        return s.back();
    }

    // Capacity
  public:
    [[nodiscard]] bool empty() const noexcept {
        return s.empty();
    }

    size_type size() const noexcept {
        return s.size();
    }
    // Stack Modifiers
    void push(const_reference value) {
        s.push_back(value);
    }

    void push(value_type &&value) {
        s.push_back(std::move(value));
    }

    void pop() noexcept {
        s.pop_back();
    }

    void swap(Stack &other) noexcept {
        std::swap(s, other.s);
    }

    template <typename... Args>
    decltype(auto) emplace(Args &&...args) {
        return s.emplace_back(std::forward<Args>(args)...);
    }

  private:
    Container s;
};

}  // namespace s21

#endif  // S21_STACK_H_
