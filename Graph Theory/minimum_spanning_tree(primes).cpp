#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
vector<pair<int, int>> adj[N];
vector<bool> visited(N, 0);

int minimumSpanningTree() {
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
  pq.push({0, 1});
  int cost = 0;
  while (!pq.empty()) {
    int u = pq.top().second;
    int w = pq.top().first;
    pq.pop();
    if (visited[u]) continue;
    visited[u] = 1;
    cost += w;
    for (auto [v, w] : adj[u]) {
      if (!visited[v]) pq.push({w, v});
    }
  }
  return cost;
}

int main() {
  // freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(false); cin.tie(0);
  int n, m; cin >> n >> m;
  for (int i = 1; i <= m; ++i) {
    int u, v, w; cin >> u >> v >> w;
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
  }
  cout << minimumSpanningTree() << '\n';
  return 0;
}