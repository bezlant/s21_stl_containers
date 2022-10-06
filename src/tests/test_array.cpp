#include "../s21_containers.hpp"
#include "gtest/gtest.h"

TEST(array, initializer_list_constructor) {
    s21::Array<int, 5> arr{1, 2, 3, 4, 5};

    for (std::size_t i = 0; i < arr.size(); ++i)
        ASSERT_EQ(arr[i], i + 1);
}

TEST(array, copy_constructor) {
    s21::Array<int, 5> arr{1, 2, 3, 4, 5};
    s21::Array<int, 5> arr1(arr);

    for (std::size_t i = 0; i < arr.size(); ++i)
        ASSERT_EQ(arr[i], arr1[i]);
}

TEST(array, back) {
    s21::Array<int, 5> arr{1, 2, 3, 4, 5};

    ASSERT_EQ(arr.back(), 5);
    ASSERT_EQ(*(arr.end() - 1), 5);
}

TEST(array, front) {
    s21::Array<int, 5> arr{1, 2, 3, 4, 5};

    ASSERT_EQ(arr.front(), 1);
    ASSERT_EQ(*arr.begin(), 1);
}

TEST(array, data) {
    s21::Array<int, 5> arr{1, 2, 3, 4, 5};

    for (std::size_t i = 0; i < arr.size(); ++i)
        ASSERT_EQ(arr.data()[i], i + 1);
}

TEST(array, at) {
    s21::Array<int, 5> arr{1, 2, 3, 4, 5};

    for (std::size_t i = 0; i < arr.size(); ++i)
        ASSERT_EQ(arr.at(3), arr[3]);
}

TEST(array, at_exception) {
    s21::Array<int, 5> arr{1, 2, 3, 4, 5};

    EXPECT_ANY_THROW(arr.at(6));
}

TEST(array, size) {
    s21::Array<int, 5> arr{1, 2, 3, 4, 5};

    ASSERT_EQ(arr.size(), 5);
}

TEST(array, max_size) {
    s21::Array<int, 5> arr{1, 2, 3, 4, 5};

    ASSERT_EQ(arr.max_size(), 5);
}

TEST(array, swap) {
    s21::Array<int, 5> arr{1, 2, 3, 4, 5};
    s21::Array<int, 5> arr1{5, 5, 5, 5, 5};

    arr.swap(arr1);

    for (auto elem : arr)
        ASSERT_EQ(elem, 5);
}

TEST(array, fill) {
    s21::Array<int, 5> arr{1, 2, 3, 4, 5};

    arr.fill(0);

    for (auto elem : arr)
        ASSERT_EQ(elem, 0);
}
