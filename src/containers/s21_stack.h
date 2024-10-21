#ifndef S21_STACK_H
#define S21_STACK_H

#include <initializer_list>
#include <stdexcept>

#include "s21_queue.h"

namespace s21 {

template <typename T>
class stack : public sequential_container<T> {
 public:
  struct Node {
    T data;
    Node* next;
    explicit Node(const T& value) : data(value), next(nullptr) {}
  };

  using value_type = typename sequential_container<T>::value_type;
  using reference = typename sequential_container<T>::reference;
  using const_reference = typename sequential_container<T>::const_reference;
  using size_type = typename sequential_container<T>::size_type;

  stack() : topNode(nullptr) {}

  explicit stack(std::initializer_list<value_type> const& items)
      : topNode(nullptr) {
    for (const value_type& item : items) {
      this->push(item);
    }
  }

  stack(const stack& s) : topNode(nullptr) {
    stack temp;
    Node* current = s.topNode;

    while (current != nullptr) {
      temp.push(current->data);
      current = current->next;
    }

    while (!temp.empty()) {
      push(temp.top());
      temp.pop();
    }
  }

  stack(stack&& s) noexcept : topNode(s.topNode) { s.topNode = nullptr; }

  ~stack() {
    while (topNode != nullptr) {
      Node* temp = topNode;
      topNode = topNode->next;
      delete temp;
    }
  }

  stack& operator=(stack&& s) noexcept {
    if (this != &s) {
      while (topNode != nullptr) {
        Node* temp = topNode;
        topNode = topNode->next;
        delete temp;
      }
      topNode = s.topNode;
      s.topNode = nullptr;
    }

    return *this;
  }

  const_reference top() {
    if (topNode != nullptr) {
      return topNode->data;
    } else {
      throw std::out_of_range("Stack is empty");
    }
  }

  bool empty() override { return topNode == nullptr; }

  size_type size() override {
    size_type count = 0;
    Node* current = topNode;
    while (current != nullptr) {
      ++count;
      current = current->next;
    }

    return count;
  }

  void push(const_reference value) override {
    Node* newNode = new Node(value);
    newNode->next = topNode;
    topNode = newNode;
  }

  void pop() override {
    if (topNode != nullptr) {
      Node* temp = topNode;
      topNode = topNode->next;
      delete temp;
    } else {
      throw std::out_of_range("Stack is empty");
    }
  }
  void swap(sequential_container<T>& other) override {
    auto* otherStack = dynamic_cast<stack<T>*>(&other);
    if (otherStack) {
      std::swap(topNode, otherStack->topNode);
    } else {
      throw std::invalid_argument(
          "Cannot swap with a different container type");
    }
  }

  template <typename... Args>
  void insert_many_front(Args&&... args) {
    (..., push(std::forward<Args>(args)));
  }

  class iterator {
   public:
    using value_type = T;
    using reference = T&;
    using pointer = T*;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;

    explicit iterator(Node* node) : current(node) {}

    reference operator*() { return current->data; }

    iterator& operator++() {
      if (current) {
        current = current->next;
      }

      return *this;
    }

    iterator operator++(int) {
      iterator temp = *this;
      ++(*this);

      return temp;
    }

    bool operator==(const iterator& other) const {
      return current == other.current;
    }

    bool operator!=(const iterator& other) const {
      return current != other.current;
    }

   private:
    Node* current;
  };

  iterator begin() { return iterator(topNode); }

  iterator end() { return iterator(nullptr); }

 private:
  Node* topNode;
};

};  // namespace s21

#endif