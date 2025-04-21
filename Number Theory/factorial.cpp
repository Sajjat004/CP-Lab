#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;
const int MOD = 998244353;

int power(int base, int exp, const int mod) {
  int res = 1 % mod;
  base %= mod;
  if (base < 0) base += mod;

  while (exp) {
    if (exp & 1) res = 1LL * res * base % mod;
    base = 1LL * base * base % mod;
    exp >>= 1;
  }

  return res;
}

vector<int> factorial(N, 1);
vector<int> inverseFactorial(N, 1);

void precomputeFactorials(int n, const int mod) {
  for (int i = 2; i <= n; ++i) {
    factorial[i] = 1LL * factorial[i - 1] * i % mod;
  }

  inverseFactorial[n] = power(factorial[n], mod - 2, mod);
  for (int i = n - 1; i >= 0; --i) {
    inverseFactorial[i] = 1LL * inverseFactorial[i + 1] * (i + 1) % mod;
  }
}


int32_t main() {
  ios_base::sync_with_stdio(false); cin.tie(0);

  precomputeFactorials(1e6, MOD);
    
  return 0;
}
