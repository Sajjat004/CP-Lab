#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solution() {
  ll n, x; cin >> n >> x;
  vector<ll> a(n);
  for (ll i = 0; i < n; ++i) {
    cin >> a[i];
  }

  auto getSubSetSums = [&](int l, int r) -> vector<ll> {
    vector<ll> sums;
    int size = r - l + 1;
    for (int mask = 0; mask < (1 << size); ++mask) {
      ll sum = 0;
      for (int i = 0; i < size; ++i) {
        if (mask & (1 << i)) {
          sum += a[l + i];
        }
      }
      sums.push_back(sum);
    }

    return sums;
  };

  vector<ll> leftSums = getSubSetSums(0, n / 2 - 1);
  vector<ll> rightSums = getSubSetSums(n / 2, n - 1);

  sort(leftSums.begin(), leftSums.end());
  sort(rightSums.begin(), rightSums.end());

  ll ans = 0;
  for (ll leftSum : leftSums) {
    if (leftSum > x) continue;
    
    ll target = x - leftSum;
    auto lower = lower_bound(rightSums.begin(), rightSums.end(), target);
    auto upper = upper_bound(rightSums.begin(), rightSums.end(), target);
    ans += upper - lower;
  }

  cout << ans << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  solution();

  return 0;
}

// Problem Link: https://cses.fi/problemset/task/1628/
