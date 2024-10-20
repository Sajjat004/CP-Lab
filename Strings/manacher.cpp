#include <bits/stdc++.h>
using namespace std;

class Manacher {
  vector<int> build(const string& s) {
    string t = "#";
    for (auto c : s) {
      t += c;
      t += '#';
    }

    int n = t.size();
    vector<int> r(n);

    for (int i = 0, j = 0; i < n; i++) {
      if (2 * j - i >= 0 && j + r[j] > i) r[i] = min(r[2 * j - i], j + r[j] - i);
      while (i - r[i] >= 0 && i + r[i] < n && t[i - r[i]] == t[i + r[i]])
        r[i] += 1;
      if (i + r[i] > j + r[j]) j = i;
      r[i]--;
    }

    return vector<int>(begin(r) + 1, end(r) - 1);
  }

  vector<int> vManacher;

public:
  Manacher(const string& s) {
    vManacher = build(s);
  }

  bool isPalindrome(int left, int right) {
    return vManacher[left + right] >= right - left + 1;
  }
};

int main() {
  // freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(false); cin.tie(0);

  string s; cin >> s;
  Manacher manacher(s);

  int q; cin >> q;
  while (q--) {
    int left, right; cin >> left >> right;
    if (manacher.isPalindrome(left, right)) cout << 1 << " ";
    else cout << 0 << " ";
  }
  cout << '\n';

  return 0;
}