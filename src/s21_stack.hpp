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
    /**
     * @brief initializer_list constructor
     *
     * @param init Elements an to initialize the stack with
     */
    explicit Stack(std::initializer_list<value_type> const &items) : s{items} {
    }

    /**
     * @brief Copy constructor - copies all values from the rhs
     *
     * @param rhs Object to copy from
     */
    Stack(const Stack &rhs) : s{rhs.s} {
    }

    /**
     * @brief Move constructor - steals all the resources from the given object
     *
     * @param rhs Object to steal resources from
     */
    Stack(Stack &&rhs) noexcept : s{std::move(rhs.s)} {
    }

    /**
     * @brief Destructor - cleans up the memory used
     *
     * @details Destructs the stack. The destructors of the elements are called
     * and the used storage is deallocated. Note, that if the elements are
     * pointers, the pointed-to objects are not destroyed.
     */
    ~Stack() noexcept = default;

    /**
     * @brief Copy assignment - copies all the elements from the given object
     *
     * @param rhs Objects to copy elements from
     * @return Results of the copy assignment
     */
    Stack &operator=(const Stack &other) {
        s = other.s;
        return *this;
    }

    /**
     * @brief Move assignment - steals all the resources from the given object
     *
     * @param rhs Objects to steal resources from
     * @return Results of the move assignment
     */
    Stack &operator=(Stack &&other) noexcept {
        s = std::move(other.s);
        return *this;
    }

    // Element access
  public:
    /**
     * @brief Returns reference to the top element in the stack.
     *
     * @details This is the most recently pushed element. This element will be
     * removed on a call to pop(). Effectively calls s.back().
     *
     * @return Reference to the last element
     */
    reference top() noexcept {
        return s.back();
    }

    /**
     * @brief Returns reference to the top element in the stack.
     *
     * @details This is the most recently pushed element. This element will be
     * removed on a call to pop(). Effectively calls s.back().
     *
     * @return Reference to the last element
     */
    const_reference top() const noexcept {
        return s.back();
    }

    // Capacity
  public:
    /**
     * @brief Checks if the underlying container has no elements, i.e. whether
     * s.empty().
     *
     * @return True if empty, otherwise false
     */
    [[nodiscard]] bool empty() const noexcept {
        return s.empty();
    }

    /**
     * @brief Returns the number of elements in the underlying container, that
     is, s.size().
     *
     * @return The number of elements in the container.
     */
    size_type size() const noexcept {
        return s.size();
    }
    // Stack Modifiers
    /**
     * @brief Pushes the given element value to the top of the stack.
     * Effectively calls s.push_back(value)
     *
     * @param value the value of the element to push
     */
    void push(const_reference value) {
        s.push_back(value);
    }

    // Stack Modifiers
    /**
     * @brief Pushes the given element value to the top of the stack.
     * Effectively calls s.push_back(std::move(value))
     *
     * @param value the value of the element to push
     */
    void push(value_type &&value) {
        s.push_back(std::move(value));
    }

    /**
     * @brief Removes the top element from the stack. Effectively calls
     * s.pop_back()
     */
    void pop() noexcept {
        s.pop_back();
    }

    /**
     * @brief Exchanges the contents of the container adaptor with those of
     * other. Effectively calls std::swap(s, other.s);
     *
     * @param other Container adaptor to exchange the contents with
     */
    void swap(Stack &other) noexcept {
        std::swap(s, other.s);
    }

    /**
     * @brief Pushes a new element on top of the stack
     *
     * @details The element is constructed in-place, i.e. no copy or move
     * operations are performed. The constructor of the element is called with
     * exactly the same arguments as supplied to the function. *Effectively
     * calls s.emplace_back(std::forward<Args>(args)...);
     * @param args arguments to forward to the constructor of the element
     * @return The value or reference, if any, returned by the above call to
     * Container::emplace_back
     */
    template <typename... Args>
    decltype(auto) emplace_back(Args &&...args) {
        return s.emplace_back(std::forward<Args>(args)...);
    }

  private:
    Container s;
};

}  // namespace s21

#endif  // S21_STACK_H_
