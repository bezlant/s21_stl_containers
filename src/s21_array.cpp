#include "s21_array.hpp"

namespace s21 {
template <typename T, std::size_t S>
Array<T, S>::Array(std::initializer_list<T> const &items) {

    std::copy(items.begin(), items.end(), m_Data);
};

template <typename T, std::size_t S>
Array<T, S>::Array() {
}

template <typename T, std::size_t S>
Array<T, S>::Array(const Array &rhs) {
}

template <typename T, std::size_t S>
Array<T, S>::Array(Array &&rhs) {
}

template <typename T, std::size_t S>
Array<T, S>::~Array() {
}

template <typename T, std::size_t S>
Array<T, S> &Array<T, S>::operator=(Array<T, S> &&rhs) {
    return *this;
}
}  // namespace s21
