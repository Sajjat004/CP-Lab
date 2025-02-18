#include <bits/stdc++.h>
using namespace std;

struct Interval {
  int left, right;
  Interval(int l, int r) : left(l), right(r) {}
};

class IntervalOperations {
public:
  vector<Interval> getIntersections(const vector<Interval>& intervals1, const vector<Interval>& intervals2) {
    vector<Interval> result;
    int index1 = 0, index2 = 0;

    while (index1 < intervals1.size() && index2 < intervals2.size()) {
      int left = max(intervals1[index1].left, intervals2[index2].left);
      int right = min(intervals1[index1].right, intervals2[index2].right);

      if (left <= right) {
        result.emplace_back(left, right);
      }

      if (intervals1[index1].right < intervals2[index2].right) {
        index1++;
      } else {
        index2++;
      }
    }
    return result;
  }

  bool containsValue(const vector<Interval>& intervals, int x) {
    auto it = lower_bound(intervals.begin(), intervals.end(), x, 
      [](const Interval& interval, int value) {
        return interval.right < value;
      });

    return it != intervals.end() && it->left <= x && x <= it->right;
  }

  vector<Interval> mergeIntervals(vector<Interval> intervals) {
    if (intervals.empty()) return {};

    sort(intervals.begin(), intervals.end(), [](const Interval& a, const Interval& b) {
      return a.left < b.left;
    });

    vector<Interval> merged;
    merged.push_back(intervals[0]);

    for (const auto& interval : intervals) {
      Interval& last = merged.back();
      if (interval.left <= last.right) {
        last.right = max(last.right, interval.right);
      } else {
        merged.push_back(interval);
      }
    }
    return merged;
  }
};

vector<Interval> getValidRanges(int XOR, int w) {
  vector<Interval> result;
  int value = 0;

  for (int i = 29; i >= 0; --i) {
    bool xorBit = XOR & (1 << i);
    bool wBit = w & (1 << i);

    if (wBit) {
      value = value | (1 - xorBit) * (1 << i);
    } else {
      int leftRange = value | (1 - xorBit) * (1 << i);
      int rightRange = leftRange;
      for (int j = i - 1; j >= 0; --j) {
        rightRange = rightRange | (1 << j);
      }

      result.emplace_back(leftRange, rightRange);
      value = value | xorBit * (1 << i);
    }
  }
  result.emplace_back(value, value);

  return result;
}

void solve() {
  int n, q; cin >> n >> q;
  vector<int> w(n + 1);
  for (int i = n; i >= 1; --i) cin >> w[i];

  vector<vector<Interval>> intervals(n + 1);
  intervals[0].push_back(Interval(0, (1 << 30) - 1));
  IntervalOperations intervalOperations;
  int XOR = 0;

  for (int i = 1; i <= n; ++i) {
    vector<Interval> validRanges = getValidRanges(XOR, w[i]);
    vector<Interval> margedIntervals = intervalOperations.mergeIntervals(validRanges);
    intervals[i] = intervalOperations.getIntersections(intervals[i - 1], margedIntervals);
    XOR ^= w[i];
  }

  while (q--) {
    int x; cin >> x;
    int left = 1, right = n;
    int ans = n;

    while (left <= right) {
      int mid = (left + right) >> 1;
      if (intervalOperations.containsValue(intervals[mid], x)) {
        ans = mid;
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }

    cout << ans << " ";
  }
  cout << "\n";
}

int32_t main() {
  ios_base::sync_with_stdio(false); cin.tie(0);

  int test; cin >> test;
  while (test--) {
    solve();
  }
    
  return 0;
}

// Problem: https://codeforces.com/contest/2064/problem/D
