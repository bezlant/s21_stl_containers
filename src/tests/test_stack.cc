#include <stack>
#include <vector>

#include "../s21_containers.h"
#include <gtest/gtest.h>

class StackTest : public ::testing::Test {
  protected:
    void SetUp() override {
    }

    s21::stack<int> s0_{1, 2, 3, 4, 5};
    s21::stack<int> s1_{};
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
}

TEST_F(StackTest, copy_constructor) {
    s21::stack<int> copy(s0_);
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

    int x = 420;
    copy.push(x);
    s0_.push(x);
    copy.push(69);
    s0_.push(69);
    ASSERT_EQ(copy.top(), s0_.top());
}

TEST_F(StackTest, move_constructor) {
    s21::stack<int> moved(std::move(s0_));
    ASSERT_EQ(moved.size(), 5);
    ASSERT_EQ(moved.top(), 5);
}

TEST_F(StackTest, copy_assignment) {
    s21::stack<int> copy;
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
    s21::stack<int> moved;
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

TEST(stack, emplace_back) {
    s21::stack<std::vector<int>> s;
    std::stack<std::vector<int>> ss;

    for (s21::stack<std::vector<int>>::size_type i = 0; i < 10; ++i) {
        s.emplace_front((std::vector<int>{1, 2, 3, 4, 5}),
                        (std::vector<int>{1, 2, 3, 4, 5}),
                        (std::vector<int>{1, 2, 3, 4, 5}));
        s.push(std::vector<int>{1, 2, 3, 4, 5});
        ss.push(std::vector<int>{1, 2, 3, 4, 5});
        ss.push(std::vector<int>{1, 2, 3, 4, 5});
        ss.push(std::vector<int>{1, 2, 3, 4, 5});
        ss.push(std::vector<int>{1, 2, 3, 4, 5});
    }

    const s21::stack<std::vector<int>> cs = s;
    ASSERT_EQ(cs.top(), s.top());

    ASSERT_EQ(s.size(), ss.size());

    for (s21::stack<std::vector<int>>::size_type i = 0; i < s.size(); i++) {
        ASSERT_EQ(s.top(), ss.top());
        s.pop();
        ss.pop();
    }
    ASSERT_EQ(s.empty(), ss.empty());
}

TEST(stack, consts) {
    s21::stack<int> x;
    std::stack<int> y;
    int val = 69;
    x.push(val);
    y.push(val);
    x.push(val);
    x.push(val);
    y.push(val);
    y.push(val);
}

TEST_F(StackTest, swap_test) {
    std::stack<int> s0({1, 2, 3, 4, 5});
    ASSERT_EQ(s0_.size(), 5);

    for (int i = 0; i < 5; ++i) {
        ASSERT_EQ(s0.top(), s0_.top());
        s0.pop();
        s0_.pop();
    }
}

TEST_F(StackTest, push_pop_top_empty_size) {
    std::stack<int> s0;
    ASSERT_EQ(s1_.size(), 0);
    ASSERT_TRUE(s1_.empty());

    s1_.push(1);
    s0.push(1);
    ASSERT_EQ(s1_.top(), s0.top());
    ASSERT_EQ(s1_.size(), s0.size());
    ASSERT_FALSE(s1_.empty());

    s1_.push(2);
    s0.push(2);
    ASSERT_EQ(s1_.top(), s0.top());
    ASSERT_EQ(s1_.size(), s0.size());
    ASSERT_FALSE(s1_.empty());

    s1_.push(3);
    s0.push(3);
    ASSERT_EQ(s1_.top(), s0.top());
    ASSERT_EQ(s1_.size(), s0.size());
    ASSERT_FALSE(s1_.empty());

    s1_.push(4);
    s0.push(4);
    ASSERT_EQ(s1_.top(), s0.top());
    ASSERT_EQ(s1_.size(), s0.size());
    ASSERT_FALSE(s1_.empty());

    s1_.push(5);
    s0.push(5);
    ASSERT_EQ(s1_.top(), s0.top());
    ASSERT_EQ(s1_.size(), s0.size());
    ASSERT_FALSE(s1_.empty());

    s1_.pop();
    s0.pop();
    ASSERT_EQ(s1_.top(), s0.top());
    ASSERT_EQ(s1_.size(), s0.size());
    ASSERT_FALSE(s1_.empty());

    s1_.pop();
    s0.pop();
    ASSERT_EQ(s1_.top(), s0.top());
    ASSERT_EQ(s1_.size(), s0.size());
    ASSERT_FALSE(s1_.empty());

    s1_.pop();
    s0.pop();
    ASSERT_EQ(s1_.top(), s0.top());
    ASSERT_EQ(s1_.size(), s0.size());
    ASSERT_FALSE(s1_.empty());

    s1_.pop();
    s0.pop();
    ASSERT_EQ(s1_.top(), s0.top());
    ASSERT_EQ(s1_.size(), s0.size());
    ASSERT_FALSE(s1_.empty());

    s1_.pop();
    s0.pop();
    ASSERT_EQ(s1_.size(), s0.size());
    ASSERT_TRUE(s1_.empty());
    ASSERT_TRUE(s0.empty());
}

// tests for s21::stack class using std::stack as a reference for methods top,
// pop, push, size, empty, size
TEST_F(StackTest, top_pop_push_size_empty) {
    std::stack<int> s0;
    ASSERT_EQ(s1_.size(), 0);
    ASSERT_TRUE(s1_.empty());

    s1_.push(1);
    s0.push(1);
    ASSERT_EQ(s1_.top(), s0.top());
    ASSERT_EQ(s1_.size(), s0.size());
    ASSERT_FALSE(s1_.empty());

    s1_.push(2);
    s0.push(2);
    ASSERT_EQ(s1_.top(), s0.top());
    ASSERT_EQ(s1_.size(), s0.size());
    ASSERT_FALSE(s1_.empty());

    s1_.push(3);
    s0.push(3);
    ASSERT_EQ(s1_.top(), s0.top());
    ASSERT_EQ(s1_.size(), s0.size());
    ASSERT_FALSE(s1_.empty());

    s1_.push(4);
    s0.push(4);
    ASSERT_EQ(s1_.top(), s0.top());
    ASSERT_EQ(s1_.size(), s0.size());
    ASSERT_FALSE(s1_.empty());

    s1_.push(5);
    s0.push(5);
    ASSERT_EQ(s1_.top(), s0.top());
    ASSERT_EQ(s1_.size(), s0.size());
    ASSERT_FALSE(s1_.empty());

    s1_.pop();
    s0.pop();
    ASSERT_EQ(s1_.top(), s0.top());
    ASSERT_EQ(s1_.size(), s0.size());
    ASSERT_FALSE(s1_.empty());

    s1_.pop();
    s0.pop();
    ASSERT_EQ(s1_.top(), s0.top());
    ASSERT_EQ(s1_.size(), s0.size());
    ASSERT_FALSE(s1_.empty());

    s1_.pop();
    s0.pop();
    ASSERT_EQ(s1_.top(), s0.top());
    ASSERT_EQ(s1_.size(), s0.size());
    ASSERT_FALSE(s1_.empty());

    s1_.pop();
    s0.pop();
    ASSERT_EQ(s1_.top(), s0.top());
    ASSERT_EQ(s1_.size(), s0.size());
    ASSERT_FALSE(s1_.empty());

    s1_.pop();
    s0.pop();
    ASSERT_EQ(s1_.size(), s0.size());
    ASSERT_TRUE(s1_.empty());
    ASSERT_TRUE(s0.empty());
}

// test for s21::stack copy constructor
TEST(Stack, copy_constructor) {
    s21::stack<int> s1;
    s1.push(1);
    s1.push(2);
    s1.push(3);
    s1.push(4);

    s21::stack<int> s0(s1);
    ASSERT_EQ(s1.size(), s0.size());
    ASSERT_EQ(s1.top(), s0.top());
    ASSERT_FALSE(s1.empty());
    ASSERT_FALSE(s0.empty());

    s1.pop();
    s0.pop();
    ASSERT_EQ(s1.size(), s0.size());
    ASSERT_EQ(s1.top(), s0.top());
    ASSERT_FALSE(s1.empty());
    ASSERT_FALSE(s0.empty());

    s1.pop();
    s0.pop();
    ASSERT_EQ(s1.size(), s0.size());
    ASSERT_EQ(s1.top(), s0.top());
    ASSERT_FALSE(s1.empty());
    ASSERT_FALSE(s0.empty());

    s1.pop();
    s0.pop();
    ASSERT_EQ(s1.size(), s0.size());
    ASSERT_EQ(s1.top(), s0.top());
    ASSERT_FALSE(s1.empty());
    ASSERT_FALSE(s0.empty());

    s1.pop();
    s0.pop();
    ASSERT_EQ(s1.size(), s0.size());
    ASSERT_TRUE(s1.empty());
    ASSERT_TRUE(s0.empty());
}

// test for s21::stack move constructor
TEST(Stack, move_constructor) {
    s21::stack<int> s1;
    s1.push(1);
    s1.push(2);
    s1.push(3);
    s1.push(4);
    s1.push(5);

    s21::stack<int> s0(std::move(s1));
    ASSERT_EQ(s1.size(), 0);
    ASSERT_EQ(s0.size(), 5);
    ASSERT_TRUE(s1.empty());
    ASSERT_FALSE(s0.empty());

    ASSERT_EQ(s0.top(), 5);
    s0.pop();
    ASSERT_EQ(s0.top(), 4);
    s0.pop();
    ASSERT_EQ(s0.top(), 3);
    s0.pop();
    ASSERT_EQ(s0.top(), 2);
    s0.pop();
    ASSERT_EQ(s0.top(), 1);
    s0.pop();
    ASSERT_TRUE(s0.empty());
}

// s21::stack constructor tests
TEST(Stack, constructor) {
    s21::stack<int> s0;
    ASSERT_EQ(s0.size(), 0);
    ASSERT_TRUE(s0.empty());
}

// s21::stack copy assignment tests
TEST(Stack, copy_assignment) {
    s21::stack<int> s1;
    s1.push(1);
    s1.push(2);
    s1.push(3);
    s1.push(4);

    s21::stack<int> s0;
    s0 = s1;
    ASSERT_EQ(s1.size(), s0.size());
    ASSERT_EQ(s1.top(), s0.top());
    ASSERT_FALSE(s1.empty());
    ASSERT_FALSE(s0.empty());

    s1.pop();
    s0.pop();
    ASSERT_EQ(s1.size(), s0.size());
    ASSERT_EQ(s1.top(), s0.top());
    ASSERT_FALSE(s1.empty());
    ASSERT_FALSE(s0.empty());

    s1.pop();
    s0.pop();
    ASSERT_EQ(s1.size(), s0.size());
    ASSERT_EQ(s1.top(), s0.top());
    ASSERT_FALSE(s1.empty());
    ASSERT_FALSE(s0.empty());

    s1.pop();
    s0.pop();
    ASSERT_EQ(s1.size(), s0.size());
    ASSERT_EQ(s1.top(), s0.top());
    ASSERT_FALSE(s1.empty());
    ASSERT_FALSE(s0.empty());

    s1.pop();
    s0.pop();
    ASSERT_EQ(s1.size(), s0.size());
    ASSERT_TRUE(s1.empty());
    ASSERT_TRUE(s0.empty());
}

// s21::stack move assignment tests
TEST(Stack, move_assignment) {
    s21::stack<int> s1;
    s1.push(1);
    s1.push(2);
    s1.push(3);
    s1.push(4);
    s1.push(5);

    s21::stack<int> s0;
    s0 = std::move(s1);
    ASSERT_EQ(s1.size(), 0);
    ASSERT_EQ(s0.size(), 5);
    ASSERT_TRUE(s1.empty());
    ASSERT_FALSE(s0.empty());

    ASSERT_EQ(s0.top(), 5);
    s0.pop();
    ASSERT_EQ(s0.top(), 4);
    s0.pop();
    ASSERT_EQ(s0.top(), 3);
    s0.pop();
    ASSERT_EQ(s0.top(), 2);
    s0.pop();
    ASSERT_EQ(s0.top(), 1);
    s0.pop();
    ASSERT_TRUE(s0.empty());
}

// stack initializer_list tests
TEST(Stack, initializer_list) {
    s21::stack<int> s0{1, 2, 3, 4, 5};
    ASSERT_EQ(s0.size(), 5);
    ASSERT_FALSE(s0.empty());

    ASSERT_EQ(s0.top(), 5);
    s0.pop();
    ASSERT_EQ(s0.top(), 4);
    s0.pop();
    ASSERT_EQ(s0.top(), 3);
    s0.pop();
    ASSERT_EQ(s0.top(), 2);
    s0.pop();
    ASSERT_EQ(s0.top(), 1);
    s0.pop();
    ASSERT_TRUE(s0.empty());
}

// stack push/pop tests
TEST(Stack, push_pop) {
    s21::stack<int> s0;
    s0.push(1);
    s0.push(2);
    s0.push(3);
    s0.push(4);
    s0.push(5);
    ASSERT_EQ(s0.size(), 5);
    ASSERT_FALSE(s0.empty());

    ASSERT_EQ(s0.top(), 5);
    s0.pop();
    ASSERT_EQ(s0.top(), 4);
    s0.pop();
    ASSERT_EQ(s0.top(), 3);
    s0.pop();
    ASSERT_EQ(s0.top(), 2);
    s0.pop();
    ASSERT_EQ(s0.top(), 1);
    s0.pop();
    ASSERT_TRUE(s0.empty());
}

// stack top tests
TEST(Stack, top) {
    s21::stack<int> s0;
    s0.push(1);
    s0.push(2);
    s0.push(3);
    s0.push(4);
    s0.push(5);
    ASSERT_EQ(s0.size(), 5);
    ASSERT_FALSE(s0.empty());

    ASSERT_EQ(s0.top(), 5);
    s0.pop();
    ASSERT_EQ(s0.top(), 4);
    s0.pop();
    ASSERT_EQ(s0.top(), 3);
    s0.pop();
    ASSERT_EQ(s0.top(), 2);
    s0.pop();
    ASSERT_EQ(s0.top(), 1);
    s0.pop();
    ASSERT_TRUE(s0.empty());
}

// stack size tests
TEST(Stack, size) {
    s21::stack<int> s0;
    ASSERT_EQ(s0.size(), 0);
    ASSERT_TRUE(s0.empty());

    s0.push(1);
    ASSERT_EQ(s0.size(), 1);
    ASSERT_FALSE(s0.empty());
}
