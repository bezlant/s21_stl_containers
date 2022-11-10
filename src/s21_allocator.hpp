// https://stackoverflow.com/questions/2376989/why-dont-stdvectors-elements-need-a-default-constructor
#ifndef S21_ALLOCATOR_H_
#define S21_ALLOCATOR_H_

#include <cstddef>
#include <stdexcept>

namespace s21 {
/**
 * @brief STL-like allocator implementation
 *
 * @tparam T type
 */
template <typename T>
class Allocator {
  public:
    typedef size_t size_type;

    Allocator() noexcept {
    }

    [[nodiscard]] constexpr T *allocate(size_type n) {
        if (n > size_t(~0) / sizeof(T))
            throw std::length_error("allocator<T>::allocate(size_t n) 'n' "
                                    "exceeds maximum supuported size");
        return static_cast<T *>(::operator new(n * sizeof(T)));
    }

    constexpr void deallocate(T *p, [[maybe_unused]] size_type n) noexcept {
        ::operator delete((void *)p);
    }
};
}  // namespace s21

#endif  // !S21_ALLOCATOR_H_
