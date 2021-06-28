#include <bits/stdc++.h>

using namespace std;

double W(double z) {
  double a0 = log(z);
  double e = exp(a0);
  double a1 = a0 - ((a0 * e - z) / ((a0 + 1) * e - ((a0 + 2) * (a0 * e - z) / (2 * a0 + 2))));
  while ( abs(a1 - a0) > 1e-6){
    a0 = a1;
    e = exp(a0);
    a1 = a0 - ((a0 * e - z) / ((a0 + 1) * e - ((a0 + 2) * (a0 * e - z) / (2 * a0 + 2))));
  }
  return a1;
}

int main() {
//  cin.tie(0);
//  cin.sync_with_stdio(0);

  int t = 1;
  //cin >> t;
  for (int cs = 1; cs <= t; cs++) {
    double y;
    cin >> y;
    cout << fixed << setprecision(12) << W(y) << '\n';
  }
  return 0;
}
