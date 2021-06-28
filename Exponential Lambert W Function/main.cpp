#include <bits/stdc++.h>

using namespace std;

double t, y, b;

double b_search(double left, double right) {
  double mid = (left + right) / 2;
  double result = mid * (log(mid) / log(b));

  if (result - y >= 1e-7 * result) {
    return b_search(left, mid);
  }

  if (result - y <= -1e-7 * result) {
    return b_search(mid, right);
  }

  return mid;
}

int main() {
  istream::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> t;
  while (t--) {
    cin >> y >> b;
    cout << fixed << setprecision(12) << b_search(0, INT_MAX) << endl;
  }

  return 0;
}