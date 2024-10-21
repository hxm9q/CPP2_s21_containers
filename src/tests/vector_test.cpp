#include "test.h"

TEST(VectorTest, VecBaseConstruct) {
  std::cout << "\n ============== TEST: S21_VECTOR ============== \n"
            << std::endl;
  s21::Vector<int> Vec;
  ASSERT_EQ(Vec.size(), (unsigned long)0);
}

TEST(VectorTest, VecLSizeConstruct1) {
  s21::Vector<int> Vec(5);
  ASSERT_EQ(Vec.capacity(), (unsigned long)5);
}

TEST(VectorTest, VecLSizeConstruct2) {
  s21::Vector<int> Vec(0);
  ASSERT_EQ(Vec.size(), (unsigned long)0);
}

TEST(VectorTest, VecListConstruct) {
  s21::Vector<int> Vec({1, 2, 3, 4, 5});
  ASSERT_EQ(Vec.size(), (unsigned long)5);
  ASSERT_EQ(Vec[2], 3);
}

TEST(VectorTest, VecVecConstruct1) {
  s21::Vector<int> Vec({1, 2, 3, 4, 5});
  s21::Vector<int> Vec1(Vec);
  ASSERT_EQ(Vec1.size(), (unsigned long)5);
  ASSERT_EQ(Vec1[2], 3);
}

TEST(VectorTest, VecVecConstruct2) {
  s21::Vector<int> Vec({1, 2, 3, 4, 5});
  s21::Vector<int> Vec1(std::move(Vec));
  ASSERT_EQ(Vec1.size(), (unsigned long)5);
  ASSERT_EQ(Vec1[2], 3);
}

TEST(VectorTest, EqualsOp1) {
  s21::Vector<int> Vec({1, 2, 3, 4, 5});
  s21::Vector<int> Vec1;
  Vec1 = Vec;
  ASSERT_EQ(Vec1[2], 3);
}

TEST(VectorTest, EqualsOp2) {
  s21::Vector<int> Vec({1, 2, 3, 4, 5});
  s21::Vector<int> Vec1;
  Vec1 = std::move(Vec);
  ASSERT_EQ(Vec1[2], 3);
}

TEST(VectorTest, VecAt) {
  s21::Vector<int> Vec({1, 2, 3, 4, 5});
  ASSERT_EQ(Vec.at(2), 3);
}

TEST(VectorTest, VecBr) {
  s21::Vector<int> Vec({1, 2, 3, 4, 5});
  int check = Vec[2];
  ASSERT_EQ(check, 3);
}

TEST(VectorTest, VecData) {
  s21::Vector<int> Vec({1, 2, 3, 4, 5});
  ASSERT_EQ(*Vec.data(), 1);
}

TEST(VectorTest, VecFront) {
  s21::Vector<int> Vec({1, 2, 3, 4, 5});
  std::vector<int> Vec1({1, 2, 3, 4, 5});
  ASSERT_EQ(Vec1.front(), Vec.front());
}

TEST(VectorTest, VecBack) {
  s21::Vector<int> Vec({1, 2, 3, 4, 5});
  std::vector<int> Vec1({1, 2, 3, 4, 5});
  ASSERT_EQ(Vec1.back(), Vec.back());
}

TEST(VectorTest, VecBegin) {
  s21::Vector<int> Vec({1, 2, 3, 4, 5});
  ASSERT_EQ(*Vec.begin(), 1);
}

TEST(VectorTest, VecEnd) {
  s21::Vector<int> Vec({1, 2, 3, 4, 5});
  std::vector<int> Vec1({1, 2, 3, 4, 5});
  ASSERT_EQ(*Vec.end(), *Vec.end());
}

TEST(VectorTest, VecSize) {
  s21::Vector<int> Vec({1, 2, 3, 4, 5});
  std::vector<int> Vec1({1, 2, 3, 4, 5});
  ASSERT_EQ(Vec1.size(), Vec.size());
}

TEST(VectorTest, VecEmpty1) {
  s21::Vector<int> Vec({1, 2, 3, 4, 5});
  ASSERT_EQ(Vec.empty(), false);
}

TEST(VectorTest, VecEmpty2) {
  s21::Vector<int> Vec;
  ASSERT_EQ(Vec.empty(), true);
}

TEST(VectorTest, VecReserve) {
  s21::Vector<int> Vec({1, 2, 3, 4, 5});
  Vec.reserve(8);
  ASSERT_EQ(Vec.size(), (unsigned long)5);
}

TEST(VectorTest, VecCapacity1) {
  s21::Vector<int> Vec(1);
  ASSERT_EQ(Vec.capacity(), (unsigned long)1);
}

TEST(VectorTest, VecSwap) {
  s21::Vector<int> Vec({1, 1, 1, 1, 1});
  s21::Vector<int> Vec1({2, 2, 2, 2, 2});
  Vec1.swap(Vec);
  ASSERT_EQ(Vec1[1], 1);
  ASSERT_EQ(Vec[2], 2);
}

TEST(VectorTest, VecPrint) { s21::Vector<int> Vec({1, 1, 1, 1, 1}); }

TEST(VectorTest, VecClear) {
  s21::Vector<int> Vec({1, 1, 1, 1, 1});
  Vec.clear();
  ASSERT_EQ(Vec.size(), (unsigned long)0);
}

TEST(VectorTest, VecShrink_to_fit) {
  s21::Vector<int> Vec({1, 1, 1, 1, 1});
  Vec.shrink_to_fit();
}

TEST(VectorTest, VecInsert) {
  s21::Vector<int> Vec({1, 2, 3, 4, 5});
  auto res1 = Vec.insert(Vec.begin(), 1);
  ASSERT_EQ(*res1, 1);
  auto res2 = Vec.insert(Vec.begin(), -11);
  ASSERT_EQ(*res2, -11);
  auto res3 = Vec.insert(Vec.end(), 1000);
  ASSERT_EQ(*res3, 1000);
  auto res4 = Vec.insert(Vec.end(), 6);
  ASSERT_EQ(*res4, 6);
  ASSERT_EQ(Vec.size(), (unsigned long)9);
}

TEST(VectorTest, VecErase) {
  s21::Vector<int> Vec({1, 2, 3, 4, 5});
  Vec.erase(Vec.begin());
  ASSERT_EQ(Vec[0], 2);
  ASSERT_EQ(Vec.size(), (unsigned long)4);
}