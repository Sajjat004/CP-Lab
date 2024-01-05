#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
vector<int> adj[N];
vector<int> visited(N, 0);

void dfs(int u) {
  visited[u] = 1;
  cout << " " << u;
  for (int v : adj[u]) {
    if (!visited[v]) {
      dfs(v);
    }
  }
}

int main() {
  freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(false); cin.tie(0);
  int n, m; cin >> n >> m;
  for (int i = 1; i <= m; ++i) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  cout << "DFS Order: ";
  dfs(1);
  cout << '\n';
  return 0;
}

/*
Time complexity: O(E + V)
E = number of edge
V = number of vertex
*/