#include <bits/stdc++.h>
using namespace std;

const int N = 3003;

int n, capacity;
vector<int> weight(N, 0), val(N, 0);
vector<vector<int>> dp(N, vector<int>(N, -1));

int func(int pos, int cap) {
  if (cap < 0) return (-1 * val[pos - 1]);
  if (pos > n or cap == 0) return 0;
  if (dp[pos][cap] != -1) return dp[pos][cap];
  return dp[pos][cap] = max((func(pos + 1, cap - weight[pos]) + val[pos]), func(pos + 1, cap));
}

int main() {
  // freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(false); cin.tie(0);
  cin >> n >> capacity;
  for (int i = 1; i <= n; ++i) {
    cin >> weight[i] >> val[i];
  }
  cout << func(1, capacity) << '\n';
  return 0;
}