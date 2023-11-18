#include <bits/stdc++.h>
using namespace std;

const int N = (int) 2e5 + 5;

vector<int> g[N], rg[N];
vector<bool> used(N, 0);
vector<int> order, comp;

void dfs(int u) {
  used[u] = 1;
  for (auto v : g[u]) {
    if (!used[v]) dfs(v);
  }
  order.push_back(u);
}

void dfs1(int u) {
  used[u] = 1;
  comp.push_back(u);
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
      g[u].push_back(v);
      rg[v].push_back(u);
    }
    for (int i = 0; i <= n; ++i) used[i] = 0;
    for (int i = 1; i <= n; ++i) {
      if (!used[i]) {
        dfs(i);
      }
    }

    for (int i = 0; i <= n; ++i) used[i] = 0;
    reverse(order.begin(), order.end());
    int kingdom = 0;
    vector<int> res(n + 2, -1);
    for (auto x : order) {
      if (!used[x]) {
        comp.clear();
        dfs1(x);
        kingdom++;
        for (auto y : comp) res[y] = kingdom;
      }
    }
    cout << kingdom << '\n';
    for (int i = 1; i <= n; ++i) cout << res[i] << " \n"[i == n];
  }
  return 0;
}

// problem: https://cses.fi/problemset/task/1683/