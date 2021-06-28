#include <bits/stdc++.h>

using namespace std;

int main() {
  istream::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  int a[n];
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  int ans[n], largest = a[0];
  for (int i = 0; i < n; i++) {
    if (largest > a[i]) {
      for (int j = i - 1; j >= 0;) {
        if (a[j] > a[i]) {
          ans[i] = j;
          // speed up using printf instead of cout
          printf("%d\n", a[j]);
          break;
        } else {
          j = ans[j];
        }
      }
    } else {
      ans[i] = -1;
      // speed up using printf instead of cout
      printf("-1\n");
      largest = a[i];
    }
  }

  return 0;
}
