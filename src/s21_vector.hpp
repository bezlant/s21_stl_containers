#ifndef S21_VECTOR_H_
#define S21_VECTOR_H_

#include <initializer_list>
#include <algorithm>
#include "s21_exceptions.hpp"

namespace s21 {

const std::string errOutOfRange =
    "Accessing the vector with []. The index is out of range";

template <typename T>
class Vector {
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
    Vector() : m_Size{0}, m_Capacity(0), m_Buffer{nullptr} {
    }

    explicit Vector(size_type size) {
        m_Size = size;
        m_Capacity = size;
        m_Buffer = nullptr;
        if (size > 0) {
            m_Buffer = new value_type[m_Size];
        }
    }

    explicit Vector(std::initializer_list<value_type> const &init)
        : m_Size{init.size()},
          m_Capacity(init.size()), m_Buffer{new value_type[init.size()]} {
        std::copy(init.begin(), init.end(), m_Buffer);
    }

    Vector(const Vector &rhs) {
        m_Size = rhs.m_Size;
        m_Capacity = rhs.m_Capacity;
        m_Buffer = nullptr;
        if (m_Size > 0) {
            m_Buffer = new value_type[m_Size];
        }
        std::copy(rhs.begin(), rhs.end(), m_Buffer);
    }

    Vector(Vector &&rhs) noexcept {
        m_Size = std::exchange(rhs.m_Size, 0);
        m_Capacity = std::exchange(rhs.m_Capacity, 0);
        m_Buffer = std::exchange(rhs.m_Buffer, nullptr);
    }

    ~Vector() {
        delete[] m_Buffer;
    }

    Vector &operator=(Vector &&rhs) {
        if (this == &rhs)
            return *this;

        m_Size = std::exchange(rhs.m_Size, 0);
        m_Capacity = std::exchange(rhs.m_Capacity, 0);
        m_Buffer = std::exchange(rhs.m_Buffer, nullptr);

        return *this;
    }
    // Element Access
  public:
    constexpr reference at(size_type pos) {
        if (pos >= m_Size)
            throw std::out_of_range(errOutOfRange);

        return m_Buffer[pos];
    }

    constexpr const_reference at(size_type pos) const {
        if (pos >= m_Size)
            throw std::out_of_range(errOutOfRange);

        return m_Buffer[pos];
    }

    constexpr reference operator[](size_type pos) {
        if (pos >= m_Size)
            throw std::out_of_range(errOutOfRange);

        return m_Buffer[pos];
    }

    constexpr const_reference operator[](size_type pos) const {
        if (pos >= m_Size)
            throw std::out_of_range(errOutOfRange);

        return m_Buffer[pos];
    }

    constexpr reference front() {
        if (m_Size == 0)
            throw ZeroSizeException{};
        return *begin();
    }

    constexpr const_reference front() const {
        if (m_Size == 0)
            throw ZeroSizeException{};
        return *begin();
    }

    constexpr reference back() {
        if (m_Size == 0)
            throw ZeroSizeException{};
        return *std::prev(end());
    }

    constexpr const_reference back() const {
        if (m_Size == 0)
            throw ZeroSizeException{};
        return *std::prev(end());
    }

    constexpr iterator data() noexcept {
        return m_Buffer;
    }

    constexpr const_iterator data() const noexcept {
        return m_Buffer;
    }

    // Iterators
    constexpr iterator begin() noexcept {
        return m_Buffer;
    }

    constexpr const_iterator begin() const noexcept {
        return m_Buffer;
    }

    constexpr iterator end() noexcept {
        return m_Buffer + m_Size;
    }

    constexpr const_iterator end() const noexcept {
        return m_Buffer + m_Size;
    }

    // Capacity
  public:
    [[nodiscard]] bool empty() const noexcept {
        return begin() == end();
    }

    constexpr size_type size() const noexcept {
        return m_Size;
    }

    constexpr size_type max_size() const noexcept {
        return std::numeric_limits<difference_type>::max();
    }

    constexpr void reserve(size_type new_cap) {
        if (new_cap <= m_Capacity)
            return;

        if (new_cap > max_size())
            throw std::length_error("Reserve capacity can't be larger than "
                                    "Vector<T>::max_size()");

        m_Capacity = new_cap;
        ReallocVector(new_cap);
    }

    constexpr size_type capacity() const noexcept {
        return m_Capacity;
    }

    constexpr void shrink_to_fit() {
        if (m_Capacity == m_Size)
            return;

        ReallocVector(m_Size);
    }

    constexpr void clear() noexcept {
        m_Size = 0;
    }

    constexpr iterator insert(iterator pos, const_reference value) {
        if (pos - begin() > end() - begin())
            throw "Unable to insert into a position out of range of begin() to "
                  "end()";

        size_type new_size = size() + 1;
        size_type index = pos - begin();

        if (new_size > capacity()) {
            m_Capacity = m_Size * 2;
            iterator tmp = new value_type[m_Capacity];
            std::copy(begin(), pos, tmp);

            *(tmp + index) = value;

            std::copy(pos, end(), tmp + index + 1);
            delete[] m_Buffer;

            m_Buffer = tmp;
        } else {
            std::copy(begin() + index, end(), begin() + index + 1);
            *(begin() + index) = value;
        }

        m_Size = new_size;
        return begin() + index;
    }

  private:
    size_type m_Size;
    size_type m_Capacity;
    iterator m_Buffer;

    void ReallocVector(size_type new_size) {
        iterator tmp = new value_type[new_size];
        std::copy(begin(), end(), tmp);
        delete[] m_Buffer;
        m_Buffer = tmp;
    }
};

}  // namespace s21

#endif  // S21_VECTOR_H_
