#include <bits/stdc++.h>
using namespace std;
 
using ll  = long long;
using vll = vector<ll>;
using vi  = vector<int>;
using pll = pair<ll, ll>;
using pii = pair<int, int>;
 
const int N   = (int) 2e5 + 5;
const int MOD = (int) 1e9 + 7;
const int INF = (int) 1e9 + 9;
 
#define nl      '\n'
#define ff      first
#define ss      second
#define szof(x) (int) x.size()
#define all(x)  x.begin(), x.end()
 
// formula for finding large fibonacci value.
// f(2 * k) = f(k) * f(k) + f(k - 1) * f(k - 1)
// f(2 * k + 1) = f(k) * f(k + 1) + f(k - 1) * f(k)
 
map<ll, ll> dp;
 
ll fact(ll n) {
  if (dp.count(n)) return dp[n];
  ll k = n / 2;
  if (n & 1) return dp[n] = (fact(k) * fact(k + 1) + fact(k - 1) * fact(k)) % MOD;
  else return dp[n] = (fact(k) * fact(k) + fact(k - 1) * fact(k - 1)) % MOD;
}
 
int main() {
  // freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(false); cin.tie(0);
  int test = 1, tc = 0;
  while (test--) {
    ll n; cin >> n;
    dp[0] = dp[1] = 1;
    if (n == 0) cout << 0 << nl;
    else cout << fact(n - 1) << nl;
  }
  return 0;
}

// problem link: https://cses.fi/problemset/task/1722