#include <gtest/gtest.h>

#include <vector>

#include "../s21_containers.h"

struct B {
  public:
    int s;
    B() : s{0} {
    }
    explicit B(int str) : s(std::move(str)) {
    }
    B(const B &o) : s(o.s) {
    }
    B(B &&o) : s(std::move(o.s)) {
    }
    B &operator=(const B &other) {
        s = other.s;
        return *this;
    }
    B &operator=(B &&other) {
        s = std::move(other.s);
        return *this;
    }
};

struct A {
    std::string s;
    A() : s("") {
    }

    explicit A(std::string str) : s(std::move(str)) {
    }
    A(const A &o) : s(o.s) {
    }
    A(A &&o) : s(std::move(o.s)) {
    }
    A &operator=(const A &other) {
        s = other.s;
        return *this;
    }
    A &operator=(A &&other) {
        s = std::move(other.s);
        return *this;
    }
};

class VectorTest : public ::testing::Test {
  protected:
    void SetUp() override {
    }

    s21::vector<int> vec0_{1, 2, 3, 4, 5, 6, 7, 8, 9};
    s21::vector<int> vec1_{9, 8, 7, 6, 5, 4, 3, 2, 1};
    s21::vector<int> vec2_{1};
    s21::vector<int> vec3_;
    s21::vector<A> vec4_;
    s21::vector<std::string> vec5_;
};

// Gtest needs this function overload so had to put struct outside of SetUp
bool operator==(const A &lhs, const A &rhs) {
    return rhs.s == lhs.s;
}

// Gtest needs this function overload so had to put struct outside of SetUp
bool operator==(const B &lhs, const B &rhs) {
    return rhs.s == lhs.s;
}

TEST_F(VectorTest, move_constructor) {
    s21::vector<int> v{std::move(vec0_)};
    for (std::size_t i = 0; i < v.size(); ++i)
        ASSERT_EQ(v[i], i + 1);
}

TEST_F(VectorTest, move_assignment) {
    s21::vector<int> v;
    v = std::move(vec0_);
    for (std::size_t i = 0; i < v.size(); ++i)
        ASSERT_EQ(v[i], i + 1);
}

TEST_F(VectorTest, copy_assignment) {
    s21::vector<int> v;
    v = vec0_;

    ASSERT_EQ(vec0_[0], v[0]);

    for (std::size_t i = 0; i < v.size(); ++i)
        ASSERT_EQ(v[i], vec0_[i]);

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
    s21::vector<int> want{vec0_};

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
    vec0_.insert(vec0_.begin() + 3, 5);
    vec0_.insert(vec0_.begin() + 3, 5);
    vec0_.insert(vec0_.begin() + 3, 5);
    vec0_.insert(vec0_.begin() + 3, 5);
    vec0_.insert(vec0_.begin() + 3, 5);
    std::vector<int> want{1, 2, 3, 4, 5, 6, 7, 8, 9};
    want.insert(want.begin() + 3, 5);
    want.insert(want.begin() + 3, 5);
    want.insert(want.begin() + 3, 5);
    want.insert(want.begin() + 3, 5);
    want.insert(want.begin() + 3, 5);
    want.insert(want.begin() + 3, 5);

    for (auto i = want.size() - 1; i < want.size(); --i)
        ASSERT_EQ(vec0_[i], want[i]);

    ASSERT_EQ(vec0_.size(), want.size());
    ASSERT_EQ(vec0_.capacity(), want.capacity());
}

TEST_F(VectorTest, insert_realloc1) {
    vec2_.insert(vec2_.begin(), 5);
    vec2_.insert(vec2_.begin(), 5);
    vec2_.insert(vec2_.begin(), 5);
    vec2_.insert(vec2_.begin(), 5);
    auto itGot = vec2_.insert(vec2_.begin(), 5);

    std::vector<int> want{1};
    want.insert(want.begin(), 5);
    want.insert(want.begin(), 5);
    want.insert(want.begin(), 5);
    want.insert(want.begin(), 5);
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
    int abobus = 69;
    ASSERT_ANY_THROW(vec0_.insert(vec0_.end() + 10, abobus));
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
    s21::vector<int> vec0_{1};
    ASSERT_ANY_THROW(vec0_.erase(vec0_.begin() + 1));
}

