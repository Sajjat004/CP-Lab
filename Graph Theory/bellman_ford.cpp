#include <bits/stdc++.h>
using namespace std;

const int INF = (int) 1e9 + 9;

struct Node {
  int u, v, w;
  Node(int u, int v, int w) {
    this->u = u;
    this->v = v;
    this->w = w;
  }
};

bool bellmanFord(int n, int m, int src, vector<Node>& node, vector<long long>& dist) {
  for (int i = 1; i <= n; ++i) dist[i] = INF;
  dist[src] = 0;
  for (int i = 1; i <= n; ++i) {
    for (auto x : node) {
      if (dist[x.u] < INF and dist[x.v] > dist[x.u] + x.w) {
        if (i == n) return 0;
        dist[x.v] = dist[x.u] + x.w;
      }
    }
  }
  return 1;
}

int main() {
  // freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(false); cin.tie(0);
  int n, m; cin >> n >> m;
  vector<Node> node;
  for (int i = 0; i < m; ++i) {
    int u, v, w; cin >> u >> v >> w;
    node.push_back(Node(u, v, w));
  }
  int src; cin >> src;
  vector<long long> dist(n + 5);
  if (bellmanFord(n, m, src, node, dist)) {
    cout << "Node -> Distance" << '\n';
    for (int i = 1; i <= n; ++i) cout << i << " -> " << dist[i] << '\n';
  } else {
    cout << "Negative cycle exists" << '\n';
  }
  return 0;
}

/*
Time complexity: O(V * E)
E = number of edge
V = number of vertex
*/