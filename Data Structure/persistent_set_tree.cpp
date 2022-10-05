#include <bits/stdc++.h>
using namespace std;

const int N = (int) 2e5 + 5;

// problem link : https://vjudge.net/contest/460861#problem/A

class PersistentSegTree {
private:
  struct Type {
    int sum, left, right;
    Type() : sum(0), left(0), right(0) {}
  };
  int cnt = 0;
  vector<Type> tree;
public:
  PersistentSegTree() {
    tree.resize(20 * N);
    cnt = 0;
  }

  int build(int b, int e) {
    int cur = ++cnt;
    if (b == e) return cur;
    int mid = (b + e) >> 1;
    tree[cur].left = build(b, mid);
    tree[cur].right = build(mid + 1, e);
    tree[cur].sum = tree[tree[cur].left].sum + tree[tree[cur].right].sum;
    return cur;
  }

  int update(int pre, int b, int e, int idx, int val) {
    if (idx < b or idx > e) return pre;
    int cur = ++cnt;
    tree[cur] = tree[pre];
    if (b == e) {
      tree[cur].sum += val;
      return cur;
    }
    int mid = (b + e) >> 1;
    tree[cur].left = update(tree[pre].left, b, mid, idx, val);
    tree[cur].right = update(tree[pre].right, mid + 1, e, idx, val);
    tree[cur].sum = tree[tree[cur].left].sum + tree[tree[cur].right].sum;
    return cur;
  }

  int query(int cur, int pre, int b, int e, int k) {
    if (b == e) return b;
    int temp = tree[tree[cur].left].sum - tree[tree[pre].left].sum;
    int mid = (b + e) >> 1;
    if (temp >= k) return query(tree[cur].left, tree[pre].left, b, mid, k);
    else return query(tree[cur].right, tree[pre].right, mid + 1, e, k - temp);
  }
};

map<int, int> ID, original;
int getID(int x) { return ID[x]; }
int getOriginal(int x) { return original[x]; }

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int test = 1, tc = 0;
  while (test--) {
    int n, q; cin >> n >> q;
    vector<int> v(n, 0);
    set<int> s;
    for (auto& x : v) {
      cin >> x;
      s.insert(x);
    }
    int p = 0;
    for (auto x : s) {
      ID[x] = ++p;
      original[p] = x;
    }
    PersistentSegTree ds;
    int root[n + 2];
    root[0] = ds.build(1, n);
    for (int i = 0; i < n; ++i) {
      root[i + 1] = ds.update(root[i], 1, n, getID(v[i]), 1);
    }
    while (q--) {
      int l, r, k; cin >> l >> r >> k;
      cout << getOriginal(ds.query(root[r], root[l - 1], 1, n, k)) << '\n';
    }
  }
  return 0;
}
