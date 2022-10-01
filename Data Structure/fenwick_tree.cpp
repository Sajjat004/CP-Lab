#include <bits/stdc++.h>
using namespace std;

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
    while (idx <= n) {
      tree[idx] += val;
      idx += (idx & -idx);
    }
  }
  type query(int idx) {
    type sum = 0;
    while (idx > 0) {
      sum += tree[idx];
      idx -= (idx & -idx);
    }
    return sum;
  }
  type query(int l, int r) {
    return query(r) - query(l - 1);
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int test = 1, tc = 0;
  while (test--) {
    int n;
    cin >> n;
    int ar[n + 2];
    for (int i = 1; i <= n; ++i) cin >> ar[i];
    FenwickTree<int> ds(n);
    for (int i = 1; i <= n; ++i) {
      ds.update(i, ar[i]);
    }
    int m;
    cin >> m;
    while (m--) {
      int l, r;
      cin >> l >> r;
      cout << ds.query(l, r) << '\n';
    }
  }
  return 0;
}
