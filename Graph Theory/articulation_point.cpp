#include <bits/stdc++.h>
using namespace std;

void dfs(int node, int parent, int& timer, vector<vector<int>>& adjList, vector<int>& discoveryTime, vector<int>& low, vector<bool>& articulationPoints) {
  discoveryTime[node] = low[node] = ++timer;
  int cntChildren = 0;
  for (int neighbor : adjList[node]) {
    if (neighbor == parent) continue;
    if (discoveryTime[neighbor] == -1) {
      cntChildren++;
      dfs(neighbor, node, timer, adjList, discoveryTime, low, articulationPoints);
      low[node] = min(low[node], low[neighbor]);
      if (low[neighbor] >= discoveryTime[node] && parent != -1) {
        articulationPoints[node] = true;
      }
    } else {
      low[node] = min(low[node], discoveryTime[neighbor]);
    }
  }

  if (parent == -1 && cntChildren > 1) {
    articulationPoints[node] = true;
  }
}

void solution() {
  int n, m; cin >> n >> m;
  vector<vector<int>> adjList(n + 1, vector<int>());
  for (int i = 0; i < m; i++) {
    int u, v; cin >> u >> v;
    adjList[u].push_back(v);
    adjList[v].push_back(u);
  }

  vector<int> discoveryTime(n + 1, -1);
  vector<int> low(n + 1, -1);
  vector<bool> articulationPoints(n + 1, false);
  int timer = 0;
  for (int i = 1; i <= n; i++) {
    if (discoveryTime[i] == -1) {
      dfs(i, -1, timer, adjList, discoveryTime, low, articulationPoints);
    }
  }

  int countArticulationPoints = 0;
  for (int i = 1; i <= n; i++) {
    if (articulationPoints[i]) {
      countArticulationPoints++;
    }
  }

  cout << countArticulationPoints << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int tests = 1;
  while (tests--) {
    solution();
  }
    
  return 0;
}
