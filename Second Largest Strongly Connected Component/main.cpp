#include <bits/stdc++.h>

using namespace std;

int n, m;
list<int> edges[100000];
list<int> edges_transpose[100000];
bool visited[100000];
stack<int> dfs_finish_stack;

int scc_count = 0;
int scc_size[100000];

void dfs_traverse(int u) {
  visited[u] = true;
  for (int v : edges[u]) {
    if (!visited[v]) {
      dfs_traverse(v);
      dfs_finish_stack.emplace(v);
    }
  }
  dfs_finish_stack.emplace(u);
}

void dfs_transpose_traverse(int u, int &size) {
  visited[u] = true;
  size++;
  for (int v : edges_transpose[u]) {
    if (!visited[v]) {
      dfs_transpose_traverse(v, size);
    }
  }
}

int main() {
  istream::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;

  int u, v;
  while (m--) {
    cin >> u >> v;
    edges[u].emplace_back(v);
    edges_transpose[v].emplace_back(u);
  }

  fill_n(&visited[0], n, false);
  for (int i = 0; i < n; i++) {
    if (!visited[i]) {
      dfs_traverse(i);
    }
  }

  fill_n(&visited[0], n, false);
  while (!dfs_finish_stack.empty()) {
    if (!visited[dfs_finish_stack.top()]) {
      int size = 0;
      dfs_transpose_traverse(dfs_finish_stack.top(), size);
      scc_size[scc_count] = size;
      scc_count++;
    }
    dfs_finish_stack.pop();
  }

  if (scc_count < 2) {
    cout << 0;
  } else {
    sort(scc_size, scc_size + scc_count);
    cout << scc_size[scc_count - 2];
  }

  return 0;
}
