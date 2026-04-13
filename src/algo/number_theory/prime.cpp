#pragma once


#include <vector>
#include <utility>


/* O(sqrt{n}) */
inline bool is_prime(int n) {
  if (n < 2) return false;
  for (int i = 2; (long long) i * i <= n; ++i) { if (n % i == 0) return false; }
  return true;
}


/* Sieve of Eratosthenes: O(n?) */
constexpr int len = 1e7+5;
bool np[len];
void get_primes(int n, std::vector<int>& p) {
  np[0] = true; np[1] = true;
  for (int i = 2; i <= n; ++i) {
    if (!np[i]) {
      p.push_back(np[i]);
      // for (int j = i; j <=n; j += i) { np[j] = true; }
      for (long long j = (long long) i * i; j <= n; j += i) { np[j] = true; }
    }
  }
}


void factorize(int n, std::vector<std::pair<int, int>> p) {
  for (int i = 2; i < n; ++i) {
    if (n % i == 0) {
      int e = 0;
      while (n % i == 0) { n /= i; e++; }
      p.emplace_back(i, e);
    }
  }
  if (n > 1) { p.emplace_back(n, 1); }
}
