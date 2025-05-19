#include <bits/stdc++.h>
using namespace std;

class MergeSortTree {
  vector<vector<int>> tree;
  int n;

  void merge(vector<int>& res, vector<int>& left, vector<int>& right) {
    int n1 = left.size();
    int n2 = right.size();

    int i = 0, j = 0;
    while (i < n1 and j < n2) {
      if (left[i] <= right[j]) res.push_back(left[i++]);
      else res.push_back(right[j++]);
    }
    while (i < n1) res.push_back(left[i++]);
    while (j < n2) res.push_back(right[j++]);
  }

  void build(int at, int begin, int end, vector<int>& v) {
    if (begin == end) {
      tree[at].push_back(v[begin]);
      return;
    }

    int mid = (begin + end) / 2;
    build(2 * at, begin, mid, v);
    build(2 * at + 1, mid + 1, end, v);
    merge(tree[at], tree[2 * at], tree[2 * at + 1]);
  }

  int query(int at, int begin, int end, int left, int right, int k) {
    if (begin > right or end < left) return 0;
    if (begin >= left and end <= right) {
      return tree[at].end() - upper_bound(tree[at].begin(), tree[at].end(), k);
    }

    int mid = (begin + end) / 2;
    int leftAns = query(2 * at, begin, mid, left, right, k);
    int rightAns = query(2 * at + 1, mid + 1, end, left, right, k);

    return leftAns + rightAns;
  }

public:
  MergeSortTree(vector<int>& v) {
    n = v.size();
    tree.resize(4 * n, vector<int>());
    build(1, 0, n - 1, v);
  }

  int query(int left, int right, int k) {
    return query(1, 0, n - 1, left, right, k);
  }
};

int32_t main() {
  ios_base::sync_with_stdio(false); cin.tie(0);

  int n; cin >> n;
  vector<int> v(n);
  for (int i = 0; i < n; i++) cin >> v[i];

  MergeSortTree mst(v);
  int q; cin >> q;
  while (q--) {
    int l, r, k; cin >> l >> r >> k;
    l--; r--;
    cout << mst.query(l, r, k) << '\n';
  }
    
  return 0;
}

// Time Complexity: O(n log n + q log n), where n is the size of the array and q is the number of queries
// Space Complexity: O(n log n), where n is the size of the array

// Pboblem Link: https://www.spoj.com/problems/KQUERY/
