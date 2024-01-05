#include <bits/stdc++.h>
using namespace std;


int lengthOfLIS(vector<int>& nums) {
  multiset<int> s;
  for (int& x : nums) {
    s.insert(x);
    auto it = s.lower_bound(x);
    it++;
    if (it != s.end()) {
      s.erase(it);
    }
  }
  return s.size();
}


int main() {
  // freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(false); cin.tie(0);
  int n; cin >> n;
  vector<int> a(n);
  for (int& x : a) cin >> x;
  cout << lengthOfLIS(a) << '\n';
  return 0;
}

/*
Time Complexity: O(NlogN)
*/