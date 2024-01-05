#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int INF = 1e9 + 9;

void path(int u, int v, vector<vector<int>>& par) {
    cout << u << " ";
    if (u != v) path(par[u][v], v, par);
}

int main() {
  // freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(false); cin.tie(0);
  int n, m; cin >> n >> m;
  vector<vector<ll>> dist(n + 1, vector<ll>(m + 1));
  vector<vector<int>> par(n + 1, vector<int>(m + 1));
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (i == j) dist[i][j] = 0;
      else dist[i][j] = INF;
      par[i][j] = j;
    }
  }
  // input
  for (int i = 1; i <= m; ++i) {
    int u, v, w; cin >> u >> v >> w;
    dist[u][v] = w;
  }
  // floyd_warshal
  for (int k = 1; k <= n; ++k) {
    for (int u = 1; u <= n; ++u) {
      for (int v = 1; v <= n; ++v) {
        if (dist[u][v] > dist[u][k] + dist[k][v]) {
          dist[u][v] = dist[u][k] + dist[k][v];
          par[u][v] = par[u][k];
        }
      }
    }
  }
  int u, v; cin >> u >> v;
  if (dist[u][v] == INF) {
    cout << "Infinite" << '\n';
  } else {
    cout << "Distance: " << dist[u][v] << '\n';
    cout << "Path: ";
    path(u, v, par);
    cout << '\n';
  }
  return 0;
}

/*
Time complexity: O(V ^ 3)
E = number of edge
V = number of vertex
*/