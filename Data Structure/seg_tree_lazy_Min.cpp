#include <bits/stdc++.h>
using namespace std;

const int N = (int) 2e5 + 5;

int ar[N];

template<typename type> class SegTreeLazyMin {
private:
  struct Type {
    type mn, lazy;
    Type() : mn(0), lazy(0) {}
  };
  vector<Type> tree;
  int n;
  void build(int at, int b, int e) {
    if (b == e) {
      tree[at].mn = ar[b];
      return;
    }
    int mid = (b + e) >> 1;
    build(2 * at, b, mid);
    build(2 * at + 1, mid + 1, e);
    tree[at].mn = min(tree[2 * at].mn, tree[2 * at + 1].mn);
  }
  void propagate(int at, int b, int e) {
    tree[at].mn += tree[at].lazy;
    if (b != e) {
      tree[2 * at].lazy += tree[at].lazy;
      tree[2 * at + 1].lazy += tree[at].lazy;
    }
    tree[at].lazy = 0;
  }
  void update(int at, int b, int e, int l, int r, type val) {
    if (tree[at].lazy) propagate(at, b, e);
    if (r < b or e < l) return;
    if (l <= b and e <= r) {
      tree[at].mn += val;
      if (b != e) {
        tree[2 * at].lazy += val;
        tree[2 * at + 1].lazy += val;
      }
      return;
    }
    int mid = (b + e) >> 1;
    update(2 * at, b, mid, l, r, val);
    update(2 * at + 1, mid + 1, e, l, r, val);
    tree[at].mn = min(tree[2 * at].mn, tree[2 * at + 1].mn);
  }
  type query(int at, int b, int e, int l, int r) {
    if (tree[at].lazy) propagate(at, b, e);
    if (r < b or e < l) return INT_MAX;
    if (l <= b and e <= r) return tree[at].mn;
    int mid = (b + e) >> 1;
    type x = query(2 * at, b, mid, l, r);
    type y = query(2 * at + 1, mid + 1, e, l, r);
    return min(x, y);
  }
public:
  SegTreeLazyMin(int n) {
    this->n = n;
    tree.resize(4 * n);
    build(1, 1, n);
  }
  void update(int l, int r, type val) {
    update(1, 1, n, l, r, val);
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
    for (int i = 1; i <= n; ++i) cin >> ar[i];
    SegTreeLazyMin<int> ds(n);
    int m; cin >> m;
    while (m--) {
      int op; cin >> op;
      if (op == 1) {
        int l, r, val; cin >> l >> r >> val;
        ds.update(l, r, val);
      } else {
        int l, r;
        cin >> l >> r; cout << ds.query(l, r) << '\n';
      }
    }
  }
  return 0;
}
