#ifndef S21_VECTOR_H_
#define S21_VECTOR_H_

#include "s21_exceptions.hpp"
#include <algorithm>
#include <initializer_list>
#include <limits>
#include <utility>
#include <vector>

namespace s21 {

const std::string errOutOfRange =
    "Accessing the vector with []. The index is out of range";

/**
 * @brief s21::vector - STL like std::vector implementation
 *
 * @tparam T containers type
 */
template <typename T>
class vector {
  public:
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using iterator = T *;
    using const_iterator = const T *;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

    // Member functions
  public:
    /**
     * @brief Default constructor doesn't assign any fields because all the
     * fields are default initialized
     */
    vector() {
    }

    /**
     * @brief Parameterized constructor, creates a vector of a given size
     *
     * @param size Size of the vector
     */
    explicit vector(size_type size) {
        m_Size = size;
        m_Capacity = size;
        m_Buffer = nullptr;
        if (size > 0) {
            m_Buffer = new value_type[m_Capacity];
        }
    }

    /**
     * @brief initializer_list constructor
     *
     * @param init Elements an to initialize the vector with
     */
    explicit vector(std::initializer_list<value_type> const &init)
        : m_Size{init.size()},
          m_Capacity(init.size()), m_Buffer{new value_type[m_Capacity]} {

        std::copy(init.begin(), init.end(), m_Buffer);
    }

    /**
     * @brief Copy constructor - copies all values from the rhs
     *
     * @param rhs Object to copy from
     */
    vector(const vector &rhs) {
        m_Size = rhs.m_Size;
        m_Capacity = rhs.m_Capacity;
        m_Buffer = nullptr;
        if (m_Size > 0) {
            m_Buffer = new value_type[m_Capacity];
        }
        std::copy(rhs.begin(), rhs.end(), m_Buffer);
    }

    /**
     * @brief Move constructor - steals all the resources from the given object
     *
     * @param rhs Object to steal resources from
     */
    vector(vector &&rhs) noexcept {
        m_Size = std::exchange(rhs.m_Size, 0);
        m_Capacity = std::exchange(rhs.m_Capacity, 0);
        m_Buffer = std::exchange(rhs.m_Buffer, nullptr);
    }

    /**
     * @brief Destructor - cleans up the memory used
     */
    ~vector() {
        delete[] m_Buffer;
    }

    /**
     * @brief Move assignment - steals all the resources from the given object
     *
     * @param rhs Objects to steal resources from
     * @return Results of the move assignment
     */
    constexpr vector &operator=(vector &&rhs) noexcept {
        if (this != &rhs) {
            m_Size = std::exchange(rhs.m_Size, 0);
            m_Capacity = std::exchange(rhs.m_Capacity, 0);
            m_Buffer = std::exchange(rhs.m_Buffer, nullptr);
        }

        return *this;
    }

    /**
     * @brief Copy assignment - copies all the elements from the given object
     *
     * @param rhs Objects to copy elements from
     * @return Results of the copy assignment
     */
    constexpr vector &operator=(const vector &rhs) {
        if (this != &rhs) {
            delete[] m_Buffer;

            if (rhs.m_Size > 0) {
                m_Buffer = new value_type[rhs.m_Capacity];
                std::copy(rhs.begin(), rhs.end(), m_Buffer);
            }
            m_Size = rhs.m_Size;
            m_Capacity = rhs.m_Capacity;
        }

        return *this;
    }
    // Element Access
  public:
    /**
     * @brief Safe access to the elements of the container
     *
     * @param pos Index of the element to access
     * @return The element of the vector at the given index
     */
    constexpr reference at(size_type pos) {
        if (pos >= m_Size)
            throw std::out_of_range(errOutOfRange);

        return m_Buffer[pos];
    }

    /**
     * @brief Safe access to the elements of the container
     *
     * @param pos Index of the element to access
     * @return The element of the vector at the given index
     */
    constexpr const_reference at(size_type pos) const {
        if (pos >= m_Size)
            throw std::out_of_range(errOutOfRange);

        return m_Buffer[pos];
    }

    /**
     * @brief Safe access to the elements of the container
     *
     * @param pos Index of the element to access
     * @return The element of the vector at the given index
     */
    constexpr reference operator[](size_type pos) {
        return at(pos);
    }

    /**
     * @brief Safe access to the elements of the container
     *
     * @param pos Index of the element to access
     * @return The element of the vector at the given index
     */
    constexpr const_reference operator[](size_type pos) const {
        return at(pos);
    }

