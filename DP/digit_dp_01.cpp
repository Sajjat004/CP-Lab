// In the name of Allah, Most Gracious, Most Merciful.
#include <bits/stdc++.h>
using namespace std;

typedef long long      ll;
typedef vector<int>    vi;
typedef vector<ll>     vll;
typedef pair<int, int> pii;
typedef pair<ll, ll>   pll;

const int N   = (int) 2e5 + 5;
const int MOD = (int) 1e9 + 7;
const int INF = (int) 1e9 + 9;

#define nl      '\n'
#define ff      first
#define ss      second
#define szof(x) (int) x.size()
#define all(x)  x.begin(), x.end()

int n;
string s;

ll dp[20][2][5];

ll fun(int pos, int isSmall, int nonZero) {
  if (nonZero > 3) return 0;
  if (pos == n) return 1;
  if (dp[pos][isSmall][nonZero] != -1) return dp[pos][isSmall][nonZero];
  ll ans = 0;
  int limit = s[pos] - '0';
  if (isSmall) limit = 9;
  for (int i = 0; i <= limit; ++i) {
    ans += fun(pos + 1, isSmall | (i < limit), nonZero + (i == 0 ? 0 : 1));
  }
  return dp[pos][isSmall][nonZero] = ans;
}

int main() {
  // freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(false); cin.tie(0);
  int test = 1, tc = 0; cin >> test;
  while (test--) {
    ll m; cin >> m;
    m -= 1;
    s = to_string(m);
    n = szof(s);
    memset(dp, -1, sizeof dp);
    ll lowAns = fun(0, 0, 0);
    cin >> s;
    n = szof(s);
    memset(dp, -1, sizeof dp);
    ll highAns = fun(0, 0, 0);
    cout << highAns - lowAns << nl;
  }
  return 0;
}

// https://codeforces.com/problemset/problem/1036/C
