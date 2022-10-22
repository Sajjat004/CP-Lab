#include <bits/stdc++.h>
using namespace std;

#define nl '\n'

// complexity O (n) and n <= 1e7;
// mpf == minimum prime factor
// pr = prime number

const int N = (int) 1e7 + 7;

int mpf[N + 1];
vector<int> prime;
void seive() {
  for (int i = 2; i <= N; ++i) {
    if (mpf[i] == 0) {
      mpf[i] = i;
      prime.push_back(i);
    }
    for (int j = 0; j < prime.size() && prime[j] <= mpf[i] && i * prime[j] <= N; ++j) {
      mpf[i * prime[j]] = prime[j];
    }
  }
}

int main() {
  // freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(false); cin.tie(0);
  int test = 1, tc = 0;
  while (test--) {
    seive();
    for (auto x : prime) cout << x << " ";
    cout << nl;
  }
  return 0;
}
