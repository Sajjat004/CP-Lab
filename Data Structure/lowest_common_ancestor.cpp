#include <bits/stdc++.h>
using namespace std;

const int N = (int) 2e5 + 5;
vector<int> g[N];

class LowestCommonAncestor {
 private:
  vector<int> depth;
  vector<vector<int>> sparseTable;

  void dfs(int u, int par = -1, int d = 0) {
    depth[u] = d;
    sparseTable[u][0] = par;
    for (int k = 1; k <= 20; ++k) {
      if (sparseTable[u][k - 1] == -1) break;
      sparseTable[u][k] = sparseTable[sparseTable[u][k - 1]][k - 1];
    }
    for (int v : g[u]) {
      if (v == par) continue;
      dfs(v, u, d + 1);
    }
  }
 public:
  LowestCommonAncestor(int n, int src) {
    depth.assign(n + 2, 0);
    sparseTable.assign(n + 2, vector<int>(22, -1));
    dfs(src);
  }
  int query(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    for (int k = 20; k >= 0; --k) {
      if ((depth[u] - (1 << k)) >= depth[v]) u = sparseTable[u][k];
    }
    if (u == v) return u;
    for (int k = 20; k >= 0; --k) {
      if (sparseTable[u][k] != -1 and sparseTable[u][k] != sparseTable[v][k]) {
        u = sparseTable[u][k];
        v = sparseTable[v][k];
      }
    }
    return sparseTable[u][0];
  }
};

int main() {
  // freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(false); cin.tie(0);
  int test = 1, tc = 0;
  while (test--) {
    int n, m; cin >> n >> m;
    for (int i = 1; i < n; ++i) {
      int u, v; cin >> u >> v;
      g[u].push_back(v);
      g[v].push_back(u);
    }
    LowestCommonAncestor lca(n, 1);
    while (m--) {
      int u, v; cin >> u >> v;
      cout << lca.query(u, v) << '\n';
    }
  }
  return 0;
}