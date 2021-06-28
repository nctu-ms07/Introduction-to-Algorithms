#include <bits/stdc++.h>

using namespace std;

int const m = pow(10, 9) + 7;

complex<long> mod(complex<long> com) {
  com.real((com.real() % m + m) % m);
  com.imag((com.imag() % m + m) % m);
  return com;
}

void fast_pow(complex<long> base, int n) {
  complex<long> ans(1, 0);
  while (n) {
    if (n & 1) { // n is odd
      ans = mod(ans * base);
    }
    base = mod(base * base);
    n >>= 1; // n /= 2
  }
  cout << ans.real() << " " << ans.imag() << endl;
}

int main() {
  //cin.tie(0);
  //cin.sync_with_stdio(0);

  int t = 1;
  //cin >> t;
  while (t--) {
    int a, b, n;
    cin >> a >> b >> n;
    fast_pow(complex<long>(a, b), n);
  }
  return 0;
}
