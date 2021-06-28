#include <bits/stdc++.h>

using namespace std;

int main() {
  int n;
  cin >> n;
  char *s = new char[n];
  char *s_reverse = new char[n];
  for (int i = 0; i < n; i++) {
    cin >> s[i];
  }
  reverse_copy(s, s + n, s_reverse);

  // the longest subsequence without adjacent element from one sequence which length is n and another sequence which length is n
  int ans[n][n];
  fill_n(&ans[0][0], n * n, 0);

  for (int i = 0; i < 2 && i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (s[i] == s_reverse[j]) {
        ans[i][j]++;
      } else {
        if (i - 1 >= 0) {
          ans[i][j] = max(ans[i][j], ans[i - 1][j]);
        }
        if (j - 1 >= 0) {
          ans[i][j] = max(ans[i][j], ans[i][j - 1]);
        }
        if (i - 1 >= 0 && j - 1 >= 0) {
          ans[i][j] = max(ans[i][j], ans[i - 1][j - 1]);
        }
      }

      if (s[j] == s_reverse[i]) {
        ans[j][i] = 1;
      } else {
        if (j - 1 >= 0) {
          ans[j][i] = max(ans[j][i], ans[j - 1][i]);
        }
        if (i - 1 >= 0) {
          ans[j][i] = max(ans[j][i], ans[j][i - 1]);
        }
        if (j - 1 >= 0 && i - 1 >= 0) {
          ans[j][i] = max(ans[j][i], ans[j - 1][i - 1]);
        }
      }
    }
  }

  for (int i = 2; i < n; i++) {
    for (int j = 2; j < n; j++) {
      if (s[i] == s_reverse[j]) {
        ans[i][j] = max(ans[i - 1][j - 1], ans[i - 2][j - 2] + 1);
      } else {
        ans[i][j] = max(ans[i - 1][j], ans[i][j - 1]);
        ans[i][j] = max(ans[i][j], ans[i - 1][j - 1]);
      }
    }
  }

  cout << ans[n - 1][n - 1] << endl;
  delete[] s;
  delete[] s_reverse;
  return 0;
}
