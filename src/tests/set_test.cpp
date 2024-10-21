#include <set>

#include "test.h"

template class s21::set<int>;

TEST(set, ConstructorDefaultSet) {
  s21::set<int> myEmptySet;
  std::set<int> origEmptySet;
  EXPECT_EQ(myEmptySet.empty(), origEmptySet.empty());
}

TEST(set, ConstructorInitializerSet) {
  s21::set<int> mySet({'x', 'b', 'z', 'y'});
  std::set<int> origSet({'x', 'b', 'z', 'y'});
  EXPECT_EQ(mySet.size(), origSet.size());
  auto myIt = mySet.begin();
  auto origIt = origSet.begin();
  for (; myIt != mySet.end(); ++myIt, ++origIt) {
    EXPECT_TRUE(*origIt == *myIt);
  }
}

TEST(set, ConstructorInitializer2Set) {
  s21::set<int> mySet = {};
  std::set<int> origSet = {};
  EXPECT_EQ(mySet.size(), origSet.size());
  auto myIt = mySet.begin();
  auto origIt = origSet.begin();
  for (; myIt != mySet.end(); ++myIt, ++origIt) {
    EXPECT_TRUE(*origIt == *myIt);
  }
}

TEST(set, ConstructorCopySet) {
  const s21::set<int> mySet({1, 2, 3, 4, 5});
  const std::set<int> origSet({1, 2, 3, 4, 5});
  s21::set<int> mySetCopy = mySet;
  std::set<int> origSetCopy = origSet;
  EXPECT_EQ(mySetCopy.size(), origSetCopy.size());
  auto myIt = mySetCopy.begin();
  auto origIt = origSetCopy.begin();
  for (; myIt != mySetCopy.end(); ++myIt, ++origIt) {
    EXPECT_TRUE(*origIt == *myIt);
  }
}

TEST(set, OperatorCopySet) {
  const s21::set<int> mySet({1, 2, 3, 4, 5});
  const std::set<int> origSet({1, 2, 3, 4, 5});
  s21::set<int> mySetCopy;
  std::set<int> origSetCopy;
  mySetCopy = mySet;
  origSetCopy = origSet;
  EXPECT_EQ(mySetCopy.size(), origSetCopy.size());
  auto myIt = mySetCopy.begin();
  auto origIt = origSetCopy.begin();
  for (; myIt != mySetCopy.end(); ++myIt, ++origIt) {
    EXPECT_TRUE(*origIt == *myIt);
  }
}

TEST(set, ConstructorMoveSet) {
  s21::set<int> mySet({1, 2, 3, 4, 5});
  std::set<int> origSet({1, 2, 3, 4, 5});
  s21::set<int> mySetCopy = std::move(mySet);
  std::set<int> origSetCopy = std::move(origSet);
  EXPECT_EQ(mySet.size(), origSet.size());
  EXPECT_EQ(mySetCopy.size(), origSetCopy.size());
  auto myIt = mySetCopy.begin();
  auto origIt = origSetCopy.begin();
  for (; myIt != mySetCopy.end(); ++myIt, ++origIt) {
    EXPECT_TRUE(*origIt == *myIt);
  }
}

TEST(set, OperatorMoveSet) {
  s21::set<int> mySet({1, 2, 3, 4, 5});
  std::set<int> origSet({1, 2, 3, 4, 5});
  s21::set<int> mySetCopy;
  std::set<int> origSetCopy;
  mySetCopy = std::move(mySet);
  origSetCopy = std::move(origSet);
  EXPECT_EQ(mySet.size(), origSet.size());
  EXPECT_EQ(mySetCopy.size(), origSetCopy.size());
  auto myIt = mySetCopy.begin();
  auto origIt = origSetCopy.begin();
  for (; myIt != mySetCopy.end(); ++myIt, ++origIt) {
    EXPECT_TRUE(*origIt == *myIt);
  }
}

TEST(set, SetIteratorsSet) {
  s21::set<int> mySet({1, 2, 3, 4, 5});
  std::set<int> origSet({1, 2, 3, 4, 5});
  auto myIt = mySet.begin();
  auto origIt = origSet.begin();
  EXPECT_TRUE(*origIt == *myIt);
}

TEST(set, CapacitySet) {
  s21::set<int> myEmptySet;
  std::set<int> origEmptySet;
  EXPECT_EQ(myEmptySet.empty(), origEmptySet.empty());
  EXPECT_EQ(myEmptySet.size(), origEmptySet.size());
  myEmptySet.insert('b');
  origEmptySet.insert('c');
  EXPECT_EQ(myEmptySet.empty(), origEmptySet.empty());
  EXPECT_EQ(myEmptySet.size(), origEmptySet.size());
}

