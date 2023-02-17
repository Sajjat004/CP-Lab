#include <bits/stdc++.h>
using namespace std;

using ll  = long long;
using vll = vector<ll>;
using vi  = vector<int>;
using pll = pair<ll, ll>;
using pii = pair<int, int>;

const int N   = (int) 2e5 + 5;
const int MOD = (int) 1e9 + 7;
const int INF = (int) 1e9 + 9;

#define nl      '\n'
#define ff      first
#define ss      second
#define szof(x) (int) x.size()
#define all(x)  x.begin(), x.end()

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
    for (int i = 0; i < (int) s.size(); ++i) {
      int id = s[i] - 'a';
      if (cur->next[id] == NULL) {
        cur->next[id] = new Node();
      }
      cur = cur->next[id];
    }
    cur->pathEnd++;
  }
  int search(string& s) {
    Node* cur = root;
    for (int i = 0; i < szof(s); ++i) {
      int id = s[i] - 'a';
      if (cur->next[id] == NULL) return 0;
      cur = cur->next[id];
    }
    return cur->pathEnd;
  }
};

int main() {
  // freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(false); cin.tie(0);
  int test = 1, tc = 0;
  while (test--) {
    int n; cin >> n;
    Trie trie;
    for (int i = 1; i <= n; ++i) {
      string s; cin >> s;
      trie.add(s);
    }
    int q; cin >> q;
    while (q--) {
      string s; cin >> s;
      cout << trie.search(s) << nl;
    }
  }
  return 0;
}