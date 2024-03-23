#include <bits/stdc++.h>
using namespace std;

class Math {
  int expo(int base, int exp, const int mod) {
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

  int modinv(int x, int mod) {
    return expo(x, mod - 2, mod);
  }

  const int MOD = (int) 1e9 + 7;
  vector<int> fact, invfact;
public:
  Math(int n) {
    fact.resize(n);
    invfact.resize(n);
    fact[0] = invfact[0] = 1;
    for (int i = 1; i < n; i++) {
      fact[i] = (1LL * i * fact[i - 1]) % MOD;
      invfact[i] = modinv(fact[i], MOD);
    }
  }

  int ncr(int n, int r) {
    if (r < 0 || r > n) return 0;
    int ans = fact[n];
    ans = (1LL * ans * invfact[n - r]) % MOD;
    ans = (1LL * ans * invfact[r]) % MOD;
    return ans;
  }
};

int main() {
  freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(false); cin.tie(0);
  Math math(10);
  cout << math.ncr(5, 3) << endl;
  return 0;
}