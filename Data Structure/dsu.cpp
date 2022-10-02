#include <bits/stdc++.h>
using namespace std;

class Dsu {
  struct type {
    int par, rank, setSize;
    type() : par(0), rank(0), setSize(0) {}
  };
  vector<type> tree;
  int n;

  int root(int x) {
    return tree[x].par = tree[x].par == x ? x : root(tree[x].par);
  }

public:
  Dsu(int n) {
    this->n = n;
    tree.resize(n + 2);
    for (int i = 0; i <= n; ++i) {
      tree[i].par = i;
      tree[i].rank = 0;
      tree[i].setSize = 1;
    }
  }

  void merge(int a, int b) {
    int x = root(a), y = root(b);
    if (x == y) return;
    if (tree[x].rank <= tree[y].rank) swap(x, y);
    tree[y].par = x;
    tree[x].setSize += tree[y].setSize;
    if (tree[x].rank == tree[y].rank) tree[x].rank++;
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int test = 1, tc = 0;
  while (test--) {
    int n; cin >> n;
    Dsu ds(n);
    int m; cin >> m;
    while (m--) {
      int u, v;
      cin >> u >> v;
      ds.merge(u, v);
    }
  }
  return 0;
}
