#include <map>

#include "test.h"

template class s21::Map<int, int>;

TEST(Map, ConstructorDefaultMap) {
  s21::Map<int, int> myEmptyMap;
  std::map<int, int> origEmptyMap;
  EXPECT_EQ(myEmptyMap.empty(), origEmptyMap.empty());
}

TEST(Map, ConstructorInitializerMap) {
  s21::Map<int, int> myMap({{1, 'x'}, {2, 'b'}, {3, 'z'}, {4, 'y'}});
  std::map<int, int> origMap({{1, 'x'}, {2, 'b'}, {3, 'z'}, {4, 'y'}});
  EXPECT_EQ(myMap.size(), origMap.size());
  auto myIt = myMap.begin();
  auto origIt = origMap.begin();
  for (; myIt != myMap.end(); ++myIt, ++origIt) {
    EXPECT_TRUE((*myIt).first == (*origIt).first);
    EXPECT_TRUE((*myIt).second == (*origIt).second);
  }
}

TEST(Map, ConstructorInitializer2Map) {
  s21::Map<int, int> myMap = {};
  std::map<int, int> origMap = {};
  EXPECT_EQ(myMap.size(), origMap.size());
  auto myIt = myMap.begin();
  auto origIt = origMap.begin();
  for (; myIt != myMap.end(); ++myIt, ++origIt) {
    EXPECT_TRUE((*myIt).first == (*origIt).first);
    EXPECT_TRUE((*myIt).second == (*origIt).second);
  }
}

TEST(Map, ConstructorCopyMap) {
  const s21::Map<int, int> myMap({{1, 2}, {3, 4}, {5, 6}});
  const std::map<int, int> origMap({{1, 2}, {3, 4}, {5, 6}});
  s21::Map<int, int> myMapCopy = myMap;
  std::map<int, int> origMapCopy = origMap;
  EXPECT_EQ(myMapCopy.size(), origMapCopy.size());
  auto myIt = myMapCopy.begin();
  auto origIt = origMapCopy.begin();
  for (; myIt != myMapCopy.end(); ++myIt, ++origIt) {
    EXPECT_TRUE((*myIt).first == (*origIt).first);
    EXPECT_TRUE((*myIt).second == (*origIt).second);
  }
}

TEST(Map, ConstructorMoveMap) {
  s21::Map<int, int> myMap({{1, 2}, {3, 4}, {5, 6}});
  std::map<int, int> origMap({{1, 2}, {3, 4}, {5, 6}});
  s21::Map<int, int> myMapCopy = std::move(myMap);
  std::map<int, int> origMapCopy = std::move(origMap);
  EXPECT_EQ(myMap.size(), origMap.size());
  EXPECT_EQ(myMapCopy.size(), origMapCopy.size());
  auto myIt = myMapCopy.begin();
  auto origIt = origMapCopy.begin();
  for (; myIt != myMapCopy.end(); ++myIt, ++origIt) {
    EXPECT_TRUE((*myIt).first == (*origIt).first);
    EXPECT_TRUE((*myIt).second == (*origIt).second);
  }
}

TEST(map, MapOperator) {
  s21::Map<int, int> myMap({{10, 1}, {20, 2}, {30, 3}});
  std::map<int, int> origMap({{10, 1}, {20, 2}, {30, 3}});
  myMap[10] = 11;
  origMap[10] = 11;
  origMap[20] = 22;
  EXPECT_TRUE(myMap[10] == origMap[10]);
  EXPECT_FALSE(myMap[20] == origMap[20]);
  EXPECT_TRUE(myMap[30] == origMap[30]);
}

TEST(map, MapAtOperatorException) {
  s21::Map<int, int> myMap({{10, 1}, {20, 2}, {30, 3}});
  EXPECT_THROW(myMap.at('g') = 1, std::out_of_range);
}

