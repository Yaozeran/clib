#pragma once


#include <cstddef>
#include <cstdint>
#include <memory>
#include <algorithm>

#include <vector>
#include <unordered_map>
#include <stack>
#include <queue>
#include <set>

#include "ds/list.h"


namespace leetcode
{


using namespace std;


enum class category {
  unknown, 
  pointers, divide_and_conquer, backtracking, dynamic_programming, greedy
};


template<category cat>
class solutions { };


/* miscellaneous */
class set0 : public solutions<category::unknown>
{
public: // helper class
  struct tree_node 
  {
    int val;
    tree_node* left;
    tree_node* right;
    tree_node() : val(0), left(nullptr), right(nullptr) {}
    tree_node(int x) : val(x), left(nullptr), right(nullptr) {}
    tree_node(int x, tree_node *left, tree_node *right) : val(x), left(left), right(right) {}
  };
public: // simple
  vector<int> two_sums_q1(vector<int>& nums, int target);
  int single_number_q136(vector<int>& nums);
  int majority_element_q169(vector<int>& nums); 
  vector<string> binary_tree_path_q257(tree_node* n);
public: // medium
  int longest_substring_without_repeating_characters(string s);
  class lru_cache_q146;
  vector<vector<int>> binary_tree_level_order_traversal_q102(tree_node* root);
  vector<vector<int>> path_sum_ii_q113(tree_node* root, int target);
  vector<int> lexicographical_numbers_q386(int n);
  vector<int> find_all_anagrams_in_a_string_q438(string s, string p);
  int subarray_sum_equals_k_q560(vector<int>& nums, int k);
public: // hard
  int binary_tree_maximum_path_sum_q124(tree_node* root);
};


/* */
class set1 : public solutions<category::pointers>
{
public: 
  linked_list_node<int>* intersection_of_two_linked_list_q160(linked_list_node<int>* a, linked_list_node<int>* b);
  linked_list_node<int>* reverse_linked_list_q206(linked_list_node<int>* n);
public:
  int container_with_most_water_q11(vector<int>& height);
public:
  int trapping_rain_water_q42(vector<int>& height);
};


class set2 : public solutions<category::divide_and_conquer>
{
public:
  int search_insert_position_q35(vector<int>& nums, int target);
public:
  bool search_a_2d_matrix_q74(vector<vector<int>>& matrix, int targe);
public:
  
};


class set3 : public solutions<category::backtracking>
{
public:

public:
  vector<vector<int>> permutations_q46(vector<int>& nums);
  vector<vector<int>> subsets_q78(vector<int>& nums);
  vector<string> letter_combinations_of_a_phone_number_q17(string digits);
  vector<vector<int>> combination_sum_q39(vector<int>& candidates, int target);
public:

};


class set4 : public solutions<category::dynamic_programming>
{
public:
  int climb_stairs_q70(int n);
  vector<vector<int>> pascals_triangle_q118(int n);
public:
  int house_robber_q198(vector<int>& nums);
  int perfect_squares_q279(int n);
  int coin_change_q322(vector<int>& coins, int amount);
};


/* */
class set5 : public solutions<category::greedy>
{
public:
  int best_time_to_buy_and_sell_stock_q121(vector<int>& prices);
public:
  bool jump_game_q55(vector<int>& nums);
  int jump_game_ii_q55(vector<int>& nums);
  vector<int> partition_labels_q763(string s);
public:

};


} // namespace leetcode