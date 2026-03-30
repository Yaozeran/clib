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


void dfs_q257(set0::tree_node* n, string& s, vector<string>& ret) {
  int len = s.size();
  s.append(to_string(n->val));
  if (!(n->left || n->right)) {
    ret.push_back(s);
  } else {
    s.append("->");
    if (n->left) dfs_q257(n->left, s, ret);
    if (n->right) dfs_q257(n->right, s, ret);
  }
  s.erase(len);
  return;
}
vector<string> set0::binary_tree_path_q257(tree_node* n) {
  vector<string> ret;
  string s;
  dfs_q257(n, s, ret);
  return ret;
}


int set0::longest_substring_without_repeating_characters(string s) {
  unordered_map<char, int> chars;
  int i = 0, j = 0, ret = 0, temp = 0;
  while (i != s.size()) {
    auto iter = chars.find(s[i]);
    if (iter != chars.end()) { 
      j = max(j, iter->second + 1);
      iter->second = i;
    } else { chars.emplace(s[i], i); }
    i++;
    ret = max(ret, i - j);
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

}; // set0::lru_cache_q146


vector<vector<int>> set0::binary_tree_level_order_traversal_q102(tree_node* root) {
  vector<vector<int>> ret{};
  if (root == nullptr) return ret;
  queue<tree_node*> nodes;
  nodes.push(root);
  while (!nodes.empty()) {
    vector<int> level_vals;
    int len = nodes.size();
    for (int i = 0; i < len; ++i) {
      tree_node* ptr = nodes.front();
      level_vals.push_back(ptr->val);
      if (ptr->left != nullptr) nodes.push(ptr->left);
      if (ptr->right != nullptr) nodes.push(ptr->right);
      nodes.pop();
    }
    ret.push_back(level_vals);
  }
  return ret;
}


void dfs_q113(set0::tree_node* n, int target, int temp, vector<int>& path, vector<vector<int>>& ret) {
  if (n->left == nullptr && n->right == nullptr) {
    if (temp + n->val != target) {
      return;
    } else {
      path.push_back(n->val);
      ret.push_back(path);
      path.pop_back();
      return;
    }
  } else {
    path.push_back(n->val);
    if (n->left != nullptr) { dfs_q113(n->left, target, temp + n->val, path, ret); }
    if (n->right != nullptr) { dfs_q113(n->right, target, temp + n->val, path, ret); }
    path.pop_back();
    return;
  }
}
vector<vector<int>> set0::path_sum_ii_q113(tree_node* root, int target) {
  vector<vector<int>> ret;
  if (root == nullptr) return ret;
  vector<int> path;
  dfs_q113(root, target, 0, path, ret);
  return ret;
}


vector<int> set0::lexicographical_numbers_q386(int n) { 
  vector<int> ret; // n = 120: 1, 10, 100, 101, ..., 11, 110, 111, 112, 113, 114, ..., 12, 120, 13, 14, ..., 20
  int cnt = 1;
  for (int i = 0; i < n; ++i) {
    ret.push_back(cnt);
    if (cnt * 10 <= n) {
      cnt *= 10;
    } else {
      if (cnt > n) cnt /= 10;
      cnt++;
      while (cnt % 10 == 0) { cnt /= 10; }
    }
  }
  return ret;
}


vector<int> set0::find_all_anagrams_in_a_string_q438(string s, string p) {
  if (s.size() < p.size()) return {};
  vector<int> ret, scnt(26, 0), pcnt(26, 0);
  for (int i = 0; i < p.size(); ++i) {
    scnt[s[i] - 'a']++;
    pcnt[p[i] - 'a']++;
  }
  if (scnt == pcnt) ret.push_back(0);
  for (int i = p.size(); i < s.size(); ++i) {
    scnt[s[i] - 'a']++;
    int j = i - p.size();
    scnt[s[j] - 'a']--;
    if (scnt == pcnt) ret.push_back(j + 1);
  }
  return ret;
}


int set0::subarray_sum_equals_k_q560(vector<int>& nums, int k) {
  int i = 0, j = 0, sum = nums[i];
  unordered_map<int, int> sums;
  while (i < nums.size()) {
    i++;
    sum += nums[i];
    sums.emplace();
  }
}


std::pair<int, int> dfs_q124(set0::tree_node* n) {
  if (!n->left && !n->right) { return {n->val, n->val}; } 
  int f, s; // the first is connected with only current node, the second is finished connecting from left to n to right
  std::pair<int, int> l, r;
  if (n->left) l = dfs_q124(n->left);
  if (n->right) r = dfs_q124(n->right);
  if (n->left && n->right) {
    f = max({l.first + n->val, r.first + n->val, n->val});
    s = max({l.second, r.second, n->val, l.first + n->val, r.first + n->val, l.first + n->val + r.first});
  } else if (n->left) {
    f = max(l.first + n->val, n->val);
    s = max({l.second, n->val, l.first + n->val});
  } else {
    f = max(r.first + n->val, n->val);
    s = max({r.second, n->val, r.first + n->val});
  }
  return {f, s};
}
int set0::binary_tree_maximum_path_sum_q124(tree_node* root) {
  auto p = dfs_q124(root);
  return max(p.first, p.second);
}


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


/* set three */


void helper_q46(vector<int>& nums, vector<bool>& selected, vector<int>& temp, vector<vector<int>>& ret) {
  if (temp.size() == nums.size()) {
    ret.push_back(temp);
    return;
  };
  for (int i = 0; i < nums.size(); ++i) {
    if (!selected[i]) {
      temp.push_back(nums[i]);
      selected[i] = true;
      helper_q46(nums, selected, temp, ret);
      selected[i] = false;
      temp.pop_back();
      return;
    } else return;
  }
}
vector<vector<int>> set3::permutations_q46(vector<int>& nums) {
  vector<vector<int>> ret;
  vector<bool> selected(nums.size(), false);
  vector<int> temp(nums.size());
  helper_q46(nums, selected, temp, ret);
  return ret;
}


void helper_q78(vector<int>& nums, vector<vector<int>>& ret, vector<int>& path, int s) {
  for (int i = s; i < nums.size(); ++i) {
    path.push_back(nums[i]);
    ret.push_back(path);
    helper_q78(nums, ret, path, i + 1);
    path.pop_back();
  }
}
vector<vector<int>> set3::subsets_q78(vector<int>& nums) {
  vector<vector<int>> ret;
  vector<int> path;
  int s = 0;
  helper_q78(nums, ret, path, s);
  return ret;
}


void helper_q17(string& digits, string& letters, vector<string>& ret, unordered_map<char, string>& data) {
  if (digits.empty()) {
    ret.push_back(letters);
    return; 
  }
  auto iter = data.find(digits[0]);
  for (char c : iter->second) {
    letters.push_back(c);
    std::string sub = digits.substr(1);
    helper_q17(sub, letters, ret, data);
    letters.pop_back();
  }
}
vector<string> set3::letter_combinations_of_a_phone_number_q17(string digits) {
  vector<string> ret;
  unordered_map<char, string> data = {
    {'2', "abc"},
    {'3', "def"},
    {'4', "ghi"},
    {'5', "jkl"},
    {'6', "mno"},
    {'7', "pqrs"},
    {'8', "tuv"},
    {'9', "wxyz"}
  };
  string letters;
  helper_q17(digits, letters, ret, data);
  return ret;
}


void helper_q39(vector<vector<int>>& ret, vector<int>& candidates, int t, vector<int>& ctx, int s) {
  if (!t) {
    ret.push_back(ctx);
    return;
  }
  for (int i = s; i < candidates.size(); ++i) {
    if (candidates[i] <= t) {
      ctx.push_back(candidates[i]);
      helper_q39(ret, candidates, t - candidates[i], ctx, i);
      ctx.pop_back();
    } else return;
  }
}
vector<vector<int>> set3::combination_sum_q39(vector<int>& candidates, int target) {
  vector<vector<int>> ret;
  vector<int> path;
  int s = 0;
  helper_q39(ret, candidates, target, path, s);
  return ret;
}


/* set four */


int set4::climb_stairs_q70(int n) {
  if (n == 1 || n == 2) return n;
  int a = 1, b = 2;
  for (int i = 2; i < n; ++i) {
    int t = a + b;
    a = b;
    b = t;
  }
  return b;
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
  if (nums.size() == 1) return nums[0];
  if (nums.size() == 2) return max(nums[0], nums[1]);
  vector<int> dp;
  dp[0] = nums[0];
  dp[1] = max(nums[0], nums[1]);
  for (int i = 2; i < nums.size(); ++i) {
    dp[i] = max(nums[i] + dp[i - 2], dp[i - 1]);
  }
  return dp[nums.size() - 1];
}


int set4::perfect_squares_q279(int n) {
  if (n < 4) return n;
  vector<int> dp(n + 1);
  dp[0] = 0;
  for (int i = 1; i < n + 1; ++i) {
    dp[i] = i;
    for (int j = 1; j * j < i + 1; ++j) {
      dp[i] = min(dp[i], dp[i - j * j] + 1);
    }
  }
  return dp[n];
}


int set4::coin_change_q322(vector<int>& coins, int amount) {
  vector<vector<int>> dp(coins.size(), vector<int>(amount + 1, 0));
  int inf = amount + 1;
  for (int i = 0; i < amount + 1; ++i) {
    dp[0][i] = inf;
  }
  for (int i = 0; i < coins.size(); ++i) {
    for (int j = 1; j < amount + 1; ++j) {
      if (coins[i] < amount) {
        dp[i][j] = dp[i - 1][j];
      } else {
        dp[i][j] = min(dp[i - 1][j], dp[i][j - 1] + 1);
      }
    }
  }
  return dp[coins.size() - 1][amount] == inf ? -1 : dp[coins.size() - 1][amount];
}


/* set five */


int set5::best_time_to_buy_and_sell_stock_q121(vector<int>& prices) {
  int b = prices[0], p = 0;
  for (int i = 0; i < prices.size(); ++i) {
    b = min(b, prices[i]);
    p = max(p, prices[i] - b);
  }
  return p;
}


bool set5::jump_game_q55(vector<int>& nums) {
  if (nums.size() == 1) return true;
  bool f;
  int i = 0, j = 0;
  while (i < nums.size()) {
    if (nums[i] == 0 && j <= i) break;
    j = max(j, i + nums[i]);
    if (j > nums.size()) f = true;
    ++i;
  }
  return f;
}


int set5::jump_game_ii_q55(vector<int>& nums) {
  if (nums.size() == 1) { return 0; }
  int ret = 0, i = 0; 
  while (i < nums.size()) {
    if (i + nums[i] >= nums.size() - 1) return ret + 1;
    int to = i, r = i;
    for (int j = 1; j < nums[i] + 1; ++j) { 
      if (r < i + j + nums[i + j]) { 
        to = i + j;
        r = i + j + nums[i + j];
      }
    }
    i = to;
    ret++;
  }
  return ret;
}


vector<int> set5::partition_labels_q763(string s) {
  vector<int> ret;
  unordered_map<char, int> data;
  for (int i = 0; i < s.size(); ++i) { data[s[i]] = i; }
  int t, cnt;
  for (int i = 0; i < s.size(); ++i) {
    auto iter = data.find(s[i]);
    t = max(t, iter->second);
    cnt++;
    if (i == t) {
      ret.push_back(cnt);
      cnt = 0;
    }
  }
  return ret;
}


} /* namespace leetcode */