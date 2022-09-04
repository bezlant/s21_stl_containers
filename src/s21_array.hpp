#ifndef S21_ARRAY_H_
#define S21_ARRAY_H_

#include <initializer_list>

template <typename T, std::size_t S> class Array {
  public:
    constexpr std::size_t size() const {
        return S;
    }

    T &operator[](std::size_t index) {
        return m_Data[index];
    }

    const T &operator[](std::size_t index) const {
        return m_Data[index];
    }

    T *data() {
        return m_Data;
    }

    const T *data() const {
        return m_Data;
    }

  private:
    T m_Data[S];
};

#endif  // S21_ARRAY_H_
