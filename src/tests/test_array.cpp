#include "../s21_array.hpp"
#include "gtest/gtest.h"

class ArrayTest : public ::testing::Test {
  protected:
    void SetUp() override {
    }
    const s21::array<int, 5> arr1_{1, 2, 3, 4, 5};
    s21::array<int, 5> arr0_{1, 2, 3, 4, 5};
    s21::array<std::string, 1> arr2_{"hello"};
};

TEST_F(ArrayTest, initializer_list_constructor) {
    for (std::size_t i = 0; i < arr0_.size(); ++i)
        ASSERT_EQ(arr0_[i], i + 1);
}

TEST_F(ArrayTest, copy_constructor) {
    s21::array<int, 5> arr1{arr0_};

    for (std::size_t i = 0; i < arr0_.size(); ++i)
        ASSERT_EQ(arr0_[i], arr1[i]);
}

TEST_F(ArrayTest, move_constructor) {
    s21::array<int, 5> arr1{std::move(arr0_)};

    for (std::size_t i = 0; i < arr0_.size(); ++i)
        ASSERT_EQ(arr0_[i], arr1[i]);
}

TEST_F(ArrayTest, copy_assignment) {
    s21::array<int, 5> arr1;
    arr1 = arr0_;

    for (std::size_t i = 0; i < arr0_.size(); ++i)
        ASSERT_EQ(arr0_[i], arr1[i]);
}

TEST_F(ArrayTest, move_assignment) {
    s21::array<int, 5> arr1;
    arr1 = std::move(arr0_);

    for (std::size_t i = 0; i < arr0_.size(); ++i)
        ASSERT_EQ(arr0_[i], arr1[i]);
}

TEST_F(ArrayTest, back) {
    ASSERT_EQ(arr1_.back(), 5);
    ASSERT_EQ(*(arr1_.end() - 1), 5);
    ASSERT_EQ(arr0_.back(), 5);
    ASSERT_EQ(*(arr0_.end() - 1), 5);
}

TEST_F(ArrayTest, front) {
    ASSERT_EQ(arr1_.front(), 1);
    ASSERT_EQ(*arr1_.begin(), 1);
    ASSERT_EQ(arr0_.front(), 1);
    ASSERT_EQ(*arr0_.begin(), 1);
}

TEST_F(ArrayTest, data) {
    for (std::size_t i = 0; i < arr0_.size(); ++i)
        ASSERT_EQ(*(arr0_.data() + i), arr0_[i]);
}

TEST_F(ArrayTest, iterator) {
    int i = 1;
    for (auto it = arr0_.begin(), end = arr0_.end(); it != end; ++it, ++i)
        ASSERT_EQ(*it, i);

    i = 1;
    for (auto it = arr1_.begin(), end = arr1_.end(); it != end; ++it, ++i)
        ASSERT_EQ(*it, i);
}

TEST_F(ArrayTest, at) {
    for (std::size_t i = 0; i < arr0_.size(); ++i)
        ASSERT_EQ(arr0_.at(3), arr0_[3]);
}

TEST_F(ArrayTest, at_exception) {
    EXPECT_ANY_THROW(arr0_.at(6));
}

TEST_F(ArrayTest, size) {
    ASSERT_EQ(arr0_.size(), 5);
}

TEST_F(ArrayTest, max_size) {
    ASSERT_EQ(arr0_.max_size(), 5);
}

TEST_F(ArrayTest, swap) {
    s21::array<int, 5> arr1{5, 5, 5, 5, 5};
    std::array<int, 5> arr2{5, 5, 5, 5, 5};
    std::array<int, 5> arr3{1, 2, 3, 4, 5};

    arr2.swap(arr3);
    arr0_.swap(arr1);

    for (s21::array<int, 5>::size_type i = 0; i < arr0_.size(); ++i)
        ASSERT_EQ(arr0_[i], arr3[i]);
}

TEST_F(ArrayTest, swap_string) {
    s21::array<std::string, 1> arr1{"world"};
    std::array<std::string, 1> arr2{"hello"};
    std::array<std::string, 1> arr3{"world"};

    arr2_.swap(arr1);
    arr2.swap(arr3);

    for (std::size_t i = 0; i < arr2_.size(); ++i)
        ASSERT_EQ(arr2_[i], arr2[i]);
}

TEST_F(ArrayTest, fill) {
    arr0_.fill(0);

    for (auto elem : arr0_)
        ASSERT_EQ(elem, 0);
}

TEST_F(ArrayTest, empty) {
    ASSERT_FALSE(arr0_.empty());
}

TEST(array, test_all) {
    s21::array<std::vector<int>, 10> a;
    std::vector<int> v{1, 2, 3, 4, 5};
    a.fill(v);

    for (auto e : a)
        ASSERT_EQ(e, v);

    ASSERT_ANY_THROW(a[11]);

    ASSERT_ANY_THROW(a.at(11));
    ASSERT_EQ(a.front(), a[0]);
    ASSERT_EQ(a.front(), *a.data());
    ASSERT_EQ(a.back(), a[9]);
    ASSERT_FALSE(a.empty());
    ASSERT_EQ(a.size(), 10);
    ASSERT_EQ(a.max_size(), 10);

    std::vector<int> w{0, 0, 0, 0, 0};
    s21::array<std::vector<int>, 10> b;
    b.fill(w);
    a.swap(b);

    for (auto e : a)
        ASSERT_EQ(e, w);

    for (auto e : b)
        ASSERT_EQ(e, v);
}

TEST(array, test_all_const) {
    std::vector<int> v{1, 2, 3, 4, 5};
    const s21::array<std::vector<int>, 10> a{v, v, v, v, v, v, v, v, v, v};

    for (auto e : a)
        ASSERT_EQ(e, v);

    ASSERT_ANY_THROW(a[11]);
    ASSERT_ANY_THROW(a.at(11));
    ASSERT_EQ(a.front(), a[0]);
    ASSERT_EQ(a.front(), *a.data());
    ASSERT_EQ(a.back(), a[9]);
    ASSERT_FALSE(a.empty());
    ASSERT_EQ(a.size(), 10);
    ASSERT_EQ(a.max_size(), 10);

    s21::array<std::vector<int>, 10> b;
    b.fill(v);

    for (int i = 0; i < 10; i++)
        ASSERT_EQ(a[i], b[i]);
}
