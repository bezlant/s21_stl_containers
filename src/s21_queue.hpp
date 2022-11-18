#ifndef S21_QUEUE_H_
#define S21_QUEUE_H_

#include <initializer_list>
#include <algorithm>
#include <queue>
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
    /**
     * @brief initializer_list constructor
     *
     * @param init Elements an to initialize the queue with
     */
    explicit Queue(std::initializer_list<value_type> const &items) : q{items} {
    }

    /**
     * @brief Copy constructor - copies all values from the rhs
     *
     * @param rhs Object to copy from
     */
    Queue(const Queue &rhs) : q{rhs.q} {
    }

    /**
     * @brief Move constructor - steals all the resources from the given object
     *
     * @param rhs Object to steal resources from
     */
    Queue(Queue &&rhs) noexcept : q{std::move(rhs.q)} {
    }

    /**
     * @brief Destructor - cleans up the memory used
     *
     * @details Destructs the queue. The destructors of the elements are called
     * and the used storage is deallocated. Note, that if the elements are
     * pointers, the pointed-to objects are not destroyed.
     */
    ~Queue() noexcept = default;

    /**
     * @brief Copy assignment - copies all the elements from the given object
     *
     * @param rhs Objects to copy elements from
     * @return Results of the copy assignment
     */
    Queue &operator=(const Queue &other) {
        q = other.q;
        return *this;
    }

    /**
     * @brief Move assignment - steals all the resources from the given object
     *
     * @param rhs Objects to steal resources from
     * @return Results of the move assignment
     */
    Queue &operator=(Queue &&other) noexcept {
        q = std::move(other.q);
        return *this;
    }

    // Element access
  public:
    /**
     * @brief Returns reference to the first element in the queue.
     *
     * @details This element will be the first element to be removed on a call
     * to pop(). Effectively calls q.front()
     *
     * @return Reference to the first element
     */
    reference front() noexcept {
        return q.front();
    }

    /**
     * @brief Returns reference to the first element in the queue. This element
     * will be the first element to be removed on a call to pop(). Effectively
     * calls q.front()
     *
     * @return Reference to the first element
     */
    const_reference front() const noexcept {
        return q.front();
    }

    /**
     * @brief Returns reference to the last element in the queue.
     *
     * @details This is the most recently pushed element. Effectively calls
     * q.back().
     *
     * @return Reference to the last element
     */
    reference back() noexcept {
        return q.back();
    }

    /**
     * @brief Returns reference to the last element in the queue.
     *
     * @details This is the most recently pushed element. Effectively calls
     * q.back().
     *
     * @return Reference to the last element
     */
    const_reference back() const noexcept {
        return q.back();
    }
    // Capacity
  public:
    /**
     * @brief Checks if the underlying container has no elements, i.e. whether
     * q.empty().
     *
     * @return True if empty, otherwise false
     */
    [[nodiscard]] bool empty() const noexcept {
        return q.empty();
    }

    /**
     * @brief Returns the number of elements in the underlying container, that
     is, q.size().
     *
     * @return The number of elements in the container.
     */
    size_type size() const noexcept {
        return q.size();
    }
    // Stack Modifiers
    /**
     * @brief Pushes the given element value to the end of the queue.
     * Effectively calls q.push_back(value)
     *
     * @param value the value of the element to push
     */
    void push(const_reference value) {
        q.push_back(value);
    }

    /**
     * @brief Pushes the given element value to the end of the queue.
     * Effectively calls q.push_back(std::move(value))
     *
     * @param value the value of the element to push
     */
    void push(value_type &&value) {
        q.push_back(std::move(value));
    }

    /**
     * @brief Removes an element from the front of the queue. Effectively calls
     * q.pop_front()
     */
    void pop() noexcept {
        q.pop_front();
    }

    /**
     * @brief Exchanges the contents of the container adaptor with those of
     * other. Effectively calls std::swap(q, other.q);
     *
     * @param other Container adaptor to exchange the contents with
     */
    void swap(Queue &other) noexcept {
        std::swap(q, other.q);
    }

    /**
     * @brief Pushes a new element to the end of the queue.
     *
     * @details The element is constructed in-place, i.e. no copy or move
     * operations are performed. The constructor of the element is called with
     * exactly the same arguments as supplied to the function. *Effectively
     * calls q.emplace_back(std::forward<Args>(args)...);
     * @param args arguments to forward to the constructor of the element
     * @return The value or reference, if any, returned by the above call to
     * Container::emplace_back
     */
    template <typename... Args>
    decltype(auto) emplace_front(Args &&...args) {
        return q.emplace_back(std::forward<Args>(args)...);
    }

  private:
    Container q;
};

}  // namespace s21

#endif  // S21_QUEUE_H_
