#include <bits/stdc++.h>
using namespace std;

#define nl '\n'

int bigMod(int base, int exp, const int mod) {
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

int main() {
  // freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(false); cin.tie(0);
  int test = 1, tc = 0;
  while (test--) {
    int base, exp, mod; cin >> base >> exp >> mod;
    cout << bigMod(base, exp, mod) << nl;
  }
  return 0;
}
