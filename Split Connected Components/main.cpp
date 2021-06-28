#include <bits/stdc++.h>

using std::cin;
using std::cout;
using std::endl;
using std::fill_n;
using std::stack;
using std::pair;
using std::make_pair;

int graph[5000][5000];
stack<pair<int, int>> operations;
stack<int> ans;

int *parent;
int *rank;

int find_representative(int vertex) {
  int representative;
  for (representative = vertex; representative != parent[representative]; representative = parent[representative]);
  while (vertex != parent[vertex]) {
    int tmp = vertex;
    vertex = parent[vertex];
    parent[tmp] = representative;
  }
  return representative;
}

int main() {
  int n, m, q;
  cin >> n >> m >> q;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      graph[i][j] = 0;
    }
  }

  int u, v;
  while (m--) {
    cin >> u >> v;
    graph[u][v]++;
    graph[v][u]++;
  }

  int i, j;
  while (q--) {
    cin >> i >> j;
    if (i >= 0) {
      graph[i][j]--;
      graph[j][i]--;
    }
    operations.push(make_pair(i, j));
  }

  parent = new int[n];
  rank = new int[n];
  for (int i = 0; i < n; i++) {
    parent[i] = i;
    rank[i] = 1;
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (graph[i][j] > 0) {
        u = find_representative(i);
        v = find_representative(j);

        if (u != v) {
          if (rank[u] > rank[v]) {
            parent[v] = u;
            rank[u] += rank[v];
          } else {
            parent[u] = v;
            rank[v] += rank[u];
          }
        }
      }
    }
  }

  while (!operations.empty()) {
    pair<int, int> operation = operations.top();
    operations.pop();
    if (operation.first >= 0) {
      graph[operation.first][operation.second]++;
      graph[operation.second][operation.first]++;

      if (graph[operation.first][operation.second] > 0) {
        u = find_representative(operation.first);
        v = find_representative(operation.second);

        if (u != v) {
          if (rank[u] > rank[v]) {
            parent[v] = u;
            rank[u] += rank[v];
          } else {
            parent[u] = v;
            rank[v] += rank[u];
          }
        }
      }
    } else {
      ans.push(rank[find_representative(operation.second)]);
    }
  }

  while (!ans.empty()) {
    cout << ans.top() << endl;
    ans.pop();
  }

  delete[] parent;
  delete[] rank;
}