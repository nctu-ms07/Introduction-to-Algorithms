#include <bits/stdc++.h>

using namespace std;

int main() {
  int n;
  cin >> n;

  int a[n];
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  if (n == 1) {
    cout << a[0];
    return 0;
  }

  int ans[n];
  ans[0] = a[0];
  ans[1] = a[1];

  for (int i = 2; i < n; i++) {
    ans[i] = max(ans[i - 1], a[i] + ans[i - 2]);
  }

  cout << ans[n - 1];
  return 0;
}