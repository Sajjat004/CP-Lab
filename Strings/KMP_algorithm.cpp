#include <bits/stdc++.h>
using namespace std;

vector<int> prefixFunction(string s) {
  int n = (int) s.length();
  vector<int> LPS(n);

  for (int i = 1; i < n; i++) {
    int j = LPS[i - 1];

    while (j > 0 && s[i] != s[j]) {
      j = LPS[j - 1];
    }

    if (s[i] == s[j]) j++;
    LPS[i] = j;
  }

  return LPS;
}

int main() {
  // freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(false); cin.tie(0);

  string s; cin >> s;
  string pattern; cin >> pattern;

  vector<int> LPS = prefixFunction(pattern + "#" + s);

  int answer = 0;
  for (int len : LPS) {
    if (len == pattern.size()) answer++;
  }

  cout << answer << '\n';

  return 0;
}

// Problem Link: https://cses.fi/problemset/task/1753/