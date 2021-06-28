#include <bits/stdc++.h>

using namespace std;

int main() {
  priority_queue<int> largest;

  int n, input;
  cin >> n;
  while (n--) {
    cin >> input;
    largest.push(input);
  }

  long cost = 0;
  int larger, smaller;
  while (largest.size() != 1) {
    larger = largest.top();
    largest.pop();
    smaller = largest.top();
    largest.pop();
    if (larger - smaller == 0) {
      continue;
    } else {
      cost += larger - smaller;
      largest.push(larger - smaller);
    }
  }
  cost += largest.top();
  cout << cost << endl;
  return 0;
}
