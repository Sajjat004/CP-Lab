// In the name of Allah, Most Gracious, Most Merciful.
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define nl '\n'

string s;
ll dp[20][2][2];
ll dp1[20][2];
int n;

ll fun2(int pos, int isSmall) {
  if (pos == n) return 1;
  if (dp1[pos][isSmall] != -1) return dp1[pos][isSmall];
  ll ans = 0;
  int limit = s[pos] - '0';
  if (isSmall) limit = 9;
  for (int i = 0; i <= limit; ++i) {
    ans += fun2(pos + 1, isSmall | (i < limit));
  }
  return dp1[pos][isSmall] = ans;
}

ll fun(int pos, int isSmall, int hasSmall) {
  if (pos == n) return 0;
  if (dp[pos][isSmall][hasSmall] != -1) return dp[pos][isSmall][hasSmall];
  ll ans = 0;
  int limit = s[pos] - '0';
  if (isSmall) limit = 9;
  for (int i = 0; i <= limit; ++i) {
    ans += fun(pos + 1, isSmall | (i < limit), hasSmall | (i != 0));
    ans += (1LL * i * fun2(pos + 1, isSmall | (i < limit)));
  }
  return dp[pos][isSmall][hasSmall] = ans;
}

int main() {
  // freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(false); cin.tie(0);
  int test = 1, tc = 0; cin >> test;
  while (test--) {
    ll m; cin >> m;
    if (m != 0) m--;
    s = to_string(m);
    n = s.size();
    memset(dp, -1, sizeof dp);
    memset(dp1, -1, sizeof dp1);
    ll dn = fun(0, 0, 0);
    cin >> s;
    n = s.size();
    memset(dp, -1, sizeof dp);
    memset(dp1, -1, sizeof dp1);
    ll up = fun(0, 0, 0);
    cout << up - dn << nl;
  }
  return 0;
}

// https://www.spoj.com/problems/PR003004/
