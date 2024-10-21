#ifndef ARRAY_H
#define ARRAY_H

#include <cstdio>
#include <initializer_list>
#include <stdexcept>
#include <utility>

namespace s21 {
template <typename T, size_t Size>
class Array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  Array() : elements{} {}

  explicit Array(std::initializer_list<value_type> const &items) {
    size_type i = 0;
    for (const value_type &item : items) {
      if (i < Size) {
        elements[i] = item;
        ++i;
      }
    }
  }

  Array(const Array &a) {
    for (size_type i = 0; i < Size; ++i) {
      elements[i] = a.elements[i];
    }
  }

  Array(Array &&a) noexcept {
    for (size_type i = 0; i < Size; ++i) {
      elements[i] = std::move(a.elements[i]);
    }
  }

  ~Array() = default;

  Array &operator=(Array &&a) noexcept {
    if (this != &a) {
      for (size_type i = 0; i < Size; ++i) {
        elements[i] = std::move(a.elements[i]);
      }
    }
    return *this;
  }

  reference at(size_type pos) {
    if (pos < Size) {
      return elements[pos];
    } else {
      throw std::out_of_range("Index out of bounds");
    }
  }

  reference operator[](size_type pos) { return elements[pos]; }

  const_reference front() { return elements[0]; }

  const_reference back() { return elements[(size_t)(Size - 1)]; }

  iterator data() { return elements; }

  const_iterator data() const { return elements; }

  iterator begin() { return elements; }

  iterator end() { return elements + Size; }

  bool empty() { return Size == 0; }

  size_type size() { return Size; }

  size_type max_size() { return Size; }

  void swap(Array &other) {
    if (this == &other) {
      return;
    }

    for (size_type i = 0; i < Size; ++i) {
      std::swap(elements[i], other.elements[i]);
    }
  }

  void fill(const_reference value) {
    for (size_type i = 0; i < Size; ++i) {
      elements[i] = value;
    }
  }

 private:
  value_type elements[Size];
};
}  // namespace s21

#endif