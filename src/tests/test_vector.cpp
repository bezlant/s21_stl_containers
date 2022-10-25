#include "../s21_containers.hpp"
#include "gtest/gtest.h"

TEST(vector, initializer_list_constructor) {
    s21::Vector<int> arr{1, 2, 3, 4, 5};

    for (std::size_t i = 0; i < arr.size(); ++i)
        ASSERT_EQ(arr[i], i + 1);
}

TEST(vector, copy_constructor) {
    s21::Vector<int> got{1, 2, 3, 4, 5};
    s21::Vector<int> want{got};

    for (std::size_t i = 0; i < got.size(); ++i)
        ASSERT_EQ(got[i], want[i]);
}
