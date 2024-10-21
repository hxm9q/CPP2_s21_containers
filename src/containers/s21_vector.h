#ifndef S21_VECTOR_H
#define S21_VECTOR_H

#include <iostream>
#include <limits>

namespace s21 {
template <typename T>
class Vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;

  class Iterator {
   public:
    Iterator(value_type *ref) { array_ptr_ = ref; }

    reference &operator*() { return *array_ptr_; }

    Iterator operator++(int) {
      Iterator temp = array_ptr_;
      ++array_ptr_;

      return temp;
    }
    Iterator &operator++() { return ++array_ptr_; }

    Iterator operator--(int) {
      Iterator temp = array_ptr_;
      --array_ptr_;

      return temp;
    }
    Iterator &operator--() { return --array_ptr_; }

    Iterator operator+(int n) { return array_ptr_ + n; }
    Iterator operator-(int n) { return array_ptr_ - n; }
    Iterator operator+=(int n) { return array_ptr_ += n; }
    Iterator operator-=(int n) { return array_ptr_ -= n; }
    bool operator==(const Iterator it) { return array_ptr_ == it.array_ptr_; }
    bool operator!=(const Iterator it) { return array_ptr_ != it.array_ptr_; }

   private:
    value_type *array_ptr_;
  };

  class ConstIterator {
   public:
    ConstIterator(value_type *ref) { array_ptr_ = ref; }
    const value_type &operator*() const { return *array_ptr_; }

    ConstIterator operator++(int) {
      ConstIterator temp = array_ptr_;
      ++array_ptr_;

      return temp;
    }
    ConstIterator operator++() { return ++array_ptr_; }

    ConstIterator operator--(int) {
      ConstIterator temp = array_ptr_;
      --array_ptr_;

      return temp;
    }
    ConstIterator operator--() { return --array_ptr_; }

    ConstIterator operator+(int n) { return array_ptr_ + n; }
    ConstIterator operator-(int n) { return array_ptr_ - n; }
    ConstIterator operator+=(int n) { return array_ptr_ += n; }
    ConstIterator operator-=(int n) { return array_ptr_ -= n; }
    bool operator==(const ConstIterator &it) {
      return array_ptr_ == it.array_ptr_;
    }
    bool operator!=(const ConstIterator &it) {
      return array_ptr_ != it.array_ptr_;
    }

   private:
    value_type *array_ptr_;
  };

  using iterator = Iterator;
  using const_iterator = ConstIterator;
  using size_type = size_t;

  Vector() : size_(0), capacity_(0), array_(nullptr) {}

  Vector(size_type n) : size_(n), capacity_(n) {
    if (n == 0) {
      array_ = nullptr;
    } else {
      array_ = new value_type[n];
      for (size_type i = 0; i < size_; i++) {
        array_[i] = 0;
      }
    }
  }

  Vector(std::initializer_list<value_type> const &items) {
    size_ = items.size();
    capacity_ = items.size();
    array_ = new value_type[size_];
    std::copy(items.begin(), items.end(), array_);
  }

  Vector(const Vector &v)
      : size_(v.size_), capacity_(v.capacity_), array_(new value_type[size_]) {
    const_iterator it = v.cbegin();
    int i = 0;
    while (it != v.cend()) {
      array_[i] = *it;
      ++i;
      ++it;
    }
  }

  Vector(Vector &&v)
      : size_(v.size()), capacity_(v.capacity()), array_(v.array_) {
    v.size_ = v.capacity_ = 0;
    v.array_ = nullptr;
  }

  ~Vector() {
    size_ = capacity_ = 0;
    if (array_ != nullptr) {
      delete[] array_;
      array_ = nullptr;
    }
  }

  Vector &operator=(const Vector &v) {
    size_ = v.size_;
    capacity_ = v.capacity_;
    delete[] this->array_;
    array_ = new value_type[capacity_];
    const_iterator src_it = v.cbegin();
    iterator dest_it = this->begin();
    while (src_it != v.cend()) {
      *dest_it = *src_it;
      src_it++;
      dest_it++;
    }

    return *this;
  }

  reference at(size_type pos) {
    if (pos >= this->size())
      throw std::out_of_range("at(): invalid input, index out of bounds");

    return array_[pos];
  }

  reference operator[](size_type pos) { return array_[pos]; }
  const_reference operator[](size_type pos) const { return array_[pos]; }

  const_reference front() {
    const value_type &const_ref = array_[0];

    return const_ref;
  }
  const_reference back() {
    const value_type &const_ref = array_[size_ - 1];

    return const_ref;
  }

  T *data() { return array_; }

  iterator begin() { return iterator(array_); }
  iterator end() { return iterator(array_ + size_); }

  const_iterator cbegin() const { return const_iterator(array_); }
  const_iterator cend() const { return const_iterator(array_ + size_); }

  bool empty() { return !(bool)size_; }
  size_type size() { return size_; }
  size_type max_size() const {
    return std::numeric_limits<size_type>::max() / (2 * sizeof(value_type));
  }

  void reserve(size_type size) {
    if (size > capacity_) {
      int i = 0;
      capacity_ = size;
      value_type *temp = new value_type[capacity_];
      Vector<value_type>::iterator it = this->begin();
      while (it != this->end()) {
        temp[i] = *it;
        i++;
        it++;
      }
      delete[] array_;
      array_ = temp;
    }
  }

  size_type capacity() { return capacity_; }

  void shrink_to_fit() {
    int i = 0;
    capacity_ = this->size();
    value_type *temp = new value_type[capacity_];
    iterator it = this->begin();
    while (it != this->end()) {
      temp[i] = *it;
      i++;
      it++;
    }
    delete[] array_;
    array_ = temp;
  }

  void clear() {
    for (size_type i = 0; i < size_; i++) {
      array_[i] = '\0';
    }
    size_ = 0;
  }

  iterator insert(iterator pos, const_reference value) {
    int count = 0;
    for (iterator it = this->end(); it != pos; it--) {
      count++;
    }
    if (size_ == capacity_) this->reserve(this->size_ * 2);
    iterator it = this->end();
    iterator it_2 = it - 1;
    for (int i = 0; i != count; i++) {
      *it = *it_2;
      it--;
      it_2--;
    }
    *it = value;
    iterator ret = it;
    size_++;

    return ret;
  }

  void erase(iterator pos) {
    iterator it = pos;
    iterator it_2 = pos + 1;
    while (it_2 != this->end()) {
      *it = *it_2;
      it++;
      it_2++;
    }
    *it = '\0';
    size_--;
  }

  void push_back(const_reference value) { this->insert(this->end(), value); }
  void pop_back() { this->erase(this->end() - 1); }

  void swap(Vector &other) {
    value_type *temp = other.data();
    int size = other.size();
    int capacity = other.capacity();

    other.array_ = this->data();
    other.size_ = this->size();
    other.capacity_ = this->capacity();

    this->array_ = temp;
    this->size_ = size;
    this->capacity_ = capacity;
  }

 private:
  size_type size_;
  size_type capacity_;
  value_type *array_;
};
}  // namespace s21

#endif