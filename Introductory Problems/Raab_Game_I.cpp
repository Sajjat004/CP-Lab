#include <bits/stdc++.h>
using namespace std;

void solution() {
  int n, a, b; cin >> n >> a >> b;
  if ((a + b) > n) {
    cout << "NO\n";
    return;
  }

  int draw = n - (a + b);
  vector<int> aTurns;
  vector<int> bTurns;
  for (int i = n - draw + 1; i <= n; ++i) {
    aTurns.push_back(i);
    bTurns.push_back(i);
  }

  n -= draw;
  if (n > 0 and (a == 0 or b == 0)) {
    cout << "NO\n";
    return;
  }

  vector<bool> aUsed(n + 1, false);
  vector<bool> bUsed(n + 1, false);
  int value = n;
  while (b > 0) {
    if (b == 1) {
      aTurns.push_back(1);
      aUsed[1] = true;
      bTurns.push_back(value);
      bUsed[value] = true;
    } else {
      aTurns.push_back(value - 1);
      aUsed[value - 1] = true;
      bTurns.push_back(value);
      bUsed[value] = true;
      value--;
    }
    b--;
  }

  int idx1 = 1, idx2 = 1;
  while (a > 0) {
    while (aUsed[idx1]) idx1++;
    while (bUsed[idx2]) idx2++;
    aTurns.push_back(idx1);
    bTurns.push_back(idx2);
    aUsed[idx1] = true;
    bUsed[idx2] = true;
    a--;
  }

  cout << "YES\n";
  for (int i = 0; i < aTurns.size(); ++i) {
    cout << aTurns[i] << ' ';
  }
  cout << '\n';
  for (int i = 0; i < bTurns.size(); ++i) {
    cout << bTurns[i] << ' ';
  }
  cout << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int tests; cin >> tests;
  while (tests--) {
    solution();
  }

  return 0;
}

// Problem Link: https://cses.fi/problemset/task/3399/
