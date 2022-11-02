#include "../s21_vector.hpp"
#include "gtest/gtest.h"

// NOTE: max_size is not tested because the MacOS result differs from the
// implementation discribed here
// https://en.cppreference.com/w/cpp/container/vector/max_size

class VectorTest : public ::testing::Test {
  protected:
    void SetUp() override {
    }

    struct A {
        std::string s;
        A(std::string str) : s(std::move(str)) {
            std::cout << " constructed\n";
        }
        A(const A &o) : s(o.s) {
            std::cout << " copy constructed\n";
        }
        A(A &&o) : s(std::move(o.s)) {
            std::cout << " move constructed\n";
        }
        A &operator=(const A &other) {
            s = other.s;
            std::cout << " copy assigned\n";
            return *this;
        }
        A &operator=(A &&other) {
            s = std::move(other.s);
            std::cout << " move assigned\n";
            return *this;
        }
    };

    s21::Vector<int> vec0_{1, 2, 3, 4, 5, 6, 7, 8, 9};
    s21::Vector<int> vec1_{9, 8, 7, 6, 5, 4, 3, 2, 1};
    s21::Vector<int> vec2_{1};
    s21::Vector<int> vec3_;
    s21::Vector<A> vec4_;
};

TEST_F(VectorTest, move_constructor) {
    s21::Vector<int> v{std::move(vec0_)};
    for (std::size_t i = 0; i < v.size(); ++i)
        ASSERT_EQ(v[i], i + 1);
}

TEST_F(VectorTest, move_assignment) {
    s21::Vector<int> v;
    v = std::move(vec0_);
    for (std::size_t i = 0; i < v.size(); ++i)
        ASSERT_EQ(v[i], i + 1);
}

TEST_F(VectorTest, copy_assignment) {
    s21::Vector<int> v;
    v = vec0_;
    for (std::size_t i = 0; i < v.size(); ++i)
        ASSERT_EQ(v[i], i + 1);
    ASSERT_EQ(v.size(), vec0_.size());
    ASSERT_EQ(v.capacity(), vec0_.capacity());
}

TEST_F(VectorTest, default_constructor) {
    ASSERT_TRUE(vec3_.empty());
    ASSERT_EQ(vec3_.size(), 0);
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

TEST_F(VectorTest, data) {
    ASSERT_EQ(vec2_.data(), &vec2_[0]);
    ASSERT_EQ(*vec2_.data(), vec2_[0]);
    ASSERT_EQ(vec2_.data(), vec2_.begin());
}

TEST_F(VectorTest, empty) {
    ASSERT_TRUE(vec3_.empty());
    ASSERT_FALSE(vec1_.empty());
}

TEST_F(VectorTest, size) {
    ASSERT_EQ(vec0_.size(), 9);
    ASSERT_EQ(vec1_.size(), 9);
    ASSERT_EQ(vec2_.size(), 1);
    ASSERT_EQ(vec3_.size(), 0);
    ASSERT_EQ(vec0_.capacity(), 9);
    ASSERT_EQ(vec1_.capacity(), 9);
    ASSERT_EQ(vec2_.capacity(), 1);
    ASSERT_EQ(vec3_.capacity(), 0);
}

TEST_F(VectorTest, reserve) {
    std::vector s{1, 2, 3, 4, 5, 6, 7, 8, 9};
    s.reserve(6969);
    vec0_.reserve(6969);
    ASSERT_EQ(vec0_.size(), s.size());
    ASSERT_EQ(vec0_.capacity(), s.capacity());
}

TEST_F(VectorTest, shrink) {
    std::vector s{1, 2, 3, 4, 5, 6, 7, 8, 9};
    s.reserve(6969);
    vec0_.reserve(6969);

    s.shrink_to_fit();
    vec0_.shrink_to_fit();
    ASSERT_EQ(vec0_.size(), s.size());
    ASSERT_EQ(vec0_.capacity(), s.capacity());
}

TEST_F(VectorTest, shrink1) {
    std::vector<int> s;

    s.shrink_to_fit();
    vec3_.shrink_to_fit();
    ASSERT_EQ(vec3_.size(), s.size());
    ASSERT_EQ(vec3_.capacity(), s.capacity());
}

TEST_F(VectorTest, clear) {
    std::vector s{1, 2, 3, 4, 5, 6, 7, 8, 9};
    s.clear();
    vec0_.clear();
    ASSERT_EQ(vec0_.size(), s.size());
    ASSERT_EQ(vec0_.capacity(), s.capacity());
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

TEST_F(VectorTest, insert_realloc2) {
    auto itGot = vec3_.insert(vec3_.begin(), 0);
    std::vector<int> want{};
    auto itWant = want.insert(want.begin(), 0);

    ASSERT_EQ(*itGot, *itWant);

    for (auto i = want.size() - 1; i < want.size(); --i)
        ASSERT_EQ(vec3_[i], want[i]);

    ASSERT_EQ(vec3_.size(), want.size());
    ASSERT_EQ(vec3_.capacity(), want.capacity());
}

TEST_F(VectorTest, insert_realloc3) {
    vec0_.insert(vec0_.end(), 0);
    std::vector<int> want{1, 2, 3, 4, 5, 6, 7, 8, 9};
    want.insert(want.end(), 0);

    for (auto i = want.size() - 1; i < want.size(); --i)
        ASSERT_EQ(vec0_[i], want[i]);

    ASSERT_EQ(vec0_.size(), want.size());
    ASSERT_EQ(vec0_.capacity(), want.capacity());
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
    vec2_.erase(vec2_.begin());
    std::vector<int> want{1};

    want.erase(want.begin());

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

TEST_F(VectorTest, emplace) {
}

TEST_F(VectorTest, emplace_back) {
    std::vector<A> want;
    want.reserve(10);
    vec4_.reserve(10);

    A two{"two"};
    A three{"three"};

    want.emplace_back("one");
    // vec4_.emplace_back("one");
    // for (auto i = want.size() - 1; i < want.size(); --i)
    //     ASSERT_EQ(vec4_[i], want[i]);
    //
    // ASSERT_EQ(vec4_.size(), want.size());
    // ASSERT_EQ(vec4_.capacity(), want.capacity());
}
