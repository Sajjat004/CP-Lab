#include <bits/stdc++.h>
using namespace std;

class Dsu {
  struct Data {
    int par, rank;
    data() {
      par = rank = 0;
    }
  };
  vector<Data> graph;

  int root(int x) {
    return graph[x].par = graph[x].par == x ? x : root(graph[x].par);
  }
public:
  Dsu(int n) {
    graph.resize(n + 5);
    for (int i = 0; i <= n; ++i) {
      graph[i].par = i;
      graph[i].rank = 0;
    }
  }
  bool merge(int a, int b) {
    int x = root(a);
    int y = root(b);
    if (x == y) return false;
    if (graph[x].rank < graph[y].rank) swap(x, y);
    graph[y].par = x;
    if (graph[x].rank == graph[y].rank) graph[x].rank++;
    return true;
  }
};

struct Edge {
  int w, u, v;
  Edge(int w, int u, int v) {
    this->w = w;
    this->u = u;
    this->v = v;
  }
};

int minimunSpanningTree(vector<Edge> edge, int n) {
  sort(edge.begin(), edge.end(), [] (Edge a, Edge b) -> bool {
    return a.w < b.w;
  });
  Dsu dsu(n);
  int cost = 0;
  for (auto [w, u, v] : edge) {
    if (dsu.merge(u, v)) {
      cost += w;
    }
  }
  return cost;
}

int main() {
  // freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(false); cin.tie(0);
  int n, m; cin >> n >> m;
  vector<Edge> edge;
  for (int i = 0; i < m; ++i) {
    int u, v, w; cin >> u >> v >> w;
    edge.push_back(Edge(w, u, v));
  }
  cout << minimunSpanningTree(edge, n) << '\n';
  return 0;
}

/*
Time Complexity: O(ElogE)
E = number of edges
*/