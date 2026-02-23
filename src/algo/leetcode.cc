#include "leetcode.h"

namespace leetcode
{

/* set zero */

vector<int> set0::two_sums_q1(vector<int>& nums, int target) {
  vector<int> ret;
  unordered_map<int, int> map;
  for (int i = 0; i < nums.size(); ++i) {
    int t = target - nums[i];
    auto iter = map.find(t);
    if (iter != map.end()) {
      ret.push_back(i);
      ret.push_back(iter->second);
      return ret;
    }
    map.emplace(nums[i], i);
  }
  return ret;
}

int set0::single_number_q136(vector<int>& nums) {
  int n;
  for (int i = 0; i < nums.size(); ++i) n ^= nums[i];
  return n;
}

int set0::majority_element_q169(vector<int>& nums) {
  unordered_map<int, int> map;
  int cnt = 0, ret;
  for (int i = 0; i < nums.size(); ++i) {
    auto iter = map.find(nums[i]);
    if (iter != map.end()) {
      map[nums[i]] = 1;
    } else { iter->second++; }
    if (iter->second > cnt) {
      ret = nums[i];
      cnt = iter->second;
    }
  }
  return ret;
}

class set0::lru_cache_q146
{
 public:

  class lru_linked_list
  {
   public:
    struct node {
      int key;
      int val;
      node* prev;
      node* next;
      node(int k, int v) : key(k), val(v), prev(nullptr), next(nullptr) {}
    };

   public: 
    lru_linked_list() : head_(nullptr), tail_(nullptr) {}
    
    ~lru_linked_list() {

    }

    bool empty() { return !head_; }

    void disconnect(node* n) {
      if (n->prev) {
        n->prev->next = n->next;
        n->prev = nullptr;
      }
      if (n->next) {
        n->next->prev = n->prev;
        n->next = nullptr;
      }
    }

    void push_back(node* n) {
      if (this->empty()) head_ = tail_ = n;
      tail_->next = n;
      n->prev = tail_;
      tail_ = n;
    }

    void push_front(node* n) {
      if (this->empty()) head_ = tail_ = n;
      head_->prev = n;
      n->next = head_;
      head_ = n;
    }

    void pop_back() {
      if (this->empty()) return;
      node* ptr = tail_;
      if (head_ == tail_) head_ = tail_ = nullptr;
      tail_->prev->next = nullptr;
      tail_ = tail_->prev;
      delete ptr;
      return;
    }

    void pop_front() {
      if (this->empty()) return;
      node* ptr = head_;
      if (head_ == tail_) head_ = tail_ = nullptr;
      head_->next->prev = nullptr;
      head_ = head_->next;
      delete ptr;
      return;
    }    

    node* head() { return head_; }
    node* tail() { return tail_; }

   private:
    node* head_;
    node* tail_;
  };
  typedef lru_linked_list::node node;

 public: 

  lru_cache_q146(int capacity) : data_(), map_() {}

  int get(int key) {
    auto iter = map_.find(key);
    if (iter == map_.end()) return -1;
    node* ptr = iter->second;
    data_.disconnect(ptr);
    data_.push_front(ptr);
    return ptr->val;
  }

  int put(int key, int value) {
    node* ptr = new node(key, value);
    data_.push_front(ptr);
    map_.erase(data_.tail()->key);
    data_.pop_back();
  }

 private:
  
  lru_linked_list data_;
  unordered_map<int, node*> map_;

};

/* set one */

linked_list_node<int>* set1::intersection_of_two_linked_list_q160(linked_list_node<int>* a, linked_list_node<int>* b) {
  linked_list_node<int>* ptr_a = a; 
  linked_list_node<int>* ptr_b = b;
  while (ptr_a != ptr_b) {
    if (ptr_a == nullptr) { 
      ptr_a = a;
    } else { ptr_a = ptr_a->next; }
    if (ptr_b == nullptr) {
      ptr_b = b;
    } else { ptr_b = ptr_b->next; }
  }
  return ptr_a;
}

linked_list_node<int>* set1::reverse_linked_list_q206(linked_list_node<int>* n) {
  linked_list_node<int>* prev = nullptr;
  linked_list_node<int>* ptr = n;
  while (ptr != nullptr) {
    linked_list_node<int>* tmp = ptr->next;
    ptr->next = prev;
    prev = ptr;
    ptr = tmp;
  }
  return ptr;
}

int set1::container_with_most_water_q11(vector<int>& height) {
  size_t i = 0, j = height.size() - 1;
  int ret = height[i] * height[j];
  while (i < j) {
    if (height[i] < height[j]) {
      int tmp = height[++i] * height[j];
      if (ret < tmp) ret = tmp;
    } else {
      int tmp = height[i] * height[--j];
      if (ret < tmp) ret = tmp;
    }
  }
  return ret;
}

int set1::trapping_rain_water_q42(vector<int>& height) {
  size_t i = 0, j = height.size() - 1;
  int lmax = height[i], rmax = height[j], ret = 0;
  while (i < j) {
    if (height[i] < height[j]) {
      i++;
      if (height[i] > lmax) lmax = height[i];
      ret += lmax < rmax ? lmax - height[i] : rmax - height[i];
    } else {
      j--;
      if (height[j] > rmax) rmax = height[j];
      ret += lmax < rmax ? lmax - height[i] : rmax - height[i];
    }
  }
  return ret;
}

/* set two */

int set2::search_insert_position_q35(vector<int>& nums, int target) {
  int i = 0, j = nums.size() - 1;
  while (i <= j) {
    int mid = (i + j) / 2;
    if (target < nums[mid]) {
      j = mid - 1;
    } else if (nums[mid] < target) {
      i = mid + 1;
    } else { return mid; }
  }
  return i;
}

bool set2::search_a_2d_matrix_q74(vector<vector<int>>& matrix, int target) {
  int top = 0, bot = matrix.size() - 1;
  while (top <= bot) {
    int mid = (top + bot) / 2;
    if (target < matrix[mid][0]) {
      bot = mid - 1;
    } else if (target > matrix[mid][0]) {
      top = mid + 1;
    } else { return true; }
  }
  int row = top, i = 0, j = matrix[row].size() - 1;
  while (i <= j) {
    int mid = (i + j) / 2;
    if (target < matrix[row][mid]) {
      j = mid - 1;
    } else if (matrix[row][mid] < target) {
      i = mid + 1;
    } else { return true; }
  }
  return false;
}

/* set four */

int set4::climb_stairs_q70(int n) {
  if (n == 1 || n == 2) return n;
  vector<int> dp(n + 1);
  dp[1] = 1;
  dp[2] = 2;
  for (int i = 3; i < n + 1; ++i) {
    dp[i] = dp[i - 1] + dp[i - 2];
  }
  return dp[n];
}

vector<vector<int>> set4::pascals_triangle_q118(int n) {
  vector<vector<int>> ret;
  ret[0] = vector<int>{1};
  if (n == 1) return ret;
  ret[1] = vector<int>{1, 1};
  if (n == 2) return ret;
  for (int i = 2; i < n; ++i) {
    vector<int> temp{};
    for (int j = 0; j < i + 1; ++j) {
      if (j == 0 || j == i) {
        temp[j] = 1;
      } else {
        temp[j] = ret[i - 1][j - 1] + ret[i - 1][j];
      }
    }
    ret[i] = temp;
  }
}

int set4::house_robber_q198(vector<int>& nums) {
  
}

/* set five */

int set5::best_time_to_buy_and_sell_stock_q121(vector<int>& prices) {

}

} /* namespace leetcode */