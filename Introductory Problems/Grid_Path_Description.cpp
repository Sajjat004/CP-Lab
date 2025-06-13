#include <bits/stdc++.h>
using namespace std;

unordered_map<char, pair<int, int>> dir = {
  {'U', {-1, 0}},
  {'D', {1, 0}},
  {'L', {0, -1}},
  {'R', {0, 1}},
};

int findWays(int x, int y, int index, string &s, vector<vector<int>> &visited) {
  if (index == (int) s.size()) return (x == 7 and y == 1) ? 1 : 0;
  if (x == 7 and y == 1) return 0;
  if (visited[x][y + 1] and visited[x][y - 1] and !visited[x + 1][y] and !visited[x - 1][y]) return 0;
  if (visited[x + 1][y] and visited[x - 1][y] and !visited[x][y + 1] and !visited[x][y - 1]) return 0;

  visited[x][y] = 1;
  int ans = 0;

  if (s[index] == '?') {
    for (auto& [d, p] : dir) {
      auto [dx, dy] = p;
      if (!visited[x + dx][y + dy]) ans += findWays(x + dx, y + dy, index + 1, s, visited);
    }
  } else {
    auto [dx, dy] = dir[s[index]];
    if (!visited[x + dx][y + dy]) ans += findWays(x + dx, y + dy, index + 1, s, visited);
  }

  visited[x][y] = 0;
  return ans;
}

void solution() {
  string s; cin >> s;
  vector<vector<int>> visited(9, vector<int>(8, 0));
  for (int i = 0; i <= 8; ++i) {
    visited[0][i] = 1;
    visited[8][i] = 1;
    visited[i][0] = 1;
    visited[i][8] = 1;
  }

  cout << findWays(1, 1, 0, s, visited) << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  solution();

  return 0;
}

// Problem Link: Grid Path Description
