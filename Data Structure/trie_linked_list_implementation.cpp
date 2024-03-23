#include <bits/stdc++.h>
using namespace std;

class Trie {
  struct Node {
    Node* next[26];
    int pathEnd = 0;
    Node() {
      pathEnd = 0;
      for (int i = 0; i < 26; ++i)
        next[i] = NULL;
    }
  };
  Node* root;
public:
  Trie() {
    root = new Node();
  }
  void add(string& s) {
    Node* cur = root;
    for (char x : s) {
      int id = x - 'a';
      if (cur->next[id] == NULL) {
        cur->next[id] = new Node();
      }
      cur = cur->next[id];
    }
    cur->pathEnd++;
  }
  int search(string& s) {
    Node* cur = root;
    for (char x : s) {
      int id = x - 'a';
      if (cur->next[id] == NULL) return 0;
      cur = cur->next[id];
    }
    return cur->pathEnd;
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