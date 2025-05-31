#include <bits/stdc++.h>
using namespace std;

struct Node {
  int maxPrefixSum;
  int maxSuffixSum;
  int totalSum;
  int maxSubarraySum;

  Node(int maxPrefixSum = 0, int maxSuffixSum = 0, int totalSum = 0, int maxSubarraySum = 0)
      : maxPrefixSum(maxPrefixSum), maxSuffixSum(maxSuffixSum), totalSum(totalSum), maxSubarraySum(maxSubarraySum) {}
};

class DynamicMaxSubArraySum {
  vector<Node> tree;
  int n;

  Node merge(const Node &leftNode, const Node &rightNode) {
    Node result;
    result.maxPrefixSum = max(leftNode.maxPrefixSum, leftNode.totalSum + rightNode.maxPrefixSum);
    result.maxSuffixSum = max(rightNode.maxSuffixSum, rightNode.totalSum + leftNode.maxSuffixSum);
    result.totalSum = leftNode.totalSum + rightNode.totalSum;
    result.maxSubarraySum = max({leftNode.maxSubarraySum, rightNode.maxSubarraySum, leftNode.maxSuffixSum + rightNode.maxPrefixSum});
    
    return result;
  }

  void update(int node, int start, int end, int index, int value) {
    if (index < start || index > end) return;
    if (start == end) {
      tree[node].maxPrefixSum = value;
      tree[node].maxSuffixSum = value;
      tree[node].totalSum = value;
      tree[node].maxSubarraySum = value;
      
      return;
    }

    int mid = (start + end) / 2;
    update(2 * node, start, mid, index, value);
    update(2 * node + 1, mid + 1, end, index, value);
    tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
  }

  Node query(int node, int start, int end, int left, int right) {
    if (left > end || right < start) return Node();
    if (left <= start && end <= right) return tree[node];

    int mid = (start + end) / 2;
    Node leftResult = query(2 * node, start, mid, left, right);
    Node rightResult = query(2 * node + 1, mid + 1, end, left, right);
    return merge(leftResult, rightResult);
  }

public:
  DynamicMaxSubArraySum(int n) : n(n) {
    tree.resize(4 * n, Node());
  }

  void update(int index, int value) {
    update(1, 1, n, index, value);
  }

  int query(int left, int right) {
    Node result = query(1, 1, n, left, right);
    return result.maxSubarraySum;
  }
};

void solution() {
  int n; cin >> n;
  vector<int> x(n + 1);
  for (int i = 1; i <= n; ++i) {
    cin >> x[i];
  }

  map<int, vector<int>> positions;
  for (int i = 1; i <= n; ++i) {
    positions[x[i]].push_back(i);
  } 

  DynamicMaxSubArraySum dms(n);
  for (int i = 1; i <= n; ++i) {
    dms.update(i, -1);
  }

  int maxSum = 0, valueForMaxSum = 0;
  for (const auto& [value, pos] : positions) {
    for (int index : pos) {
      dms.update(index, 1);
    }
    
    int currentMax = dms.query(1, n);
    if (currentMax > maxSum) {
      maxSum = currentMax;
      valueForMaxSum = value;
    }

    for (int index : pos) {
      dms.update(index, -1);
    }
  }

  vector<int> temp(n + 1, 0);
  for (int i = 1; i <= n; ++i) {
    temp[i] = x[i] == valueForMaxSum ? 1 : -1;
  }

  int leftIndex = 1, rightIndex = n, prefixSum = 0, maxPrefixSum = 0, len = 0;
  for (int i = 1; i <= n; ++i) {
    prefixSum += temp[i];
    len++;
    if (prefixSum > maxPrefixSum) {
      maxPrefixSum = prefixSum;
      rightIndex = i;
      leftIndex = i - len + 1;
    }
    if (prefixSum < 0) {
      prefixSum = 0;
      len = 0;
    }
  }

  cout << valueForMaxSum << ' ' << leftIndex << ' ' << rightIndex << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int tests; cin >> tests;
  while (tests--) {
    solution();
  }
  
  return 0;
}

// Problem Link: https://codeforces.com/problemset/problem/1692/H
