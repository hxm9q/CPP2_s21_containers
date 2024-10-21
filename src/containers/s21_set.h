#ifndef S21_SET_H
#define S21_SET_H

#include "s21_binary_tree.h"

namespace s21 {
template <class Key, class Compare = std::less<Key>>
class set {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  using tree_type = BinaryTree::BinaryTree<key_type, Compare>;
  using iterator = typename tree_type::iterator;
  using const_iterator = typename tree_type::const_iterator;

  set() : tree_() {}
  explicit set(std::initializer_list<value_type> const &items) : tree_(items) {}
  set(const set &s) : tree_(s.tree_) {}
  set(set &&s) noexcept : tree_(std::move(s.tree_)) {}
  ~set() { clear(); }

  iterator begin() { return tree_.begin(); }
  const_iterator begin() const { return tree_.begin(); }
  iterator end() { return tree_.end(); }
  const_iterator end() const { return tree_.end(); }

  [[nodiscard]] bool empty() const noexcept { return tree_.empty(); }
  [[nodiscard]] size_type size() const noexcept { return tree_.size(); }
  [[nodiscard]] size_type max_size() const noexcept { return tree_.max_size(); }

  void clear() noexcept { tree_.clear(); }
  std::pair<iterator, bool> insert(const value_type &value) {
    return tree_.insert(value);
  }
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    std::vector<std::pair<iterator, bool>> results;
    (results.emplace_back(insert(std::forward<Args>(args))), ...);
    return results;
  }
  void erase(iterator pos) noexcept { tree_.erase(pos); }
  void swap(set &other) noexcept { std::swap(tree_, other.tree_); }
  void merge(set &other) { tree_.merge(other.tree_); }

  iterator find(const Key &key) noexcept { return tree_.find(key); }
  const_iterator find(const Key &key) const noexcept { return tree_.find(key); }
  bool contains(const Key &key) const noexcept { return tree_.contains(key); }

  set &operator=(set &&s) & noexcept {
    if (this == &s) return *this;
    tree_ = std::move(s.tree_);
    return *this;
  }
  set &operator=(const set &s) & {
    if (this == &s) return *this;
    tree_ = s.tree_;
    return *this;
  }

 private:
  tree_type tree_;
};
}  // namespace s21

#endif