    /**
     * @brief Safe access to the first element of the container
     *
     * @return The first element of the container
     */
    constexpr reference front() {
        if (m_Size == 0)
            throw ZeroSizeException{};
        return *begin();
    }

    /**
     * @brief Safe access to the first element of the container
     *
     * @return The first element of the container
     */
    constexpr const_reference front() const {
        if (m_Size == 0)
            throw ZeroSizeException{};
        return *begin();
    }

    /**
     * @brief Safe access to the last element of the container
     *
     * @return The last element of the container
     */
    constexpr reference back() {
        if (m_Size == 0)
            throw ZeroSizeException{};
        return *std::prev(end());
    }

    /**
     * @brief Safe access to the last element of the container
     *
     * @return The last element of the container
     */
    constexpr const_reference back() const {
        if (m_Size == 0)
            throw ZeroSizeException{};
        return *std::prev(end());
    }

    /**
     * @brief Access to the underlying pointer to the memory we allocated for
     * the vector
     *
     * @return Pointer to the first element of the vector
     */
    constexpr iterator data() noexcept {
        return m_Buffer;
    }

    /**
     * @brief Access to the underlying pointer to the memory we allocated for
     * the vector
     *
     * @return Pointer to the first element of the vector
     */
    constexpr const_iterator data() const noexcept {
        return m_Buffer;
    }

    // Iterators
    /**
     * @brief Access to the iterator pointing to the first element of the
     * container
     *
     * @return Pointer to the first element of the vector
     */
    constexpr iterator begin() noexcept {
        return m_Buffer;
    }

    /**
     * @brief Access to the iterator pointing to the first element of the
     * container
     *
     * @return Pointer to the first element of the vector
     */
    constexpr const_iterator begin() const noexcept {
        return m_Buffer;
    }

    /**
     * @brief Access to the iterator pointing to the last element of the
     * container
     *
     * @return Pointer to the last element of the vector
     */
    constexpr iterator end() noexcept {
        return m_Buffer + m_Size;
    }

    /**
     * @brief Access to the iterator pointing to the last element of the
     * container
     *
     * @return Pointer to the last element of the vector
     */
    constexpr const_iterator end() const noexcept {
        return m_Buffer + m_Size;
    }

    // Capacity
  public:
    /**
     * @brief Checks if the container is empty
     *
     * @return True if empty, otherwise false
     */
    [[nodiscard]] bool empty() const noexcept {
        return begin() == end();
    }

    /**
     * @brief Current size of the container (std::distance(begin(), end())
     *
     * @return Size of the container
     */
    constexpr size_type size() const noexcept {
        return std::distance(begin(), end());
    }

    /**
     * @brief Returns the maximum number of elements the container is able to
     * hold due to system or library implementation limitations, i.e.
     * std::distance(begin(), end()) for the largest container
     *
     * @return Maximum capacity
     */
    constexpr size_type max_size() const noexcept {
        return std::numeric_limits<difference_type>::max();
    }

    /**
     * @brief Increase the capacity of the vector (the total number of elements
     * that the vector can hold without requiring reallocation) to a value
     * that's greater or equal to new_cap. If new_cap is greater than the
     * current capacity(), new storage is allocated, otherwise the function does
     * nothing
     *
     * @param new_cap new capacity of the vector, in number of elements
     */
    constexpr void reserve(size_type new_cap) {
        if (new_cap <= m_Capacity)
            return;

        if (new_cap > max_size())
            throw std::length_error("Reserve capacity can't be larger than "
                                    "Vector<T>::max_size()");

        ReallocVector(new_cap);
    }

    /**
     * @brief Returns the number of elements that the container has currently
     * allocated space for
     *
     * @return Current capacity
     */
    constexpr size_type capacity() const noexcept {
        return m_Capacity;
    }

    /**
     * @brief Requests the removal of unused capacity
     */
    constexpr void shrink_to_fit() {
        if (m_Capacity == m_Size)
            return;

        ReallocVector(m_Size);
    }

    /**
     * @brief Erases all elements from the container. After this call, size()
     * returns zero
     */
    constexpr void clear() noexcept {
        m_Size = 0;
    }

