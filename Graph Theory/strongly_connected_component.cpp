#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
vector<int> adj[N];
vector<int> tadj[N];
vector<bool> visited(N);
vector<int> order, component;

void dfs(int u) {
  visited[u] = 1;
  for (int v : adj[u]) {
    if (!visited[v]) dfs(v);
  }
  order.push_back(u);
}

void dfs1(int u) {
  visited[u] = 1;
  component.push_back(u);
  for (int v : tadj[u]) {
    if (!visited[v]) dfs1(v);
  }
}

int main() {
  // freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(false); cin.tie(0);
  int n, m; cin >> n >> m;
  for (int i = 0; i < m; ++i) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v);
    tadj[v].push_back(u);
  }
  for (int i = 0; i <= n; ++i) visited[i] = 0;
  for (int i = 1; i <= n; ++i) {
    if (!visited[i]) dfs(i);
  }
  for (int i = 1; i <= n; ++i) visited[i] = 0;
  reverse(order.begin(), order.end());
  int kingdom = 0;
  vector<int> ans(n + 1, 0);
  for (int i : order) {
    if (!visited[i]) {
      component.clear();
      dfs1(i);
      ++kingdom;
      for (int x : component) ans[x] = kingdom;
    }
  }
  cout << kingdom << '\n';
  for (int i = 1; i <= n; ++i) cout << ans[i] << " \n"[i == n];
  return 0;
}

/*
problem: https://cses.fi/problemset/task/1683/
Time Complexity: O(E + V)
E = number of edge
V = number of vertex
*/