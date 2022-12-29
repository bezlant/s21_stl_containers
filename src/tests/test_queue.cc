#include <queue>
#include <vector>

#include "../s21_containers.h"
#include <gtest/gtest.h>

class QueueTest : public ::testing::Test {
  protected:
    void SetUp() override {
    }

    s21::queue<int> s0_{1, 2, 3, 4, 5};
    s21::queue<int> s1_{};
};

TEST_F(QueueTest, default_constructor) {
    ASSERT_TRUE(s1_.empty());
    ASSERT_EQ(s1_.size(), 0);
}

TEST_F(QueueTest, initializer_list_constructor) {
    ASSERT_EQ(s0_.back(), 5);
    ASSERT_FALSE(s0_.empty());
    ASSERT_EQ(s0_.size(), 5);
    s0_.pop();
    ASSERT_EQ(s0_.size(), 4);
    s0_.pop();
    ASSERT_EQ(s0_.size(), 3);
    ASSERT_EQ(s0_.front(), 3);
    s0_.pop();
    s0_.pop();
    s0_.pop();
    ASSERT_TRUE(s0_.empty());

    // NOTE:exception test here when s21::list added
    // ASSERT_ANY_THROW(s0_.pop());
}

TEST_F(QueueTest, copy_constructor) {
    s21::queue<int> copy(s0_);
    ASSERT_EQ(copy.front(), s0_.front());
    copy.pop();
    s0_.pop();
    ASSERT_EQ(copy.front(), s0_.front());
    copy.pop();
    s0_.pop();
    ASSERT_EQ(copy.front(), s0_.front());
    copy.pop();
    s0_.pop();
    ASSERT_EQ(copy.front(), s0_.front());
    copy.pop();
    s0_.pop();
    ASSERT_EQ(copy.front(), s0_.front());
    copy.pop();
    s0_.pop();

    ASSERT_TRUE(copy.empty());
    ASSERT_TRUE(s0_.empty());

    copy.push(69);
    s0_.push(69);
    ASSERT_EQ(copy.front(), s0_.front());
    ASSERT_EQ(copy.back(), s0_.back());
}

TEST_F(QueueTest, move_constructor) {
    s21::queue<int> moved(std::move(s0_));
    ASSERT_EQ(moved.size(), 5);
    ASSERT_EQ(moved.back(), 5);
}

TEST_F(QueueTest, copy_assignment) {
    s21::queue<int> copy;
    copy = s0_;
    ASSERT_EQ(copy.front(), s0_.front());
    copy.pop();
    s0_.pop();
    ASSERT_EQ(copy.front(), s0_.front());
    copy.pop();
    s0_.pop();
    ASSERT_EQ(copy.front(), s0_.front());
    copy.pop();
    s0_.pop();
    ASSERT_EQ(copy.front(), s0_.front());
    copy.pop();
    s0_.pop();
    ASSERT_EQ(copy.front(), s0_.front());
    copy.pop();
    s0_.pop();

    ASSERT_TRUE(copy.empty());
    ASSERT_TRUE(s0_.empty());

    copy.push(69);
    s0_.push(69);
    ASSERT_EQ(copy.front(), s0_.front());
}

TEST_F(QueueTest, move_assignment) {
    s21::queue<int> moved;
    moved = std::move(s0_);
    ASSERT_EQ(moved.size(), 5);
    ASSERT_EQ(moved.back(), 5);
}

