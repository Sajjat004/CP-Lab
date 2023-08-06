#include <bits/stdc++.h>
using namespace std;

const int N = 5005;

int main() {
  // freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(false); cin.tie(0);
  int n; cin >> n;
  vector<int> weight(n + 2, 0);
  for (int i = 1; i <= n; ++i) cin >> weight[i];
  int sum; cin >> sum;
  bitset<N> dp;
  dp[0] = 1;
  for (int i = 1; i <= n; ++i) dp |= (dp << weight[i]);
  if (dp[sum]) cout << "YES" << '\n';
  else cout << "NO" << '\n';
  return 0;
}