TEST(Map, MapAtOperator) {
  s21::Map<int, int> myMap({{10, 1}, {20, 2}, {30, 3}});
  std::map<int, int> origMap({{10, 1}, {20, 2}, {30, 3}});
  myMap.at(10) = 11;
  origMap.at(10) = 11;
  origMap.at(20) = 22;
  EXPECT_TRUE(myMap[10] == origMap[10]);
  EXPECT_FALSE(myMap[20] == origMap[20]);
  EXPECT_TRUE(myMap[30] == origMap[30]);
}

TEST(Map, MapAtConstOperator) {
  const s21::Map<int, int> myMap({{10, 1}, {20, 2}, {30, 3}});
  const std::map<int, int> origMap({{10, 1}, {20, 2}, {30, 3}});
  EXPECT_TRUE(myMap.at(10) == origMap.at(10));
  EXPECT_TRUE(myMap.at(20) == origMap.at(20));
  EXPECT_TRUE(myMap.at(30) == origMap.at(30));
  EXPECT_ANY_THROW(myMap.at(40));
}

TEST(Map, MapCapacity) {
  s21::Map<int, int> myMap;
  std::map<int, int> origMap;
  EXPECT_TRUE(myMap.empty() == origMap.empty());
  myMap.insert(10, 1);
  EXPECT_FALSE(myMap.empty() == origMap.empty());
  EXPECT_EQ(myMap.size(), 1);
}

TEST(Map, MapClear) {
  s21::Map<int, int> myMap;
  std::map<int, int> origMap;
  myMap.clear();
  origMap.clear();
  EXPECT_EQ(myMap.empty(), origMap.empty());
  myMap.insert(std::make_pair(1, 1));
  origMap.insert(std::make_pair(1, 1));
  EXPECT_EQ(myMap.empty(), origMap.empty());
  myMap.clear();
  origMap.clear();
  EXPECT_EQ(myMap.empty(), origMap.empty());
}

TEST(Map, MapInsert1) {
  s21::Map<int, int> myMap;
  std::map<int, int> origMap;
  myMap.insert(std::make_pair(1, 'a'));
  myMap.insert(std::make_pair(2, 'a'));
  myMap.insert(std::make_pair(3, 'a'));
  origMap.insert(std::make_pair(1, 'a'));
  origMap.insert(std::make_pair(2, 'a'));
  origMap.insert(std::make_pair(3, 'a'));

  auto myIt = myMap.begin();
  auto origIt = origMap.begin();
  for (; myIt != myMap.end(); ++myIt, ++origIt) {
    EXPECT_TRUE((*myIt).first == (*origIt).first);
    EXPECT_TRUE((*myIt).second == (*origIt).second);
  }

  auto pr1 = myMap.insert(std::make_pair(1, 'a'));
  auto pr2 = origMap.insert(std::make_pair(1, 'a'));
  EXPECT_TRUE(pr1.second == pr2.second);
}

TEST(Map, MapInsert2) {
  s21::Map<int, int> myMap;
  std::map<int, int> origMap;
  myMap.insert(1, 'a');
  myMap.insert(2, 'a');
  myMap.insert(3, 'a');
  origMap.insert(std::make_pair(1, 'a'));
  origMap.insert(std::make_pair(2, 'a'));
  origMap.insert(std::make_pair(3, 'a'));

  auto myIt = myMap.begin();
  auto origIt = origMap.begin();
  for (; myIt != myMap.end(); ++myIt, ++origIt) {
    EXPECT_TRUE((*myIt).first == (*origIt).first);
    EXPECT_TRUE((*myIt).second == (*origIt).second);
  }

  auto pr1 = myMap.insert(1, 'a');
  auto pr2 = origMap.insert(std::make_pair(1, 'a'));
  EXPECT_TRUE(pr1.second == pr2.second);
}

