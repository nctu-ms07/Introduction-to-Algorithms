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
list<Edge> network[1024];
list<Edge *> residue_network[1024];
Edge *path[1024];

int total_profit = 0;

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
  int flow;
  for (int i = 0; i < n; i++) {
    cin >> flow;
    // 0 is source and 1 is sink
    // 2 to 2 + n - 1 is tool
    network[0].emplace_back(Edge(i + 2, flow));
    Edge *to = new Edge(i + 2, flow);
    Edge *back = new Edge(0, 0);
    to->opposite = back;
    back->opposite = to;
    residue_network[0].emplace_back(to);
    residue_network[i + 2].emplace_back(back);
  }

  for (int i = n + 2; i < n + 2 + m; i++) {
    cin >> flow;
    total_profit += flow;
    // n + 2 to n + 2 + m - 1 is product
    network[i].emplace_back(Edge(1, flow));
    Edge *to = new Edge(1, flow);
    Edge *back = new Edge(i, 0);
    to->opposite = back;
    back->opposite = to;
    residue_network[i].emplace_back(to);
    residue_network[1].emplace_back(back);
  }

  int tool, product;
  while (k--) {
    cin >> tool >> product;
    network[tool + 2].emplace_back(Edge(product + n + 2, INT_MAX));
    Edge *to = new Edge(product + n + 2, INT_MAX);
    Edge *back = new Edge(tool + 2, 0);
    to->opposite = back;
    back->opposite = to;
    residue_network[tool + 2].emplace_back(to);
    residue_network[product + n + 2].emplace_back(back);
  }

  int augment_flow;
  while ((augment_flow = bfs())) {
    for (Edge *edge = path[1]; edge; edge = path[edge->dest]) {
      edge->flow += augment_flow;
      edge->opposite->flow -= augment_flow;
    }
    total_profit -= augment_flow;
  }

  cout << total_profit;
  return 0;
}
