// In the name of Allah, Most Gracious, Most Merciful.
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


class FenwickTree {
  vector<vector<int>> tree;
  int n;
public:
  FenwickTree(int m) {
    this->n = m;
    tree.resize(n + 2, vector<int>(n + 2, 0));
  }
  void update(int x, int y, int val) {
    while (x <= n) {
      int y1 = y;
      while (y1 <= n) {
        tree[x][y1] += val;
        y1 += (y1 & -y1);
      }
      x += (x & -x);
    }
  }
  int query(int x, int y) {
    int sum = 0;
    while (x > 0) {
      int y1 = y;
      while (y1 > 0) {
        sum += tree[x][y1];
        y1 -= (y1 & -y1);
      }
      x -= (x & -x);
    }
    return sum;
  }
  int query(int x1, int y1, int x2, int y2) {
    return query(x2, y2) - query(x1 - 1, y2) - query(x2, y1 - 1) + query(x1 - 1, y1 - 1);
  }
};

int main() {
  // freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(false); cin.tie(0);
  int test = 1, tc = 0; cin >> test;
  while (test--) {
    int q; cin >> q;
    const int limit = 1005;
    FenwickTree bit(limit);
    vector<vector<bool>> flag(limit + 1, vector<bool>(limit + 1, 0));
    cout << "Case " << ++tc << ":\n";
    while (q--) {
      int op; cin >> op;
      if (op == 0) {
        int x, y; cin >> x >> y;
        x++, y++;
        if (!flag[x][y]) {
          flag[x][y] = 1;
          bit.update(x, y, 1);
        }
      } else {
        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        x1++, y1++, x2++, y2++;
        cout << bit.query(x1, y1, x2, y2) << nl;
      }
    }
  }
  return 0;
}

// problem link: https://lightoj.com/problem/points-in-rectangle
