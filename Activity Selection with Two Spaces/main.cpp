#include <bits/stdc++.h>

using namespace std;

struct Activity {
  unsigned int from, to;
};

int main() {
  int n;
  cin >> n;
  Activity activities[n];
  for (int i = 0; i < n; i++) {
    cin >> activities[i].from;
    cin >> activities[i].to;
  }

  if (n <= 2) {
    cout << n;
    return 0;
  }

  sort(activities, activities + n, [](Activity a, Activity b) { return a.to < b.to; });
  unsigned int space1 = 0;
  unsigned int space2 = activities[0].to;
  unsigned int ans = 1;

  for (int i = 1; i < n; i++) {
    if (activities[i].from < space1 && activities[i].from < space2) {
      continue;
    }

    if (space1 > space2) {
      if (activities[i].from >= space1) {
        space1 = activities[i].to;
      } else {
        space2 = activities[i].to;
      }
    } else {
      if (activities[i].from >= space2) {
        space2 = activities[i].to;
      } else {
        space1 = activities[i].to;
      }
    }
    ans++;
  }

  cout << ans;

  return 0;
}