TEST(Map, MapInsert3) {
  s21::Map<int, int> myMap;
  std::map<int, int> origMap;
  myMap.insert(1, 'a');
  myMap.insert(2, 'a');
  myMap.insert(3, 'a');
  origMap.insert(std::make_pair(1, 'a'));
  origMap.insert(std::make_pair(2, 'a'));
  origMap.insert(std::make_pair(3, 'a'));

  auto myIt = myMap.begin();
  auto origIt = origMap.begin();
  for (; myIt != myMap.end(); ++myIt, ++origIt) {
    EXPECT_TRUE((*myIt).first == (*origIt).first);
    EXPECT_TRUE((*myIt).second == (*origIt).second);
  }

  auto pr1 = myMap.insert_or_assign(1, 'b');
  auto i = origMap.begin();
  EXPECT_TRUE((*pr1.first).first == (*i).first);
  EXPECT_FALSE((*pr1.first).second == (*i).second);
}

TEST(Map, MapErase_1) {
  s21::Map<int, int> myMap({{1, 'x'}, {2, 'b'}, {3, 'z'}, {4, 'y'}});
  std::map<int, int> origMap({{1, 'x'}, {2, 'b'}, {3, 'z'}, {4, 'y'}});
  EXPECT_EQ(myMap.size(), origMap.size());
  myMap.erase(myMap.begin());
  origMap.erase(origMap.begin());
  EXPECT_EQ(myMap.size(), origMap.size());
  auto myIt = myMap.begin();
  auto origIt = origMap.begin();
  for (; myIt != myMap.end(); ++myIt, ++origIt) {
    EXPECT_TRUE((*myIt).first == (*origIt).first);
    EXPECT_TRUE((*myIt).second == (*origIt).second);
  }
}

TEST(Map, MapErase_2) {
  s21::Map<int, int> myMap({{5, 50},
                            {7, 70},
                            {4, 40},
                            {3, 30},
                            {8, 80},
                            {1, 10},
                            {2, 20},
                            {6, 60},
                            {9, 90}});
  std::map<int, int> origMap({{5, 50},
                              {7, 70},
                              {4, 40},
                              {3, 30},
                              {8, 80},
                              {1, 10},
                              {2, 20},
                              {6, 60},
                              {9, 90}});
  EXPECT_EQ(myMap.size(), origMap.size());
  auto myIt = myMap.begin();
  auto origIt = origMap.begin();
  for (size_t i = 0; i < 4; ++i, ++myIt, ++origIt);
  myMap.erase(myIt);
  origMap.erase(origIt);
  EXPECT_EQ(myMap.size(), origMap.size());
  myIt = myMap.begin();
  origIt = origMap.begin();
  for (; myIt != myMap.end(); ++myIt, ++origIt) {
    EXPECT_TRUE((*myIt).first == (*origIt).first);
    EXPECT_TRUE((*myIt).second == (*origIt).second);
  }
}

TEST(Map, MapErase_3) {
  s21::Map<int, int> myMap({{5, 50},
                            {7, 70},
                            {4, 40},
                            {3, 30},
                            {8, 80},
                            {1, 10},
                            {2, 20},
                            {6, 60},
                            {9, 90}});
  std::map<int, int> origMap({{5, 50},
                              {7, 70},
                              {4, 40},
                              {3, 30},
                              {8, 80},
                              {1, 10},
                              {2, 20},
                              {6, 60},
                              {9, 90}});
  EXPECT_EQ(myMap.size(), origMap.size());
  auto myIt = myMap.begin();
  auto origIt = origMap.begin();
  for (size_t i = 0; i < 8; ++i, ++myIt, ++origIt);
  myMap.erase(myIt);
  origMap.erase(origIt);
  EXPECT_EQ(myMap.size(), origMap.size());
  myIt = myMap.begin();
  origIt = origMap.begin();
  for (; myIt != myMap.end(); ++myIt, ++origIt) {
    EXPECT_TRUE((*myIt).first == (*origIt).first);
    EXPECT_TRUE((*myIt).second == (*origIt).second);
  }
}

