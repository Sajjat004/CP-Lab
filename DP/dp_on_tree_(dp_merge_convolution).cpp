class Solution {
public:
  int maxProfit(int n, vector<int>& present, vector<int>& future, vector<vector<int>>& hierarchy, int budget) {
    vector<vector<int>> tree(n);
    for (const auto& edge : hierarchy) {
      tree[edge[0] - 1].push_back(edge[1] - 1);
    }

    vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(budget + 1, -1)));
    findMaxProfit(0, present, future, tree, dp, budget);

    int totalProfit = 0;
    for (int b = 0; b <= budget; ++b) {
      totalProfit = max(totalProfit, dp[0][0][b]);
    }

    return totalProfit;
  }

private:
  void findMaxProfit(int node, const vector<int>& present, const vector<int>& future, const vector<vector<int>>& tree, vector<vector<vector<int>>>& dp, int budget) {
    // store children's DP results
    vector<vector<vector<int>>> childDPS;
    for (int child : tree[node]) {
      findMaxProfit(child, present, future, tree, dp, budget);
      childDPS.push_back({dp[child][0], dp[child][1]});
    }

    for (int parentBought = 0; parentBought <= 1; ++parentBought) {
      int price = parentBought ? present[node] / 2 : present[node];
      int profit = future[node] - price;

      vector<int> currentDP(budget + 1, 0);

      // don't buy from this node
      vector<int> baseDP(budget + 1, 0);
      for (const auto& childDP : childDPS) {
        vector<int> nextDP(budget + 1, 0);
        for (int b1 = 0; b1 <= budget; ++b1) {
          if (baseDP[b1] == 0 and b1 != 0) continue;
          for (int b2 = 0; b1 + b2 <= budget; ++b2) {
            nextDP[b1 + b2] = max(nextDP[b1 + b2], baseDP[b1] + childDP[0][b2]);
          }
        }

        baseDP = move(nextDP);
      }

      for (int b = 0; b <= budget; ++b) {
        currentDP[b] = max(currentDP[b], baseDP[b]);
      }

      // buy from this node
      if (price <= budget) {
        baseDP = vector<int>(budget + 1, 0);
        for (const auto& childDP : childDPS) {
          vector<int> nextDP(budget + 1, 0);
          for (int b1 = 0; b1 <= budget; ++b1) {
            if (baseDP[b1] == 0 and b1 != 0) continue;
            for (int b2 = 0; b1 + b2 <= budget; ++b2) {
              nextDP[b1 + b2] = max(nextDP[b1 + b2], baseDP[b1] + childDP[1][b2]);
            }
          }

          baseDP = move(nextDP);
        }

        for (int b = price; b <= budget; ++b) {
          currentDP[b] = max(currentDP[b], baseDP[b - price] + profit);
        }
      }

      dp[node][parentBought] = move(currentDP);
    }
  }
};

// Problem Link: https://leetcode.com/problems/maximum-profit-from-trading-stocks-with-discounts/description/
