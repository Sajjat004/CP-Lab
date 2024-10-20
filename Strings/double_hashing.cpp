#include <bits/stdc++.h>
using namespace std;

class Hashing {
  static const int MOD = (int) 1e9 + 7;
  static const int N = (int) 1e6;
  static int add(int a, int b, int mod) { a += b; return a >= mod ? a - mod : a < 0 ? a + mod : a; }
  static int mult(int a, int b, int mod) { return 1LL * a * b % mod; }
  static int power(int base, int exp, const int mod) {
    int res = 1;
    base %= mod;
    if (base < 0) base += mod;
    while (exp) {
      if (exp & 1) res = (1LL * res * base) % mod;
      base = (1LL * base * base) % mod;
      exp >>= 1;
    }
    return res;
  }
  static int get(char ch) { return ch - 'a' + 1; }
  static const int MOD1 = 127657753, MOD2 = 987654319;
  static const int BASE1 = 137, BASE2 = 277;

  static vector<pair<int, int>> pw, invPw;
  vector<pair<int, int>> hash;

  int n;
  string s;

  void build() {
    hash.push_back({0, 0});
    for (int i = 0; i < n; ++i) {
      pair<int, int> p;
      p.first = add(hash[i].first, mult(get(s[i]), pw[i].first, MOD1), MOD1);
      p.second = add(hash[i].second, mult(get(s[i]), pw[i].second, MOD2), MOD2);
      hash.push_back(p);
    }
  }

  void preCalculate() {
    static bool calculated = false;
    if (calculated) return;

    static const int inveMod1 = power(BASE1, MOD1 - 2, MOD1);
    static const int inveMod2 = power(BASE2, MOD2 - 2, MOD2);

    pw.assign(N + 2, {1, 1});
    invPw.assign(N + 2, {1, 1});
    for (int i = 1; i <= N; ++i) {
      pw[i].first = mult(pw[i - 1].first, BASE1, MOD1);
      pw[i].second = mult(pw[i - 1].second, BASE2, MOD2);
      invPw[i].first = mult(invPw[i - 1].first, inveMod1, MOD1);
      invPw[i].second = mult(invPw[i - 1].second, inveMod2, MOD2);
    }
  }

public:
  Hashing(string _s) {
    s = _s;
    n = s.size();
    preCalculate();
    build();
  }

  pair<int, int> getHash(int l, int r) {
    pair<int, int> p;
    p.first = mult(add(hash[r].first, -hash[l - 1].first, MOD1), invPw[l - 1].first, MOD1);
    p.second = mult(add(hash[r].second, -hash[l - 1].second, MOD2), invPw[l - 1].second, MOD2);
    return p;
  }
};

vector<pair<int, int>> Hashing::pw;
vector<pair<int, int>> Hashing::invPw;

int main() {
  // freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(false); cin.tie(0);

  string s, t; cin >> s >> t;
  int n = s.size(), m = t.size();
  Hashing hash(s);
  auto hs = Hashing(t).getHash(1, m);
  int ans = 0;
  for (int i = 1; i + m - 1 <= n; ++i) {
    if (hash.getHash(i, i + m - 1) == hs) ans++;
  }
  cout << ans << '\n';

  return 0;
}

// problem link: https://cses.fi/problemset/task/1753/