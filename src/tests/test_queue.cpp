#include "../s21_queue.hpp"
#include "gtest/gtest.h"

class QueueTest : public ::testing::Test {
  protected:
    void SetUp() override {
    }

    s21::Queue<int> s0_{1, 2, 3, 4, 5};
    s21::Queue<int> s1_{};
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
    s21::Queue copy(s0_);
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
    s21::Queue moved(std::move(s0_));
    ASSERT_EQ(moved.size(), 5);
    ASSERT_EQ(moved.back(), 5);
}

TEST_F(QueueTest, copy_assignment) {
    s21::Queue<int> copy;
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
    s21::Queue<int> moved;
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

TEST_F(QueueTest, push_refref_move) {
    s21::Queue<std::vector<int>> qv;
    std::vector<int> x{1, 2, 3, 4, 5};

    qv.push(std::move(x));

    ASSERT_EQ(x.data(), nullptr);
}

TEST_F(QueueTest, emplace) {
    using std::string;
    struct S {
        int id;
        string name;
        string surname;

        S(int i, const std::string &n, const std::string &s)
            : id{i}, name{n}, surname{s} {
        }
    };

    s21::Queue<S> adaptor;
    int num = 69;
    string name = "Billy";
    string surname = "Herrington";
    const S &s = adaptor.emplace(num, "Billy", "Herrington");

    ASSERT_EQ(s.id, num);
    ASSERT_EQ(s.name, name);
    ASSERT_EQ(s.surname, surname);
}
