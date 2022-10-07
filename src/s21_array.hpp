#ifndef S21_ARRAY_H_
#define S21_ARRAY_H_

#include <initializer_list>
#include <iostream>
#include <algorithm>

namespace s21 {

class UbException : public std::exception {
  private:
    std::string message =
        "Calling front or back on empty containers results in UB";

  public:
    const char *what() const noexcept override {
        return message.c_str();
    }
};

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
    Array() noexcept {
    }

    explicit Array(std::initializer_list<value_type> const &items) {
        if (items.size() != S)
            throw "Initializer_list's size is not the same as the array's size";

        for (size_type i = 0; i < S; ++i)
            m_Data[i] = items.begin()[i];
    }

    Array(const Array &rhs) {
        if (S != rhs.size())
            throw "Array sizes aren't equal -> can't copy";

        for (size_type i = 0; i < S; ++i)
            m_Data[i] = rhs.m_Data[i];
    }
    Array &operator=(const Array &rhs) = default;

    Array(Array &&rhs) = default;
    Array &operator=(Array &&rhs) = default;

    ~Array() = default;

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
        return this->at(index);
    }

    constexpr const_reference operator[](size_type index) const {
        return this->at(index);
    }

    constexpr reference front() {
        if (S == 0)
            throw UbException{};
        return m_Data[0];
    }

    constexpr const_reference front() const {
        if (S == 0)
            throw UbException{};
        return m_Data[0];
    }

    constexpr reference back() {
        if (S == 0)
            throw UbException{};
        return m_Data[S - 1];
    }

    constexpr const_reference back() const {
        if (S == 0)
            throw UbException{};
        return m_Data[S - 1];
    }

    constexpr iterator data() noexcept {
        return m_Data;
    }

    constexpr const T *data() const noexcept {
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
        return begin() != end();
    }

    constexpr size_type max_size() const noexcept {
        return S;
    }

    // Modifiers
  public:
    constexpr void swap(Array &other) noexcept {
        Array<T, S> tmp = *this;
        *this = other;
        other = tmp;
    }

    constexpr void fill(const_reference value) {
        for (auto *it = begin(); it != end(); it++)
            *it = value;
    }

  private:
    value_type m_Data[S] = {};
};

}  // namespace s21

#endif  // S21_ARRAY_H_
