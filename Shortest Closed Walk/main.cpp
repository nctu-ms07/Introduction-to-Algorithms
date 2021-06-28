#include <bits/stdc++.h>

#define INF LLONG_MAX >> 4

using namespace std;

struct Node {
  int index;
  long long value;

  Node(int index, long long value) {
    this->index = index;
    this->value = value;
  }

  bool operator<(const Node vertex) const {
    return value > vertex.value;
  }
};

int n, m, u, v, w;
list<Node> edges[100000];
bool visited[10000];
long long path_length[10000];
priority_queue<Node> q;

void dijkstra(int source) {
  fill_n(path_length, n, INF);
  fill_n(visited, n, false);
  path_length[source] = 0;
  q.push(Node(source, 0));

  while (!q.empty()) {
    Node vertex = q.top();
    q.pop();

    if (visited[vertex.index]) {
      continue;
    }

    visited[vertex.index] = true;
    for (Node edge : edges[vertex.index]) {
      if (path_length[edge.index] > vertex.value + edge.value) {
        path_length[edge.index] = vertex.value + edge.value;
        q.push(Node(edge.index, path_length[edge.index]));
      }
    }
  }
}

long long u_v, v_w, w_u;
long long u_w, w_v, v_u;

int main() {
  istream::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m >> u >> v >> w;

  int i, j, k;
  while (m--) {
    cin >> i >> j >> k;
    edges[i].emplace_back(Node(j, k));
  }

  dijkstra(u);
  u_v = path_length[v];
  u_w = path_length[w];

  dijkstra(v);
  v_u = path_length[u];
  v_w = path_length[w];

  dijkstra(w);
  w_u = path_length[u];
  w_v = path_length[v];

  long long ans = min(u_v + v_w + w_u, u_w + w_v + v_u);
  cout << (ans > INF ? -1 : ans);

  return 0;
}
