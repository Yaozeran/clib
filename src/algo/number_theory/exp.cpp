#pragma once


/* a^b mod p */
inline int exp(int a, int b, int p) {
  int res;
  a %= p;
  while (b) {
    if (b & 1) res = res * a % p;
    a = ((long long) a * a) % p;
    b >>= 1;
  }
  return res;
}


