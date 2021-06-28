#include <bits/stdc++.h>

using namespace std;

int main() {
  istream::sync_with_stdio(0);
  cin.tie(0);

  priority_queue<int> largest; //maximum heap for any number that is smaller or equal than percentiles
  priority_queue<int, vector<int>, greater<> > smallest;//minimum heap for any number that is larger than percentiles

  int n, input, x; //x is the current percentiles
  double k;
  cin >> n >> k >> x;
  n--;
  k /= 100;
  while (n--) {
    cin >> input;
    if (input == 0) {
      cout << x << endl;
    } else {

      //theoretically k shouldn't be 0 since percentiles only ranged from 1 to 100
      if(k == 0){ // if k == 0, answer would just be the smallest number
        x = min(x, input);
        continue;
      }

      if (input <= x) {
        largest.push(input);
      } else {
        smallest.push(input);
      }

      int position = ceil(k * (largest.size() + smallest.size() + 1)); //current percentiles position

      if (position == largest.size()) {
        smallest.push(x);
        x = largest.top();
        largest.pop();
      }

      if (position == largest.size() + 2) {
        largest.push(x);
        x = smallest.top();
        smallest.pop();
      }
    }
  }

  return 0;
}