#include <bits/stdc++.h>
using namespace std;

struct State {
  int x, y;
  State(int x, int y) : x(x), y(y) {}

  bool operator<(const State& other) const {
    return x > other.x; // Min-heap based on x
  }
};

int32_t main() {
  ios_base::sync_with_stdio(false); cin.tie(0);

  // Example of custom class comparator usage in a priority queue
  priority_queue<State> pq;
  pq.push(State(1, 2));
  pq.push(State(3, 4));
  pq.push(State(0, 5));
  pq.push(State(2, 6));
  pq.push(State(4, 7));

  while (!pq.empty()) {
    State current = pq.top();
    pq.pop();
    cout << "State: (" << current.x << ", " << current.y << ")\n";
  }
  cout << "\n";

  // Example of custom lambda comparator usage in a priority queue
  auto cmp = [&](pair<int, int> a, pair<int, int> b) {
    return a.first > b.first; // Min-heap based on the first element of the pair
  };
  
  priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq1(cmp);
  pq1.push({1, 2});
  pq1.push({3, 4});
  pq1.push({0, 5});
  pq1.push({2, 6});
  pq1.push({4, 7});

  while (!pq1.empty()) {
    pair<int, int> current = pq1.top();
    pq1.pop();
    cout << "Pair: (" << current.first << ", " << current.second << ")\n";
  }
    
  return 0;
}
