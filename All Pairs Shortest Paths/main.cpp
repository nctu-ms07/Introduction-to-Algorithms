#include <bits/stdc++.h>

#define INF INT_MAX >> 4

using namespace std;

int graph[500][500];

int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int w;
      cin >> w;
      if (w == 0) {
        graph[i][j] = INF;
      } else {
        graph[i][j] = 1;
      }
    }
  }

  for (int intermediate = 0; intermediate < n; intermediate++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (i != j) {
          graph[i][j] = min(graph[i][intermediate] + graph[intermediate][j], graph[i][j]);
        } else {
          graph[i][j] = 0;
        }
      }
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (graph[i][j] >= INF) {
        cout << -1;
      } else {
        cout << graph[i][j];
      }
      cout << ' ';
    }
    cout << endl;
  }

  return 0;
}