TEST(Map, MapErase_4) {
  s21::Map<int, int> myMap({{1, 10}, {3, 30}, {2, 20}});
  std::map<int, int> origMap({{1, 10}, {3, 30}, {2, 20}});
  EXPECT_EQ(myMap.size(), origMap.size());
  auto myIt = myMap.begin();
  auto origIt = origMap.begin();
  for (size_t i = 0; i < 2; ++i, ++myIt, ++origIt);
  myMap.erase(myIt);
  origMap.erase(origIt);
  EXPECT_EQ(myMap.size(), origMap.size());
  myIt = myMap.begin();
  origIt = origMap.begin();
  for (; myIt != myMap.end(); ++myIt, ++origIt) {
    EXPECT_TRUE((*myIt).first == (*origIt).first);
    EXPECT_TRUE((*myIt).second == (*origIt).second);
  }
}

TEST(Map, MapErase_5) {
  s21::Map<int, int> myMap({{3, 30}, {1, 10}, {2, 20}});
  std::map<int, int> origMap({{3, 30}, {1, 10}, {2, 20}});
  EXPECT_EQ(myMap.size(), origMap.size());
  auto myIt = myMap.begin();
  auto origIt = origMap.begin();
  for (size_t i = 0; i < 2; ++i, ++myIt, ++origIt);
  myMap.erase(myIt);
  origMap.erase(origIt);
  EXPECT_EQ(myMap.size(), origMap.size());
  myIt = myMap.begin();
  origIt = origMap.begin();
  for (; myIt != myMap.end(); ++myIt, ++origIt) {
    EXPECT_TRUE((*myIt).first == (*origIt).first);
    EXPECT_TRUE((*myIt).second == (*origIt).second);
  }
}

TEST(Map, SwapMap) {
  s21::Map<int, int> myMap({{1, 1}});
  s21::Map<int, int> mySwapMap({{3, 3}, {4, 4}});

  myMap.swap(mySwapMap);
  EXPECT_EQ(myMap.size(), 2);
  EXPECT_EQ(mySwapMap.size(), 1);
  auto x = myMap.begin();
  auto y = mySwapMap.begin();
  EXPECT_EQ((*x).first, 3);
  EXPECT_EQ((*y).first, 1);
}

TEST(Map, MergeMap) {
  s21::Map<int, int> myMap({{1, 1}, {4, 4}, {2, 2}});
  s21::Map<int, int> myMapMerge({{3, 3}, {4, 4}});

  std::map<int, int> origMap({{1, 1}, {4, 4}, {2, 2}});
  std::map<int, int> origMapMerge({{3, 3}, {4, 4}});

  myMap.merge(myMapMerge);
  origMap.merge(origMapMerge);

  EXPECT_EQ(myMap.size(), origMap.size());
  EXPECT_EQ(myMapMerge.size(), origMapMerge.size());

  auto myIt = myMap.begin();
  auto origIt = origMap.begin();
  for (; myIt != myMap.end(); ++myIt, ++origIt) {
    EXPECT_TRUE((*myIt).first == (*origIt).first);
    EXPECT_TRUE((*myIt).second == (*origIt).second);
  }
  EXPECT_TRUE(myMapMerge.contains(4));
  EXPECT_FALSE(myMapMerge.contains(3));
}

TEST(Map, ConstBegin) {
  const s21::Map<int, int> myMap({{1, 2}, {3, 4}, {5, 6}});
  auto myIt = myMap.begin();
  EXPECT_EQ((*myIt).first, 1);
  EXPECT_EQ((*myIt).second, 2);
  ++myIt;
  ++myIt;
  EXPECT_EQ((*myIt).first, 5);
  EXPECT_EQ((*myIt).second, 6);
  --myIt;
  EXPECT_EQ((*myIt).first, 3);
  EXPECT_EQ((*myIt).second, 4);
}

