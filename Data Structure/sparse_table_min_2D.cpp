#include <bits/stdc++.h>
using namespace std;

class SparseTableSum2D {
  vector<vector<vector<vector<int>>>> sTable;
  int n, m, logN, logM;

  void build(vector<vector<int>>& v) {
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= m; ++j) {
        sTable[i][0][j][0] = v[i][j];
      }
      for (int l = 1; l <= logM; ++l) {
        for (int j = 1; j + (1 << l) - 1 <= m; ++j) {
          sTable[i][0][j][l] = min(sTable[i][0][j][l - 1], sTable[i][0][j + (1 << (l - 1))][l - 1]);
        }
      }
    }
    for (int k = 1; k <= logN; ++k) {
      for (int i = 1; i + (1 << k) - 1 <= n; ++i) {
        for (int l = 1; l <= logM; ++l) {
          for (int j = 1; j + (1 << l) - 1 <= m; ++j) {
            sTable[i][k][j][l] = min(sTable[i][k - 1][j][l], sTable[i + (1 << (k - 1))][k - 1][j][l]);
          }
        }
      }
    }
  }
public:
  SparseTableSum2D(int n, int m, vector<vector<int>>& v) {
    this->n = n;
    this->m = m;
    logN = log2(n);
    logM = log2(m);
    sTable.assign(n + 2, vector<vector<vector<int>>> (logN + 2, vector<vector<int>> (m + 2, vector<int> (logM + 2, 0))));
    build(v);
  }

  int query(int x1, int y1, int x2, int y2) {
    int logX = log2(x2 - x1 + 1);
    int logY = log2(y2 - y1 + 1);
    int mxR1 = min(sTable[x1][logX][y1][logY], sTable[x1][logX][y2 - (1 << logY) + 1][logY]);
    int mxR2 = min(sTable[x2 - (1 << logX) + 1][logX][y1][logY], sTable[x2 - (1 << logX) + 1][logX][y2 - (1 << logY) + 1][logY]);
    return min(mxR1, mxR2);
  }
};

int main() {
  // freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(false); cin.tie(0);
  int n, m; cin >> n >> m;
  vector<vector<int>> v(n + 2, vector<int>(m + 2, 0));
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) cin >> v[i][j];
  }
  SparseTableSum2D sp(n, m, v);
  int q; cin >> q;
  while (q--) {
    int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
    cout << sp.query(x1, y1, x2, y2) << '\n';
  }
  return 0;
}