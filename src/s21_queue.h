#ifndef S21_CONTAINERS_S21_CONTAINERS_S21_STACK_H_S21_QUEUE_H_
#define S21_CONTAINERS_S21_CONTAINERS_S21_STACK_H_S21_QUEUE_H_

#include "s21_list.h"
#include <algorithm>
#include <initializer_list>

namespace s21 {

template <typename T, typename Container = s21::list<T>>
class queue {
  public:
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using size_type = std::size_t;

    // Member functions
  public:
    queue() noexcept : container_{} {
    }

    // Constructors below may look weird but, they will call the required
    // constructor of the Container, assuming the Container implements it.
    /**
     * @brief initializer_list constructor
     *
     * @param init Elements an to initialize the queue with
     */
    explicit queue(std::initializer_list<value_type> const &items)
        : container_{items} {
    }

    /**
     * @brief Copy constructor - copies all values from the rhs
     *
     * @param rhs Object to copy from
     */
    queue(const queue &rhs) : container_{rhs.container_} {
    }

    /**
     * @brief Move constructor - steals all the resources from the given object
     *
     * @param rhs Object to steal resources from
     */
    queue(queue &&rhs) noexcept : container_{std::move(rhs.container_)} {
    }

    /**
     * @brief Destructor - cleans up the memory used
     *
     * @details Destructs the queue. The destructors of the elements are called
     * and the used storage is deallocated. Note, that if the elements are
     * pointers, the pointed-to objects are not destroyed.
     */
    ~queue() noexcept = default;

    /**
     * @brief Copy assignment - copies all the elements from the given object
     *
     * @param rhs Objects to copy elements from
     * @return Results of the copy assignment
     */
    queue &operator=(const queue &other) {
        container_ = other.container_;
        return *this;
    }

    /**
     * @brief Move assignment - steals all the resources from the given object
     *
     * @param rhs Objects to steal resources from
     * @return Results of the move assignment
     */
    queue &operator=(queue &&other) noexcept {
        container_ = std::move(other.container_);
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
        return container_.front();
    }

    /**
     * @brief Returns reference to the first element in the queue. This element
     * will be the first element to be removed on a call to pop(). Effectively
     * calls q.front()
     *
     * @return Reference to the first element
     */
    const_reference front() const noexcept {
        return container_.front();
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
        return container_.back();
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
        return container_.back();
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
        return container_.empty();
    }

    /**
     * @brief Returns the number of elements in the underlying container, that
     is, q.size().
     *
     * @return The number of elements in the container.
     */
    [[nodiscard]] size_type size() const noexcept {
        return container_.size();
    }
    // Stack Modifiers
    /**
     * @brief Pushes the given element value to the end of the queue.
     * Effectively calls q.push_back(value)
     *
     * @param value the value of the element to push
     */
    void push(const_reference value) {
        container_.push_back(value);
    }

    /**
     * @brief Pushes the given element value to the end of the queue.
     * Effectively calls q.push_back(std::move(value))
     *
     * @param value the value of the element to push
     */
    void push(value_type &&value) {
        container_.push_back(std::move(value));
    }

    /**
     * @brief Removes an element from the front of the queue. Effectively calls
     * q.pop_front()
     */
    void pop() noexcept {
        container_.pop_front();
    }

    /**
     * @brief Exchanges the contents of the container adaptor with those of
     * other. Effectively calls std::swap(q, other.q);
     *
     * @param other Container adaptor to exchange the contents with
     */
    void swap(queue &other) noexcept {
        std::swap(container_, other.container_);
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
    void emplace_back(Args &&...args) {
        container_.emplace_back(std::forward<Args>(args)...);
    }

  private:
    Container container_;
};

}  // namespace s21

#endif  // S21_CONTAINERS_S21_CONTAINERS_S21_STACK_H_S21_QUEUE_H_
