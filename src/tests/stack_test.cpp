#include <stack>

#include "test.h"

template class s21::stack<int>;

TEST(Stack, Constructor_Default) {
  s21::stack<int> our_stack;
  std::stack<int> std_stack;
  EXPECT_EQ(our_stack.empty(), std_stack.empty());
}

TEST(Stack, Constructor_List) {
  s21::stack<int> our_stack({1, 2, 3});
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  EXPECT_EQ(our_stack.top(), std_stack.top());
}

TEST(Stack, Constructor_Copy) {
  s21::stack<int> our_stack({1, 2, 3});
  s21::stack<int> our_copy(our_stack);
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  std::stack<int> std_copy(std_stack);
  EXPECT_EQ(our_copy.top(), std_copy.top());
}

TEST(Stack, Constructor_Move) {
  s21::stack<int> our_stack({1, 2, 3});
  s21::stack<int> our_move(std::move(our_stack));
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  std::stack<int> std_move(std::move(std_stack));
  EXPECT_EQ(our_move.top(), std_move.top());
  EXPECT_EQ(our_stack.empty(), std_stack.empty());
}

TEST(Stack, Operator_Move_1) {
  s21::stack<int> our_stack_int({1, 2, 3});
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  s21::stack<int> our_stack_empty;
  std::stack<int> std_stack_empty;
  our_stack_empty = std::move(our_stack_int);
  std_stack_empty = std::move(std_stack_int);
  EXPECT_EQ(our_stack_empty.top(), std_stack_empty.top());
  EXPECT_EQ(our_stack_int.empty(), std_stack_int.empty());
}

TEST(Stack, Operator_Move_2) {
  s21::stack<int> int_s({1, 2, 3});
  s21::stack<int> new_s({4, 5});
  new_s = std::move(int_s);
  EXPECT_EQ(new_s.top(), 3);
  EXPECT_TRUE(int_s.empty());
}

TEST(Stack, Top) {
  s21::stack<int> our_stack_int({1, 2, 3});
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  EXPECT_EQ(our_stack_int.top(), std_stack_int.top());
}

TEST(Stack, Empty) {
  s21::stack<int> our_stack_int({1, 2, 3});
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  EXPECT_EQ(our_stack_int.empty(), std_stack_int.empty());
  s21::stack<int> our_stack_empty;
  std::stack<int> std_stack_empty;
  EXPECT_EQ(our_stack_empty.empty(), std_stack_empty.empty());
}

TEST(Stack, size) {
  s21::stack<int> our_stack_int({1, 2, 3});
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  EXPECT_EQ(our_stack_int.size(), std_stack_int.size());
  s21::stack<int> our_stack_empty;
  std::stack<int> std_stack_empty;
  EXPECT_EQ(our_stack_empty.size(), std_stack_empty.size());
}

TEST(Stack, Push) {
  s21::stack<int> our_stack_int;
  our_stack_int.push(1);
  our_stack_int.push(2);
  our_stack_int.push(3);
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  EXPECT_EQ(our_stack_int.top(), std_stack_int.top());
}

TEST(Stack, Pop) {
  s21::stack<int> our_stack_int;
  our_stack_int.push(1);
  our_stack_int.push(2);
  our_stack_int.push(3);
  our_stack_int.pop();
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  std_stack_int.pop();
  EXPECT_EQ(our_stack_int.top(), std_stack_int.top());
  our_stack_int.pop();
  our_stack_int.pop();
  std_stack_int.pop();
  std_stack_int.pop();
  EXPECT_EQ(our_stack_int.empty(), std_stack_int.empty());
}

TEST(Stack, Swap) {
  s21::stack<int> our_stack_int({1, 2, 3});
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  s21::stack<int> our_stack_empty;
  std::stack<int> std_stack_empty;
  our_stack_empty.swap(our_stack_int);
  std_stack_empty.swap(std_stack_int);
  EXPECT_EQ(our_stack_empty.top(), std_stack_empty.top());
  EXPECT_EQ(our_stack_int.empty(), std_stack_int.empty());
}

TEST(Stack, InsertManyFront) {
  s21::stack<int> our_stack_int;
  our_stack_int.insert_many_front(1, 2, 3);
  EXPECT_EQ(our_stack_int.top(), 3);
}

TEST(Stack, Begin) {
  s21::stack<int> s({1, 2, 3});
  auto iter = s.begin();
  iter++;  // cppcheck-suppress postfixOperator
  EXPECT_EQ(*iter, 2);
}

TEST(Stack, IteratorEqual) {
  s21::stack<int> s({1, 2, 3});
  EXPECT_TRUE(s.begin() == s.begin());
  EXPECT_FALSE(s.begin() == s.end());
}

TEST(Stack, IteratorNotEqual) {
  s21::stack<int> s({1, 2, 3});
  EXPECT_TRUE(s.begin() != s.end());
  EXPECT_FALSE(s.begin() != s.begin());
}

TEST(Stack, PopThrow) {
  s21::stack<int> s;
  EXPECT_THROW(s.pop(), std::out_of_range);
}

TEST(Stack, TopThrow) {
  s21::stack<int> s;
  EXPECT_THROW(s.top(), std::out_of_range);
}

TEST(Stack, SwapThrow) {
  s21::stack<int> s({1, 2, 3});
  s21::queue<int> q({3, 2, 1});
  EXPECT_THROW(s.swap(q), std::invalid_argument);
}