TEST(map, OperatorCopy) {
  const s21::Map<int, int> m1({{9, 10}, {7, 8}, {5, 6}, {3, 4}, {1, 2}});
  s21::Map<int, int> m2;
  m2 = m1;
  auto myIt = m2.begin();
  EXPECT_EQ((*myIt).first, 1);
  EXPECT_EQ((*myIt).second, 2);
  ++myIt;
  ++myIt;
  EXPECT_EQ((*myIt).first, 5);
  EXPECT_EQ((*myIt).second, 6);
  --myIt;
  EXPECT_EQ((*myIt).first, 3);
  EXPECT_EQ((*myIt).second, 4);
  --myIt;
  EXPECT_EQ((*myIt).first, 1);
  EXPECT_EQ((*myIt).second, 2);
  auto myIt2 = m1.begin();
  EXPECT_EQ((*myIt2).first, 1);
  EXPECT_EQ((*myIt2).second, 2);
  ++myIt2;
  ++myIt2;
  EXPECT_EQ((*myIt2).first, 5);
  EXPECT_EQ((*myIt2).second, 6);
  --myIt2;
  EXPECT_EQ((*myIt2).first, 3);
  EXPECT_EQ((*myIt2).second, 4);
  --myIt2;
  EXPECT_EQ((*myIt2).first, 1);
  EXPECT_EQ((*myIt2).second, 2);
}

TEST(Map, OperatorMove) {
  s21::Map<int, int> m1({{9, 10}, {7, 8}, {5, 6}, {3, 4}, {1, 2}});
  s21::Map<int, int> m2;
  m2 = std::move(m1);
  auto it1 = m2.begin();
  EXPECT_EQ((*it1).first, 1);
  EXPECT_EQ((*it1).second, 2);
  ++it1;
  ++it1;
  EXPECT_EQ((*it1).first, 5);
  EXPECT_EQ((*it1).second, 6);
  --it1;
  EXPECT_EQ((*it1).first, 3);
  EXPECT_EQ((*it1).second, 4);
  --it1;
  EXPECT_EQ((*it1).first, 1);
  EXPECT_EQ((*it1).second, 2);

  EXPECT_EQ(m1.size(), 0);
}

TEST(Map, Find) {
  s21::Map<int, int> m1({{1, 2}, {3, 4}, {5, 6}});
  auto itEnd = m1.end();
  auto itAns = m1.begin();
  ++itAns;
  auto it1 = m1.find(3);
  EXPECT_FALSE(it1 == itEnd);
  EXPECT_TRUE(it1 == itAns);
  it1 = m1.find(6);
  EXPECT_TRUE(it1 == itEnd);
}

TEST(Map, ConstFind) {
  const s21::Map<int, int> m1({{1, 2}, {3, 4}, {5, 6}});
  auto itEnd = m1.end();
  auto itAns = m1.begin();
  ++itAns;
  auto it1 = m1.find(3);
  EXPECT_FALSE(it1 == itEnd);
  EXPECT_TRUE(it1 == itAns);
  it1 = m1.find(6);
  EXPECT_TRUE(it1 == itEnd);
}

TEST(Map, OperatorBracket) {
  s21::Map<int, int> m1({{3, 4}, {5, 6}, {1, 2}});
  m1[8] = 80;
  EXPECT_EQ((*(m1.find(8))).second, 80);
}

TEST(Map, MaxSize) {
  s21::Map<int, int> m1({{1, 2}, {3, 4}, {5, 6}});
  s21::Map<int, int> m2({{1, 2}, {3, 4}, {5, 6}});
  EXPECT_EQ(m1.max_size(), m2.max_size());
}

TEST(map, InsertMany) {
  s21::Map<int, int> m1({{3, 30}, {5, 50}, {1, 10}});
  m1.insert_many(std::make_pair(2, 20), std::make_pair(4, 40));
  EXPECT_EQ(m1.contains(2), true);
  EXPECT_EQ(m1.contains(4), true);
}