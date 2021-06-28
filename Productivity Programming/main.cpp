#include <bits/stdc++.h>

using namespace std;

int main() {
  int n, m, k;
  cin >> n >> m >> k;

  int products[n];
  for (int i = 0; i < n; i++) {
    cin >> products[i];
    products[i] *= (n - i);
  }

  m -= n * k;

  if (m < 0) {
    cout << abs(m);
    return 0;
  }

  // maximum product that we can produce, which is less than its index
  int max_product[2 * m + 1];
  fill_n(max_product, 2 * m + 1, 0);
  for (int i = 0; i < n; i++) {
    for (int j = 2 * m; j >= products[i]; j--) {
      max_product[j] = max(max_product[j - products[i]] + products[i], max_product[j]);
    }
  }

  int ans = INT_MAX;
  for(int i = 0; i < 2 * m + 1; i++){
    ans = min(ans, abs(m - max_product[i]));
  }

  cout << ans;
  return 0;
}