#pragma once

#include <cstddef>
#include <optional>

/* A node of a double linked list
 * */
template<typename T>
struct linked_list_node
{
  typedef T value_type;

  linked_list_node<value_type>* prev;
  linked_list_node<value_type>* next;
  value_type data;
  
  linked_list_node() : prev(nullptr), next(nullptr) {}
  explicit linked_list_node(value_type d) : data(d), prev(nullptr), next(nullptr) {}
};

/* A double linked list
 * */
template<typename T>
class linked_list
{
  typedef T value_type;
  typedef linked_list_node<T> node;

 public:

  linked_list() : head_(nullptr), tail_(nullptr) {}

  ~linked_list() {

  }

  inline bool empty() const { return head_ == nullptr; }

  inline size_t size() const {
    if (this->empty()) return 0;
    size_t t = 1;
    node* ptr = head_;
    while (ptr != tail_) {
      t++;
      ptr = ptr->next;
    }
    return t;
  }

  inline void push_back(node* n) {
    if (this->empty()) {
      head_ = tail_ = n;
    } else {
      tail_->next = n;
      n->prev = tail_;
      tail_ = n;
    }
    n->next = nullptr;
  }

  inline void push_back(value_type val) {
    node* n = new node(val);
    push_back(n);
  }

  inline void push_front(node* n) {
    if (this->empty()) { 
      head_ = tail_ = n;
    } else {
      n->next = head_;
      head_->prev = n;
      head_ = n;
    }
    n->prev = nullptr;
  }
  
  inline void push_front(value_type val) {
    node* n = new node(val);
    this->push_front(n);
  }

  inline std::optional<value_type> pop_back() {
    if (this->empty()) return std::nullopt;
    node* ptr = tail_;
    value_type ret = tail_->data;
    if (head_ == tail_) {
      head_ = tail_ = nullptr;
    } else {
      tail_->prev->next = nullptr;
      tail_ = tail_->prev;
    }
    delete ptr;
    return ret;
  }

  inline std::optional<value_type> pop_front() {
    if (this->empty()) return std::nullopt;
    node* ptr = head_;
    value_type ret = head_->val_;
    if (head_ == tail_) {
      head_ = tail_ = nullptr;
    } else {
      head_->next->prev = nullptr;
      head_ = head_->next;
    }
    delete ptr;
    return ret;
  }

  inline void sort() {

  }

  inline void print() {
    
  }

 private:

  node* head_;
  node* tail_;

};
