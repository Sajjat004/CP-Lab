#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 2e5 + 5;
const ll INF = 1e16 + 6;

vector<pair<int, ll>> adj[N];
ll dist[N];
int par[N];

void dijkstra(int src, int n) {
  for (int i = 1; i <= n; ++i) dist[i] = INF;
  priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
  pq.push({0, src});
  dist[src] = 0;
  par[src] = 0;
  while (!pq.empty()) {
    ll du = pq.top().first;
    int u = pq.top().second;
    pq.pop();
    if (du != dist[u]) continue;
    for (auto x : adj[u]) {
      int v = x.first;
      ll w = x.second;
      if (dist[v] > (dist[u] + w)) {
        dist[v] = dist[u] + w;
        pq.push({dist[v], v});
        par[v] = u;
      }
    }
  }
}

void path(int u) {
  if (par[u]) path(par[u]);
  cout << u << " ";
}

int main() {
  // freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(false); cin.tie(0);
  int n, m; cin >> n >> m;
  for (int i = 0; i < m; ++i) {
    int u, v; cin >> u >> v;
    ll w; cin >> w;
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
  }
  dijkstra(1, n);
  if (dist[n] == INF) {
    cout << -1 << '\n';
  } else {
    path(n);
    cout << '\n';
  }
  return 0;
}

// problem link: https://codeforces.com/contest/20/problem/C