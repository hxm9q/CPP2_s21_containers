#ifndef S21_MULTISET_H
#define S21_MULTISET_H

#include "s21_binary_tree.h"

namespace s21 {
template <class Key, class Compare = std::less<Key>>
class multiset {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  using tree_type = BinaryTree::BinaryTree<key_type, Compare>;
  using iterator = typename tree_type::iterator;
  using const_iterator = typename tree_type::const_iterator;

  multiset() : tree_() {}
  explicit multiset(std::initializer_list<value_type> const &items) : tree_() {
    for (const auto &item : items) tree_.insert_with_repetitions(item);
  }
  multiset(const multiset &ms) : tree_(ms.tree_) {}
  multiset(multiset &&ms) noexcept : tree_(std::move(ms.tree_)) {}
  ~multiset() { clear(); }

  multiset &operator=(multiset &&ms) & noexcept {
    if (this == &ms) return *this;
    tree_ = std::move(ms.tree_);
    return *this;
  }
  multiset &operator=(const multiset &ms) & {
    if (this == &ms) return *this;
    tree_ = ms.tree_;
    return *this;
  }

  iterator begin() { return tree_.begin(); }
  const_iterator begin() const { return tree_.begin(); }
  iterator end() { return tree_.end(); }
  const_iterator end() const { return tree_.end(); }

  void clear() noexcept { tree_.clear(); }
  iterator insert(const value_type &key) {
    return tree_.insert_with_repetitions(key);
  }
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    std::vector<std::pair<iterator, bool>> results;
    (results.emplace_back(insert(std::forward<Args>(args))), ...);
    return results;
  }
  void erase(iterator pos) noexcept { tree_.erase(pos); }
  void swap(multiset &other) noexcept { std::swap(tree_, other.tree_); }
  void merge(multiset &other) {
    for (const auto &item : other) insert(item);
    other.clear();
  }

  [[nodiscard]] bool empty() const noexcept { return tree_.empty(); }
  [[nodiscard]] size_type size() const noexcept { return tree_.size(); }
  [[nodiscard]] size_type max_size() const noexcept { return tree_.max_size(); }

  size_type count(const Key &key) const noexcept { return tree_.count(key); }
  iterator find(const Key &key) noexcept { return tree_.find(key); }
  const_iterator find(const Key &key) const noexcept { return tree_.find(key); }
  bool contains(const Key &key) const noexcept { return tree_.contains(key); }
  std::pair<iterator, iterator> equal_range(const Key &key) noexcept {
    return tree_.equal_range(key);
  }
  std::pair<const_iterator, const_iterator> equal_range(
      const Key &key) const noexcept {
    return tree_.equal_range(key);
  }
  iterator lower_bound(const Key &key) noexcept {
    return tree_.lower_bound(key);
  }
  const_iterator lower_bound(const Key &key) const noexcept {
    return tree_.lower_bound(key);
  }
  iterator upper_bound(const Key &key) noexcept {
    return tree_.upper_bound(key);
  }
  const_iterator upper_bound(const Key &key) const noexcept {
    return tree_.upper_bound(key);
  }

 private:
  tree_type tree_;
};
}  // namespace s21
#endif