#ifndef S21_LIST_H
#define S21_LIST_H

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <limits>

namespace s21 {
template <typename T>
class List {
 public:
  class ListIterator;
  class ListIteratorConst;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using iterator = ListIterator;
  using const_iterator = ListIteratorConst;
  // конструктор по умолчанию
  List()
      : l_size_(0U),
        head(nullptr),
        tail(nullptr),
        fake(nullptr) {  // 0U - unsigned zero
    fake = new Node;
  }
  // конструктор списка из n элементов
  explicit List(size_type n) : List() {
    while (n > 0) {
      Push_Back(value_type());
      --n;
    }
  }
  // инициализация списка
  explicit List(std::initializer_list<value_type> const &items) : List() {
    for (const auto &item : items) {
      Push_Back(item);
    }
  }
  // конструктор копирования
  List(const List &l) : List() { Copy(l); }
  // конструктор перемещения
  List(List &&l) noexcept : List() {
    l_size_ = l.l_size_;
    Swap(l);
  }
  // деструктор
  ~List() {
    Clear();
    delete fake;
    fake = nullptr;
  }

  List &operator=(List const &l) {
    Clear();
    Copy(l);

    return *this;
  }

  List &operator=(List &&l) noexcept {
    l_size_ = l.l_size_;
    Swap(l);

    return *this;
  }

  const_reference Front() const { return head->data; }

  const_reference Back() const { return tail->data; }

  iterator Begin() noexcept { return iterator(head); }

  const_iterator Cbegin() const noexcept { return const_iterator(head); }

  iterator End() noexcept { return iterator(fake); }

  const_iterator Cend() const noexcept { return const_iterator(fake); }

  bool Empty() { return ((head == nullptr) && (tail == nullptr)); }

  size_type Size() {
    if (!Empty()) {
      size_type n = 0;
      for (iterator it = Begin(); it != End(); ++it) {
        ++n;
      }
    }

    return l_size_;
  }

  size_type Max_Size() noexcept {
    return std::numeric_limits<size_type>::max() / sizeof(Node) / 2;
  }

  void Clear() {
    if (!Empty()) {
      while (head != fake) {
        tail = head->next;
        delete head;
        head = tail;
        --l_size_;
      }
      fake->next = nullptr;
      fake->prev = nullptr;
      head = nullptr;
      tail = nullptr;
      delete fake;
      fake = nullptr;
      l_size_ = 0;
    }
  }

  iterator Insert(iterator idx, value_type value) {
    bool out = false;
    iterator it_b = Begin();
    while (it_b != End()) {
      if (it_b == idx) {
        out = false;
        break;
      }
      out = true;
      ++it_b;
    }
    if (idx == Begin()) {
      Push_Front(value);
      idx = iterator(head);
    } else if (out) {
      Push_Back(value);
      idx = iterator(tail);
    } else {
      Node *newNode = new Node(value);
      Node *tmp = head;
      Node *tmp2 = tmp->next;
      iterator it = Begin();
      --idx;
      while (it != idx) {
        tmp = tmp->next;
        tmp2 = tmp2->next;
        ++it;
      }
      newNode->next = tmp->next;
      newNode->prev = tmp;
      tmp->next = newNode;
      tmp2->prev = newNode;
      ++it;
      ++l_size_;
      return it;
    }
    return idx;
  }

  void Erase(iterator idx) {
    if (l_size_ == 0) return;
    Node *delEl;
    if (idx == End()) {
      delEl = tail;
    } else {
      delEl = head;
      for (iterator it = Begin(); it != idx; ++it) {
        delEl = delEl->next;
      }
    }
    Node *prev = delEl->prev;
    Node *next = delEl->next;
    delete delEl;
    if ((l_size_ > 1) && (prev != nullptr)) {
      prev->next = next;
    }
    if ((next != fake) && (l_size_ > 1)) {
      next->prev = prev;
    }
    if (idx == Begin()) {
      head = next;
    }
    if (idx == End()) {
      tail = prev;
    }
    --l_size_;
  }

  void Push_Back(value_type value) {
    try {
      Node *tmp = new Node;
      tmp->next = nullptr;
      tmp->prev = tail;
      tmp->data = value;
      if (tail != nullptr) {
        tail->next = tmp;
      }
      if (l_size_ == 0) {
        head = tail = tmp;
      } else {
        tail = tmp;
      }
      tail->next = fake;
      fake->prev = tail;
      fake->next = head;
      ++l_size_;
    } catch (std::bad_alloc &err) {
      std::cout << err.what() << std::endl;
    }
  }

  void Pop_Back() { Erase(End()); }

  void Push_Front(value_type value) {
    Node *tmp = new Node;
    tmp->next = head;
    tmp->prev = nullptr;
    tmp->data = value;
    if (l_size_ > 0) {
      head->prev = tmp;
      head = tmp;
    } else {
      head = tail = tmp;
    }
    tail->next = fake;
    fake->prev = tail;
    fake->next = head;
    ++l_size_;
  }

  void Pop_Front() { Erase(Begin()); }

  void Swap(List &other) {
    if (this != &other) {
      std::swap(head, other.head);
      std::swap(tail, other.tail);
      std::swap(fake, other.fake);
      std::swap(l_size_, other.l_size_);
    }
  }

