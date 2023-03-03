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

vi g[N];
vi subTreeSize(N, 0), bit(N, 0), check;
vector<bool> deleted(N, 0);
ll sum;
vll cnt((1 << 20), 0), dp(N, 0), ans(N, 0);

void findSubTreeSize(int u, int par) {
  subTreeSize[u] = 1;
  for (int v : g[u]) {
    if (v == par or deleted[v]) continue;
    findSubTreeSize(v, u);
    subTreeSize[u] += subTreeSize[v];
  }
}

int getCentroid(int u, int par, int totalSize) {
  for (int v : g[u]) {
    if (v == par or deleted[v]) continue;
    if (subTreeSize[v] > totalSize / 2) return getCentroid(v, u, totalSize);
  }
  return u;
}

void update(int u, int par, int mask, int val) {
  mask ^= bit[u];
  cnt[mask] += val;
  for (int v : g[u]) {
    if (v == par or deleted[v]) continue;
    update(v, u, mask, val);
  }
}
// palindromes between two child of centroid node.
void solve(int u, int par, int mask) {
  mask ^= bit[u];
  dp[u] = 0;
  for (int x : check) {
    dp[u] += cnt[mask ^ x];
    sum += cnt[mask ^ x];
  }
  for (int v : g[u]) {
    if (v == par or deleted[v]) continue;
    solve(v, u, mask);
    dp[u] += dp[v];
  }
  ans[u] += dp[u];
}
// palindromes between centroid to child node
void solve2(int u, int par, int mask) {
  mask ^= bit[u];
  for (int x : check) if (x == mask) sum++;
  for (int v : g[u]) {
    if (v == par or deleted[v]) continue;
    solve2(v, u, mask);
  }
}

void decompose(int u, int par) {
  findSubTreeSize(u, par);
  int centroid = getCentroid(u, par, subTreeSize[u]);
  deleted[centroid] = 1;
  sum = 0;
  update(centroid, 0, 0, 1);
  for (int v : g[centroid]) {
    if (v == par or deleted[v]) continue;
    update(v, centroid, bit[centroid], -1);
    solve(v, centroid, 0);
    update(v, centroid, bit[centroid], 1);
  }
  for (int v : g[centroid]) {
    if (v == par or deleted[v]) continue;
    solve2(v, centroid, bit[centroid]);
  }
  update(centroid, 0, 0, -1);
  ans[centroid] += sum / 2;
  for (int v : g[centroid]) {
    if (v == par or deleted[v]) continue;
    decompose(v, centroid);
  }
}

int main() {
  // freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(false); cin.tie(0);
  int test = 1, tc = 0;
  while (test--) {
    int n; cin >> n;
    for (int i = 1; i < n; ++i) {
      int u, v; cin >> u >> v;
      g[u].push_back(v);
      g[v].push_back(u);
    }
    string s; cin >> s;
    for (int i = 0; i < n; ++i) {
      bit[i + 1] = (1 << s[i] - 'a');
    }
    check.push_back(0);
    for (char c = 'a'; c <= 't'; ++c) check.push_back(1 << (c - 'a'));
    decompose(1, 0);
    for (int i = 1; i <= n; ++i) cout << ans[i] + 1 << " ";
    cout << nl;
  }
  return 0;
}
// problem link: https://codeforces.com/contest/914/problem/E