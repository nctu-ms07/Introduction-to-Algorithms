#include <bits/stdc++.h>

using namespace std;

int n, m;
int a[500000];
unordered_map<int, int> frequency;

int main() {
  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  int l, r, ans;
  while (m--) {
    cin >> l >> r;
    ++frequency[a[l]];
    ans = a[l];
    for (int i = l + 1; i < r; i++) {
      ++frequency[a[i]];
      if (frequency[a[i]] > frequency[ans]) {
        ans = a[i];
      }

      if (frequency[a[i]] == frequency[ans]) {
        ans = min(a[i], ans);
      }
    }

    cout << ans << endl;
    frequency.clear();
  }
  return 0;
}
