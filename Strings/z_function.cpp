#include <bits/stdc++.h>
using namespace std;

// An element Z[i] of Z array stores length of the longest substring
// starting from str[i] which is also a prefix of str[0..n-1].
// The first entry of Z array is meaning less as complete string is always prefix of itself.
// Here Z[0]=0.
vector<int> zFunction(const string& s) {
  int n = (int) s.size();
  vector<int> z(n);

  for (int index = 1, left = 0, right = 0; index < n; ++index) {
    if (index <= right) {
      z[index] = min (right - index + 1, z[index - left]);
    }
    while (index + z[index] < n && s[z[index]] == s[index + z[index]]) {
      ++z[index];
    }
    if (index + z[index] - 1 > right) {
      left = index, right = index + z[index] - 1;
    }
  }

  return z;
}

int32_t main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  
  string s, t; cin >> s >> t;
  s = t + "$" + s;
  vector<int> z = zFunction(s);
  
  int n = (int) t.size();
  int ans = 0;
  for (int i = 1; i < s.size(); ++i) {
    if (z[i] == n) {
      ans++;
    }
  }
  cout << ans << '\n';

  return 0;
}

// Problem Link: https://cses.fi/problemset/task/1753/
