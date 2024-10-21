#include <list>

#include "test.h"

template class s21::List<int>;

TEST(List, Constructor_Default) {
  s21::List<int> our_list;
  std::list<int> std_list;
  EXPECT_EQ(our_list.Empty(), std_list.empty());
}

TEST(List, Constructor_size) {
  s21::List<int> our_list(5);
  std::list<int> std_list(5);
  EXPECT_EQ(our_list.Size(), std_list.size());
}

TEST(List, Constructor_List) {
  s21::List<int> our_list({1, 2, 3});
  std::list<int> std_list({1, 2, 3});
  EXPECT_EQ(our_list.Front(), std_list.front());
  EXPECT_EQ(our_list.Back(), std_list.back());
}

TEST(List, Constructor_Copy) {
  s21::List<int> our_list({1, 2, 3});
  std::list<int> std_list({1, 2, 3});
  s21::List<int> our_copy(our_list);
  std::list<int> std_copy(std_list);
  EXPECT_EQ(our_copy.Front(), std_copy.front());
  EXPECT_EQ(our_copy.Back(), std_copy.back());
}

TEST(List, Operator_Copy) {
  s21::List<int> our_list({1, 2, 3});
  std::list<int> std_list({1, 2, 3});
  s21::List<int> our_copy;
  our_copy = our_list;
  std::list<int> std_copy;
  std_copy = std_list;
  EXPECT_EQ(our_copy.Front(), std_copy.front());
  EXPECT_EQ(our_copy.Back(), std_copy.back());
}

TEST(List, Constructor_Move) {
  s21::List<int> our_list({1, 2, 3});
  std::list<int> std_list({1, 2, 3});
  s21::List<int> our_copy(std::move(our_list));
  std::list<int> std_copy(std::move(std_list));
  EXPECT_EQ(our_copy.Front(), std_copy.front());
  EXPECT_EQ(our_copy.Back(), std_copy.back());
  EXPECT_EQ(our_list.Empty(), std_list.empty());
}

TEST(List, Operator_Move) {
  s21::List<int> our_list({1, 2, 3});
  std::list<int> std_list({1, 2, 3});
  s21::List<int> our_copy;
  our_copy = std::move(our_list);
  std::list<int> std_copy;
  std_copy = std::move(std_list);
  EXPECT_EQ(our_copy.Front(), std_copy.front());
  EXPECT_EQ(our_copy.Back(), std_copy.back());
  EXPECT_EQ(our_list.Empty(), std_list.empty());
}

TEST(List, size) {
  s21::List<int> our_list({1, 2, 3});
  std::list<int> std_list({1, 2, 3});
  EXPECT_EQ(our_list.Size(), std_list.size());
}

TEST(List, Push_Front) {
  s21::List<int> our_list;
  std::list<int> std_list;
  our_list.Push_Front(1);
  std_list.push_front(1);
  EXPECT_EQ(our_list.Front(), std_list.front());
  EXPECT_EQ(our_list.Back(), std_list.back());
  our_list.Push_Front(2);
  std_list.push_front(2);
  EXPECT_EQ(our_list.Front(), std_list.front());
  EXPECT_EQ(our_list.Back(), std_list.back());
  our_list.Push_Front(3);
  std_list.push_front(3);
  EXPECT_EQ(our_list.Front(), std_list.front());
  EXPECT_EQ(our_list.Back(), std_list.back());
}

TEST(List, Push_Back) {
  s21::List<int> our_list;
  std::list<int> std_list;
  our_list.Push_Back(1);
  std_list.push_back(1);
  EXPECT_EQ(our_list.Front(), std_list.front());
  EXPECT_EQ(our_list.Back(), std_list.back());
  our_list.Push_Back(2);
  std_list.push_back(2);
  EXPECT_EQ(our_list.Front(), std_list.front());
  EXPECT_EQ(our_list.Back(), std_list.back());
  our_list.Push_Back(3);
  std_list.push_back(3);
  EXPECT_EQ(our_list.Front(), std_list.front());
  EXPECT_EQ(our_list.Back(), std_list.back());
}

TEST(List, Pop_Front) {
  s21::List<int> our_list;
  std::list<int> std_list;
  our_list.Push_Back(1);
  std_list.push_back(1);
  EXPECT_EQ(our_list.Front(), std_list.front());
  EXPECT_EQ(our_list.Back(), std_list.back());
  our_list.Push_Back(2);
  std_list.push_back(2);
  EXPECT_EQ(our_list.Front(), std_list.front());
  EXPECT_EQ(our_list.Back(), std_list.back());
  our_list.Push_Back(3);
  std_list.push_back(3);
  EXPECT_EQ(our_list.Front(), std_list.front());
  EXPECT_EQ(our_list.Back(), std_list.back());
  our_list.Pop_Front();
  std_list.pop_front();
  EXPECT_EQ(our_list.Front(), std_list.front());
  EXPECT_EQ(our_list.Back(), std_list.back());
}

