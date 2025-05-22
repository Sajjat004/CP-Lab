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

  FenwickTree(vector<type>& a) {
    n = a.size();
    tree.assign(n + 2, 0);
    for (int i = 1; i <= n; ++i) {
      update(i, a[i]);
    }
  }

  void update(int idx, type val) {
    for ( ; idx <= n; idx += (idx & -idx)) tree[idx] += val;
  }

  type query(int idx) {
    type sum = 0;
    for ( ; idx > 0; idx -= (idx & -idx)) sum += tree[idx];
    return sum;
  }

  // Range update only works for single point query
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

  int n; cin >> n;
  vector<int> a(n + 1);
  for (int i = 1; i <= n; ++i) cin >> a[i];

  FenwickTree<int> ds(a);
  
  int m; cin >> m;
  while (m--) {
    int left, right; cin >> left >> right;
    cout << ds.query(left, right) << '\n';
  }

  return 0;
}
