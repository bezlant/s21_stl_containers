
#ifndef S21_VECTOR_H_
#define S21_VECTOR_H_

#include <initializer_list>
#include <algorithm>
#include "s21_exceptions.hpp"

namespace s21 {

template <typename T>
class Vector {
  public:
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using iterator = T *;
    using const_iterator = const T *;
    using size_type = std::size_t;

    // Member functions
  public:
    Vector() : m_Size{0}, m_Buffer{nullptr} {
    }

    explicit Vector(size_type size) {
        m_Size = size;
        m_Buffer = nullptr;
        if (m_Size > 0) {
            m_Buffer = new T[m_Size];
        }
    }

    Vector(std::initializer_list<value_type> const &init)
        : m_Size{init.size()}, m_Buffer{new T[init.size()]} {
        std::copy(init.begin(), init.end(), m_Buffer);
    }

    Vector(const Vector &rhs) {
        m_Size = rhs.m_Size;
        m_Buffer = nullptr;
        if (m_Size > 0) {
            m_Buffer = new T[m_Size];
        }
        std::copy(rhs.begin(), rhs.end(), m_Buffer);
    }

    Vector(Vector &&rhs) noexcept {
        m_Size = std::exchange(rhs.m_Size, 0);
        m_Buffer = std::exchange(rhs.m_Buffer, nullptr);
    }

    ~Vector() {
        delete[] m_Buffer;
    }

    Vector &operator=(Vector &&rhs) {
        if (*this == rhs)
            return *this;

        m_Size = std::exchange(rhs.m_Size, 0);
        m_Buffer = std::exchange(rhs.m_Buffer, nullptr);

        return *this;
    }
    // Element Access
  public:
    reference operator[](size_type pos) {
        if (pos >= m_Size)
            throw std::out_of_range(
                "Accessing the vector with []. The index is out of range");

        return m_Buffer[pos];
    }
    // Capacity
  public:
    size_type size() const noexcept {
        return m_Size;
    }

  private:
    size_t m_Size;
    T *m_Buffer;
};

}  // namespace s21

#endif  // S21_VECTOR_H_
