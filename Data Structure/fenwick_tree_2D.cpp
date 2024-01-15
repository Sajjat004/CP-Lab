#include <bits/stdc++.h>
using namespace std;

class FenwickTree {
  vector<vector<long long>> tree;
  int n;
public:
  FenwickTree(int n) {
    this->n = n;
    tree.resize(12, vector<long long>(n + 2, 0));
  }
  // Time Complexity: O(logN)
  void update(int len, int idx, long long val) {
    while (idx <= n) {
      tree[len][idx] += val;
      idx += (idx & -idx);
    }
  }
  // Time Complexity: O(logN)
  long long query(int len, int idx) {
    long long sum = 0;
    while (idx > 0) {
      sum += tree[len][idx];
      idx -= (idx & -idx);
    }
    return sum;
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int test = 1, tc = 0;
  while (test--) {
    int n, K;
    cin >> n >> K;
    vector<long long> nums(n, 0);
    FenwickTree ds(n + 2);
    for (auto& x : nums) cin >> x;
    for (auto x : nums) {
      for (int k = 1; k <= (K + 1); ++k) {
        long long value = ds.query(k - 1, x - 1);
        if (k == 1) value = 1;
        ds.update(k, x, value);
      }
    }
    cout << ds.query(K + 1, n) << '\n';
  }
  return 0;
}
/*
problem link: https://vjudge.net/contest/491215#problem/E
Solution Tag: 2D bit + dp
*/
