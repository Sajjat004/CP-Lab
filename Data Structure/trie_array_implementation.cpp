#include <bits/stdc++.h>
using namespace std;

class Trie {
  const int N = (int) 2e3 + 5;
  vector<vector<int>> node;
  vector<int> cntPath;
  int state = 0;
public:
  Trie() {
    node.resize(N, vector<int>(26, -1));
    cntPath.resize(N, 0);
    state = 0;
  }
  void add(string& s) {
    int cur = 0;
    for (int i = 0; i < (int) s.size(); ++i) {
      int id = s[i] - 'a';
      if (node[cur][id] == -1) node[cur][id] = ++state;
      cur = node[cur][id];
    }
    cntPath[cur]++;
  }
  int search(string& s) {
    int cur = 0;
    for (int i = 0; i < (int) s.size(); ++i) {
      int id = s[i] - 'a';
      if (node[cur][id] == -1) return 0;
      cur = node[cur][id];
    }
    return cntPath[cur];
  }
};

int main() {
  // freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(false); cin.tie(0);
  int n; cin >> n;
  Trie trie;
  for (int i = 1; i <= n; ++i) {
    string s; cin >> s;
    trie.add(s);
  }
  string t; cin >> t;
  cout << trie.search(t) << '\n';

  return 0;
}

/*
Time complexity: O(N * avgL)
N = number of strings
avgL = average length of 'N' strings
*/