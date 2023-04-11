#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
const int blockSize = 440;

vector<int> nums(N, 0), cnt(N, 0);
int disNum = 0;

struct MosData {
  int l, r, idx;
  bool operator < (const MosData& x) {
    if (l / blockSize == x.l / blockSize) {
      return ((l / blockSize) & 1) ? r > x.r : r < x.r;
    }
    return (l / blockSize) < (x.l / blockSize);
  }
};

void add(int idx) {
  cnt[nums[idx]]++;
  if (cnt[nums[idx]] == 1) disNum++;
}

void remove(int idx) {
  cnt[nums[idx]]--;
  if (cnt[nums[idx]] == 0) disNum--;
}

vector<int> MosAlgorithm(vector<MosData>& query) {
  int m = query.size();
  sort(query.begin(), query.end());
  vector<int> ans(m + 2, 0);
  disNum = 0;
  for (int i = 0; i < N; ++i) cnt[i] = 0;
  int curL = 1, curR = 0;
  for (auto x : query) {
    while (curL > x.l) add(--curL);
    while (curL < x.l) remove(curL++);
    while (curR > x.r) remove(curR--);
    while (curR < x.r) add(++curR);
    ans[x.idx] = disNum;
  }
  return ans;
}

int main() {
  // freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(false); cin.tie(0);
  int test, tc = 0; cin >> test;
  while (test--) {
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> nums[i];
    vector<MosData> query;
    for (int i = 1; i <= m; ++i) {
      int l, r; cin >> l >> r;
      query.push_back({l, r, i});
    }
    cout << "Case " << ++tc << ":\n";
    vector<int> ans = MosAlgorithm(query);
    for (int i = 1; i <= m; ++i) cout << ans[i] << '\n';
  }
  return 0;
}

// problem link : https://vjudge.net/contest/457653#problem/F