#include <bits/stdc++.h>
using namespace std;

#define nl '\n'

const int N = (int) 1e7 + 7;

bool isOn(int n, int at) { return (bool) (n & (1 << at)); }
int bitOn(int n, int at) { return n = n | (1 << at); }

int vis[(N >> 5) + 2];
vector<int> prime;

// complexity O(nloglogn)
void bitwiseSieve() {
  vis[1 >> 5] = bitOn(vis[1 >> 5], 1 & 31);
  for (int i = 4; i <= N; i += 2) {
    vis[i >> 5] = bitOn(vis[i >> 5], i & 31);
  }
  for (int i = 3; i * i <= N; i += 2) {
    if (!isOn(vis[i >> 5], i & 31)) {
      for (int j = i * i; j <= N; j += (2 * i)) {
        vis[j >> 5] = bitOn(vis[j >> 5], j & 31);
      }
    }
  }
  for (int i = 2; i <= N; ++i) {
    if (!isOn(vis[i >> 5], i & 31)) {
      prime.push_back(i);
    }
  }
}

int main() {
  // freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(false); cin.tie(0);
  int test = 1, tc = 0;
  while (test--) {
    bitwiseSieve();
    for (auto x : prime) cout << x << " ";
    cout << nl;
  }
  return 0;
}
