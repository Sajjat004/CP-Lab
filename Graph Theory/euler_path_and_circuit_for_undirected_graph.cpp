#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
#define ff first
#define ss second

// all the edges should be in the same connected component
// #undirected graph: euler path: all degrees are even or exactly two of them are odd.
// #undirected graph: euler circuit: all degrees are even
// euler path in an undirected graph
// it also finds circuit if it exists

// https://cses.fi/problemset/task/1691/

vector<pair<int, int>> g[200005];
vector<int> used(200005, 0);

int main() {
  // freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(false); cin.tie(0);
  int test = 1, tc = 0;
  while (test--) {
    int n, m; cin >> n >> m;
    map<int, int> degree;
    for (int i = 1; i <= m; ++i) {
      int u, v; cin >> u >> v;
      g[u].push_back({v, i});
      g[v].push_back({u, i});
      degree[u]++;
      degree[v]++;
    }
    bool possible = 1;
    for (auto x : degree) if (x.second & 1) possible = 0;
    if (!possible) {
      cout << "IMPOSSIBLE" << nl;
      return 0;
    }
    vector<int> ans;
    stack<int> st;
    st.push(1);
    while (!st.empty()) {
      int u = st.top();
      bool done = 0;
      while (!g[u].empty()) {
        auto x = g[u].back();
        g[u].pop_back();
        int v = x.ff, id = x.ss;
        if (!used[id]) {
          st.push(v);
          used[id] = 1;
          done = 1;
          break;
        }
      }
      if (!done) {
        ans.push_back(u);
        st.pop();
      }
    }
    if ((ans.size() - 1) != m) cout << "IMPOSSIBLE" << nl;
    else {
      for (auto x : ans) cout << x << " ";
      cout << nl;
    }
  }
  return 0;
}