TEST(List, Pop_Back) {
  s21::List<int> our_list;
  std::list<int> std_list;
  our_list.Push_Back(1);
  std_list.push_back(1);
  EXPECT_EQ(our_list.Front(), std_list.front());
  EXPECT_EQ(our_list.Back(), std_list.back());
  our_list.Push_Back(2);
  std_list.push_back(2);
  EXPECT_EQ(our_list.Front(), std_list.front());
  EXPECT_EQ(our_list.Back(), std_list.back());
  our_list.Push_Back(3);
  std_list.push_back(3);
  EXPECT_EQ(our_list.Front(), std_list.front());
  EXPECT_EQ(our_list.Back(), std_list.back());
  our_list.Pop_Back();
  std_list.pop_back();
  EXPECT_EQ(our_list.Front(), std_list.front());
  EXPECT_EQ(our_list.Back(), std_list.back());
}

TEST(List, Iterator_Begin) {
  s21::List<int> our_list({1, 2, 3});
  std::list<int> std_list({1, 2, 3});
  s21::List<int>::iterator our_it;
  our_it = our_list.Begin();
  std::list<int>::iterator std_it;
  std_it = std_list.begin();
  EXPECT_EQ(*our_it, *std_it);
}

TEST(List, Iterator_BeginPlusAndMinus) {
  s21::List<int> our_list({1, 2, 3});
  std::list<int> std_list({1, 2, 3});
  s21::List<int>::iterator our_it;
  our_it = our_list.Begin();
  ++our_it;
  std::list<int>::iterator std_it;
  std_it = std_list.begin();
  ++std_it;
  EXPECT_EQ(*our_it, *std_it);
  --our_it;
  --std_it;
  EXPECT_EQ(*our_it, *std_it);
}

TEST(List, Iterator_End_Last) {
  s21::List<int> our_list({1, 2, 3});
  std::list<int> std_list({1, 2, 3});
  s21::List<int>::iterator our_it;
  our_it = our_list.End();
  --our_it;
  std::list<int>::iterator std_it;
  std_it = std_list.end();
  --std_it;
  EXPECT_EQ(*our_it, *std_it);
}

TEST(List, ConstIterator_End_Last) {
  const s21::List<int> our_list({1, 2, 3});
  const std::list<int> std_list({1, 2, 3});
  auto our_it = our_list.Cend();
  --our_it;
  auto std_it = std_list.cend();
  --std_it;
  EXPECT_EQ(*our_it, *std_it);
}

TEST(List, ConstIterator_End_Last_2) {
  const s21::List<int> our_list({1, 2, 3});
  auto our_it = our_list.Cend();
  --our_it;
  --our_it;
  --our_it;
  EXPECT_TRUE(our_list.Cbegin() == our_it);
}

TEST(List, Iterator_Equals) {
  s21::List<int> first_list({1, 2, 3});
  s21::List<int>::iterator our_it_first;
  our_it_first = first_list.Begin();
  s21::List<int>::iterator our_it_second;
  our_it_second = first_list.Begin();
  EXPECT_TRUE(our_it_first == our_it_second);
  ++our_it_second;
  EXPECT_TRUE(our_it_first != our_it_second);
}

TEST(List, Insert) {
  s21::List<int> our_list;
  std::list<int> std_list;
  s21::List<int>::iterator our_it;
  our_it = our_list.Begin();
  std::list<int>::iterator std_it;
  std_it = std_list.begin();
  our_list.Insert(our_it, 5);
  std_list.insert(std_it, 5);
  EXPECT_EQ(our_list.Front(), std_list.front());
  EXPECT_EQ(our_list.Back(), std_list.back());
  our_list.Insert(our_it, 7);
  std_list.insert(std_it, 7);
  our_list.Insert(our_it, 9);
  std_list.insert(std_it, 9);
  EXPECT_EQ(our_list.Front(), std_list.front());
  EXPECT_EQ(our_list.Back(), std_list.back());
}

TEST(List, Erase) {
  s21::List<int> our_list({1, 2, 3, 4, 5});
  std::list<int> std_list({1, 2, 3, 4, 5});
  our_list.Erase(our_list.Begin());
  std_list.erase(std_list.begin());
  EXPECT_EQ(our_list.Front(), std_list.front());
  EXPECT_EQ(our_list.Back(), std_list.back());
  s21::List<int>::iterator our_it;
  our_it = our_list.Begin();
  ++our_it;
  std::list<int>::iterator std_it;
  std_it = std_list.begin();
  ++std_it;
  EXPECT_EQ(our_list.Front(), std_list.front());
  EXPECT_EQ(our_list.Back(), std_list.back());
}

TEST(List, Splice) {
  s21::List<int> our_list_first({1});
  s21::List<int> our_list_second({2, 3, 4, 5});
  std::list<int> std_list_first({1});
  std::list<int> std_list_second({2, 3, 4, 5});
  s21::List<int>::const_iterator our_it = our_list_first.Cbegin();
  std::list<int>::iterator std_it = std_list_first.begin();
  our_list_first.Splice(our_it, our_list_second);
  std_list_first.splice(std_it, std_list_second);
  EXPECT_EQ(our_list_first.Front(), std_list_first.front());
  EXPECT_EQ(our_list_first.Back(), std_list_first.back());
}