TEST(set, ClearSet) {
  s21::set<int> myEmptySet;
  std::set<int> origEmptySet;
  myEmptySet.clear();
  origEmptySet.clear();
  EXPECT_EQ(myEmptySet.empty(), origEmptySet.empty());
  EXPECT_EQ(myEmptySet.size(), origEmptySet.size());
  myEmptySet.insert('a');
  origEmptySet.insert('b');
  EXPECT_EQ(myEmptySet.empty(), origEmptySet.empty());
  EXPECT_EQ(myEmptySet.size(), origEmptySet.size());
  myEmptySet.clear();
  origEmptySet.clear();
  EXPECT_EQ(myEmptySet.empty(), origEmptySet.empty());
  EXPECT_EQ(myEmptySet.size(), origEmptySet.size());
}

TEST(set, InsertSet) {
  s21::set<int> mySet({1, 2, 3, 4, 5});
  std::set<int> origSet({1, 2, 3, 4, 5});
  auto myPr = mySet.insert(6);
  auto origPr = origSet.insert(6);
  EXPECT_TRUE(myPr.second == origPr.second);
  EXPECT_TRUE(*myPr.first == *origPr.first);
  myPr = mySet.insert(7);
  origPr = origSet.insert(7);
  EXPECT_TRUE(myPr.second == origPr.second);
  EXPECT_TRUE(*myPr.first == *origPr.first);
}

TEST(set, EraseSet) {
  s21::set<int> mySet({5, 4, 3, 2, 7, 8, 9});
  std::set<int> origSet({5, 4, 3, 2, 7, 8, 9});
  auto size = mySet.size();
  mySet.erase(mySet.end());
  auto new_size = mySet.size();
  EXPECT_EQ(size, new_size);
  mySet.erase(mySet.begin());
  origSet.erase(origSet.begin());
  auto myIt = mySet.begin();
  auto origIt = origSet.begin();
  for (; myIt != mySet.end(); ++myIt, ++origIt) {
    EXPECT_TRUE(*origIt == *myIt);
  }
}

TEST(set, SwapSet) {
  s21::set<int> mySet({1});
  s21::set<int> mySwapSet({3, 4, 5});

  mySet.swap(mySwapSet);
  EXPECT_EQ(mySet.size(), 3);
  EXPECT_EQ(mySwapSet.size(), 1);
  auto mySetIt = mySet.begin();
  auto mySwapSet_it = mySwapSet.begin();
  EXPECT_EQ(*mySetIt, 3);
  EXPECT_EQ(*mySwapSet_it, 1);
}

TEST(set, MergeSet) {
  s21::set<int> mySet({1});
  s21::set<int> myMergeSet({3, 4, 5});
  mySet.merge(myMergeSet);

  std::set<int> origSet({1});
  std::set<int> origMergeSet({3, 4, 5});
  origSet.merge(origMergeSet);
  auto myIt = mySet.begin();
  auto origIt = origSet.begin();
  for (; myIt != mySet.end(); ++myIt, ++origIt) {
    EXPECT_TRUE(*origIt == *myIt);
  }
  EXPECT_EQ(origSet.size(), mySet.size());
  EXPECT_EQ(myMergeSet.size(), origMergeSet.size());
}

TEST(set, FindSet) {
  s21::set<int> mySet({1, 2, 3, 4, 5});
  std::set<int> origSet({1, 2, 3, 4, 5});
  auto myIt = mySet.find(4);
  auto origIt = origSet.find(4);
  EXPECT_TRUE(*origIt == *myIt);
}

TEST(set, ContainsSet) {
  s21::set<int> mySet({1, 2, 3, 4, 5});
  EXPECT_FALSE(mySet.contains(8));
  EXPECT_TRUE(mySet.contains(2));
}

TEST(set, Find) {
  s21::set<int> s1({1, 2, 3});
  auto itEnd = s1.end();
  auto itAns = s1.begin();
  ++itAns;
  auto it1 = s1.find(2);
  EXPECT_FALSE(it1 == itEnd);
  EXPECT_TRUE(it1 == itAns);
  it1 = s1.find(6);
  EXPECT_TRUE(it1 == itEnd);
}

TEST(set, ConstFind) {
  const s21::set<int> s1({1, 2, 3});
  auto itEnd = s1.end();
  auto itAns = s1.begin();
  ++itAns;
  auto it1 = s1.find(2);
  EXPECT_FALSE(it1 == itEnd);
  EXPECT_TRUE(it1 == itAns);
  it1 = s1.find(6);
  EXPECT_TRUE(it1 == itEnd);
}

TEST(set, MaxSize) {
  s21::set<int> s1({1, 2, 3});
  s21::set<int> s2({1, 2, 3});
  EXPECT_EQ(s1.max_size(), s2.max_size());
}

TEST(set, InsertMany) {
  s21::set<int> s1({1, 2, 3});
  s1.insert_many(4, 5, 6);
  EXPECT_TRUE(s1.contains(4));
  EXPECT_TRUE(s1.contains(5));
  EXPECT_TRUE(s1.contains(6));
}