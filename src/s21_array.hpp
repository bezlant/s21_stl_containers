#ifndef S21_ARRAY_H_
#define S21_ARRAY_H_

#include "s21_exceptions.hpp"
#include <initializer_list>
#include <algorithm>

namespace s21 {

template <typename T, std::size_t S>
class Array {
  public:
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using iterator = T *;
    using const_iterator = const T *;
    using size_type = std::size_t;

    // Member functions
  public:
    Array() noexcept = default;

    explicit Array(std::initializer_list<value_type> const &items) {
        if (items.size() != S)
            throw "Initializer_list's size is not the same as the array's size";

        for (size_type i = 0; i < S; ++i)
            m_Data[i] = items.begin()[i];
    }

    // Default works as intented and arrays of different sizes won't compile.
    Array(const Array &rhs) noexcept = default;
    Array &operator=(const Array &rhs) = default;
    Array(Array &&rhs) = default;
    Array &operator=(Array &&rhs) = default;
    ~Array() noexcept = default;

    // Element access
  public:
    reference at(size_type index) {
        if (index >= S)
            throw std::out_of_range("The index is out of range");

        return m_Data[index];
    }

    constexpr const_reference at(size_type index) const {
        if (index >= S)
            throw std::out_of_range("The index is out of range");

        return m_Data[index];
    }

    constexpr reference operator[](size_type index) {
        return at(index);
    }

    constexpr const_reference operator[](size_type index) const {
        return at(index);
    }

    constexpr reference front() {
        if (S == 0)
            throw ZeroSizeException{};
        return m_Data[0];
    }

    constexpr const_reference front() const {
        if (S == 0)
            throw ZeroSizeException{};
        return m_Data[0];
    }

    constexpr reference back() {
        if (S == 0)
            throw ZeroSizeException{};
        return m_Data[S - 1];
    }

    constexpr const_reference back() const {
        if (S == 0)
            throw ZeroSizeException{};
        return m_Data[S - 1];
    }

    constexpr iterator data() noexcept {
        return m_Data;
    }

    constexpr const_iterator data() const noexcept {
        return m_Data;
    }
    // Iterators
  public:
    constexpr iterator begin() noexcept {
        return m_Data;
    }

    constexpr const_iterator begin() const noexcept {
        return m_Data;
    }

    constexpr iterator end() noexcept {
        return m_Data + S;
    }

    constexpr const_iterator end() const noexcept {
        return m_Data + S;
    }

    // Capacity
  public:
    constexpr size_type size() const noexcept {
        return S;
    }

    [[nodiscard]] constexpr bool empty() const noexcept {
        return begin() == end();
    }

    constexpr size_type max_size() const noexcept {
        return std::distance(begin(), end());
    }

    // Modifiers
  public:
    constexpr void swap(Array &other) noexcept {
        for (auto first1 = begin(), last1 = end(), first2 = other.begin();
             first1 != last1; ++first1, ++first2) {
            T tmp = std::move(*first1);
            *first1 = std::move(*first2);
            *first2 = std::move(tmp);
        }
    }

    void fill(const_reference value) {
        for (auto *it = begin(); it != end(); it++)
            *it = value;
    }

  private:
    value_type m_Data[S] = {};
};

}  // namespace s21

#endif  // S21_ARRAY_H_
