#ifndef S21_VECTOR_H_
#define S21_VECTOR_H_

#include <initializer_list>

template <typename T> class Vector {
  private:
    std::size_t m_size;
    std::size_t m_capacity;
    T *ptr;
};

#endif  // S21_VECTOR_H_
