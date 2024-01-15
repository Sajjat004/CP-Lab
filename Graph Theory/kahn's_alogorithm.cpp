#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

vector<int> g[N];

int main() {
  // freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(false); cin.tie(0);
  int n, m; cin >> n >> m;
  vector<int> inDegree(n + 1, 0);
  for (int i = 0; i < m; ++i) {
    int u, v; cin >> u >> v;
    g[u].push_back(v);
    inDegree[v]++;
  }
  queue<int> q;
  for (int i = 1; i <= n; ++i) {
    if (inDegree[i] == 0) q.push(i);
  }
  vector<int> order;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    order.push_back(u);
    for (int v : g[u]) {
      inDegree[v]--;
      if (inDegree[v] == 0) q.push(v);
    }
  }
  if ((int) order.size() < n) {
    cout << "cycle exist\n";
  } else {
    for (int x : order) cout << x << " ";
    cout << '\n';
  }
  return 0;
}

/*
Time Complexity: O(E + V)
E = number of edge
V = number of vertex
*/