#include <bits/stdc++.h>
using namespace std;

int main() {
  // freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(false); cin.tie(0);
  int n, m; cin >> n >> m;
  vector<int> adj[n + 1];
  vector<int> inDegree(n + 1, 0);
  for (int i = 0; i < m; ++i) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v);
    inDegree[v]++;
  }
  queue<int> q;
  for (int i = 1; i <= n; ++i) {
    if (inDegree[i] == 0) q.push(i);
  }
  vector<int> topoOrder;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    topoOrder.push_back(u);
    for (int v : adj[u]) {
      inDegree[v]--;
      if (inDegree[v] == 0) q.push(v);
    }
  }
  if ((int) topoOrder.size() != n) cout << "Acyclic exist" << '\n';
  else {
    cout << "Topological Order: ";
    for (int x : topoOrder) cout << x << " ";
    cout << '\n';
  } 
  return 0;
}