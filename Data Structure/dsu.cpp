#include <bits/stdc++.h>
using namespace std;

class Dsu {
  struct Data {
    int par, rank, setSize;
    Data() {
      par = rank = setSize = 0;
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
      graph[i].setSize = 1;
    }
  }
  void merge(int a, int b) {
    int x = root(a);
    int y = root(b);
    if (x == y) return;
    if (graph[x].rank <= graph[y].rank) swap(x, y);
    graph[y].par = x;
    graph[x].setSize += graph[y].setSize;
    if (graph[x].rank == graph[y].rank) graph[x].rank++;
  }

  int getSetSize(int x) {
    return graph[root(x)].setSize;
  }
};

int main() {
  // freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(false); cin.tie(0);
  int n, m; cin >> n >> m;
  Dsu dsu(n);
  for (int i = 0; i < m; ++i) {
    int u, v; cin >> u >> v;
    dsu.merge(u, v);
  }
  int x; cin >> x;
  cout << dsu.getSetSize(x) << '\n';
  return 0;
}

/*
Time complexity: O(m alpha(n)) where alpha(n) <= 4.
              => O(m)
*/