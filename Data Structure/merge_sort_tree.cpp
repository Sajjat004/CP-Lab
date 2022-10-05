#include <bits/stdc++.h>
using namespace std;

const int N = (int) 2e5 + 5;

int ar[N];

class MergeSortTree {
private:
  vector<vector<int>> tree;
  int n;

  void merge(vector<int>& a, vector<int>& b, vector<int>& c) {
    int l = (int) b.size(), r = (int) c.size();
    int i = 0, j = 0;
    while (i < l or j < r) {
      if (i < l and j < r) {
        if (b[i] <= c[j]) {
          a.push_back(b[i]);
          i++;
        } else {
          a.push_back(c[j]);
          j++;
        }
      } else if (i < l) {
        a.push_back(b[i]);
        i++;
      } else {
        a.push_back(c[j]);
        j++;
      }
    }
  }

  void build(int at, int b, int e) {
    if (b == e) {
      tree[at].push_back(ar[b]);
      return;
    }
    int mid = (b + e) >> 1;
    build(2 * at, b, mid);
    build(2 * at + 1, mid + 1, e);
    merge(tree[at], tree[2 * at], tree[2 * at + 1]);
  }

  int query(int at, int b, int e, int l, int r, int k) {
    if (r <= b or e <= l) return 0;
    if (l <= b and e <= r) {
      int cnt = lower_bound(tree[at].begin(), tree[at].end(), k) - tree[at].begin();
      return cnt;
    }
    int mid = (b + e) >> 1;
    int x = query(2 * at, b, mid, l, r, k);
    int y = query(2 * at + 1, mid + 1, e, l, r, k);
    return x + y;
  }

public:
  MergeSortTree(int n) {
    this->n = n;
    tree.resize(4 * n, vector<int>());
    build(1, 1, n);
  }

  int query(int l, int r, int k) {
    return query(1, 1, n, l, r, k);
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int test = 1, tc = 0;
  while (test--) {
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> ar[i];
    MergeSortTree ds(n);
    int m; cin >> m;
    while (m--) {
      int l, r, k;
      cin >> l >> r >> k;
      cout << ds.query(l, r, k) << '\n';
    }
  }
  return 0;
}