TEST(List, Merge) {
  s21::List<int> our_list_first({1});
  s21::List<int> our_list_second({2, 3, 4, 5});
  std::list<int> std_list_first({1});
  std::list<int> std_list_second({2, 3, 4, 5});
  our_list_first.Merge(our_list_second);
  std_list_first.merge(std_list_second);
  EXPECT_EQ(our_list_first.Front(), std_list_first.front());
  EXPECT_EQ(our_list_first.Back(), std_list_first.back());
  EXPECT_EQ(our_list_second.Empty(), std_list_second.empty());
}

TEST(List, Reverse) {
  s21::List<int> our_list({1, 2, 3, 4, 5});
  std::list<int> std_list({1, 2, 3, 4, 5});
  our_list.Reverse();
  std_list.reverse();
  EXPECT_EQ(our_list.Front(), std_list.front());
  EXPECT_EQ(our_list.Back(), std_list.back());
}

TEST(List, Unique) {
  s21::List<int> our_list({1, 2, 2, 3, 3});
  std::list<int> std_list({1, 2, 2, 3, 3});
  s21::List<int>::iterator our_it;
  std::list<int>::iterator std_it;
  our_list.Unique();
  std_list.unique();
  our_it = our_list.Begin();
  std_it = std_list.begin();
  EXPECT_EQ(*our_it, *std_it);
  ++our_it;
  ++std_it;
  EXPECT_EQ(*our_it, *std_it);
  ++our_it;
  ++std_it;
  EXPECT_EQ(*our_it, *std_it);
}

TEST(List, Sort) {
  s21::List<int> our_list({2, 4, 1, 3, 5});
  std::list<int> std_list({2, 4, 1, 3, 5});
  s21::List<int>::iterator our_it;
  std::list<int>::iterator std_it;
  our_list.Sort();
  std_list.sort();
  our_it = our_list.Begin();
  std_it = std_list.begin();
  EXPECT_EQ(*our_it, *std_it);
  ++our_it;
  ++std_it;
  EXPECT_EQ(*our_it, *std_it);
  ++our_it;
  ++std_it;
  EXPECT_EQ(*our_it, *std_it);
  ++our_it;
  ++std_it;
  EXPECT_EQ(*our_it, *std_it);
  ++our_it;
  ++std_it;
  EXPECT_EQ(*our_it, *std_it);
}

TEST(List, Insert_Many) {
  s21::List<int> our_list({1, 2, 3, 4, 5});
  s21::List<int>::const_iterator our_it = our_list.Cbegin();
  ++our_it;
  our_list.Insert_Many(our_it, 7, 8, 9);
  s21::List<int>::iterator our_it2 = our_list.Begin();
  EXPECT_EQ(*our_it2, 1);
  ++our_it2;
  EXPECT_EQ(*our_it2, 7);
  ++our_it2;
  EXPECT_EQ(*our_it2, 8);
  ++our_it2;
  EXPECT_EQ(*our_it2, 9);
  ++our_it2;
  EXPECT_EQ(*our_it2, 2);
}

TEST(List, Insert_Many_Back) {
  s21::List<int> our_list({1, 2, 3, 4, 5});
  s21::List<int>::iterator our_it;
  our_list.Insert_Many_Back(7, 8, 9);
  our_it = our_list.End();
  --our_it;
  EXPECT_EQ(*our_it, 9);
  --our_it;
  EXPECT_EQ(*our_it, 8);
  --our_it;
  EXPECT_EQ(*our_it, 7);
  --our_it;
  EXPECT_EQ(*our_it, 5);
  --our_it;
  EXPECT_EQ(*our_it, 4);
}

TEST(List, Insert_Many_Front) {
  s21::List<int> our_list({1, 2, 3, 4, 5});
  s21::List<int>::iterator our_it;
  our_list.insert_many_front(7, 8, 9);
  our_it = our_list.Begin();
  EXPECT_EQ(*our_it, 9);
  ++our_it;
  EXPECT_EQ(*our_it, 8);
  ++our_it;
  EXPECT_EQ(*our_it, 7);
  ++our_it;
  EXPECT_EQ(*our_it, 1);
  ++our_it;
  EXPECT_EQ(*our_it, 2);
}

TEST(List, ListIteratorConst) {
  const s21::List<int> l({1, 2, 3});
  s21::List<int>::ListIteratorConst it;
  it = l.Cbegin();
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  --it;
  EXPECT_EQ(*it, 2);
  --it;
  EXPECT_EQ(*it, 1);
}

TEST(List, ListIterator) {
  s21::List<int> l({1, 2, 3});
  s21::List<int>::ListIterator it;
  it = l.Begin();
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  --it;
  EXPECT_EQ(*it, 2);
  --it;
  EXPECT_EQ(*it, 1);
}