TEST_F(QueueTest, swap) {
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

TEST(Queue, emplace_back) {
    s21::queue<std::vector<int>> s;
    std::queue<std::vector<int>> ss;

    for (s21::queue<std::vector<int>>::size_type i = 0; i < 10; ++i) {
        s.emplace_back((std::vector<int>{1, 2, 3, 4, 5}),
                       (std::vector<int>{1, 2, 3, 4, 5}),
                       (std::vector<int>{1, 2, 3, 4, 5}));
        s.push(std::vector<int>{1, 2, 3, 4, 5});
        ss.push(std::vector<int>{1, 2, 3, 4, 5});
        ss.push(std::vector<int>{1, 2, 3, 4, 5});
        ss.push(std::vector<int>{1, 2, 3, 4, 5});
        ss.push(std::vector<int>{1, 2, 3, 4, 5});
    }

    ASSERT_EQ(s.size(), ss.size());

    for (s21::queue<std::vector<int>>::size_type i = 0; i < s.size(); i++) {
        ASSERT_EQ(s.front(), ss.front());
        s.pop();
        ss.pop();
    }
    ASSERT_EQ(s.empty(), ss.empty());
}

TEST(Queue, consts) {
    s21::queue<int> x;
    std::queue<int> y;
    int val = 69;
    x.push(val);
    y.push(val);
    x.push(val);
    x.push(val);
    y.push(val);
    y.push(val);

    const s21::queue<int> cx = x;
    const std::queue<int> cy = y;

    ASSERT_EQ(cx.front(), cy.front());
    ASSERT_EQ(cx.back(), cy.back());
}

TEST_F(QueueTest, swap_test) {
    std::queue<int> s0({1, 2, 3, 4, 5});
    ASSERT_EQ(s0_.size(), 5);

    for (int i = 0; i < 5; ++i) {
        ASSERT_EQ(s0.front(), s0_.front());
        s0.pop();
        s0_.pop();
    }
}

TEST_F(QueueTest, push_pop_front_empty_size) {
    std::queue<int> s0;
    ASSERT_EQ(s1_.size(), 0);
    ASSERT_TRUE(s1_.empty());

    s1_.push(1);
    s0.push(1);
    ASSERT_EQ(s1_.front(), s0.front());
    ASSERT_EQ(s1_.size(), s0.size());
    ASSERT_FALSE(s1_.empty());

    s1_.push(2);
    s0.push(2);
    ASSERT_EQ(s1_.front(), s0.front());
    ASSERT_EQ(s1_.size(), s0.size());
    ASSERT_FALSE(s1_.empty());

    s1_.push(3);
    s0.push(3);
    ASSERT_EQ(s1_.front(), s0.front());
    ASSERT_EQ(s1_.size(), s0.size());
    ASSERT_FALSE(s1_.empty());

    s1_.push(4);
    s0.push(4);
    ASSERT_EQ(s1_.front(), s0.front());
    ASSERT_EQ(s1_.size(), s0.size());
    ASSERT_FALSE(s1_.empty());

    s1_.push(5);
    s0.push(5);
    ASSERT_EQ(s1_.front(), s0.front());
    ASSERT_EQ(s1_.size(), s0.size());
    ASSERT_FALSE(s1_.empty());

    s1_.pop();
    s0.pop();
    ASSERT_EQ(s1_.front(), s0.front());
    ASSERT_EQ(s1_.size(), s0.size());
    ASSERT_FALSE(s1_.empty());

    s1_.pop();
    s0.pop();
    ASSERT_EQ(s1_.front(), s0.front());
    ASSERT_EQ(s1_.size(), s0.size());
    ASSERT_FALSE(s1_.empty());

    s1_.pop();
    s0.pop();
    ASSERT_EQ(s1_.front(), s0.front());
    ASSERT_EQ(s1_.size(), s0.size());
    ASSERT_FALSE(s1_.empty());

    s1_.pop();
    s0.pop();
    ASSERT_EQ(s1_.front(), s0.front());
    ASSERT_EQ(s1_.size(), s0.size());
    ASSERT_FALSE(s1_.empty());

    s1_.pop();
    s0.pop();
    ASSERT_EQ(s1_.size(), s0.size());
    ASSERT_TRUE(s1_.empty());
    ASSERT_TRUE(s0.empty());
}

// pop, push, size, empty, size
TEST_F(QueueTest, front_pop_push_size_empty) {
    std::queue<int> s0;
    ASSERT_EQ(s1_.size(), 0);
    ASSERT_TRUE(s1_.empty());

    s1_.push(1);
    s0.push(1);
    ASSERT_EQ(s1_.front(), s0.front());
    ASSERT_EQ(s1_.size(), s0.size());
    ASSERT_FALSE(s1_.empty());

    s1_.push(2);
    s0.push(2);
    ASSERT_EQ(s1_.front(), s0.front());
    ASSERT_EQ(s1_.size(), s0.size());
    ASSERT_FALSE(s1_.empty());

    s1_.push(3);
    s0.push(3);
    ASSERT_EQ(s1_.front(), s0.front());
    ASSERT_EQ(s1_.size(), s0.size());
    ASSERT_FALSE(s1_.empty());

    s1_.push(4);
    s0.push(4);
    ASSERT_EQ(s1_.front(), s0.front());
    ASSERT_EQ(s1_.size(), s0.size());
    ASSERT_FALSE(s1_.empty());

    s1_.push(5);
    s0.push(5);
    ASSERT_EQ(s1_.front(), s0.front());
    ASSERT_EQ(s1_.size(), s0.size());
    ASSERT_FALSE(s1_.empty());

    s1_.pop();
    s0.pop();
    ASSERT_EQ(s1_.front(), s0.front());
    ASSERT_EQ(s1_.size(), s0.size());
    ASSERT_FALSE(s1_.empty());

    s1_.pop();
    s0.pop();
    ASSERT_EQ(s1_.front(), s0.front());
    ASSERT_EQ(s1_.size(), s0.size());
    ASSERT_FALSE(s1_.empty());

    s1_.pop();
    s0.pop();
    ASSERT_EQ(s1_.front(), s0.front());
    ASSERT_EQ(s1_.size(), s0.size());
    ASSERT_FALSE(s1_.empty());

    s1_.pop();
    s0.pop();
    ASSERT_EQ(s1_.front(), s0.front());
    ASSERT_EQ(s1_.size(), s0.size());
    ASSERT_FALSE(s1_.empty());

    s1_.pop();
    s0.pop();
    ASSERT_EQ(s1_.size(), s0.size());
    ASSERT_TRUE(s1_.empty());
    ASSERT_TRUE(s0.empty());
}

// test for s21::queue copy constructor
TEST(Queue, copy_constructor) {
    s21::queue<int> s1;
    s1.push(1);
    s1.push(2);
    s1.push(3);
    s1.push(4);

    s21::queue<int> s0(s1);
    ASSERT_EQ(s1.size(), s0.size());
    ASSERT_EQ(s1.front(), s0.front());
    ASSERT_FALSE(s1.empty());
    ASSERT_FALSE(s0.empty());

    s1.pop();
    s0.pop();
    ASSERT_EQ(s1.size(), s0.size());
    ASSERT_EQ(s1.front(), s0.front());
    ASSERT_FALSE(s1.empty());
    ASSERT_FALSE(s0.empty());

    s1.pop();
    s0.pop();
    ASSERT_EQ(s1.size(), s0.size());
    ASSERT_EQ(s1.front(), s0.front());
    ASSERT_FALSE(s1.empty());
    ASSERT_FALSE(s0.empty());

    s1.pop();
    s0.pop();
    ASSERT_EQ(s1.size(), s0.size());
    ASSERT_EQ(s1.front(), s0.front());
    ASSERT_FALSE(s1.empty());
    ASSERT_FALSE(s0.empty());

    s1.pop();
    s0.pop();
    ASSERT_EQ(s1.size(), s0.size());
    ASSERT_TRUE(s1.empty());
    ASSERT_TRUE(s0.empty());
}

// test for s21::queue move constructor
TEST(Queue, move_constructor) {
    s21::queue<int> s1;
    s1.push(1);
    s1.push(2);
    s1.push(3);
    s1.push(4);
    s1.push(5);

    s21::queue<int> s0(std::move(s1));
    ASSERT_EQ(s1.size(), 0);
    ASSERT_EQ(s0.size(), 5);
    ASSERT_TRUE(s1.empty());
    ASSERT_FALSE(s0.empty());

    ASSERT_EQ(s0.front(), 1);
    s0.pop();
    ASSERT_EQ(s0.front(), 2);
    s0.pop();
    ASSERT_EQ(s0.front(), 3);
    s0.pop();
    ASSERT_EQ(s0.front(), 4);
    s0.pop();
    ASSERT_EQ(s0.front(), 5);
    s0.pop();
    ASSERT_TRUE(s0.empty());
}

// s21::queue constructor tests
TEST(Queue, constructor) {
    s21::queue<int> s0;
    ASSERT_EQ(s0.size(), 0);
    ASSERT_TRUE(s0.empty());
}

// s21::queue copy assignment tests
TEST(Queue, copy_assignment) {
    s21::queue<int> s1;
    s1.push(1);
    s1.push(2);
    s1.push(3);
    s1.push(4);

    s21::queue<int> s0;
    s0 = s1;
    ASSERT_EQ(s1.size(), s0.size());
    ASSERT_EQ(s1.front(), s0.front());
    ASSERT_FALSE(s1.empty());
    ASSERT_FALSE(s0.empty());

    s1.pop();
    s0.pop();
    ASSERT_EQ(s1.size(), s0.size());
    ASSERT_EQ(s1.front(), s0.front());
    ASSERT_FALSE(s1.empty());
    ASSERT_FALSE(s0.empty());

    s1.pop();
    s0.pop();
    ASSERT_EQ(s1.size(), s0.size());
    ASSERT_EQ(s1.front(), s0.front());
    ASSERT_FALSE(s1.empty());
    ASSERT_FALSE(s0.empty());

    s1.pop();
    s0.pop();
    ASSERT_EQ(s1.size(), s0.size());
    ASSERT_EQ(s1.front(), s0.front());
    ASSERT_FALSE(s1.empty());
    ASSERT_FALSE(s0.empty());

    s1.pop();
    s0.pop();
    ASSERT_EQ(s1.size(), s0.size());
    ASSERT_TRUE(s1.empty());
    ASSERT_TRUE(s0.empty());
}

// s21::queue move assignment tests
TEST(Queue, move_assignment) {
    s21::queue<int> s1;
    s1.push(1);
    s1.push(2);
    s1.push(3);
    s1.push(4);
    s1.push(5);

    s21::queue<int> s0;
    s0 = std::move(s1);
    ASSERT_EQ(s1.size(), 0);
    ASSERT_EQ(s0.size(), 5);
    ASSERT_TRUE(s1.empty());
    ASSERT_FALSE(s0.empty());

    ASSERT_EQ(s0.front(), 1);
    s0.pop();
    ASSERT_EQ(s0.front(), 2);
    s0.pop();
    ASSERT_EQ(s0.front(), 3);
    s0.pop();
    ASSERT_EQ(s0.front(), 4);
    s0.pop();
    ASSERT_EQ(s0.front(), 5);
    s0.pop();
    ASSERT_TRUE(s0.empty());
}

// test for s21::queue back method
TEST(Queue, back) {
    s21::queue<int> s0;
    s0.push(1);
    s0.push(2);
    s0.push(3);
    s0.push(4);
    s0.push(5);

    ASSERT_EQ(s0.back(), 5);
    s0.pop();
    ASSERT_EQ(s0.back(), 5);
    s0.pop();
    ASSERT_EQ(s0.back(), 5);
    s0.pop();
    ASSERT_EQ(s0.back(), 5);
    s0.pop();
    ASSERT_EQ(s0.back(), 5);
    s0.pop();
    ASSERT_TRUE(s0.empty());
}
