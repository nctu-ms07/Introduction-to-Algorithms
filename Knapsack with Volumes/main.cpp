#include <bits/stdc++.h>

using namespace std;

struct Item {
  int weight, volume, profit;
};

int main() {
  int n, W, V;
  cin >> n >> W >> V;

  Item items[n];
  for (int i = 0; i < n; i++) {
    cin >> items[i].weight >> items[i].volume >> items[i].profit;
  }

  // the profit that may includes items from 0 to n, which its total weight isn't bigger than w, total volume isn't bigger than v
  int ans[n][W + 1][V + 1];

  for (int w = 0; w <= W; w++) {
    for (int v = 0; v <= V; v++) {
      if (items[0].weight <= w && items[0].volume <= v) {
        ans[0][w][v] = items[0].profit;
      } else {
        ans[0][w][v] = 0;
      }
    }
  }

  for (int i = 1; i < n; i++) {
    for (int w = 0; w <= W; w++) {
      for (int v = 0; v <= V; v++) {
        if (items[i].weight > w || items[i].volume > v) {
          ans[i][w][v] = ans[i - 1][w][v];
        } else {
          ans[i][w][v] = max(ans[i - 1][w][v], ans[i - 1][w - items[i].weight][v - items[i].volume] + items[i].profit);
        }
      }
    }
  }

  cout << ans[n - 1][W][V];

  return 0;
}
