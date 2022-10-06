#ifndef S21_ARRAY_H_
#define S21_ARRAY_H_

#include <initializer_list>
#include <iostream>
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

  public:
    Array() {
    }

    explicit Array(std::initializer_list<value_type> const &items) {
        if (items.size() != S)
            throw "Initializer_list's size is not the same as the array's size";

        for (std::size_t i = 0; i < S; ++i)
            m_Data[i] = items[i];
    }

    Array(const Array &rhs) {
        if (S != rhs.size())
            throw "Array sizes aren't equal -> can't copy";

        for (size_type i = 0; i < S; ++i)
            m_Data[i] = rhs.m_Data[i];
    }

    Array(Array &&rhs) = delete;

    ~Array();

    Array &operator=(Array &&rhs) = delete;

  public:
    constexpr size_type size() const {
        return S;
    }

    reference operator[](size_type index) {
        return m_Data[index];
    }

    const_reference operator[](size_type index) const {
        return m_Data[index];
    }

    iterator data() {
        return m_Data;
    }

    const_iterator data() const {

        return m_Data;
    }

  private:
    value_type m_Data[S];
};

}  // namespace s21

#endif  // S21_ARRAY_H_
