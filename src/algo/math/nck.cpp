#pragma once


#include <vector>


/* int (4 bytes): -2,147,483,648 ~ 2,147,483,647 (1 ~ 10^9) 
 * long: 
 *   linux/macos: -9,223,372,036,854,775,808 ~ 9,223,372,036,854,775,807 (1 ~ 10^18)
 *   windows: -2,147,483,648 ~ 2,147,483,647 (1 ~ 10^9)
 * long long (8 bytes): -9,223,372,036,854,775,808 ~ 9,223,372,036,854,775,807 (1 ~ 10^18) */
constexpr int p = 1e9 + 7; // 1,000,000,007 is prime and fit 32-bits


/* Pascal triangle: nCk = (n-1)C(k-1) + (n-1)Ck, use when n < 2000;
 * 
 *   n\k 0 1 2 3 4
 *   0   1
 *   1   1 1
 *   2   1 2 1
 *   3   1 3 3 1
 *   4   1 4 6 4 1   */
int nck_pascal(int n, int k) {
  std::vector<std::vector<int>> dp(n+1, std::vector<int>(k+1, 0));
  for (int i = 0; i <= n; ++i) {
    dp[i][0] = 1;
    for (int j = 1; j <= i; ++j) { dp[i][j] = (dp[i-1][j-1] + dp[i-1][j]) % p; }
  }
  return dp[n][k];
}


inline int modexp(int a, int b) {
  int res = 1; a %= p;
  while (b) { if (b & 1) res = res * a % p; a = a * a % p; b >>= 1; }
  return res;
}

/* i! = (i+1)!/(i+1) implies (i!)^{-1} = ((i+1)!)^{-1} * (i+1) */
void factorial(std::vector<int>& fac, std::vector<int>& ifac, int n) {
  for (int i = 1; i <= n; ++i) { fac[i] = i * fac[i-1] % p; }
  ifac[n] = modexp(fac[n], p-2);
  for (int i = n - 1; i >= 0; --i) { ifac[i] = ifac[i+1] * (i+1) % p; }
}

/* nCk = n! / k!(n-k)! mod p = n! * (k!)^{-1} * ((n-k)!)^{-1} mod p
 *   
 *   Fermat's Little Thm: (n!)^{-1} = (n!)^{p-2} mod p
 *    */
int nck(int n, int k) {
  std::vector<int> fac(n+1, 1), ifac(n+1, 1);
  factorial(fac, ifac, n);
  return fac[n] * ifac[k] % p * ifac[n-k] % p;
}
