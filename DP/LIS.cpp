#include <bits/stdc++.h>
using namespace std;

int lengthOfLIS(vector<int>& nums) {
  int n = nums.size();
  vector<int> dp(n, 1);
  for (int i = 1; i < n; ++i) {
    int mx = dp[i];
    for (int j = 0; j < i; ++j) {
      if (nums[j] < nums[i]) {
        mx = max(mx, dp[i] + dp[j]);
      }
    }
    dp[i] = mx;
  }
  int ans = 0;
  for (int i = 0; i < n; ++i) ans = max(ans, dp[i]);
  return ans;
}

int main() {
  // freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(false); cin.tie(0);
  int n; cin >> n;
  vector<int> a(n);
  for (int& x : a) cin >> x;
  cout << lengthOfLIS(a) << '\n';
  return 0;
}

// Time Complexity: O(N^2)