  void Merge(List &other) {
    if (!Empty() && !other.Empty()) {
      iterator it = Begin();
      iterator oit = other.Begin();
      while (it != End()) {
        if (oit != other.End()) {
          if (*it >= *oit) {
            Insert(it, *oit);
            ++oit;
          } else {
            ++it;
          }
        } else {
          break;
        }
      }
      while (oit != other.End()) {
        Insert(it, *oit);
        ++oit;
      }
    } else if (Empty() && !other.Empty()) {
      Copy(other);
    }
    other.Clear();
  }

  void Splice(const_iterator pos, List &other) {
    if (!other.Empty()) {
      iterator pos_c = Begin();
      const_iterator pos_p = Cbegin();
      while (pos_p != pos) {
        ++pos_c;
        ++pos_p;
      }
      iterator it = other.Begin();
      for (; it != other.End(); ++it) {
        Insert(pos_c, *it);
      }
      other.Clear();
    }
  }

  void Reverse() {
    Node *cur = head;
    Node *it = tail;
    size_type mid = Size() / 2;
    for (size_t idx = 0, jdx = Size(); idx < mid; ++idx, --jdx) {
      Swap_Elem(cur->data, it->data);
      cur = cur->next;
      it = it->prev;
    }
  }

  void Unique() {
    iterator next = Begin();
    ++next;
    iterator it = Begin();
    iterator new_it = it;
    for (; it != End(); ++next) {
      ++new_it;
      if (*it == *next) {
        Erase(it);
      }
      it = new_it;
    }
  }

  void Sort() {
    Node *cur = nullptr;
    Node *it = nullptr;
    for (cur = head; cur->next != fake; cur = cur->next) {
      for (it = cur->next; it != fake; it = it->next) {
        if (cur->data > it->data) {
          Swap_Elem(cur->data, it->data);
        }
      }
    }
  }

  void Swap_Elem(value_type &val1, value_type &val2) { std::swap(val1, val2); }

  void Copy(const List<value_type> &obj) {
    Clear();
    Node *tmp = obj.head;
    while (tmp != obj.fake) {
      Push_Back(tmp->data);
      tmp = tmp->next;
    }
  }

 private:
  struct Node {
    value_type data;
    Node *prev;
    Node *next;
    explicit Node(value_type value = value_type(), Node *prev = nullptr,
                  Node *next = nullptr)
        : data(value), prev(prev), next(next) {}
  };

  size_t l_size_;
  Node *head;
  Node *tail;
  Node *fake;

 public:
  class ListIterator {
   public:
    using value_type = T;
    using reference = value_type &;
    using pointer = value_type *;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;

    ListIterator() : cur(nullptr) {}

    explicit ListIterator(Node *cur) : cur(cur) {}

    reference operator*() noexcept { return cur->data; }

    iterator &operator++() noexcept {
      if (cur) {
        cur = cur->next;
      }
      return *this;
    }

    iterator operator++(int) noexcept {
      iterator temp = *this;
      ++(*this);
      return temp;
    }

    iterator &operator--() noexcept {
      if (cur) {
        cur = cur->prev;
      }
      return *this;
    }

    iterator operator--(int) noexcept {
      iterator temp = *this;
      --(*this);
      return temp;
    }

    bool operator==(const iterator &other) const { return cur == other.cur; }

    bool operator!=(const iterator &other) const { return cur != other.cur; }

   private:
    Node *cur;
  };

  class ListIteratorConst {
   public:
    using value_type = T;
    using reference = value_type &;
    using pointer = value_type *;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;

    ListIteratorConst() : cur(nullptr) {}

    explicit ListIteratorConst(Node *cur) : cur(cur) {}

    reference operator*() const noexcept { return cur->data; }

    const_iterator &operator++() noexcept {
      if (cur) {
        cur = cur->next;
      }
      return *this;
    }

    const_iterator operator++(int) noexcept {
      const_iterator temp = *this;
      ++(*this);
      return temp;
    }

    const_iterator &operator--() noexcept {
      if (cur) {
        cur = cur->prev;
      }
      return *this;
    }

    const_iterator operator--(int) noexcept {
      const_iterator temp = *this;
      --(*this);
      return temp;
    }

    bool operator==(const const_iterator &other) const {
      return (cur == other.cur);
    }

    bool operator!=(const const_iterator &other) const {
      return (cur != other.cur);
    }

   private:
    Node *cur;
  };

  template <typename... Args>
  iterator Insert_Many(const_iterator pos, Args &&...args) {
    auto args_v =
        std::initializer_list<value_type>{std::forward<Args>(args)...};
    const_iterator it = Cbegin();
    iterator new_pos = Begin();
    while (it != pos) {
      ++new_pos;
      ++it;
    }

    for (auto const &i : args_v) {
      new_pos = Insert((new_pos), i);
      ++new_pos;
    }
    return new_pos;
  }

  template <typename... Args>
  void Insert_Many_Back(Args &&...args) {
    auto args_v =
        std::initializer_list<value_type>{std::forward<Args>(args)...};
    for (auto const &i : args_v) {
      Push_Back(i);
    }
  }

  template <typename... Args>
  void insert_many_front(Args &&...args) {
    auto args_v =
        std::initializer_list<value_type>{std::forward<Args>(args)...};
    for (auto const &i : args_v) {
      Push_Front(i);
    }
  }
};
}  // namespace s21

#endif