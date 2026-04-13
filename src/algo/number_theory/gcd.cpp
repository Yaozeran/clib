#pragma once


/* Euclid's 
 *   lemma: a = qb + r implies gcd(a, b) = gcd(b, r) */
inline int gcd(int a, int b) {
  return b ? gcd(b, a % b) : a;
}


inline int lcm(int a, int b) {
  return a / gcd(a, b) * b;
}