    /**
     * @brief Inserts elements at the specified location in the container
     *
     * @param pos iterator before which the content will be inserted. pos may be
     * the end() iterator
     * @param value element value to insert
     * @return Iterator pointing to the inserted value
     */
    constexpr iterator insert(const_iterator pos, value_type &&value) {
        size_type index = pos - begin();
        if (index > m_Size)
            throw std::out_of_range("Unable to insert into a position out of "
                                    "range of begin() to end()");

        if (m_Size == m_Capacity)
            ReallocVector(m_Size ? m_Size * 2 : 1);

        std::copy(begin() + index, end(), begin() + index + 1);
        *(m_Buffer + index) = std::move(value);

        ++m_Size;
        return begin() + index;
    }

    /**
     * @brief Inserts elements at the specified location in the container
     *
     * @param pos iterator before which the content will be inserted. pos may be
     * the end() iterator
     * @param value element value to insert
     * @return Iterator pointing to the inserted value
     */
    constexpr iterator insert(const_iterator pos, const_reference value) {
        size_type index = pos - begin();
        if (index > m_Size)
            throw std::out_of_range("Unable to insert into a position out of "
                                    "range of begin() to end()");

        if (m_Size == m_Capacity)
            ReallocVector(m_Size ? m_Size * 2 : 1);

        std::copy(begin() + index, end(), begin() + index + 1);
        *(m_Buffer + index) = value;

        ++m_Size;
        return begin() + index;
    }

    /**
     * @brief Erases the specified elements from the container
     *
     * @param pos iterator to the element to remove
     * @return Iterator following the last removed element.
     */
    constexpr iterator erase(const_iterator pos) {
        size_type index = pos - begin();
        if (index >= m_Size)
            throw std::out_of_range(
                "Unable to erase a position out of range of begin() to end()");

        std::copy(begin(), const_cast<iterator>(pos), m_Buffer);
        std::copy(const_cast<iterator>(pos) + 1, end(), m_Buffer + index);

        --m_Size;
        return begin() + index;
    }

    /**
     * @brief Appends the given element value to the end of the container.
     *
     * @param value the value of the element to append
     */
    constexpr void push_back(const_reference value) {
        if (m_Size == m_Capacity)
            reserve(m_Size ? m_Size * 2 : 1);

        m_Buffer[m_Size] = value;
        ++m_Size;
    }

    /**
     * @brief Appends the given element value to the end of the container.
     *
     * @param value the value of the element to append
     */
    constexpr void push_back(value_type &&value) {
        if (m_Size == m_Capacity)
            reserve(m_Size ? m_Size * 2 : 1);

        m_Buffer[m_Size] = std::move(value);
        ++m_Size;
    }

    /**
     * @brief Removes the last element of the container.
     * @details Iterators and references to the last element, as well as the
     * end() iterator, are invalidated.
     */
    constexpr void pop_back() {
        if (m_Size == 0)
            throw std::length_error(
                "Calling pop_back on an empty container results in UB");
        --m_Size;
    }

    /**
     * @brief Exchanges the contents of the container with those of other. Does
     * not invoke any move, copy, or swap operations on individual elements.
     * All iterators and references remain valid. The past-the-end iterator is
     * invalidated.
     *
     * @param other container to exchange the contents with
     */
    constexpr void swap(vector &other) noexcept {
        std::swap(m_Buffer, other.m_Buffer);
        std::swap(m_Size, other.m_Size);
        std::swap(m_Capacity, other.m_Capacity);
    }

    /**
     * @brief Inserts a new element into the container directly before pos.
     *
     * @param pos iterator before which the new element will be constructed
     * @param args arguments to forward to the constructor of the element
     * @return Iterator pointing to the emplaced element.
     */
    template <typename... Args>
    constexpr iterator emplace(const_iterator pos, Args &&...args) {
        return insert(pos, T(std::forward<Args>(args)...));
    }

    /**
     * @brief Appends a new element to the end of the container.
     *
     * @param args arguments to forward to the constructor of the element
     * @return Iterator pointing to the emplaced element.
     */
    template <typename... Args>
    constexpr iterator emplace_back(Args &&...args) {
        push_back(T(std::forward<Args>(args)...));
        return end() - 1;
    }

  private:
    size_type m_Size = 0;
    size_type m_Capacity = 0;
    iterator m_Buffer = nullptr;

    void ReallocVector(size_type new_capacity) {
        iterator tmp = new value_type[new_capacity];
        for (size_type i = 0; i < m_Size; ++i)
            tmp[i] = std::move(m_Buffer[i]);

        delete[] m_Buffer;
        m_Buffer = tmp;
        m_Capacity = new_capacity;
    }
};

}  // namespace s21

#endif  // S21_VECTOR_H_
