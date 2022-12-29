#ifndef S21_CONTAINERS_S21_CONTAINERS_S21_ARRAY_H_
#define S21_CONTAINERS_S21_CONTAINERS_S21_ARRAY_H_

#include <algorithm>
#include <initializer_list>

namespace s21 {

/**
 * @brief s21::array - STL like std::array implementation
 *
 * @tparam T containers type
 * @tparam S size of the container
 */
template <typename T, std::size_t S>
class array {
  public:
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using iterator = T *;
    using const_iterator = const T *;
    using size_type = std::size_t;

    // Member functions
  public:
    /**
     * @brief Default constructor doesn't assign any fields because all the
     * fields are default initialized
     */
    array() noexcept = default;

    /**
     * @brief initializer_list constructor
     *
     * @param init Elements an to initialize the array with
     */
    explicit array(std::initializer_list<value_type> const &items) {
        if (items.size() != S)
            throw std::runtime_error(
                "s21::array::array(std::initializer_list<value_type> const "
                "&items) "
                "Initializer_list's size is not the same as the array's size");

        for (size_type i = 0; i < S; ++i)
            data_[i] = items.begin()[i];
    }

    /**
     * @brief Copy constructor - copies all values from the rhs
     *
     * @param rhs Object to copy from
     */
    array(const array &rhs) noexcept {
        for (size_type i = 0; i < S; ++i)
            data_[i] = rhs.data_[i];
    }

    /**
     * @brief Copy assignment - copies all the elements from the given object
     *
     * @param rhs Objects to copy elements from
     * @return Results of the copy assignment
     */
    array &operator=(const array &rhs) noexcept {
        for (size_type i = 0; i < S; ++i)
            data_[i] = rhs.data_[i];
        return *this;
    }

    /**
     * @brief Move constructor - steals all the resources from the given object
     *
     * @details The default move constructor for a (non-union) class performs a
     * member-wise move
     * @param rhs Object to steal resources from
     */
    array(array &&rhs) {
        if (this != &rhs) {
            for (size_type i = 0; i < S; ++i)
                data_[i] = std::move(rhs.data_[i]);
        }
    }

    /**
     * @brief Move assignment - steals all the resources from the given object
     *
     * @details The default move constructor for a (non-union) class performs a
     * member-wise move
     * @param rhs Objects to steal resources from
     * @return Results of the move assignment
     */
    array &operator=(array &&rhs) {
        if (this != &rhs) {
            for (size_type i = 0; i < S; ++i)
                data_[i] = std::move(rhs.data_[i]);
        }
        return *this;
    }

    /**
     * @brief Empty constructor since the underlying array is formed on the
     * stack
     */
    ~array() noexcept {
    }

    // Element access
  public:
    /**
     * @brief Safe access to the elements of the container
     *
     * @param pos Index of the element to access
     * @return The element of the array at the given index
     */
    reference at(size_type index) {
        if (index >= S)
            throw std::out_of_range("s21::array::at The index is out of range");

        return data_[index];
    }

    /**
     * @brief Safe access to the elements of the container
     *
     * @param pos Index of the element to access
     * @return The element of the array at the given index
     */
    constexpr const_reference at(size_type index) const {
        if (index >= S)
            throw std::out_of_range("s21::array::at The index is out of range");

        return data_[index];
    }

    /**
     * @brief Safe access to the elements of the container
     *
     * @param pos Index of the element to access
     * @return The element of the array at the given index
     */
    constexpr reference operator[](size_type index) {
        return at(index);
    }

    /**
     * @brief Safe access to the elements of the container
     *
     * @param pos Index of the element to access
     * @return The element of the array at the given index
     */
    constexpr const_reference operator[](size_type index) const {
        return at(index);
    }

    /**
     * @brief Safe access to the first element of the container
     *
     * @return The first element of the container
     */
    constexpr reference front() {
        if (S == 0)
            throw std::out_of_range("s21::array::front Using methods on a zero "
                                    "sized container results "
                                    "in the UB");
        return data_[0];
    }

