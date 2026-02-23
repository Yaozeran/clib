#pragma once

#include <utility>
#include <cstddef>
#include <algorithm>

template<typename T>
struct binary_tree_node
{
  typedef T value_t;

  std::pair<value_t, size_t> val_;
  binary_tree_node* left_;
  binary_tree_node* right_;
  int height_;

  binary_tree_node() = default;
  binary_tree_node(value_t val)
      : val_(std::pair<value_t, size_t>(val, 1)), height_(0), left_(nullptr), right_(nullptr) {}
};

template<typename T>
class avl_tree
{

  typedef T value_t;
  typedef binary_tree_node<T> node;

 public:

  avl_tree() = default;

  inline void insert(value_t val) {
    auto node = new node(n);
    insert_helper(node, root_);
  }

  inline void adjust() {}

 private:

  node* root_;

  inline void insert_helper(node* n, node* cur) {
    if (!cur) { 
      cur = std::move(n); 
    } else if (n < cur->val_) {
      insert_helper(n, cur->left_);
    } else if (n > cur->val_) {
      insert_helper(n, cur->right_);
    } else { 
      cur->val_.second++;
      delete n;
      n = nullptr;
    }
  }

  inline int height(const node* n) {
    return n == nullptr ? -1 : n->height_;
  }

  inline void update_height(node* n) {
    n->height_ = std::max(height(n->left_), height(n->right_)) + 1;
  }

  inline int balance_factor(const node* n) {
    return n == nullptr ? 0 : height(n->left_) - height(n->right_);
  }

  inline node* rotate_left(node* n) {
    node* ptr = n->right_;
    n->right_ = ptr->left_;
    ptr->left_ = n;
    update_height(ptr);
    update_height(n);
    return ptr;
  }

  inline node* rotate_right(node* n) {
    node* ptr = n->left_;
    n->left_ = ptr->right_;
    ptr->right_ = n;
    update_height(ptr);
    update_height(n);
    return ptr;
  }

  inline void adjust_helper();
};
