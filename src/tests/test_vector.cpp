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

TEST(vector, insert_norealloc) {
    s21::Vector<int> got{1, 2, 3, 4, 5, 6};
    got.reserve(100);
    auto itGot = got.insert(got.begin() + 3, 5);
    std::vector<int> want{1, 2, 3, 4, 5, 6};
    want.reserve(100);
    auto itWant = want.insert(want.begin() + 3, 5);

    ASSERT_EQ(*itGot, *itWant);

    for (auto i = want.size() - 1; i < want.size(); --i)
        ASSERT_EQ(got[i], want[i]);

    ASSERT_EQ(got.size(), want.size());
    ASSERT_EQ(got.capacity(), want.capacity());
}

TEST(vector, erase) {
    s21::Vector<int> got{1, 2, 3, 4, 5, 6};
    auto itGot = got.erase(got.begin() + 3);
    std::vector<int> want{1, 2, 3, 4, 5, 6};
    auto itWant = want.erase(want.begin() + 3);

    ASSERT_EQ(*itGot, *itWant);

    for (auto i = want.size() - 1; i < want.size(); --i)
        ASSERT_EQ(got[i], want[i]);

    ASSERT_EQ(got.size(), want.size());
    ASSERT_EQ(got.capacity(), want.capacity());
}

TEST(vector, erase_edge) {
    s21::Vector<int> got{1};
    auto itGot = got.erase(got.begin());
    std::vector<int> want{1};
    auto itWant = want.erase(want.begin());

    ASSERT_EQ(*itGot, *itWant);

    for (auto i = want.size() - 1; i < want.size(); --i)
        ASSERT_EQ(got[i], want[i]);

    ASSERT_EQ(got.size(), want.size());
    ASSERT_EQ(got.capacity(), want.capacity());
}

TEST(vector, erase_edge1) {
    s21::Vector<int> got{1, 2, 3, 4, 5};
    auto itGot = got.erase(got.begin() + 4);
    std::vector<int> want{1, 2, 3, 4, 5};
    auto itWant = want.erase(want.begin() + 4);

    ASSERT_EQ(*itGot, *itWant);

    for (auto i = want.size() - 1; i < want.size(); --i)
        ASSERT_EQ(got[i], want[i]);

    ASSERT_EQ(got.size(), want.size());
    ASSERT_EQ(got.capacity(), want.capacity());
}

TEST(vector, erase_exception) {
    s21::Vector<int> got{1};
    ASSERT_ANY_THROW(got.erase(got.begin() + 1));
}

TEST(vector, push_back) {
    s21::Vector<int> got{1, 2, 3, 4, 5};
    got.push_back(6);
    std::vector<int> want{1, 2, 3, 4, 5};
    want.push_back(6);

    for (auto i = want.size() - 1; i < want.size(); --i)
        ASSERT_EQ(got[i], want[i]);

    ASSERT_EQ(got.size(), want.size());
    ASSERT_EQ(got.capacity(), want.capacity());
}

TEST(vector, push_back_empty) {
    s21::Vector<int> got;
    got.push_back(69);
    std::vector<int> want;
    want.push_back(69);

    for (auto i = want.size() - 1; i < want.size(); --i)
        ASSERT_EQ(got[i], want[i]);

    ASSERT_EQ(got.size(), want.size());
    ASSERT_EQ(got.capacity(), want.capacity());
}

TEST(vector, pop_back) {
    s21::Vector<int> got{1, 2, 3, 4};
    got.pop_back();
    std::vector<int> want{1, 2, 3, 4};
    want.pop_back();

    for (auto i = want.size() - 1; i < want.size(); --i)
        ASSERT_EQ(got[i], want[i]);

    ASSERT_EQ(got.size(), want.size());
    ASSERT_EQ(got.capacity(), want.capacity());
}

TEST(vector, pop_empty) {
    s21::Vector<int> got;
    ASSERT_ANY_THROW(got.pop_back());
}
