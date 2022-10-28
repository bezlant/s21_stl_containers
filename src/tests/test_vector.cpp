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

TEST(vector, insert_realloc) {
    s21::Vector<int> got{1, 2, 3, 4, 5, 6, 7, 8, 9};
    got.insert(got.begin() + 3, 5);
    std::vector<int> want{1, 2, 3, 4, 5, 6, 7, 8, 9};
    want.insert(want.begin() + 3, 5);

    for (auto i = want.size() - 1; i < want.size(); --i)
        ASSERT_EQ(got[i], want[i]);

    ASSERT_EQ(got.size(), want.size());
    ASSERT_EQ(got.capacity(), want.capacity());
}

TEST(vector, insert_realloc1) {
    s21::Vector<int> got{1};
    auto itGot = got.insert(got.begin(), 5);
    std::vector<int> want{1};
    auto itWant = want.insert(want.begin(), 5);

    ASSERT_EQ(*itGot, *itWant);

    for (auto i = want.size() - 1; i < want.size(); --i)
        ASSERT_EQ(got[i], want[i]);

    ASSERT_EQ(got.size(), want.size());
    ASSERT_EQ(got.capacity(), want.capacity());
}
