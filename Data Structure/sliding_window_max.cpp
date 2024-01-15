#include <bits/stdc++.h>
using namespace std;

vector<int> maxSlidingWindow(vector<int>& nums, int k) {
  int n = nums.size();
  vector<int> ans;
  deque<pair<int, int>> dq;
  for (int i = 0; i < n; ++i) {
    while (!dq.empty() and dq.back().first <= nums[i]) {
      dq.pop_back();
    }
    dq.push_back({nums[i], i});
    while (dq.front().second <= i - k) {
      dq.pop_front();
    }
    if (i >= (k - 1)) ans.push_back(dq.front().first);
  }
  return ans;
}

int main() {
  // freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(false); cin.tie(0);
  int n, k; cin >> n >> k;
  vector<int> a(n);
  for (int& x : a) cin >> x;
  vector<int> ans = maxSlidingWindow(a, k);
  for (int i = 0; i < ans.size(); ++i) cout << ans[i] << " ";
  cout << '\n';
  return 0;
}

/*
Problem Link: https://leetcode.com/problems/sliding-window-maximum/description/
Time Complexity: O(N)
*/