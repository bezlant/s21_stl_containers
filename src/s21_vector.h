#ifndef S21_CONTAINERS_S21_CONTAINERS_S21_VECTOR_H_
#define S21_CONTAINERS_S21_CONTAINERS_S21_VECTOR_H_

#include <algorithm>
#include <initializer_list>
#include <limits>
#include <utility>

namespace s21 {

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
        size_ = size;
        capacity_ = size;
        buffer_ = nullptr;
        if (size > 0) {
            buffer_ = new value_type[capacity_];
        }
    }

    /**
     * @brief initializer_list constructor
     *
     * @param init Elements an to initialize the vector with
     */
    explicit vector(std::initializer_list<value_type> const &init)
        : size_{init.size()},
          capacity_(init.size()), buffer_{new value_type[capacity_]} {
        std::copy(init.begin(), init.end(), buffer_);
    }

    /**
     * @brief Copy constructor - copies all values from the rhs
     *
     * @param rhs Object to copy from
     */
    vector(const vector &rhs) {
        size_ = rhs.size_;
        capacity_ = rhs.capacity_;
        buffer_ = nullptr;
        if (size_ > 0) {
            buffer_ = new value_type[capacity_];
        }
        std::copy(rhs.begin(), rhs.end(), buffer_);
    }

    /**
     * @brief Move constructor - steals all the resources from the given object
     *
     * @param rhs Object to steal resources from
     */
    vector(vector &&rhs) noexcept {
        size_ = std::exchange(rhs.size_, 0);
        capacity_ = std::exchange(rhs.capacity_, 0);
        buffer_ = std::exchange(rhs.buffer_, nullptr);
    }

    /**
     * @brief Destructor - cleans up the memory used
     */
    ~vector() {
        delete[] buffer_;
    }

    /**
     * @brief Move assignment - steals all the resources from the given object
     *
     * @param rhs Objects to steal resources from
     * @return Results of the move assignment
     */
    constexpr vector &operator=(vector &&rhs) noexcept {
        if (this != &rhs) {
            size_ = std::exchange(rhs.size_, 0);
            capacity_ = std::exchange(rhs.capacity_, 0);
            buffer_ = std::exchange(rhs.buffer_, nullptr);
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
            delete[] buffer_;

            if (rhs.size_ > 0) {
                buffer_ = new value_type[rhs.capacity_];
                std::copy(rhs.begin(), rhs.end(), buffer_);
            }
            size_ = rhs.size_;
            capacity_ = rhs.capacity_;
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
        if (pos >= size_)
            throw std::out_of_range(
                "s21::vector::at The index is out of range");

        return buffer_[pos];
    }

    /**
     * @brief Safe access to the elements of the container
     *
     * @param pos Index of the element to access
     * @return The element of the vector at the given index
     */
    constexpr const_reference at(size_type pos) const {
        if (pos >= size_)
            throw std::out_of_range(
                "s21::vector::at The index is out of range");

        return buffer_[pos];
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
        if (size_ == 0)
            throw std::out_of_range("s21::vector::front Using methods on a "
                                    "zero sized container results "
                                    "in the UB");
        return *begin();
    }

    /**
     * @brief Safe access to the first element of the container
     *
     * @return The first element of the container
     */
    constexpr const_reference front() const {
        if (size_ == 0)
            throw std::out_of_range("s21::vector::front Using methods on a "
                                    "zero sized container results "
                                    "in the UB");
        return *begin();
    }

    /**
     * @brief Safe access to the last element of the container
     *
     * @return The last element of the container
     */
    constexpr reference back() {
        if (size_ == 0)
            throw std::out_of_range("s21::vector::back Using methods on a zero "
                                    "sized container results "
                                    "in the UB");
        return *std::prev(end());
    }

    /**
     * @brief Safe access to the last element of the container
     *
     * @return The last element of the container
     */
    constexpr const_reference back() const {
        if (size_ == 0)
            throw std::out_of_range("s21::vector::back Using methods on a zero "
                                    "sized container results "
                                    "in the UB");
        return *std::prev(end());
    }

    /**
     * @brief Access to the underlying pointer to the memory we allocated for
     * the vector
     *
     * @return Pointer to the first element of the vector
     */
    constexpr iterator data() noexcept {
        return buffer_;
    }

    /**
     * @brief Access to the underlying pointer to the memory we allocated for
     * the vector
     *
     * @return Pointer to the first element of the vector
     */
    constexpr const_iterator data() const noexcept {
        return buffer_;
    }

    // Iterators
    /**
     * @brief Access to the iterator pointing to the first element of the
     * container
     *
     * @return Pointer to the first element of the vector
     */
    constexpr iterator begin() noexcept {
        return buffer_;
    }

    /**
     * @brief Access to the iterator pointing to the first element of the
     * container
     *
     * @return Pointer to the first element of the vector
     */
    constexpr const_iterator begin() const noexcept {
        return buffer_;
    }

    /**
     * @brief Access to the iterator pointing to the last element of the
     * container
     *
     * @return Pointer to the last element of the vector
     */
    constexpr iterator end() noexcept {
        return buffer_ + size_;
    }

    /**
     * @brief Access to the iterator pointing to the last element of the
     * container
     *
     * @return Pointer to the last element of the vector
     */
    constexpr const_iterator end() const noexcept {
        return buffer_ + size_;
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
    [[nodiscard]] constexpr size_type size() const noexcept {
        return std::distance(begin(), end());
    }

    /**
     * @brief Returns the maximum number of elements the container is able to
     * hold due to system or library implementation limitations, i.e.
     * std::distance(begin(), end()) for the largest container
     *
     * @return Maximum capacity
     */
    [[nodiscard]] constexpr size_type max_size() const noexcept {
        return std::numeric_limits<size_type>::max() / sizeof(value_type) / 2;
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
        if (new_cap <= capacity_)
            return;

        if (new_cap > max_size())
            throw std::length_error(
                "s21::vector::reserve Reserve capacity can't be larger than "
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
        return capacity_;
    }

    /**
     * @brief Requests the removal of unused capacity
     */
    constexpr void shrink_to_fit() {
        if (capacity_ == size_)
            return;

        ReallocVector(size_);
    }

    /**
     * @brief Erases all elements from the container. After this call, size()
     * returns zero
     */
    constexpr void clear() noexcept {
        size_ = 0;
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
        if (index > size_)
            throw std::out_of_range(
                "s21::vector::insert Unable to insert into a position out of "
                "range of begin() to end()");

        if (size_ == capacity_)
            ReallocVector(size_ ? size_ * 2 : 1);

        std::copy(begin() + index, end(), begin() + index + 1);
        *(buffer_ + index) = std::move(value);

        ++size_;
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
        if (index > size_)
            throw std::out_of_range(
                "s21::vector::insert Unable to insert into a position out of "
                "range of begin() to end()");

        if (size_ == capacity_)
            ReallocVector(size_ ? size_ * 2 : 1);

        std::copy(begin() + index, end(), begin() + index + 1);
        *(buffer_ + index) = value;

        ++size_;
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
        if (index >= size_)
            throw std::out_of_range(
                "s21::vector::erase Unable to erase a position out of range of "
                "begin() to end()");

        std::copy(begin(), const_cast<iterator>(pos), buffer_);
        std::copy(const_cast<iterator>(pos) + 1, end(), buffer_ + index);

        --size_;
        return begin() + index;
    }

    /**
     * @brief Appends the given element value to the end of the container.
     *
     * @param value the value of the element to append
     */
    constexpr void push_back(const_reference value) {
        if (size_ == capacity_)
            reserve(size_ ? size_ * 2 : 1);

        buffer_[size_] = value;
        ++size_;
    }

    /**
     * @brief Appends the given element value to the end of the container.
     *
     * @param value the value of the element to append
     */
    constexpr void push_back(value_type &&value) {
        if (size_ == capacity_)
            reserve(size_ ? size_ * 2 : 1);

        buffer_[size_] = std::move(value);
        ++size_;
    }

    /**
     * @brief Removes the last element of the container.
     * @details Iterators and references to the last element, as well as the
     * end() iterator, are invalidated.
     */
    constexpr void pop_back() {
        if (size_ == 0)
            throw std::length_error(
                "s21::vector::pop_back Calling pop_back on an empty container "
                "results in UB");
        --size_;
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
        std::swap(buffer_, other.buffer_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
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
        iterator ret = nullptr;
        auto id = pos - begin();
        reserve(capacity_ + sizeof...(args));

        for (auto &&item : {std::forward<Args>(args)...})
            ret = insert(begin() + id, item);

        return ret;
    }

    /**
     * @brief Appends a new element to the end of the container.
     *
     * @param args arguments to forward to the constructor of the element
     * @return Iterator pointing to the emplaced element.
     */
    template <typename... Args>
    constexpr iterator emplace_back(Args &&...args) {
        for (auto &&item : {std::forward<Args>(args)...}) {
            push_back(item);
        }
        return end() - 1;
    }

  private:
    size_type size_ = 0;
    size_type capacity_ = 0;
    iterator buffer_ = nullptr;

    void ReallocVector(size_type new_capacity) {
        iterator tmp = new value_type[new_capacity];
        for (size_type i = 0; i < size_; ++i)
            tmp[i] = std::move(buffer_[i]);

        delete[] buffer_;
        buffer_ = tmp;
        capacity_ = new_capacity;
    }
};

}  // namespace s21

#endif  // S21_CONTAINERS_S21_CONTAINERS_S21_VECTOR_H_
