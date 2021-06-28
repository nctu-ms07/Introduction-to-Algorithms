#include <bits/stdc++.h>

using namespace std;

int n, m;

list<int> edges[20000];
list<int> edges_transpose[20000];
bool visited[20000];
stack<int> dfs_finish;

void dfs_traversal(int vertex) {
  visited[vertex] = true;
  for (int edge : edges[vertex]) {
    if (visited[edge]) {
      continue;
    }
    dfs_traversal(edge);
    dfs_finish.push(edge);
  }
  dfs_finish.push(vertex);
}

void dfs_transpose_traversal(int vertex, int &scc_size) {
  visited[vertex] = true;
  scc_size++;
  for (int edge : edges_transpose[vertex]) {
    if (visited[edge]) {
      continue;
    }
    dfs_transpose_traversal(edge, scc_size);
  }
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    cin >> n >> m;
    int u, v;
    while (m--) {
      cin >> u >> v;
      edges[u].emplace_back(v);
      edges_transpose[v].emplace_back(u);
    }

    fill_n(visited, n, false);
    for (int i = 0; i < n; i++) {
      if (!visited[i]) {
        dfs_traversal(i);
      }
    }

    fill_n(visited, n, false);
    int scc_size = 0;
    dfs_transpose_traversal(dfs_finish.top(), scc_size);

    for (int i = 0; i < n; i++) {
      edges[i].clear();
      edges_transpose[i].clear();
    }

    while (!dfs_finish.empty()) {
      dfs_finish.pop();
    }

    cout << (scc_size == n) << endl;
  }
  return 0;
}