TEST_F(VectorTest, push_back_vector) {
    s21::vector<s21::vector<int>> my;
    std::vector<s21::vector<int>> want;

    my.push_back(s21::vector<int>{1, 2, 3});
    want.push_back(s21::vector<int>{1, 2, 3});
}

TEST_F(VectorTest, push_back_B) {
    s21::vector<B> vec6_;
    vec6_.push_back(B(3));
    vec6_.push_back(B(3));
    vec6_.push_back(B(3));
    vec6_.push_back(B(3));
    vec6_.push_back(B(3));
    vec6_.push_back(B(3));
    vec6_.push_back(B(3));
    vec6_.push_back(B(3));
    vec6_.push_back(B(3));
    vec6_.push_back(B(3));
    std::vector<B> want;
    want.push_back(B(3));
    want.push_back(B(3));
    want.push_back(B(3));
    want.push_back(B(3));
    want.push_back(B(3));
    want.push_back(B(3));
    want.push_back(B(3));
    want.push_back(B(3));
    want.push_back(B(3));
    want.push_back(B(3));

    for (auto i = want.size() - 1; i < want.size(); --i)
        ASSERT_EQ(vec6_[i], want[i]);

    ASSERT_EQ(vec6_.size(), want.size());
    ASSERT_EQ(vec6_.capacity(), want.capacity());
}

