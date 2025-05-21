#include <bits/stdc++.h>
using namespace std;

template<typename type> void coordinateCompress(vector<type>& nums) {
  vector<type> sorted = nums;
  sort(sorted.begin(), sorted.end());
  sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());
  
  for (int i = 0; i < nums.size(); i++) {
    nums[i] = lower_bound(sorted.begin(), sorted.end(), nums[i]) - sorted.begin(); 
  }

  // Original value of nums[i] can be obtained through sorted[nums[i]]
}

int32_t main() {
  ios_base::sync_with_stdio(false); cin.tie(0);

  int n; cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  coordinateCompress(a);
  for (int i = 0; i < n; i++) {
    cout << a[i] << ' ';
  }
  cout << '\n';
    
  return 0;
}
