#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int N = 1e5 + 5;

class Math {
  vector<int> factorial;
  vector<int> inverseFactorial;

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

  int modInverse(int a, const int mod) {
    return power(a, mod - 2, mod);
  }

  void buildFactorial(int n, const int mod) {
    factorial[0] = 1;
    for (int i = 1; i <= n; ++i) {
      factorial[i] = 1LL * factorial[i - 1] * i % mod;
    }

    inverseFactorial[n] = power(factorial[n], mod - 2, mod);
    for (int i = n - 1; i >= 0; --i) {
      inverseFactorial[i] = 1LL * inverseFactorial[i + 1] * (i + 1) % mod;
    }
  }

public:
  Math(int n, const int mod) {
    factorial.resize(n + 1);
    inverseFactorial.resize(n + 1);

    buildFactorial(n, mod);
  }

  int ncr(int n, int r, const int mod) {
    if (r < 0 || r > n) return 0;

    int ans = factorial[n];
    ans = (1LL * ans * inverseFactorial[n - r]) % mod;
    ans = (1LL * ans * inverseFactorial[r]) % mod;

    return ans;
  }
};

int32_t main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  Math math(N, MOD);

  int n, k; cin >> n >> k;
  cout << math.ncr(n + k - 1, k - 1, MOD) << '\n';

  return 0;
}

// You have to find the number of ways to distribute n candies among k children. We solved this problem using stars and bars principle, which is a combinatorial method for distributing indistinguishable objects (candies) into distinguishable boxes (children).

// Resouce: CP Algorithm - https://cp-algorithms.com/combinatorics/stars_and_bars.html
