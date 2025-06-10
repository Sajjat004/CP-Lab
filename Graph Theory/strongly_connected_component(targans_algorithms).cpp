#include <bits/stdc++.h>
using namespace std;
 
void findSSC(int node, vector<vector<int>>& adjList, vector<bool>& presentInSt, vector<int>& discovery, vector<int>&low, int& timer, stack<int>& st, vector<vector<int>>& components) {
  discovery[node] = low[node] = ++timer;
  st.push(node);
  presentInSt[node] = true;
 
  for (int neighbor : adjList[node]) {
    if (discovery[neighbor] == -1) {
      findSSC(neighbor, adjList, presentInSt, discovery, low, timer, st, components);
      low[node] = min(low[node], low[neighbor]);
    } else if (presentInSt[neighbor]) {
      low[node] = min(low[node], discovery[neighbor]);
    }
  }
 
  if (discovery[node] == low[node]) {
    vector<int> component;
    while (true) {
      int top = st.top();
      st.pop();
      presentInSt[top] = false;
      component.push_back(top);
      if (top == node) break;
    }
    components.push_back(component);
  }
}
 
void solution() {
  int n, m; cin >> n >> m;
  vector<vector<int>> adjList(n + 1, vector<int>());
  for (int i = 0; i < m; ++i) {
    int u, v; cin >> u >> v;
    adjList[u].push_back(v);
  }
 
  vector<bool> presentInSt(n + 1, false);
  vector<int> discovery(n + 1, -1);
  vector<int> low(n + 1, 0);
  stack<int> st;
  vector<vector<int>> components;
  int timer = 0;
  for (int i = 1; i <= n; ++i) {
    if (discovery[i] == -1) {
      findSSC(i, adjList, presentInSt, discovery, low, timer, st, components);
    }
  }
 
  vector<int> kingdoms(n + 1, 0);
  for (int i = 0; i < components.size(); ++i) {
    for (int node : components[i]) {
      kingdoms[node] = i + 1;
    }
  }
  
  cout << components.size() << '\n';
  for (int i = 1; i <= n; ++i) {
    cout << kingdoms[i] << ' ';
  }
  cout << '\n';
}
 
int32_t main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int tests = 1;
  while (tests--) {
    solution();
  }
    
  return 0;
}

// Problem Link: https://cses.fi/problemset/task/1683/