    /**
     * @brief Safe access to the first element of the container
     *
     * @return The first element of the container
     */
    constexpr const_reference front() const {
        if (S == 0)
            throw std::out_of_range("s21::array::front Using methods on a zero "
                                    "sized container results "
                                    "in the UB");
        return data_[0];
    }

    /**
     * @brief Safe access to the last element of the container
     *
     * @return The last element of the container
     */
    constexpr reference back() {
        if (S == 0)
            throw std::out_of_range("s21::array::front Using methods on a zero "
                                    "sized container results "
                                    "in the UB");
        return data_[S - 1];
    }

    /**
     * @brief Safe access to the last element of the container
     *
     * @return The last element of the container
     */
    constexpr const_reference back() const {
        if (S == 0)
            throw std::out_of_range("s21::array::front Using methods on a zero "
                                    "sized container results "
                                    "in the UB");
        return data_[S - 1];
    }

    /**
     * @brief Access to the underlying pointer to the memory where the array is
     * stored
     *
     * @return Pointer to the first element of the array
     */
    constexpr iterator data() noexcept {
        return data_;
    }

    /**
     * @brief Access to the underlying pointer to the memory where the array is
     * stored
     *
     * @return Pointer to the first element of the array
     */
    constexpr const_iterator data() const noexcept {
        return data_;
    }
    // Iterators
  public:
    /**
     * @brief Access to the iterator pointing to the first element of the
     * container
     *
     * @return Pointer to the first element of the array
     */
    constexpr iterator begin() noexcept {
        return data_;
    }

    constexpr const_iterator begin() const noexcept {
        return data_;
    }

    /**
     * @brief Access to the iterator pointing to the last element of the
     * container
     *
     * @return Pointer to the last element of the vector
     */
    constexpr iterator end() noexcept {
        return data_ + S;
    }

    /**
     * @brief Access to the iterator pointing to the last element of the
     * container
     *
     * @return Pointer to the last element of the vector
     */
    constexpr const_iterator end() const noexcept {
        return data_ + S;
    }

    // Capacity
  public:
    /**
     * @brief Current size of the container (std::distance(begin(), end())
     *
     * @return Size of the container
     */
    [[nodiscard]] constexpr size_type size() const noexcept {
        return std::distance(begin(), end());
    }

    /**
     * @brief Checks if the container is empty
     *
     * @return True if empty, otherwise false
     */
    [[nodiscard]] constexpr bool empty() const noexcept {
        return begin() == end();
    }

    /**
     * @brief Returns the maximum number of elements the container is able to
     * hold due to system or library implementation limitations, i.e.
     * std::distance(begin(), end()) for the largest container.
     *
     * @return Maximum number of elements
     */
    [[nodiscard]] constexpr size_type max_size() const noexcept {
        return std::distance(begin(), end());
    }

    // Modifiers
  public:
    /**
     * @brief Exchanges the contents of the container with those of other. Does
     * not cause iterators and references to associate with the other container.
     *
     * @param other container to exchange the contents with
     */
    constexpr void swap(array &other) noexcept {
        for (auto first1 = begin(), last1 = end(), first2 = other.begin();
             first1 != last1; ++first1, ++first2) {
            T tmp = std::move(*first1);
            *first1 = std::move(*first2);
            *first2 = std::move(tmp);
        }
    }

    /**
     * @brief Assigns the value to all elements in the container.
     *
     * @param value Value to assign ot all the elemnts of the container
     */
    void fill(const_reference value) {
        for (auto *itBegin = begin(), *itEnd = end(); itBegin != itEnd;
             ++itBegin)
            *itBegin = value;
    }

  private:
    value_type data_[S] = {};
};

}  // namespace s21

#endif  // S21_CONTAINERS_S21_CONTAINERS_S21_ARRAY_H_
