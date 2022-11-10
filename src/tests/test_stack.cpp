#include "../s21_stack.hpp"
#include "gtest/gtest.h"

class StackTest : public ::testing::Test {
  protected:
    void SetUp() override {
    }

    s21::Stack<int> s0_{1, 2, 3, 4, 5};
    s21::Stack<int> s1_{};
};

TEST_F(StackTest, default_constructor) {
    ASSERT_TRUE(s1_.empty());
    ASSERT_EQ(s1_.size(), 0);
}

TEST_F(StackTest, initializer_list_constructor) {
    ASSERT_EQ(s0_.top(), 5);
    ASSERT_FALSE(s0_.empty());
    ASSERT_EQ(s0_.size(), 5);
    s0_.pop();
    ASSERT_EQ(s0_.size(), 4);
    s0_.pop();
    ASSERT_EQ(s0_.size(), 3);
    ASSERT_EQ(s0_.top(), 3);
    s0_.pop();
    s0_.pop();
    s0_.pop();
    ASSERT_TRUE(s0_.empty());

    // NOTE:exception test here when s21::list added
    // ASSERT_ANY_THROW(s0_.pop());
}

TEST_F(StackTest, copy_constructor) {
    s21::Stack copy(s0_);
    ASSERT_EQ(copy.top(), s0_.top());
    copy.pop();
    s0_.pop();
    ASSERT_EQ(copy.top(), s0_.top());
    copy.pop();
    s0_.pop();
    ASSERT_EQ(copy.top(), s0_.top());
    copy.pop();
    s0_.pop();
    ASSERT_EQ(copy.top(), s0_.top());
    copy.pop();
    s0_.pop();
    ASSERT_EQ(copy.top(), s0_.top());
    copy.pop();
    s0_.pop();

    ASSERT_TRUE(copy.empty());
    ASSERT_TRUE(s0_.empty());

    copy.push(69);
    s0_.push(69);
    ASSERT_EQ(copy.top(), s0_.top());
}

TEST_F(StackTest, move_constructor) {
    s21::Stack moved(std::move(s0_));
    ASSERT_EQ(moved.size(), 5);
    ASSERT_EQ(moved.top(), 5);
}

TEST_F(StackTest, copy_assignment) {
    s21::Stack<int> copy;
    copy = s0_;
    ASSERT_EQ(copy.top(), s0_.top());
    copy.pop();
    s0_.pop();
    ASSERT_EQ(copy.top(), s0_.top());
    copy.pop();
    s0_.pop();
    ASSERT_EQ(copy.top(), s0_.top());
    copy.pop();
    s0_.pop();
    ASSERT_EQ(copy.top(), s0_.top());
    copy.pop();
    s0_.pop();
    ASSERT_EQ(copy.top(), s0_.top());
    copy.pop();
    s0_.pop();

    ASSERT_TRUE(copy.empty());
    ASSERT_TRUE(s0_.empty());

    copy.push(69);
    s0_.push(69);
    ASSERT_EQ(copy.top(), s0_.top());
}

TEST_F(StackTest, move_assignment) {
    s21::Stack<int> moved;
    moved = std::move(s0_);
    ASSERT_EQ(moved.size(), 5);
    ASSERT_EQ(moved.top(), 5);
}

TEST_F(StackTest, swap) {
    ASSERT_EQ(s1_.size(), 0);
    ASSERT_EQ(s0_.size(), 5);
    ASSERT_FALSE(s0_.empty());
    ASSERT_TRUE(s1_.empty());
    s0_.swap(s1_);
    ASSERT_FALSE(s1_.empty());
    ASSERT_TRUE(s0_.empty());
    ASSERT_EQ(s0_.size(), 0);
    ASSERT_EQ(s1_.size(), 5);
}

TEST_F(StackTest, push_refref_move) {
    s21::Stack<std::vector<int>> sv;
    std::vector<int> x{1, 2, 3, 4, 5};

    sv.push(std::move(x));

    ASSERT_EQ(x.data(), nullptr);
}

TEST_F(StackTest, emplace) {
    using std::string;
    struct S {
        int id;
        string name;
        string surname;

        S(int i, const std::string &n, const std::string &s)
            : id{i}, name{n}, surname{s} {
        }
    };

    s21::Stack<S> adaptor;
    int num = 69;
    string name = "Billy";
    string surname = "Herrington";
    const S &s = adaptor.emplace_back(num, "Billy", "Herrington");

    ASSERT_EQ(s.id, num);
    ASSERT_EQ(s.name, name);
    ASSERT_EQ(s.surname, surname);
}
