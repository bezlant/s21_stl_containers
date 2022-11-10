#ifndef S21_VECTOR_H_
#define S21_VECTOR_H_

#include <initializer_list>
#include <algorithm>
#include <vector>
#include "s21_exceptions.hpp"
#include "s21_allocator.hpp"

namespace s21 {

const std::string errOutOfRange =
    "Accessing the vector with []. The index is out of range";

template <typename T, class Allocator = s21::Allocator<T>>
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
    Vector() = default;

    explicit Vector(size_type size) {
        m_Size = size;
        m_Capacity = size;
        m_Buffer = nullptr;
        if (size > 0) {
            m_Buffer = alloc.allocate(m_Size);
        }
    }

    explicit Vector(std::initializer_list<value_type> const &init)
        : m_Size{init.size()},
          m_Capacity(init.size()), m_Buffer{alloc.allocate(m_Size)} {

        std::copy(init.begin(), init.end(), m_Buffer);
    }

    Vector(const Vector &rhs) {
        m_Size = rhs.m_Size;
        m_Capacity = rhs.m_Capacity;
        m_Buffer = nullptr;
        if (m_Size > 0) {
            m_Buffer = alloc.allocate(m_Size);
        }
        std::copy(rhs.begin(), rhs.end(), m_Buffer);
    }

    Vector(Vector &&rhs) noexcept {
        m_Size = std::exchange(rhs.m_Size, 0);
        m_Capacity = std::exchange(rhs.m_Capacity, 0);
        m_Buffer = std::exchange(rhs.m_Buffer, nullptr);
    }

    ~Vector() {
        alloc.deallocate(m_Buffer, m_Capacity);
    }

    constexpr Vector &operator=(Vector &&rhs) {
        if (this != &rhs) {
            m_Size = std::exchange(rhs.m_Size, 0);
            m_Capacity = std::exchange(rhs.m_Capacity, 0);
            m_Buffer = std::exchange(rhs.m_Buffer, nullptr);
        }

        return *this;
    }

    constexpr Vector &operator=(const Vector &rhs) {
        if (this != &rhs) {
            alloc.deallocate(m_Buffer, m_Capacity);
            if (rhs.m_Size > 0) {
                m_Buffer = alloc.allocate(m_Size);
                std::copy(rhs.begin(), rhs.end(), m_Buffer);
            }
            m_Size = rhs.m_Size;
            m_Capacity = rhs.m_Capacity;
        }

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
        return at(pos);
    }

    constexpr const_reference operator[](size_type pos) const {
        return at(pos);
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
        return std::distance(begin(), end());
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
            throw std::out_of_range("Unable to insert into a position out of "
                                    "range of begin() to end()");

        size_type new_size = size() + 1;
        size_type index = pos - begin();

        if (new_size > capacity()) {
            m_Capacity = m_Size == 0 ? 1 : m_Size * 2;
            iterator tmp = alloc.allocate(m_Size);
            std::copy(begin(), pos, tmp);

            *(tmp + index) = value;

            std::copy(pos, end(), tmp + index + 1);
            alloc.deallocate(m_Buffer, m_Capacity);
            m_Buffer = tmp;
        } else {
            std::copy(begin() + index, end(), begin() + index + 1);
            *(begin() + index) = value;
        }

        m_Size = new_size;
        return begin() + index;
    }

    constexpr iterator erase(iterator pos) {
        if (pos - begin() >= end() - begin())
            throw std::out_of_range(
                "Unable to erase a position out of range of begin() to end()");
        auto removed_index = pos - begin();

        std::copy(begin(), pos, m_Buffer);
        std::copy(pos + 1, end(), m_Buffer + removed_index);

        --m_Size;
        return begin() + removed_index;
    }

    constexpr void push_back(const_reference value) {
        if (size() + 1 > capacity())
            ReallocVector(m_Size == 0 ? 1 : m_Size * 2);

        m_Buffer[m_Size] = value;
        ++m_Size;
    }

    constexpr void push_back(value_type &&value) {
        if (size() + 1 > capacity())
            ReallocVector(m_Size == 0 ? 1 : m_Size * 2);

        m_Buffer[m_Size] = std::move(value);
        ++m_Size;
    }

    constexpr void pop_back() {
        if (m_Size == 0)
            throw std::length_error(
                "Calling pop_back on an empty container results in UB");
        --m_Size;
    }

    constexpr void swap(Vector &other) noexcept {
        iterator tmp_buffer = m_Buffer;
        size_type tmp_size = m_Size;
        size_type tmp_capacity = m_Capacity;

        m_Buffer = other.m_Buffer;
        other.m_Buffer = tmp_buffer;

        m_Size = other.m_Size;
        other.m_Size = tmp_size;

        m_Capacity = other.m_Capacity;
        other.m_Capacity = tmp_capacity;
    }

    template <typename... Args>
    constexpr iterator emplace(const_iterator pos, Args &&...args) {
        return insert(pos, T(std::forward<Args>(args)...));
    }

    template <typename... Args>
    constexpr iterator emplace_back(Args &&...args) {
        push_back(T(std::forward<Args>(args)...));
        return end() - 1;
    }

  private:
    Allocator alloc;
    size_type m_Size = 0;
    size_type m_Capacity = 0;
    iterator m_Buffer = nullptr;

    void ReallocVector(size_type new_size) {
        iterator tmp = alloc.allocate(new_size);

        std::size_t i = 0;
        for (auto first1 = begin(), first2 = tmp; i < m_Size;
             ++first1, ++first2, ++i) {
            *first2 = std::move(*first1);
        }

        alloc.deallocate(m_Buffer, m_Size);
        m_Buffer = tmp;
        m_Capacity = new_size;
    }
};

}  // namespace s21

#endif  // S21_VECTOR_H_
