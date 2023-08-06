#include <bits/stdc++.h>
using namespace std;

int main() {
  // freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(false); cin.tie(0);
  int n; cin >> n;
  vector<int> weight(n + 2, 0);
  for (int i = 1; i <= n; ++i) cin >> weight[i];
  int sum; cin >> sum;
  vector<vector<bool>> dp(n + 2, vector<bool>(sum + 2, 0));
  dp[0][0] = 1;
  for (int k = 1; k <= n; ++k) {
    for (int x = 1; x <= sum; ++x) {
      if (x >= weight[k]) dp[k][x] = dp[k - 1][x - weight[k]];
      dp[k][x] = dp[k][x] | dp[k - 1][x];
    }
  }
  if (dp[n][sum]) cout << "YES" << '\n';
  else cout << "NO" << '\n';
  return 0;
}