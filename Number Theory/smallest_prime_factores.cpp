#include <bits/stdc++.h>
using namespace std;

vector<int> smallestPrimeFactors(int n) {
  vector<int> spf(n + 1, 0);
  vector<int> primes;

  for (int i = 2; i <= n; i++) {
    if (spf[i] == 0) {
      spf[i] = i;
      primes.push_back(i);
    }

    for (int j = 0; j < (int)primes.size() && primes[j] <= spf[i] && i * primes[j] <= n; j++) {
      spf[i * primes[j]] = primes[j];
    }
  }

  return spf;
}

int32_t main() {
  ios_base::sync_with_stdio(false); cin.tie(0);

  int n; cin >> n;

  vector<int> spf = smallestPrimeFactors(n);
  for (int i = 1; i <= n; i++) {
    cout << i << ": " << spf[i] << '\n';
  }
    
  return 0;
}
