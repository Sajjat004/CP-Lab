#include <bits/stdc++.h>
using namespace std;

typedef long long          ll;
typedef long double        ld;
typedef unsigned long long ull;
typedef pair<int, int>     pii;
typedef pair<ll, ll>       pll;
typedef vector<int>        vi;
typedef vector<ll>         vll;

const int N      = (int) 2e5 + 5;
const int mxN    = (int) 1e6 + 6;
const int MOD    = (int) 1e9 + 7;
const int INF    = (int) 1e9 + 9;
const double EPS = (double) 1e-9;

#define all(x)   x.begin(), x.end()
#define szof(x)  (int) x.size()
#define ff       first
#define ss       second
#define pb       push_back
#define nl       '\n'
#define PI       acos(-1.0)
#define debug(x) cerr << #x << " = " << x << '\n';

// problem: https://cses.fi/problemset/task/1683/

vi g[N], rg[N];
vector<bool> used(N, 0);
vi order, comp;

void dfs(int u) {
  used[u] = 1;
  for (auto v : g[u]) {
    if (!used[v]) dfs(v);
  }
  order.pb(u);
}

void dfs1(int u) {
  used[u] = 1;
  comp.pb(u);
  for (auto v : rg[u]) {
    if (!used[v]) dfs1(v);
  }
}

int main() {
  // freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(false); cin.tie(0);
  int test = 1, tc = 0;
  while (test--) {
    int n, m; cin >> n >> m;
    for (int i = 0; i < m; ++i) {
      int u, v; cin >> u >> v;
      g[u].pb(v);
      rg[v].pb(u);
    }
    for (int i = 0; i <= n; ++i) used[i] = 0;
    for (int i = 1; i <= n; ++i) {
      if (!used[i]) {
        dfs(i);
      }
    }

    for (int i = 0; i <= n; ++i) used[i] = 0;
    reverse(all(order));
    int kingdom = 0;
    vi res(n + 2, -1);
    for (auto x : order) {
      if (!used[x]) {
        comp.clear();
        dfs1(x);
        kingdom++;
        for (auto y : comp) res[y] = kingdom;
      }
    }
    cout << kingdom << nl;
    for (int i = 1; i <= n; ++i) cout << res[i] << " \n"[i == n];
  }
  return 0;
}