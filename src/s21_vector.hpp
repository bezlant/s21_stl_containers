#ifndef S21_VECTOR_H_
#define S21_VECTOR_H_

#include <initializer_list>

template <typename T> class Vector {
  private:
    size_t m_size;
    size_t m_capacity;
    T *ptr;
};

#endif  // S21_VECTOR_H_
