#include <bits/stdc++.h>
using namespace std;

const int N = (int) 2e5 + 5;

int arr[N];

template<typename type> class SegTreeMax {
  vector<type> tree;
  int n;

  void build(int at, int b, int e) {
    if (b == e) {
      tree[at] = arr[b];
      return;
    }
    int mid = (b + e) >> 1;
    build(2 * at, b, mid);
    build(2 * at + 1, mid + 1, e);
    tree[at] = max(tree[2 * at], tree[2 * at + 1]);
  }

  void update(int at, int b, int e, int idx, type val) {
    if (e < idx or idx < b) return;
    if (b == e) {
      tree[at] += val;
      return;
    }
    int mid = (b + e) >> 1;
    update(2 * at, b, mid, idx, val);
    update(2 * at + 1, mid + 1, e, idx, val);
    tree[at] = max(tree[2 * at], tree[2 * at + 1]);
  }

  type query(int at, int b, int e, int l, int r) {
    if (r < b or e < l) return (type) INT_MIN;
    if (l <= b and e <= r) return tree[at];
    int mid = (b + e) >> 1;
    type x = query(2 * at, b, mid, l, r);
    type y = query(2 * at + 1, mid + 1, e, l, r);
    return max(x, y);
  }

public:
  SegTreeMax(int n) {
    this->n = n;
    tree.assign(4 * n, 0);
    build(1, 1, n);
  }

  void update(int idx, type val) {
    update(1, 1, n, idx, val);
  }

  type query(int l, int r) {
    return query(1, 1, n, l, r);
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int test = 1, tc = 0;
  while (test--) {
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> arr[i];
    SegTreeMax<int> ds(n);
    int m; cin >> m;
    while (m--) {
      int op; cin >> op;
      if (op == 1) {
        int idx, val; cin >> idx >> val;
        ds.update(idx, val);
      } else {
        int l, r; cin >> l >> r;
        cout << ds.query(l, r) << '\n';
      }
    }
  }
  return 0;
}
