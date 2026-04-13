#pragma once


/* Count number of ones: Brian Kernighan */
inline int count_ones(int n) {
  int cnt;
  while (n) { n &= n - 1; cnt++; }
  return cnt;
}


/* Bitmask subset enumeration: suppose {0, 1, 2, 3}
 *   case: m = 0001 -> { 1 } 
 *   case: m = 0011 -> { 0, 1 } 
 *   case: m = 0010 -> { 2 } 
 *   case: m = 0111 -> { 0, 1, 2 } */
inline void enum_subsets(int n) {
  for (int m = 0; m < (1 << n); ++m) {
    for (int i = 0; i < n; ++i) {
      if (m >> i & 1) { /* access item at pos i */ }
    }    
  }
}


