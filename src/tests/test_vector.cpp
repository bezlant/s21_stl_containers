#include "../s21_vector.hpp"
#include "gtest/gtest.h"

class VectorTest : public ::testing::Test {
  protected:
    void SetUp() override {
    }

    s21::Vector<int> vec0_{1, 2, 3, 4, 5, 6, 7, 8, 9};
    s21::Vector<int> vec1_{9, 8, 7, 6, 5, 4, 3, 2, 1};
    s21::Vector<int> vec2_{1};
};

TEST(vector, default_constructor) {
}

TEST_F(VectorTest, initializer_list_constructor) {
    for (std::size_t i = 0; i < vec0_.size(); ++i)
        ASSERT_EQ(vec0_[i], i + 1);
}

TEST_F(VectorTest, copy_constructor) {
    s21::Vector<int> want{vec0_};

    for (std::size_t i = 0; i < vec0_.size(); ++i)
        ASSERT_EQ(vec0_[i], want[i]);
}

TEST_F(VectorTest, insert_realloc) {
    vec0_.insert(vec0_.begin() + 3, 5);
    std::vector<int> want{1, 2, 3, 4, 5, 6, 7, 8, 9};
    want.insert(want.begin() + 3, 5);

    for (auto i = want.size() - 1; i < want.size(); --i)
        ASSERT_EQ(vec0_[i], want[i]);

    ASSERT_EQ(vec0_.size(), want.size());
    ASSERT_EQ(vec0_.capacity(), want.capacity());
}

TEST_F(VectorTest, insert_realloc1) {
    auto itGot = vec2_.insert(vec2_.begin(), 5);
    std::vector<int> want{1};
    auto itWant = want.insert(want.begin(), 5);

    ASSERT_EQ(*itGot, *itWant);

    for (auto i = want.size() - 1; i < want.size(); --i)
        ASSERT_EQ(vec2_[i], want[i]);

    ASSERT_EQ(vec2_.size(), want.size());
    ASSERT_EQ(vec2_.capacity(), want.capacity());
}

TEST_F(VectorTest, insert_norealloc) {
    vec0_.reserve(100);
    auto itGot = vec0_.insert(vec0_.begin() + 3, 5);
    std::vector<int> want{1, 2, 3, 4, 5, 6, 7, 8, 9};
    want.reserve(100);
    auto itWant = want.insert(want.begin() + 3, 5);

    ASSERT_EQ(*itGot, *itWant);

    for (auto i = want.size() - 1; i < want.size(); --i)
        ASSERT_EQ(vec0_[i], want[i]);

    ASSERT_EQ(vec0_.size(), want.size());
    ASSERT_EQ(vec0_.capacity(), want.capacity());
}

TEST_F(VectorTest, erase) {
    auto itGot = vec0_.erase(vec0_.begin() + 3);
    std::vector<int> want{1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto itWant = want.erase(want.begin() + 3);

    ASSERT_EQ(*itGot, *itWant);

    for (auto i = want.size() - 1; i < want.size(); --i)
        ASSERT_EQ(vec0_[i], want[i]);

    ASSERT_EQ(vec0_.size(), want.size());
    ASSERT_EQ(vec0_.capacity(), want.capacity());
}

TEST_F(VectorTest, erase_edge) {
    auto itGot = vec2_.erase(vec2_.begin());
    std::vector<int> want{1};
    auto itWant = want.erase(want.begin());

    ASSERT_EQ(*itGot, *itWant);

    for (auto i = want.size() - 1; i < want.size(); --i)
        ASSERT_EQ(vec2_[i], want[i]);

    ASSERT_EQ(vec2_.size(), want.size());
    ASSERT_EQ(vec2_.capacity(), want.capacity());
}

TEST_F(VectorTest, erase_edge1) {
    auto itGot = vec0_.erase(vec0_.begin() + 4);
    std::vector<int> want{1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto itWant = want.erase(want.begin() + 4);

    ASSERT_EQ(*itGot, *itWant);

    for (auto i = want.size() - 1; i < want.size(); --i)
        ASSERT_EQ(vec0_[i], want[i]);

    ASSERT_EQ(vec0_.size(), want.size());
    ASSERT_EQ(vec0_.capacity(), want.capacity());
}

TEST_F(VectorTest, erase_exception) {
    s21::Vector<int> vec0_{1};
    ASSERT_ANY_THROW(vec0_.erase(vec0_.begin() + 1));
}

TEST_F(VectorTest, push_back) {
    vec0_.push_back(6);
    std::vector<int> want{1, 2, 3, 4, 5, 6, 7, 8, 9};
    want.push_back(6);

    for (auto i = want.size() - 1; i < want.size(); --i)
        ASSERT_EQ(vec0_[i], want[i]);

    ASSERT_EQ(vec0_.size(), want.size());
    ASSERT_EQ(vec0_.capacity(), want.capacity());
}

TEST_F(VectorTest, push_back_empty) {
    s21::Vector<int> got;
    got.push_back(69);
    std::vector<int> want;
    want.push_back(69);

    for (auto i = want.size() - 1; i < want.size(); --i)
        ASSERT_EQ(got[i], want[i]);

    ASSERT_EQ(got.size(), want.size());
    ASSERT_EQ(got.capacity(), want.capacity());
}

TEST_F(VectorTest, pop_back) {
    vec0_.pop_back();
    std::vector<int> want{1, 2, 3, 4, 5, 6, 7, 8, 9};
    want.pop_back();

    for (auto i = want.size() - 1; i < want.size(); --i)
        ASSERT_EQ(vec0_[i], want[i]);

    ASSERT_EQ(vec0_.size(), want.size());
    ASSERT_EQ(vec0_.capacity(), want.capacity());
}

TEST_F(VectorTest, pop_empty) {
    s21::Vector<int> got;
    ASSERT_ANY_THROW(got.pop_back());
}

TEST_F(VectorTest, swap) {
    auto want_a = vec1_;
    auto want_b = vec0_;

    vec0_.swap(vec1_);

    for (auto i = want_a.size() - 1; i < want_a.size(); --i)
        ASSERT_EQ(want_a[i], vec0_[i]);
    ASSERT_EQ(want_a.size(), vec0_.size());
    ASSERT_EQ(want_a.capacity(), vec0_.capacity());

    for (auto i = want_b.size() - 1; i < want_b.size(); --i)
        ASSERT_EQ(want_b[i], vec1_[i]);
    ASSERT_EQ(want_b.size(), vec1_.size());
    ASSERT_EQ(want_b.capacity(), vec1_.capacity());
}