TEST_F(VectorTest, push_back_A) {
    vec4_.push_back(A("one"));
    vec4_.push_back(A("two"));
    vec4_.push_back(A("three"));
    vec4_.push_back(A("four"));
    std::vector<A> want;
    want.push_back(A("one"));
    want.push_back(A("two"));
    want.push_back(A("three"));
    want.push_back(A("four"));

    for (auto i = want.size() - 1; i < want.size(); --i)
        ASSERT_EQ(vec4_[i], want[i]);

    ASSERT_EQ(vec4_.size(), want.size());
    ASSERT_EQ(vec4_.capacity(), want.capacity());
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
    s21::vector<int> got;
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
    s21::vector<int> got;
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

TEST_F(VectorTest, emplace_back) {
    std::vector<A> want;

    A two{"two"};
    A three{"three"};
    A four{"four"};

    want.push_back(three);
    want.push_back(two);
    want.push_back(four);
    vec4_.emplace_back(three, two, four);

    for (std::size_t i = 0; i < want.size(); ++i) {
        ASSERT_EQ(vec4_[i], want[i]);
    }

    ASSERT_EQ(vec4_.size(), want.size());
    ASSERT_EQ(vec4_.capacity(), want.capacity());
}

TEST_F(VectorTest, emplace) {
    using std::string;
    std::vector<string> want;

    want.emplace(want.begin(), "one");
    vec5_.emplace(vec5_.begin(), "one");
    want.emplace(want.begin(), "one");
    vec5_.emplace(vec5_.begin(), "one");
    want.emplace(want.begin(), "one");
    vec5_.emplace(vec5_.begin(), "one");
    want.emplace(want.begin(), "one");
    vec5_.emplace(vec5_.begin(), "one");

    for (std::size_t i = 0; i < want.size(); ++i)
        ASSERT_EQ(vec5_[i], want[i]);

    ASSERT_EQ(vec5_.size(), want.size());
    ASSERT_EQ(vec5_.capacity(), want.capacity());
}

TEST(vector, test_all) {
    s21::vector<std::string> vs21;
    std::vector<std::string> vsstd;
    for (size_t i = 0; i < 100; i++) {
        vs21.push_back(std::string("aboba"));
        vsstd.push_back(std::string("aboba"));
    }

    ASSERT_EQ(vs21.front(), vsstd.front());
    ASSERT_EQ(vs21.back(), vsstd.back());
    ASSERT_EQ(vs21.size(), vsstd.size());
    ASSERT_EQ(vs21.capacity(), vsstd.capacity());

    for (size_t i = 0; i < 30; i++) {
        vs21.insert(vs21.begin() + 3, "aboba");
        vsstd.insert(vsstd.begin() + 3, "aboba");
    }

    ASSERT_EQ(vs21.size(), vsstd.size());
    ASSERT_EQ(vs21.capacity(), vsstd.capacity());

    for (size_t i = 0; i < vs21.size(); ++i)
        ASSERT_EQ(vs21[i], vsstd[i]);

    for (auto *it = vs21.begin(); it != vs21.end(); ++it)
        vs21.erase(it);
    for (auto it = vsstd.begin(); it != vsstd.end(); ++it)
        vsstd.erase(it);

    ASSERT_EQ(vs21.size(), vsstd.size());
    ASSERT_EQ(vs21.capacity(), vsstd.capacity());

    for (size_t i = 0; i < 1234; i++) {
        vs21.push_back("aboba");
        vsstd.push_back("aboba");
    }

    ASSERT_EQ(vs21.size(), vsstd.size());
    ASSERT_EQ(vs21.capacity(), vsstd.capacity());

    vs21.reserve(2000);
    vsstd.reserve(2000);

    ASSERT_EQ(vs21.size(), vsstd.size());
    ASSERT_EQ(vs21.capacity(), vsstd.capacity());

    vs21.shrink_to_fit();
    vsstd.shrink_to_fit();

    ASSERT_EQ(vs21.size(), vsstd.size());
    ASSERT_EQ(vs21.capacity(), vsstd.capacity());

    vs21.clear();
    vsstd.clear();

    ASSERT_EQ(vs21.size(), vsstd.size());
    ASSERT_EQ(vs21.capacity(), vsstd.capacity());

    ASSERT_EQ(vs21.max_size(), vsstd.max_size());

    ASSERT_ANY_THROW(vs21[10]);
    ASSERT_ANY_THROW(vs21[-1]);
    ASSERT_ANY_THROW(vs21.at(-1));
}

TEST(vector, test_all_const) {
    const s21::vector<std::string> vs21{
        "hello", "world", "help", "me", "make", "a", "decent", "choice", "?"};
    const std::vector<std::string> vsstd{
        "hello", "world", "help", "me", "make", "a", "decent", "choice", "?"};
    ASSERT_EQ(vs21.size(), vsstd.size());
    ASSERT_EQ(vs21.capacity(), vsstd.capacity());

    auto itstd = vsstd.begin();
    for (auto *it = vs21.begin(); it != vs21.end(); ++it) {
        ASSERT_EQ(*it, *itstd++);
    }

    ASSERT_EQ(*vs21.data(), *vsstd.data());

    for (size_t i = 0; i < vs21.size(); ++i)
        ASSERT_EQ(vs21[i], vsstd[i]);

    ASSERT_EQ(vs21.size(), vsstd.size());
    ASSERT_EQ(vs21.capacity(), vsstd.capacity());

    ASSERT_EQ(std::string{"hello"}, vs21.front());
    ASSERT_EQ(std::string{"?"}, vs21.back());

    ASSERT_ANY_THROW(vs21[10]);
    ASSERT_ANY_THROW(vs21[-1]);
    ASSERT_ANY_THROW(vs21.at(-1));
}

TEST(vector, vzero) {
    s21::vector<int> vzero;
    const s21::vector<int> cvzero;
    ASSERT_ANY_THROW(vzero.insert(vzero.begin() + 10, 69));
    ASSERT_ANY_THROW(vzero.front());
    ASSERT_ANY_THROW(vzero.back());
    ASSERT_ANY_THROW(cvzero.front());
    ASSERT_ANY_THROW(cvzero.back());
}

TEST(vector, reserve_exception) {
    s21::vector<int> vzero;
    ASSERT_ANY_THROW(vzero.reserve(vzero.max_size() + 1));
}
