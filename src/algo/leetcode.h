#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>

#include <vector>
#include <unordered_map>

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
 public:
  vector<int> two_sums_q1(vector<int>& nums, int target);
  int single_number_q136(vector<int>& nums);
  int majority_element_q169(vector<int>& nums);
 public: 
  class lru_cache_q146;
 public:
  
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

/* */
class set2 : public solutions<category::divide_and_conquer>
{
 public:
  int search_insert_position_q35(vector<int>& nums, int target);
 public:
  bool search_a_2d_matrix_q74(vector<vector<int>>& matrix, int targe);
 public:
  
};

/* */
class set3 : public solutions<category::backtracking>
{

};

/* */
class set4 : public solutions<category::dynamic_programming>
{
 public:
  int climb_stairs_q70(int n);
  vector<vector<int>> pascals_triangle_q118(int n);
 public:
  int house_robber_q198(vector<int>& nums);
};

/* */
class set5 : public solutions<category::greedy>
{
 public:
  int best_time_to_buy_and_sell_stock_q121(vector<int>& prices);
};

} /* namespace leetcode */