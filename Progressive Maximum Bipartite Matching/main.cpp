#include <bits/stdc++.h>

using namespace std;

struct Edge {
  int dest, flow;
  Edge *opposite = nullptr;
  Edge(int dest, int flow) {
    this->dest = dest;
    this->flow = flow;
  }
};

int n, m, k;
list<Edge> network[2002];
list<Edge *> residue_network[2002];
Edge *path[2002];

int bfs() {
  fill_n(path, m + n + 2, nullptr);
  queue<pair<int, int>> bfs_queue;
  bfs_queue.push({0, INT_MAX});
  while (!bfs_queue.empty()) {
    int vertex = bfs_queue.front().first;
    int flow = bfs_queue.front().second;
    bfs_queue.pop();

    for (Edge *edge  : residue_network[vertex]) {
      if (edge->dest != 0 && path[edge->dest] == nullptr && edge->flow > 0) {
        path[edge->dest] = edge->opposite;
        int new_flow = min(flow, edge->flow);
        if (edge->dest == 1) {
          return new_flow;
        }
        bfs_queue.push({edge->dest, new_flow});
      }
    }
  }

  return 0;
}

int main() {
  cin >> n >> m >> k;
  for (int i = 0; i < n; i++) {
    // 0 is source and 1 is sink
    // 2 to 2 + n - 1 is set U
    network[0].emplace_back(Edge(i + 2, 1));
    Edge *to = new Edge(i + 2, 1);
    Edge *back = new Edge(0, 0);
    to->opposite = back;
    back->opposite = to;
    residue_network[0].emplace_back(to);
    residue_network[i + 2].emplace_back(back);
  }

  for (int i = n + 2; i < n + 2 + m; i++) {
    // n + 2 to n + 2 + m - 1 is set V
    network[i].emplace_back(Edge(1, 1));
    Edge *to = new Edge(1, 1);
    Edge *back = new Edge(i, 0);
    to->opposite = back;
    back->opposite = to;
    residue_network[i].emplace_back(to);
    residue_network[1].emplace_back(back);
  }

  int u, v, augment_flow, matching = 0;
  while (k--) {
    cin >> u >> v;
    network[u + 2].emplace_back(Edge(v + n + 2, 1));
    Edge *to = new Edge(v + n + 2, 1);
    Edge *back = new Edge(u + 2, 0);
    to->opposite = back;
    back->opposite = to;
    residue_network[u + 2].emplace_back(to);
    residue_network[v + n + 2].emplace_back(back);

    while ((augment_flow = bfs())) {
      for (Edge *edge = path[1]; edge; edge = path[edge->dest]) {
        edge->flow += augment_flow;
        edge->opposite->flow -= augment_flow;
      }
      matching += augment_flow;
    }

    cout << matching << endl;
  }

  return 0;
}
