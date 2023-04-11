#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
vector<int> v(N, 0);

class SparseTableMin {
  vector<vector<int>> sTable;
  int n;

  void build(int n) {
    for (int i = 1; i <= n; ++i) sTable[i][0] = v[i];
    for (int j = 1; (1 << j) <= n; ++j) {
      for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
        sTable[i][j] = min(sTable[i][j - 1], sTable[i + (1 << (j - 1))][j - 1]);
      }
    }
  }
public:
  SparseTableMin(int n) {
    this->n = n;
    sTable.resize(n + 5, vector<int>(24, 0));
    build(n);
  }

  int query(int l, int r) {
    int k = log2(r - l + 1);
    return min(sTable[l][k], sTable[r - (1 << k) + 1][k]);
  }
};

int main() {
  // freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(false); cin.tie(0);
  int n; cin >> n;
  for (int i = 1; i <= n; ++i) cin >> v[i];
  SparseTableMin sp(n);
  int m; cin >> m;
  while (m) {
    int l, r; cin >> l >> r;
    cout << sp.query(l, r) << '\n';
  }
  return 0;
}