#include <bits/stdc++.h>
using namespace std;

const int N = (int) 2e5 + 5;

// problem link: https://toph.co/p/just-another-range-query

long long sum[35 * N], lazy[35 * N];
int L[35 * N], R[35 * N];

int cnt = 1;
int node(int& u) {
  if (!u) u = ++cnt;
  return u;
}

void propagate(int at, int b, int e) {
  sum[at] += 1LL * (e - b + 1) * lazy[at];
  if (b != e) {
    lazy[node(L[at])] += lazy[at];
    lazy[node(R[at])] += lazy[at];
  }
  lazy[at] = 0LL;
  return;
}

void update(int at, int b, int e, int l, int r, int val) {
  if (lazy[at]) propagate(at, b, e);
  if (r < b or e < l) return;
  if (l <= b and e <= r) {
    sum[at] += 1LL * (e - b + 1) * val;
    if (b != e) {
      lazy[node(L[at])] += val;
      lazy[node(R[at])] += val;
    }
    return;
  }
  int mid = (b + e) >> 1;
  update(node(L[at]), b, mid, l, r, val);
  update(node(R[at]), mid + 1, e, l, r, val);
  sum[at] = sum[L[at]] + sum[R[at]];
}

long long  query(int at, int b, int e, int l, int r) {
  if (lazy[at]) propagate(at, b, e);
  if (r < b or e < l) return 0;
  if (l <= b and e <= r) return sum[at];
  int mid = (b + e) >> 1;
  long long  x = query(node(L[at]), b, mid, l, r);
  long long  y = query(node(R[at]), mid + 1, e, l, r);
  return x + y;
}

long long  get(int l, int r) {
  long long  up = 1LL * r * (r + 1) / 2LL;
  long long  dn = 1ll * l * (l - 1) / 2LL;
  return up - dn;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int test = 1, tc = 0;
  while (test--) {
    int n, m; cin >> n >> m;
    while (m--) {
      int op; cin >> op;
      if (op == 1) {
        int l, r, val;
        cin >> l >> r >> val;
        update(1, 1, n, l, r, val);
      } else {
        int l, r; cin >> l >> r;
        cout << get(l, r) - query(1, 1, n, l, r) << '\n';
      }
    }
  }
  return 0;
}
