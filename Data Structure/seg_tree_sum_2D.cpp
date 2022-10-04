#include <bits/stdc++.h>
using namespace std;

// problem link: https://vjudge.net/contest/491215#problem/E
// 2D segment tree + DP

template<typename type> class SegTree {
private:
  vector<vector<type>> tree;
  int n;

  void build(int at, int b, int e, int len) {
    if (b == e) {
      tree[len][at] = 0LL;
      return;
    }
    int mid = (b + e) >> 1;
    build(2 * at, b, mid, len);
    build(2 * at + 1, mid + 1, e, len);
    tree[len][at] = tree[len][2 * at] + tree[len][2 * at + 1];
  }
  void update(int at, int b, int e, int idx, type val, int len) {
    if (idx < b or idx > e) return;
    if (b == e) {
      tree[len][at] += val;
      return;
    }
    int mid = (b + e) >> 1;
    update(2 * at, b, mid, idx, val, len);
    update(2 * at + 1, mid + 1, e, idx, val, len);
    tree[len][at] = tree[len][2 * at] + tree[len][2 * at + 1];
  }
  type query(int at, int b, int e, int l, int r, int len) {
    if (r < b or e < l) return 0;
    if (l <= b and e <= r) return tree[len][at];
    int mid = (b + e) >> 1;
    type x = query(2 * at, b, mid, l, r, len);
    type y = query(2 * at + 1, mid + 1, e, l, r, len);
    return x + y;
  }

public:
  SegTree(int n) {
    this->n = n;
    tree.resize(14, vector<type>(4 * n, 0));
    for (int i = 0; i <= 12; ++i) build(1, 1, n, i);
    
  }
  void update(int idx, type val, int len) {
    update(1, 1, n, idx, val, len);
  }
  type query(int l, int r, int len) {
    return query(1, 1, n, l, r, len);
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int test = 1, tc = 0;
  while (test--) {
    int n, K;
    cin >> n >> K;
    vector<long long> nums(n);
    SegTree<long long> ds(n);
    for (auto& x : nums) cin >> x;
    for (auto x : nums) {
      for (int k = 1; k <= (K + 1); ++k) {
        long long value = ds.query(1, x - 1, k - 1);
        if (k == 1) value = 1;
        ds.update(x, value, k);
      }
    }
    cout << ds.query(1, n, K + 1) << '\n';
  }
  return 0;
}
