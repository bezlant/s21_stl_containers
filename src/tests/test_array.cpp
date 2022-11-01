#include "../s21_array.hpp"
#include "gtest/gtest.h"

class ArrayTest : public ::testing::Test {
  protected:
    void SetUp() override {
    }

    s21::Array<int, 5> arr0_{1, 2, 3, 4, 5};
};

TEST_F(ArrayTest, initializer_list_constructor) {
    for (std::size_t i = 0; i < arr0_.size(); ++i)
        ASSERT_EQ(arr0_[i], i + 1);
}

TEST_F(ArrayTest, copy_constructor) {
    s21::Array<int, 5> arr1{arr0_};

    for (std::size_t i = 0; i < arr0_.size(); ++i)
        ASSERT_EQ(arr0_[i], arr1[i]);
}

TEST_F(ArrayTest, move_constructor) {
    s21::Array<int, 5> arr1{std::move(arr0_)};

    for (std::size_t i = 0; i < arr0_.size(); ++i)
        ASSERT_EQ(arr0_[i], arr1[i]);
}

TEST_F(ArrayTest, copy_assignment) {
    s21::Array<int, 5> arr1;
    arr1 = arr0_;

    for (std::size_t i = 0; i < arr0_.size(); ++i)
        ASSERT_EQ(arr0_[i], arr1[i]);
}

TEST_F(ArrayTest, move_assignment) {
    s21::Array<int, 5> arr1;
    arr1 = std::move(arr0_);

    for (std::size_t i = 0; i < arr0_.size(); ++i)
        ASSERT_EQ(arr0_[i], arr1[i]);
}

TEST_F(ArrayTest, back) {
    ASSERT_EQ(arr0_.back(), 5);
    ASSERT_EQ(*(arr0_.end() - 1), 5);
}

TEST_F(ArrayTest, front) {
    ASSERT_EQ(arr0_.front(), 1);
    ASSERT_EQ(*arr0_.begin(), 1);
}

TEST_F(ArrayTest, data) {
    for (std::size_t i = 0; i < arr0_.size(); ++i)
        ASSERT_EQ(arr0_.data()[i], i + 1);
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
    s21::Array<int, 5> arr1{5, 5, 5, 5, 5};

    arr0_.swap(arr1);

    for (auto elem : arr0_)
        ASSERT_EQ(elem, 5);
}

TEST_F(ArrayTest, fill) {
    arr0_.fill(0);

    for (auto elem : arr0_)
        ASSERT_EQ(elem, 0);
}

TEST_F(ArrayTest, empty) {
    ASSERT_FALSE(arr0_.empty());
}
