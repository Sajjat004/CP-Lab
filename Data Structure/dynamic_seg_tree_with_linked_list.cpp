#include <bits/stdc++.h>
using namespace std;

// problem link: https://toph.co/p/just-another-range-query

struct node {
  long long sum, lazy;
  node* left;
  node* right;
  node() : sum(0LL), lazy(0LL), left(NULL), right(NULL) {}
};

void propagate(node* cur, int b, int e) {
  cur->sum += 1LL * (e - b + 1) * cur->lazy;
  if (b != e) {
    if (cur->left == NULL) cur->left = new node();
    if (cur->right == NULL) cur->right = new node();
    cur->left->lazy += cur->lazy;
    cur->right->lazy += cur->lazy;
  }
  cur->lazy = 0;
}

void update(node* cur, int b, int e, int l, int r, int val) {
  if (cur->lazy) propagate(cur, b, e);
  if (r < b or e < l) return;
  if (l <= b and e <= r) {
    cur->sum += 1LL * (e - b + 1) * val;
    if (b != e) {
      if (cur->left == NULL) cur->left = new node();
      if (cur->right == NULL) cur->right = new node();
      cur->left->lazy += val;
      cur->right->lazy += val;
    }
    return;
  }
  int mid = (b + e) >> 1;
  if (cur->left == NULL) cur->left = new node();
  if (cur->right == NULL) cur->right = new node();
  update(cur->left, b, mid, l, r, val);
  update(cur->right, mid + 1, e, l, r, val);
  cur->sum = cur->left->sum + cur->right->sum;
}

long long query(node* cur, int b, int e, int l, int r) {
  if (cur->lazy != 0LL) propagate(cur, b, e);
  if (!cur->sum or r < b or e < l) return 0;
  if (l <= b and e <= r) {
    return cur->sum;
  }
  int mid = (b + e) >> 1;
  long long x = query(cur->left, b, mid, l, r);
  long long y = query(cur->right, mid + 1, e, l, r);
  return x + y;
}

long long get(int l, int r) {
  int h = r - l + 1;
  return 1LL * (l + r) * h / 2LL;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int test = 1, tc = 0;
  while (test--) {
    int n, m; cin >> n >> m;
    node* root = new node();
    while (m--) {
      int op; cin >> op;
      if (op == 1) {
        int l, r, val; cin >> l >> r >> val;
        update(root, 1, n, l, r, val);
      } else {
        int l, r; cin >> l >> r;
        cout << get(l, r) - query(root, 1, n, l, r) << '\n';
      }
    }
  }
  return 0;
}
