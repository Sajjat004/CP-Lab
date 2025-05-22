#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
vector<vector<int>> adjList(N);
vector<int> startIndex(N);
vector<int> endIndex(N);
int timer = 0;

void eulerTour(int node, int parent) {
  startIndex[node] = ++timer;
  for (int child : adjList[node]) {
    if (child != parent) {
      eulerTour(child, node);
    }
  }
  endIndex[node] = timer;
}

template <typename type> class FenwickTree {
private:
  vector<type> tree;
  int n;
public:
  FenwickTree(int n) {
    this->n = n;
    tree.assign(n + 2, 0);
  }

  void update(int idx, type val) {
    for ( ; idx <= n; idx += (idx & -idx)) tree[idx] += val;
  }

  type query(int idx) {
    type sum = 0;
    for ( ; idx > 0; idx -= (idx & -idx)) sum += tree[idx];
    return sum;
  }

  type query(int l, int r) {
    return query(r) - query(l - 1);
  }
};

int32_t main() {
  ios_base::sync_with_stdio(false); cin.tie(0);

  int n, q; cin >> n >> q;
  vector<int> value(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> value[i];
  }

  for (int i = 1; i < n; i++) {
    int u, v; cin >> u >> v;
    adjList[u].push_back(v);
    adjList[v].push_back(u);
  }

  eulerTour(1, -1);

  FenwickTree<long long> fenwickTree(timer + 1);
  for (int i = 1; i <= n; ++i) {
    fenwickTree.update(startIndex[i], value[i]);
  }

  while (q--) {
    int opType; cin >> opType;
    if (opType == 1) {
      int node, val; cin >> node >> val;
      fenwickTree.update(startIndex[node], -value[node]);
      fenwickTree.update(startIndex[node], val);
      value[node] = val;
    } else {
      int node; cin >> node;
      long long result = fenwickTree.query(startIndex[node], endIndex[node]);
      cout << result << '\n';
    }
  }
    
  return 0;
}

// Problem Link: https://cses.fi/problemset/task/1137/
