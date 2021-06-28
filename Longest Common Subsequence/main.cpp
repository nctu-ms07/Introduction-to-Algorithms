#include <bits/stdc++.h>

using namespace std;

int main() {
  istream::sync_with_stdio(false);
  cin.tie(nullptr);

  string s1, s2;
  cin >> s1 >> s2;

  int s1_size = s1.size();
  int s2_size = s2.size();

  int ans[s1_size][s2_size];

  fill_n(&ans[0][0], s1_size * s2_size, 0);

  for (int i = 0; i < s1_size; i++) {
    if (s1[i] == s2[0]) {
      ans[i][0] = 1;
    }
  }

  for (int i = 0; i < s2_size; i++) {
    if (s2[i] == s1[0]) {
      ans[0][i] = 1;
    }
  }

  for (int i = 1; i < s1_size; i++) {
    for (int j = 1; j < s2_size; j++) {
      if (s1[i] == s2[j]) {
        ans[i][j] = ans[i - 1][j - 1] + 1;
      } else {
        ans[i][j] = max(ans[i - 1][j], ans[i][j - 1]);
      }
    }
  }

  cout << ans[s1_size - 1][s2_size - 1];

  return 0;
}