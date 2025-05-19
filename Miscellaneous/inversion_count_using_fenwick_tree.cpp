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

  void update(int idx, type val) {
    for ( ; idx <= n; idx += (idx & -idx)) tree[idx] += val;
  }

  type query(int idx) {
    type sum = 0;
    for ( ; idx > 0; idx -= (idx & -idx)) sum += tree[idx];

    return sum;
  }

  void update(int l, int r, int val) {
    update(l, val);
    update(r + 1, -val);
  }

  type query(int l, int r) {
    return query(r) - query(l - 1);
  }
};

void compressNums(vector<int>& nums) {
  vector<int> sorted = nums;
  sort(sorted.begin(), sorted.end());
  sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());

  for (int i = 0; i < nums.size(); i++) {
    nums[i] = lower_bound(sorted.begin(), sorted.end(), nums[i]) - sorted.begin() + 1;
  }
}

long long inversionCount(vector<int>& nums) {
  int n = nums.size();
  compressNums(nums);

  FenwickTree<int> fenwick(n);
  long long invCount = 0;
  for (int i = n - 1; i >= 0; i--) {
    invCount += fenwick.query(nums[i] - 1);
    fenwick.update(nums[i], 1);
  }

  return invCount;
}

long long solve() {
  int n; cin >> n;
  vector<int> nums(n);
  for (int i = 0; i < n; i++) cin >> nums[i];

  return inversionCount(nums);
}

int32_t main() {
  ios_base::sync_with_stdio(false); cin.tie(0);

  int tests; cin >> tests;
  while (tests--) {
    cout << solve() << '\n';
  }
    
  return 0;
}

// Inversion Count using Fenwick Tree
// Time Complexity: O(nlogn), Space Complexity: O(n)

// Problem Link: https://www.spoj.com/problems/INVCNT/en/
