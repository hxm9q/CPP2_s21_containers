#include <set>

#include "test.h"

template class s21::multiset<int>;

TEST(multiset, ConstructorDefaultSet) {
  s21::multiset<int> myEmptySet;
  std::multiset<int> origEmptySet;
  EXPECT_EQ(myEmptySet.empty(), origEmptySet.empty());
}

TEST(multiset, ConstructorInitializerSet) {
  s21::multiset<int> mySet({6, 2, 2, 9, 9, 9, 7, 7, 7, 7});
  std::multiset<int> origSet({6, 2, 2, 9, 9, 9, 7, 7, 7, 7});
  EXPECT_EQ(mySet.size(), origSet.size());
  auto myIt = mySet.begin();
  auto origIt = origSet.begin();
  for (size_t i = 0, n = origSet.size(); i < n; ++i, ++myIt, ++origIt) {
    EXPECT_TRUE(*origIt == *myIt);
  }
}

TEST(multiset, ConstructorInitializer2Set) {
  s21::multiset<int> mySet = {};
  std::multiset<int> origSet = {};
  EXPECT_EQ(mySet.size(), origSet.size());
  auto myIt = mySet.begin();
  auto origIt = origSet.begin();
  for (size_t i = 0, n = origSet.size(); i < n; ++i, ++myIt, ++origIt) {
    EXPECT_TRUE(*origIt == *myIt);
  }
}

TEST(multiset, ConstructorCopySet) {
  const s21::multiset<int> mySet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  const std::multiset<int> origSet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  s21::multiset<int> mySetCopy = mySet;
  std::multiset<int> origSetCopy = origSet;
  EXPECT_EQ(mySetCopy.size(), origSetCopy.size());
  auto myIt = mySetCopy.begin();
  auto origIt = origSetCopy.begin();
  for (size_t i = 0, n = origSet.size(); i < n; ++i, ++myIt, ++origIt) {
    EXPECT_TRUE(*origIt == *myIt);
  }
}

TEST(multiset, OperatorCopySet) {
  const s21::multiset<int> mySet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  const std::multiset<int> origSet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  s21::multiset<int> mySetCopy;
  std::multiset<int> origSetCopy;
  mySetCopy = mySet;
  origSetCopy = origSet;
  EXPECT_EQ(mySetCopy.size(), origSetCopy.size());
  auto myIt = mySetCopy.begin();
  auto origIt = origSetCopy.begin();
  for (size_t i = 0, n = origSet.size(); i < n; ++i, ++myIt, ++origIt) {
    EXPECT_TRUE(*origIt == *myIt);
  }
}

TEST(multiset, ConstructorMoveSet) {
  s21::multiset<int> mySet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  std::multiset<int> origSet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  s21::multiset<int> mySetCopy = std::move(mySet);
  std::multiset<int> origSetCopy = std::move(origSet);
  EXPECT_EQ(mySet.size(), origSet.size());
  EXPECT_EQ(mySetCopy.size(), origSetCopy.size());
  auto myIt = mySetCopy.begin();
  auto origIt = origSetCopy.begin();
  for (size_t i = 0, n = origSetCopy.size(); i < n; ++i, ++myIt, ++origIt) {
    EXPECT_TRUE(*origIt == *myIt);
  }
}

TEST(multiset, OperatorMoveSet) {
  s21::multiset<int> mySet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  std::multiset<int> origSet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  s21::multiset<int> mySetCopy;
  std::multiset<int> origSetCopy;
  mySetCopy = std::move(mySet);
  origSetCopy = std::move(origSet);
  EXPECT_EQ(mySet.size(), origSet.size());
  EXPECT_EQ(mySetCopy.size(), origSetCopy.size());
  auto myIt = mySetCopy.begin();
  auto origIt = origSetCopy.begin();
  for (size_t i = 0, n = origSetCopy.size(); i < n; ++i, ++myIt, ++origIt) {
    EXPECT_TRUE(*origIt == *myIt);
  }
}

TEST(multiset, SetIteratorsSet) {
  s21::multiset<int> mySet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  std::multiset<int> origSet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  auto myIt = mySet.begin();
  auto origIt = origSet.begin();
  EXPECT_TRUE(*origIt == *myIt);
}

TEST(multiset, CapacitySet) {
  s21::multiset<int> myEmptySet;
  std::multiset<int> origEmptySet;
  EXPECT_EQ(myEmptySet.empty(), origEmptySet.empty());
  EXPECT_EQ(myEmptySet.size(), origEmptySet.size());
  myEmptySet.insert(2);
  origEmptySet.insert(2);
  EXPECT_EQ(myEmptySet.empty(), origEmptySet.empty());
  EXPECT_EQ(myEmptySet.size(), origEmptySet.size());
}

TEST(multiset, ClearSet) {
  s21::multiset<int> myEmptySet;
  std::multiset<int> origEmptySet;
  myEmptySet.clear();
  origEmptySet.clear();
  EXPECT_EQ(myEmptySet.empty(), origEmptySet.empty());
  EXPECT_EQ(myEmptySet.size(), origEmptySet.size());
  myEmptySet.insert(1);
  origEmptySet.insert(1);
  EXPECT_EQ(myEmptySet.empty(), origEmptySet.empty());
  EXPECT_EQ(myEmptySet.size(), origEmptySet.size());
  myEmptySet.clear();
  origEmptySet.clear();
  EXPECT_EQ(myEmptySet.empty(), origEmptySet.empty());
  EXPECT_EQ(myEmptySet.size(), origEmptySet.size());
}

TEST(multiset, InsertSet) {
  s21::multiset<int> mySet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  std::multiset<int> origSet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  mySet.insert(6);
  origSet.insert(6);
  mySet.insert(7);
  origSet.insert(7);
  EXPECT_EQ(mySet.size(), origSet.size());
  auto myIt = mySet.begin();
  auto origIt = origSet.begin();
  for (size_t i = 0, n = origSet.size(); i < n; ++i, ++myIt, ++origIt) {
    EXPECT_TRUE(*origIt == *myIt);
  }
}

TEST(multiset, EraseSet) {
  s21::multiset<int> mySet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  std::multiset<int> origSet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  EXPECT_EQ(mySet.size(), origSet.size());
  auto myIt = mySet.begin();
  auto origIt = origSet.begin();
  for (size_t i = 0; i < 4; ++i, ++myIt, ++origIt);
  mySet.erase(myIt);
  origSet.erase(origIt);
  EXPECT_EQ(mySet.size(), origSet.size());
  myIt = mySet.begin();
  origIt = origSet.begin();
  for (size_t i = 0, n = origSet.size(); i < n; ++i, ++myIt, ++origIt) {
    EXPECT_TRUE(*origIt == *myIt);
  }
}
