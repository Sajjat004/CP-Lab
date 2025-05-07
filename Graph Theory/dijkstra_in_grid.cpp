struct State {
  int x, y, distance;
  State(int x, int y, int distance) : x(x), y(y), distance(distance) {}

  bool operator<(const State& other) const {
    return distance > other.distance; // Min-heap based on distance
  }
};

class Solution {
public:
  int minTimeToReach(vector<vector<int>>& moveTime) {
    int n = moveTime.size(), m = moveTime[0].size();

    vector<vector<int>> distance(n, vector<int>(m, INT_MAX));
    vector<vector<bool>> visited(n, vector<bool>(m, false));

    int dx[8] = { 0, -1, 0, 1, -1, -1, 1, 1 };
    int dy[8] = { -1, 0, 1, 0, -1, 1, 1, -1 };

    priority_queue<State> pq;
    pq.push(State(0, 0, 0));
    distance[0][0] = 0;

    while (!pq.empty()) {
      State current = pq.top();
      pq.pop();

      int x = current.x, y = current.y, dist = current.distance;

      if (visited[x][y]) continue;
      visited[x][y] = true;

      for (int i = 0; i < 4; ++i) {
        int newX = x + dx[i], newY = y + dy[i];
        if (newX >= 0 && newX < n && newY >= 0 && newY < m) {
          int newDist = max(distance[x][y], moveTime[newX][newY]) + 1;

          if (newDist < distance[newX][newY]) {
            distance[newX][newY] = newDist;
            pq.push(State(newX, newY, newDist));
          }
        }
      }
    }

    return distance[n - 1][m - 1];
  }
};

// Problem Link: https://leetcode.com/problems/find-minimum-time-to-reach-last-room-i/description/
