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
  // Time Complexity: O(logN)
  void update(int idx, type val) {
    for ( ; idx <= n; idx += (idx & -idx)) tree[idx] += val;
  }
  // Time Complexity: O(logN)
  type query(int idx) {
    type sum = 0;
    for ( ; idx > 0; idx -= (idx & -idx)) sum += tree[idx];
    return sum;
  }
  void update(int l, int r, int val) {
    update(l, val);
    update(r + 1, -val);
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
